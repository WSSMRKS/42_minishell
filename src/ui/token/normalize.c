#include "../../../headers/minishell.h"

// repeating seperators -> single seperator
static void	remove_dup_seperators(t_vec *tokens)
{
	t_token	*token;
	t_token	*next;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_SEPERATOR)
		{
			while (i + 1 < tokens->len)
			{
				next = vec_get_at(tokens, i + 1);
				if (next->type == TK_SEPERATOR)
					vec_remove_at(tokens, i + 1);
				else
					break ;
			}
		}
		i++;
	}
}

static bool	is_redundant_separator(t_vec *tokens, size_t i)
{
    t_token	*prev;
    t_token	*next;

	if (i == 0 || i == tokens->len - 1)
		return (true);
    if (i > 0)
    {
        prev = vec_get_at(tokens, i - 1);
        if (prev->type == TK_OPERATOR || prev->type == TK_CONTINUE_NL || prev->type == TK_NL)
            return (true);
    }
    if (i + 1 < tokens->len)
    {
        next = vec_get_at(tokens, i + 1);
        if (next->type == TK_OPERATOR || next->type == TK_CONTINUE_NL || next->type == TK_NL)
            return (true);
    }
    return (false);
}

static void	remove_redundant_separators(t_vec *tokens)
{
    t_token	*token;
    size_t	i;

    i = 0;
    while (i < tokens->len)
    {
        token = vec_get_at(tokens, i);
        if (token->type == TK_SEPERATOR && is_redundant_separator(tokens, i))
            vec_remove_at(tokens, i);
        else
            i++;
    }
}

// chained tokens of kind TOKEN_WORD, TOKEN_LITERAL, TOKEN_DQUOTE -> single WORD token
static void	merge_chained_word_tokens(t_vec *tokens)
{
	t_token	*token;
	t_token	*next;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_WORD || token->type == TK_LITERAL || token->type == TK_DQUOTE)
		{
			while (i + 1 < tokens->len)
			{
				next = vec_get_at(tokens, i + 1);
				if (next->type == TK_WORD || next->type == TK_LITERAL || next->type == TK_DQUOTE)
				{
					str_cat(&token->str, str_view(&next->str));
					str_destroy(&next->str);
					vec_remove_at(tokens, i + 1);
				}
				else
					break ;
			}
		}
		i++;
	}
}

// after merging chained word tokens, seperators are not needed anymore
static void	remove_all_seperators(t_vec *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_SEPERATOR)
			vec_remove_at(tokens, i);
		else
			i++;
	}
}

// repeating seperators -> single seperator
// remove seperator before or after one of [TOKEN_OPERATOR, TOKEN_CONTINUE_NL, TOKEN_NL]
// chained tokens of kind TOKEN_WORD, TOKEN_LITERAL, TOKEN_DQUOTE -> single WORD token
void	tokens_normalize(t_vec *tokens)
{
	remove_dup_seperators(tokens);
	remove_redundant_separators(tokens);
	merge_chained_word_tokens(tokens);
	remove_all_seperators(tokens);
}
