/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:11:36 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Gives read access to the vec data.
/// @param vec Vec to read from.
/// @return Pointer to the vec data.
void	*vec_get(const t_vec *vec)
{
	if (vec->heap)
		return (vec->_large_buf);
	return ((void *)vec->_small_buf);
}

/// @brief Gives read access to the vec data at the given index.
/// @param vec Vec to read from.
/// @param index Index to read from.
/// @return (Null)Pointer to the vec data at the given index.
void	*vec_get_at(const t_vec *vec, size_t index)
{
	if (index >= vec->len)
		return (NULL);
	return (vec_get(vec) + index * vec->element_size);
}

/// @brief Gives read access to the last element of the vec.
/// @param vec Vec to read from.
/// @return (Null)Pointer to the last element of the vec.
void	*vec_get_last(const t_vec *vec)
{
	if (vec->len == 0)
		return (NULL);
	return (vec_get(vec) + (vec->len - 1) * vec->element_size);
}

/// @brief Destroys the given vec and returns its data.
/// @param vec Vec to destroy.
/// @return Pointer to the vec data or null.
/// @note Might need to malloc if the data is on the stack.
void	*vec_take(t_vec *vec)
{
	char	*out;

	if (vec->heap)
		out = vec->_large_buf;
	else
		out = ft_memdup(vec->_small_buf, vec->len * vec->element_size);
	if (out != 0)
		*vec = vec_empty(vec->element_size);
	return (out);
}

/// @brief Clones the data of the given vec.
/// @param vec Vec to clone.
/// @return Pointer to the cloned vec data or null.
void	*vec_get_cloned(const t_vec *vec)
{
	return (ft_memdup(vec_get(vec), vec->len * vec->element_size));
}
