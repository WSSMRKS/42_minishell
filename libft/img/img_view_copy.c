/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgview_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:32 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 17:01:57 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"

uint32_t	*imgview_pixel(t_imgview img, t_upoint pt)
{
	return (&img.img->px[(img.from.y + pt.y) * img.img->width
			+ img.from.x + pt.x]);
}

uint32_t	*imgview_lane(t_imgview img, uint32_t y)
{
	return (&img.img->px[(img.from.y + y) * img.img->width + img.from.x]);
}

void	imgview_fill(t_imgview img, uint32_t color)
{
	uint32_t	y;

	if (img.height == img.img->height && img.width == img.img->width)
		ft_memset32(img.img->px, color, img.img->px_len);
	else
	{
		y = 0;
		while (y < img.height)
			ft_memset32(imgview_lane(img, y++), color, img.width);
	}
}

void	imgview_copy(t_imgview src, t_imgview dest)
{
	uint32_t	y;

	src.urect = urect_at(src.from, u32min(src.width, dest.width),
			u32min(src.height, dest.height));
	y = 0;
	while (y < src.height)
	{
		ft_memcpy(imgview_lane(dest, y), imgview_lane(src, y),
			src.width * sizeof(uint32_t));
		y++;
	}
}

void	imgview_copy_scaled(t_imgview src, t_imgview dest, size_t scale)
{
	t_upoint	pt;
	uint32_t	src_px;

	dest.urect = urect_at(dest.from, u32min(dest.width, src.width * scale),
			u32min(dest.height, src.height * scale));
	pt.y = 0;
	while (pt.y < dest.height)
	{
		pt.x = 0;
		while (pt.x < dest.width)
		{
			src_px = *imgview_pixel(src, upoint_div(pt, scale));
			*imgview_pixel(dest, pt) = src_px;
			pt.x++;
		}
		pt.y++;
	}
}
