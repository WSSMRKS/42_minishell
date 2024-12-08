/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsl_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:45:52 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:22:27 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"

/// @brief Removes leading and trailing whitespace from a stringview.
/// @param s The stringview to trim.
/// @return The trimmed stringview.
t_str_slice	strsl_trim(t_str_slice s)
{
	return (strsl_trim_start(strsl_trim_end(s)));
}

/// @brief Removes trailing whitespace from a stringview.
/// @param s The stringview to trim.
/// @return The trimmed stringview.
t_str_slice	strsl_trim_end(t_str_slice s)
{
	while (s.len && ft_isspace(s.str[s.len - 1]))
		s.len--;
	return (s);
}

/// @brief Removes leading whitespace from a stringview.
/// @param s The stringview to trim.
/// @return The trimmed stringview.
t_str_slice	strsl_trim_start(t_str_slice s)
{
	while (s.len && ft_isspace(*s.str))
	{
		s.str++;
		s.len--;
	}
	return (s);
}
