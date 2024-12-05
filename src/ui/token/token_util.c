/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:33:28 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 17:57:52 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool	token_has_str(t_token *token)
{
	return (token->type == TK_DQUOTE || token->type == TK_LITERAL || token->type == TK_WORD);
}

void	free_token(void *token)
{
	t_token	*tk;

	tk = token;
	if (tk->type != TK_OPERATOR)
		str_destroy(&tk->str);
}
