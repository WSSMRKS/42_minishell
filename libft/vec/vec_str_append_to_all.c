/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_str_append_to_all.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:34:59 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Appends a string slice to all strings in a vec of strings.
/// @param vec The vec of strings.
/// @param i The index of the string to append to.
/// @param to_append The string slice to append.
void	iter_str_append(t_vec *vec, size_t i, void *to_append)
{
	t_str	*str;

	str = vec_get_at(vec, i);
	str_pushstr(str, *(t_str_slice *)to_append);
}

/// @brief Appends a string slice to all strings in a vec of strings.
/// @param strs The vec of strings.
/// @param to_append The string slice to append.
/// @return True if successful, false otherwise.
bool	vec_strs_append_to_all(t_vec *strs, t_str_slice to_append)
{
	vec_iteri(strs, iter_str_append, &to_append);
	return (!vec_contains(strs, str_mem_err));
}
