/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iabs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:57:37 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/27 22:40:36 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int8_t	i8abs(int8_t num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int16_t	i16abs(int16_t num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int32_t	i32abs(int32_t num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int64_t	i64abs(int64_t num)
{
	if (num < 0)
		return (-num);
	return (num);
}

ssize_t	isizeabs(ssize_t num)
{
	if (num < 0)
		return (-num);
	return (num);
}
