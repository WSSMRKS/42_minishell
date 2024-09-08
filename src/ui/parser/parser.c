/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:46:27 by dkoca             #+#    #+#             */
/*   Updated: 2024/09/07 20:07:40 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/* Parses tokens into a data structure that makes them permissable for execution.
	Separates the command string into a different (next) simple command,
	if there are connections (pipes)*/
int type_match(t_token *token)
{
	if (token->type == TOKEN_IO_IN)
		
}


int parse(t_token *tokens, t_cmd_list **cmd_list)
{
	(void)tokens;
	while (tokens)
	{
		// handle flags
		// make command (fill in word_list)
		// handle token depending on type (rediraction, etc)
		
	}
	
}