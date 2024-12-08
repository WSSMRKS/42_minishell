/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:18:00 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/17 23:21:06 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_memswap(void *b1, void *b2, size_t n)
{
	char	*ptr1;
	char	*ptr2;
	char	tmp;
	size_t	i;

	ptr1 = b1;
	ptr2 = b2;
	i = 0;
	while (i < n)
	{
		tmp = *ptr1;
		*ptr1++ = *ptr2;
		*ptr2++ = tmp;
		i++;
	}
}
