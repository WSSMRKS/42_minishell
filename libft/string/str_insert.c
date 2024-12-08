/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:16:30 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:18:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Insert a character at a given index into the string.
/// @param str The string to insert into.
/// @param at The index to insert the character at.
/// @param c The character to insert.
/// @warning Check the error flag for memory allocation errors.
void	str_insert(t_str *str, size_t at, char c)
{
	str_insertn(str, at, c, 1);
}

/// @brief Insert a character n times at a given index into the string.
/// @param str The string to insert into.
/// @param at The index to insert the character at.
/// @param c The character to insert.
/// @param n The number of times to insert the character.
/// @warning Check the error flag for memory allocation errors.
void	str_insertn(t_str *str, size_t at, char c, size_t n)
{
	char	*cstr;
	size_t	cap;

	if (at > str->len)
		return ;
	cap = str_capacity(str);
	if (str->len + n >= cap)
		if (!str_try_grow(str, str->len + n - cap + 1))
			return ;
	cstr = cstr_mut(str);
	ft_memmove(cstr + at + n, cstr + at, str->len - at + 1);
	ft_memset(cstr + at, c, n);
	str->len += n;
}

/// @brief Insert a string at a given index into the string.
/// @param str The string to insert into.
/// @param at The index to insert the string at.
/// @param s The string to insert.
/// @warning Check the error flag for memory allocation errors.
void	str_insertstr(t_str *str, size_t at, t_str_slice s)
{
	char	*cstr;
	size_t	cap;

	if (at > str->len)
		return ;
	cap = str_capacity(str);
	if (str->len + s.len >= cap)
		if (!str_try_grow(str, str->len + s.len - cap + 1))
			return ;
	cstr = cstr_mut(str);
	ft_memmove(cstr + at + s.len, cstr + at, str->len - at + 1);
	cstr = cstr + at;
	str->len += s.len;
	while (*s.str && s.len--)
		*cstr++ = *s.str++;
}

/// @brief Insert a string n times at a given index into the string.
/// @param str The string to insert into.
/// @param at The index to insert the string at.
/// @param s The string to insert.
/// @param n The number of times to insert the string.
/// @warning Check the error flag for memory allocation errors.
void	str_insertstrn(t_str *str, size_t at, t_str_slice s, size_t n)
{
	char	*cstr;
	size_t	cap;

	if (at > str->len)
		return ;
	cap = str_capacity(str);
	if (str->len + n * s.len >= cap)
		if (!str_try_grow(str, str->len + n * s.len - cap + 1))
			return ;
	cstr = cstr_mut(str);
	ft_memmove(cstr + at + n * s.len, cstr + at, str->len - at + 1);
	while (n--)
		ft_memcpy(cstr + at + n * s.len, s.str, s.len);
	str->len += s.len * n;
}
