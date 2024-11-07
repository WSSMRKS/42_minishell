#include "../../../headers/minishell.h"
#include <stdio.h>

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

t_bool	handle_quoted(t_str_slice *inp, t_vec *tokens)
{
	size_t	len;

	if (bounded_token_len(inp->str, '"', '"', &len))
		vec_push_tk(tokens, tk_dquote(cstr_slice(inp->str, len)));
	else if (bounded_token_len(inp->str, '\'', '\'', &len))
		vec_push_tk(tokens, tk_lit(cstr_slice(inp->str, len)));
	else
		return (FALSE);
	strsl_move_inplace(inp, len);
	return (TRUE);
}

t_bool	handle_word_or_op(t_str_slice *inp, t_vec *tokens)
{
	t_str_slice		word;
	t_operator_ty	op;

	word = cstr_slice(inp->str, word_len(inp->str, 0));
	if (str_is_operator(word, &op))
		vec_push_tk(tokens, tk_op(op));
	else if (word.len)
		vec_push_tk(tokens, tk_word(word));
	else
		return (FALSE);
	strsl_move_inplace(inp, word.len);
	return (TRUE);
}

// Tokenize input
// Expand Env vars
// Detokenize into commands/arguments and operators

/// @brief Tokenizes the input string.
/// @param inp The input string.
/// @return A vector of tokenized strings (t_token).
/// Example input and output:
/// mycmd "hello"world"" wooord "'mystring'" $HOME 'bla'>myfile
/// -> [word(mycmd), sep(), dquote(hello), word(world), dquote(),
///		sep(), word(wooord), sep(), dquote('mystring'),
///		sep(), word($HOME), sep(), literal(bla), operator(redir), word(myfile)]
t_vec	tokenize(t_str_slice inp)
{
	t_vec	out;

	out = vec_empty(sizeof(t_token));
	while (TRUE)
	{
		if (ft_isspace(*inp.str))
		{
			vec_push_tk(&out, tk_sep());
			strsl_trim_start_inplace(&inp);
		}
		if (!inp.len)
			break ;
		if (handle_quoted(&inp, &out) || handle_word_or_op(&inp, &out))
			continue ;
		perror("tokenize error");
		break ;
	}
	return (out);
}
