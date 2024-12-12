/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:26:07 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:26:08 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	free_token(void *token)
{
	t_token	*tk;

	tk = token;
	if (tk->type != TK_OPERATOR)
		str_destroy(&tk->str);
}

bool	token_has_str(t_token *token)
{
	return (token->type == TK_DQUOTE
		|| token->type == TK_LITERAL
		|| token->type == TK_WORD);
}

void	vec_push_tk(t_vec *vec, t_token tk)
{
	vec_push(vec, &tk);
}
