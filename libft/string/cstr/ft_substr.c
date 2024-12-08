/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:30:54 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:44 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdlib.h>

/**
 * Creates a substring from the given string.
 *
 * @param s The string from which to create the substring.
 * @param start The start index of the substring in the string 's'.
 * @param len The maximum length of the substring.
 * @return The substring.
 *         NULL if the allocation fails.
 */
char	*ft_substr(const char *s, uint32_t start, size_t len)
{
	char	*out;
	size_t	s_len;

	while (start && *s)
	{
		s++;
		start--;
	}
	s_len = 0;
	while (s[s_len] && s_len < len)
		s_len++;
	out = malloc(s_len + 1);
	if (!out)
		return (0);
	out[s_len] = '\0';
	ft_memcpy(out, s, s_len);
	return (out);
}
