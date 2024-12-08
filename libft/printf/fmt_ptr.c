/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:39:17 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	add_padding_hex(t_str *str, t_fmt fmt, bool allow_zero)
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
		if (fmt.pad.fill_char == '0')
			cstr_mut(str)[1] = '0';
		str_pushn_front(str, fmt.pad.fill_char, fmt.pad.min_width - str->len);
		if (fmt.pad.fill_char == '0')
			cstr_mut(str)[1] = 'x';
	}
}

t_str	fmt_ptr(va_list *args, t_fmt fmt)
{
	t_str	out;
	void	*ptr;

	ptr = va_arg(*args, void *);
	if (!ptr)
	{
		out = str_clone_from(cstr_slice("(nil)", 5));
		add_padding(&out, fmt, false);
	}
	else
	{
		out = str_clone_from(cstr_slice("0x", 2));
		ulltoa_base_radix(&out, (unsigned long long)ptr, "0123456789abcdef",
			16);
		add_padding_hex(&out, fmt, true);
	}
	return (out);
}
