/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:53:06 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:41:22 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	char			*tmp;
	unsigned long	a;
	char			c;

	c = '\0';
	a = 0;
	tmp = s;
	while (a < n)
	{
		*tmp = c;
		a++;
		tmp++;
	}
	return (s);
}

/*
#include <unistd.h>

char	ft_hexchar(int ch)
{
	char	c;

	if (ch == 10)
		c = 'a';
	if (ch == 11)
		c = 'b';
	if (ch == 12)
		c = 'c';
	if (ch == 13)
		c = 'd';
	if (ch == 14)
		c = 'e';
	if (ch == 15)
		c = 'f';
	return (c);
}

int	ft_asciin(char *str)
{
	int		ch;
	char	inp;

	inp = *str;
	ch = (int) inp;
	if (ch < 0)
		ch *= -1;
	return (ch);
}

void	ft_hex(int ch, char *hex)
{
	int	tmp;

	*hex = '\\';
	tmp = ch;
	ch /= 16;
	hex++;
	if (9 >= ch)
		*hex = '0' + ch;
	if (10 <= ch && ch <= 15)
		*hex = ft_hexchar(ch);
	ch = tmp;
	ch %= 16;
	hex++;
	if (9 >= ch)
		*hex = '0' + ch;
	if (10 <= ch && ch <= 15)
		*hex = ft_hexchar(ch);
}

void	ft_putstr_non_printable(char *str, size_t n)
{
	int					ch;
	char				hex[3];
	unsigned long		i;

	i = 0;
	while (i < n)
	{
		if (*str <= 31 || *str == 127)
		{
			ch = ft_asciin(str);
			ft_hex(ch, hex);
			write(1, hex, 3);
		}
		else
			write(1, str, 1);
		str++;
		i++;
	}
}

#include <strings.h>

int	main(void)
{
	char	arr1[45];
	int		arr2[10];
	char	*a;
	char	*b;

	a = (char *) ft_bzero(arr1, 45);
	b = (char *) ft_bzero(arr2, 45);

	ft_putstr_non_printable(a, 45);
	write(1, "\n----------\n", 12);
	ft_putstr_non_printable(b, 45);
	// printf("%s\n", (char *)ft_bzero(arr1, 40));
	// printf("%s\n", (char *) ft_bzero(arr2, 50));
	// printf("%s\n", (char *) bzero(arr1, 30));
	// printf("%s\n", (char *) bzero(arr2, 30));
}
*/
