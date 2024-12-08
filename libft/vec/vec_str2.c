/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_str2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:01:28 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	map_str_to_str_slice(const void *from, void *to)
{
	*(t_str_slice *)to = str_view(from);
}

/// @brief Transforms a vec of strings to a vec of string slices.
/// @param strs Vec of strings.
/// @param out Vec of string slices.
/// @warning `out` may *NOT* be an alias of `strs`,
/// @return True if successful, false otherwise.
bool	vec_strs_to_str_slices(const t_vec *strs, t_vec *out)
{
	*out = vec_map(strs, map_str_to_str_slice, sizeof(char *));
	if (out->mem_err)
	{
		vec_destroy(out, 0);
		return (false);
	}
	return (true);
}

void	map_str_clone(const void *from, void *to)
{
	*(t_str *)to = str_clone(from);
}

/// @brief Transforms a vec of cstrings to a vec of cloned cstrings.
/// @param cstrs Vec of cstrings.
/// @param out Vec of cloned cstrings.
/// @warning `out` may *NOT* be an alias of `cstrs`.
/// @return True if successful, false otherwise.
bool	vec_strs_clone(const t_vec *strs, t_vec *out)
{
	*out = vec_map(strs, map_str_clone, sizeof(t_str));
	if (out->mem_err || vec_contains(out, str_mem_err))
	{
		vec_destroy(out, iter_str_destroy);
		return (false);
	}
	return (true);
}
