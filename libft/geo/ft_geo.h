/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_geo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:07:15 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GEO_H
# define FT_GEO_H
# pragma once

# include "../libft.h"

t_upoint	upoint(uint32_t x, uint32_t y);
t_upoint	upoint_add(t_upoint point, t_upoint offset);
t_upoint	upoint_sub(t_upoint point, t_upoint offset);
t_upoint	upoint_min(t_upoint var1, t_upoint var2);
t_upoint	upoint_max(t_upoint var1, t_upoint var2);

bool		upoint_lt(t_upoint pt, t_upoint other);
bool		upoint_gt(t_upoint pt, t_upoint other);
bool		upoint_eq(t_upoint pt, t_upoint other);
bool		upoint_lte(t_upoint pt, t_upoint other);
bool		upoint_gte(t_upoint pt, t_upoint other);

t_upoint	upoint_constrain(t_upoint point, t_urect constraint);
t_upoint	upoint_mult(t_upoint point, size_t factor);
t_upoint	upoint_div(t_upoint point, size_t factor);

t_upoint	point_unsign(t_point point);
t_upoint	point_as_upoint(t_point point);
t_point		point(int32_t x, int32_t y);
t_point		point_add(t_point point, t_point offset);
t_point		point_sub(t_point point, t_point offset);
t_point		point_min(t_point var1, t_point var2);
t_point		point_max(t_point var1, t_point var2);

t_point		point_constrain(t_point point, t_rect constraint);
t_point		point_mult(t_point point, size_t factor);
t_point		point_div(t_point point, size_t factor);

bool		point_is_pos(t_point point);

t_urect		urect(uint32_t width, uint32_t height);
t_urect		urect_at(t_upoint origin, uint32_t width, uint32_t height);
t_urect		urect_from(t_upoint var1, t_upoint var2);
t_urect		urect_center_in(t_urect outer, uint32_t width, uint32_t height);
t_urect		urect_center_at(t_upoint center, uint32_t width, uint32_t height);

t_urect		urect_add(t_urect urect, t_upoint offset);
t_urect		urect_sub(t_urect urect, t_upoint offset);
t_urect		urect_constrain(t_urect urect, t_urect constraint);

bool		urect_contains(t_urect urect, t_upoint point);

t_urect		rect_unsign(t_rect rect);
t_urect		rect_as_urect(t_rect rect);
t_rect		rect(uint32_t width, uint32_t height);
t_rect		rect_at(t_point origin, uint32_t width, uint32_t height);
t_rect		rect_from(t_point var1, t_point var2);
t_rect		rect_center_in(t_rect outer, uint32_t width, uint32_t height);
t_rect		rect_center_at(t_point center, uint32_t width, uint32_t height);

t_rect		rect_add(t_rect rect, t_point offset);
t_rect		rect_sub(t_rect rect, t_point offset);
t_rect		rect_constrain(t_rect rect, t_rect constraint);

bool		rect_contains(t_rect rect, t_point point);

t_size		size(uint32_t width, uint32_t height);

#endif
