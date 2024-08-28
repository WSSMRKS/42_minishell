/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:20:38 by maweiss           #+#    #+#             */
/*   Updated: 2024/06/14 16:35:16 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	*ft_ovfh(size_t nmemb, size_t size, size_t *res)
{
	*res = nmemb * size;
	if (nmemb != 0 && *res / nmemb != size)
		return (NULL);
	else
		return (res);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;
	size_t	res;

	i = 0;
	if (!ft_ovfh(nmemb, size, &res))
		return (NULL);
	else
	{
		str = malloc(res);
		if (!str)
			return (NULL);
	}
	while (i < res)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

/*
int	main(void)
{
	int				*arr;
	unsigned char	*d;
	int				i;

	i = 0;
	arr = ft_calloc(5, 1);
	d = (unsigned char *)arr;
	while (i < 20)
	{
		printf("%02x\n", *d);
		d++;
		i++;
	}
	free(arr);
}
*/