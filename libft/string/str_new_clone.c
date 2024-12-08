/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_new_clone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:13:04 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:18:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Clones the given string slice into a new string.
/// @param s The string slice to clone.
/// @return The new string.
/// @warning Check the error flag for memory allocation errors.
t_str	str_clone_from(t_str_slice s)
{
	t_str	str;
	char	*cstr;

	str = str_empty_with_capacity(s.len + 1);
	if (str_capacity(&str) > s.len)
	{
		cstr = cstr_mut(&str);
		str.len = s.len;
		ft_memcpy(cstr, s.str, s.len);
		cstr[s.len] = 0;
	}
	return (str);
}
