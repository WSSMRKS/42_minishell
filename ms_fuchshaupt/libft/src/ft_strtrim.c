/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:23:17 by zblume            #+#    #+#             */
/*   Updated: 2024/06/21 13:59:44 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s;
	int		e;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	s = 0;
	e = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[s]) && s <= e)
		s++;
	if (s > e)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[e]) && e >= 0)
		e--;
	str = (char *)malloc(e - s + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[s], e - s + 2);
	return (str);
}
