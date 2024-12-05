/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:21:21 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 17:57:52 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "util.h"

// TODO remove (debug only)
void	print_all_tokens(t_vec *tokens);

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

static t_ms_status	add_tokens_to_parser(t_parser *p)
{
	(void)p;
	return (MS_ERROR);
}

// DBG_PARSER(ft_putstr_fd("[DBG_PARSE] TEMP TOKENS:\n", STDERR));
// DBG_PARSER(print_all_tokens(&tmp_tokens));
// DBG_PARSER(ft_putstr_fd("[DBG_PARSE] TEMP TOKENS EXPANDED:\n", STDERR));
// DBG_PARSER(print_all_tokens(&tmp_tokens));
// DBG_PARSER(ft_putstr_fd("[DBG_PARSE] TEMP TOKENS UNESCAPED:\n", STDERR));
// DBG_PARSER(print_all_tokens(&tmp_tokens));
// This function is called if there are no leftover tokens in the parser
static t_ms_status	read_tokens(t_parser *p)
{
	char	*inp;
	t_vec	tmp_tokens;

	inp = p->read_input(false, p->data);
	str_cat(&p->last_input, cstr_view(inp));
	if (!inp)
		return (MS_EOF);
	if (!tokenize(cstr_view(inp), &tmp_tokens))
	{
		// TODO handle error
	}
	free(inp);
	if (tmp_tokens.mem_err)
		return (MS_ERROR);
	expand_vars(&tmp_tokens, p->get_stab(p->data), p->get_last_ret(p->data));
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
	else if (cstr_ref(&p->last_input)[p->last_input.len - 1] == '\\')
		str_pop(&p->last_input);
	ft_putendl_fd("minishell syntax error:", STDERR);
	ft_putendl_fd("Multiline commands (e.g. via line continuation)"
	" are unsupported", STDERR);
	vec_clear(&p->tokens);
	str_clear(&p->last_input);
	inp = p->read_input(false, p->data);
	str_cat(&p->last_input, cstr_view(inp));
	DBG_PARSER(ft_putstr_fd("[DBG_PARSE] ALL TOKENS:\n", STDERR));
	DBG_PARSER(print_all_tokens(&p->tokens));
	tokens_normalize(&p->tokens);
	DBG_PARSER(ft_putstr_fd("[DBG_PARSE] ALL TOKENS NORMALIZED:\n", STDERR));
	DBG_PARSER(print_all_tokens(&p->tokens));
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
