/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:26:16 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:41:34 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (c);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_isalpha(','));
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", ft_isalpha('7'));
	printf("%d\n", ft_isalpha('A'));
	printf("%d\n", ft_isalpha('0'));
	printf("%d\n", isalpha(','));
	printf("%d\n", isalpha('a'));
	printf("%d\n", isalpha('z'));
	printf("%d\n", isalpha('A'));
	printf("%d\n", isalpha('Z'));
	printf("%d\n", isalpha('7'));
}
*/
