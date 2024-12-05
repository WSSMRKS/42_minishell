/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:58:52 by zblume            #+#    #+#             */
/*   Updated: 2024/06/21 14:23:57 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

static int	params(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_ret_putchar(va_arg(args, int));
	else if (c == 'd' || c == 'i')
		len += ft_ret_putnbr(va_arg(args, int));
	else if (c == 's')
		len += ft_ret_putstr(va_arg(args, char *));
	else if (c == 'p')
		len += ft_putptr(va_arg(args, void *));
	else if (c == 'x')
		len += ft_hex_convert(va_arg(args, unsigned int), 2);
	else if (c == 'X')
		len += ft_hex_convert(va_arg(args, unsigned int), 1);
	else if (c == 'u')
		len += ft_ret_putunsigned(va_arg(args, unsigned int));
	else if (c == '%')
		len += ft_ret_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += params(str[i + 1], args);
			i = i + 2;
			if (!str[i])
				break ;
		}
		else
			len += ft_ret_putchar(str[i++]);
	}
	va_end(args);
	return (len);
}
