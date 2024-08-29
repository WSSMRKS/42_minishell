/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:04:41 by maweiss           #+#    #+#             */
/*   Updated: 2024/06/12 11:57:37 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_init(int *count, int *i, const char *s)
{
	char	type;

	if (s == 0)
		*count = -1;
	else
		*count = 0;
	*i = 0;
	type = 0;
	return (type);
}

static int	ft_p(long tmp, int fd)
{
	int	count;

	count = 0;
	if (tmp == 0)
		count += ft_putstr_fd_ret("(nil)", fd);
	else
	{
		count += ft_putstr_fd_ret("0x", fd);
		count += ft_pnb_b_fd(tmp, "0123456789abcdef", fd, 0);
	}
	return (count);
}

static long	ft_core(char type, va_list ar, int *count, int fd)
{
	long	tmp;

	if (type == 'c')
		*count += ft_putchar_fd_ret(va_arg(ar, int), fd);
	else if (type == 's')
		*count += ft_putstr_fd_ret(va_arg(ar, char *), fd);
	else if (type == 'd' || type == 'i')
		*count += ft_pnb_b_fd((long) va_arg(ar, int), "0123456789", fd, 1);
	else if (type == 'u')
		*count += ft_pnb_b_fd((long) va_arg(ar, unsigned int),
				"0123456789", fd, 1);
	else if (type == 'p')
	{
		tmp = va_arg(ar, long);
		*count += ft_p(tmp, fd);
	}
	else if (type == 'x')
	{
		*count += ft_pnb_b_fd_s(va_arg(ar, int), "0123456789abcdef", fd, 0);
	}
	else if (type == 'X')
		*count += ft_pnb_b_fd_s(va_arg(ar, int), "0123456789ABCDEF", fd, 0);
	else
		*count += ft_putchar_fd_ret('%', fd);
	return (1);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	va_list	args;
	int		count;
	int		i;
	char	type;

	type = ft_init(&count, &i, s);
	va_start(args, s);
	while (s != 0 && s[i])
	{
		if (s[i] == '%')
		{
			type = s[i + 1];
			if (type == '\0')
				return (-1);
			if (type == '%')
				count += ft_putchar_fd_ret('%', fd);
			if (type != '\0' && type != '%')
				ft_core(type, args, &count, fd);
			i += 2;
		}
		else
			count += ft_putchar_fd_ret(s[i++], fd);
	}
	va_end(args);
	return (count);
}
