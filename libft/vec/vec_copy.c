/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 06:48:43 by kwurster          #+#    #+#             */
/*   Updated: 2024/07/29 13:44:35 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Copies the data of the source vec to the destination vec.
/// @param dst Destination vec.
/// @param src Source vec.
/// @warning Check the error flag for memory allocation errors.
void	vec_copy(t_vec *dst, const t_vec *src)
{
	vec_copy_sized(dst, src, src->len);
}

/// @brief Copies the data of the source vec to the destination vec.
/// @param dst Destination vec.
/// @param src Source vec.
/// @param new_len New length of the destination vec.
/// @warning Check the error flag for memory allocation errors.
void	vec_copy_sized(t_vec *dst, const t_vec *src, size_t new_len)
{
	size_t	cap;

	cap = vec_capacity(dst);
	if (new_len > cap)
	{
		if (!vec_try_grow(dst, new_len - cap))
			return ;
	}
	new_len = usizemin(new_len, src->len);
	ft_memcpy(vec_get(dst), vec_get(src), new_len * src->element_size);
	dst->len = new_len;
}

/// @brief Concatenates the source vec to the destination vec.
/// @param dst Destination vec.
/// @param src Source vec.
/// @warning Check the error flag for memory allocation errors.
void	vec_cat(t_vec *dst, const t_vec *src)
{
	vec_cat_sized(dst, src, src->len);
}

/// @brief Concatenates the source vec to the destination vec.
/// @param dst Destination vec.
/// @param src Source vec.
/// @param n Number of elements to concatenate.
/// @warning Check the error flag for memory allocation errors.
void	vec_cat_sized(t_vec *dst, const t_vec *src, size_t n)
{
	size_t	new_len;
	size_t	cap;

	n = usizemin(n, src->len);
	new_len = dst->len + n;
	cap = vec_capacity(dst);
	if (new_len > cap)
	{
		if (!vec_try_grow(dst, new_len - cap))
			return ;
	}
	ft_memcpy(vec_get(dst) + dst->len * dst->element_size, vec_get(src), n
		* src->element_size);
	dst->len = new_len;
}
