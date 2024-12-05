/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:52:31 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 17:57:52 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "util.h"

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

/// if the first character is '#' the rest of the string is treated as comment and should be thrown out
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
size_t	word_len(const char *str, size_t *out)
{
	size_t	len;
	size_t	total_len;

	total_len = ft_strlen(str);
	len = 0;
	if (is_word_delimiter(str[len]))
		len = 1;
	while (str[len])
	{
		if (str[len] == '\\')
		{
			if (str[len + 1] == 0)
			{
				if (len == 0)
					len++;
				break;
			}
			len += 2;
		}
		else if (!is_word_delimiter(str[len])
			&& !str_starts_with_op(cstr_slice(&str[len], usizemin(total_len - len, 2)), 0))
			len++;
		else
			break ;
	}
	if (out)
		*out = len;
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
