/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/02 12:50:07 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_scan_cmds(t_ms *ms)
{
	if (ms->global_flags == 1)
		ft_here_doc(ms);
	ft_executor(ms);
}

void	ft_redir_handler(t_ms *ms, t_cmd_list *curr)
{
	t_list_redir	*redirects;

	redirects = curr->cmd->redir;
	while (redirects)
	{
		//handle each redirect at a time;
	}
}

void	ft_executor(t_ms *ms)
{
	t_cmd_list		*curr;

	curr = ms->cmds;
	while (curr)
	{
		if(curr->cmd->redir)
			ft_redir_handler(ms, curr);
	}
}
