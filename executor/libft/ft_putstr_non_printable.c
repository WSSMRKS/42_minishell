/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:49:04 by maweiss           #+#    #+#             */
/*   Updated: 2023/11/07 16:49:17 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
