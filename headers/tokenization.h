/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:06:08 by dkoca             #+#    #+#             */
/*   Updated: 2024/09/10 20:52:38 by dkoca            ###   ########.fr       */
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

typedef enum e_operator_ty
{
	OP_PIPE,
	OP_REDIRECT,
	OP_INP_REDIRECT,
	OP_APPEND,
	OP_HEREDOC
}	t_operator_ty;

typedef enum e_token_ty
{
	TOKEN_SEPERATOR,
	TOKEN_WORD,
	TOKEN_LITERAL,
	TOKEN_DQUOTE,
	TOKEN_OPERATOR,
}	t_token_ty;

typedef struct s_token
{
	union {
		t_str			str;
		t_operator_ty	op;
	};
	t_token_ty type;
}	t_token;

t_token	tk_sep();
t_token	tk_word(t_str_slice word);
t_token	tk_op(t_operator_ty op);
t_token	tk_lit(t_str_slice quoted);
t_token	tk_dquote(t_str_slice quoted);
void	vec_push_tk(t_vec *vec, t_token tk);

size_t	bounded_token_len(const char *str, char open, char close, size_t *out);
size_t	word_len(const char *str, size_t *out);
t_bool	str_is_operator(t_str_slice str, t_operator_ty *out);


/******** FUNCTIONS *********/
t_token *get_token(char *content, int type, int len, t_token **prev_next_ptr);
int tokenizer(char *line, t_token **tokens);
void skip_whitespace_between_words(char **cmd);
int is_word(int cur_char);
int is_quoted(int first_char, int quote);
int is_end(char *chr_itr);
t_token *has_single_quotes(char **chr_itr, t_token *prev_token);
t_token *has_double_quotes(char **chr_itr, t_token *prev_token);

/* DEBUG*/
void print_token(t_token *token);


#endif
