/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:07:52 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/26 12:30:13 by dkoca            ###   ########.fr       */
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

int lookahead(const char *chr_itr, char *start)
{
	if (start - chr_itr == 0)
		return (chr_itr);
	chr_itr++;
	return (*chr_itr);	
}

/* tokenizes operator and consumes used chars*/
int tokenize_operator(char **chr_itr, t_token *prev_token)
{
	t_token *token;
	
	if (**chr_itr == '(')
		token = add_token(*chr_itr, TOKEN_LPAREN, 1, &prev_token->next);
	else if (**chr_itr == ')')
		token = add_token(*chr_itr, TOKEN_RPAREN, 1, &prev_token->next);
	else if (**chr_itr == '|')
		token = add_token(*chr_itr, TOKEN_PIPE, 1, &prev_token->next);
	else if (ft_strncmp(*chr_itr, ">>", 2) == 0)
		token = add_token(*chr_itr, TOKEN_APPEND, 2, &prev_token->next);
	else if (ft_strncmp(*chr_itr, "<<", 2) == 0)
		token = add_token(*chr_itr, TOKEN_HEREDOC, 2, &prev_token->next);
	else if (**chr_itr == '>')
		token = add_token(*chr_itr, TOKEN_IO_OUT, 1, &prev_token->next);
	else if (**chr_itr == '<')
		token = add_token(*chr_itr, TOKEN_IO_IN, 1, &prev_token->next);
	*chr_itr += token->cmd.len;
	return (token);
}

t_token *tokenize_word(char **chr_itr, t_token *prev_token)
{
	t_token *token;
	
	// check for double and single quotes
	return (token);
}

t_token *scan(int c, char *chr_itr, t_token *prev_token)
{
	t_token *token;
	
	if (ft_strchr("|<>()", c))
		token = tokenize_operator(&chr_itr, prev_token);
	else
		//tokenize_word
	return (token);
}

void skip_whitespace_between_words(char **chr_itr)
{
	while (**chr_itr != '\0' && ft_isspace(**chr_itr) && **chr_itr != '\n')
		*chr_itr++;
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
		skip_whitespace_between_words(&chr_itr);
		if (!is_not_end(chr_itr))
			break;
		cur_char = lookahead(chr_itr, line);
		// new_tok = scan(prev_tok)
		prev_tok = new_tok;
	}
	
	
	//start of lexical analysis, find out type and create token
}