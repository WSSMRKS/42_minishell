/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:46:27 by dkoca             #+#    #+#             */
/*   Updated: 2024/09/08 20:26:16 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/* Parses tokens into a data structure that makes them permissable for execution.
	Separates the command string into a different (next) simple command,
	if there are connections (pipes)*/
// int type_match(t_token *token)
// {
// 	if (token->type == TOKEN_IO_IN)
		
// }


t_word_desc *make_word(t_tok_span *word_info)
{
	t_word_desc *new_word;

	new_word = ft_calloc(1, sizeof(t_word_desc));
	new_word->word = ft_calloc(word_info->len + 1, sizeof(char));
	ft_strlcpy(new_word->word, word_info->start, word_info->len + 1);
	/*handle flags here*/
	return (new_word);
}

t_list_words *make_word_list(t_tok_span *word_info, t_list_words *list)
{
	t_list_words *new;

	new = ft_calloc(1, sizeof(t_list_words));
	
	new->word = make_word(word_info);
	new->next = list;
	return (new);	
}

/* TODO: Add error checking allocation functions*/
t_simple_com *make_simple_cmd(t_token *token, t_simple_com *cmd)
{
	if (cmd == NULL)
		cmd = ft_calloc(1, sizeof(t_simple_com));
	if (token->type == TOKEN_WORD)
	{
		cmd->words = make_word_list(&token->cmd, cmd->words);
	}
	// else if (token->type >= REDIRECTION)
	// {
		
	// }
	// else
		// return (NULL);
	return (cmd);
}

int parse(t_token *tokens)
{
	(void)tokens;
	t_cmd_list *cmd_list;
	// t_simple_com *cmd;
	
	cmd_list = ft_calloc(1, sizeof(t_cmd_list));
	// printf("simp cmd = %p\n", cmd);
	while (tokens) //parse simple command
	{
		cmd_list->cmd = make_simple_cmd(tokens, cmd_list->cmd);
		printf("word = %s\n", cmd_list->cmd->words->word->word);
		tokens = tokens->next;				
	}
	return (EXIT_SUCCESS);
}