/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:56:53 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Remove the last character from the string.
/// @param str The string to remove from.
/// @return The removed character.
char	str_pop(t_str *str)
{
	char	*cstr;
	char	out;

	if (str->len == 0)
		return (0);
	cstr = cstr_mut(str);
	out = cstr[--(str->len)];
	cstr[str->len] = 0;
	return (out);
}

/// @brief Remove a character at a given index from the string.
/// @param str The string to remove from.
/// @param at The index of the character to remove.
/// @return The removed character.
char	str_remove(t_str *str, size_t at)
{
	char	*cstr;
	char	out;

	if (at >= str->len)
		return (0);
	cstr = cstr_mut(str);
	out = cstr[at];
	ft_memmove(cstr + at, cstr + at + 1, str->len - at);
	str->len--;
	return (out);
}

/// @brief Remove a range of characters from the string.
/// @param str The string to remove from.
/// @param start The start index of the range to remove.
/// @param end The end index of the range to remove.
void	str_remove_range(t_str *str, size_t start, size_t end)
{
	char	*cstr;

	start = usizemin(start, str->len);
	end = usizemin(end, str->len);
	cstr = cstr_mut(str);
	ft_memmove(cstr + start, cstr + end, str->len - end + 1);
	str->len -= end - start;
}

/// @brief Truncate the string to a given length.
/// @param str The string to truncate.
/// @param new_len The new length of the string.
void	str_trunc(t_str *str, size_t new_len)
{
	new_len = usizemin(new_len, str->len);
	cstr_mut(str)[new_len] = 0;
	str->len = new_len;
}

/// @brief Clear the string.
/// @param str The string to clear.
void	str_clear(t_str *str)
{
	cstr_mut(str)[0] = 0;
	str->len = 0;
	str->mem_err = false;
}
