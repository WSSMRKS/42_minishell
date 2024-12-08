/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:02:06 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include <stdlib.h>

/// @brief Destroy the string and free the memory.
/// @param str The string to destroy.
/// @note The string will be empty, but still usable after this operation.
void	str_destroy(t_str *str)
{
	if (str->heap)
	{
		free(str->_large_str);
		str->heap = false;
	}
	str->len = 0;
	str->_small_str[0] = 0;
	str->mem_err = false;
}
