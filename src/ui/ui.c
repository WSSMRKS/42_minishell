/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/26 10:22:14 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <readline/readline.h>

static bool	is_dot(const char *c)
{
	return (*c == '.');
}

t_str	get_trunc_hostname(void)
{
	t_str	hostname;
	size_t	hostname_colon;

	hostname = str_from2(ft_hostname());
	str_trim(&hostname);
	if (str_find(&hostname, is_dot, &hostname_colon))
		str_remove_range(&hostname, hostname_colon, hostname.len);
	return (hostname);
}

/// @brief Get the prompt string for the REPL
/// @param ms The minishell struct
/// @return The prompt string "ms/$USER@<hostname>:$PWD$ "
static char	*get_prompt(t_ms *ms)
{
	t_str		out;
	t_str_slice	user;
	t_str		user_home;
	t_str		hostname;
	t_str		pwd;

	out = str_clone_from(cstr_slice("ms/", 3));
	str_pushstr(&out, cstr_view(GREEN));
	user = cstr_view(ft_lookup_symtab(ms->be->global_symtabs, "USER"));
	if (user.len == 0)
		user = cstr_slice("?", 1);
	user_home = str_clone_from(cstr_slice("/home/", 6));
	str_pushstr(&user_home, user);
	str_pushstr(&out, user);
	str_pushstr(&out, cstr_slice("@", 1));
	hostname = get_trunc_hostname();
	if (hostname.len == 0)
		str_push(&hostname, '?');
	str_pushstr(&out, str_view(&hostname));
	str_destroy(&hostname);
	str_pushstr(&out, cstr_view(WHITE));
	str_push(&out, ':');
	str_pushstr(&out, cstr_view(GREEN));
	pwd = str_clone_from(cstr_view(ft_lookup_symtab(ms->be->global_symtabs, "PWD")));
	if (pwd.len == 0)
		str_push(&out, '?');
	if (str_starts_with(&pwd, &user_home))
	{
		str_remove_range(&pwd, 0, user_home.len);
		str_push_front(&pwd, '~');
	}
	str_destroy(&user_home);
	str_pushstr(&out, str_view(&pwd));
	str_destroy(&pwd);
	str_pushstr(&out, cstr_view(RESET));
	str_pushstr(&out, cstr_slice("$ ", 2));
	return (cstr_take(&out));
}

static char *read_input(bool append_mode, void *data)
{
	char		*prompt;
	char		*input;

	(void)data;
	if (!isatty(STDIN))
	{
		input = get_next_line(STDIN);
		if (input && *input && input[ft_strlen(input) - 1] == '\n')
			input[ft_strlen(input) - 1] = '\0';
		return (input);
	}
	prompt = get_prompt(data);
	if (append_mode)
		input = readline("> ");
	else
		input = readline(prompt);
	free(prompt);
	return (input);
}

static t_symtab_stack	*get_symtab(void *data)
{
	t_ms	*ms;

	ms = (t_ms *)data;
	return (ms->be->global_symtabs);
}

static int	get_last_ret(void *data)
{
	t_ms	*ms;

	ms = (t_ms *)data;
	return (ms->be->last_ret);
}

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
	// if (ms->cmds && ms->cmds->cmd && strcmp("exit", ms->cmds->cmd->argv[0]) == 0)
	// 	return (MS_EOF);
	if (ms->cmds)
	{
		ms->global_flags = cmdlist_has_heredoc(ms->cmds);
		ft_back_end(ms);
		ms->cmds = NULL;
	}
	return (MS_OK);
}

void	repl(int argc, char **argv, char **envp)
{
	t_ms		ms;
	t_ms_status	status;

	ms.parser = parser_init(&ms, read_input, get_symtab, get_last_ret);
	ft_init_ms(&ms);
	ft_init_be(&ms, argc, argv, envp);
	while (true) // read eval print loop REPL
	{
		status = parse_next_command(&ms.parser, &ms.cmds);
		if (status == MS_EOF)
			break ;
		else if (status == MS_ERROR)
		{
			perror("parse (memory) error");
			break ;
		}
		if (ms.parser.last_input.len > 0)
			add_history(cstr_ref(&ms.parser.last_input));
		status = evaluate(&ms);
		if (status != MS_OK)
			break ;
	}
	if (status == MS_EOF && isatty(STDIN))
		ft_printf("exit\n");
	get_next_line_finish(STDIN);
	ft_cleanup_exit(&ms, 0);
}
