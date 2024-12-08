/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:14:23 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 03:32:09 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

/// @brief Reallocates a memory block.
/// @param ptr Pointer to the memory block to reallocate.
/// @param from Size of the memory block to reallocate.
/// @param to New size of the memory block.
/// @return Pointer to the reallocated memory block.
void	*ft_realloc(void *ptr, size_t from, size_t to)
{
	void	*new_ptr;

	new_ptr = malloc(to);
	if (!new_ptr)
		return (0);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, usizemin(from, to));
		free(ptr);
	}
	return (new_ptr);
}

/// @brief Reallocates a memory block.
/// @param ptr Pointer to the memory block to reallocate.
/// @param from Number of elements.
/// @param nmemb New number of elements.
/// @param size Size of each element.
/// @return Pointer to the reallocated memory block.
void	*ft_reallocarray(void *ptr, size_t from, size_t nmemb, size_t size)
{
	size_t	len;

	if (!usizemult(nmemb, size, &len))
		return (0);
	return (ft_realloc(ptr, from * size, len));
}

/// @brief Reallocates a string.
/// @param ptr Pointer to the string to reallocate.
/// @param to New size of the string.
/// @return Pointer to the reallocated string.
char	*ft_reallocstring(char *ptr, size_t to)
{
	char	*new_ptr;

	new_ptr = malloc(to);
	if (!new_ptr)
		return (0);
	new_ptr[0] = 0;
	if (ptr)
	{
		ft_strlcpy(new_ptr, ptr, to);
		free(ptr);
	}
	return (new_ptr);
}
