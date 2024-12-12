#include "../../../headers/minishell.h"

void	ast_printerr(t_vec *ast, size_t err_i, const char *err);

bool	last_tk_is_continue_nl(t_vec *tokens)
{
	t_vec	tokens_clone;
	t_token_ty	last;

	tokens_clone = vec_clone(tokens);
	if (tokens_clone.mem_err)
		return (false);
	tokens_normalize_for_continue_nl_check(&tokens_clone);
	if (tokens_clone.len == 0)
	{
		vec_destroy(&tokens_clone, NULL);
		return (false);
	}
	last = ((t_token*)vec_get_last(&tokens_clone))->type;
	vec_destroy(&tokens_clone, NULL);
	return (last == TK_CONTINUE_NL);
}

/// @brief
/// @param ast
/// @param i
/// @return false if given ast at i is no pipe.
/// If it is a pipe it will return true if the pipe has no argument.
static bool	is_pipe_without_arg_at(t_vec *ast, size_t i)
{
	t_ast	*pipe;
	t_ast	*next;

	pipe = vec_get_at(ast, i);
	if (pipe->ty != AST_OP || pipe->op.ty != OP_PIPE)
		return (false);
	if (i == 0 || i + 1 >= ast->len)
		return (true);
	next = vec_get_at(ast, i + 1);
	if (next->ty == AST_OP && next->op.ty == OP_PIPE)
		return (true);
	return (false);
}

/// @brief
/// @param ast
/// @param i
/// @return false if given ast at i is no op
static bool	is_op_without_arg_at(t_vec *ast, size_t i)
{
	t_ast	*op;

	op = vec_get_at(ast, i);
	if (op->ty != AST_OP || op->op.ty == OP_PIPE)
		return (false);
	return (op->op.arg == NULL);
}

bool	ast_has_integrity(t_vec *ast)
{
	size_t	i;
	bool	ok;

	i = 0;
	ok = true;
	while (i < ast->len)
	{
		if (is_pipe_without_arg_at(ast, i)
			|| is_op_without_arg_at(ast, i))
		{
			ast_printerr(ast, i, "operator is missing an argument");
			ok = false;
		}
		i++;
	}
	return (ok);
}
