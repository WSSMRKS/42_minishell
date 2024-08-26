/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:33:03 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:42:13 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_special(int *nb, char *buff, int fd)
{
	if (*nb == -2147483648)
	{
		write(fd, "-2", 2);
		*nb = 147483648;
	}
	if (*nb < 0)
	{
		*nb = -*nb;
		write(fd, "-", 1);
	}
	if (*nb == 0)
	{
		buff[0] = '0';
		buff[1] = '\0';
		return ;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buff[11];
	int		tmp;
	int		digits;
	int		i;

	ft_special(&n, buff, fd);
	tmp = n;
	digits = 1;
	while (tmp >= 10)
	{
		tmp /= 10;
		digits++;
	}
	i = digits - 1;
	while (n > 0)
	{
		buff[i] = '0' + n % 10;
		n /= 10;
		i--;
	}
	write(fd, buff, digits);
}

/*
int	main(void)
{
	ft_putnbr_fd(-21354654, 1);
}
*/
