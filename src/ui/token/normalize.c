/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:25:56 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:25:57 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

// repeating seperators -> single seperator
void	remove_dup_seperators(t_vec *tokens)
{
	t_token	*token;
	t_token	*next;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_SEPERATOR)
		{
			while (i + 1 < tokens->len)
			{
				next = vec_get_at(tokens, i + 1);
				if (next->type == TK_SEPERATOR)
					vec_remove_at(tokens, i + 1);
				else
					break ;
			}
		}
		i++;
	}
}

bool	is_redundant_separator(t_vec *tokens, size_t i)
{
	t_token	*prev;
	t_token	*next;

	if (i == 0 || i == tokens->len - 1)
		return (true);
	if (i > 0)
	{
		prev = vec_get_at(tokens, i - 1);
		if (prev->type == TK_OPERATOR || prev->type == TK_CONTINUE_NL
			|| prev->type == TK_NL)
			return (true);
	}
	if (i + 1 < tokens->len)
	{
		next = vec_get_at(tokens, i + 1);
		if (next->type == TK_OPERATOR || next->type == TK_CONTINUE_NL
			|| next->type == TK_NL)
			return (true);
	}
	return (false);
}

void	remove_redundant_separators(t_vec *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_SEPERATOR && is_redundant_separator(tokens, i))
			vec_remove_at(tokens, i);
		else
			i++;
	}
}

// chained tokens of kind TOKEN_WORD, TOKEN_LITERAL, TOKEN_DQUOTE -> single WORD token
void	merge_chained_word_tokens(t_vec *tokens)
{
	t_token	*token;
	t_token	*next;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token_has_str(token))
		{
			while (i + 1 < tokens->len)
			{
				next = vec_get_at(tokens, i + 1);
				if (token_has_str(next))
				{
					str_cat(&token->str, str_view(&next->str));
					str_destroy(&next->str);
					vec_remove_at(tokens, i + 1);
				}
				else
					break ;
			}
		}
		i++;
	}
}

// after merging chained word tokens, seperators are not needed anymore
void	remove_all_seperators(t_vec *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_SEPERATOR)
			vec_remove_at(tokens, i);
		else
			i++;
	}
}
