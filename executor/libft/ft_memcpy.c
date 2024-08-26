/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:31:34 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:41:58 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void			*tmp;
	unsigned long	a;

	a = 0;
	if (dest == NULL && src == NULL)
		return (dest);
	tmp = dest;
	while (a < n)
	{
		*(char *) dest = *(char *) src;
		a++;
		dest++;
		src++;
	}
	return (tmp);
}

/*
#include <string.h>
#include <unistd.h>

int	main(void)
{
	static int	arr1[40] = {12, 39, 23, 23, 454, 6, 4, 4, 3, 2};
	static char	arr2[] = "sjdaflajsdfljas;lfkja;lkjfsflsahdkfjaha";
	static int	arr3[40] = {12, 39, 23, 23, 454, 6, 4, 4, 3, 2};

	write(1, arr2, 40);
	write(1, "\n", 1);
	write(1, arr1, 40);
	write(1, "\n", 1);
	ft_memcpy(arr1, arr2, 40);
	write(1, arr2, 40);
	write(1, "\n", 1);
	write(1, arr1, 40);
	write(1, "\n", 1);
	write(1, "--------------------------------\n", 33);
	memcpy(arr3, arr1, 40);
	write(1, arr3, 40);
	write(1, "\n", 1);
	write(1, arr1, 40);
	write(1, "\n", 1);
}
*/
