/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:46:27 by dkoca             #+#    #+#             */
/*   Updated: 2024/09/10 17:20:52 by dkoca            ###   ########.fr       */
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


t_list_words *make_word(t_tok_span *word_info)
{
	t_list_words *new_word;
	
	new_word = ft_calloc(1, sizeof(t_list_words));
	new_word->word = ft_calloc(word_info->len + 1, sizeof(char));
	printf("new word = %p\n", new_word);

	ft_strlcpy(new_word->word, word_info->start, word_info->len + 1);
	/*handle flags here*/
	return (new_word);
}

t_list_words **make_word_list(t_tok_span *word_info, t_list_words ***tail)
{
	t_list_words *new;

	// new = ft_calloc(1, sizeof(t_list_words));
	
	new = make_word(word_info);
	printf("tail prev = %p\n", tail);
	**tail = new;
	printf("tail is pointing at new = %p\n", *tail);
	printf("new word next = %p\n", &(new)->next);
	// tail = &new->next;
	// printf("tail is pointing at new next = %p\n", *tail);
	// new->next = list;
	return (&new->next);	
}

/* TODO: Add error checking allocation functions*/
t_simple_com *make_simple_cmd(t_token *token, t_simple_com *cmd, t_list_words ***tail)
{
	if (cmd == NULL){
		cmd = ft_calloc(1, sizeof(t_simple_com));
		*tail = &(cmd->words);
		printf("head of the list = %p\n", &cmd->words);
	}
	if (token->type == TOKEN_WORD)
	{
		*tail = make_word_list(&token->cmd, tail);
		printf("tail is pointing at new next = %p\n", tail);

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
	t_list_words **tail;
	// t_simple_com *cmd;
	
	cmd_list = ft_calloc(1, sizeof(t_cmd_list));
	tail = NULL;
	// printf("simp cmd = %p\n", cmd);
	while (tokens) //parse simple command
	{
		cmd_list->cmd = make_simple_cmd(tokens, cmd_list->cmd, &tail);
		printf("words head = %p\n", cmd_list->cmd->words);
		printf("word = %s\n", cmd_list->cmd->words->word);
		tokens = tokens->next;				
	}
	return (EXIT_SUCCESS);
}