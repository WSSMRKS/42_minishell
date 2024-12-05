/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:28:44 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:28:44 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*env_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			last = env_lstlast(*lst);
			last->next = new;
			new->prev = last;
		}
	}
}

void	del_variable(t_data *data, t_env *node)
{
	if (node->prev == NULL)
		data->first_env = node->next;
	else
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node)
	{
		if (node->name)
			free(node->name);
		if (node->value)
			free(node->value);
		free(node);
	}
}

t_env	*env_new(t_data *data, char *envp)
{
	t_env	*new;
	int		pos;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		exit_on_error(data, MEM, 1, 1);
	new->prev = NULL;
	new->next = NULL;
	new->name = NULL;
	new->value = NULL;
	new->equal[0] = '\0';
	new->equal[1] = '\0';
	pos = get_name(data, new, envp);
	get_value(data, new, envp, pos);
	return (new);
}

void	env_init(t_data *data, char **env)
{
	int		pos;
	char	*shlvl;
	t_env	*tmp;

	pos = 0;
	data->first_env = NULL;
	while (env[pos])
	{
		tmp = env_new(data, env[pos]);
		if (tmp == NULL)
			exit_on_error(data, MEM, 1, 1);
		env_lstadd_back(&(data->first_env), tmp);
		pos ++;
	}
	tmp = get_env(data->first_env, "SHLVL");
	if (!tmp)
		return ;
	pos = ft_atoi(tmp->value);
	pos ++;
	shlvl = ft_itoa(pos);
	update_pwd_envs(tmp, shlvl);
	free(shlvl);
}
