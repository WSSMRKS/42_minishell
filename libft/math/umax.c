/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   umax.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:29:52 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/27 22:33:26 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

uint8_t	u8max(uint8_t var1, uint8_t var2)
{
	if (var1 > var2)
		return (var1);
	return (var2);
}

uint16_t	u16max(uint16_t var1, uint16_t var2)
{
	if (var1 > var2)
		return (var1);
	return (var2);
}

uint32_t	u32max(uint32_t var1, uint32_t var2)
{
	if (var1 > var2)
		return (var1);
	return (var2);
}

uint64_t	u64max(uint64_t var1, uint64_t var2)
{
	if (var1 > var2)
		return (var1);
	return (var2);
}

size_t	usizemax(size_t var1, size_t var2)
{
	if (var1 > var2)
		return (var1);
	return (var2);
}
