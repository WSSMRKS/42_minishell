/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsl_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:00:54 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"

/// @brief Moves a stringview.
/// @param s The stringview to move.
/// @param n The amount of characters to move by.
/// @return The moved stringview.
t_str_slice	strsl_move(t_str_slice s, size_t n)
{
	n = usizemin(n, s.len);
	s.str += n;
	s.len -= n;
	return (s);
}

/// @brief Moves a stringview.
/// @param s The stringview to move.
/// @param n The amount of characters to move by.
/// @return false if the stringview's len or n are 0.
bool	strsl_move_inplace(t_str_slice *s, size_t n)
{
	n = usizemin(n, s->len);
	s->str += n;
	s->len -= n;
	return (n != 0);
}

/// @brief Get a reference to the string slice before moving it.
/// @param s The string slice to move.
/// @param n The amount of characters to move by.
/// @return A reference to the string slice before moving it.
const char	*strsl_ref_move(t_str_slice *s, size_t n)
{
	const char	*ret;

	n = usizemin(n, s->len);
	ret = s->str;
	s->str += n;
	s->len -= n;
	return (ret);
}

/// @brief Get a reference to the string slice after moving it.
/// @param s The string slice to move.
/// @param n The amount of characters to move by.
/// @return A reference to the string slice after moving it.
const char	*strsl_move_ref(t_str_slice *s, size_t n)
{
	n = usizemin(n, s->len);
	s->str += n;
	s->len -= n;
	return (s->str);
}
