/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:30:05 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# pragma once

# include "../libft.h"
# include <stdarg.h>

typedef enum e_flag_kind
{
	FLAG_PAD_END = '-',
	FLAG_SIGN_PLUS = '+',
	FLAG_SIGN_SPACE = ' ',
	FLAG_ALT = '#',
	FLAG_PAD_ZERO = '0',
}				t_flag_kind;

typedef struct s_padding
{
	char		fill_char;
	size_t		min_width;
	bool		pad_end;
}				t_padding;

typedef struct s_spec
{
	const char	*spec_str;
	int32_t		fmt_fn_index;
}				t_spec;

typedef struct s_fmt
{
	bool		bad_fmt;
	bool		malloc_err;
	t_spec		specifier;
	bool		alternate_form;
	char		*pos_nbr_sign;
	t_padding	pad;
	int32_t		precision;
}				t_fmt;

typedef t_str	(*t_fmt_fn)(va_list *, t_fmt);

int32_t			ft_printf(const char *s, ...);

int32_t			ft_printf_fd(int32_t fd, const char *s, ...);

int32_t			print_formatted_arg(const char **fmt_begin, va_list *arg,
					int32_t fd);
int32_t			return_with_va_end(int32_t code, va_list *args);

t_str			fmt_c(va_list *args, t_fmt fmt);
t_str			fmt_str(va_list *args, t_fmt fmt);
t_str			fmt_ptr(va_list *args, t_fmt fmt);
t_str			fmt_int(va_list *args, t_fmt fmt);
t_str			fmt_uint(va_list *args, t_fmt fmt);
t_str			fmt_hex(va_list *args, t_fmt fmt);
t_str			fmt_hexup(va_list *args, t_fmt fmt);
t_str			percent_char(va_list *args, t_fmt fmt);

void			init_fmt(t_fmt *fmt);
void			parse_formatting(const char *s, t_fmt *fmt);
void			add_padding(t_str *str, t_fmt fmt, bool allow_zero);

void			add_precision_leading_zeroes(t_str *str, t_fmt fmt,
					bool has_sign);
void			swap_sign_with_leading_zero(t_str *str, t_fmt fmt,
					bool is_neg);
void			ulltoa_base_radix(t_str *out, unsigned long long num,
					const char *base, size_t radix);
void			sanitize_fmt_unsigned(t_fmt *fmt);

#endif
