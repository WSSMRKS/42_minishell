/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:34:39 by zblume            #+#    #+#             */
/*   Updated: 2024/06/21 14:44:06 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

size_t	ft_gnl_strlen_line(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_line(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_gnl_strlen_line(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_line(char *trim, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!trim)
	{
		trim = (char *)malloc(1 * sizeof(char));
		trim[0] = '\0';
	}
	if (!trim || !buff)
		return (NULL);
	str = malloc(sizeof(char) * (
				(ft_gnl_strlen_line(trim) + ft_gnl_strlen_line(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (trim)
		while (trim[++i] != '\0')
			str[i] = trim[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_gnl_strlen_line(trim) + ft_gnl_strlen_line(buff)] = '\0';
	clean_pointer(&trim);
	return (str);
}

void	clean_pointer(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
