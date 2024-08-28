/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:26:16 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:41:30 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
		|| ('0' <= c && c <= '9'))
		return (c);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_isalnum(','));
	printf("%d\n", ft_isalnum('a'));
	printf("%d\n", ft_isalnum('7'));
	printf("%d\n", ft_isalnum('A'));
	printf("%d\n", ft_isalnum('0'));
	printf("%d\n", isalnum(','));
	printf("%d\n", isalnum('a'));
	printf("%d\n", isalnum('z'));
	printf("%d\n", isalnum('A'));
	printf("%d\n", isalnum('Z'));
	printf("%d\n", isalnum('7'));
}
*/
