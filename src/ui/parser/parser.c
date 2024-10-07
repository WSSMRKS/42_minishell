/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:46:27 by dkoca             #+#    #+#             */
/*   Updated: 2024/10/07 18:35:49 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/* redirection types except for pipes*/
void redir_type_match(int type, e_redir_type *instruction)
{
	if (type == TOKEN_IO_IN)
		*instruction = redir_infile;
	else if (type == TOKEN_IO_OUT)
		*instruction = redir_outfile;
	else if (type == TOKEN_APPEND)
		*instruction = redir_append;
	else if (type == TOKEN_HEREDOC)
		*instruction = redir_here_doc;
	else
		*instruction = redir_err;
}

void set_filename(t_token *tokens, t_list_redir **redir)
{
	char *filename;

	if ((*redir)->instruction == redir_infile
		|| (*redir)->instruction == redir_outfile
		|| (*redir)->instruction == redir_append)
	{
		(*redir)->target->filename = ft_calloc(tokens->cmd.len + 1, sizeof(char));
		ft_strlcpy(tokens->cmd.start, (*redir)->target->filename, tokens->cmd.len + 1);
		// redir->target->fd = -1;
	}
	else if ((*redir)->instruction == redir_here_doc)
	{
		/* code */
	}


}


// int set_infile(t_token *tokens, t_list_redir *redir)
// {
// 	if (redir->instruction == redir_infile)
// 	{
// 		if (tokens->next ==)
// 		redir->target->fd = ;
// 	}

// }

t_list_redir *make_redirection(t_token *token)
{
	t_list_redir *redirection;

	redirection = ft_calloc(1, sizeof(t_list_redir));
	redir_type_match(token->type, &redirection->instruction);
	if (token->next)
		set_filename(token->next, &redirection);
	else
		return (NULL);

	// set infile
	return (redirection);
}

/* TODO: Add error checking allocation functions*/
/* Parses tokens into a data structure that makes them permissable for execution.
	Separates the command string into a different (next) simple command,
	if there are connections (pipes)*/
t_simple_com *make_simple_cmd(t_token *token, t_simple_com *cmd, t_list_words ***wl_tail, t_list_redir ***rl_tail)
{
	if (cmd == NULL){
		cmd = ft_calloc(1, sizeof(t_simple_com));
		*wl_tail = &(cmd->words);
		printf("head of the list = %p\n", &cmd->words);
	}
	if (token->type == TOKEN_WORD)
	{
		*wl_tail = make_word_list(&token->cmd, wl_tail);
	}
	// else if (token->type >= REDIRECTION)
	// {

	// }
	// else
		// return (NULL);
	return (cmd);
}

int parse_simple_cmd(t_token *tokens)
{
	(void)tokens;
	t_cmd_list *cmd_list;
	t_list_words **wl_tail;
	t_list_redir **rl_tail;

	cmd_list = ft_calloc(1, sizeof(t_cmd_list));
	wl_tail = NULL;
	while (tokens) //parse simple command
	{
		if (tokens->type == TOKEN_PIPE)
			continue;
		cmd_list->cmd = make_simple_cmd(tokens, cmd_list->cmd, &wl_tail, &rl_tail);
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

// int parse(t_token *tokens)
// {
// 	t_token *temp;
// 	if (!tokens)
// 		return (EXIT_FAILURE);
// 	temp = tokens;
// 	while (temp)
// 	{
// 		if (temp->type == TOKEN_PIPE)
// 		{
// 			/* c
// 		}

// 		temp = temp->next;
// 		/* code */
// 	}

// }
