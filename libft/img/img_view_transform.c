/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgview_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:16:58 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 18:50:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"

/// @brief Mirrors the image horizontally (left-right).
/// @param img The image to flip.
void	imgview_flip_h(t_imgview img)
{
	t_upoint	pt;
	uint32_t	tmp;
	uint32_t	x;

	pt.y = 0;
	while (pt.y < img.height)
	{
		pt.x = 0;
		while (pt.x < img.width / 2)
		{
			x = img.width - pt.x - 1;
			tmp = *imgview_pixel(img, pt);
			*imgview_pixel(img, pt) = *imgview_pixel(img, upoint(x, pt.y));
			*imgview_pixel(img, upoint(x, pt.y)) = tmp;
			pt.x++;
		}
		pt.y++;
	}
}

/// @brief Mirrors the image vertically (up-down).
/// @param img The image to flip.
void	imgview_flip_v(t_imgview img)
{
	t_upoint	pt;
	uint32_t	tmp;
	uint32_t	y;

	pt.x = 0;
	while (pt.x < img.width)
	{
		pt.y = 0;
		while (pt.y < img.height / 2)
		{
			y = img.height - pt.y - 1;
			tmp = *imgview_pixel(img, pt);
			*imgview_pixel(img, pt) = *imgview_pixel(img, upoint(pt.x, y));
			*imgview_pixel(img, upoint(pt.x, y)) = tmp;
			pt.y++;
		}
		pt.x++;
	}
}

void	imgview_rotate90(t_imgview src, t_imgview dest)
{
	t_upoint	pt;

	src.urect = urect_at(src.from, u32min(src.width, dest.height),
			u32min(src.height, dest.width));
	pt.y = 0;
	while (pt.y < src.height)
	{
		pt.x = 0;
		while (pt.x < src.width)
		{
			*imgview_pixel(dest,
				upoint(pt.y, src.width - pt.x - 1)
				) = *imgview_pixel(src, pt);
			pt.x++;
		}
		pt.y++;
	}
}

void	imgview_rotate180(t_imgview src, t_imgview dest)
{
	t_upoint	pt;

	pt.y = 0;
	while (pt.y < src.height)
	{
		pt.x = 0;
		while (pt.x < src.width)
		{
			*imgview_pixel(dest,
				upoint(src.width - pt.x - 1, src.height - pt.y - 1)
				) = *imgview_pixel(src, pt);
			pt.x++;
		}
		pt.y++;
	}
}

void	imgview_rotate270(t_imgview src, t_imgview dest)
{
	t_upoint	pt;

	src.urect = urect_at(src.from, u32min(src.width, dest.height),
			u32min(src.height, dest.width));
	pt.y = 0;
	while (pt.y < src.height)
	{
		pt.x = 0;
		while (pt.x < src.width)
		{
			*imgview_pixel(dest,
				upoint(src.height - pt.y - 1, pt.x)
				) = *imgview_pixel(src, pt);
			pt.x++;
		}
		pt.y++;
	}
}
