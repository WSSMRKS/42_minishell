/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:09 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:09 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec(t_data *data, t_cmd_list *cmd)
{
	t_exe	pass;
	char	**paths;

	data->exe = &pass;
	pass.argv = NULL;
	pass.env = NULL;
	paths = get_paths(data, cmd);
	if (paths != NULL)
		check_access(data, cmd, paths, 0);
	create_pass_env(data, cmd, &pass);
	create_pass_argv(data, cmd, &pass);
	if (cmd->fd_in > 1)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > 1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	small_cleanup(data);
	data->first_env = cleaunup_env(data);
	if (execve(pass.argv[0], pass.argv, pass.env) == -1)
	{
		if (pass.argv)
			pass.argv = free_map(pass.argv);
		if (pass.env)
			pass.env = free_map(pass.env);
		exit_on_error(data, EXF, 1, 127);
	}
}

char	**get_paths(t_data *data, t_cmd_list *cmd)
{
	char	**paths;
	t_env	*path;

	if (cmd->name[0] == '.' || cmd->name[0] == '/')
		return (NULL);
	path = get_env(cmd->first_env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path->value, ':');
	if (!paths)
		exit_on_error(data, CNF, data->parent + 1, 127);
	return (paths);
}

void	check_access(t_data *data, t_cmd_list *cmd, char **paths, int pos)
{
	char	*tmp;
	char	*tmp2;

	while (paths[pos])
	{
		tmp = ft_strjoin(paths[pos], "/");
		if (!tmp)
			exit_on_error(data, SPE, 1, 1);
		tmp2 = ft_strjoin(tmp, cmd->name);
		free(tmp);
		if (!tmp2)
			exit_on_error(data, SPE, 1, 1);
		if (access(tmp2, X_OK) == 0)
		{
			cmd->name = tmp2;
			cmd->flag = 1;
			free_map(paths);
			return ;
		}
		free(tmp2);
		pos ++;
	}
	free_map(paths);
	exit_on_error(data, CNF, data->parent + 1, 127);
}

void	create_pass_env(t_data *data, t_cmd_list *cmd, t_exe *pass)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = cmd->first_env;
	while (tmp)
	{
		i ++;
		tmp = tmp->next;
	}
	pass->env = (char **) malloc ((i + 1) * sizeof(char *));
	if (!pass->env)
		exit_on_error(data, MEM, 1, 1);
	pass->env[i] = NULL;
	tmp = cmd->first_env;
	i = 0;
	while (tmp)
	{
		combine_env(tmp, pass->env, i);
		tmp = tmp->next;
		i ++;
	}
}

void	create_pass_argv(t_data *data, t_cmd_list *cmd, t_exe *pass)
{
	t_token	*tmp;
	int		pos;
	int		len;

	pos = 1;
	len = 2;
	tmp = cmd->first_token;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	pass->argv = (char **)malloc((len) * sizeof(char *));
	if (!pass->argv)
		exit_on_error(data, MEM, 1, 1);
	pass->argv[len - 1] = NULL;
	pass->argv[0] = ft_strdup(cmd->name);
	tmp = cmd->first_token;
	while (pos < len -1 && tmp)
	{
		pass->argv[pos] = ft_strdup(tmp->str);
		tmp = tmp->next;
		pos ++;
	}
}
