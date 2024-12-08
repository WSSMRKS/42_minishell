/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:21:30 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:25:32 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <fcntl.h>

bool	ft_rand(uint8_t *bytes, size_t n)
{
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (false);
	if (read(fd, bytes, n) < 0)
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
