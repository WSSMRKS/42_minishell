/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:53:51 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:19:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

t_str	vec_display(t_vec *vec, void (*display)(const void *, t_str *))
{
	t_str	out;
	size_t	i;

	out = str_clone_from(cstr_slice("[", 1));
	i = 0;
	while (i < vec->len)
	{
		display(vec_get_at(vec, i), &out);
		if (i + 1 < vec->len)
			str_pushstr(&out, cstr_slice(", ", 2));
		++i;
	}
	str_pushstr(&out, cstr_slice("]", 1));
	return (out);
}

t_str	vec_debug(t_vec *vec, void (*debug)(const void *, t_str *))
{
	t_str	out;
	size_t	i;

	out = str_clone_from(cstr_slice("{len=", 5));
	str_itoa_cat(vec->len, base10(), &out);
	str_pushstr(&out, cstr_slice(" cap=", 5));
	str_itoa_cat(vec_capacity(vec), base10(), &out);
	if (vec->mem_err)
		str_pushstr(&out, cstr_slice(" !mem_err!", 10));
	str_pushstr(&out, cstr_slice(" [", 2));
	i = 0;
	while (i < vec->len)
	{
		debug(vec_get_at(vec, i), &out);
		if (i + 1 < vec->len)
			str_pushstr(&out, cstr_slice(", ", 2));
		++i;
	}
	str_pushstr(&out, cstr_slice("]}", 2));
	return (out);
}
