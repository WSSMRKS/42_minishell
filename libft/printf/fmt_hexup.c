/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:46:11 by kwurster          #+#    #+#             */
/*   Updated: 2024/01/01 20:00:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	add_padding_hex(t_str *str, t_fmt fmt, bool allow_zero,
		uint32_t num)
{
	if (str->len >= fmt.pad.min_width)
		return ;
	if (!allow_zero)
		fmt.pad.fill_char = ' ';
	if (fmt.precision != -1)
		fmt.pad.fill_char = ' ';
	if (fmt.pad.pad_end)
		str_pushn(str, ' ', fmt.pad.min_width - str->len);
	else
	{
		if (fmt.pad.fill_char == '0' && num != 0 && fmt.alternate_form)
			cstr_mut(str)[1] = '0';
		str_pushn_front(str, fmt.pad.fill_char, fmt.pad.min_width - str->len);
		if (fmt.pad.fill_char == '0' && num != 0 && fmt.alternate_form)
			cstr_mut(str)[1] = 'X';
	}
}

t_str	fmt_hexup(va_list *args, t_fmt fmt)
{
	t_str		out;
	uint32_t	num;

	num = va_arg(*args, uint32_t);
	out = str_empty();
	sanitize_fmt_unsigned(&fmt);
	ulltoa_base_radix(&out, num, "0123456789ABCDEF", 16);
	add_precision_leading_zeroes(&out, fmt, false);
	if (num != 0 && fmt.alternate_form)
		str_pushstr_front(&out, cstr_slice("0X", 2));
	add_padding_hex(&out, fmt, true, num);
	return (out);
}
