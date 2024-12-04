/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 15:38:18 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/// @brief Lookup a key in the symbol table
/// and return the corresponding key string.
///		Functionality:
///		1. Calculate the hash value of the key.
///		2. Check if the position in the symbol table is empty;
///		if so, return NULL.
///		3. Traverse the linked list in the symbol table at the computed hash
///		and match the key.
/// @param stab_lvl Pointer to the symbol table structure.
/// @param key The key string to be looked up.
/// @return The key string if found; NULL otherwise.
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

/// @brief Lookup a key in the symbol table and return the
/// corresponding value string.
///        Functionality:
///        1. Calculate the hash value of the key.
///        2. Check if the position in the symbol table is empty;
///        if so, return NULL.
///        3. Traverse the linked list in the symbol table at the computed hash
///        and match the key.
/// @param stab_lvl Pointer to the symbol table structure.
/// @param key The key string to be looked up.
/// @return The value string if found; NULL otherwise.
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

/// @brief Create an environment variable array (**envp)
///        from the current global symbol table.
///        Functionality:
///        1. Traverse the global symbol table and count the number of variables
///        2. Allocate memory for a new **envp of size equal to the
///        number of variables + 1.
///        3. Traverse the symbol table again and add each variable
///        in the format `key=value` to **envp.
///        4. Return the **envp.
/// @param ms Pointer to the main structure containing the global symbol table.
/// @return A newly allocated **envp array with the current variable state.

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

/// @brief Free three dynamically allocated memory blocks.
/// @param tofree1 Pointer to the first memory block to be freed.
/// @param tofree2 Pointer to the second memory block to be freed.
/// @param tofree3 Pointer to the third memory block to be freed.
/// @return Void.
void	ft_free_3(void *tofree1, void *tofree2, void *tofree3)
{
	free(tofree1);
	free(tofree2);
	free(tofree3);
}

/// @brief Remove a key-value pair from the symbol table.
///        Functionality:
///        1. Calculate the hash value of the key.
///        2. If the position in the symbol table is empty, return 1.
///        3. Traverse the linked list at the computed hash
///        and find the key to remove.
///        4. Adjust the linked list to bypass the removed entry.
///        5. Free the memory for the key, value, and entry.
///        6. Decrement the used count in the symbol table.
///        7. Return 0 on successful removal; 1 if the key was not found.
/// @param stab_lvl Pointer to the symbol table structure.
/// @param key The key string to be removed.
/// @return 0 on successful removal; 1 if the key was not found.
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
			ft_free_3((void *)tmp->key, (void *) tmp->val, (void *) tmp);
			stab_lvl->used--;
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}
