/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:52:32 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:43:03 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (*str)
	{
		a++;
		str++;
	}
	return (a);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%zu\n", ft_strlen("0123456789ssdad\n"));
	printf("%zu\n", strlen("0123456789ssdad\n\0sdajh;fahf"));
}
*/
