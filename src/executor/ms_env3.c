/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/27 14:03:48 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_lookup_key(t_stab_st *stab_lvl, char *key)
{
	unsigned long	hash;
	t_stab			*tmp;

	if (!stab_lvl)
		return (NULL);
	if (key[0] == '$')
		key = &key[1];
	hash = ft_hash_function(stab_lvl, key);
	if (stab_lvl->stab[hash] == NULL)
		return (NULL);
	tmp = stab_lvl->stab[hash];
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

/* function to lookup a val in the symbol table
functionality:
1. Calculate the hash val of the key
2. If the position in the symbol table is empty, return NULL
3. If the position in the symbol table is not empty,
traverse the linked list and return the val
*/
char	*ft_lookup_stab(t_stab_st *stab_lvl, char *key)
{
	unsigned long	hash;
	t_stab			*tmp;

	if (!stab_lvl)
		return (NULL);
	if (key[0] == '$')
		key = &key[1];
	hash = ft_hash_function(stab_lvl, key);
	if (stab_lvl->stab[hash] == NULL)
		return (NULL);
	tmp = stab_lvl->stab[hash];
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

/* function to create **envp out of the current state of the 
environmental variables
functionality:
1. Traverse the global symbol table and count the number of variables
2. Create a new **envp with the size of the number of variables + 1
3. Traverse the global symbol table and add the variables to the **envp
4. Return the **envp
*/
char	**ft_create_envp(t_ms *ms)
{
	int				i;
	int				j;
	char			**envp;
	t_stab_st		*global;
	t_stab			*tmp;

	j = 0;
	envp = ft_calloc(sizeof(char *), ms->be->global_stabs->used + 1);
	global = ms->be->global_stabs;
	while (global)
	{
		i = 0;
		while (i < global->size)
		{
			tmp = global->stab[i++];
			while (tmp)
			{
				if (tmp->val)
					envp[j++] = ft_multistrjoin(3, tmp->key, "=", tmp->val);
				tmp = tmp->next;
			}
		}
		global = global->next;
	}
	return (envp);
}


/* function to alter one particular val when executing a command
functionality:
1. take actual **envp
2. find the stated val
3. If val is there update
4. If val is not there add
*/
char	**ft_update_envp_runtime(char **envp, char *key, char *val)
{
	int		i;
	char	*tmp;
	char	**tmp2;

	i = -1;
	if (!envp)
		return (NULL);
	tmp = ft_multistrjoin(3, key, "=", val);
	if (!tmp)
		return (NULL);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], tmp, ft_strlen(key) + 1))
		{
			free(envp[i]);
			envp[i] = tmp;
			return (envp);
		}
	}
	tmp2 = ft_calloc(sizeof(char *), i + 2);
	i = -1;
	while (envp[++i])
		tmp2[i] = envp[i];
	tmp2[i] = tmp;
	free(envp);
	return (tmp2);
}

/* function that removes a variable from the stab
functionality:
1. Calculate the hash val of the key
2. If the position in the symbol table is empty, return 1
3. If the position in the symbol table is not empty,
traverse the linked list and remove the val
4. Return 0
*/
int	ft_remove_from_stab(t_stab_st *stab_lvl, char *key)
{
	unsigned long	hash;
	t_stab			*tmp;
	t_stab			*prev;
	int				i;

	i = 0;
	hash = ft_hash_function(stab_lvl, key);
	if (stab_lvl->stab[hash] == NULL)
		return (1);
	tmp = stab_lvl->stab[hash];
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			if (prev)
				prev->next = tmp->next;
			else
				stab_lvl->stab[hash] = tmp->next;
			free(tmp->key);
			tmp->key = NULL;
			free(tmp->val);
			tmp->val = NULL;
			free(tmp);
			tmp = NULL;
			stab_lvl->used--;
			return (0);
		}
		prev = tmp;
		i++;
		tmp = tmp->next;
	}
	return (1);
}

/* function that updates a val in the stab
functionality:
1. Calculate the hash val of the key
2. If the position in the symbol table is empty, return 1
3. If the position in the symbol table is not empty,
traverse the linked list and update the val
4. Return 0
*/
int	ft_upd_stab_val(t_stab_st *stab_lvl, char *key, char *val)
{
	unsigned long	hash;
	t_stab			*tmp;

	hash = ft_hash_function(stab_lvl, key);
	if (stab_lvl->stab[hash] == NULL)
		return (1);
	tmp = stab_lvl->stab[hash];
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			if (val)
			{
				free(tmp->val);
				tmp->val = ft_strdup(val);
			}
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

/* function to free the whole stab_stack
functionality:
1. Traverse the symbol table stack and free the symbol table
2. Free the symbol table stack
*/
void	ft_free_stab_stack(t_stab_st *stab_stack)
{
	t_stab_st		*tmp;
	t_stab			*tmp2;
	t_stab			*tmp3;
	int				i;

	while (stab_stack)
	{
		i = 0;
		while (i < stab_stack->size)
		{
			tmp2 = stab_stack->stab[i];
			while (tmp2)
			{
				tmp3 = tmp2;
				if (tmp2 && tmp2->key != NULL)
				{
					free(tmp2->key);
					tmp2->key = NULL;
				}
				if (tmp2 && tmp2->val != NULL)
				{
					free(tmp2->val);
					tmp2->val = NULL;
				}
				tmp2 = tmp2->next;
				free(tmp3);
				tmp3 = NULL;
			}
			i++;
		}
		free(stab_stack->stab);
		tmp = stab_stack;
		stab_stack = stab_stack->next;
		free(tmp);
		tmp = NULL;
	}
}
