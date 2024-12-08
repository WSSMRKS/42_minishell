/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   urect2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:26:13 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 03:26:56 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

t_urect	urect_add(t_urect urect, t_upoint offset)
{
	return (
		urect_from(
			upoint_add(urect.from, offset),
			upoint_add(urect.to, offset)
		)
	);
}

t_urect	urect_sub(t_urect urect, t_upoint offset)
{
	return (
		urect_from(
			upoint_sub(urect.from, offset),
			upoint_sub(urect.to, offset)
		)
	);
}

t_urect	urect_constrain(t_urect urect, t_urect constraint)
{
	return (
		urect_from(
			upoint_constrain(urect.from, constraint),
			upoint_constrain(urect.to, constraint)
		)
	);
}

t_urect	rect_unsign(t_rect rect)
{
	return (urect_from(point_unsign(rect.from), point_unsign(rect.to)));
}

t_urect	rect_as_urect(t_rect rect)
{
	return ((t_urect){.rect = rect});
}
