/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:52:06 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/13 16:26:01 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* Function to handle the different exitstatus of ms for err 127*/
// void	ft_errno_127(t_ms *ms, int i, int *err)
// {
// 	if (WEXITSTATUS(ms->be->child_ret[i]) == 127)
// 	{
// 		ft_printf_err("%s: command not found\n", ms->cmds->cmd->words->word);
// 		if (i != 0)
// 			*err = 1;
// 		if (i == ms->be->nb_cmds - 1)
// 			*err = 127;
// 	}
// }

/* Function to handle the different exitstatus of ms for err 1, 2, 13*/
// void	ft_errno_1_2_13(t_ms *ms, int i, int *err)
// {
// 	char	*filename;

// 	if (WEXITSTATUS(ms->be->child_ret[i]) == 13
// 		|| WEXITSTATUS(ms->be->child_ret[i]) == 2)
// 	{
// 		if (i == 0)
// 			filename = ms->infile;
// 		else if (i == 0 && ms->mode == here_doc)
// 			filename = TEMP_FILE;
// 		else
// 		{
// 			filename = ms->outfile;
// 			*err = 1;
// 		}
// 		ft_printf_err("ms: %s: %s\n", filename,
// 			strerror(WEXITSTATUS(ms->be->child_ret[i])));
// 	}
// 	else if (WEXITSTATUS(ms->be->child_ret[i]) == 1 && i == 0)
// 		*err = 0;
// 	else if (WEXITSTATUS(ms->be->child_ret[i]) == 1 && i != 0)
// 		*err = 1;
// }

void	ft_wait_error(t_ms *ms)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < ms->be->nb_cmds)
	{
		ms->be->child_ret[i] = 0;
		waitpid(ms->be->child_pids[i], &(ms->be->child_ret[i]), 0);
		if (WIFEXITED(ms->be->child_ret[i]))
		{
			printf("Exit code of the childs: child nr. %d exitcode %d\n",i , ms->be->child_ret[i]);
			// ft_errno_127(ms, i, &err);
			// ft_errno_1_2_13(ms, i, &err);
		}
		i++;
	}
}
