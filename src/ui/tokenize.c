#include "../../headers/minishell.h"
#include <stdio.h>

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

size_t	word_len(const char *str, size_t *out)
{
	*out = 0;
	while (str[*out] && !ft_isspace(str[*out]))
		(*out)++;
	return (*out);
}

t_bool	word_is_operator(t_str_slice str)
{
	size_t						i;
	static const t_str_slice	OPERATORS[] = {
    {"|", 1},
    {">", 1},
    {"<", 1},
    // {"&", 1},
    // {";", 1},
    {">>", 2},
    {"<<", 2},
    // {"&&", 2},
    // {"||", 2},
    {NULL, 0}  // terminator
	};

	i = 0;
	while (OPERATORS[i].str)
	{
		if (strsl_eq(str, OPERATORS[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/* ??????????????????????
```bash
$ echo "hello"world""
helloworld

$ echo hello"world"
helloworld

$ echo hello"world
>

$ echo "hello"world
helloworld

$ echo hello"world"hey
helloworldhey

$ echo hello'world'hey
helloworldhey

$ ./pargs my 1 "very" "'complex'" "sentence" and multi tests" sentence end"? 'no no "nooo"'
argc: 10
argv[0]: ./pargs
argv[1]: my
argv[2]: 1
argv[3]: very
argv[4]: 'complex'
argv[5]: sentence
argv[6]: and
argv[7]: multi
argv[8]: tests sentence end?
argv[9]: no no "nooo"
```
*/

/// @brief Tokenizes the input string.
/// @param inp The input string.
/// @return A vector of tokenized strings (t_str_slice).
/// Example:
/// mycmd "hello"world"" wooord "'mystring'"
/// -> [mycmd, "hello", world, "", wooord]
t_vec	tokenize(t_str_slice inp)
{
	t_vec		out;
	t_str_slice	token;

	out = vec_empty(sizeof(t_str_slice));
	token = cstr_slice(inp.str, 0);
	while (TRUE)
	{
		strsl_trim_start_inplace(&inp);
		if (!inp.len)
			break ;
		if (bounded_token_len(inp.str, '"', '"', &token.len)
			|| bounded_token_len(inp.str, '\'', '\'', &token.len)
			|| word_len(inp.str, &token.len))
		{
			vec_push(&out, &token);
			strsl_move_inplace(&inp, token.len);
			continue ;
		}
		perror("tokenize error");
		break ;
	}
	return (out);
}
