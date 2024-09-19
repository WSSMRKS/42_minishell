/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:52:06 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/19 12:18:42 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_wait_error(t_ms *ms)
{
	int	i;
	int	err;
	t_cmd_list *curr;

	curr = ms->cmds;
	i = 0;
	err = 0;
	while (i < ms->be->nb_cmds)
	{
		ms->be->child_ret[i] = 0;
		waitpid(ms->be->child_pids[i], &(ms->be->child_ret[i]), 0);
		if (WIFEXITED(ms->be->child_ret[i]))
		{
			ft_printf_err("Exit code of the childs: child nr. %d exitcode %d\n",i , WEXITSTATUS(ms->be->child_ret[i]));
			ms->be->child_ret[i] = WEXITSTATUS(ms->be->child_ret[i]);
			if (ms->be->child_ret[i] == 127)
				ft_printf_err("%s: command not found\n", curr->cmd->words->word);
			// else if (ms->be->child_ret[i] == 2)
			// 	ft_printf_err("%s: No such file or directory\n", curr->cmd->redir->from->filename);	// [ ] adjust to target and unify
			// else if (ms->be->child_ret[i] == 13)
			// 	ft_printf_err("%s: Permission denied\n", curr->cmd->redir->to->filename);
			if (ms->be->child_ret[i] != 0 && ms->be->child_ret[i] != 127 && ms->be->child_ret[i] != 2 && ms->be->child_ret[i] != 13)
				ft_printf_err("%s: %s\n", curr->cmd->words->word, strerror(ms->be->child_ret[i]));
			// else
			// 	ft_errno_1_2_13(ms->be->child_ret[i], curr->cmd);
			if (i == ms->be->nb_cmds - 1)
				err = ms->be->child_ret[i];
		}
		curr = curr->next;
		i++;
	}
}
