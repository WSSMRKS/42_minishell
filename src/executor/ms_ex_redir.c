/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/09 12:53:56 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_infile(t_ms *ms, char *filename)
{
	int		fdin;

	fdin = open(filename, O_RDONLY);
	if (fdin < 0)
		ft_cleanup_exit(ms, errno);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void	ft_inpipe(t_ms *ms, int i)
{
	dup2(ms->be->pipes[i & 1][0], STDOUT_FILENO);
}

void	ft_outfile(t_ms *ms, char *filename, int mode)
{
	int		fdout;

	if (mode == O_APPEND)
		fdout = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fdout = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fdout < 0)
		ft_cleanup_exit(ms, errno);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

void	ft_outpipe(t_ms *ms, int i)
{
	dup2(ms->be->pipes[i & 1][1], STDOUT_FILENO);
}

void	ft_redir_handler(t_ms *ms, t_cmd_list *curr, int i)
{
	t_list_redir	*rd;

	rd = curr->cmd->redir;
	while (rd)
	{
		if (curr->cmd->prio_in == 3 && rd->instruction == redir_here_doc
			&& rd->rightmost == true)
			ft_infile(ms, rd->hd_file->filename->word);
		else if (curr->cmd->prio_in == 2
			&& rd->instruction == redir_infile && rd->rightmost == true)
			ft_infile(ms, rd->from->filename->word);
		else if (curr->cmd->prio_in == 1
			&& rd->instruction == redir_inpipe)
			ft_inpipe(ms, i);
		if (curr->cmd->prio_out == 3 && rd->instruction == redir_append
			&& rd->rightmost == true)
			ft_outfile(ms, rd->to->filename->word, O_APPEND);
		else if (curr->cmd->prio_out == 2
			&& rd->instruction == redir_outfile && rd->rightmost == true)
			ft_outfile(ms, rd->to->filename->word, O_WRONLY);
		else if (curr->cmd->prio_out == 1
			&& rd->instruction == redir_outpipe)
			ft_outpipe(ms, i);
		rd = rd->next;
	}
}

void	ft_ex_prio(t_cmd_list *curr)
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
			&& (curr->cmd->prio_in != 3 && curr->cmd->prio_in != 2))
			curr->cmd->prio_in = 1;
		if (rd->instruction == redir_outfile
			&& rd->rightmost == true)
			curr->cmd->prio_out = 2;
		else if (rd->instruction == redir_append
			&& rd->rightmost == true)
			curr->cmd->prio_out = 3;
		else if (rd->instruction == redir_outpipe
			&& (curr->cmd->prio_out != 3 && curr->cmd->prio_out != 2))
			curr->cmd->prio_out = 1;
		rd = rd->next;
	}
}
