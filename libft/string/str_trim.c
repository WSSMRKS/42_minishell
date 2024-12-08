/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:11:55 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/18 17:43:27 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Remove leading and trailing whitespace from the string.
/// @param str The string to trim.
/// @note see ft_isspace
void	str_trim(t_str *str)
{
	str_trim_end(str);
	str_trim_start(str);
}

/// @brief Remove leading whitespace from the string.
/// @param str The string to trim.
/// @note see ft_isspace
void	str_trim_start(t_str *str)
{
	const char	*cstr;
	size_t		i;

	cstr = cstr_ref(str);
	i = 0;
	while (ft_isspace(cstr[i]))
		i++;
	str_remove_range(str, 0, i);
}

/// @brief Remove trailing whitespace from the string.
/// @param str The string to trim.
/// @note see ft_isspace
void	str_trim_end(t_str *str)
{
	const char	*cstr;
	size_t		i;

	i = 0;
	cstr = cstr_ref(str);
	while (i != str->len && ft_isspace(cstr[str->len - i - 1]))
		i++;
	str_trunc(str, str->len - i);
}
