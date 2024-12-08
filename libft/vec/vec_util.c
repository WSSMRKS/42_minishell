/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:16:26 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include <stdlib.h>

void	iter_str_destroy(void *ele)
{
	str_destroy(ele);
}

void	iter_ptr_free(void *ptr)
{
	free(*(void **)ptr);
}

bool	vec_push_null(t_vec *vec)
{
	void	*next_uninit;

	next_uninit = vec_get_next_uninit_incr_len(vec);
	if (!next_uninit)
		return (false);
	ft_memset(next_uninit, 0, vec->element_size);
	return (true);
}
