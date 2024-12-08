/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:50:33 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Pushes a single element to the front of the vec.
/// @param vec The vec to push to.
/// @param data The data to push.
/// @warning Check the error flag for memory allocation errors.
bool	vec_push_front(t_vec *vec, void *data)
{
	return (vec_insert(vec, 0, data));
}

/// @brief Pushes n elements to the front of the vec.
/// @param vec The vec to push to.
/// @param data The data to push.
/// @param n The number of elements to push.
/// @warning Check the error flag for memory allocation errors.
void	vec_pushn_front(t_vec *vec, void *data, size_t n)
{
	vec_insertn(vec, 0, data, n);
}

/// @brief Pushes an array of elements to the front of the vec.
/// @param vec The vec to push to.
/// @param arr The array to push.
/// @param len The number of elements to push.
/// @warning Check the error flag for memory allocation errors.
void	vec_pusharr_front(t_vec *vec, void *arr, size_t len)
{
	vec_insertarr(vec, 0, arr, len);
}

/// @brief Pushes n arrays of elements to the front of the vec.
/// @param vec The vec to push to.
/// @param arr The array to push.
/// @param len The number of elements to push.
/// @param n The number of arrays to push.
/// @warning Check the error flag for memory allocation errors.
/// @note Unoptimized (TODO).
void	vec_pusharrn_front(t_vec *vec, void *arr, size_t len, size_t n)
{
	while (n--)
		vec_insertarr(vec, 0, arr, len);
}
