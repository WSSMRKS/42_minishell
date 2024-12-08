/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new_repeat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:44:07 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Creates a vec by repeating the given array 'n' times.
/// @param arr Array to repeat.
/// @param element_size Size of each element.
/// @param len Length of the given array or less.
/// @param n Number of repetitions.
/// @return Repeated vec or empty vec if `arr` is null.
/// @warning Check the error flag for memory allocation errors.
t_vec	vec_new_repeat(void *arr, size_t element_size, size_t len, size_t n)
{
	t_vec	vec;
	void	*buf;

	vec = vec_empty_with_capacity(element_size, len * n);
	if (arr && vec_capacity(&vec) >= len * n)
	{
		vec.len = len * n;
		buf = vec_get(&vec);
		while (n--)
			ft_memcpy(buf + n * len * element_size, arr,
				len * element_size);
	}
	return (vec);
}
