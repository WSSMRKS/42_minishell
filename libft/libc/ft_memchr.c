/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:20:49 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:05 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int32_t c, size_t n)
{
	const char	*buf;
	size_t		i;

	buf = s;
	i = 0;
	while (i < n && buf[i] != (char)c)
		i++;
	if (i == n)
		return (0);
	return ((void *)&buf[i]);
}
