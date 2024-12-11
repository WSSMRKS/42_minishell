/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/11 16:43:11 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_search_tmp(void)
{
	int		nb;
	char	*filename;
	char	*number;

	nb = 1;
	while (nb < INT_MAX)
	{
		number = ft_itoa(nb);
		filename = ft_strjoin("/tmp/ms_tmp_", number);
		free(number);
		number = NULL;
		if (access(filename, F_OK) != 0)
			break ;
		free(filename);
		filename = NULL;
		nb++;
	}
	return (filename);
}

void	ft_garbage_add(char *filename, t_ms *ms)
{
	int				i;
	t_list_hdfiles	*curr;

	i = 1;
	curr = ms->be->garbage->heredoc;
	if (ms->be->garbage->nb_heredocs == 0)
	{
		curr = ft_calloc(sizeof(t_list_hdfiles), 1);
		curr->next = NULL;
		ms->be->garbage->heredoc = curr;
	}
	else
	{
		while (i++ < ms->be->garbage->nb_heredocs)
			curr = curr->next;
		curr->next = ft_calloc(sizeof(t_list_hdfiles), 1);
		curr->next->next = NULL;
		curr = curr->next;
	}
	curr->filename = ft_strdup(filename);
	ms->be->garbage->nb_heredocs += 1;
}

char	*ft_tmp_name(t_ms *ms, int *fd)
{
	char		*filename;

	filename = ft_search_tmp();
	*fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*fd < 1)
		exit(EBADF);
	else
		ft_garbage_add(filename, ms);
	return (filename);
}

void	handle_sigint_hd(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	rl_replace_line("", 0);
	ioctl(STDOUT_FILENO, TIOCSTI, "\n");
}

/*heredoc insights:
	- several heredocs in one command are handled left to right.
	  only the most left here doc is handled.
	- even over several pipes heredoc is handled left to right.
*/
void	ft_here_doc(t_ms *ms)
{
	t_cmd_list			*cmd_list;
	t_list_redir		*curr_redir;
	struct sigaction	sa_int_hd;

	sa_int_hd.sa_handler = &handle_sigint_hd;
	sa_int_hd.sa_flags = SA_RESTART;
	sigemptyset(&sa_int_hd.sa_mask);
	sigaction(SIGINT, &sa_int_hd, NULL);
	cmd_list = ms->cmds;
	while ((ms->global_flags & 1) != 0 && cmd_list != NULL && g_signal != 130)
	{
		curr_redir = cmd_list->cmd.redir;
		while (cmd_list->cmd.heredoc && curr_redir != NULL && g_signal != 130)
		{
			if (curr_redir->instruction == redir_here_doc)
				ft_hd_input(curr_redir, ms);
			curr_redir = curr_redir->next;
		}
		cmd_list = cmd_list->next;
	}
	if (!signal(SIGINT, SIG_DFL))
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
}
