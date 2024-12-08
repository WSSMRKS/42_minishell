/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:47 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include <stdlib.h>

/// @brief Shift the vec by 'n' elements to the left.
/// @param vec The vec to shift.
/// @param n The number of elements to shift by.
void	vec_shiftleft(t_vec *vec, size_t n)
{
	ft_memmove(vec_get(vec), vec_get_at(vec, n), (vec->len - n)
		* vec->element_size);
}

/// @brief Shift the vec by 'n' elements to the right.
/// @param vec The vec to shift.
/// @param n The number of elements to shift by.
/// @warning The left most 'n' elements are left unchanged.
void	vec_shiftright(t_vec *vec, size_t n)
{
	ft_memmove(vec_get_at(vec, n), vec_get(vec), (vec->len - n)
		* vec->element_size);
}

/// @brief Rotate the vec by 'n' elements to the right.
/// @param vec The vec to rotate.
/// @param n The number of elements to rotate by.
/// @return true if the operation was successful, false otherwise.
/// @warning Will not rotate elements if memory allocation fails.
bool	vec_rotate(t_vec *vec, size_t n)
{
	t_vec	temp;

	n = n % vec->len;
	temp = vec_new_clone(vec_get_at(vec, vec->len - n), vec->element_size, n);
	if (!temp.mem_err)
	{
		vec_shiftright(vec, n);
		ft_memcpy(vec_get(vec), vec_get(&temp), n * vec->element_size);
	}
	if (temp.heap)
		free(temp._large_buf);
	return (!temp.mem_err);
}

/// @brief Rotate the vec by 'n' elements to the left.
/// @param vec The vec to rotate.
/// @param n The number of elements to rotate by.
/// @return true if the operation was successful, false otherwise.
/// @warning Will not rotate elements if memory allocation fails.
bool	vec_rrotate(t_vec *vec, size_t n)
{
	t_vec	temp;

	n = n % vec->len;
	temp = vec_new_clone(vec_get(vec), vec->element_size, n);
	if (!temp.mem_err)
	{
		vec_shiftleft(vec, n);
		ft_memcpy(vec_get_at(vec, vec->len - n), vec_get(&temp), n
			* vec->element_size);
	}
	if (temp.heap)
		free(temp._large_buf);
	return (!temp.mem_err);
}
