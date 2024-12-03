/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_junk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/27 13:24:18 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// /* function to add a new val to the local variables
// functionality:
// 1. Find the position of the equal sign in the string
// 2. Create a new string with the key
// 3. Create a new string with the val
// 4. Check if the load factor is greater than 0.7
// 5. If the load factor is greater than 0.7, resize the symbol table
// 6. Increment the used variable
// 7. Calculate the new load factor
// 8. Add the val to the symbol table
// */
// void	ft_add_local_val(t_ms *ms, char *env)
// {
// 	char		*key;
// 	char		*val;
// 	int			i;
// 	t_stab_st	*local;

// 	i = 0;
// 	while (env[i] && env[i] != '=')
// 		i++;
// 	key = ft_substr(env, 0, i);
// 	val = ft_strdup(&env[i + 1]);
// 	if (ms->be->global_stabs->next == NULL)
// 		ft_add_local_stab(ms);
// 	local = ms->be->global_stabs->next;
// 	if (ft_lookup_stab(local, key) != NULL)
// 	{
// 		ft_upd_stab_val(local, key, val);
// 		free(val);
// 		free(key);
// 	}
// 	else
// 		ft_add_to_stab(ms, local, key, val);
// }

// /* function to add a val to the symbol table
// functionality:
// 1. Find the position of the equal sign in the string
// 2. Create a new string with the key
// 3. Create a new string with the val
// 4. Add the val to the symbol table
// */
// void	ft_add_val(t_ms *ms, char *env)
// {
// 	char	*key;
// 	char	*val;
// 	int		i;

// 	i = 0;
// 	while (env[i] && env[i] != '=')
// 		i++;
// 	key = ft_substr(env, 0, i);
// 	val = ft_strdup(&env[i + 1]);
// 	ft_add_to_stab(ms, ms->be->global_stabs, key, val);
// }

/* function to add the local stab
functionality:
1. Add the local symbol table to the global symbol table
*/
// void	ft_add_local_stab(t_ms *ms)
// {
// 	t_stab_st	*local;

// 	local = ft_calloc(sizeof(t_stab_st), 1);
// 	ms->be->global_stabs->next = local;
// 	local->stab = ft_calloc(sizeof(char *), ms->be->global_stabs->size);
// 	local->size = ft_calc_stab_size(5);
// 	local->used = 0;
// 	local->load_factor = 0;
// 	local->level = ms->be->global_stabs->level + 1;
// }

/* function that makes a local variable global
functionality:
1. search the variable in the local stab
2. if variable is found remove the val and add it to the global stab.
3. if the variable is not found return -1
*/
// int	ft_make_global(t_ms *ms, char *key)
// {
// 	char			*val;
// 	t_stab_st		*local;
// 	t_stab_st		*global;

// 	local = ms->be->global_stabs->next;
// 	global = ms->be->global_stabs;
// 	val = ft_lookup_stab(local, key);
// 	if (val == NULL)
// 		return (-1);
// 	val = ft_strdup(val);
// 	key = ft_strdup(key);
// 	ft_add_to_stab(ms, global, key, val);
// 	ft_remove_from_stab(local, key);
// 	return (0);
// }

// /* function to print the contents of either the local or the global symbol table
// functionality:
// 1. Traverse the selected symbol table and print the key and val
// */
// void	ft_print_stab(t_ms *ms, int lvl)
// {
// 	t_stab_st		*tmp;
// 	t_stab			*tmp2;
// 	int				i;

// 	tmp = ms->be->global_stabs;
// 	while (tmp)
// 	{
// 		if (tmp->level == lvl)
// 		{
// 			i = 0;
// 			while (i < tmp->size)
// 			{
// 				tmp2 = tmp->stab[i];
// 				while (tmp2 != NULL)
// 				{
// 					printf("key: %s, val: %s\n", tmp2->key, tmp2->val);
// 					tmp2 = tmp2->next;
// 				}
// 				i++;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }