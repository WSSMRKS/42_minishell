/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pnb_b_fd_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:35:58 by maweiss           #+#    #+#             */
/*   Updated: 2024/03/06 11:51:34 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_check(char *str)
{
	int	strlen;
	int	i;
	int	j;

	i = 0;
	strlen = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' || str[i] == '+' )
			return (-1);
		j = 0;
		while (str[j] != '\0')
		{
			if (str[j] == str[i] && i != j && str[i] != 0)
				return (-1);
			j++;
		}
		strlen++;
		str++;
	}
	if (strlen <= 1)
		return (-1);
	return (strlen);
}

static unsigned int	ft_neg(int nbr, int fd, int negp)
{
	unsigned int	u_inp;

	if (nbr < 0 && negp == 1)
	{
		u_inp = nbr * -1;
		ft_putchar_fd_ret('-', fd);
	}
	else
		u_inp = (unsigned int) nbr;
	return (u_inp);
}

static int	ft_power(unsigned int nbr, int b_len)
{
	int	power;

	power = 0;
	while (nbr >= (unsigned int) b_len)
	{
		nbr /= b_len;
		power++;
	}
	return (power);
}

static int	ft_ret(int nbr, int u_inp, int b_len)
{
	if (nbr != u_inp)
		return (ft_power(u_inp, b_len) + 2);
	else
		return (ft_power(u_inp, b_len) + 1);
}

int	ft_pnb_b_fd_s(int nbr, char *base, int fd, int negp)
{
	int				b_len;
	int				power;
	unsigned int	tmp;
	int				div_count;
	unsigned int	u_inp;

	b_len = 0;
	b_len = ft_strlen_check(base);
	if (b_len < 0)
		return (-1);
	u_inp = ft_neg(nbr, fd, negp);
	power = ft_power(u_inp, b_len);
	while (power >= 0)
	{
		div_count = power;
		tmp = u_inp;
		while (div_count > 0)
		{
			tmp /= b_len;
			div_count--;
		}
		ft_putchar_fd_ret(base[tmp % b_len], fd);
		power--;
	}
	return (ft_ret(nbr, u_inp, b_len));
}

// int	main(void)
// {
// 	printf("%d", ft_itoa_base_fd(4294967295, "0123456789"));
// }
