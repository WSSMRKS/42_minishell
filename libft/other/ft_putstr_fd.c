/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:34:56 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:38:40 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putstr_fd(const char *s, int32_t fd)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (write(fd, s, len));
}

ssize_t	ft_putstrsl_fd(t_str_slice strsl, int32_t fd)
{
	return (write(fd, strsl.str, strsl.len));
}
