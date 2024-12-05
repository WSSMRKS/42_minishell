/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:28:39 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:28:39 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	redirect(t_data *data, t_cmd_list *tmp)
{
	int	error;

	error = 0;
	if (tmp->input_operator
		&& ft_strncmp(tmp->input_operator->str, "<", 1) == 0)
		error = redirect_input(data, tmp);
	else if (tmp->input_operator
		&& ft_strncmp(tmp->input_operator->str, "<<", 2) == 0)
		heredoc(data, tmp);
	if (error == 1)
		return (1);
	if (tmp->output_operator
		&& ft_strncmp(tmp->output_operator->str, ">", 1) == 0)
		error = redirect_output(data, tmp);
	else if (tmp->output_operator
		&& ft_strncmp(tmp->output_operator->str, ">>", 2) == 0)
		error = redirect_append(data, tmp);
	if (error == 1)
		return (1);
	else 
		return (0);
}

int	redirect_input(t_data *data, t_cmd_list *cmd)
{
	if (cmd->input_argument == NULL)
		return (exit_on_error(data, "expected argument after '<'",
				0, 1));
	if (cmd->fd_in > 2)
		cmd->fd_in = close_fd(&(cmd->fd_in));
	if (cmd->input_argument->str)
		cmd->fd_in = open(cmd->input_argument->str, O_RDONLY, 0666);
	if (cmd->fd_in == -1)
	{
		cmd->error = NSF;
		return (0);
	}
	return (0);
}

int	heredoc(t_data *data, t_cmd_list *cmd)
{
	if (cmd->input_argument == NULL)
		return (exit_on_error(data, "expected argument after '<<'",
				0, 1));
	if (pipe(cmd->heredoc_pipe) == -1)
		return (exit_on_error(data, "Heredoc piping failed", 0, 1));
	if (cmd->prev != NULL)
		cmd->prev->pipe_read_end_used = 0;
	heredoc_loop(data, cmd);
	cmd->heredoc_pipe[1] = close_fd(&(cmd->heredoc_pipe[1]));
	if (cmd->fd_in > 2)
		cmd->fd_in = close_fd(&(cmd->fd_in));
	cmd->fd_in = cmd->heredoc_pipe[0];
	return (0);
}

int	redirect_output(t_data *data, t_cmd_list *cmd)
{
	if (cmd->output_argument == NULL)
		return (exit_on_error(data, "expected argument after '>'",
				0, 1));
	if (cmd->fd_out > 2)
		cmd->fd_out = close_fd(&(cmd->fd_out));
	if (cmd->output_argument->str)
		cmd->fd_out = open(cmd->output_argument->str,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (cmd->fd_out == -1)
	{
		cmd->error = NSF;
		return (1);
	}
	return (0);
}

int	redirect_append(t_data *data, t_cmd_list *cmd)
{
	if (cmd->output_argument == NULL)
		return (exit_on_error(data, "expected argument after '>>'",
				0, 1));
	if (cmd->fd_out > 2)
		cmd->fd_out = close_fd(&(cmd->fd_out));
	if (cmd->output_argument->str)
		cmd->fd_out = open(cmd->output_argument->str,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (cmd->fd_out == -1)
	{
		cmd->error = NSF;
		return (1);
	}
	return (0);
}
