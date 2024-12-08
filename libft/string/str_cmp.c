/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:56:42 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/18 17:59:36 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Checks if the given string is identical to another string.
/// Strings can be equal but not be identical
/// if the data location is different.
/// @param str1
/// @param str2
/// @return true if the strings are identical, false otherwise.
bool	str_identical(const t_str *str1, const t_str *str2)
{
	if (str1->heap)
		return (str2->heap && str1->_large_str == str2->_large_str);
	return (ft_strcmp(str1->_small_str, str2->_small_str) == 0);
}

/// @brief Checks if the given string is equal to another string.
/// @param str1
/// @param str2
/// @return true if the strings are equal, false otherwise.
bool	str_eq(const t_str *str1, const t_str *str2)
{
	if (str1->len != str2->len)
		return (false);
	return (ft_strcmp(cstr_ref(str1), cstr_ref(str2)));
}

/// @brief Checks if the given string starts with a given pattern.
/// @param str The string to check.
/// @param pattern The pattern to check for.
/// @return true if the string starts with the pattern, false otherwise.
bool	str_starts_with(const t_str *str, const t_str *pattern)
{
	if (str->len < pattern->len)
		return (false);
	return (ft_memcmp(cstr_ref(str), cstr_ref(pattern), pattern->len) == 0);
}
