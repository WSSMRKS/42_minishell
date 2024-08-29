/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:26:16 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:41:46 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (' ' <= c && c <= '~')
		return (c);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_isprint(','));
	printf("%d\n", ft_isprint('a'));
	printf("%d\n", ft_isprint('7'));
	printf("%d\n", ft_isprint('A'));
	printf("%d\n", ft_isprint('0'));
	printf("%d\n", ft_isprint(31));
	printf("%d\n", ft_isprint(127));
	printf("%d\n", ft_isprint('0'));
	printf("%d\n", isprint(','));
	printf("%d\n", isprint('a'));
	printf("%d\n", isprint('z'));
	printf("%d\n", isprint('A'));
	printf("%d\n", isprint('Z'));
	printf("%d\n", isprint('7'));
	printf("%d\n", isprint(127));
	printf("%d\n", isprint(31));
	printf("%d\n", isprint(127));
}
*/
