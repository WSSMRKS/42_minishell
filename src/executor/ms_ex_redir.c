/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wssmrks <wssmrks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/25 15:48:04 by wssmrks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_infile(t_ms *ms, t_list_redir *rd)
{
	int		fdin;

	fdin = open(rd->target.filename, O_RDONLY);
	if (fdin < 0)
	{
		ft_printf_fd(2, "%s: %s\n", rd->target.filename, strerror(errno));
		ft_clear_ast(ms); // [ ] take care of this in case of not a child!!
		ft_clear_be(ms); // [ ] take care of this in case of not a child!!
		ft_cleanup_exit(ms, errno);
	}
	// if (ms->cmds->cmd->flags & IS_BUILTIN == IS_BUILTIN)
	// 		ms->be->saved_std[0] = dup(STDIN_FILENO);
	// 	ms->be->saved_std[1] = dup(STDOUT_FILENO);
	if (rd->rightmost == true)
		dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void	ft_inpipe(t_ms *ms, int i)
{
	dup2(ms->be->pipes[(i-1) & 1][0], STDIN_FILENO);
}

void	ft_outfile(t_ms *ms, t_list_redir *rd, int mode)
{
	int		fdout;

	if (mode == O_APPEND)
		fdout = open(rd->target.filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fdout = open(rd->target.filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fdout < 0)
	{
		ft_printf_fd(2, "%s: %s\n", rd->target.filename, strerror(errno));
		ft_clear_ast(ms); // [ ] take care of this in case of not a child!!
		ft_clear_be(ms); // [ ] take care of this in case of not a child!!
		ft_cleanup_exit(ms, errno);
	}
	if (rd->rightmost == true)
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

	curr->cmd.prio_in = 1;
	if (i > 0)
		ft_inpipe(ms, i);
	if (curr->next != NULL)
		ft_outpipe(ms, i);
	rd = curr->cmd.redir;
	while (rd)
	{
		if (rd->instruction == redir_here_doc && curr->cmd.prio_in == 1)
			ft_infile(ms, rd);
		else if (rd->instruction == redir_infile && curr->cmd.prio_in == 1)
			ft_infile(ms, rd);
		if (rd->instruction == redir_append && curr->cmd.prio_in == 0)
			ft_outfile(ms, rd, O_APPEND);
		else if (rd->instruction == redir_outfile && curr->cmd.prio_in == 0)
			ft_outfile(ms, rd, O_WRONLY);
		rd = rd->next;
		if (!rd && curr->cmd.prio_in == 1)
		{
			curr->cmd.prio_in = 0;
			rd = curr->cmd.redir;
		}
	}
}
