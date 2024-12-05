/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:04 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:04 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_pwd_envs(t_env *env, char *str)
{
	if (str && env)
	{
		free(env->value);
		env->value = malloc(ft_strlen(str) + 1);
		ft_memcpy(env->value, str, ft_strlen(str) + 1);
	}
}

int	handle_env(t_data *data, t_cmd_list *cmd)
{
	t_env	*node;

	node = cmd->first_env;
	if (cmd->first_token != NULL)
		exit_on_error(data, TMA, 1, 1);
	while (node)
	{
		if (node->equal[0] != '=')
		{
			node = node->next;
			continue ;
		}
		write(cmd->fd_out, node->name, ft_strlen(node->name));
		write(cmd->fd_out, "=", 1);
		if (node->value != NULL)
			write(cmd->fd_out, node->value, ft_strlen(node->value));
		write(cmd->fd_out, "\n", 1);
		node = node->next;
	}
	return (0);
}

t_env	*get_env(t_env *envp, char *set)
{
	while (envp != NULL)
	{
		if (ft_strncmp(envp->name, set, ft_strlen(set)) == 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

int	handle_unset(t_data *data, t_cmd_list *cmd)
{
	t_env	*tmp;
	t_token	*arg;

	arg = cmd->first_token;
	if (cmd->first_token == NULL)
		return (exit_on_error(data,
				"Unset: missing identifier\n", data->parent +1, 1));
	while (arg != NULL)
	{
		if (ft_strchr(arg->str, '=') != NULL)
			return (0);
		tmp = get_env(cmd->first_env, arg->str);
		if (tmp)
			del_variable(data, tmp);
		arg = arg->next;
	}
	return (0);
}
