/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upoint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:35:43 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 03:38:35 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_upoint	upoint(uint32_t x, uint32_t y)
{
	return ((t_upoint){{x, y}});
}

t_upoint	upoint_add(t_upoint point, t_upoint offset)
{
	t_upoint	out;

	out.x = point.x + offset.x;
	out.y = point.y + offset.y;
	return (out);
}

t_upoint	upoint_sub(t_upoint point, t_upoint offset)
{
	t_upoint	out;

	if (offset.x > point.x)
		out.x = 0;
	else
		out.x = point.x - offset.x;
	if (offset.y > point.y)
		out.y = 0;
	else
		out.y = point.y - offset.y;
	return (out);
}

t_upoint	upoint_min(t_upoint var1, t_upoint var2)
{
	t_upoint	out;

	out.x = u32min(var1.x, var2.x);
	out.y = u32min(var1.y, var2.y);
	return (out);
}

t_upoint	upoint_max(t_upoint var1, t_upoint var2)
{
	t_upoint	out;

	out.x = u32max(var1.x, var2.x);
	out.y = u32max(var1.y, var2.y);
	return (out);
}
