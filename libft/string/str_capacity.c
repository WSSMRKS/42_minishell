/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capacity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:48:52 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include <stdlib.h>

static void	heap_arr_to_stack_arr(t_str *str)
{
	char	*temp;

	temp = str->_large_str;
	ft_strlcpy(str->_small_str, temp, FT_SMALL_STR);
	str->len = usizemin(str->len, FT_SMALL_STR - 1);
	str->heap = false;
	free(temp);
}

static bool	stack_arr_to_heap_arr(t_str *str, size_t capacity)
{
	char	*temp;

	temp = malloc(capacity);
	if (temp == 0)
		return (false);
	ft_strlcpy(temp, str->_small_str, capacity);
	str->_large_str = temp;
	str->heap = true;
	return (true);
}

static bool	resize_heap_arr(t_str *str, size_t n)
{
	char	*temp;

	temp = ft_reallocstring(str->_large_str, n);
	if (temp == 0)
		return (false);
	str->_large_str = temp;
	return (true);
}

/// @brief Changes the capacity of the string.
/// @param str String to change the capacity of.
/// @param n New capacity.
/// @note The capacity can't be less than FT_SMALL_STR.
/// @return true if the operation was successful, false otherwise.
/// @warning Check the error flag for memory allocation errors.
bool	str_try_set_capacity(t_str *str, size_t n)
{
	bool	success;

	success = true;
	n = usizemax(n, FT_SMALL_STR);
	if (n == FT_SMALL_STR)
	{
		if (str->heap)
			heap_arr_to_stack_arr(str);
	}
	else if (!str->heap)
		success = stack_arr_to_heap_arr(str, n);
	else
		success = resize_heap_arr(str, n);
	if (success)
	{
		if (str->heap)
			str->_capacity = n;
		str->len = usizemin(str->len, n - 1);
	}
	else
		str->mem_err = true;
	return (success);
}

/// @brief Get the capacity of the string.
/// @param str String to get the capacity of.
/// @return The capacity of the string.
size_t	str_capacity(const t_str *str)
{
	if (str->heap)
		return (str->_capacity);
	return (FT_SMALL_STR);
}
