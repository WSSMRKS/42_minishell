/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upoint2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:42:25 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 16:53:20 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_upoint	upoint_constrain(t_upoint point, t_urect constraint)
{
	t_upoint	out;

	out.x = u32min(u32max(point.x, constraint.from.x), constraint.to.x);
	out.y = u32min(u32max(point.y, constraint.from.y), constraint.to.y);
	return (out);
}

t_upoint	point_unsign(t_point point)
{
	t_upoint	out;

	if (point.x < 0)
		out.x = 0;
	else
		out.x = point.x;
	if (point.y < 0)
		out.y = 0;
	else
		out.y = point.y;
	return (out);
}

t_upoint	point_as_upoint(t_point point)
{
	return ((t_upoint){.point = point});
}

t_upoint	upoint_mult(t_upoint point, size_t factor)
{
	t_upoint	out;

	out.x = point.x * factor;
	out.y = point.y * factor;
	return (out);
}

t_upoint	upoint_div(t_upoint point, size_t factor)
{
	t_upoint	out;

	out.x = point.x / factor;
	out.y = point.y / factor;
	return (out);
}
