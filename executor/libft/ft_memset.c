/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:31:34 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:42:04 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			*tmp;
	unsigned long	a;

	a = 0;
	tmp = s;
	while (a < n)
	{
		*tmp = c;
		a++;
		tmp++;
	}
	return (s);
}

/*
#include <string.h>

int	main(void)
{
	char	arr1[40];
	int		arr2[10];

	printf("%s\n", (char *)ft_memset(arr1, 126, 40));
	printf("%s\n", (char *) ft_memset(arr2, 16, 50));
	printf("%s\n", (char *) memset(arr1, 16, 30));
	printf("%s\n", (char *) memset(arr2, 126, 30));
}
*/
