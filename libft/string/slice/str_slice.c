/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_slice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:15:30 by kwurster          #+#    #+#             */
/*   Updated: 2024/07/29 13:43:51 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"
#include <stdlib.h>

/// @brief Creates a stringview from a cstr.
/// @param str The string to view.
/// @return The stringview.
t_str_slice	cstr_view(const char *str)
{
	if (str == 0)
		return (strsl_null());
	return ((t_str_slice){.len = ft_strlen(str), .str = str});
}

/// @brief Creates a stringview from a cstr.
/// @param str The string to view.
/// @param len The length of the stringview.
/// @return The stringview.
/// @warning The length of the stringview is not checked.
t_str_slice	cstr_slice(const char *str, size_t len)
{
	return ((t_str_slice){.len = len, .str = str});
}

/// @brief Creates a stringview from a string.
/// @param str The string to view.
/// @return The stringview.
t_str_slice	str_view(const t_str *str)
{
	return ((t_str_slice){.len = str->len, .str = cstr_ref(str)});
}

/// @brief Creates a stringview from a string.
/// @param str The string to view.
/// @param start The start index of the view.
/// @param end The end index of the view.
/// @return The stringview.
t_str_slice	str_slice(const t_str *str, size_t start, size_t end)
{
	start = usizemin(start, str->len);
	end = usizemax(start, usizemin(end, str->len));
	return ((t_str_slice){.len = end - start, .str = cstr_ref(str) + start});
}

/// @brief Clones a stringview into a cstr.
/// @param s The stringview to clone.
/// @return The cloned cstr or null.
char	*cstr_clone_from(t_str_slice s)
{
	char	*out;

	out = malloc(s.len + 1);
	if (out == 0)
		return (0);
	ft_memcpy(out, s.str, s.len);
	out[s.len] = 0;
	return (out);
}
