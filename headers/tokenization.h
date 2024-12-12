/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:06:08 by dkoca             #+#    #+#             */
/*   Updated: 2024/12/12 12:00:02 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "../headers/minishell.h"

# define SINGLE_QUO 39
# define DOUBLE_QUO 34

typedef enum e_op_ty
{
	OP_PIPE,
	OP_REDIRECT,
	OP_INP_REDIRECT,
	OP_APPEND,
	OP_HEREDOC
}	t_op_ty;

typedef enum e_token_ty
{
	TK_SEPERATOR,
	TK_WORD,
	TK_LITERAL,
	TK_DQUOTE,
	TK_OPERATOR,
	TK_CONTINUE_NL,
	TK_NL,
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

bool		tokenize(t_str_slice inp, t_vec *out, bool *syntax_err);
void		expand_vars(t_vec *tokens, t_stab_st *st, int last_ret);
bool		char_is_escaped(const char *str, size_t i);
void		unescape_chars(t_vec *tokens);
void		tokens_normalize(t_vec *tokens);
void		tokens_normalize_for_continue_nl_check(t_vec *tokens);
bool		tokens_to_ast(t_vec *tokens, t_vec *out);
t_cmd_list	*ast_to_commands(t_vec *ast);
void		free_token(void *token);
void		free_ast(void *ast_node);

t_token		tk_empty(t_token_ty ty);
t_token		tk_word(t_str_slice word);
t_token		tk_op(t_op_ty op);
t_token		tk_lit(t_str_slice quoted);
t_token		tk_dquote(t_str_slice quoted);
void		vec_push_tk(t_vec *vec, t_token tk);
bool		token_has_str(t_token *token);
void		strsl_trim_start_delim(t_str_slice *s);
size_t		bounded_token_len(const char *str, char bounds, size_t *out);
size_t		word_len(t_str_slice s);
size_t		comment_len(const char *str);
size_t		var_len(const char *str, size_t *out);
bool		str_is_operator(t_str_slice str, t_op_ty *out);
bool		str_starts_with_op(t_str_slice str, t_op_ty *out);
void		token_print(const t_token *token, int fd);
const char	*op_str(t_op_ty op);
void		ast_print(const t_ast *ast, int fd);

#endif
