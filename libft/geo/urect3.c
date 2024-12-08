/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   urect3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:21:19 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_geo.h"

bool	urect_contains(t_urect urect, t_upoint point)
{
	return (
		point.x >= urect.from.x && point.x < urect.to.x
		&& point.y >= urect.from.y && point.y < urect.to.y
	);
}
