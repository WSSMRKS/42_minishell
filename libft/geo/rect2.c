/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 03:01:55 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 03:16:40 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_rect	rect_add(t_rect rect, t_point offset)
{
	t_rect	out;

	out.from.x = rect.from.x + offset.x;
	out.from.y = rect.from.y + offset.y;
	out.to.x = rect.to.x + offset.x;
	out.to.y = rect.to.y + offset.y;
	return (out);
}

t_rect	rect_sub(t_rect rect, t_point offset)
{
	t_rect	out;

	out.from.x = rect.from.x - offset.x;
	out.from.y = rect.from.y - offset.y;
	out.to.x = rect.to.x - offset.x;
	out.to.y = rect.to.y - offset.y;
	return (out);
}

t_rect	rect_constrain(t_rect rect, t_rect constraint)
{
	return (
		rect_from(
			point_constrain(rect.from, constraint),
			point_constrain(rect.to, constraint)
		)
	);
}
