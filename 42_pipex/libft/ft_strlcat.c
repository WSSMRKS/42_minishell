/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:20:41 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:42:57 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*tmp;
	size_t	lensrc;
	size_t	lendst;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	tmp = dst;
	if (size < lendst)
		return (lensrc + size);
	while (*tmp && size > 0)
	{
		tmp++;
		size--;
	}
	while (*src && size > 1)
	{
		*tmp = *src;
		src++;
		tmp++;
		size--;
	}
	if (size > 0)
		*tmp = '\0';
	return (lendst + lensrc);
}

/*
#include <string.h>
#include <bsd/string.h>


int	main(void)
{
	static char	*src1 = "1234567890\0/123456789";
	char		dst1[50];
	static char	*src2 = "1234567890\0/123456789";
	char		dst2[50];

	dst1[0] = 'a';
	dst1[1] = 'b';
	dst1[2] = 'c';
	dst1[3] = 'd';
	dst1[4] = 'e';
	dst1[5] = 'f';
	dst1[6] = '\0';
	// dst1[0] = '\0';
	dst2[0] = 'a';
	dst2[1] = 'b';
	dst2[2] = 'c';
	dst2[3] = 'd';
	dst2[4] = 'e';
	dst2[5] = 'f';
	dst2[6] = '\0';

	// dst2[0] = '\0';
	printf("%s\n", src1);
	printf("%s\n", dst1);
	printf("%zu\n", ft_strlcat(dst1, src1, 18));
	printf("%s\n", dst1);
	printf("-------------------------\n");
	printf("%s\n", src2);
	printf("%s\n", dst2);
	printf("%zu\n", strlcat(dst2, src2, 18));
	printf("%s\n", dst2);
}
*/
