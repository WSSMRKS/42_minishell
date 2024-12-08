/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:02:06 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include <stdlib.h>

/// @brief Destroy the vec and free the memory.
/// @param vec The vec to destroy.
/// @param destroy (Null)Pointer to function to call for each element.
/// @note The vec will be empty, but still usable after this operation.
void	vec_destroy(t_vec *vec, t_vec_iter destroy)
{
	if (destroy)
		vec_iter(vec, destroy);
	if (vec->heap)
	{
		free(vec->_large_buf);
		vec->heap = false;
	}
	vec->len = 0;
	vec->mem_err = false;
}
