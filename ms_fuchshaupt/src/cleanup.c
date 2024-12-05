/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:16 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:16 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	small_cleanup(t_data *data)
{
	if (g_signal == SIGINT || g_signal == SIGQUIT)
		data->status = 128 + g_signal;
	g_signal = 0;
	data->first_cmd = cleanup_cmd(data);
	if (data->input)
		free(data->input);
	if (data->first_token)
		data->first_token = free_tokens(data->first_token);
	if (data->var)
		free_var(data);
	data->input = NULL;
	data->dont = 0;
	return (0);
}

void	wait_for_children(t_data *data)
{
	t_cmd_list	*tmp;
	int			exit_status;

	tmp = data->first_cmd;
	while (tmp != NULL)
	{
		waitpid(tmp->pid, &exit_status, 0);
		data->status = WEXITSTATUS(exit_status);
		tmp = tmp->next;
	}
}

void	*free_map(char **map)
{
	int	pos;

	pos = map_len(map) -1;
	while (pos >= 0)
	{
		if (map[pos])
			free(map[pos]);
		pos --;
	}
	if (map)
		free(map);
	map = NULL;
	return (NULL);
}

int	cleanup(t_data *data)
{
	if (data)
	{
		data->first_cmd = cleanup_cmd(data);
		data->first_env = cleaunup_env(data);
		if (data->exe)
		{
			if (data->exe->argv != NULL)
				data->exe->argv = free_map(data->exe->argv);
			if (data->exe->env != NULL)
				data->exe->env = free_map(data->exe->env);
		}
		if (data->first_token)
			data->first_token = free_tokens(data->first_token);
		if (data->input)
			free(data->input);
		if (data->var)
			free_var(data);
		data->input = NULL;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(2);
	return (0);
}
