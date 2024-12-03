/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/27 15:07:42 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
