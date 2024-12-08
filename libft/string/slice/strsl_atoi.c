/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsl_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:44:55 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"

static int32_t	handle_sign(t_str_slice *s)
{
	int32_t	sign;

	if (s->len == 0)
		return (0);
	sign = 1;
	if (*s->str == '-')
	{
		sign = -1;
		strsl_move_inplace(s, 1);
	}
	else if (*s->str == '+')
		strsl_move_inplace(s, 1);
	return (sign);
}

/// @brief Handle the next digit in the string.
/// @param out The current value of the integer to be modified.
/// @param c The current char.
/// @param sign The sign of the integer.
/// @param base The base to use for the conversion.
/// @return 1 if the conversion was successful, 0 if the char is invalid, 2 if
/// the integer overflowed and was capped at INT_MIN or INT_MAX.
static int32_t	handle_next_char(int32_t *out, char c, int32_t sign,
		t_str_slice base)
{
	const char	*base_match;
	int32_t		digit;

	base_match = strsl_chr(base, c);
	if (!base_match)
		return (false);
	digit = (int32_t)(base_match - base.str);
	if (*out > INT32_MAX / (int32_t)base.len)
		return (2);
	if (*out == INT32_MAX / (int32_t)base.len)
	{
		if (sign == -1 && digit > ((INT32_MAX % (int32_t)base.len) + 1))
		{
			*out = INT32_MIN;
			return (2);
		}
		if (sign == 1 && digit > INT32_MAX % (int32_t)base.len)
		{
			*out = INT32_MAX;
			return (2);
		}
	}
	*out *= base.len;
	*out += digit;
	return (true);
}

static void	skip_whitespace(t_str_slice *s)
{
	while (s->len && ft_isspace(*s->str))
		strsl_move_inplace(s, 1);
}

/// @brief Convert a string to an integer.
/// @param s The string to convert.
/// @param base The base to use for the conversion.
/// @param out The integer to write to.
/// @param ofb The overflow behavior.
/// @return True if the conversion was successful, false otherwise.
/// @note Will skip leading/trailing whitespace and accept an optional sign.
/// @note Will return false if the string is empty or contains invalid chars.
bool	strsl_atoi(t_str_slice s, t_str_slice base, int32_t *out,
		t_overflow_behavior ofb)
{
	int32_t	sign;
	int32_t	code;

	skip_whitespace(&s);
	sign = handle_sign(&s);
	*out = 0;
	if (s.len == 0 || !ft_isdigit(*s.str))
		return (false);
	code = 1;
	while (s.len && code == 1)
	{
		code = handle_next_char(out, *s.str, sign, base);
		if (code == 1)
			strsl_move_inplace(&s, 1);
	}
	if (code == 2 && ofb == OFB_ERROR)
		return (false);
	if (code != 2)
		*out *= sign;
	skip_whitespace(&s);
	return (s.len == 0);
}
