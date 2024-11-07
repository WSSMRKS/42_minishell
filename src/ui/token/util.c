#include "../../../headers/minishell.h"

static t_bool	is_word_delimiter(char c)
{
	return (ft_isspace(c) || c == '"' || c == '\'');
}

/// @brief Checks if the string starts with a specific opening character
/// and contains its closing character.
/// @param str The string to check.
/// @param open The opening character (e.g., '"', '\'', '(')
/// @param close The closing character (e.g., '"', '\'', ')')
/// @param out The length of the bounded substring including delimiters.
/// @return The length of the bounded substring.
/// Returns 0 if not found or unterminated.
size_t	bounded_token_len(const char *str, char open, char close, size_t *out)
{
	if (*str != open)
		return (0);
	*out = 1;
	while (TRUE)
	{
		if (str[*out] == 0)
			return (0);
		if (str[(*out)++] == close)
			return (*out);
	}
}

/// @brief Gets the length of a word delimited by is_word_delimiter.
/// @param str The string to check.
/// @param out The length of the word. (nullpointer allowed)
/// @return The length of the word.
size_t	word_len(const char *str, size_t *out)
{
	size_t	len;

	len = 0;
	while (str[len] && !is_word_delimiter(str[len]))
		len++;
	if (out)
		*out = len;
	return (len);
}

/// @brief Checks if the string is an operator.
/// @param str The string to check.
/// @param out (Null)Pointer for output.
/// @return TRUE if the string is an operator, FALSE otherwise.
t_bool	str_is_operator(t_str_slice str, t_operator_ty *out)
{
	size_t						i;
	static const t_str_slice	OPERATORS[] = {
    [OP_PIPE]={"|", 1},
    [OP_REDIRECT]={">", 1},
    [OP_INP_REDIRECT]={"<", 1},
    [OP_APPEND]={">>", 2},
    [OP_HEREDOC]={"<<", 2},
    {NULL, 0}
	};

	i = 0;
	while (OPERATORS[i].str)
	{
		if (strsl_eq(str, OPERATORS[i]))
		{
			if (out)
				*out = (t_operator_ty)i;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	vec_push_tk(t_vec *vec, t_token tk)
{
	vec_push(vec, &tk);
}
