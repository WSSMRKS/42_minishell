/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:08:48 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:06:35 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Removes and destroys the head node of the list.
/// @param list The list to remove from.
/// @return true if the node was removed, false if the list is empty or invalid.
bool	list_remove_head(t_list *list)
{
	void	*data;

	if (!list_pop_front(list, &data))
		return (false);
	if (list->destructor && data)
		list->destructor(data);
	return (true);
}

/// Removes and destroys the tail node of the list.
/// @param list The list to remove from.
/// @return true if the node was removed, false if the list is empty or invalid.
bool	list_remove_tail(t_list *list)
{
	void	*data;

	if (!list_pop_back(list, &data))
		return (false);
	if (list->destructor && data)
		list->destructor(data);
	return (true);
}

/// Removes and destroys the node at the specified index.
/// @param list The list to remove from.
/// @param index The index to remove at.
/// @return true if the node was removed, false if the index was out of bounds
/// or the list is invalid.
bool	list_remove_at(t_list *list, size_t index)
{
	void	*data;

	if (!list_pop_at(list, index, &data))
		return (false);
	if (list->destructor && data)
		list->destructor(data);
	return (true);
}

/// Removes and destroys a range of nodes from the list.
/// @param list The list to remove from.
/// @param start The start index (inclusive).
/// @param end The end index (exclusive).
/// @return true if the range was removed, false if the range was invalid
/// or the list is invalid.
bool	list_remove_range(t_list *list, size_t start, size_t end)
{
	size_t	i;

	if (list == NULL || start >= list->len || end > list->len || start >= end)
		return (false);
	i = start;
	while (i < end)
	{
		if (!list_remove_at(list, start))
			return (false);
		i++;
	}
	return (true);
}
