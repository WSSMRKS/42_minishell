/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multistrjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wssmrks <wssmrks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:48:44 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/08 17:23:52 by wssmrks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "stdarg.h"
#include "stdlib.h"

/*join as many strings as needed.
res = ft_multistrjoin(int nb_strings, char const *s1, s2, sn, ...)
*/
char	*ft_multistrjoin(int nb_strings, char const *s1, ...)
{
	va_list	args;
	char	*res;
	char	*tmp;
	char	*free_me;
	int		i;

	i = 0;
	if (nb_strings < 1)
		return (NULL);
	res = ft_strdup((char *) s1);
	if (nb_strings == 1 || !res)
		return (res);
	va_start(args, s1);
	while (i++ < nb_strings -1)
	{
		tmp = va_arg(args, char *);
		free_me = res;
		res = ft_strjoin(res, tmp);
		free(free_me);
		if (!res)
			break ;
	}
	va_end(args);
	return (res);
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
