/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:26:16 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:43:35 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - 32);
	else
		return (c);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_toupper(','));
	printf("%d\n", ft_toupper('a'));
	printf("%d\n", ft_toupper('7'));
	printf("%d\n", ft_toupper('A'));
	printf("%d\n", ft_toupper('0'));
	printf("%d\n", toupper(','));
	printf("%d\n", toupper('a'));
	printf("%d\n", toupper('z'));
	printf("%d\n", toupper('A'));
	printf("%d\n", toupper('Z'));
	printf("%d\n", toupper('7'));
}
*/
