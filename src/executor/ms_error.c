/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wssmrks <wssmrks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:52:06 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/23 18:00:52 by wssmrks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_wait_error(t_ms *ms)
{
	int	i;
	// int	err;
	t_cmd_list *curr;

	curr = ms->cmds;
	i = 0;
	// err = 0;
	while (i < ms->be->nb_cmds)
	{
		ms->be->child_ret[i] = 0;
		waitpid(ms->be->child_pids[i], &(ms->be->child_ret[i]), 0);
		if (WIFEXITED(ms->be->child_ret[i]))
		{
			ms->be->child_ret[i] = WEXITSTATUS(ms->be->child_ret[i]);
			// DEBUG(ft_printf_fd(2, "Exit code of the childs: child nr. %d exitcode %d\n",i , WEXITSTATUS(ms->be->child_ret[i])));
		}
		curr = curr->next;
		i++;
	}
	ms->be->last_ret = ms->be->child_ret[ms->be->nb_cmds - 1];
}
