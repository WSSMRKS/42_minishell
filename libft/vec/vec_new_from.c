/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new_from.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:11:52 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Wraps the given array in a t_vec.
/// @note Will not malloc.
/// @param arr Array to wrap.
/// @param element_size Size of a single element in the array.
/// @param len Number of elements in the array.
/// @return Wrapped vec or empty vec if `arr` is null.
/// @warning May access invalid memory if the given 'len' is out of bounds.
/// @warning The given array must be freeable.
/// @warning The given array may not be used after wrapping.
t_vec	vec_new_from(void *arr, size_t element_size, size_t len)
{
	t_vec	vec;

	vec = vec_empty(element_size);
	if (arr)
	{
		vec.len = len;
		vec._capacity = len;
		vec._large_buf = arr;
		vec.heap = true;
	}
	return (vec);
}
