/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:07:52 by dkoca             #+#    #+#             */
/*   Updated: 2024/09/14 18:09:36 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/* tokenizes operator and consumes used chars*/
t_token *tokenize_operator(char **cur_ptr, char cur_chr, t_token *prev_token)
{
	t_token *token;

	token = NULL;	
	if (cur_chr == '|')
		token = get_token(*cur_ptr, TOKEN_PIPE, 1, &prev_token);
	else if (ft_strncmp(*cur_ptr, ">>", 2) == 0)
		token = get_token(*cur_ptr, TOKEN_APPEND, 2, &prev_token);
	else if (ft_strncmp(*cur_ptr, "<<", 2) == 0)
		token = get_token(*cur_ptr, TOKEN_HEREDOC, 2, &prev_token);
	else if (cur_chr == '>')
		token = get_token(*cur_ptr, TOKEN_IO_OUT, 1, &prev_token);
	else if (cur_chr == '<')
		token = get_token(*cur_ptr, TOKEN_IO_IN, 1, &prev_token);
	*cur_ptr += token->cmd.len;
	return (token);
}

t_token *scan_word(char **chr_itr, t_token *prev_token)
{
	t_token *new_token;
	char *start;
	int len;
	
	if (chr_itr == NULL || *chr_itr == NULL)
		return (NULL);
	new_token = NULL;
	start = *chr_itr;
	len = 0;
	while ((!is_end(*chr_itr)) && is_word(**chr_itr))
	{
		(*chr_itr)++;
		len++;
	}
	if (len > 0 && !is_end(start))
		new_token = get_token(start, TOKEN_WORD, len, &prev_token);	
	return (new_token);
}

t_token *tokenize_word(char **chr_itr, t_token *prev_token)
{
	t_token *token;

	token = NULL;
	token = has_single_quotes(chr_itr, prev_token);
	if (!token && chr_itr && !is_end(*chr_itr))
		token = has_double_quotes(chr_itr, prev_token);
	if (!token && chr_itr && !is_end(*chr_itr))
		token = scan_word(chr_itr, prev_token);
	return (token);
}

t_token *scan(char **cmd, t_token *prev_token)
{
	t_token *token;
	char cur;
	
	if (*cmd == NULL)
		return (NULL);
	cur = **cmd;
	token = NULL;
	if (cur && ft_strchr("|<>", cur))
		token = tokenize_operator(cmd, cur, prev_token);
	else
	{
		token = tokenize_word(cmd, prev_token);
	}
	return (token);
}

int tokenizer(char *line, t_token **tokens)
{
	t_token *new_tok;
	t_token *prev_tok;
	char	*cmd;

	ft_strtrim(line, " \t");
	cmd = line;
	prev_tok = NULL;
	*tokens = prev_tok;
	while (!is_end(cmd))
	{
		new_tok = NULL;
		skip_whitespace_between_words(&cmd);
		if (is_end(cmd) || *cmd == '\n')
			break;
		new_tok = scan(&cmd, prev_tok);
		print_token(new_tok);
		if (prev_tok == NULL && new_tok)
			*tokens = new_tok;
		prev_tok = new_tok;
	}
	return (EXIT_SUCCESS);
}
