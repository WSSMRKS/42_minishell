/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/20 12:24:59 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* Environmental variables implementation steps:
- Create a new struct that holds the environmental variables
- Create a new function that initializes the environmental variables given by the system
- Create a function that initializes the hash table for the environmental variables
- Create a function that initializes the hash table for the local variables
- Create a new function that frees the environmental variables
- Create a new function that prints the environmental variables
- Create a new function that adds a new environmental variable
- Create a new function that deletes/unsets an environmental variable
- Create a new function that searches for an environmental variable
- Create a new function that updates an environmental variable
- Create a new function that exports the environmental variables

Advantage of a hash table over a regular array or linkedlist.

finding a particular value in an array:
traverse through the array and strncmp the value with the string in the array. time complexity O(n)
finding a particular value in a linked list:
traverse through the array and strncmp the value with the string in the array. time complexity O(n)
finding a particular value in a hash table:
get the hash value multiplying the string with the hash function. hash value % table size (should be prime) = position in the array.
time complexity O(1)

*/

unsigned long	ft_hash_function(t_ms *ms, char *key)
{
	int				i;
	unsigned long	hash;

	i = 0;
	hash = 5381;
	while (key[i])
	{
		hash = ((hash << 5) + hash) + key[i]; /* hash * 33 + key[i] */
		i++;
	}
	return (hash % (unsigned long) ms->be->global_symtabs->size);
}

void	ft_resize_load_factor(t_ms *ms)
{

}

void	ft_resize_symtab(t_ms *ms)
{

}

void	ft_add_env(t_ms *ms, char *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	value = ft_strdup(&env[i + 1]);
	ft_add_symtab(ms, key, value);
}

void ft_add_to_symtab(t_ms *ms, char **symtab, char *key, char *value)
{
	unsigned long	hash;
	t_symtab		*new;
	t_symtab		*tmp;


	hash = ft_hash_function(ms, key);
	new = ft_calloc(sizeof(t_symtab), 1);
	new->key = key;
	new->value = value;
	if (symtab[hash] == NULL)
	{
		symtab[hash] = new;
	}
	else
	{
		symtab[hash];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_hash_env(t_ms *ms)
{
	int		i;
	char	**env;

	i = 0;
	env = ms->be->envp;
	while (env[i])
	{
		ft_add_env(ms, env[i]);
		i++;
	}
}


void	ft_init_env(t_ms *ms)
{
	int		i;
	char	**env;

	i = 0;
	env = ms->be->envp;
	while (env[i])
	{
		ft_add_env(ms, env[i]);
		i++;
	}
}
