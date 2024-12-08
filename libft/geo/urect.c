/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   urect.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:55 by kwurster          #+#    #+#             */
/*   Updated: 2024/07/29 14:11:25 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_urect	urect(uint32_t width, uint32_t height)
{
	return ((t_urect){{.from = {{0, 0}}, .to = {{width, height}},
			.width = width, .height = height}});
}

t_urect	urect_at(t_upoint origin, uint32_t width, uint32_t height)
{
	t_urect	rect;

	rect.from = origin;
	rect.to = upoint(origin.x + width, origin.y + height);
	rect.width = width;
	rect.height = height;
	return (rect);
}

t_urect	urect_from(t_upoint var1, t_upoint var2)
{
	t_urect		rect;

	rect.from = upoint_min(var1, var2);
	rect.to = upoint_max(var1, var2);
	rect.width = rect.to.x - rect.from.x;
	rect.height = rect.to.y - rect.from.y;
	return (rect);
}

t_urect	urect_center_in(t_urect outer, uint32_t width, uint32_t height)
{
	return (
		urect_center_at(
			upoint_add(outer.from, upoint(outer.width / 2, outer.height / 2)),
			width, height
		)
	);
}

t_urect	urect_center_at(t_upoint center, uint32_t width, uint32_t height)
{
	return (
		urect_at(
			upoint_sub(center, upoint(width / 2, height / 2)),
			width, height
		)
	);
}
