/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 18:48:43 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <stdbool.h>

static bool	ft_add_vars(t_ms *ms, t_cmd_list *curr)
{
	t_list_words	*words;
	bool			ok;

	words = curr->cmd.words->next;
	ok = true;
	while (words)
	{
		if (!ft_add_global_val(ms, words->word))
			ok = false;
		words = words->next;
	}
	return (ok);
}

static void	ft_extract_keys(t_ms *ms, int lvl, char **sorted_array)
{
	t_stab_st		*tmp;
	t_stab			*tmp2;
	int				i;
	int				j;

	j = 0;
	tmp = ms->be->global_stabs;
	while (tmp)
	{
		if (tmp->level == lvl)
		{
			i = 0;
			while (i < tmp->size)
			{
				tmp2 = tmp->stab[i];
				while (tmp2 != NULL)
				{
					sorted_array[j++] = tmp2->key;
					tmp2 = tmp2->next;
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}

static int	ft_strcmp_handler(const void *ptr1, const void *ptr2)
{
	char	**str1;
	char	**str2;

	str1 = (char **) ptr1;
	str2 = (char **) ptr2;
	return (ft_strcmp(*str1, *str2));
}

/*
Functionality:
- extract all the vals in the hash table to an array.
  (without mallocing the keys&vals)
- sort the array
- call ft_lookup val to print one after the other.
*/
static void	ft_print_alpha(t_ms *ms)
{
	char	**sorted_array;
	int		i;

	i = 0;
	sorted_array = ft_calloc(sizeof(char *), ms->be->global_stabs->used + 1);
	ft_extract_keys(ms, 1, sorted_array);
	arr_qsort(sorted_array, ms->be->global_stabs->used, sizeof(char *),
		ft_strcmp_handler);
	while (sorted_array[i])
	{
		if (ft_lookup_stab(ms->be->global_stabs, sorted_array[i]) == NULL)
			ft_printf("declare -x %s\n", sorted_array[i]);
		else
			ft_printf("declare -x %s=\"%s\"\n", sorted_array[i],
				ft_lookup_stab(ms->be->global_stabs, sorted_array[i]));
		i++;
	}
	free(sorted_array);
}

int	ft_export(t_ms *ms, t_cmd_list *curr)
{
	(void) curr;
	if (curr->cmd.words->next != NULL)
	{
		if (!ft_add_vars(ms, curr))
			return (1);
	}
	else
		ft_print_alpha(ms);
	return (0);
}
