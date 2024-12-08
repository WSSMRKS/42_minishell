/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_finish.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:36:46 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/18 16:40:22 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_next_line_finish(int32_t fd)
{
	_get_next_line(fd, true);
}

bool	get_next_line2(int32_t fd, char **out)
{
	char	*line;

	line = _get_next_line(fd, false);
	if (!line && out)
		*out = 0;
	else
		*out = line;
	if (!out)
		free(line);
	return (line != 0);
}
