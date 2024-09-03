/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/03 12:20:49 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_redir_handler(t_ms *ms, t_cmd_list *curr)
{
	t_list_redir	*rd;

	rd = curr->cmd->redir;
	while (rd)
	{
		if (curr->cmd->prio_in == 3 && rd->instruction == redir_here_doc
			&& rd->rightmost == true)
			ft_infile();
		else if (curr->cmd->prio_in == 2
			&& rd->instruction == redir_infile && rd->rightmost == true)
			ft_infile();
		else if (curr->cmd->prio_in == 1
			&& rd->instruction == redir_inpipe)
			ft_inpipe();
		if (curr->cmd->prio_out == 3 && rd->instruction == redir_append
			&& rd->rightmost == true)
			ft_outfile();
		else if (curr->cmd->prio_out == 2
			&& rd->instruction == redir_outfile && rd->rightmost == true)
			ft_outfile();
		else if (curr->cmd->prio_out == 1
			&& rd->instruction == redir_outpipe)
			ft_outpipe();
		rd = rd->next;
	}
}

void	ft_ex_prio(t_ms *ms, t_cmd_list *curr)
{
	t_list_redir	*rd;

	rd = curr->cmd->redir;
	while (rd)
	{
		if (rd->instruction == redir_infile
			&& rd->rightmost == true)
			curr->cmd->prio_in = 2;
		else if (rd->instruction == redir_here_doc
			&& rd->rightmost == true)
			curr->cmd->prio_in = 3;
		else if (rd->instruction == redir_inpipe
			&& (curr->cmd->prio_in != 3 || curr->cmd->prio_in != 2))
			curr->cmd->prio_in = 1;
		if (rd->instruction == redir_outfile
			&& rd->rightmost == true)
			curr->cmd->prio_out = 2;
		else if (rd->instruction == redir_append
			&& rd->rightmost == true)
			curr->cmd->prio_out = 3;
		else if (rd->instruction == redir_outpipe
			&& (curr->cmd->prio_out != 3 || curr->cmd->prio_out != 2))
			curr->cmd->prio_out = 1;
		rd = rd->next;
	}
}

void	ft_executor(t_ms *ms)
{
	t_cmd_list		*curr;

	curr = ms->cmds;
	while (curr)
	{
		if (curr->cmd->redir)
		{
			ft_ex_prio(ms, curr);
			ft_redir_handler(ms, curr);
		}
		ft_fork_execute();
		curr = curr->next;
	}
}



void	ft_scan_cmds(t_ms *ms)
{
	if (ms->global_flags == 1)
		ft_here_doc(ms);
	ft_executor(ms);
}
