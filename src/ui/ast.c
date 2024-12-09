#include "../../headers/minishell.h"

void	free_ast(void *ast_node)
{
	t_ast	*ast;

	ast = ast_node;
	if (ast->ty == AST_CMD)
	{
		ft_free_2d(ast->cmd);
		ast->cmd = NULL;
	}
	else
	{
		free(ast->op.arg);
		ast->op.arg = NULL;
	}
}

// token at i == string (command exe), rest every token = one argument except for when token == operator
// returns false if there was a mem error, true otherwise
bool	try_add_command(t_vec *tokens, size_t *i, t_vec *ast)
{
	char	*tmp;
	t_vec	args;
	t_ast	ast_cmd;
	t_token	*token;

	ast_cmd = (t_ast){.ty = AST_CMD, .cmd = NULL};
	args = vec_empty(sizeof(char *));
	while (*i < tokens->len)
	{
		token = vec_get_at(tokens, *i);
		if (!token_has_str(token))
			break ;
		tmp = cstr_take(&token->str);
		if (tmp == NULL)
		{
			vec_destroy(&args, iter_ptr_free);
			return (false);
		}
		if (!vec_push(&args, &tmp))
		{
			free(tmp);
			vec_destroy(&args, iter_ptr_free);
			return (false);
		}
		(*i)++;
	}
	if (args.len == 0)
		return (true);
	if (vec_push_null(&args))
		ast_cmd.cmd = vec_take(&args);
	if (ast_cmd.cmd == NULL)
	{
		vec_destroy(&args, iter_ptr_free);
		return (false);
	}
	if (vec_push(ast, &ast_cmd))
		return (true);
	ft_free_2d(ast_cmd.cmd);
	return (false);
}

bool	try_add_operator(t_vec *tokens, size_t *i, t_vec *ast)
{
	t_ast	ast_op;
	t_token	*token;

	ast_op = (t_ast){.ty = AST_OP, .op = {0}};
	token = vec_get_at(tokens, *i);
	if (token->type != TK_OPERATOR)
		return (true);
	ast_op.op.ty = token->op;
	*i += 1;
	if (*i != tokens->len && token->op != OP_PIPE)
	{
		token = vec_get_at(tokens, *i);
		if (token_has_str(token))
		{
			ast_op.op.arg = cstr_take(&token->str);
			if (ast_op.op.arg == NULL)
				return (false);
			*i += 1;
		}
	}
	vec_push(ast, &ast_op);
	if (!ast->mem_err)
		return (true);
	free(ast_op.op.arg);
	return (false);
}

// handle and remove any TK_CONTINUE_NL tokens before using this function
// postprocess by removing any commands that are not first and are not preceded by PIPE
// the input tokens array will be cleared if done, otherwise there are more
// commands left to be parsed for which this function should be called again
bool	tokens_to_ast(t_vec *tokens, t_vec *out)
{
	size_t	i;

	*out = vec_empty(sizeof(t_ast));
	i = 0;
	while (i < tokens->len)
	{
		if (((t_token*)vec_get_at(tokens, i))->type == TK_NL)
		{
			vec_remove_range(tokens, 0, i + 1);
			// TODO free in range before removing
			return (true);
		}
		if (!try_add_command(tokens, &i, out)
			|| (i < tokens->len && !try_add_operator(tokens, &i, out)))
		{
			vec_destroy(out, free_ast);
			return (false);
		}
	}
	vec_destroy(tokens, free_token);
	return (true);
}
