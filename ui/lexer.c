/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:07:52 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/26 08:26:36 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_not_end(const char *itr)
{
	itr++;
	if (*itr != '\0' && *itr != '\n')
		return (TRUE);
	return (FALSE);
}

int lookahead(const char *chr_itr)
{
	chr_itr++;
	return (*chr_itr);	
}

int tokenize_operator(char *chr_itr, t_token *prev_token)
{
	t_token *token;
	
	if (*chr_itr == '(')
		token = add_token(chr_itr, TOKEN_LPAREN, 1, &prev_token);
	else if (*chr_itr == ')')
		token = add_token(chr_itr, TOKEN_RPAREN, 1, &prev_token);
	else if (*chr_itr == '|')
		token = add_token(chr_itr, TOKEN_PIPE, 1, &prev_token);
	else if (*chr_itr == '>')
		token = add_token(chr_itr, TOKEN_IO_OUT, 1, &prev_token);
	else if (*chr_itr == '<')
		token = add_token(chr_itr, TOKEN_IO_IN, 1, &prev_token);
	else if (*chr_itr == '>>')
		token = add_token(chr_itr, TOKEN_RPAREN, 1, &prev_token);
	return (token);
}

t_token *scan(int c, char *chr_itr, t_token *prev_token)
{
	t_token token;
	
	if (ft_strchr("|<>()", c))
		// tokenize_operator
	else
		//tokenize_word
}

int tokenizer(char *line)
{
	t_token *new_tok;
	t_token *prev_tok;
	char *chr_itr;
	int cur_char;
	
	ft_strtrim(line, " \t");
	chr_itr = line;
	prev_tok = NULL;
	while (is_not_end(chr_itr))
	{
		// skip spaces
		cur_char = lookahead(chr_itr);
		// new_tok = scan(prev_tok)
		prev_tok = new_tok;
	}
	
	
	//start of lexical analysis, find out type and create token
}