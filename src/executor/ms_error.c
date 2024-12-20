/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:52:06 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/11 16:25:12 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// void	ft_wait_error(t_ms *ms)
// {
// 	int				i;
// 	t_cmd_list		*curr;

// 	curr = ms->cmds;
// 	i = 0;
// 	while (i < ms->be->nb_cmds)
// 	{
// 		ms->be->child_ret[i] = 0;
// 		waitpid(ms->be->child_pids[i], &(ms->be->child_ret[i]), 0);
// 		if (WIFEXITED(ms->be->child_ret[i]))
// 			ms->be->child_ret[i] = WEXITSTATUS(ms->be->child_ret[i]);
// 		curr = curr->next;
// 		i++;
// 	}
// 	ms->be->last_ret = ms->be->child_ret[ms->be->nb_cmds - 1];
// }

static void	ft_status_error(t_ms *ms, int status, int i)
{
	ms->be->child_ret[i] = 128 + WTERMSIG(status);
	if (ms->be->child_ret[i] == 131)
		printf("Quit (core dumped)\n");
	if (ms->be->child_ret[i] == 130)
		printf("\n");
}

void	ft_wait_error(t_ms *ms)
{
	int		status;
	pid_t	pid;
	int		i;

	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		i = -1;
		while (++i < ms->be->nb_cmds)
		{
			if (ms->be->child_pids[i] == pid)
			{
				if (WIFEXITED(status))
					ms->be->child_ret[i] = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					ft_status_error(ms, status, i);
				break ;
			}
		}
	}
	if (pid == -1 && errno != ECHILD)
		perror("waitpid error");
	ms->be->last_ret = ms->be->child_ret[ms->be->nb_cmds - 1];
}
