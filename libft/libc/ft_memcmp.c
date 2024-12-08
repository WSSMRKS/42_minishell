/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:32:56 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/30 09:33:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int32_t	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*buf1 = s1;
	const unsigned char	*buf2 = s2;

	while (n-- > 0)
	{
		if (*buf1++ != *buf2++)
		{
			if (buf1[-1] < buf2[-1])
				return (-1);
			else
				return (1);
		}
	}
	return (0);
}
