/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:36:55 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:41:27 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putendl_fd(const char *s, int32_t fd)
{
	ssize_t	out_width;

	out_width = ft_putstr_fd(s, fd);
	if (out_width < 0)
		return (out_width);
	if (write(fd, "\n", 1) < 0)
		return (-1);
	return (out_width + 1);
}
