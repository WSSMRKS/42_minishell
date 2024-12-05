/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:15:25 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:15:25 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	var_init(t_data *data)
{
	t_var	*new;

	if (data->var == NULL)
	{
		new = malloc(sizeof(t_var));
		if (!new)
			exit_on_error(data, "Memory allocation failed.", 1, 1);
		data->var = new;
	}
	if (data->var != NULL)
	{
		data->var->start = 0;
		data->var->end = 0;
		data->var->new = NULL;
		data->var->pos = 0;
		data->var->sq = 0;
		data->var->dq = 0;
		data->var->hd = 0;
		data->var->env = 0;
	}
}

void	*free_var(t_data *data)
{
	if (data->var)
	{
		if (data->var->new)
			free(data->var->new);
		free(data->var);
	}
	data->var = NULL;
	return (NULL);
}

void	set_up_data(t_data *data, char **envp, int argc, char **argv)
{
	data->input = NULL;
	data->command_count = 0;
	data->first_cmd = NULL;
	data->tokens = NULL;
	data->envp_original = envp;
	data->first_env = NULL;
	data->parent = 0;
	data->status = 0;
	data->exe = NULL;
	data->pos = 0;
	data->pos3 = 0;
	data->dont = 0;
	data->pid = getpid();
	data->first_token = NULL;
	data->var = NULL;
	var_init(data);
	if (argc > 1 || argv[1] != NULL)
		exit_on_error(data, "Too many arguments!", 1, 1);
	env_init(data, envp);
}
