/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:07:52 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/31 15:03:54 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_end(char *chr_itr)
{
	if (chr_itr != NULL && *chr_itr != '\0')
		return (FALSE);
	return (TRUE);
}

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

int is_quoted(int first_char, int quote)
{
	if (first_char == quote)
		return (TRUE);
	else
		return (FALSE);
}

t_token *has_single_quotes(char **chr_itr, t_token *prev_token)
{
	t_token *new_token;
	char *start;
	int len;

	new_token = NULL;
	start = NULL;
	len = 0;
	printf("s quote str = %s\n", *chr_itr);
		// has_backslash = FALSE;
	if (!is_quoted(**chr_itr, '\"') || ft_strncmp(*chr_itr, "\\\'", 2))
		return (NULL);
	// if (ft_strncmp(*chr_itr, "\\\'", 2) == 0)
		// ++(*chr_itr);
	if (!is_quoted(**chr_itr, '\''))
		return (NULL);
	start = ++(*chr_itr);
	while (!is_end(*chr_itr))
	{
		if (**chr_itr == '\'')
		{
			(*chr_itr)++;
			break;
		}
		(*chr_itr)++;
		len++;
	}
	if (len > 0 && !is_end(start))
	{
		if (ft_strchr(start, '\''))
			new_token = get_token(start, TOKEN_WORD_SQUOTE, len, &prev_token);
		else if (start == NULL && !ft_strchr(start, '\''))
			new_token = get_token(start, TOKEN_ERR, len, &prev_token);
	}
	return (new_token);
}


t_token *has_double_quotes(char **chr_itr, t_token *prev_token)
{
	t_token *new_token;
	char *start;
	int len;
	// int has_backslash;

	new_token = NULL;
	start = NULL;
	len = 0;
	// has_backslash = FALSE;
	if (!is_quoted(**chr_itr, '\"') || ft_strncmp(*chr_itr, "\\\"", 2))
		return (NULL);
	if (ft_strncmp(*chr_itr, "\\\"", 2) == 0)
		++(*chr_itr);
	start = ++(*chr_itr);
	while (!is_end(*chr_itr))
	{
		if (**chr_itr == '\"')
		{
			(*chr_itr)++;
			break;
		}
		(*chr_itr)++;
		len++;
	}
	if (len > 0 && !is_end(start))
	{
		if (ft_strchr(start, '\"'))
			new_token = get_token(start, TOKEN_WORD_DQUOTE, len, &prev_token);
		else if (start == NULL && !ft_strchr(start, '\"'))
			new_token = get_token(start, TOKEN_ERR, len, &prev_token);
	}
	return (new_token);
}

int is_word(int cur_char)
{
	if (!ft_isspace(cur_char) && !ft_strchr("|<>;", cur_char))
		return (TRUE);
	return (FALSE);	
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
		++(*chr_itr);
		len++;
	}
	if (len > 0)
		new_token = get_token(start, TOKEN_WORD, len, &prev_token);	
	return (new_token);
}

t_token *tokenize_word(char **chr_itr, t_token *prev_token)
{
	t_token *token;

	token = NULL;
	printf("str = %s\n", *chr_itr);
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


void skip_whitespace_between_words(char **cmd)
{
	char cur;

	cur = **cmd;
	while (!is_end(*cmd)&& cur == ' ')
	{
		(*cmd)++;
		cur = **cmd;
	}
}

void print_token(t_token *token);

int tokenizer(char *line)
{
	t_token *new_tok;
	t_token *prev_tok;
	char	*cmd;

	ft_strtrim(line, " \t");
	cmd = line;
	prev_tok = NULL;
	while (!is_end(cmd))
	{
		new_tok = NULL;
		skip_whitespace_between_words(&cmd);
		if (is_end(cmd) || *cmd == '\n')
			break;
		new_tok = scan(&cmd, prev_tok);
		print_token(new_tok);
		prev_tok = new_tok;
	}
	return (EXIT_SUCCESS);
}


void print_token(t_token *token)
{
	size_t i;
	if (token)
	{
		for (i = 0; i < token->cmd.len; i++)
		{
			printf("%c", token->cmd.start[i]);
		}
	}
	printf("\n");
}