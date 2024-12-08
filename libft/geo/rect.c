/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:27:52 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 03:37:13 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_rect	rect(uint32_t width, uint32_t height)
{
	return ((t_rect){.from = {0, 0}, .to = {width, height},
		.size = {width, height}});
}

t_rect	rect_at(t_point origin, uint32_t width, uint32_t height)
{
	t_rect	rect;

	rect.from = origin;
	rect.to = point(origin.x + width, origin.y + height);
	rect.width = width;
	rect.height = height;
	return (rect);
}

t_rect	rect_from(t_point var1, t_point var2)
{
	t_rect	rect;

	rect.from = point_min(var1, var2);
	rect.to = point_max(var1, var2);
	rect.width = rect.to.x - rect.from.x;
	rect.height = rect.to.y - rect.from.y;
	return (rect);
}

t_rect	rect_center_in(t_rect outer, uint32_t width, uint32_t height)
{
	return (
		rect_center_at(
			point_add(outer.from, point(outer.width / 2, outer.height / 2)),
			width, height
		)
	);
}

t_rect	rect_center_at(t_point center, uint32_t width, uint32_t height)
{
	return (
		rect_at(
			point_sub(center, point(width / 2, height / 2)),
			width, height
		)
	);
}
