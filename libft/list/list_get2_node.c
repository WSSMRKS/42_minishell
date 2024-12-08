/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get2_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:15:16 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:13:25 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Gets the head node of the list.
/// @param list The list to get from.
/// @return The head node or NULL if the list is empty or invalid.
t_node	*list_get2_head(const t_list *list)
{
	t_node	*node;

	if (!list_get_head(list, &node))
		return (NULL);
	return (node);
}

/// Gets the tail node of the list.
/// @param list The list to get from.
/// @return The tail node or NULL if the list is empty or invalid.
t_node	*list_get2_tail(const t_list *list)
{
	t_node	*node;

	if (!list_get_tail(list, &node))
		return (NULL);
	return (node);
}

/// Gets the node at the specified index.
/// @param list The list to get from.
/// @param index The index of the node to get.
/// @return The node at the specified index or NULL if the index was
/// out of bounds or the list is invalid.
t_node	*list_get2_node_at(const t_list *list, size_t index)
{
	t_node	*node;

	if (!list_get_node_at(list, index, &node))
		return (NULL);
	return (node);
}
