/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:48:44 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:42:54 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*res;
	char	*tmp1;
	char	*tmp2;

	len = 0;
	tmp1 = (char *)s1;
	while (*s1++)
		len++;
	tmp2 = (char *)s2;
	while (*s2++)
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (*tmp1)
		*res++ = *tmp1++;
	while (*tmp2)
		*res++ = *tmp2++;
	*res = '\0';
	return (&res[-len]);
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

int	main(void)
{
	static char	*s1 = "copy me";
	static char	*s2 = "copy me as well";
	char		*str;

	str = ft_strjoin(s1, s2);

	ft_putstr_non_printable(str, 23);
}
*/
