/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_chr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:01:32 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:18:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Find the first occurrence of a character in the string.
/// @param str The string to search.
/// @param c The character to search for.
/// @return A pointer to the first occurrence of the character or NULL.
const char	*str_chr(const t_str *str, char c)
{
	return (ft_strchr(cstr_ref(str), c));
}

/// @brief Find the last occurrence of a character in the string.
/// @param str The string to search.
/// @param c The character to search for.
/// @return A pointer to the last occurrence of the character or NULL.
const char	*str_rchr(const t_str *str, char c)
{
	size_t		i;
	const char	*cstr;

	i = str->len + 1;
	cstr = cstr_ref(str);
	while (i--)
		if (cstr[i] == c)
			return (cstr + i);
	return (0);
}
