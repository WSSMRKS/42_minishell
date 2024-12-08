/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:11:10 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Swaps the two vecs.
/// @param vec1
/// @param vec2
void	vec_swap(t_vec *vec1, t_vec *vec2)
{
	t_vec	temp;

	temp = *vec1;
	*vec1 = *vec2;
	*vec2 = temp;
}

/// @brief Swaps the two elements at the given indices.
/// @param vec1
/// @param index1
/// @param vec2
/// @param index2
void	vec_swap_at(t_vec *vec1, size_t index1, t_vec *vec2, size_t index2)
{
	if (index1 >= vec1->len || index2 >= vec2->len)
		return ;
	ft_memswap(vec_get(vec1) + index1 * vec1->element_size, vec_get(vec2)
		+ index2 * vec2->element_size, vec2->element_size);
}
