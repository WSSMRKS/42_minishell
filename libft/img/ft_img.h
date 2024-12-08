/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 03:44:30 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IMG_H
# define FT_IMG_H
# pragma once

# include "../libft.h"

# define TRANSPARENT 0xFF

t_img		img(uint32_t *px, uint32_t width, uint32_t height);
bool		img_alloc(t_img *img, uint32_t width, uint32_t height, bool zero);
bool		img_malloc(t_img *img, uint32_t width, uint32_t height);
bool		img_calloc(t_img *img, uint32_t width, uint32_t height);
bool		img_clone(t_imgview src, t_img *out);
void		img_destroy(t_img *img);

t_imgview	imgview(const t_img *img);
t_imgview	imgview_urect(const t_img *img, t_urect urect);
t_imgview	imgview_at(const t_img *img, t_upoint origin,
				uint32_t width, uint32_t height);
t_imgview	imgview_from(const t_img *img, t_upoint var1, t_upoint var2);
t_imgview	imgview_center(const t_img *img, uint32_t width, uint32_t height);

uint32_t	*imgview_pixel(t_imgview img, t_upoint pt);
uint32_t	*imgview_lane(t_imgview img, uint32_t y);
void		imgview_fill(t_imgview img, uint32_t color);
void		imgview_copy(t_imgview src, t_imgview dest);
void		imgview_copy_scaled(t_imgview src, t_imgview dest, size_t scale);
void		imgview_blend(t_imgview src, t_imgview dest);
void		imgview_blend_scaled(t_imgview src, t_imgview dest, size_t scale);

void		imgview_draw_border(t_imgview img, uint32_t color,
				uint32_t thickness);

void		imgview_flip_v(t_imgview img);
void		imgview_flip_h(t_imgview img);
void		imgview_rotate90(t_imgview src, t_imgview dest);
void		imgview_rotate180(t_imgview src, t_imgview dest);
void		imgview_rotate270(t_imgview src, t_imgview dest);
void		imgview_rotate180_inplace(t_imgview img);

bool		is_transparent(uint32_t color);
bool		is_opaque(uint32_t color);
uint32_t	blend_colors(uint32_t bg, uint32_t color);

#endif
