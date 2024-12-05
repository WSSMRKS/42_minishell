#include "../../../headers/minishell.h"

t_token	tk_word(t_str_slice word)
{
	return ((t_token){.type = TK_WORD, .str = str_clone_from(word)});
}

t_token	tk_op(t_op_ty op)
{
	return ((t_token){.type = TK_OPERATOR, .op = op});
}

t_token	tk_lit(t_str_slice quoted)
{
	quoted.len -= 2;
	quoted.str += 1;
	return ((t_token){.type = TK_LITERAL, .str = str_clone_from(quoted)});
}

t_token	tk_dquote(t_str_slice quoted)
{
	quoted.len -= 2;
	quoted.str += 1;
	return ((t_token){.type = TK_DQUOTE, .str = str_clone_from(quoted)});
}

t_token	tk_empty(t_token_ty ty)
{
	return ((t_token){.type = ty, .str = str_empty()});
}
