/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:53:49 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	map_cstr_into_str(const void *from, void *to)
{
	char *const	*cstr;

	cstr = from;
	*(t_str *)to = str_from_parts(*cstr, ft_strlen(*cstr));
}

void	map_cstr_to_cloned_str(const void *from, void *to)
{
	*(t_str *)to = str_clone_from(cstr_view(*(const char **)from));
}

/// @brief Transforms a vec of cstrings to a vec of strings.
/// @param cstrs Vec of cstrings to be turned into a vec of strings.
/// @warning `cstrs` must be made of owned, freeable cstrs.
/// @return True if successful, false otherwise.
bool	vec_cstrs_into_strs(t_vec *cstrs)
{
	t_vec	tmp;

	tmp = vec_map(cstrs, map_cstr_into_str, sizeof(t_str));
	if (tmp.mem_err)
	{
		vec_destroy(&tmp, 0);
		return (false);
	}
	vec_destroy(cstrs, 0);
	*cstrs = tmp;
	return (true);
}

/// @brief Transforms a vec of cstrings to a vec of cloned strings.
/// @param cstrs Vec of cstrings.
/// @param out Vec of cloned strings.
/// @warning `out` may *NOT* be an alias of `cstrs`.
/// @return True if successful, false otherwise.
bool	vec_cstrs_to_cloned_strs(const t_vec *cstrs, t_vec *out)
{
	t_vec	tmp;

	tmp = vec_map(cstrs, map_cstr_to_cloned_str, sizeof(t_str));
	if (tmp.mem_err || vec_contains(&tmp, str_mem_err))
	{
		vec_destroy(&tmp, iter_str_destroy);
		return (false);
	}
	*out = tmp;
	return (true);
}
