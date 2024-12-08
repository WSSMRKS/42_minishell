/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:00:27 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:21:55 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int32_t	get_and_skip_sign(const char **nptr)
{
	if (**nptr == '-')
	{
		(*nptr)++;
		return (-1);
	}
	if (**nptr == '+')
		(*nptr)++;
	return (1);
}

int32_t	ft_atoi(const char *nptr)
{
	int32_t	sign;
	int32_t	nbr;

	while (ft_isspace(*nptr))
		nptr++;
	sign = get_and_skip_sign(&nptr);
	nbr = 0;
	while (ft_isdigit(*nptr))
	{
		if (nbr > INT32_MAX / 10 || (nbr == INT32_MAX / 10 && *nptr > '7'))
		{
			if (sign == -1)
				return (INT32_MIN);
			return (INT32_MAX);
		}
		nbr = (nbr * 10) + *nptr - '0';
		nptr++;
	}
	return (sign * nbr);
}
