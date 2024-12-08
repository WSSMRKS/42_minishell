/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsl_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:32:40 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:22:27 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"

/// @brief Find the first occurence of a character in a string.
/// @param s The string to search in.
/// @param c The character to search for.
/// @return (Null)Pointer to the first occurence of c.
const char	*strsl_chr(t_str_slice s, char c)
{
	while (s.len > 0)
	{
		if (*s.str == c)
			return (s.str);
		s.str += 1;
		s.len -= 1;
	}
	return (0);
}

/// @brief Find the last occurence of a character in a string.
/// @param s The string to search in.
/// @param c The character to search for.
/// @return (Null)Pointer to the last occurence of c.
const char	*strsl_rchr(t_str_slice s, char c)
{
	while (s.len > 0)
	{
		if (s.str[s.len - 1] == c)
			return (s.str + s.len - 1);
		s.len--;
	}
	return (0);
}
