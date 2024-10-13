/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:46:27 by dkoca             #+#    #+#             */
/*   Updated: 2024/10/13 23:52:54 by dkoca            ###   ########.fr       */
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
	if ((*redir)->instruction == redir_infile
		|| (*redir)->instruction == redir_outfile
		|| (*redir)->instruction == redir_append)
	{
		(*redir)->target = ft_calloc(1, sizeof(t_redir_aim));
		(*redir)->target->filename = ft_calloc(tokens->cmd.len + 1, sizeof(char));
		ft_strlcpy((*redir)->target->filename, tokens->cmd.start, tokens->cmd.len + 1);
	}
	else if ((*redir)->instruction == redir_here_doc)
	{
		(*redir)->hd_del = ft_calloc(tokens->cmd.len + 1, sizeof(char));
		ft_strlcpy((*redir)->hd_del, tokens->cmd.start, tokens->cmd.len + 1);
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

t_list_redir *make_redirection(t_token **token)
{
	t_list_redir *redirection;

	redirection = ft_calloc(1, sizeof(t_list_redir));
	redir_type_match((*token)->type, &redirection->instruction);
	if ((*token)->next)
	{
		*token = (*token)->next;	
		set_filename(*token, &redirection);
	}
	else
		return (NULL); // error, no input after redirection

	// set infile
	return (redirection);
}

t_list_redir **make_redir_list(t_token **token, t_list_redir ***rl_tail)
{
	t_list_redir *new;
	
	new = make_redirection(token);
	**rl_tail = new;	
	return (&new->next);
}

/* TODO: Add error checking allocation functions*/
/* Parses tokens into a data structure that makes them permissable for execution.
	Separates the command string into a different (next) simple command,
	if there are connections (pipes)*/
t_simple_com *make_simple_cmd(t_token **token, t_simple_com *cmd, t_list_words ***wl_tail, t_list_redir ***rl_tail)
{
	if (cmd == NULL){
		cmd = ft_calloc(1, sizeof(t_simple_com));
		*wl_tail = &(cmd->words);
		*rl_tail = &(cmd->redir);
		printf("head of the list = %p\n", &cmd->words);
	}
	if ((*token)->type == TOKEN_WORD)
	{
		*wl_tail = make_word_list(&(*token)->cmd, wl_tail);
	}
	else if ((*token)->type >= REDIRECTION)
	{
		*rl_tail = make_redir_list(token, rl_tail);
	}
	// else
		// return (NULL);
	return (cmd);
}

int parse_simple_cmd(t_token *tokens)
{
	// (void)tokens;
	t_cmd_list *cmd_list;
	// t_simple_com *cmd;
	t_list_words **wl_tail;
	t_list_redir **rl_tail;

	cmd_list = ft_calloc(1, sizeof(t_cmd_list));
	while (tokens) //parse simple command
	{
		if (tokens->type == TOKEN_PIPE)
		{
			tokens = tokens->next;
			// cmd_list->next = ft_calloc(1, sizeof(t_cmd_list));
			// cmd_list = cmd_list->next;
			continue;
		}
		cmd_list->cmd = make_simple_cmd(&tokens, cmd_list->cmd, &wl_tail, &rl_tail);
		tokens = tokens->next;
	}
	t_simple_com *tmp = cmd_list->cmd;
	while (tmp && tmp->words)
	{
		printf("word = %s\n", tmp->words->word);
		tmp->words = tmp->words->next;
		/* code */
	}
	tmp = cmd_list->cmd;
	while (tmp && tmp->redir)
	{
		if (tmp->redir->target)
			printf("redir = %s\n", tmp->redir->target->filename);
		else
			printf("heredoc = %s\n", tmp->redir->hd_del);
		tmp->redir = tmp->redir->next;
		/* code */
	}
	
	
	return (EXIT_SUCCESS);
}

// int parse(t_token *tokens)
// {
// 	t_cmd_list *cmd_list;
	
// 	cmd_list = ft_calloc(1, sizeof(t_cmd_list));
// 	while (tokens)
// 	{
// 		/* code */
// 	}
	
	

// }

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
