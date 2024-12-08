/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:47:40 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:44 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdlib.h>

static int32_t	set_contains(const char *set, char c)
{
	while (*set)
		if (*set++ == (char)c)
			return (1);
	return (0);
}

/**
 * Removes leading and trailing characters from a string
 * based on a given set of characters.
 *
 * @param s1 The string to be trimmed.
 * @param set The set of characters to be removed.
 * @return A newly allocated trimmed string, or NULL if memory allocation fails.
 */
char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	char	*out;

	while (set_contains(set, *s1))
		s1++;
	len = 0;
	while (s1[len])
		len++;
	while (len && set_contains(set, s1[len - 1]))
		len--;
	out = malloc(len + 1);
	if (!out)
		return (0);
	out[len] = 0;
	ft_memcpy(out, s1, len);
	return (out);
}
