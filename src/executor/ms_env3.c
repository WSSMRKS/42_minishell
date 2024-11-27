/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/27 15:02:44 by maweiss          ###   ########.fr       */
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

void	ft_free_3(void *tofree1, void *tofree2, void *tofree3)
{
	free(tofree1);
	free(tofree2);
	free(tofree3);
}

/* function that removes a variable from the stab
functionality:
1. Calculate the hash val of the key
2. If the position in the symbol table is empty, return 1
3. If the position in the symbol table is not empty,
traverse the linked list and remove the val
4. Return 0
*/
int	ft_rem_fr_stab(t_stab_st *stab_lvl, char *key)
{
	unsigned long	hash;
	t_stab			*tmp;
	t_stab			*prev;

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
			ft_free_3((void *)tmp->key,(void *) tmp->val,(void *) tmp);
			stab_lvl->used--;
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}
