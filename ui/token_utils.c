/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 05:48:37 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/26 12:28:00 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *add_token(char *content, int type, int len, t_token **prev_next_ptr)
{
	t_token *new_tok;

	new_tok = ft_calloc(1, sizeof(t_token));
	if (new_tok == NULL)
		// safe exit or create safe malloc
	new_tok->cmd.start = ft_calloc(len + 1, sizeof(char));
	if (new_tok == NULL)
		// safe exit or create safe malloc
	new_tok->cmd.start = content;
	new_tok->cmd.len = len;
	new_tok->type = type;
	new_tok->next = NULL;
	if (prev_next_ptr)
		*prev_next_ptr = new_tok;
	return (new_tok);
}

