#include "../../../headers/minishell.h"

/// @brief If the last token is word(\), replace the token with newline().
/// @param tokens The token vector.
static void	handle_continue_nl_token(t_vec *tokens)
{
	static t_token	newline = tk_empty(TK_CONTINUE_NL);
	t_token	*token;

	token = vec_get_last(tokens);
	if (token && token->type == TK_WORD && token->str.len == 1 && cstr_ref(&token->str)[0] == '\\')
	{
		vec_remove_last(tokens);
		vec_push(tokens, &newline);
	}
}
// for double quotes only unescape <‘$’, ‘"’, ‘\’, newline>.
static void	str_unescape_chars(t_str *str, t_token_ty tk_ty)
{
	size_t	i;
	char	*buf;

	i = 0;
	while (true)
	{
		buf = cstr_mut(str);
		if (buf[i] == 0)
			break ;
		if (buf[i] == '\\' && buf[i + 1] != 0
			&& (tk_ty != TK_DQUOTE || ft_strchr("\"\\$", buf[i + 1])))
			str_remove(str, i);
		i++;
	}
}

void	unescape_chars(t_vec *tokens)
{
	t_token	*token;
	size_t	i;

	handle_continue_nl_token(tokens);
	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_WORD || token->type == TK_DQUOTE)
			str_unescape_chars(&token->str, token->type);
		i++;
	}
}
