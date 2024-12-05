/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:07 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:07 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cd_home(t_data *data)
{
	t_env	*env;

	env = get_env(data->first_env, "HOME");
	if (env->value == NULL)
		return (exit_on_error(data, HNS, data->parent +1, 1));
	else if (chdir(env->value) != 0)
		return (exit_on_error(data, NSD, data->parent +1, 1));
	return (0);
}

int	cd_prev(t_data *data, t_cmd_list *cmd)
{
	t_env	*env;

	env = get_env(data->first_env, "OLDPWD");
	if (!env)
		return (exit_on_error(data, ONS, 0, 1));
	if (env->value == NULL)
		return (exit_on_error(data, ONS, 0, 1));
	if (chdir(env->value) != 0)
		return (exit_on_error(data, NSD, data->parent +1, 1));
	write(cmd->fd_out, env->value, ft_strlen(env->value));
	write(cmd->fd_out, "\n", 1);
	return (0);
}

int	cd_home_sth(t_data *data, t_cmd_list *cmd)
{
	t_env	*env;
	char	*tmp;

	env = get_env(data->first_env, "HOME");
	if (env->value == NULL)
		return (exit_on_error(data, HNS, data->parent +1, 1));
	tmp = ft_strjoin(env->value, cmd->first_token->str + 1);
	if (chdir(tmp) != 0)
	{
		free(tmp);
		return (exit_on_error(data, NSD, data->parent +1, 1));
	}
	free(tmp);
	return (0);
}

int	cd_step_root(t_data *data, char *cwd)
{
	int		pos;
	char	*back;

	pos = ft_strlen(cwd) - 1;
	back = NULL;
	if (pos < 0)
		return (exit_on_error(data, SRF, data->parent +1, 1));
	while (cwd[pos])
	{
		if (cwd[pos] == '/')
			break ;
		pos --;
		if (pos < 0)
			break ;
	}
	if (pos >= 0)
		back = ft_substr(cwd, 0, pos + 1);
	if (chdir(back) != 0)
		(exit_on_error(data, SRF, data->parent +1, 1));
	if (back)
		free(back);
	return (0);
}

int	delegate_cd(t_data *data, t_cmd_list *cmd, char *cwd)
{
	if (cmd->first_token && cmd->first_token->str == NULL)
		return (0);
	if (cmd->first_token == NULL)
		return (cd_home(data));
	else if (cmd->first_token->next != NULL)
		return (exit_on_error(data, TMA, data->parent +1, 1));
	else if (ft_strncmp(cmd->first_token->str, "-", 1) == 0)
		return (cd_prev(data, cmd));
	else if (ft_strncmp(cmd->first_token->str, "..", 2) == 0)
		return (cd_step_root(data, cwd));
	else if (cmd->first_token->str[0] == '~')
		return (cd_home_sth(data, cmd));
	else if (ft_strncmp(cmd->first_token->str, "--", 2) == 0)
		return (cd_home(data));
	else if (chdir(cmd->first_token->str) != 0)
		return (exit_on_error(data, NSD, data->parent +1, 1));
	return (0);
}
