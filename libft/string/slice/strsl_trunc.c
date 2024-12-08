/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsl_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:49:57 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"

/// @brief Creates a stringview with a new length.
/// @param s The stringview to change the length of.
/// @param new_len The new length of the stringview.
/// @return The stringview with the new length.
t_str_slice	strsl_trunc(t_str_slice s, size_t new_len)
{
	s.len = usizemin(s.len, new_len);
	return (s);
}

/// @brief Sets the length of a stringview.
/// @param s The stringview to change the length of.
/// @param new_len The new length of the stringview.
/// @return false if the stringview's len or new_len are 0.
bool	strsl_trunc_inplace(t_str_slice *s, size_t new_len)
{
	new_len = usizemin(s->len, new_len);
	s->len = new_len;
	return (new_len != 0);
}
