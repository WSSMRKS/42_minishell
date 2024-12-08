/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfill_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 01:14:15 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:41:59 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putfill_fd(char c, int32_t fd, size_t fill)
{
	ssize_t	put_len;

	put_len = 0;
	while (fill--)
	{
		if (write(fd, &c, 1) < 0)
			return (-1);
		put_len++;
	}
	return (put_len);
}
