/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:50:27 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARRAY_H
# define FT_ARRAY_H
# pragma once

# include "../libft.h"

typedef void	(*t_vec_iteri)(t_vec *vec, size_t i, void *extra);
/// @brief A comparator function used for determining the order of elements.
/// @return 0 if a == b, < 0 if a less than b, > 0 if a bigger than b.
typedef int32_t	(*t_comparator)(const void *a, const void *b);

typedef struct s_qsort_state
{
	t_comparator	cmp;
	/// @brief Clone of the pivot element. (temp alloc)
	void			*pivot;
	size_t			element_size;
}					t_qsort_state;

typedef struct mid_partition
{
	size_t	lt;
	size_t	gt;
}			t_mid_partition;

void	array_free(void *array, size_t len, size_t element_size,
			void (*destroy)(void *));
bool	arr_qsort(void *arr, size_t len, size_t element_size, t_comparator cmp);
bool	arr_is_sorted(void *arr, size_t len, size_t element_size,
			t_comparator cmp);

#endif
