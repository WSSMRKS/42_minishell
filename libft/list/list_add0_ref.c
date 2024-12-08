/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add0_ref.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:52:00 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:06:19 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_list_util.h"

/// Tries to add data to the back of the list.
/// @param list The list to add to.
/// @param data The (nullable) data to add.
/// @return true if the data was added, false if allocation failed.
bool	list_push0_back_ref(t_list *list, const void *data)
{
	t_node	*node;

	if (list == NULL)
		return (false);
	node = create_node(data);
	if (node == NULL)
		return (false);
	if (list->tail == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
	update_skip_pointers_after_add(list, node, list->len);
	list->len++;
	return (true);
}

/// Tries to add data to the front of the list.
/// @param list The list to add to.
/// @param data The (nullable) data to add.
/// @return true if the data was added, false if allocation failed.
bool	list_push0_front_ref(t_list *list, const void *data)
{
	t_node	*node;

	if (list == NULL)
		return (false);
	node = create_node(data);
	if (node == NULL)
		return (false);
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}
	update_skip_pointers_after_add(list, node, 0);
	list->len++;
	return (true);
}

/// Tries to insert data at the specified index in the list.
/// @param list The list to insert into.
/// @param index The index to insert at.
/// @param data The (nullable) data to insert.
/// @return true if the data was inserted, false if allocation failed
/// or the index was out of bounds.
bool	list_insert0_at_ref(t_list *list, size_t index, const void *data)
{
	t_node	*node;
	t_node	*current;

	if (list == NULL || index > list->len)
		return (false);
	if (index == 0)
		return (list_push0_front_ref(list, data));
	if (index == list->len)
		return (list_push0_back_ref(list, data));
	node = create_node(data);
	if (node == NULL)
		return (false);
	list_get_node_at(list, index, &current);
	node->prev = current->prev;
	node->next = current;
	current->prev->next = node;
	current->prev = node;
	update_skip_pointers_after_add(list, node, index);
	list->len++;
	return (true);
}
