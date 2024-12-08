/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:15:52 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:42 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	out;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (src_len + size);
	out = src_len + dest_len;
	while (dest_len < size - 1 && *src)
		dst[dest_len++] = *src++;
	dst[dest_len] = '\0';
	return (out);
}
