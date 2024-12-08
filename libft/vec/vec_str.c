/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:16:19 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include <stdlib.h>

void	map_str_into_cstr(const void *from, void *to)
{
	*(char **)to = cstr_take((t_str *)from);
}

void	map_str_to_aliased_cstr(const void *from, void *to)
{
	*(char **)to = (char *)cstr_ref(from);
}

/// @brief Transforms a vec of strings to a vec of cstrings.
/// @param strs Vec of strings to be turned into a vec of cstrings.
/// @return True if successful, false otherwise.
bool	vec_strs_into_cstrs(t_vec *strs)
{
	t_vec	tmp;

	tmp = vec_map(strs, map_str_into_cstr, sizeof(char *));
	vec_destroy(strs, 0);
	if (tmp.mem_err || vec_contains(&tmp, ptr_is_null))
	{
		vec_destroy(&tmp, iter_ptr_free);
		return (false);
	}
	*strs = tmp;
	return (true);
}

/// @brief Transforms a vec of strings to a vec of aliased cstrings.
/// @param strs Vec of strings.
/// @param out Vec of aliased cstrings.
/// @warning `out` may *NOT* be an alias of `strs`.
/// @return True if successful, false otherwise.
bool	vec_strs_to_aliased_cstrs(const t_vec *strs, t_vec *out)
{
	*out = vec_map(strs, map_str_to_aliased_cstr, sizeof(char *));
	if (out->mem_err)
	{
		vec_destroy(out, 0);
		return (false);
	}
	return (true);
}
