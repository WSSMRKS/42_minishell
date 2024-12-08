/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:51:54 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:06:17 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Adds data to the back of the list.
/// @param list The list to add to.
/// @param data The non-null data to add.
/// @return true if the data was added, false if allocation failed.
/// @return false if data is NULL.
/// @note If allocation fails, the destructor is called on the data.
bool	list_push_back(t_list *list, void *data)
{
	if (!list_push_back_ref(list, data))
	{
		if (list && list->destructor && data)
			list->destructor(data);
		return (false);
	}
	return (true);
}

/// Adds data to the front of the list.
/// @param list The list to add to.
/// @param data The non-null data to add.
/// @return true if the data was added, false if allocation failed.
/// @return false if data is NULL.
/// @note If allocation fails, the destructor is called on the data.
bool	list_push_front(t_list *list, void *data)
{
	if (!list_push_front_ref(list, data))
	{
		if (list && list->destructor && data)
			list->destructor(data);
		return (false);
	}
	return (true);
}

/// Inserts data at the specified index in the list.
/// @param list The list to insert into.
/// @param index The index to insert at.
/// @param data The non-null data to insert.
/// @return true if the data was inserted, false if allocation failed
/// or the index was out of bounds.
/// @return false if data is NULL.
/// @note If allocation fails, the destructor is called on the data.
bool	list_insert_at(t_list *list, size_t index, void *data)
{
	if (!list_insert_at_ref(list, index, data))
	{
		if (list && list->destructor && data)
			list->destructor(data);
		return (false);
	}
	return (true);
}
