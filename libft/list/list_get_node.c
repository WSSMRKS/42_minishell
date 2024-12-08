/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:12:44 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:13:44 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Gets the head node of the list and stores it at the given location.
/// @param list The list to get from.
/// @param out Where to store the node.
/// @return true if the node was retrieved, false if the list is empty
/// or invalid.
bool	list_get_head(const t_list *list, t_node **out)
{
	if (list == NULL || out == NULL || list->head == NULL)
		return (false);
	*out = list->head;
	return (true);
}

/// Gets the tail node of the list and stores it at the given location.
/// @param list The list to get from.
/// @param out Where to store the node.
/// @return true if the node was retrieved, false if the list is empty
/// or invalid.
bool	list_get_tail(const t_list *list, t_node **out)
{
	if (list == NULL || out == NULL || list->tail == NULL)
		return (false);
	*out = list->tail;
	return (true);
}

/// Gets the node at the specified index and stores it at the given location.
/// @param list The list to get from.
/// @param index The index of the node to get.
/// @param out Where to store the node.
/// @return true if the node was retrieved, false if the index was out of bounds
/// or the list is invalid.
bool	list_get_node_at(const t_list *list, size_t index, t_node **out)
{
	t_node	*current;
	size_t	i;

	if (list == NULL || out == NULL || index >= list->len)
		return (false);
	if (index == 0)
		return (list_get_head(list, out));
	if (index == list->len - 1)
		return (list_get_tail(list, out));
	current = list->head;
	i = 0;
	while (current && current->next_skip && i + LIST_SKIP_STEP <= index)
	{
		current = current->next_skip;
		i += LIST_SKIP_STEP;
	}
	while (i < index)
	{
		current = current->next;
		i++;
	}
	*out = current;
	return (true);
}
