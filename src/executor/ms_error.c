/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:52:06 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/14 19:14:58 by maweiss          ###   ########.fr       */
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
			ft_printf_err("Exit code of the childs: child nr. %d exitcode %d\n",i , WEXITSTATUS(ms->be->child_ret[i]));
			ms->be->child_ret[i] = WEXITSTATUS(ms->be->child_ret[i]);
			if (ms->be->child_ret[i] == 127)
				ft_printf_err("%s: command not found\n", curr->cmd->words->word); // other errors are handled in child.
			// if (i == ms->be->nb_cmds - 1)
				// err = ms->be->child_ret[i];
		}
		curr = curr->next;
		i++;
	}
}
