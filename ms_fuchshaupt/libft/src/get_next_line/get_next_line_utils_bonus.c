/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:34:39 by zblume            #+#    #+#             */
/*   Updated: 2024/06/29 14:13:59 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line_bonus.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[gnl_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_gnl_strjoin(char *trim, char *buff)
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
	str = malloc(sizeof(char) * ((gnl_strlen(trim) + gnl_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (trim)
		while (trim[++i] != '\0')
			str[i] = trim[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[gnl_strlen(trim) + gnl_strlen(buff)] = '\0';
	clean_pointer(&trim);
	return (str);
}

void	clean_pointer(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
