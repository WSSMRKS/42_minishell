/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:13:59 by sgramsch          #+#    #+#             */
/*   Updated: 2024/11/27 12:10:03 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	combine_env(t_env *tmp, char **env, int i)
{
	char	*first;

	first = ft_strjoin(tmp->name, "=");
	env[i] = ft_strjoin(first, tmp->value);
	free(first);
}

int	get_name(t_data *data, t_env *new, char *envp)
{
	int	pos;

	pos = 0;
	while (envp[pos])
	{
		if (envp[pos + 1] == '=' || envp[pos + 1] == '\0')
		{
			new->name = (char *)malloc((pos + 2) * sizeof(char));
			if (!new->name)
				exit_on_error(data, MEM, 1, 1);
			ft_strlcpy(new->name, envp, pos + 2);
			pos ++;
			break ;
		}
		pos ++;
	}
	return (pos);
}

int	set_empty_value(t_data *data, t_env *new)
{
	new->value = ft_strdup("");
	if (!new->value)
		exit_on_error(data, MEM, 1, 1);
	return (0);
}

int	get_value(t_data *data, t_env *new, char *envp, int pos)
{
	int	pos2;

	pos2 = 0;
	if (!envp[pos])
		return (set_empty_value(data, new));
	if (envp[pos] == '=')
		new->equal[0] = '=';
	pos ++;
	if (!envp[pos])
		return (set_empty_value(data, new));
	while (envp[pos + pos2])
	{
		if (envp[pos + pos2 + 1] == '\0')
		{
			new->value = (char *)malloc((pos2 + 2) * sizeof(char));
			if (!new->value)
				exit_on_error(data, MEM, 1, 1);
			ft_strlcpy(new->value, envp + pos, pos2 + 3);
			break ;
		}
		pos2 ++;
	}
	return (0);
}
