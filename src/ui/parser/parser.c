/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:46:27 by dkoca             #+#    #+#             */
/*   Updated: 2024/09/10 20:12:42 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/* redirection types except for pipes*/
// void redir_type_match(int type, e_redir_type *instruction)
// {
// 	if (type == TOKEN_IO_IN)
// 		*instruction = redir_infile;
// 	else if (type == TOKEN_IO_OUT)
// 		*instruction = redir_outfile;
// 	else if (type == TOKEN_APPEND)
// 		*instruction = redir_append;
// 	else if (type == TOKEN_HEREDOC)
// 		*instruction = redir_here_doc;
// 	else
// 		*instruction = redir_err;			
// }

// char *set_filename(t_token *tokens)
// {
// 	char *filename;

// 	if
// }


// int set_infile(t_token *tokens, t_list_redir *redir)
// {
// 	if (redir->instruction == redir_infile)
// 	{
// 		if (tokens->next ==)
// 		redir->from->fd = ;
// 	}
	
// }

// t_list_redir *make_redirection(t_token *token)
// {
// 	t_list_redir *redirection;
	
// 	redirection = ft_calloc(1, sizeof(t_list_redir));
// 	redir_type_match(token->type, &redirection->instruction);
	
	
// }

/* TODO: Add error checking allocation functions*/
/* Parses tokens into a data structure that makes them permissable for execution.
	Separates the command string into a different (next) simple command,
	if there are connections (pipes)*/
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
	
	cmd_list = ft_calloc(1, sizeof(t_cmd_list));
	tail = NULL;
	while (tokens) //parse simple command
	{
		cmd_list->cmd = make_simple_cmd(tokens, cmd_list->cmd, &tail);
		tokens = tokens->next;				
	}
	return (EXIT_SUCCESS);
}