/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/11 16:25:31 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

int	ft_builtin(t_ms *ms, t_cmd_list *curr, int *i)
{
	int		ret;

	ret = 0;
	if (curr->cmd.builtin_nr == 1)
		ret = ft_echo(ms, curr);
	else if (curr->cmd.builtin_nr == 2)
		ret = ft_cd(ms, curr);
	else if (curr->cmd.builtin_nr == 3)
		ret = ft_pwd(ms, curr);
	else if (curr->cmd.builtin_nr == 4)
		ret = ft_export(ms, curr);
	else if (curr->cmd.builtin_nr == 5)
		ret = ft_unset(ms, curr);
	else if (curr->cmd.builtin_nr == 6)
		ret = ft_env(ms, curr);
	else if (curr->cmd.builtin_nr == 7)
		ret = ft_exit(ms, curr);
	if (ms->be->child_pids[*i] == 0)
	{
		ft_clear_ast(ms);
		ft_clear_be(ms);
		ft_cleanup_exit(ms, ret);
	}
	return (ret);
}

void	ft_back_end(t_ms *ms)
{
	ft_reinit_be(ms);
	if (ms->global_flags == 1)
		ft_here_doc(ms);
	if (ms->cmds)
	{
		ft_execution(ms);
		ft_close_all_fds(ms);
		if (!ms->cmds->cmd.builtin || ms->be->nb_cmds > 1)
			ft_wait_error(ms);
		ft_clear_ast(ms);
	}
	ft_clear_be(ms);
}
