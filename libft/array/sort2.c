/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:15:12 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"
#include <stdlib.h>

void	quicksort(void *arr, size_t len, t_qsort_state *st);

/// @brief Sorts an array using the quicksort algorithm.
/// @param arr The array to sort.
/// @param len The number of elements in the array.
/// @param element_size The size of each element in the array.
/// @param cmp The comparator function used to compare elements.
/// @return true if the array was successfully sorted, otherwise false.
/// @note May fail due to malloc failure.
bool	arr_qsort(void *arr, size_t len, size_t element_size, t_comparator cmp)
{
	t_qsort_state	st;

	st.cmp = cmp;
	st.element_size = element_size;
	st.pivot = malloc(element_size);
	if (!st.pivot)
		return (false);
	quicksort(arr, len, &st);
	free(st.pivot);
	return (true);
}

bool	arr_is_sorted(void *arr, size_t len, size_t element_size,
		t_comparator cmp)
{
	size_t	i;

	i = 1;
	while (i < len)
	{
		if (cmp(arr + (i - 1) * element_size, arr + i * element_size) > 0)
			return (false);
		i++;
	}
	return (true);
}
