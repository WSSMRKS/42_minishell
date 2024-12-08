/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_ref.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:43:27 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:14:32 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Tries to add data to the back of the list.
/// @param list The list to add to.
/// @param data The non-null data to add.
/// @return true if the data was added, false if allocation failed.
/// @return false if data is NULL.
bool	list_push_back_ref(t_list *list, const void *data)
{
	if (data == NULL)
		return (false);
	else
		return (list_push0_back_ref(list, data));
}

/// Tries to add data to the front of the list.
/// @param list The list to add to.
/// @param data The non-null data to add.
/// @return true if the data was added, false if allocation failed.
/// @return false if data is NULL.
bool	list_push_front_ref(t_list *list, const void *data)
{
	if (data == NULL)
		return (false);
	else
		return (list_push0_front_ref(list, data));
}

/// Tries to insert data at the specified index in the list.
/// @param list The list to insert into.
/// @param index The index to insert at.
/// @param data The non-null data to insert.
/// @return true if the data was inserted, false if allocation failed
/// or the index was out of bounds.
/// @return false if data is NULL.
bool	list_insert_at_ref(t_list *list, size_t index, const void *data)
{
	if (data == NULL)
		return (false);
	else
		return (list_insert0_at_ref(list, index, data));
}
