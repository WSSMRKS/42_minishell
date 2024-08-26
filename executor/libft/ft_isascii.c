/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:26:16 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:41:39 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (100 + c);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_isascii(','));
	printf("%d\n", ft_isascii('a'));
	printf("%d\n", ft_isascii('7'));
	printf("%d\n", ft_isascii('A'));
	printf("%d\n", ft_isascii('0'));
	printf("%d\n", ft_isascii(128));
	printf("%d\n", ft_isascii(127));
	printf("%d\n", ft_isascii(-1));
	printf("%d\n", isascii(','));
	printf("%d\n", isascii('a'));
	printf("%d\n", isascii('z'));
	printf("%d\n", isascii('A'));
	printf("%d\n", isascii('Z'));
	printf("%d\n", isascii('7'));
	printf("%d\n", isascii(128));
	printf("%d\n", isascii(127));
	printf("%d\n", isascii(-1));
}
*/
