/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:24:48 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:24:48 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_pwd(t_data *data, t_cmd_list *cmd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(cmd->fd_out, &cwd, ft_strlen(cwd));
		write(cmd->fd_out, "\n", 1);
	}
	else
		return (exit_on_error(data, "pwd: error retrieving current directory",
				data->parent +1, 1));
	return (0);
}

int	handle_echo(t_cmd_list *cmd)
{
	int		newline;
	t_token	*arg;

	newline = 1;
	arg = cmd->first_token;
	if (arg)
	{
		while (ft_strncmp(arg->str, "-n", 2) == 0)
		{
			newline = 0;
			arg = arg->next;
			if (arg == NULL)
				return (0);
		}
		while (arg != NULL)
		{
			write(cmd->fd_out, arg->str, ft_strlen(arg->str));
			if (arg->next != NULL)
				write(cmd->fd_out, " ", 1);
			arg = arg->next;
		}
	}
	if (newline)
		write(cmd->fd_out, "\n", 1);
	return (0);
}

int	handle_cd(t_data *data, t_cmd_list *cmd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (exit_on_error(data, "-minishell: cd: error on saving the cwd",
				data->parent +1, 1));
	if (delegate_cd(data, cmd, cwd) == 1)
		return (1);
	update_pwd_envs(get_env(data->first_env, "OLDPWD"), cwd);
	getcwd(cwd, sizeof(cwd));
	update_pwd_envs(get_env(data->first_env, "PWD"), cwd);
	return (0);
}
