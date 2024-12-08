/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 04:05:45 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_img.h"
#include <stdlib.h>

bool	img_alloc(t_img *img, uint32_t width, uint32_t height, bool zero)
{
	size_t	alloc;

	img->px = 0;
	if (!(usizemult(width, height, &img->px_len)
			&& usizemult(img->px_len, sizeof(uint32_t), &alloc)))
		return (false);
	img->px = malloc(alloc);
	if (img->px == 0)
		return (false);
	if (zero)
		ft_bzero(img->px, alloc);
	img->urect = urect(width, height);
	return (true);
}

bool	img_malloc(t_img *img, uint32_t width, uint32_t height)
{
	return (img_alloc(img, width, height, false));
}

bool	img_calloc(t_img *img, uint32_t width, uint32_t height)
{
	return (img_alloc(img, width, height, true));
}

bool	img_clone(t_imgview src, t_img *out)
{
	if (!img_malloc(out, src.width, src.height))
		return (false);
	imgview_copy(src, imgview(out));
	return (true);
}

t_img	img(uint32_t *px, uint32_t width, uint32_t height)
{
	return ((t_img){.px = px, .urect = urect(width, height),
		.px_len = width * height});
}
