#include "../../../headers/minishell.h"

void	parser_destroy(t_parser *p)
{
	vec_destroy(&p->tokens, NULL);
	str_destroy(&p->last_input);
}

t_parser	parser_init(void *data, t_read_input read_input, t_get_symtab get_symtab)
{
	t_parser	p;

	p.tokens = vec_empty(sizeof(t_token));
	p.read_input = read_input;
	p.get_symtab = get_symtab;
	p.data = data;
	p.last_input = str_empty();
	return (p);
}

static bool	last_tk_is_continue_nl(t_vec *tokens)
{
	t_token	*last;

	if (tokens->len == 0)
		return (false);
	last = vec_get_last(tokens);
	return (last->type == TK_CONTINUE_NL);
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
		free(inp);
		if (tmp_tokens.mem_err)
			return (MS_ERROR);
		expand_vars(&tmp_tokens, p->get_symtab(p->data));
		unescape_chars(&tmp_tokens);
		vec_pushvec(&p->tokens, &tmp_tokens);
		if (p->tokens.mem_err)
		{
			vec_destroy(&tmp_tokens, NULL); // TODO
			return (MS_ERROR);
		}
		vec_destroy(&tmp_tokens, NULL);
		if (!last_tk_is_continue_nl(&p->tokens))
			break;
		else
			str_pop(&p->last_input);
		inp = p->read_input(true, p->data);
		str_cat(&p->last_input, cstr_view(inp));
		((t_token *)vec_get_last(&p->tokens))->type = TK_SEPERATOR;
	}
	tokens_normalize(&p->tokens);
	return (MS_OK);
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
	if (p->tokens.len == 0)
		vec_destroy(&p->tokens, NULL);
	*out = ast_to_commands(&ast);
	vec_destroy(&ast, NULL);
	return (MS_OK);
}
