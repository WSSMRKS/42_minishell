/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:08:17 by maweiss           #+#    #+#             */
/*   Updated: 2024/03/06 15:18:23 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

/*
int	main(void)
{
	printf("123456789aldfkgj;sldfkjglsdkj");
	printf("\n");
	printf("%s\n", ft_strchr("123456789aldfkgj;sldfkjglsdkj", 0));
	printf("123456789aldfkgj;sldfkjglsdkj");
	printf("\n");
	printf("%s\n", strchr("123456789aldfkgj;sldfkjglsdkj", 0));
}
*/
