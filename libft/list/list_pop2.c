/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 06:02:05 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:06:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

/// Extracts data from the back of the list and returns it.
/// @param list The list to pop from.
/// @return The extracted data or NULL if the list is empty or invalid.
/// @warning This function is not safe to use with a list which
/// may contain NULL data.
void	*list_pop2_back(t_list *list)
{
	void	*data;

	if (!list_pop_back(list, &data))
		return (NULL);
	return (data);
}

/// Extracts data from the front of the list and returns it.
/// @param list The list to pop from.
/// @return The extracted data or NULL if the list is empty or invalid.
/// @warning This function is not safe to use with a list which
/// may contain NULL data.
void	*list_pop2_front(t_list *list)
{
	void	*data;

	if (!list_pop_front(list, &data))
		return (NULL);
	return (data);
}

/// Extracts data at the specified index and returns it.
/// @param list The list to pop from.
/// @param index The index to pop from.
/// @return The extracted data or NULL if the index was out of bounds
/// or the list is invalid.
/// @warning This function is not safe to use with a list which
/// may contain NULL data.
void	*list_pop2_at(t_list *list, size_t index)
{
	void	*data;

	if (!list_pop_at(list, index, &data))
		return (NULL);
	return (data);
}
