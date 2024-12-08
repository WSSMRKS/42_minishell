/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:33:32 by kwurster          #+#    #+#             */
/*   Updated: 2024/07/29 13:44:40 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Extracts elements in the range [start, end) from the vec.
/// @param vec The vec to extract elements from.
/// @param start The start index of the range.
/// @param end The end index of the range.
/// @return The extracted elements.
/// @note The extracted elements are copied onto a new vec.
/// @warning Will not remove elements if memory allocation fails.
/// @warning Check the error flag for memory allocation errors.
t_vec	vec_extract_range(t_vec *vec, size_t start, size_t end)
{
	t_vec	out;

	if (start >= vec->len || end <= start)
		return (vec_empty(vec->element_size));
	end = usizemin(end, vec->len);
	out = vec_new_clone(vec_get(vec) + start * vec->element_size,
			vec->element_size, end - start);
	if (!out.mem_err)
		vec_remove_range(vec, start, end);
	return (out);
}
