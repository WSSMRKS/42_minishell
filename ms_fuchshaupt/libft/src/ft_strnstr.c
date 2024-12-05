/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:49:51 by zblume            #+#    #+#             */
/*   Updated: 2024/06/21 13:59:44 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	char		*b;

	b = (char *)big;
	i = 0;
	if (little[0] == '\0')
		return (b);
	while (b[i] && i < len)
	{
		j = 0;
		while (b[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return (&b[i]);
			j++;
		}
		i++;
	}
	return (0);
}
