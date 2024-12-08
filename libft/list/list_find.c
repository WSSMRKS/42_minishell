/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 07:23:14 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:12:43 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Finds the first occurrence of an element in the list that matches the key
/// according to the comparison function and stores it at the given location.
/// @param list The list to search in.
/// @param key The key to search for.
/// @param cmp The comparison function.
/// @param out Where to store the found data.
/// @return true if an element was found, false otherwise.
bool	list_find(const t_list *list, const void *key, t_list_find_fn cmp,
	void **out)
{
	t_node	*node;

	if (!list_find_node(list, key, cmp, &node))
		return (false);
	*out = node->data;
	return (true);
}

/// Finds the first node containing an element that matches the key
/// according to the comparison function and stores it at the given location.
/// @param list The list to search in.
/// @param key The key to search for.
/// @param cmp The comparison function.
/// @param out Where to store the found node.
/// @return true if a node was found, false otherwise.
bool	list_find_node(const t_list *list, const void *key, t_list_find_fn cmp,
	t_node **out)
{
	t_node	*current;

	if (list == NULL || cmp == NULL || out == NULL)
		return (false);
	current = list->head;
	while (current)
	{
		if (cmp(current->data, key))
		{
			*out = current;
			return (true);
		}
		current = current->next;
	}
	return (false);
}

/// Finds the index of the first element that matches the key
/// according to the comparison function and stores it at the given location.
/// @param list The list to search in.
/// @param key The key to search for.
/// @param cmp The comparison function.
/// @param out Where to store the found index.
/// @return true if an element was found, false otherwise.
bool	list_find_index(const t_list *list, const void *key, t_list_find_fn cmp,
	size_t *out)
{
	t_node	*current;
	size_t	i;

	if (list == NULL || cmp == NULL || out == NULL)
		return (false);
	current = list->head;
	i = 0;
	while (current)
	{
		if (cmp(current->data, key))
		{
			*out = i;
			return (true);
		}
		current = current->next;
		i++;
	}
	return (false);
}
