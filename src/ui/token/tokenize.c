/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:26:12 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:38:21 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	span_printerr(t_str_slice s, size_t err_i, const char *err);

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
	bool		ok;

	ok = true;
	word = cstr_slice(inp->str, word_len(*inp));
	if (str_starts_with_op(*inp, &op))
	{
		if ((op == OP_APPEND && inp->str[2] == '>')
			|| (op == OP_PIPE && inp->str[1] == '|')
			|| (op == OP_HEREDOC && inp->str[2] == '<'))
			ok = false;
		vec_push_tk(tokens, tk_op(op));
		word.len = ft_strlen(op_str(op));
	}
	else if (word.len)
		vec_push_tk(tokens, tk_word(word));
	else
		return (false);
	strsl_move_inplace(inp, word.len);
	return (ok);
}

static void	handle_space_and_comment(t_str_slice *inp, t_vec *tokens)
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
static void	tokens_reset_current_line(t_vec *tokens, t_str_slice *err_input,
	bool *syntax_err)
{
	while (tokens->len && ((t_token *)vec_get_last(tokens))->type != TK_NL)
	{
		free_token(vec_get_last(tokens));
		vec_remove_last(tokens);
	}
	while (err_input->len && *err_input->str != '\n')
		strsl_move_inplace(err_input, 1);
	*syntax_err = true;
}

/// @brief Tokenizes the input string.
/// @return false if unknown error without clearing the out vec
/// Example input and output:
///
/// You entered:
/// (mycmd "hello"world"" wooord "'mystring' with space" $HOME 'bla'>myfile)
/// tokens: 15
/// WORD: (mycmd)
/// SEP : ()
/// DQUO: (hello)
/// WORD: (world)
/// DQUO: ()
/// SEP : ()
/// WORD: (wooord)
/// SEP : ()
/// DQUO: ('mystring' with space)
/// SEP : ()
/// WORD: ($HOME)
/// SEP : ()
/// LIT : (bla)
/// OP  : (>)
/// WORD: (myfile)
bool	tokenize(t_str_slice inp, t_vec *out, bool *syntax_err)
{
	t_str_slice	inp_start;
	int			ok;

	inp_start = inp;
	*out = vec_empty(sizeof(t_token));
	while (true)
	{
		handle_space_and_comment(&inp, out);
		if (!inp.len)
			break ;
		ok = handle_quoted(&inp, out);
		if (ok == -1)
		{
			span_printerr(inp_start, inp_start.len - inp.len,
				"unclosed quotes");
			tokens_reset_current_line(out, &inp, syntax_err);
		}
		else if (ok != 1 && !handle_word_or_op(&inp, out))
		{
			span_printerr(inp_start, inp_start.len - inp.len,
				"unexpected character");
			tokens_reset_current_line(out, &inp, syntax_err);
		}
	}
	return (true);
}
