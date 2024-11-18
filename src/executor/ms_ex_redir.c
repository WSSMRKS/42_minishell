/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/18 11:28:27 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_infile(t_ms *ms, char *filename)
{
	int		fdin;

	fdin = open(filename, O_RDONLY);
	if (fdin < 0)
	{
		ft_printf_fd(2, "%s: %s\n", filename, strerror(errno));
		ft_clear_ast(ms); // [ ] take care of this in case of not a child!!
		ft_clear_be(ms); // [ ] take care of this in case of not a child!!
		ft_cleanup_exit(ms, errno);
	}
	// if (ms->cmds->cmd->flags & IS_BUILTIN == IS_BUILTIN)
	// 		ms->be->saved_std[0] = dup(STDIN_FILENO);
	// 	ms->be->saved_std[1] = dup(STDOUT_FILENO);
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void	ft_inpipe(t_ms *ms, int i)
{
	dup2(ms->be->pipes[(i-1) & 1][0], STDIN_FILENO);
}

void	ft_outfile(t_ms *ms, char *filename, int mode)
{
	int		fdout;

	if (mode == O_APPEND)
		fdout = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fdout = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fdout < 0)
	{
		ft_printf_fd(2, "%s: %s\n", filename, strerror(errno));
		ft_clear_ast(ms); // [ ] take care of this in case of not a child!!
		ft_clear_be(ms); // [ ] take care of this in case of not a child!!
		ft_cleanup_exit(ms, errno);
	}
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

	if (i > 0)
		ft_inpipe(ms, i);
	if (curr->next != NULL)
		ft_outpipe(ms, i);
	rd = curr->cmd->redir;
	if (rd)
		
	while (rd)
	{
		if (curr->cmd->prio_in == 3 && rd->instruction == redir_here_doc
			&& rd->rightmost == true)
			ft_infile(ms, rd->target->filename);
		else if (curr->cmd->prio_in == 2
			&& rd->instruction == redir_infile && rd->rightmost == true)
			ft_infile(ms, rd->target->filename);
		if (curr->cmd->prio_out == 3 && rd->instruction == redir_append
			&& rd->rightmost == true)
			ft_outfile(ms, rd->target->filename, O_APPEND);
		else if (curr->cmd->prio_out == 2
			&& rd->instruction == redir_outfile && rd->rightmost == true)
			ft_outfile(ms, rd->target->filename, O_WRONLY);
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
		// else if (rd->instruction == redir_inpipe
		// 	&& (curr->cmd->prio_in != 3 && curr->cmd->prio_in != 2))
		// 	curr->cmd->prio_in = 1;
		if (rd->instruction == redir_outfile
			&& rd->rightmost == true)
			curr->cmd->prio_out = 2;
		else if (rd->instruction == redir_append
			&& rd->rightmost == true)
			curr->cmd->prio_out = 3;
		// else if (rd->instruction == redir_outpipe
		// 	&& (curr->cmd->prio_out != 3 && curr->cmd->prio_out != 2))
		// 	curr->cmd->prio_out = 1;
		rd = rd->next;
	}
}
