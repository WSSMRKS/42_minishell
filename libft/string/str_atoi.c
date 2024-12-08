/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:00 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Convert a string to an integer.
/// @param str The string to convert.
/// @param base The base of the number.
/// @param out The output integer.
/// @param ofb The behavior on overflow.
/// @return True if the conversion was successful.
/// @note Will skip leading/trailing whitespace and accept an optional sign.
/// @note Will return false if the string is empty or contains invalid chars.
bool	str_atoi(const t_str *str, t_str_slice base, int32_t *out,
		t_overflow_behavior ofb)
{
	return (strsl_atoi(str_view(str), base, out, ofb));
}
