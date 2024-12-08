/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_uninit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:05:22 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	*vec_get_next_uninit(t_vec *vec)
{
	if (vec->len == vec_capacity(vec))
		if (!vec_try_grow(vec, 1))
			return (0);
	return (vec_get(vec) + vec->len * vec->element_size);
}

void	*vec_get_next_uninit_incr_len(t_vec *vec)
{
	void	*uninit;

	uninit = vec_get_next_uninit(vec);
	if (uninit)
		vec->len++;
	return (uninit);
}
