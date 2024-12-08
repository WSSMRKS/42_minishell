/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ref.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:11:36 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:18:50 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

/// @brief Gives read access to the string data.
/// @param str String to read from.
/// @return Pointer to the borrowed string data.
const char	*cstr_ref(const t_str *str)
{
	if (str->heap)
		return (str->_large_str);
	return (str->_small_str);
}

/// @brief Gives write access to the string data.
/// @param str String to write to.
/// @return Pointer to the borrowed string data.
char	*cstr_mut(t_str *str)
{
	if (str->heap)
		return (str->_large_str);
	return (str->_small_str);
}

/// @brief Destroys the given string and returns its data.
/// @param str String to destroy.
/// @return (Null)Pointer to the owned string data.
char	*cstr_take(t_str *str)
{
	char	*out;

	if (str->heap)
		out = str->_large_str;
	else
		out = ft_strndup(str->_small_str, str->len);
	*str = str_empty();
	return (out);
}

/// @brief Clones the data of the given string.
/// @param str String to clone.
/// @return (Null)Pointer to the cloned string data.
char	*cstr_clone(const t_str *str)
{
	return (ft_strndup(cstr_ref(str), str->len));
}
