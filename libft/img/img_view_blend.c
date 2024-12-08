/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgview_blend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:17:30 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 17:35:05 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"

void	imgview_blend(t_imgview src, t_imgview dest)
{
	t_upoint	pt;
	uint32_t	src_px;
	uint32_t	*dest_px;

	src.urect = urect_at(src.from, u32min(src.width, dest.width),
			u32min(src.height, dest.height));
	pt.y = 0;
	while (pt.y < src.height)
	{
		pt.x = 0;
		while (pt.x < src.width)
		{
			src_px = *imgview_pixel(src, pt);
			dest_px = imgview_pixel(dest, pt);
			*dest_px = blend_colors(*dest_px, src_px);
			pt.x++;
		}
		pt.y++;
	}
}

void	imgview_blend_scaled(t_imgview src, t_imgview dest, size_t scale)
{
	t_upoint	pt;
	uint32_t	src_px;
	uint32_t	*dest_px;

	dest.urect = urect_at(dest.from, u32min(dest.width, src.width * scale),
			u32min(dest.height, src.height * scale));
	pt.y = 0;
	while (pt.y < dest.height)
	{
		pt.x = 0;
		while (pt.x < dest.width)
		{
			src_px = *imgview_pixel(src, upoint_div(pt, scale));
			dest_px = imgview_pixel(dest, pt);
			*dest_px = blend_colors(*dest_px, src_px);
			pt.x++;
		}
		pt.y++;
	}
}
