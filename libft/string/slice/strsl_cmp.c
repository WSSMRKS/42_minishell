/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsl_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:40:11 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"

/// @brief Compare two string slices.
/// @param s1
/// @param s2
/// @return True if the slices are equal.
bool	strsl_eq(t_str_slice s1, t_str_slice s2)
{
	if (s1.str == s2.str)
		return (true);
	if (s1.len != s2.len)
		return (false);
	return (ft_memcmp(s1.str, s2.str, s1.len) == 0);
}

/// @brief Check if a string slice starts with a pattern.
/// @param s The string slice to check.
/// @param pattern The pattern to check for.
/// @return True if the string slice starts with the pattern.
bool	strsl_starts_with(t_str_slice s, t_str_slice pattern)
{
	if (s.len < pattern.len)
		return (0);
	return (ft_memcmp(s.str, pattern.str, pattern.len) == 0);
}

/// @brief Check if a string slice ends with a pattern.
/// @param s The string slice to check.
/// @param pattern The pattern to check for.
/// @return True if the string slice ends with the pattern.
bool	strsl_ends_with(t_str_slice s, t_str_slice pattern)
{
	if (s.len < pattern.len)
		return (0);
	return (ft_memcmp(s.str + s.len - pattern.len, pattern.str,
			pattern.len) == 0);
}
