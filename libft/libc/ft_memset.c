/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:24:42 by kwurster          #+#    #+#             */
/*   Updated: 2024/07/29 14:03:44 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

uint64_t	*ft_memset64(uint64_t *dest, uint64_t src, size_t n)
{
	size_t	i;

	if (!dest || !n)
		return (0);
	i = 0;
	while (i < n)
		dest[i++] = src;
	return (dest);
}

uint32_t	*ft_memset32(uint32_t *dest, uint32_t src, size_t n)
{
	size_t	i;

	if (!dest || !n)
		return (0);
	i = 0;
	while (i < n)
		dest[i++] = src;
	return (dest);
}

uint16_t	*ft_memset16(uint16_t *dest, uint16_t src, size_t n)
{
	size_t	i;

	if (!dest || !n)
		return (0);
	i = 0;
	while (i < n)
		dest[i++] = src;
	return (dest);
}

void	*ft_memset(void *dest, uint8_t src, size_t n)
{
	uint8_t	*dest8;
	size_t	i;

	if (!dest || !n)
		return (0);
	i = 0;
	dest8 = dest;
	while (i < n)
		dest8[i++] = src;
	return (dest);
}
