/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:25:43 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 12:04:22 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include <stdbool.h>

bool	ast_has_integrity(t_parser *p, t_vec *ast);

void	parser_destroy(t_parser *p)
{
	vec_destroy(&p->tokens, free_token);
	str_destroy(&p->last_input);
}

t_parser	parser_init(void *data, t_read_input read_input,
	t_get_stab get_stab, t_get_last_ret get_last_ret)
{
	t_parser	p;

	p.tokens = vec_empty(sizeof(t_token));
	p.read_input = read_input;
	p.get_stab = get_stab;
	p.get_last_ret = get_last_ret;
	p.data = data;
	p.last_input = str_empty();
	return (p);
}

static bool	add_tokens(t_parser *p, char *inp)
{
	t_vec	tmp_tokens;
	bool	syntax_err;
	bool	parse_err;

	syntax_err = false;
	parse_err = !tokenize(cstr_view(inp), &tmp_tokens, &syntax_err);
	free(inp);
	if (tmp_tokens.mem_err)
		return (false);
	if (syntax_err || parse_err)
		((t_ms *)p->data)->be->last_ret = 2;
	if (parse_err)
		return (true);
	expand_vars(&tmp_tokens, p->get_stab(p->data), p->get_last_ret(p->data));
	unescape_chars(&tmp_tokens);
	vec_pushvec(&p->tokens, &tmp_tokens);
	if (p->tokens.mem_err)
	{
		vec_destroy(&tmp_tokens, free_token);
		return (false);
	}
	vec_destroy(&tmp_tokens, NULL);
	tokens_normalize(&p->tokens);
	return (true);
}

static t_ms_status	read_tokens(t_parser *p)
{
	char	*inp;

	inp = p->read_input(false, p->data);
	str_cat(&p->last_input, cstr_view(inp));
	if (!inp)
	{
		if (p->tokens.len == 0)
			return (MS_EOF);
		return (MS_OK);
	}
	add_tokens(p, inp);
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
		vec_destroy(&p->tokens, free_token);
		vec_destroy(&ast, free_ast);
		return (MS_ERROR);
	}
	if (!ast_has_integrity(p, &ast))
		return (MS_OK);
	if (p->tokens.len == 0)
		vec_destroy(&p->tokens, free_token);
	*out = ast_to_commands(&ast);
	vec_destroy(&ast, free_ast);
	return (MS_OK);
}
