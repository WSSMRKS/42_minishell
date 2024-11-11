/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:06:08 by dkoca             #+#    #+#             */
/*   Updated: 2024/11/11 16:27:40 by kwurster         ###   ########.fr       */
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

Unquoted implicit null arguments, resulting from the expansion of parameters that have no values, are removed.

If a parameter with no value is expanded within double quotes, a null argument results and is retained and passed to a command as an empty string.
When a quoted null argument appears as part of a word whose expansion is non-null, the null argument is removed.
That is, the word -d'' becomes -d after word splitting and null argument removal.

Note that if no expansion occurs, no splitting is performed.
*/

typedef enum e_operator_ty
{
	OP_PIPE,			// CMD1 | CMD2 (PIPE)
	OP_REDIRECT,		// > ARG (OUTFILE)
	OP_INP_REDIRECT,	// < ARG (INFILE)
	OP_APPEND,			// >> ARG (APPEND)
	OP_HEREDOC			// << ARG (HEREDOC)
}	t_operator_ty;

typedef enum e_token_ty
{
	TOKEN_SEPERATOR,
	TOKEN_WORD,
	TOKEN_LITERAL,
	TOKEN_DQUOTE,
	TOKEN_OPERATOR,
	TOKEN_CONTINUE_NL,
	TOKEN_NL,
}	t_token_ty;

typedef struct s_token
{
	union {
		t_str			str;
		t_operator_ty	op;
	};
	t_token_ty type;
}	t_token;

typedef enum	e_node_type {
	NODE_COMMAND,
	NODE_OPERATOR
}	t_node_type;

typedef struct	s_cmd_node {
	char		*command;
	char		**args;
}	t_cmd_node;

typedef struct	s_op_node {
	t_operator_ty	operator;
	char			*arg;
}	t_op_node;

/// @brief generic AST node holding either a command or an operator.
typedef struct s_ast_node {
	t_node_type			ty;
	union {
		t_cmd_node		command;
		t_op_node		operator;
	};
}	t_ast_node;

t_vec	tokenize(t_str_slice inp);
void	expand_vars(t_vec *tokens, t_symtab_stack *st);
void	unescape_chars(t_vec *tokens);
void	tokens_normalize(t_vec *tokens);

t_token	tk_word(t_str_slice word);
t_token	tk_op(t_operator_ty op);
t_token	tk_lit(t_str_slice quoted);
t_token	tk_dquote(t_str_slice quoted);
void	vec_push_tk(t_vec *vec, t_token tk);

void	strsl_trim_start_delim(t_str_slice *s);
size_t	bounded_token_len(const char *str, char open, char close, size_t *out);
size_t	word_len(const char *str, size_t *out);
size_t	var_len(const char *str, size_t *out);
bool	str_is_operator(t_str_slice str, t_operator_ty *out);
bool	str_starts_with_op(t_str_slice str, t_operator_ty *out);
void	token_print(const t_token *token, int fd);
char	*op_str(t_operator_ty op);

#endif
