#include "../../../headers/minishell.h"

/// @brief If the last token is word(\), replace the token with newline().
/// @param tokens The token vector.
static void	handle_newline_token(t_vec *tokens)
{
	static t_token	newline = {.type = TOKEN_NEWLINE};
	t_token	*token;

	token = vec_get_last(tokens);
	if (token && token->type == TOKEN_WORD && token->str.len == 1 && cstr_ref(&token->str)[0] == '\\')
	{
		vec_remove_last(tokens);
		vec_push(tokens, &newline);
	}

}

static void	str_unescape_chars(t_str *str)
{
	size_t	i;
	char	*buf;

	i = 0;
	while (true)
	{
		buf = cstr_mut(str);
		if (buf[i] == 0)
			break ;
		if (buf[i] == '\\' && buf[i + 1] != 0)
			str_remove(str, i);
		i++;
	}
}

void	unescape_chars(t_vec *tokens)
{
	t_token	*token;
	size_t	i;

	handle_newline_token(tokens);
	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TOKEN_WORD || token->type == TOKEN_DQUOTE)
			str_unescape_chars(&token->str);
		i++;
	}
}
