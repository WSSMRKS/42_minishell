#include "../../../headers/minishell.h"
#include <stdbool.h>
#include <stdio.h>

static void	print_all_tokens(t_vec *tokens)
{
	for (size_t i = 0; i < tokens->len; i++)
	{
		t_token *token = vec_get_at(tokens, i);
		token_print(token, STDERR);
		if (!write(STDERR, "\n", 1))
			perror("write error");
	}
}

void	parser_destroy(t_parser *p)
{
	vec_destroy(&p->tokens, NULL);
	str_destroy(&p->last_input);
}

t_parser	parser_init(void *data, t_read_input read_input,
	t_get_symtab get_symtab, t_get_last_ret get_last_ret)
{
	t_parser	p;

	p.tokens = vec_empty(sizeof(t_token));
	p.read_input = read_input;
	p.get_symtab = get_symtab;
	p.get_last_ret = get_last_ret;
	p.data = data;
	p.last_input = str_empty();
	return (p);
}

static bool	last_tk_is_continue_nl(t_vec *tokens)
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

static t_ms_status	read_tokens(t_parser *p)
{
	char	*inp;
	t_vec	tmp_tokens;

	inp = p->read_input(false, p->data);
	str_cat(&p->last_input, cstr_view(inp));
	while (true)
	{
		if (!inp)
		{
			if (p->tokens.len == 0)
				return (MS_EOF);
			break;
		}
		tmp_tokens = tokenize(cstr_view(inp));
		DBG_PARSER(ft_putstr_fd("[DBG_PARSE] TEMP TOKENS:\n", STDERR));
		DBG_PARSER(print_all_tokens(&tmp_tokens));
		free(inp);
		if (tmp_tokens.mem_err)
			return (MS_ERROR);
		expand_vars(&tmp_tokens, p->get_symtab(p->data), p->get_last_ret(p->data));
		DBG_PARSER(ft_putstr_fd("[DBG_PARSE] TEMP TOKENS EXPANDED:\n", STDERR));
		DBG_PARSER(print_all_tokens(&tmp_tokens));
		unescape_chars(&tmp_tokens);
		DBG_PARSER(ft_putstr_fd("[DBG_PARSE] TEMP TOKENS UNESCAPED:\n", STDERR));
		DBG_PARSER(print_all_tokens(&tmp_tokens));
		vec_pushvec(&p->tokens, &tmp_tokens);
		if (p->tokens.mem_err)
		{
			vec_destroy(&tmp_tokens, NULL); // TODO
			return (MS_ERROR);
		}
		vec_destroy(&tmp_tokens, NULL);
		if (!last_tk_is_continue_nl(&p->tokens))
			break;
		else if (cstr_ref(&p->last_input)[p->last_input.len - 1] == '\\')
			str_pop(&p->last_input);
		else
			str_push(&p->last_input, ' ');
		inp = p->read_input(true, p->data);
		str_cat(&p->last_input, cstr_view(inp));
		if (((t_token *)vec_get_last(&p->tokens))->type == TK_CONTINUE_NL)
			vec_remove_last(&p->tokens);
	}
	DBG_PARSER(ft_putstr_fd("[DBG_PARSE] ALL TOKENS:\n", STDERR));
	DBG_PARSER(print_all_tokens(&p->tokens));
	tokens_normalize(&p->tokens);
	DBG_PARSER(ft_putstr_fd("[DBG_PARSE] ALL TOKENS NORMALIZED:\n", STDERR));
	DBG_PARSER(print_all_tokens(&p->tokens));
	return (MS_OK);
}

static void	str_push_ast(t_str *str, t_ast *ast, bool first)
{
	size_t	i;

	if (ast->ty == AST_OP)
	{
		if (!first)
			str_push(str, ' ');
		str_pushstr(str, cstr_view(op_str(ast->op.ty)));
		if (ast->op.arg)
		{
			str_push(str, ' ');
			str_pushstr(str, cstr_view(ast->op.arg));
		}
		return ;
	}
	i = 0;
	while (ast->cmd[i])
	{
		if (!first || i > 0)
			str_push(str, ' ');
		str_pushstr(str, cstr_view(ast->cmd[i]));
		i++;
	}
}

static void	ast_printstr(t_vec *ast)
{
	size_t	i;
	t_str	ast_line;

	i = 0;
	ast_line = str_empty();
	while (i < ast->len)
	{
		str_push_ast(&ast_line, vec_get_at(ast, i), i == 0);
		i++;
	}
	write(2, "[DBG] parsed AST: ", 18);
	write(2, cstr_ref(&ast_line), ast_line.len);
	write(2, "\n", 1);
	str_destroy(&ast_line);
}

static void	ast_printerr(t_vec *ast, size_t err_i)
{
	size_t	i;
	t_str	ast_line;
	t_str	err_line;

	i = 0;
	ast_line = str_empty();
	err_line = str_empty();
	while (i < ast->len)
	{
		if (i == err_i)
		{
			str_pushn(&err_line, ' ', ast_line.len);
			str_push_ast(&ast_line, vec_get_at(ast, i), i == 0);
			if (ast_line.len > err_line.len)
				str_push(&err_line, ' ');
			str_pushn(&err_line, '^', ast_line.len - err_line.len);
		}
		else
			str_push_ast(&ast_line, vec_get_at(ast, i), i == 0);
		i++;
	}
	str_push(&ast_line, '\n');
	str_push(&err_line, '\n');
	write(2, "minishell syntax error:\n", 24);
	write(2, cstr_ref(&ast_line), ast_line.len);
	write(2, cstr_ref(&err_line), err_line.len);
	str_destroy(&ast_line);
	str_destroy(&err_line);
}

static bool	ast_has_integrity(t_vec *ast)
{
	size_t	i;
	t_ast	*node;
	bool	ok;

	i = 0;
	ok = true;
	while (i < ast->len)
	{
		node = vec_get_at(ast, i);
		if ((node->ty == AST_OP && node->op.ty == OP_PIPE && i == 0)
			|| (node->ty == AST_OP && node->op.ty != OP_PIPE && node->op.arg == NULL))
		{
			ast_printerr(ast, i);
			ok = false;
		}
		i++;
	}
	return (ok);
}

t_ms_status	parse_next_command(t_parser *p, t_cmd_list	**out)
{
	t_vec		ast;
	t_ms_status	status;

	str_clear(&p->last_input);
	if (p->tokens.len == 0)
	{
		status = read_tokens(p);
		if (status != MS_OK)
			return (status);
	}
	if (!tokens_to_ast(&p->tokens, &ast))
	{
		vec_destroy(&p->tokens, NULL); // TODO
		vec_destroy(&ast, NULL); // TODO
		return (MS_ERROR);
	}
	if (!ast_has_integrity(&ast))
	{
		vec_destroy(&ast, NULL);
		return (MS_OK);
	}
	else
		DEBUG(ast_printstr(&ast));
	if (p->tokens.len == 0)
		vec_destroy(&p->tokens, NULL);
	*out = ast_to_commands(&ast);
	vec_destroy(&ast, NULL);
	return (MS_OK);
}
