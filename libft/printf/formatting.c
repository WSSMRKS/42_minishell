/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:34:31 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_fmt(t_fmt *fmt)
{
	*fmt = (t_fmt){0};
	fmt->specifier.fmt_fn_index = -1;
	fmt->pad.fill_char = ' ';
	fmt->pos_nbr_sign = "";
	fmt->precision = -1;
}

static void	parse_flags(const char **s, t_fmt *fmt)
{
	while (**s && *s != fmt->specifier.spec_str)
	{
		if (**s == FLAG_PAD_END)
			fmt->pad.pad_end = true;
		else if (**s == FLAG_SIGN_PLUS)
			fmt->pos_nbr_sign = "+";
		else if (**s == FLAG_SIGN_SPACE && *fmt->pos_nbr_sign == 0)
			fmt->pos_nbr_sign = " ";
		else if (**s == FLAG_ALT)
			fmt->alternate_form = true;
		else if (**s == FLAG_PAD_ZERO)
			fmt->pad.fill_char = '0';
		else
			break ;
		(*s)++;
	}
}

void	parse_formatting(const char *s, t_fmt *fmt)
{
	parse_flags(&s, fmt);
	fmt->pad.min_width = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
	{
		fmt->precision = ft_atoi(++s);
		while (ft_isdigit(*s))
			s++;
	}
	if (s != fmt->specifier.spec_str)
		fmt->bad_fmt = true;
}

void	add_padding(t_str *str, t_fmt fmt, bool allow_zero)
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
		str_pushn_front(str, fmt.pad.fill_char, fmt.pad.min_width - str->len);
}
