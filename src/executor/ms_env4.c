/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/06 11:46:05 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/// @brief Update a value in the symbol table.
///        Functionality:
///        1. Calculate the hash value of the key.
///        2. If the position in the symbol table is empty, return 1.
///        3. If the position in the symbol table is not empty,
///           traverse the linked list and update the value if the key matches.
///        4. Return 0 if the value was successfully updated, 1 otherwise.
/// @param stab_lvl Pointer to the symbol table structure.
/// @param key The key string whose value needs to be updated.
/// @param val The new value string to assoc. with the key. If NULL, no update.
/// @return 0 if the value was successfully updated, 1 if the key was not found.
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

/// @brief Free the entire symbol table stack.
///        Functionality:
///        1. Traverse the symbol table stack and free all entries.
///        2. Free the symbol table stack array and the stack structure itself.
/// @param stab_stack Pointer to the symbol table stack to be freed.
/// @return Void. The symbol table stack and its contents are deallocated.
void	ft_free_stab(t_stab_st *stab_stack)
{
	t_stab			*tmp2;
	t_stab			*tmp3;
	int				i;

	i = 0;
	while (i < stab_stack->size)
	{
		tmp2 = stab_stack->stab[i];
		while (tmp2)
		{
			tmp3 = tmp2;
			if (tmp2 && tmp2->key != NULL)
				free(tmp2->key);
			if (tmp2 && tmp2->val != NULL)
				free(tmp2->val);
			tmp2 = tmp2->next;
			free(tmp3);
			tmp3 = NULL;
		}
		i++;
	}
	free(stab_stack->stab);
	free(stab_stack);
}

/// @brief Update the $SHLVL variable by incrementing its value.
///        Functionality:
///        1. Retrieve the current value of the $SHLVL variable.
///        2. If $SHLVL is missing, initialize it to 1 and add it to the env.
///        3. If $SHLVL exists, increment its value. If negative, reset it to 1.
///        4. Update the $SHLVL variable in the global environment.
///        5. Handle errors, including memory allocation failures.
/// @param ms Pointer to the main structure containing global states.
void	ft_upd_shlvl(t_ms *ms)
{
	char	*shlvl;
	int		curr_shlvl;

	shlvl = ft_lookup_stab(ms->be->global_stabs, "SHLVL");
	if (!shlvl)
	{
		ft_printf_fd(2, "minishell: variable $SHLVL not found. Set to 1\n");
		ft_add_global_val(ms, "SHLVL=1");
	}
	else
	{
		curr_shlvl = ft_atoi(shlvl);
		if (curr_shlvl < 0)
			curr_shlvl = 1;
		else
			curr_shlvl += 1;
		shlvl = ft_itoa(curr_shlvl);
		if (!shlvl)
			ft_cleanup_exit(ms, ENOMEM);
		ft_upd_stab_val(ms->be->global_stabs, "SHLVL", shlvl);
		free(shlvl);
	}
}
