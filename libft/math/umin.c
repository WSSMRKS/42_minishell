/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   umin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:57:38 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/27 22:37:02 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

uint8_t	u8min(uint8_t var1, uint8_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}

uint16_t	u16min(uint16_t var1, uint16_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}

uint32_t	u32min(uint32_t var1, uint32_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}

uint64_t	u64min(uint64_t var1, uint64_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}

size_t	usizemin(size_t var1, size_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}
