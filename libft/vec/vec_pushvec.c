/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pushvec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:51:45 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Pushes a vec to the end of the vec.
/// @param vec Vec to push to.
/// @param data Vec to push.
/// @warning Check the error flag for memory allocation errors.
void	vec_pushvec(t_vec *vec, const t_vec *data)
{
	vec_pusharr(vec, vec_get(data), data->len);
}

/// @brief Pushes a vec to the front of the vec.
/// @param vec Vec to push to.
/// @param data Vec to push.
/// @warning Check the error flag for memory allocation errors.
void	vec_pushvec_front(t_vec *vec, const t_vec *data)
{
	vec_pusharr_front(vec, vec_get(data), data->len);
}

/// @brief Pushes n vecs to the end of the vec.
/// @param vec Vec to push to.
/// @param data Vec to push.
/// @param n Number of times to push the data.
void	vec_pushvecn(t_vec *vec, const t_vec *data, size_t n)
{
	vec_pusharrn(vec, vec_get(data), data->len, n);
}

/// @brief Pushes n vecs to the front of the vec.
/// @param vec Vec to push to.
/// @param data Vec to push.
/// @param n Number of times to push the data.
void	vec_pushvecn_front(t_vec *vec, const t_vec *data, size_t n)
{
	vec_pusharrn_front(vec, vec_get(data), data->len, n);
}
