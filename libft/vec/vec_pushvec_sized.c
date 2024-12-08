/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pushvec_sized.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:05:15 by kwurster          #+#    #+#             */
/*   Updated: 2024/07/29 13:45:28 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Pushes a vec to the end of the vec.
/// @param vec Vec to push to.
/// @param data Vec to push.
/// @param len Number of elements to push.
/// @warning Check the error flag for memory allocation errors.
void	vec_pushvec_sized(t_vec *vec, const t_vec *data, size_t len)
{
	vec_pusharr(vec, vec_get(data), usizemin(len, data->len));
}

/// @brief Pushes a vec to the front of the vec.
/// @param vec Vec to push to.
/// @param data Vec to push.
/// @param len Number of elements to push.
/// @warning Check the error flag for memory allocation errors.
void	vec_pushvec_front_sized(t_vec *vec, const t_vec *data, size_t len)
{
	vec_pusharr_front(vec, vec_get(data), usizemin(len, data->len));
}

/// @brief Pushes n vecs to the end of the vec.
/// @param vec Vec to push to.
/// @param data Vec to push.
/// @param len Number of elements to push.
/// @param n Number of times to push the data.
/// @warning Check the error flag for memory allocation errors.
void	vec_pushvecn_sized(t_vec *vec, const t_vec *data, size_t len, size_t n)
{
	vec_pusharrn(vec, vec_get(data), usizemin(len, data->len), n);
}

/// @brief Pushes n vecs to the front of the vec.
/// @param vec Vec to push to.
/// @param data Vec to push.
/// @param len Number of elements to push.
/// @param n Number of times to push the data.
/// @warning Check the error flag for memory allocation errors.
void	vec_pushvecn_front_sized(t_vec *vec, const t_vec *data, size_t len,
		size_t n)
{
	vec_pusharrn_front(vec, vec_get(data), usizemin(len, data->len), n);
}
