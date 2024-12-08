/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:12:51 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stdlib.h>

char	**ft_split_recursion(const char *s, char c, int32_t i, size_t len)
{
	char	**out;
	char	*str;

	if (!s)
		return (malloc((i + 1) * sizeof(char *)));
	while (s[len] && s[len] != c)
		len++;
	str = ft_substr(s, 0, len);
	if (str == 0)
		return (0);
	s = s + len;
	while (*s && *s == c)
		s++;
	if (!*s)
		s = 0;
	out = ft_split_recursion(s, c, i + 1, 0);
	if (!out)
	{
		free(str);
		return (0);
	}
	if (!s)
		out[i + 1] = 0;
	out[i] = str;
	return (out);
}

char	**ft_split(const char *s, char c)
{
	char	**out;

	while (*s && *s == c)
		s++;
	if (*s)
		return (ft_split_recursion(s, c, 0, 0));
	out = malloc(sizeof(char *));
	if (out)
		*out = 0;
	return (out);
}
