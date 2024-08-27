/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:06:08 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/27 09:16:52 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	TOKENIZATION_H
# define	TOKENIZATION_H

#include "minishell.h"

// int current_command_line_count;

// /* The number of lines in a command saved while we run parse_and_execute */
// int saved_command_line_count;

// /* The token that currently denotes the end of parse. */
// int shell_eof_token;

// /* The token currently being read. */
// int current_token;

// int last_was_backslash;

typedef enum e_token_type
{
	TOKEN_ERR,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_IO_IN,
	TOKEN_IO_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SUBSHELL
}	t_token_type;

typedef struct  s_tok_span
{
	char *start;
	size_t len;
} t_tok_span;


typedef struct s_token
{
	t_token_type type;
	t_tok_span cmd;
	// int quoted;
	struct s_token *next;
}	t_token;

/******** FUNCTIONS *********/
t_token *add_token(char *content, int type, int len, t_token **prev_next_ptr);
int tokenizer(char *line);
#endif