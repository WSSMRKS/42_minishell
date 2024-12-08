/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 23:27:59 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:18:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
/// @brief Append a character to the string.
/// @param str The string to append to.
/// @param c The character to append.
/// @warning Check the error flag for memory allocation errors.
void	str_push(t_str *str, char c)
{
	char	*cstr;

	if (str->len + 1 >= str_capacity(str))
		if (!str_try_grow(str, 1))
			return ;
	cstr = cstr_mut(str);
	cstr[str->len++] = c;
	cstr[str->len] = 0;
}

/// @brief Insert a character at the start of the string.
/// @param str The string to insert into.
/// @param c The character to insert.
/// @warning Check the error flag for memory allocation errors.
void	str_push_front(t_str *str, char c)
{
	str_insert(str, 0, c);
}

/// @brief Append a character n times to the string.
/// @param str The string to append to.
/// @param c The character to append.
/// @param n The number of times to append the character.
/// @warning Check the error flag for memory allocation errors.
void	str_pushn(t_str *str, char c, size_t n)
{
	char	*cstr;
	size_t	cap;

	cap = str_capacity(str);
	if (str->len + n >= cap)
		if (!str_try_grow(str, str->len + n - cap + 1))
			return ;
	cstr = cstr_mut(str);
	while (n--)
		cstr[str->len++] = c;
	cstr[str->len] = 0;
}

/// @brief Insert a character n times at the start of the string.
/// @param str The string to insert into.
/// @param c The character to insert.
/// @param n The number of times to insert the character.
/// @warning Check the error flag for memory allocation errors.
void	str_pushn_front(t_str *str, char c, size_t n)
{
	str_insertn(str, 0, c, n);
}
