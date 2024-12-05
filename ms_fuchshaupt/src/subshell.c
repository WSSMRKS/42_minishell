/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:28:33 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:28:33 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_subshell(t_data *data)
{
	int			i;
	t_cmd_list	*tmp;

	i = 0;
	tmp = data->first_cmd;
	if (!tmp)
		return (0);
	if (data->command_count <= 1 && parent(data, tmp->name_token->str) == 1)
	{
		delegate(data, tmp);
		return (0);
	}
	while (i < data->command_count)
	{
		tmp->pid = fork();
		if (tmp->pid == 0)
			subshell(data, i);
		else if (tmp->pid < 0)
			exit_on_error(data, "Fork returned negative value", 0, 1);
		i++;
		tmp = tmp->next;
	}
	close_all_fds(data->first_cmd);
	wait_for_children(data);
	return (0);
}

int	delegate(t_data *data, t_cmd_list *cmd)
{
	if (ft_strncmp(cmd->name, "cd", 2) == 0)
		data->status = handle_cd(data, cmd);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		data->status = handle_pwd(data, cmd);
	else if (ft_strncmp(cmd->name, "exit", 4) == 0)
		data->status = handle_exit(data, cmd);
	else if (ft_strncmp(cmd->name, "echo", 4) == 0)
		handle_echo(cmd);
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		handle_env(data, cmd);
	else if (ft_strncmp(cmd->name, "export", 6) == 0)
		data->status = handle_export(data, cmd);
	else if (ft_strncmp(cmd->name, "unset", 5) == 0)
		data->status = handle_unset(data, cmd);
	else if (!cmd->name || !ft_strncmp(cmd->name, "", ft_strlen(cmd->name)))
		data->status = exit_on_error(data, CNF, data->parent + 1, 127);
	else
		exec(data, cmd);
	return (0);
}

int	subshell(t_data *data, int index)
{
	t_cmd_list	*cmd;

	cmd = data->first_cmd;
	while (cmd->index != index)
		cmd = cmd->next;
	if (cmd->eof == 1)
		exit_on_error(data, "Heredoc: End of line", data->parent + 1, 0);
	else if (cmd->error != NULL)
		exit_on_error(data, cmd->error, data->parent + 1, 1);
	else
		delegate(data, cmd);
	if (cmd->pid == 0)
	{
		cleanup(data);
		exit(0);
	}
	return (0);
}
