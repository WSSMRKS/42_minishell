/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:43:49 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:41:56 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0 && *(unsigned char *)s1 == *(unsigned char *)s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0 )
	{
		if (*(unsigned char *)s1 == *(unsigned char *)s2)
		{
			s1++;
			s2++;
			n--;
		}
		else
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
	if (n == 0)
		return (0);
	return (0);
}


int	main(void)
{
	int	bla[] = {112, 12, 122, 11, 12};
	int	bla2[] = {112, 12, 122, 11, 11};

	printf("%d\n", ft_memcmp(bla, bla2, 16));
	printf("----------------------------\n");
	printf("%d\n", memcmp(bla, bla2, 16));
}
*/
