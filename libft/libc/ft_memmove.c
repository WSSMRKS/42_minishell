/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:06:11 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/18 14:29:15 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	uint8_t			*dest8;
	const uint8_t	*src8;
	size_t			i;

	if (n == 0 || !dest || !src || dest == src)
		return (dest);
	dest8 = (uint8_t *)dest;
	src8 = (const uint8_t *)src;
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			dest8[i] = src8[i];
			i++;
		}
		return (dest);
	}
	else
		while (n--)
			dest8[n] = src8[n];
	return (dest);
}
