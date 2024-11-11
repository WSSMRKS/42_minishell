#include "../../../headers/minishell.h"

/* ??????????????????????
```bash
$ echo "hello"world""
helloworld

$ echo hello"world"
helloworld

$ echo hello"world
>

$ echo "hello"world
helloworld

$ echo hello"world"hey
helloworldhey

$ echo hello'world'hey
helloworldhey

$ ./pargs my 1 "very" "'complex'" "sentence" and multi tests" sentence end"? 'no no "nooo"'
argc: 10
argv[0]: ./pargs
argv[1]: my
argv[2]: 1
argv[3]: very
argv[4]: 'complex'
argv[5]: sentence
argv[6]: and
argv[7]: multi
argv[8]: tests sentence end?
argv[9]: no no "nooo"
```
*/

static bool	handle_quoted(t_str_slice *inp, t_vec *tokens)
{
	size_t	len;

	if (bounded_token_len(inp->str, '"', '"', &len))
		vec_push_tk(tokens, tk_dquote(cstr_slice(inp->str, len)));
	else if (bounded_token_len(inp->str, '\'', '\'', &len))
		vec_push_tk(tokens, tk_lit(cstr_slice(inp->str, len)));
	else
		return (false);
	strsl_move_inplace(inp, len);
	return (true);
}

static bool	handle_word_or_op(t_str_slice *inp, t_vec *tokens)
{
	t_str_slice		word;
	t_operator_ty	op;

	word = cstr_slice(inp->str, word_len(inp->str, 0));
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

static void	handle_whitespace(t_str_slice *inp, t_vec *tokens)
{
	while (*inp->str == ' ' || *inp->str == '\t' || *inp->str == '\n')
	{
		if (*inp->str == '\n')
			vec_push_tk(tokens, (t_token){.type = TOKEN_NL});
		else
			vec_push_tk(tokens, (t_token){.type = TOKEN_SEPERATOR});
		inp->str++;
		inp->len--;
	}
}

// IMPORTANT FOR REPL AND NEWLINE TOKEN
// In repl have parser_state, if last token is newline,
// get another line of input and then continue parsing
// with a special merge of the tokens but without
// the newline token which was there before

/// @brief Tokenizes the input string.
/// @param inp The input string.
/// @return A vector of tokenized strings (t_token).
/// Example input and output:
///
/// You entered: (mycmd "hello"world"" wooord "'mystring' with space" $HOME 'bla'>myfile)
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
t_vec	tokenize(t_str_slice inp)
{
	t_vec	out;

	out = vec_empty(sizeof(t_token));
	while (true)
	{
		handle_whitespace(&inp, &out);
		if (!inp.len)
			break ;
		if (handle_quoted(&inp, &out) || handle_word_or_op(&inp, &out))
			continue ;
		perror("tokenize error");
		break ;
	}
	return (out);
}
