/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new_clone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:13:04 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Clones the given vec.
/// @param arr Array to clone.
/// @param element_size Size of each element.
/// @param len Length of the array.
/// @return Cloned vec or empty vec if 'arr' is null.
/// @warning Check the error flag for memory allocation errors.
t_vec	vec_new_clone(const void *arr, size_t element_size, size_t len)
{
	t_vec	vec;

	vec = vec_empty_with_capacity(element_size, len);
	if (arr && vec_capacity(&vec) >= len)
	{
		vec.len = len;
		ft_memcpy(vec_get(&vec), arr, vec.len * element_size);
	}
	return (vec);
}
