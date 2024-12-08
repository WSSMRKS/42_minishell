/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_find2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 07:23:49 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:12:28 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Finds the first occurrence of an element in the list that matches the key
/// according to the comparison function.
/// @param list The list to search in.
/// @param key The key to search for.
/// @param cmp The comparison function.
/// @return The found data or NULL if not found.
void	*list_find2(const t_list *list, const void *key, t_list_find_fn cmp)
{
	void	*data;

	if (!list_find(list, key, cmp, &data))
		return (NULL);
	return (data);
}

/// Finds the first node containing an element that matches the key
/// according to the comparison function.
/// @param list The list to search in.
/// @param key The key to search for.
/// @param cmp The comparison function.
/// @return The found node or NULL if not found.
t_node	*list_find2_node(const t_list *list, const void *key,
	t_list_find_fn cmp)
{
	t_node	*node;

	if (!list_find_node(list, key, cmp, &node))
		return (NULL);
	return (node);
}

/// Finds the index of the first element that matches the key
/// according to the comparison function.
/// @param list The list to search in.
/// @param key The key to search for.
/// @param cmp The comparison function.
/// @return The found index or SIZE_MAX if not found.
size_t	list_find2_index(const t_list *list, const void *key,
	t_list_find_fn cmp)
{
	size_t	index;

	if (!list_find_index(list, key, cmp, &index))
		return (SIZE_MAX);
	return (index);
}
