/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:45:21 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:42 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*out;

	len = ft_strlen(s) + 1;
	out = malloc(len);
	if (out)
		ft_memcpy(out, s, len);
	return (out);
}

char	*ft_strndup(const char *s, size_t len)
{
	char	*out;

	out = malloc(len + 1);
	if (out)
		ft_memcpy(out, s, len + 1);
	return (out);
}
