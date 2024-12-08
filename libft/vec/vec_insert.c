/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:04:38 by kwurster          #+#    #+#             */
/*   Updated: 2024/07/29 13:45:09 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Inserts a single element at the given index.
/// @param vec The vec to insert into.
/// @param index The index to insert at.
/// @param data The data to insert.
bool	vec_insert(t_vec *vec, size_t index, void *data)
{
	return (vec_insertn(vec, index, data, 1));
}

/// @brief Inserts n elements at the given index.
/// @param vec The vec to insert into.
/// @param index The index to insert at.
/// @param data The data to insert.
/// @param n The number of elements to insert.
bool	vec_insertn(t_vec *vec, size_t index, void *data, size_t n)
{
	char	*buf;
	size_t	cap;

	if (!data || index > vec->len)
		return (true);
	cap = vec_capacity(vec);
	if (vec->len + n > cap)
		if (!vec_try_grow(vec, vec->len + n - cap))
			return (false);
	buf = vec_get(vec);
	ft_memmove(buf + (index + n) * vec->element_size, buf + index
		* vec->element_size, (vec->len - index) * vec->element_size);
	vec->len += n;
	while (n--)
		ft_memcpy(buf + (index + n) * vec->element_size, data,
			vec->element_size);
	return (true);
}

/// @brief Inserts an array at the given index.
/// @param vec The vec to insert into.
/// @param index The index to insert at.
/// @param arr The array to insert.
/// @param len The length of the array.
void	vec_insertarr(t_vec *vec, size_t index, void *arr, size_t len)
{
	void	*buf;
	size_t	cap;

	if (!arr || index > vec->len)
		return ;
	cap = vec_capacity(vec);
	if (vec->len + len > cap)
		if (!vec_try_grow(vec, vec->len + len - cap))
			return ;
	buf = vec_get(vec);
	ft_memmove(buf + (index + len) * vec->element_size, buf + index
		* vec->element_size, (vec->len - index) * vec->element_size);
	ft_memcpy(buf + index * vec->element_size, arr, len * vec->element_size);
	vec->len += len;
}

/// @brief Inserts a vec at the given index.
/// @param vec The vec to insert into.
/// @param index The index to insert at.
/// @param data The vec to insert.
void	vec_insertvec(t_vec *vec, size_t index, const t_vec *data)
{
	vec_insertarr(vec, index, vec_get(data), data->len);
}

/// @brief Inserts n elements of a vec at the given index.
/// @param vec The vec to insert into.
/// @param index The index to insert at.
/// @param data The vec to insert.
/// @param n The number of elements to insert.
void	vec_insertvec_sized(t_vec *vec, size_t index, const t_vec *data,
		size_t n)
{
	vec_insertarr(vec, index, vec_get(data), usizemin(n, data->len));
}
