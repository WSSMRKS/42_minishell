/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:04 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:42:02 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	if (n == 0)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			((char *)dest)[n - 1] = ((char *)src)[n - 1];
			n--;
		}
	}
	else if (src == dest)
		return (dest);
	else
	{
		i = 0;
		while (n > 0)
		{
			((char *)dest)[i] = ((char *)src)[i];
			n--;
			i++;
		}
	}
	return (dest);
}

/*
int	main(void)
{
	static char	arr[] = "11111111102222222222";

	printf("%s\n", arr);
	printf("%s\n", (char *)memmove(&arr[0], &arr[10], 20));
	printf("%s\n", arr);

	static char arr2[] = "11111111102222222222";

	printf("%s\n", arr2);
	printf("%s\n", (char *)ft_memmove(&arr2[0], &arr2[10], 20));
	printf("%s\n", arr2);
}
*/
