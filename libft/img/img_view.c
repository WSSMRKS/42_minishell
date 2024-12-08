/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgview.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:03:20 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 16:09:48 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"

t_imgview	imgview(const t_img *img)
{
	t_imgview	view;

	view.img = img;
	view.urect = img->urect;
	return (view);
}

t_imgview	imgview_urect(const t_img *img, t_urect urect)
{
	t_imgview	view;

	view.img = img;
	view.urect = urect_constrain(urect, img->urect);
	return (view);
}

t_imgview	imgview_at(const t_img *img, t_upoint origin,
				uint32_t width, uint32_t height)
{
	t_imgview	view;

	view.img = img;
	view.urect = urect_constrain(urect_at(origin, width, height), img->urect);
	return (view);
}

t_imgview	imgview_from(const t_img *img, t_upoint var1, t_upoint var2)
{
	t_imgview	view;

	view.img = img;
	view.urect = urect_constrain(urect_from(var1, var2), img->urect);
	return (view);
}

t_imgview	imgview_center(const t_img *img, uint32_t width, uint32_t height)
{
	t_imgview	view;

	view.img = img;
	view.urect = urect_constrain(urect_center_in(img->urect, width, height),
			img->urect);
	return (view);
}
