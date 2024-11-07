#include "../../../headers/minishell.h"

t_token	tk_sep()
{
	return ((t_token){.type = TOKEN_SEPERATOR});
}

t_token	tk_word(t_str_slice word)
{
	return ((t_token){.type = TOKEN_WORD, .str = str_clone_from(word)});
}

t_token	tk_op(t_operator_ty op)
{
	return ((t_token){.type = TOKEN_OPERATOR, .op = op});
}

t_token	tk_lit(t_str_slice quoted)
{
	quoted.len -= 2;
	quoted.str += 1;
	return ((t_token){.type = TOKEN_LITERAL, .str = str_clone_from(quoted)});
}

t_token	tk_dquote(t_str_slice quoted)
{
	quoted.len -= 2;
	quoted.str += 1;
	return ((t_token){.type = TOKEN_DQUOTE, .str = str_clone_from(quoted)});
}
