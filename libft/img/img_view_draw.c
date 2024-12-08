/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgview_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:14:45 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 17:46:37 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"

void	imgview_draw_border(t_imgview img, uint32_t color, uint32_t thickness)
{
	imgview_fill(imgview_at(img.img, img.from, img.width, thickness), color);
	imgview_fill(imgview_at(img.img, img.from, thickness, img.height), color);
	if (img.to.y >= thickness)
		imgview_fill(imgview_at(img.img,
				upoint(img.from.x, img.to.y - thickness),
				img.width, thickness), color);
	else
		imgview_fill(imgview_at(img.img,
				upoint(img.from.x, 0),
				img.width, thickness), color);
	if (img.to.x >= thickness)
		imgview_fill(imgview_at(img.img,
				upoint(img.to.x - thickness, img.from.y),
				thickness, img.height), color);
	else
		imgview_fill(imgview_at(img.img,
				upoint(0, img.from.y),
				thickness, img.height), color);
}
