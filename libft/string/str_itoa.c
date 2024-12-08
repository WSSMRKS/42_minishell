/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:16:49 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:20:13 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Converts an integer to a string and appends it to the output string.
/// @param num The integer to convert.
/// @param base The base to use for the conversion.
/// @param out The output string.
/// @warning Check the error flag for memory allocation errors.
static void	_str_itoa_recursive(uint32_t num, t_str_slice base, t_str *out)
{
	if (num >= base.len)
		_str_itoa_recursive(num / base.len, base, out);
	str_push(out, base.str[num % base.len]);
}

static void	_str_itoa(int32_t num, t_str_slice base, t_str *out)
{
	if (num == INT32_MIN)
		str_pushstr(out, cstr_slice("-2147483648", 11));
	else if (num < 0)
	{
		str_push(out, '-');
		_str_itoa_recursive(-num, base, out);
	}
	else
		_str_itoa_recursive(num, base, out);
}

/// @brief Converts an integer to a string and appends it to the output string.
/// @param num The integer to convert.
/// @param base The base to use for the conversion.
/// @param out The output string.
/// @warning Check the error flag for memory allocation errors.
void	str_itoa_cat(int32_t num, t_str_slice base, t_str *out)
{
	_str_itoa(num, base, out);
}

/// @brief Converts an integer to a string.
/// @param num The integer to convert.
/// @param base The base to use for the conversion.
/// @return The string representation of the integer.
/// @warning Check the error flag for memory allocation errors.
t_str	str_itoa(int32_t num, t_str_slice base)
{
	t_str	out;

	out = str_empty();
	_str_itoa(num, base, &out);
	return (out);
}

/// @brief Inserts the string representation of an integer into another string.
/// @param num The integer to convert.
/// @param base The base to use for the conversion.
/// @param out The output string.
/// @param at The index to insert the string at.
/// @warning Check the error flag for memory allocation errors.
bool	str_insert_itoa(int num, t_str_slice base, t_str *out, size_t at)
{
	t_str	str;

	str = str_itoa(num, base);
	if (str.mem_err)
		out->mem_err = true;
	str_insertstr(out, at, str_view(&str));
	str_destroy(&str);
	return (out->mem_err);
}
