/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:08:56 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:42 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdlib.h>

/**
 * Concatenates two strings.
 *
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return The new string.
 *         NULL if the allocation fails.
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*out;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	out = malloc(s1_len + s2_len + 1);
	if (!out)
		return (0);
	ft_memcpy(out, s1, s1_len);
	ft_memcpy(out + s1_len, s2, s2_len);
	out[s1_len + s2_len] = 0;
	return (out);
}
