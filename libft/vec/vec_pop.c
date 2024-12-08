/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:05:03 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Remove the last element from the vec.
/// @param vec  The vec to remove the element from.
/// @return The removed element.
/// @warning Will not remove the element if memory allocation fails.
/// @warning Check the error flag for memory allocation errors.
t_vec	vec_pop(t_vec *vec)
{
	return (vec_extract_range(vec, vec->len - 1, vec->len));
}

/// @brief Remove the first element from the vec.
/// @param vec The vec to remove the element from.
/// @return The removed element.
/// @warning Will not remove the element if memory allocation fails.
/// @warning Check the error flag for memory allocation errors.
t_vec	vec_pop_front(t_vec *vec)
{
	return (vec_extract_range(vec, 0, 1));
}
