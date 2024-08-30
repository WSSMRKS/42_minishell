/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:07:52 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/30 15:50:21 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int lookahead(t_cmd *cmd, int pos)
// {
// 	if (cmd->chr_itr == NULL)
// 		return (EOF);
// 	if (pos == PEEK_START)
// 		return (*(cmd->chr_itr));
// 	pos++;
// 	printf("pos in peek = %i\n", pos);
// 	return (cmd->chr_itr[pos]);
// }

int is_not_end(char *chr_itr)
{
	// printf("cur str = %s, c = %i\n", chr_itr, *chr_itr);
	if (chr_itr == NULL && *chr_itr == '\0')
		return (FALSE);
	return (TRUE);
}

/* tokenizes operator and consumes used chars*/
t_token *tokenize_operator(char **cur_ptr, char cur_chr, t_token *prev_token)
{
	t_token *token;

	token = NULL;	
	printf("cur char = %c\n", **cur_ptr);
	if (cur_chr == '|')
		token = add_token(*cur_ptr, TOKEN_PIPE, 1, &prev_token);
	else if (ft_strncmp(*cur_ptr, ">>", 2) == 0)
		token = add_token(*cur_ptr, TOKEN_APPEND, 2, &prev_token);
	else if (ft_strncmp(*cur_ptr, "<<", 2) == 0)
		token = add_token(*cur_ptr, TOKEN_HEREDOC, 2, &prev_token);
	else if (cur_chr == '>')
		token = add_token(*cur_ptr, TOKEN_IO_OUT, 1, &prev_token);
	else if (cur_chr == '<')
		token = add_token(*cur_ptr, TOKEN_IO_IN, 1, &prev_token);
	*cur_ptr += token->cmd.len;
	return (token);
}

t_token *has_single_quotes(char **chr_itr, t_token *prev_token)
{
	t_token *new_token;
	char *start;
	int len;

	new_token = NULL;
	start = NULL;
	len = 0;
	if (**chr_itr == '\'')
		(*chr_itr)++;
	else
		return (NULL);
	if (is_not_end(*chr_itr))
		start = *chr_itr;
	while (start != NULL && (**chr_itr != '\0' || **chr_itr != '\n'))
	{
		if (**chr_itr == '\'')
		{
			(*chr_itr)++;
			break;
		}
		(*chr_itr)++;
		len++;
	}
	if (len > 0)
	{
		if (ft_strchr(start, '\''))
			new_token = add_token(start, TOKEN_WORD, len, &prev_token);
		else if (start == NULL && !ft_strchr(start, '\''))
			new_token = add_token(start, TOKEN_ERR, len, &prev_token);
	}
	return (new_token);
}

t_token *has_double_quotes(char **chr_itr, t_token *prev_token)
{
	t_token *new_token;
	char *start;
	int len;

	new_token = NULL;
	start = NULL;
	len = 0;
	if (**chr_itr == '\"')
		(*chr_itr)++;
	else
		return (NULL);
	if (is_not_end(*chr_itr))
		start = *chr_itr;
	while (start != NULL && (**chr_itr != '\0' || **chr_itr != '\n'))
	{
		if (**chr_itr == '\"')
		{
			(*chr_itr)++;
			break;
		}
		(*chr_itr)++;
		len++;
	}
	if (len > 0)
	{
		if (ft_strchr(start, '\"'))
			new_token = add_token(start, TOKEN_WORD, len, &prev_token);
		else if (start == NULL && !ft_strchr(start, '\"'))
			new_token = add_token(start, TOKEN_ERR, len, &prev_token);
	}
	return (new_token);
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
	printf("cur str = %s\n", *chr_itr);
	printf("Initial pointer address: %p\n", (void *)*chr_itr);
	// printf("one more pointer address: %p\n", (void *)*chr_itr);
	int i = 0;
	while ( i < 1 && (**chr_itr != '\0' || **chr_itr != '\n') && !ft_isspace(**chr_itr))
	{
		printf("one more pointer address: %p\n", (void *)*chr_itr);
		++(*chr_itr);
		len++;
		i++;
	}
	if (len > 0)
		new_token = add_token(start, TOKEN_WORD, len, &prev_token);	
	return (new_token);
}

t_token *tokenize_word(char **chr_itr, t_token *prev_token)
{
	t_token *token;

	token = NULL;
	printf("chr itr 0 = %s\n", *chr_itr);
	token = has_single_quotes(chr_itr, prev_token);
	printf("chr itr 1 = %s\n", *chr_itr);
	if (!token && chr_itr && is_not_end(*chr_itr))
		token = has_double_quotes(chr_itr, prev_token);
	printf("chr itr 2 = %s\n", *chr_itr);
	if (!token && chr_itr && is_not_end(*chr_itr))
		token = scan_word(chr_itr, prev_token);
	
	// check for double and single quotes
	return (token);
}

t_token *scan(t_cmd *cmd, t_token *prev_token)
{
	t_token *token;
	char cur;
	
	if (cmd->chr_itr == NULL)
		return (NULL);
	cur = *cmd->chr_itr;
	token = NULL;
	printf("chr itr = %c\n", *cmd->chr_itr);
	if (cur && ft_strchr("|<>", cur))
		token = tokenize_operator(&cmd->chr_itr, cur, prev_token);
	else
		token = tokenize_word(&cmd->chr_itr, prev_token);
	return (token);
}


void skip_whitespace_between_words(t_cmd *cmd)
{
	char cur;
	char **skip;
	
	skip = &cmd->chr_itr;
	cur = *cmd->chr_itr;
	printf("before moving %p\n", cmd->chr_itr);
	printf("before spaces %s\n", cmd->chr_itr);
	while (is_not_end(cmd->chr_itr) && cur != '\n' && cur == ' ')
	{
		printf("cur in skip space=%c\n", cur);
		++(*skip);
		cur = *cmd->chr_itr;
	}
	printf("moved here %p\n", cmd->chr_itr);
}

int tokenizer(char *line)
{
	t_token *new_tok;
	t_token *prev_tok;
	t_cmd	cmd;

	size_t i = 0;
	ft_strtrim(line, " \t");
	cmd.chr_itr = line;
	prev_tok = NULL;
	while (is_not_end(cmd.chr_itr) || *cmd.chr_itr != '\n')
	{
		new_tok = NULL;
		skip_whitespace_between_words(&cmd);
		printf("moved here2 %p\n", cmd.chr_itr);
		if (!is_not_end(cmd.chr_itr) || *cmd.chr_itr == '\n')
			break;
		new_tok = scan(&cmd, prev_tok);
		printf("new token = ");
		if (new_tok)
		{
			for (i = 0; i < new_tok->cmd.len; i++)
			{
				printf("%c", new_tok->cmd.start[i]);
			}
		}
		printf("\n");
		prev_tok = new_tok;
	}
	return (EXIT_SUCCESS);
}