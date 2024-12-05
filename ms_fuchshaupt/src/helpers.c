/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:16:28 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:16:28 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_blank(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_whitespace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	map_len(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len] != NULL)
		len++;
	return (len);
}

char	*join(char *first, char *second)
{
	char	*tmp;

	tmp = ft_strjoin(first, second);
	free(first);
	free(second);
	return (tmp);
}

int	parent(t_data *data, char *name)
{
	if (ft_strncmp(name, "cd", 2) == 0 || ft_strncmp(name, "pwd", 3) == 0
		|| ft_strncmp(name, "exit", 4) == 0
		|| ft_strncmp(name, "export", 6) == 0 
		|| ft_strncmp(name, "unset", 5) == 0)
	{
		data->parent = 1;
		return (1);
	}
	return (0);
}
