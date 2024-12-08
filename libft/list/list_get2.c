/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:19:24 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:12:59 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// list_get2.c

#include "ft_list.h"

/// Gets data from the front of the list.
/// @param list The list to get from.
/// @return The data or NULL if the list is empty or invalid.
/// @warning This function is not safe to use with a list which
/// may contain NULL data.
void	*list_get2_front(const t_list *list)
{
	void	*data;

	if (!list_get_front(list, &data))
		return (NULL);
	return (data);
}

/// Gets data from the back of the list.
/// @param list The list to get from.
/// @return The data or NULL if the list is empty or invalid.
/// @warning This function is not safe to use with a list which
/// may contain NULL data.
void	*list_get2_back(const t_list *list)
{
	void	*data;

	if (!list_get_back(list, &data))
		return (NULL);
	return (data);
}

/// Gets data at the specified index.
/// @param list The list to get from.
/// @param index The index to get from.
/// @return The data or NULL if the index was out of bounds or
/// the list is invalid.
/// @warning This function is not safe to use with a list which
/// may contain NULL data.
void	*list_get2_at(const t_list *list, size_t index)
{
	void	*data;

	if (!list_get_at(list, index, &data))
		return (NULL);
	return (data);
}
