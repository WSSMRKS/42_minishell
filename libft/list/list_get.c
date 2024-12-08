/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:19:07 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:06:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// list_get.c

#include "ft_list.h"

/// Gets data from the front of the list and stores it at the given location.
/// @param list The list to get from.
/// @param out Where to store the data.
/// @return true if data was retrieved, false if the list is empty or invalid.
bool	list_get_front(const t_list *list, void **out)
{
	t_node	*node;

	if (out == NULL || !list_get_head(list, &node))
		return (false);
	*out = node->data;
	return (true);
}

/// Gets data from the back of the list and stores it at the given location.
/// @param list The list to get from.
/// @param out Where to store the data.
/// @return true if data was retrieved, false if the list is empty or invalid.
bool	list_get_back(const t_list *list, void **out)
{
	t_node	*node;

	if (out == NULL || !list_get_tail(list, &node))
		return (false);
	*out = node->data;
	return (true);
}

/// Gets data at the specified index and stores it at the given location.
/// @param list The list to get from.
/// @param index The index to get from.
/// @param out Where to store the data.
/// @return true if data was retrieved, false if the index was out of bounds
/// or the list is invalid.
bool	list_get_at(const t_list *list, size_t index, void **out)
{
	t_node	*node;

	if (out == NULL || !list_get_node_at(list, index, &node))
		return (false);
	*out = node->data;
	return (true);
}
