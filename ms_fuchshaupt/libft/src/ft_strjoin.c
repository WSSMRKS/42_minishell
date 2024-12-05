/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:52:18 by zblume            #+#    #+#             */
/*   Updated: 2024/10/31 12:16:12 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*create_ret(const char *s, size_t len)
{
	char	*ret;

	ret = malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len);
	return (ret);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (create_ret(s2, ft_strlen(s2) + 1));
	if (!s2)
		return (create_ret(s1, ft_strlen(s1) + 1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
	ft_strlcat(ret, s2, len);
	return (ret);
}
