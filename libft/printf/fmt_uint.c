/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_uint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 07:39:56 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	sanitize_fmt_unsigned(t_fmt *fmt)
{
	fmt->pos_nbr_sign = "";
}

static void	ulltoa_base_radix_inner(t_str *out, unsigned long long num,
		const char *base, size_t radix)
{
	if (num == 0)
		return ;
	ulltoa_base_radix_inner(out, num / radix, base, radix);
	str_push(out, base[num % radix]);
}

void	ulltoa_base_radix(t_str *out, unsigned long long num, const char *base,
		size_t radix)
{
	if (num == 0)
		str_push(out, '0');
	else
		ulltoa_base_radix_inner(out, num, base, radix);
}

t_str	fmt_uint(va_list *args, t_fmt fmt)
{
	t_str		out;
	uint32_t	num;

	num = va_arg(*args, uint32_t);
	out = str_empty();
	sanitize_fmt_unsigned(&fmt);
	ulltoa_base_radix(&out, num, "0123456789", 10);
	if (!(num == 0 && fmt.precision == 0))
	{
		add_precision_leading_zeroes(&out, fmt, false);
		str_pushstr_front(&out, cstr_view(fmt.pos_nbr_sign));
	}
	add_padding(&out, fmt, true);
	if (fmt.precision < 0 && fmt.pad.fill_char == '0' && !fmt.pad.pad_end)
		swap_sign_with_leading_zero(&out, fmt, false);
	return (out);
}
