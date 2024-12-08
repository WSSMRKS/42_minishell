/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:21:44 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"

bool	is_transparent(uint32_t color)
{
	return (color >> 24 == TRANSPARENT);
}

bool	is_opaque(uint32_t color)
{
	return (color >> 24 != TRANSPARENT);
}

uint32_t	blend_colors(uint32_t bg, uint32_t color)
{
	uint8_t		alpha;
	uint32_t	mask;

	alpha = color >> 24;
	mask = ~((alpha == TRANSPARENT) - 1);
	return ((bg & mask) | (color & ~mask));
}
