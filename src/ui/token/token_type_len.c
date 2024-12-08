/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:52:31 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 18:11:59 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "tk_util.h"
#include <stddef.h>

/// @brief Checks if the string starts with a specific opening character
/// and contains its closing character.
/// @param str The string to check.
/// @param bounds The opening/closing character (e.g., '"', '\'', '(')
/// @param out The length of the bounded substring including delimiters.
/// @return The length of the bounded substring.
/// Returns 0 if not found or unterminated.
size_t	bounded_token_len(const char *str, char bounds, size_t *out)
{
	if (*str != bounds)
		return (0);
	*out = 1;
	while (str[*out])
	{
		if (str[*out] == '\\' && str[*out + 1] != 0)
			(*out) += 2;
		else if (str[(*out)++] == bounds)
			return (*out);
	}
	return (0);
}

/// if the first character is '#' the rest of the string
/// is treated as comment and should be thrown out
size_t	comment_len(const char *str)
{
	if (*str != '#')
		return (0);
	return (ft_strlen(str));
}

/// @brief Gets the length of a word delimited by is_word_delimiter.
/// @param str The string to check.
/// @param out The length of the word. (nullpointer allowed)
/// @return The length of the word.
size_t	word_len(const char *str)
{
	t_str_slice	s;
	size_t		len;

	len = 0;
	s = cstr_view(str);
	while (s.str[len])
	{
		if (str[len] == '\\')
		{
			if (len == s.len)
			{
				if (len == 0)
					len++;
				break ;
			}
			len += 2;
		}
		else if (!is_word_delimiter(str[len])
			&& !str_starts_with_op(cstr_slice(&str[len],
					usizemin(s.len - len, 2)), 0))
			len++;
		else
			break ;
	}
	return (len);
}

size_t	var_len(const char *str, size_t *out)
{
	size_t	len;

	if (*str != '$')
		return (0);
	len = 1;
	// TODO No number if first char
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	if (len == 1)
	{
		if (str[len] == '?')
			len = 2;
		else
			len = 0;
	}
	if (out)
		*out = len;
	return (len);
}
