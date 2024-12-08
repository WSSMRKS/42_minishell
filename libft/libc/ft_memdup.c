/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 06:21:52 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/17 06:22:08 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

void	*ft_memdup(const void *src, size_t n)
{
	void	*out;

	out = malloc(n);
	if (!out)
		return (0);
	return (ft_memcpy(out, src, n));
}
