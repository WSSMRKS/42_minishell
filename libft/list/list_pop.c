/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 05:55:00 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:14:04 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_list_util.h"
#include <stdlib.h>

/// Extracts data from the back of the list and stores it at the given location.
/// @param list The list to pop from.
/// @param out Where to store the extracted data.
/// @return true if data was extracted, false if the list is empty or invalid.
bool	list_pop_back(t_list *list, void **out)
{
	t_node	*node;

	if (list == NULL || list->tail == NULL || out == NULL)
		return (false);
	node = list->tail;
	update_skip_pointers_before_remove(list, node, list->len - 1);
	*out = node->data;
	list->tail = node->prev;
	if (list->tail)
		list->tail->next = NULL;
	else
		list->head = NULL;
	free(node);
	list->len--;
	return (true);
}

/// Extracts data from the front of the list and stores it
/// at the given location.
/// @param list The list to pop from.
/// @param out Where to store the extracted data.
/// @return true if data was extracted, false if the list is empty or invalid.
bool	list_pop_front(t_list *list, void **out)
{
	t_node	*node;

	if (list == NULL || list->head == NULL || out == NULL)
		return (false);
	node = list->head;
	*out = node->data;
	list->head = node->next;
	if (list->head)
		list->head->prev = NULL;
	else
		list->tail = NULL;
	free(node);
	list->len--;
	return (true);
}

/// Extracts data at the specified index and stores it at the given location.
/// @param list The list to pop from.
/// @param index The index to pop from.
/// @param out Where to store the extracted data.
/// @return true if data was extracted, false if the index was out of bounds
/// or the list is invalid.
bool	list_pop_at(t_list *list, size_t index, void **out)
{
	t_node	*node;

	if (list == NULL || out == NULL || index >= list->len)
		return (false);
	if (index == 0)
		return (list_pop_front(list, out));
	if (index == list->len - 1)
		return (list_pop_back(list, out));
	list_get_node_at(list, index, &node);
	*out = node->data;
	update_skip_pointers_before_remove(list, node, index);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
	list->len--;
	return (true);
}
