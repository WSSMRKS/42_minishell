/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:32:59 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:33:21 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_point	point(int32_t x, int32_t y)
{
	return ((t_point){x, y});
}

t_point	point_add(t_point point, t_point offset)
{
	t_point	out;

	out.x = point.x + offset.x;
	out.y = point.y + offset.y;
	return (out);
}

t_point	point_sub(t_point point, t_point offset)
{
	t_point	out;

	out.x = point.x - offset.x;
	out.y = point.y - offset.y;
	return (out);
}

t_point	point_min(t_point var1, t_point var2)
{
	t_point	out;

	out.x = i32min(var1.x, var2.x);
	out.y = i32min(var1.y, var2.y);
	return (out);
}

t_point	point_max(t_point var1, t_point var2)
{
	t_point	out;

	out.x = i32max(var1.x, var2.x);
	out.y = i32max(var1.y, var2.y);
	return (out);
}
