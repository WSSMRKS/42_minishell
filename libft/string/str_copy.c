/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:25:11 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:18:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Copy a string.
/// @param dst The destination string.
/// @param src The source string.
/// @warning Check the error flag for memory allocation errors.
void	str_replace(t_str *dst, t_str_slice src)
{
	str_clear(dst);
	str_cat(dst, src);
}

/// @brief Concatenate a string.
/// @param dst The destination string.
/// @param src The source string.
/// @warning Check the error flag for memory allocation errors.
void	str_cat(t_str *dst, t_str_slice src)
{
	char	*cstr;
	size_t	cap;

	cap = str_capacity(dst);
	if (dst->len + src.len >= cap)
		if (!str_try_grow(dst, dst->len + src.len - cap + 1))
			return ;
	cstr = cstr_mut(dst);
	ft_memcpy(cstr + dst->len, src.str, src.len);
	dst->len += src.len;
	cstr[dst->len] = 0;
}
