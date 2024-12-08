/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:27:33 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

/// @brief Might add leading zeroes to the number string.
/// @param str The string consisting only of the number.
/// @param fmt The format struct.
/// @param has_sign Whether the number has a sign.
void	add_precision_leading_zeroes(t_str *str, t_fmt fmt, bool has_sign)
{
	int32_t	num_len;
	size_t	insert_index;

	num_len = str->len;
	insert_index = 0;
	if (has_sign)
	{
		num_len--;
		insert_index++;
	}
	if (fmt.precision > num_len)
		str_insertn(str, insert_index, '0', fmt.precision - num_len);
}

/// @brief Swaps the sign with the leading zero.
/// @param str The string.
/// @param fmt The format struct.
/// @param is_neg Whether the number is negative.
void	swap_sign_with_leading_zero(t_str *str, t_fmt fmt, bool is_neg)
{
	char	*sign;
	char	*buf_sign;
	char	*buf;

	if (!is_neg)
		sign = fmt.pos_nbr_sign;
	else
		sign = "-";
	if (!*sign)
		return ;
	buf = cstr_mut(str);
	buf_sign = ft_strchr(buf, *sign);
	if (buf_sign)
		*buf_sign = '0';
	buf[0] = *sign;
}

t_str	fmt_int(va_list *args, t_fmt fmt)
{
	t_str	out;
	int32_t	num;

	num = va_arg(*args, int32_t);
	out = str_empty();
	str_itoa_cat(num, base10(), &out);
	if (!(num == 0 && fmt.precision == 0))
	{
		if (num >= 0)
			str_pushstr_front(&out, cstr_view(fmt.pos_nbr_sign));
		add_precision_leading_zeroes(&out, fmt, num < 0
			|| *fmt.pos_nbr_sign != 0);
	}
	add_padding(&out, fmt, true);
	if (fmt.precision < 0 && fmt.pad.fill_char == '0' && !fmt.pad.pad_end)
		swap_sign_with_leading_zero(&out, fmt, num < 0);
	return (out);
}
