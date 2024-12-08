/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upoint_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:39:37 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

bool	upoint_lt(t_upoint pt, t_upoint other)
{
	return (pt.x < other.x && pt.y < other.y);
}

bool	upoint_gt(t_upoint pt, t_upoint other)
{
	return (pt.x > other.x && pt.y > other.y);
}

bool	upoint_eq(t_upoint pt, t_upoint other)
{
	return (pt.x == other.x && pt.y == other.y);
}

bool	upoint_gte(t_upoint pt, t_upoint other)
{
	return (pt.x >= other.x && pt.y >= other.y);
}

bool	upoint_lte(t_upoint pt, t_upoint other)
{
	return (pt.x <= other.x && pt.y <= other.y);
}
