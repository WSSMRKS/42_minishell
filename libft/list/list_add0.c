/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:50:02 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:06:18 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Adds data to the back of the list.
/// @param list The list to add to.
/// @param data The (nullable) data to add.
/// @return true if the data was added, false if allocation failed.
/// @note If allocation fails, the destructor is called on the data.
bool	list_push0_back(t_list *list, void *data)
{
	if (!list_push0_back_ref(list, data))
	{
		if (list && list->destructor && data)
			list->destructor(data);
		return (false);
	}
	return (true);
}

/// Adds data to the front of the list.
/// @param list The list to add to.
/// @param data The (nullable) data to add.
/// @return true if the data was added, false if allocation failed.
/// @note If allocation fails, the destructor is called on the data.
bool	list_push0_front(t_list *list, void *data)
{
	if (!list_push0_front_ref(list, data))
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
/// @param data The (nullable) data to insert.
/// @return true if the data was inserted, false if allocation failed
/// or the index was out of bounds.
/// @note If allocation fails, the destructor is called on the data.
bool	list_insert0_at(t_list *list, size_t index, void *data)
{
	if (!list_insert0_at_ref(list, index, data))
	{
		if (list && list->destructor && data)
			list->destructor(data);
		return (false);
	}
	return (true);
}
