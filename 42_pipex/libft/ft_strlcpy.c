/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:20:41 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:43:00 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char	*tmp;
	size_t	lensrc;
	size_t	i;

	lensrc = ft_strlen(src);
	tmp = dst;
	i = 0;
	if (size == 0)
		return (lensrc);
	if (lensrc == 0 && size > 0)
	{
		*dst = '\0';
		return (lensrc);
	}
	while (i < size - 1 && *src)
	{
		tmp[i] = *src;
		src++;
		i++;
	}
	tmp[i] = '\0';
	return (lensrc);
}

/*
int	main(void)
{
	static char	*src = "1234567890123456789012345678901234567890";
	char		dst[50];

	dst[0] = 'a';
	dst[1] = 'b';
	dst[2] = '\0';
	printf("%s\n", src);
	printf("%s\n", dst);
	printf("%zu\n", ft_strlcpy(dst, src, 10));
	printf("%s\n", dst);
}
*/
