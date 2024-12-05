/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:23:05 by zblume            #+#    #+#             */
/*   Updated: 2024/06/21 13:59:44 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	while (c > 127)
		c -= 128;
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return ((char *)&str[i]);
		i++;
	}
	if (c == str[i])
		return ((char *)&str[i]);
	return (NULL);
}
