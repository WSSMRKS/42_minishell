/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:51:35 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/20 18:52:09 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int32_t	ft_printf_fd(int32_t fd, const char *s, ...)
{
	va_list	args;
	int32_t	total_put_width;
	int32_t	put_width;

	va_start(args, s);
	total_put_width = 0;
	while (s && *s)
	{
		if (*s != '%')
		{
			if (write(fd, s, 1) != 1)
				break ;
			total_put_width++;
			s++;
			continue ;
		}
		put_width = print_formatted_arg((const char **)&s, &args, fd);
		if (put_width == -1)
			return (return_with_va_end(-1, &args));
		total_put_width += put_width;
	}
	va_end(args);
	if (!s || *s)
		return (-1);
	return (total_put_width);
}
