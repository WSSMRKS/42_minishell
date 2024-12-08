/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:40:01 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:14:45 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list_util.h"
#include <stdlib.h>

/// Creates a new node with the given data.
/// @param data The data to store in the node.
/// @return The new node or NULL if allocation failed.
t_node	*create_node(const void *data)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->data = (void *)data;
	node->next = NULL;
	node->prev = NULL;
	node->next_skip = NULL;
	return (node);
}

static void	slice_fill_from_mid_node(t_node **slice, t_node *mid, size_t radius)
{
	size_t	i;

	slice[radius] = mid;
	if (radius == 0)
		return ;
	i = 0;
	while (i < radius)
	{
		if (slice[radius - i])
			slice[radius - i - 1] = slice[radius - i]->prev;
		else
			slice[radius - i - 1] = NULL;
		i++;
	}
	i = 0;
	while (i < radius)
	{
		if (slice[radius + i])
			slice[radius + i + 1] = slice[radius + i]->next;
		else
			slice[radius + i + 1] = NULL;
		i++;
	}
}

/// Updates affected node's skip pointers after inserting a new node.
/// @param list The list to update.
/// @param new_node The newly added node.
/// @param index The index where the node was inserted.
void	update_skip_pointers_after_add(t_list *list, t_node *new_node,
	size_t index)
{
	t_node	*cache[LIST_SKIP_STEP * 2 + 1];
	size_t	cache_i;
	size_t	i;

	if (list->len <= LIST_SKIP_STEP)
		return ;
	slice_fill_from_mid_node(cache, new_node, LIST_SKIP_STEP);
	i = usizemin(index, LIST_SKIP_STEP) - LIST_SKIP_STEP;
	while (i <= index && i < list->len - LIST_SKIP_STEP)
	{
		cache_i = i - index + LIST_SKIP_STEP;
		cache[cache_i]->next_skip = cache[cache_i + LIST_SKIP_STEP];
		i++;
	}
}

/// Updates affected node's skip pointers before removing a node.
/// @param list The list to update.
/// @param node The node to remove.
/// @param index The index of the node to remove.
void	update_skip_pointers_before_remove(t_list *list, t_node *node,
	size_t index)
{
	t_node	*cache[LIST_SKIP_STEP * 2 + 1];
	size_t	cache_i;
	size_t	i;

	if (list->len <= LIST_SKIP_STEP)
		return ;
	slice_fill_from_mid_node(cache, node, LIST_SKIP_STEP);
	i = usizemin(index, LIST_SKIP_STEP) - LIST_SKIP_STEP;
	while (i < index && i < list->len - LIST_SKIP_STEP)
	{
		cache_i = i - index + LIST_SKIP_STEP;
		cache[cache_i]->next_skip = cache[cache_i + LIST_SKIP_STEP + 1];
		i++;
	}
}
