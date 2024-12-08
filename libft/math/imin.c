/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:34:47 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/27 22:36:47 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int8_t	i8min(int8_t var1, int8_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}

int16_t	i16min(int16_t var1, int16_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}

int32_t	i32min(int32_t var1, int32_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}

int64_t	i64min(int64_t var1, int64_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}

ssize_t	isizemin(ssize_t var1, ssize_t var2)
{
	if (var1 < var2)
		return (var1);
	return (var2);
}
