/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_remove2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:54:13 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

/// @brief Remove the elements matching the given element.
/// @param vec The vec to remove the element from.
/// @param index The index of the element to remove.
void	vec_remove(t_vec *vec, const void *element)
{
	char	*buf;
	size_t	i;

	if (vec->len == 0)
		return ;
	buf = vec_get(vec);
	i = vec->len - 1;
	while (true)
	{
		if (!ft_memcmp(buf + i * vec->element_size, element, vec->element_size))
			vec_remove_at(vec, i);
		if (i == 0)
			break ;
		i--;
	}
}

/// @brief Remove the first 'n' elements matching the given element.
/// @param vec The vec to remove the element from.
/// @param element The element to remove.
/// @param n The number of elements to remove.
/// @note Used when expecting large `n` & `vec->len` to avoid stack overflow.
void	vec_remove_first_n_iterative(t_vec *vec, const void *element, size_t n)
{
	char	*buf;
	size_t	i;
	t_vec	to_remove;

	buf = vec_get(vec);
	i = 0;
	to_remove = vec_empty(sizeof(size_t));
	while (i < vec->len && n)
	{
		if (!ft_memcmp(buf + i * vec->element_size, element, vec->element_size))
		{
			n--;
			vec_push(&to_remove, &i);
			if (vec->mem_err)
			{
				vec_remove_at(vec, i);
				continue ;
			}
		}
		i++;
	}
	i = to_remove.len;
	while (i--)
		vec_remove_at(vec, *(size_t *)vec_get_at(&to_remove, i));
	vec_destroy(&to_remove, 0);
}

static void	vec_remove_first_n_recursive_inner(t_vec *vec, const void *element,
			size_t n, size_t i)
{
	char	*buf;

	buf = vec_get(vec);
	while (i < vec->len && n)
	{
		if (!ft_memcmp(buf + i * vec->element_size, element, vec->element_size))
		{
			vec_remove_first_n_recursive_inner(vec, element, n - 1, i + 1);
			vec_remove_at(vec, i);
			return ;
		}
		i++;
	}
}

/// @brief Remove the first 'n' elements matching the given element.
/// @param vec The vec to remove the element from.
/// @param element The element to remove.
/// @param n The number of elements to remove.
/// @warning NEEDS TESTING
void	vec_remove_first_n_recursive(t_vec *vec, const void *element, size_t n)
{
	vec_remove_first_n_recursive_inner(vec, element, n, 0);
}

/// @brief Remove the last 'n' elements matching the given element.
/// @param vec The vec to remove the element from.
/// @param element The element to remove.
/// @param n The number of elements to remove.
void	vec_remove_last_n(t_vec *vec, const void *element, size_t n)
{
	char	*buf;
	size_t	i;

	if (vec->len == 0)
		return ;
	buf = vec_get(vec);
	i = vec->len - 1;
	while (n)
	{
		if (!ft_memcmp(buf + i * vec->element_size, element, vec->element_size))
		{
			vec_remove_at(vec, i);
			n--;
		}
		if (i == 0)
			break ;
		i--;
	}
}
