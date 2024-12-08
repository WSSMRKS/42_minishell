/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_pushstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:57:01 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:18:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Append a string to the string.
/// @param str The string to append to.
/// @param s The string to append.
/// @warning Check the error flag for memory allocation errors.
void	str_pushstr(t_str *str, t_str_slice s)
{
	str_insertstr(str, str->len, s);
}

/// @brief Insert a string at the start of the string.
/// @param str The string to insert into.
/// @param s The string to insert.
/// @warning Check the error flag for memory allocation errors.
void	str_pushstr_front(t_str *str, t_str_slice s)
{
	str_insertstr(str, 0, s);
}

/// @brief Append a string to the string.
/// @param str The string to append to.
/// @param s The string to append.
/// @param n Number of times to append the string.
/// @warning Check the error flag for memory allocation errors.
void	str_pushstrn(t_str *str, t_str_slice s, size_t n)
{
	str_insertstrn(str, str->len, s, n);
}

/// @brief Insert a string at the start of the string.
/// @param str The string to insert into.
/// @param s The string to insert.
/// @param n Number of times to insert the string.
/// @warning Check the error flag for memory allocation errors.
void	str_pushstrn_front(t_str *str, t_str_slice s, size_t n)
{
	str_insertstrn(str, 0, s, n);
}
