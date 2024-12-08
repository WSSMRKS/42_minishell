/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   umult.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:50:16 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

bool	u8mult(uint8_t var1, uint8_t var2, uint8_t *out)
{
	*out = var1 * var2;
	if (var1 == 0 || var2 == 0)
		return (true);
	return (var1 == *out / var2);
}

bool	u16mult(uint16_t var1, uint16_t var2, uint16_t *out)
{
	*out = var1 * var2;
	if (var1 == 0 || var2 == 0)
		return (true);
	return (var1 == *out / var2);
}

bool	u32mult(uint32_t var1, uint32_t var2, uint32_t *out)
{
	*out = var1 * var2;
	if (var1 == 0 || var2 == 0)
		return (true);
	return (var1 == *out / var2);
}

bool	u64mult(uint64_t var1, uint64_t var2, uint64_t *out)
{
	*out = var1 * var2;
	if (*out == 0)
		return (true);
	return (var1 == *out / var2);
}

bool	usizemult(size_t var1, size_t var2, size_t *out)
{
	*out = var1 * var2;
	if (var1 == 0 || var2 == 0)
		return (true);
	return (var1 == *out / var2);
}
