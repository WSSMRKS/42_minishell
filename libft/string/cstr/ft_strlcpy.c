/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:13:38 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:42 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

/**
 * Copies a string from source to destination, up to a given size.
 *
 * @param dst The destination string.
 * @param src The source string.
 * @param size The size of the destination buffer (including null terminator).
 * @return The total length of the source string.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	if (!size)
		return (ft_strlen(src));
	src_len = 0;
	while (size-- > 1 && src[src_len])
		*dst++ = src[src_len++];
	while (src[src_len])
		src_len++;
	*dst = '\0';
	return (src_len);
}
