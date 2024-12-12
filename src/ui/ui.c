/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/12 04:26:35 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	cmdlist_has_heredoc(t_cmd_list *cmds)
{
	t_cmd_list	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->cmd.heredoc)
			return (true);
		curr = curr->next;
	}
	return (false);
}

static t_ms_status	evaluate(t_ms *ms)
{
	if (ms->cmds)
	{
		ms->global_flags = cmdlist_has_heredoc(ms->cmds);
		ft_back_end(ms);
		ms->cmds = NULL;
	}
	return (MS_OK);
}

// Signal handler for SIGINT (Ctrl+C)
static void handle_sigint(int sig) {
	(void) sig;
	g_signal = 128 + SIGINT;
	// printf("\nCaught signal %d (SIGINT), ignoring Ctrl+C\n", sig);
	printf("\n");
	// Re-prompt the user after ignoring SIGINT
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	reinit_sigint_handler(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = &handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	if (g_signal != 0)
		g_signal = 0;
}

/// Str can be either one line with one command pipeline or multiple lines with
/// multiple command pipelines.
/// Those lines are added to history seperately.
static void	add_lines_to_history(const char *str)
{
	char	**lines;
	size_t	i;

	i = 0;
	lines = ft_split(str, '\n');
	if (!lines)
		return ;
	while (lines[i])
	{
		add_history(lines[i]);
		i++;
	}
	ft_free_2d(lines);
}

void	repl(t_ms *ms)
{
	t_ms_status	status;

	while (true)
	{
		reinit_sigint_handler();
		status = parse_next_command(&ms->parser, &ms->cmds);
		if (status == MS_EOF)
			break ;
		else if (status == MS_ERROR)
		{
			perror("error while parsing");
			break ;
		}
		if (ms->parser.last_input.len > 0)
			add_lines_to_history(cstr_ref(&ms->parser.last_input));
		if (evaluate(ms) != MS_OK)
			break ;
	}
	if (status == MS_EOF && isatty(STDIN))
		ft_printf("exit\n");
	if (g_signal)
		ft_cleanup_exit(ms, g_signal);
	else
		ft_cleanup_exit(ms, ms->be->last_ret);
}
