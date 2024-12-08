/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:38:35 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:44:17 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putnbr_fd(int32_t n, int32_t fd)
{
	long	n_long;
	ssize_t	out_width;
	ssize_t	tmp;

	n_long = n;
	out_width = 0;
	if (n_long < 0)
	{
		if (write(fd, "-", 1) < 0)
			return (-1);
		out_width++;
		n_long *= -1;
	}
	if (n_long >= 10)
	{
		tmp = ft_putnbr_fd(n_long / 10, fd);
		if (tmp < 0)
			return (-1);
		out_width += tmp;
	}
	tmp = ft_putchar_fd('0' + (n_long % 10), fd);
	if (tmp < 0)
		return (-1);
	return (out_width + tmp);
}
