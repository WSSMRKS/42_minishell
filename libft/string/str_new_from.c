/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_new_from.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:11:52 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/18 17:22:28 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Wraps the given string in a t_str.
/// @param str String to wrap.
/// @param len Length of the given string.
/// @return Wrapped string or empty string if 's' is null.
/// @note Will not malloc.
/// @warning The given length must be the actual length of the string.
/// @warning The given string must be freeable (for str_destroy to not crash).
/// @warning The given string may only be used through this wrapper afterwards.
t_str	str_from_parts(char *str, size_t len)
{
	if (str)
		return ((t_str){.len = len, ._capacity = len + 1, ._large_str = str,
			.heap = true, .mem_err = false});
	return (str_empty());
}

/// @brief Wraps the given string in a t_str (safely).
/// @note Will malloc if the given 'len' is larger than the len of the string.
/// @param str String to wrap.
/// @param new_len Length of the resulting string (len of given `str` or less).
/// @return Wrapped string or empty string if 's' is null.
/// @warning The given string must be freeable.
/// @warning The given string may not be used after wrapping.
/// @warning Check the error flag for memory allocation errors.
t_str	str_from(char *str, size_t new_len)
{
	t_str	out;
	size_t	actual_len;

	out = str_empty();
	if (str)
	{
		actual_len = ft_strlen(str);
		new_len = usizemin(actual_len, new_len);
		out.len = new_len;
		out._capacity = actual_len + 1;
		str[new_len] = 0;
		out._large_str = str;
		out.heap = true;
	}
	return (out);
}

t_str	str_from2(char *str)
{
	return (str_from(str, ft_strlen(str)));
}
