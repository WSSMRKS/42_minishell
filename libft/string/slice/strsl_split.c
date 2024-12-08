/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsl_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:19:21 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/18 17:04:14 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"

static t_str_slice	split_next(t_str_slice *s, size_t (*pattern)(t_str_slice s))
{
	t_str_slice	out;

	while (strsl_move_inplace(s, pattern(*s)))
		;
	out = strsl_trunc(*s, 0);
	while (out.len < s->len && !pattern(strsl_move(*s, out.len)))
		out.len++;
	*s = strsl_move(*s, out.len);
	return (out);
}

/// @brief Splits a string into a vec of `t_str_slice`.
/// @param s The string to split.
/// @param pattern The pattern to split the string at.
/// @return A vec of stringviews.
/// @warning Check the error flag for memory allocation errors.
t_vec	strsl_split_where(t_str_slice s, size_t (*pattern)(t_str_slice s))
{
	t_vec		out;
	t_str_slice	next;

	out = vec_empty(sizeof(t_str_slice));
	while (s.len != 0)
	{
		next = split_next(&s, pattern);
		vec_push(&out, &next);
	}
	if (out.len > 0 && ((t_str_slice *)vec_get_last(&out))->len == 0)
		vec_remove_last(&out);
	return (out);
}

static t_str_slice	splitstr_next(t_str_slice *s, t_str_slice pattern)
{
	t_str_slice	out;
	size_t		tmp;

	while (strsl_starts_with(*s, pattern) && strsl_move_inplace(s, pattern.len))
		;
	out = strsl_trunc(*s, 0);
	tmp = s->len;
	while (out.len < tmp)
	{
		out.len++;
		strsl_move_inplace(s, 1);
		if (strsl_starts_with(*s, pattern))
			break ;
	}
	return (out);
}

/// @brief Splits a string into a vec of `t_str_slice`.
/// @param s The string to split.
/// @param pattern The string pattern to split the string at.
/// @return A vec of stringviews.
/// @warning Check the error flag for memory allocation errors.
t_vec	strsl_split(t_str_slice s, t_str_slice pattern)
{
	t_vec		out;
	t_str_slice	next;

	out = vec_empty(sizeof(t_str_slice));
	while (true)
	{
		next = splitstr_next(&s, pattern);
		if (next.len == 0)
			break ;
		vec_push(&out, &next);
	}
	if (out.len > 0 && ((t_str_slice *)vec_get_last(&out))->len == 0)
		vec_remove_last(&out);
	return (out);
}
