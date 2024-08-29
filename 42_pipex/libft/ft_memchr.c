/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:48:45 by maweiss           #+#    #+#             */
/*   Updated: 2024/06/12 11:36:04 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(char *)s == (char)c)
			return ((void *)s);
		s++;
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	printf("0123456789aldfkgj;sldfkjgzlsdkj");
	printf("\n");
	printf("%s\n", (char *)ft_memchr("0s", 'z', 26));
	printf("0123456789aldfkgj;sldfkjgzlsdkj");
	printf("\n");
	printf("%s\n", (char *)memchr("0123456789aldfkgj;sldfkjgzlsdkj", 'z', 26));
}
*/
