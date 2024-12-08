/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:57:49 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 16:54:00 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_point	point_constrain(t_point point, t_rect constraint)
{
	t_point	out;

	out.x = i32min(i32max(point.x, constraint.from.x), constraint.to.x);
	out.y = i32min(i32max(point.y, constraint.from.y), constraint.to.y);
	return (out);
}

t_point	point_mult(t_point point, size_t factor)
{
	t_point	out;

	out.x = point.x * factor;
	out.y = point.y * factor;
	return (out);
}

t_point	point_div(t_point point, size_t factor)
{
	t_point	out;

	out.x = point.x / factor;
	out.y = point.y / factor;
	return (out);
}
