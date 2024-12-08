/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:23:28 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:43 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(uint32_t, char))
{
	char		*out;
	uint32_t	i;

	out = malloc(ft_strlen(s) + 1);
	if (!out)
		return (0);
	i = 0;
	while (*s)
	{
		out[i] = f(i, *s++);
		i++;
	}
	out[i] = '\0';
	return (out);
}
