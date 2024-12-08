/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:27:59 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Pushes an element to the end of the vec.
/// @param vec Vec to push to.
/// @param data Data to push.
/// @warning Check the error flag for memory allocation errors.
bool	vec_push(t_vec *vec, void *data)
{
	if (!data)
		return (true);
	if (vec->len == vec_capacity(vec))
		if (!vec_try_grow(vec, 1))
			return (false);
	ft_memcpy(vec_get(vec) + vec->len * vec->element_size, data,
		vec->element_size);
	vec->len++;
	return (true);
}

/// @brief Pushes an element n times to the end of the vec.
/// @param vec Vec to push to.
/// @param data Data to push.
/// @param n Number of times to push the data.
/// @warning Check the error flag for memory allocation errors.
void	vec_pushn(t_vec *vec, void *data, size_t n)
{
	void	*buf;
	size_t	cap;

	if (!data)
		return ;
	cap = vec_capacity(vec);
	if (vec->len + n > cap)
		if (!vec_try_grow(vec, vec->len + n - cap))
			return ;
	buf = vec_get(vec);
	while (n--)
	{
		ft_memcpy(buf + vec->len * vec->element_size, data, vec->element_size);
		vec->len++;
	}
}

/// @brief Pushes an array to the end of the vec.
/// @param vec Vec to push to.
/// @param arr Array to push.
/// @param len Length of the array.
/// @warning Check the error flag for memory allocation errors.
void	vec_pusharr(t_vec *vec, void *arr, size_t len)
{
	void	*buf;
	size_t	cap;

	if (!arr)
		return ;
	cap = vec_capacity(vec);
	if (vec->len + len > cap)
		if (!vec_try_grow(vec, vec->len + len - cap))
			return ;
	buf = vec_get(vec);
	ft_memcpy(buf + vec->len * vec->element_size, arr, len * vec->element_size);
	vec->len += len;
}

/// @brief Pushes an array n times to the end of the vec.
/// @param vec Vec to push to.
/// @param arr Array to push.
/// @param len Length of the array.
/// @param n Number of times to push the array.
/// @warning Check the error flag for memory allocation errors.
void	vec_pusharrn(t_vec *vec, void *arr, size_t len, size_t n)
{
	void	*buf;
	size_t	cap;

	if (!arr)
		return ;
	cap = vec_capacity(vec);
	if (vec->len + len * n > cap)
		if (!vec_try_grow(vec, vec->len + len * n - cap))
			return ;
	buf = vec_get(vec);
	while (n--)
		ft_memcpy(buf + (vec->len + n) * vec->element_size, arr, len
			* vec->element_size);
	vec->len += len;
}
