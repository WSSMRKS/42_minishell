/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cstr2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:44:02 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	map_cstr_clone(const void *from, void *to)
{
	*(char **)to = ft_strdup(*(const char **)from);
}

/// @brief Transforms a vec of cstrings to a vec of cloned cstrings.
/// @param cstrs Vec of cstrings.
/// @param out Vec of cloned cstrings.
/// @warning `out` may *NOT* be an alias of `cstrs`.
/// @return True if successful, false otherwise.
bool	vec_cstrs_clone(const t_vec *cstrs, t_vec *out)
{
	t_vec	tmp;

	tmp = vec_map(cstrs, map_cstr_clone, sizeof(char *));
	if (tmp.mem_err || vec_contains(&tmp, ptr_is_null))
	{
		vec_destroy(&tmp, iter_ptr_free);
		return (false);
	}
	*out = tmp;
	return (true);
}
