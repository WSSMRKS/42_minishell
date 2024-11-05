/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 05:48:37 by dkoca             #+#    #+#             */
/*   Updated: 2024/10/07 16:50:53 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_token *get_token(char *content, int type, int len, t_token **prev)
{
	t_token *new_tok;

	new_tok = ft_calloc(1, sizeof(t_token));
	// if (new_tok == NULL)
		// safe exit or create safe malloc
	new_tok->cmd.start = ft_calloc(len + 1, sizeof(char));
	// if (new_tok == NULL)
		// safe exit or create safe malloc
	new_tok->cmd.start = content;
	new_tok->cmd.len = len;
	new_tok->type = type;
	new_tok->next = NULL;
	if (*prev)
		(*prev)->next = new_tok;
	return (new_tok);
}

int is_quoted(int first_char, int quote)
{
	if (first_char == quote)
		return (TRUE);
	else
		return (FALSE);
}

int is_word(int cur_char)
{
	if (!ft_strchr("|<> \t", cur_char))
		return (TRUE);
	return (FALSE);
}

void skip_whitespace_between_words(char **cmd)
{
	char cur;

	cur = **cmd;
	while (!is_end(*cmd)&& cur == ' ')
	{
		(*cmd)++;
		cur = **cmd;
	}
}

int is_end(char *chr_itr)
{
	if (chr_itr != NULL && *chr_itr != '\0')
		return (FALSE);
	return (TRUE);
}

/* debugging function*/
void print_token(t_token *token)
{
	(void) token;
	// size_t i;
	// if (token)
	// {
	// 	for (i = 0; i < token->cmd.len; i++)
	// 	{
	// 		printf("%c", token->cmd.start[i]);
	// 	}
	// printf("\n");
	// printf("token len = %zu\n", token->cmd.len);
	// printf("token type = %i\n", token->type);
	// }
}
