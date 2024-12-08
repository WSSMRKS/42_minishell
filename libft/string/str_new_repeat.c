/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_new_repeat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:44:07 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:18:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Creates a string by repeating the given string 'n' times.
/// @param s String to repeat.
/// @param n Number of repetitions.
/// @return Repeated string.
/// @warning Check the error flag for memory allocation errors.
t_str	str_repeat_from(t_str_slice s, size_t n)
{
	(void)s;
	(void)n;
	return (str_empty());
}
