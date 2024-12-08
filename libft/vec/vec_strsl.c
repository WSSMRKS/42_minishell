/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_strsl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:37:51 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include <stdlib.h>

void	map_strsl_to_cloned_str(const void *from, void *to)
{
	*(t_str *)to = str_clone_from(*(const t_str_slice *)from);
}

void	map_strsl_to_cloned_cstr(const void *from, void *to)
{
	*(char **)to = cstr_clone_from(*(const t_str_slice *)from);
}

/// @brief Transforms a vec of t_str_slice to a vec of cloned strings.
/// @param slices Vec of t_str_slice.
/// @param out Vec of cloned strings.
/// @note `out` may be an alias of `slices`,
/// in which case `slices` is destroyed.
/// @return True if successful, false otherwise.
bool	vec_strsls_to_cloned_strs(const t_vec *slices, t_vec *out)
{
	t_vec	tmp;

	tmp = vec_map(slices, map_strsl_to_cloned_str, sizeof(t_str));
	if (tmp.mem_err || vec_contains(&tmp, str_mem_err))
	{
		vec_destroy(&tmp, iter_str_destroy);
		return (false);
	}
	if (slices == out)
		vec_destroy(out, 0);
	*out = tmp;
	return (true);
}

/// @brief Transforms a vec of t_str_slice to a vec of cloned cstrings.
/// @param slices Vec of t_str_slice.
/// @param out Vec of cloned cstrings.
/// @note `out` may be an alias of `slices`,
/// in which case `slices` is destroyed.
/// @return True if successful, false otherwise.
bool	vec_strsls_to_cloned_cstrs(const t_vec *slices, t_vec *out)
{
	t_vec	tmp;

	tmp = vec_map(slices, map_strsl_to_cloned_cstr, sizeof(char *));
	if (tmp.mem_err || vec_contains(&tmp, ptr_is_null))
	{
		vec_destroy(&tmp, iter_ptr_free);
		return (false);
	}
	if (slices == out)
		vec_destroy(out, 0);
	*out = tmp;
	return (true);
}
