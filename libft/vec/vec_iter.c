/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:02:47 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Iterates over the vec.
/// @param vec Vec to iterate over.
/// @param iter Function to call for each element.
void	vec_iter(t_vec *vec, t_vec_iter iter)
{
	size_t	i;
	void	*buf;

	i = 0;
	buf = vec_get(vec);
	while (i < vec->len)
	{
		iter(buf + i * vec->element_size);
		++i;
	}
}

/// @brief Iterates over the vec with index.
/// @param vec Vec to iterate over.
/// @param iteri Function to call for each element.
/// @param extra Extra data to pass to the iteri function.
void	vec_iteri(t_vec *vec, t_vec_iteri iteri, void *extra)
{
	size_t	i;

	i = 0;
	while (i < vec->len)
	{
		iteri(vec, i, extra);
		++i;
	}
}

/// @brief Maps all elements of the vec into a new vec with new element_size.
/// @param vec Vec to map.
/// @param map Function to map the elements.
/// @param element_size Size of a single element in the new vec.
/// @return New vec with mapped elements.
/// @warning Check the error flag for memory allocation errors.
t_vec	vec_map(const t_vec *vec, t_vec_map map, size_t element_size)
{
	t_vec	out;
	size_t	i;
	void	*buf;
	void	*out_buf;

	out = vec_empty_with_capacity(element_size, vec->len);
	if (out.mem_err)
		return (out);
	i = 0;
	buf = vec_get(vec);
	out_buf = vec_get(&out);
	while (i < vec->len)
	{
		map(buf + i * vec->element_size, out_buf + i * element_size);
		++i;
		out.len++;
	}
	return (out);
}

/// @brief Maps all elements of the vec into a new vec with new element_size.
/// @param vec Vec to map.
/// @param mapi Function to map the elements.
/// @param element_size Size of a single element in the new vec.
/// @param extra Extra data to pass to the mapi function.
/// @return New vec with mapped elements.
/// @warning Check the error flag for memory allocation errors.
t_vec	vec_mapi(const t_vec *vec, t_vec_mapi mapi, size_t element_size,
		void *extra)
{
	t_vec	out;
	size_t	i;

	out = vec_empty_with_capacity(element_size, vec->len);
	if (out.mem_err)
		return (out);
	i = 0;
	while (i < vec->len)
	{
		out.len++;
		mapi(vec, &out, i, extra);
		++i;
	}
	return (out);
}
