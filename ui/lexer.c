/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:07:52 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/30 11:58:49 by dkoca            ###   ########.fr       */
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

int is_not_end(t_cmd *cmd)
{
	if (!cmd)
		return (FALSE);
	if (cmd->chr_itr == NULL)
		return (FALSE);
	if (*cmd->chr_itr != '\0')
		return (TRUE);
	return (FALSE);
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

// int check_quote_amount(char *start, int len, int chr)
// {
// 	int has;

// 	has = 0;
// 	while (*start)
// 	{
// 		if (*start == chr)
// 			return 
// 	}
	

// 	return (FALSE);
// }

t_token *has_single_quotes(char **chr_itr, t_token *prev_token)
{
	t_token *new_token;
	char *start;
	int len;

	new_token = NULL;
	len = 0;
	if (**chr_itr == '\'')
	{
		(*chr_itr)++;
	}
	start = *chr_itr;
	while (**chr_itr != '\0' || **chr_itr != '\n')
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
		{
			new_token = add_token(start, TOKEN_WORD, len, &prev_token);
			*chr_itr += len + 1;
		}
		else
		{
			new_token = add_token(start, TOKEN_ERR, len, &prev_token);
			*chr_itr += len;
		}
			
	}
	return (new_token);
}

// t_token scan_word(t_cmd *cmd, char **chr_itr, t_token *prev_token)
// {
// 	t_token *new_token;
// 	char cur_chr;
	
// 	while ((is_not_end(cmd) || cmd->chr_itr != '\n') && !ft_isdigit(cur_chr))
// 	{
		
// 	}
	
// }

t_token *tokenize_word(char **chr_itr, t_token *prev_token)
{
	t_token *token;

		
	token = has_single_quotes(chr_itr, prev_token);
	// check for double and single quotes
	return (token);
}

t_token *scan(t_cmd *cmd, t_token *prev_token)
{
	t_token *token;
	char cur;
	
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
	while (is_not_end(cmd) && cur != '\n' && cur == ' ')
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
	while (is_not_end(&cmd) || *cmd.chr_itr != '\n')
	{
		new_tok = NULL;
		skip_whitespace_between_words(&cmd);
		printf("moved here2 %p\n", cmd.chr_itr);

		if (!is_not_end(&cmd) || *cmd.chr_itr == '\n')
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