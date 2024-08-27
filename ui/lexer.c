/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 06:07:52 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/27 16:08:12 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lookahead(t_cmd *cmd, int pos)
{
	if (cmd->chr_itr == NULL)
		return (EOF);
	printf("pos in peek = %i\n", pos);
	if (pos == PEEK_START)
		return (*cmd->chr_itr);
	return (cmd->chr_itr[pos + 1]);
}

int is_not_end(t_cmd *cmd, int pos)
{
	char next;

	if (cmd->chr_itr == NULL)
		return (FALSE);
	next = lookahead(cmd, pos);
	if (next != '\0' && next != '\n')
		return (TRUE);
	return (FALSE);
}


/* tokenizes operator and consumes used chars*/
t_token *tokenize_operator(char **next_ptr, char next, t_token *prev_token)
{
	t_token *token;
	
	printf("next char = %c\n", **next_ptr);
	if (next == '|')
		token = add_token(*next_ptr, TOKEN_PIPE, 1, &prev_token);
	else if (ft_strncmp(*next_ptr, ">>", 2) == 0)
		token = add_token(*next_ptr, TOKEN_APPEND, 2, &prev_token);
	else if (ft_strncmp(*next_ptr, "<<", 2) == 0)
		token = add_token(*next_ptr, TOKEN_HEREDOC, 2, &prev_token);
	else if (next == '>')
		token = add_token(*next_ptr, TOKEN_IO_OUT, 1, &prev_token);
	else if (next == '<')
		token = add_token(*next_ptr, TOKEN_IO_IN, 1, &prev_token);
	// *next_ptr += token->cmd.len - 1;
	return (token);
}

// int has_single_quotes(char **chr_itr, t_token *prev_token)
// {
// 	char next;
// 	int has;

// 	has = FALSE;
	
// }

// t_token *tokenize_word(char **chr_itr, t_token *prev_token)
// {
// 	t_token *token;
// 	char next;

	
		
// 	// check for double and single quotes
// 	return (token);
// }

t_token *scan(t_cmd *cmd, int pos, t_token *prev_token)
{
	t_token *token;
	char next;
	char *next_ptr;
	
	if (pos == PEEK_START)
		next_ptr = cmd->chr_itr;
	else 
		next_ptr = cmd->chr_itr + 1;
	// printf("chr itr = %c\n", *cmd->chr_itr);
	next = lookahead(cmd, pos);
	if (next && ft_strchr("|<>", next))
		token = tokenize_operator(&next_ptr, next, prev_token);
	// else
		//tokenize_word
	return (token);
}

void skip_whitespace_between_words(t_cmd *cmd, int *pos)
{
	char next;
	char **skip;

	skip = &cmd->chr_itr;
	
	next = lookahead(cmd, *pos);
	printf("before spaces %s\n", cmd->chr_itr);
	printf("next in skip space=%c\n", cmd->chr_itr[*pos + 1]);
	while (next != '\0' && next != '\n' && next == ' ')
	{
		printf("here\n");
		(*pos)++;
		++(*skip);
		next = lookahead(cmd, *pos);
	}
	printf("moved here %p\n", cmd->chr_itr);
}

int tokenizer(char *line)
{
	t_token *new_tok;
	t_token *prev_tok;
	t_cmd	cmd;
	// char *chr_itr;
	int itr_pos;

	int i = 0;
	// int next_char;
	
	itr_pos = -2;
	ft_strtrim(line, " \t");
	// chr_itr = ft_calloc(ft_strlen(line), sizeof(char));
	cmd.chr_itr = line;
	prev_tok = NULL;
	while (is_not_end(&cmd, itr_pos))
	{
		printf("left = %s\n", cmd.chr_itr);
		printf("before skipping %p\n", cmd.chr_itr);
		skip_whitespace_between_words(&cmd, &itr_pos);
		printf("after skipping %p\n", cmd.chr_itr);
		printf("left after spaces =%s\n", cmd.chr_itr);
		printf("itr pos = %i\n", itr_pos);
		if (!is_not_end(&cmd, itr_pos))
			break;
		new_tok = scan(&cmd, itr_pos, prev_tok);
		itr_pos = new_tok->cmd.start - line + new_tok->cmd.len - 1;
		cmd.chr_itr += new_tok->cmd.len - 1;
		printf("new token = ");
		for (i = 0; i < new_tok->cmd.len; i++)
		{
			printf("%c", new_tok->cmd.start[i]);
		}
		printf("\n");
		prev_tok = new_tok;
	}
	return (EXIT_SUCCESS);
}