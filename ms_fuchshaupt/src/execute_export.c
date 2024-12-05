/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:01 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:01 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*check_existence(t_env *envp, char *set)
{
	if (set == NULL)
		return (NULL);
	while (envp)
	{
		if (ft_strnstr(set, envp->name, ft_strlen(envp->name)) != 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

void	change_value(t_env *env, char *str)
{
	int		pos;
	char	*new_value;

	pos = 0;
	while (str[pos] && str[pos] != '=')
		pos++;
	if (str[pos] != '=')
		return ;
	env->equal[0] = '=';
	if (str[pos + 1] == '\0')
		return ;
	new_value = ft_strdup(str + pos + 1);
	if (new_value == NULL)
		return ;
	free(env->value);
	env->value = new_value;
}

void	print_export(t_data *data, t_env *tmp, t_cmd_list *cmd)
{
	if (data == NULL || cmd == NULL)
		return ;
	while (tmp != NULL)
	{
		write(cmd->fd_out, "declare -x ", 11);
		write(cmd->fd_out, tmp->name, ft_strlen(tmp->name));
		if (tmp->equal[0] != '\0')
		{
			write(cmd->fd_out, tmp->equal, ft_strlen(tmp->equal));
			write(cmd->fd_out, "\"", 1);
			write(cmd->fd_out, tmp->value, ft_strlen(tmp->value));
			write(cmd->fd_out, "\"", 1);
		}
		write(cmd->fd_out, "\n", 1);
		tmp = tmp->next;
	}
	return ;
}

int	valid_identifier(char *str)
{
	int	pos;

	pos = 0;
	if (!str)
		return (0);
	if (ft_isalpha(str[0]) == 0)
		return (0);
	while (str[pos])
	{
		if (str[pos] == '=')
			break ;
		if (ft_isalpha(str[pos]) == 0)
			return (0);
		pos ++;
	}
	return (1);
}

int	handle_export(t_data *data, t_cmd_list *cmd)
{
	t_env	*tmp;
	t_token	*arg;

	tmp = cmd->first_env;
	if (cmd->first_token == NULL)
	{
		print_export(data, tmp, cmd);
		return (0);
	}
	arg = cmd->first_token;
	while (arg)
	{
		if (valid_identifier(arg->str) == 0)
			return (exit_on_error(data, "bad identifier", data->parent +1, 1));
		tmp = check_existence(cmd->first_env, arg->str);
		if (tmp == NULL)
		{
			tmp = env_new(data, arg->str);
			env_lstadd_back(&(cmd->first_env), tmp);
		}
		else
			change_value(tmp, arg->str);
		arg = arg->next;
	}
	return (0);
}
