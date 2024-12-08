/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_grow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:27:44 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Try to set the capacity of the vec to a given value.
/// @param vec The vec to modify.
/// @param min_growth The minimum growth of the vec.
/// @return true if the operation was successful, otherwise false.
/// @warning Check the error flag for memory allocation errors.
bool	vec_try_grow(t_vec *vec, size_t min_growth)
{
	size_t	new_capacity;

	new_capacity = usizemax((vec_capacity(vec) + min_growth) * FT_VEC_GROW,
			FT_VEC_MIN_HEAP_CAPACITY);
	return (vec_try_set_capacity(vec, new_capacity));
}

/// @brief Try to set the capacity of the vec to the current length.
/// @param vec The vec to modify.
/// @note This function can be used to free unused memory.
/// @return true if the operation was successful, otherwise false.
/// @warning Check the error flag for memory allocation errors.
bool	vec_shrink_to_fit(t_vec *vec)
{
	if (vec_capacity(vec) != vec->len)
		return (vec_try_set_capacity(vec, vec->len));
	return (true);
}
