/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:01:56 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 16:44:21 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/// @brief Copies `n` bytes from src to dest. (Forward-copy)
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	uint8_t			*dest8;
	const uint8_t	*src8;
	size_t			i;

	if (dest == src || !dest || !src || n == 0)
		return (dest);
	dest8 = (uint8_t *)dest;
	src8 = (const uint8_t *)src;
	i = 0;
	while (i < n)
	{
		dest8[i] = src8[i];
		i++;
	}
	return (dest);
}
