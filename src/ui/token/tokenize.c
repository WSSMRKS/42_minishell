/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:21:21 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 18:12:05 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "tk_util.h"

/// @brief
/// @param inp
/// @param tokens
/// @return -1 for syntax error, 0 for false, 1 for true
static int	handle_quoted(t_str_slice *inp, t_vec *tokens)
{
	size_t	len;

	if (*inp->str == DOUBLE_QUO)
	{
		if (!bounded_token_len(inp->str, DOUBLE_QUO, &len))
			return (-1);
		vec_push_tk(tokens, tk_dquote(cstr_slice(inp->str, len)));
	}
	else if (*inp->str == SINGLE_QUO)
	{
		if (!bounded_token_len(inp->str, SINGLE_QUO, &len))
			return (-1);
		vec_push_tk(tokens, tk_lit(cstr_slice(inp->str, len)));
	}
	else
		return (false);
	strsl_move_inplace(inp, len);
	return (true);
}

static bool	handle_word_or_op(t_str_slice *inp, t_vec *tokens)
{
	t_str_slice	word;
	t_op_ty		op;

	word = cstr_slice(inp->str, word_len(inp->str));
	if (str_starts_with_op(*inp, &op))
	{
		vec_push_tk(tokens, tk_op(op));
		word.len = ft_strlen(op_str(op));
	}
	else if (word.len)
		vec_push_tk(tokens, tk_word(word));
	else
		return (false);
	strsl_move_inplace(inp, word.len);
	return (true);
}

/// Returns true if the remaining input string > 0
static bool	handle_space_and_comment(t_str_slice *inp, t_vec *tokens)
{
	while (*inp->str == ' ' || *inp->str == '\t' || *inp->str == '\n')
	{
		if (*inp->str == '\n')
			vec_push_tk(tokens, tk_empty(TK_NL));
		else
			vec_push_tk(tokens, tk_empty(TK_SEPERATOR));
		inp->str++;
		inp->len--;
	}
	if (tokens->len == 0
		|| ((t_token*)vec_get_last(tokens))->type == TK_NL
		|| ((t_token*)vec_get_last(tokens))->type == TK_SEPERATOR
		|| ((t_token*)vec_get_last(tokens))->type == TK_OPERATOR)
		strsl_move_inplace(inp, comment_len(inp->str));
	return (inp->len != 0);
}

// IMPORTANT FOR REPL AND NEWLINE TOKEN
// In repl have parser_state, if last token is newline,
// get another line of input and then continue parsing
// with a special merge of the tokens but without
// the newline token which was there before

/// @brief Sets the input cursor to the start of next line or the end and
/// and removes the last few gathered tokens after the last newline
/// @param tokens
/// @param err_input
static void	tokens_reset_current_line(t_vec *tokens, t_str_slice *err_input)
{
	while (tokens->len && ((t_token *)vec_get_last(tokens))->type != TK_NL)
		vec_remove_last(tokens);
	while (err_input->len && *err_input->str != '\n')
		strsl_move_inplace(err_input, 1);
}

/// @brief Tokenizes the input string.
/// @param inp The input string.
/// @param out The output vector.
/// @return false if unknown error without clearing the out vec
bool	tokenize(t_str_slice inp, t_vec *out)
{
	t_str_slice	inp_start;
	int			ok;

	inp_start = inp;
	*out = vec_empty(sizeof(t_token));
	while (handle_space_and_comment(&inp, out))
	{
		ok = handle_quoted(&inp, out);
		if (ok == 1)
			continue ;
		if (ok == -1)
		{
			span_printerr(inp_start, inp_start.len - inp.len,
				"unclosed quotes");
			tokens_reset_current_line(out, &inp);
		}
		else if (!handle_word_or_op(&inp, out))
		{
			ft_putendl_fd("minishell tokenization: error", STDERR);
			return (false);
		}
	}
	return (true);
}
