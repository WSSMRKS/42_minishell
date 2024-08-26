/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:25:26 by maweiss           #+#    #+#             */
/*   Updated: 2024/02/27 14:30:59 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_core(const char *str)
{
	long	i;
	long	digits;
	long	nb;

	i = 1;
	digits = 1;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digits *= 10;
		i++;
	}
	i = 0;
	while (digits > 0)
	{
		nb = nb + (str[i] - '0') * digits;
		digits /= 10;
		i++;
	}
	return (nb);
}

long	ft_atol(const char *nptr)
{
	long		sign;

	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\v' || *nptr == '\r'
		|| *nptr == '\n' || *nptr == '\f')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr == '0' && *(nptr + 1) == '0')
		nptr++;
	if (*nptr >= '0' && *nptr <= '9')
		return (ft_core(nptr) * sign);
	else
		return (0);
}

/*
able to handle long !!
*/
