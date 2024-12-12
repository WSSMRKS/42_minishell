/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgview_transform2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:48:59 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 18:50:47 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"

static void	rotate_middle_lane(t_imgview img)
{
	t_upoint	pt;
	t_upoint	pt_tmp;
	uint32_t	tmp;
	uint32_t	tmp2;

	pt = upoint(0, (img.height / 2) - 1);
	while (++pt.x < img.width / 2)
	{
		tmp = *imgview_pixel(img, pt);
		pt_tmp = upoint(img.width - pt.x - 1, pt.y);
		tmp2 = *imgview_pixel(img, pt_tmp);
		*imgview_pixel(img, pt) = tmp2;
		*imgview_pixel(img, pt_tmp) = tmp;
	}
}

void	imgview_rotate180_inplace(t_imgview img)
{
	t_upoint	pt;
	t_upoint	pt_tmp;
	uint32_t	tmp;
	uint32_t	tmp2;

	pt.y = 0;
	while (pt.y < img.height / 2)
	{
		pt.x = 0;
		while (pt.x < img.width)
		{
			tmp = *imgview_pixel(img, pt);
			pt_tmp = upoint(img.width - pt.x - 1, img.height - pt.y - 1);
			tmp2 = *imgview_pixel(img, pt_tmp);
			*imgview_pixel(img, pt) = tmp2;
			*imgview_pixel(img, pt_tmp) = tmp;
			pt.x++;
		}
		pt.y++;
	}
	if (img.height % 2 != 0)
		rotate_middle_lane(img);
}
