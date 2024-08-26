/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:17:42 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:41:50 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_special(int *nb, int *digits)
{
	int		tmp;
	char	*buff;

	tmp = *nb;
	if (*nb < 0)
	{
		while (tmp <= -10)
		{
			tmp /= 10;
			(*digits)++;
		}
		buff = malloc(*digits + 2);
	}
	if (*nb >= 0)
	{
		while (tmp >= 10)
		{
			tmp /= 10;
			(*digits)++;
		}
		buff = malloc(*digits + 1);
	}
	return (buff);
}

char	*ft_itoa(int nb)
{
	char	*buff;
	int		digits;
	int		i;

	digits = 1;
	buff = ft_special(&nb, &digits);
	if (!buff)
		return (NULL);
	i = digits;
	if (nb < 0)
	{
		buff[0] = '-';
		i += 1;
	}
	buff[i--] = 0;
	while (digits > 0)
	{
		if (nb >= 0)
			buff[i--] = '0' + nb % 10;
		if (nb < 0)
			buff[i--] = '0' + -1 * (nb % 10);
		nb /= 10;
		digits--;
	}
	return (buff);
}

/*
int	main(void)
{
	int		nb;
	char	*string;

	nb = -2147483648;
	string = ft_itoa(nb);
	printf("Number: %d\n", nb);
	printf("String: %s\n", string);
	nb = 2147483647;
	string = ft_itoa(nb);
	printf("Number: %d\n", nb);
	printf("String: %s\n", string);
	nb = -1;
	string = ft_itoa(nb);
	printf("Number: %d\n", nb);
	printf("String: %s\n", string);
	nb = 1;
	string = ft_itoa(nb);
	printf("Number: %d\n", nb);
	printf("String: %s\n", string);
	nb = 0;
	string = ft_itoa(nb);
	printf("Number: %d\n", nb);
	printf("String: %s\n", string);
	nb = 105060;
	string = ft_itoa(nb);
	printf("Number: %d\n", nb);
	printf("String: %s\n", string);
	nb = -105060;
	string = ft_itoa(nb);
	printf("Number: %d\n", nb);
	printf("String: %s\n", string);
	nb = 1580698;
	string = ft_itoa(nb);
	printf("Number: %d\n", nb);
	printf("String: %s\n", string);
}
*/
