/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:00:38 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 13:01:08 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	vec_push_tk(t_vec *vec, t_token tk)
{
	vec_push(vec, &tk);
}

bool	is_word_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '"' || c == '\'');
}

bool	token_has_str(t_token *token)
{
	return (token->type == TK_DQUOTE || token->type == TK_LITERAL || token->type == TK_WORD);
}

/// @brief Removes leading whitespace from a stringview.
/// @param s The stringview to trim.
void	strsl_trim_start_delim(t_str_slice *s)
{
	while (s->len && is_word_delimiter(*s->str))
	{
		s->str++;
		s->len--;
	}
}
