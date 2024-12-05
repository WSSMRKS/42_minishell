/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:34:37 by zblume            #+#    #+#             */
/*   Updated: 2024/06/21 14:44:06 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

char	*ft_get_line(char *trim)
{
	int		i;
	char	*str;

	i = 0;
	if (!trim[i])
		return (NULL);
	while (trim[i] && trim[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (trim[i] && trim[i] != '\n')
	{
		str[i] = trim[i];
		i++;
	}
	if (trim[i] == '\n')
	{
		str[i] = trim[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_trim(char *trim)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (trim[i] && trim[i] != '\n')
		i++;
	if (!trim[i])
	{
		clean_pointer(&trim);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_gnl_strlen_line(trim) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (trim[i])
		str[j++] = trim[i++];
	str[j] = '\0';
	clean_pointer(&trim);
	return (str);
}

char	*ft_read_to_trim(int fd, char *trim)
{
	char	*buff;
	int		size;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	size = 1;
	while (!ft_strchr_line(trim, '\n') && size != 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
		{
			clean_pointer(&buff);
			return (NULL);
		}
		buff[size] = '\0';
		trim = ft_strjoin_line(trim, buff);
	}
	clean_pointer(&buff);
	return (trim);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*trim;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd >= __FD_SETSIZE)
		return (0);
	trim = ft_read_to_trim(fd, trim);
	if (!trim)
		return (NULL);
	line = ft_get_line(trim);
	trim = ft_new_trim(trim);
	return (line);
}
