/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expanding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:15:49 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:15:49 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_exit_status(t_data *data, t_var *var)
{
	char	*status;

	status = ft_itoa(data->status);
	var->new = join(var->new, status);
	var->start = var->pos + 2;
	var->pos = var->start - 1;
}

void	add_shell_pid(t_data *data, t_var *var)
{
	char	*pid;

	pid = ft_itoa(data->pid);
	var->new = join(var->new, pid);
	var->start = var->pos + 2;
	var->pos = var->start - 1;
}

void	get_env_name(t_data *data, t_var *var, char *str, char **name)
{
	var->pos ++;
	var->start = var->pos;
	while (ft_isalnum(str[var->pos]) || str[var->pos] == '_')
		var->pos ++;
	var->end = var->pos - 1;
	if (var->end >= var->start)
	{
		*name = malloc(var->end - var->start + 2);
		if (!(*name))
			exit_on_error(data, MEM, 1, 1);
		ft_strlcpy(*name, str + var->start, var->end - var->start + 2);
	}
	var->start = var->end + 1;
	var->pos = var->start - 1;
}

void	switch_env(t_data *data, t_var *var, char *str)
{
	t_env	*env;
	char	*name;

	name = NULL;
	get_env_name(data, var, str, &name);
	env = get_env(data->first_env, name);
	free(name);
	if (env)
		var->new = join(var->new, ft_strdup(env->value));
}

void	env_expanding(t_data *data, t_var *var, char *str)
{
	if (str[var->pos + 1] == '\0'
		|| is_whitespace(str[var->pos + 1]) == 1 || var->sq)
	{
		var->end = var->pos;
		add_normal(data, str, var);
		return ;
	}
	else
	{
		var->end = var->pos -1;
		add_normal(data, str, var);
	}
	if (str[var->pos + 1] == '$')
		add_shell_pid(data, var);
	else if (str[var->pos + 1] == '?')
		add_exit_status(data, var);
	else
		switch_env(data, var, str);
	var->env = 1;
}
