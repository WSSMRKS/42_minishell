/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:06:08 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/25 05:23:24 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	TOKENIZATION_H
# define	TOKENIZATION_H

#include "minishell.h"

typedef enum e_token_type
{
	TOKEN_ERR,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_IO_IN,
	TOKEN_IO_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
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
	struct s_token *next;
}	t_token;

#endif