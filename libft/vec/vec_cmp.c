/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:54:05 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Checks if the given vec is identical to another vec.
/// Vecs can be equal but not be identical
/// if the data location is different.
/// @param vec1
/// @param vec2
/// @return true if the vecs are identical, false otherwise.
bool	vec_identical(const t_vec *vec1, const t_vec *vec2)
{
	if (vec1->element_size != vec2->element_size)
		return (false);
	if (vec1->len != vec2->len)
		return (false);
	if (vec1->heap && vec2->heap)
		return (vec1->_large_buf == vec2->_large_buf);
	if (!vec1->heap && !vec2->heap)
		return (ft_memcmp(vec1->_small_buf, vec2->_small_buf, vec1->len
				* vec1->element_size) == 0);
	return (false);
}

/// @brief Checks if the given vec is equal to another vec.
/// @param vec1
/// @param vec2
/// @return true if the vecs are equal, false otherwise.
bool	vec_cmp(const t_vec *vec1, const t_vec *vec2)
{
	if (vec1->element_size != vec2->element_size)
		return (false);
	if (vec1->len != vec2->len)
		return (false);
	if (vec1->heap && vec2->heap)
		return (vec1->_large_buf == vec2->_large_buf);
	return (ft_memcmp(vec_get(vec1), vec_get(vec2),
			vec1->len * vec1->element_size) == 0);
}
