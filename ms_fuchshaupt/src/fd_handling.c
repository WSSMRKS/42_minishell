/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:52:08 by sgramsch          #+#    #+#             */
/*   Updated: 2024/11/27 10:52:08 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	setup_pipes(t_cmd_list *cmd)
{
	while (cmd->next != NULL)
	{
		if (pipe(cmd->pipe_fds) == -1)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	close_fd(int *fd)
{
	if (*fd != -1)
		close(*fd);
	return (-1);
}

int	close_all_fds(t_cmd_list *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->pipe_fds[0] > 2)
			cmd->pipe_fds[0] = close_fd(&(cmd->pipe_fds[0]));
		if (cmd->pipe_write_end_used == 0 && cmd->fd_out > 2)
			cmd->fd_out = close_fd(&(cmd->fd_out));
		if (cmd->pipe_fds[1] > 2)
			cmd->pipe_fds[1] = close_fd(&(cmd->pipe_fds[1]));
		if (cmd->index != 0)
		{
			if (cmd->prev->pipe_read_end_used == 0 && cmd->fd_in > 2)
				cmd->fd_in = close_fd(&(cmd->fd_in));
		}
		else if (cmd->index == 0 && cmd->fd_in > 2)
			cmd->fd_in = close_fd(&(cmd->fd_in));
		cmd = cmd->next;
	}
	return (0);
}

void	set_pipe_flags(t_cmd_list *tmp)
{
	while (tmp)
	{
		if (tmp->fd_out == -1 && tmp->next != NULL)
		{
			tmp->fd_out = tmp->pipe_fds[1];
			tmp->pipe_write_end_used = 1;
		}
		else
			tmp->pipe_fds[1] = close_fd(&(tmp->pipe_fds[1]));
		if (tmp->prev != NULL && tmp->fd_in == -1)
		{
			tmp->fd_in = tmp->prev->pipe_fds[0];
			tmp->prev->pipe_read_end_used = 1;
		}
		tmp = tmp->next;
	}
}

void	prepare_fds(t_cmd_list *cmd)
{
	t_cmd_list	*tmp;

	tmp = cmd;
	if (cmd->fd_in == -1)
		cmd->fd_in = 0;
	tmp = cmd_lstlast(cmd);
	if (tmp->fd_out == -1)
		tmp->fd_out = 1;
	set_pipe_flags(cmd);
}
