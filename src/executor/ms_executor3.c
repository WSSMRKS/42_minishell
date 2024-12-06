/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/06 16:22:48 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_pipe_reset(t_ms *ms, int *i)
{
	if (close(ms->be->pipes[(*i - 1) & 1][0])
	|| close(ms->be->pipes[(*i - 1) & 1][1]))
		perror("ms");
	pipe(ms->be->pipes[(*i - 1) & 1]);
}

void	ft_execute(t_ms *ms, t_cmd_list *curr, int *i)
{
	if (ms->be->child_pids[*i] == 0)
	{
		ft_close_all_fds(ms);
		if (curr->cmd.builtin == true)
			ft_builtin(ms, curr, i);
		else
			ft_ms_execve(ms, curr);
	}
	else if (curr->cmd.builtin && ms->be->nb_cmds == 1)
	{
		if (ms->be->redir_err == 0)
		{
			g_signal = ft_builtin(ms, curr, i);
			dup2(ms->be->saved_std[0], STDIN_FILENO);
			dup2(ms->be->saved_std[1], STDOUT_FILENO);
		}
		close(ms->be->saved_std[0]);
		close(ms->be->saved_std[1]);
	}
}

void	ft_fork(t_ms *ms, t_cmd_list *curr, int *i)
{
	if (!curr->cmd.builtin || ms->be->nb_cmds > 1)
		ms->be->child_pids[*i] = fork();
	else
	{
		ms->be->child_pids[*i] = ft_grab_pid();
		ft_safe_std(ms);
	}
	if (ms->be->child_pids[*i] < 0)
	{
		perror("fork failed");
		ft_cleanup_exit(ms, EPIPE);
	}
	if (ms->be->child_pids[*i] == 0
		|| (curr->cmd.builtin && ms->be->nb_cmds == 1))
		ft_ex_prep(ms, curr, i);
	ft_execute(ms, curr, i);
	if (*i > 0 && ms->be->child_pids[*i] != 0)
		ft_pipe_reset(ms, i);
}

void	ft_is_builtin(t_cmd_list *curr, t_ms *ms)
{
	int		i;
	int		len;

	i = -1;
	while (ms->cmds->cmd.words && ms->be->builtins[++i])
	{
		len = ft_strlen(ms->be->builtins[i]);
		if (ft_strncmp(curr->cmd.words->word, ms->be->builtins[i], len) == 0
			&& (int) ft_strlen(curr->cmd.words->word) == len)
		{
			curr->cmd.builtin = true;
			curr->cmd.builtin_nr = i + 1;
		}
	}
}

void	ft_execution(t_ms *ms)
{
	t_cmd_list			*curr;
	int					i;

	curr = ms->cmds;
	i = 0;
	while (curr)
	{
		ft_is_builtin(curr, ms);
		ft_fork(ms, curr, &i);
		curr = curr->next;
		i++;
	}
}
