/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:52:33 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:39 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include <stdlib.h>

void	array_free(void *array, size_t len, size_t element_size,
			void (*destroy)(void *))
{
	size_t	i;

	if (destroy)
	{
		i = 0;
		while (i < len)
		{
			destroy(array + i * element_size);
			i++;
		}
	}
	free(array);
}
