/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:06:08 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 17:57:52 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	TOKENIZATION_H
# define	TOKENIZATION_H

#include "../headers/minishell.h"

// int current_command_line_count;

// /* The number of lines in a command saved while we run parse_and_execute */
// int saved_command_line_count;

// /* The token that currently denotes the end of parse. */
// int shell_eof_token;

// /* The token currently being read. */
// int current_token;

// int last_was_backslash;


// {"&", 1},
// {";", 1},
// {"&&", 2},
// {"||", 2},

/*
Explicit null arguments ("" or '') are retained and passed to commands as empty strings.

Unquoted implicit null arguments, resulting from the expansion of parameters that have no vals, are removed.

If a parameter with no val is expanded within double quotes, a null argument results and is retained and passed to a command as an empty string.
When a quoted null argument appears as part of a word whose expansion is non-null, the null argument is removed.
That is, the word -d'' becomes -d after word splitting and null argument removal.

Note that if no expansion occurs, no splitting is performed.
*/

# define SINGLE_QUO '\''
# define DOUBLE_QUO '"'

typedef enum e_op_ty
{
	OP_PIPE,			// CMD1 | CMD2 (PIPE)
	OP_REDIRECT,		// > ARG (OUTFILE)
	OP_INP_REDIRECT,	// < ARG (INFILE)
	OP_APPEND,			// >> ARG (APPEND)
	OP_HEREDOC			// << ARG (HEREDOC)
}	t_op_ty;

typedef enum e_token_ty
{
	TK_SEPERATOR,		// space or tab
	TK_WORD,			// string
	TK_LITERAL,			// 'string'
	TK_DQUOTE,			// "string"
	TK_OPERATOR,		// | > < >> <<
	TK_CONTINUE_NL,		// \ (indicating line continuation) -- UNSUPPORTED
	TK_NL,				// \n (indicating another command following)
}	t_token_ty;

typedef struct s_token
{
	union {
		t_str	str;
		t_op_ty	op;
	};
	t_token_ty	type;
}				t_token;

typedef enum	e_ast_ty {
	AST_CMD,
	AST_OP
}	t_ast_ty;

typedef struct	s_op {
	t_op_ty	ty;
	char	*arg;
}			t_op;

/// @brief generic AST node holding either a command or an operator.
typedef struct s_ast {
	t_ast_ty			ty;
	union {
		char		**cmd;
		t_op		op;
	};
}	t_ast;

bool		tokenize(t_str_slice inp, t_vec *out);
void		expand_vars(t_vec *tokens, t_stab_st *st, int last_ret);
void		unescape_chars(t_vec *tokens);
void		tokens_normalize(t_vec *tokens);
void		tokens_normalize_for_continue_nl_check(t_vec *tokens);
bool		tokens_to_ast(t_vec *tokens, t_vec *out);
t_cmd_list	*ast_to_commands(t_vec *ast);

void		free_token(void *token);

#endif
