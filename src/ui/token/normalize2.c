/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:25:59 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:31:43 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	remove_all_seperators(t_vec *tokens);
void	merge_chained_word_tokens(t_vec *tokens);
void	remove_redundant_separators(t_vec *tokens);
bool	is_redundant_separator(t_vec *tokens, size_t i);
void	remove_dup_seperators(t_vec *tokens);

// repeating seperators -> single seperator
// remove seperator before or after
// one of [TOKEN_OPERATOR, TOKEN_CONTINUE_NL, TOKEN_NL]
// chained tokens of kind TOKEN_WORD, TOKEN_LITERAL, TOKEN_DQUOTE
// -> single WORD token
void	tokens_normalize(t_vec *tokens)
{
	remove_dup_seperators(tokens);
	remove_redundant_separators(tokens);
	merge_chained_word_tokens(tokens);
	remove_all_seperators(tokens);
}

void	tokens_normalize_for_continue_nl_check(t_vec *tokens)
{
	remove_dup_seperators(tokens);
	remove_redundant_separators(tokens);
	remove_all_seperators(tokens);
}
