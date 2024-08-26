/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:26:16 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:43:28 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_tolower(','));
	printf("%d\n", ft_tolower('a'));
	printf("%d\n", ft_tolower('z'));
	printf("%d\n", ft_tolower('A'));
	printf("%d\n", ft_tolower('Z'));
	printf("%d\n", ft_tolower('7'));
	printf("---------------------\n");
	printf("%d\n", tolower(','));
	printf("%d\n", tolower('a'));
	printf("%d\n", tolower('z'));
	printf("%d\n", tolower('A'));
	printf("%d\n", tolower('Z'));
	printf("%d\n", tolower('7'));
}
*/
