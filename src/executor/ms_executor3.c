/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/11 01:03:05 by kwurster         ###   ########.fr       */
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
			ft_builtin(ms, curr, i); // TODO/FIXME: SUS, what about saving the return value to last_ret?
		else
			ft_ms_execve(ms, curr);
	}
	else if (curr->cmd.builtin && ms->be->nb_cmds == 1)
	{
		if (ms->be->redir_err == 0)
		{
			ms->be->last_ret = ft_builtin(ms, curr, i);
			dup2(ms->be->saved_std[0], STDIN_FILENO);
			dup2(ms->be->saved_std[1], STDOUT_FILENO);
		}
		close(ms->be->saved_std[0]);
		close(ms->be->saved_std[1]);
	}
}

void	handle_sigint_exec(int sig)
{
	(void)sig;
}

void	ft_fork(t_ms *ms, t_cmd_list *curr, int *i)
{
	struct sigaction	sa_int_exec;

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
	sa_int_exec.sa_handler = &handle_sigint_exec;
	sa_int_exec.sa_flags = SA_RESTART;
	sigemptyset(&sa_int_exec.sa_mask);
	sigaction(SIGINT, &sa_int_exec, NULL);
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
