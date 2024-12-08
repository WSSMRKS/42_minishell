/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_empty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:47:22 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Creates an empty vec.
/// @param element_size Size of a single element in the vec (sizeof(T)).
/// @note Will not malloc.
/// @return Empty vec.
t_vec	vec_empty(size_t element_size)
{
	t_vec	vec;

	vec.len = 0;
	vec.heap = false;
	vec.mem_err = false;
	vec.element_size = element_size;
	return (vec);
}

/// @brief Creates an empty vec with the given capacity.
/// @param n Capacity of the vec.
/// @return Empty vec.
/// @warning May return with a lower capacity if memory allocation fails.
/// @warning Check the error flag for memory allocation errors.
t_vec	vec_empty_with_capacity(size_t element_size, size_t n)
{
	t_vec	vec;

	vec = vec_empty(element_size);
	vec_try_set_capacity(&vec, n);
	return (vec);
}
