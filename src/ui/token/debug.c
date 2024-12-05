/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:57:03 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 17:57:52 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "util.h"

void	token_print(const t_token *token, int fd)
{
	const char	*ty;
	const char	*tk_str;

	// depending on token type put their respective type as str
	if (token->type == TK_WORD)
		ty = "WORD";
	else if (token->type == TK_LITERAL)
		ty = "LIT";
	else if (token->type == TK_DQUOTE)
		ty = "DQUO";
	else if (token->type == TK_OPERATOR)
		ty = "OP";
	else if (token->type == TK_CONTINUE_NL)
		ty = "CONT_NL";
	else if (token->type == TK_NL)
		ty = "NL";
	else
		ty = "SEP";
	tk_str = "";
	if (token->type == TK_WORD || token->type == TK_LITERAL
		|| token->type == TK_DQUOTE)
		tk_str = cstr_ref(&token->str);
	else if (token->type == TK_OPERATOR)
		tk_str = op_str(token->op);
	ft_printf_fd(fd, "%-4s: (%s)", ty, tk_str);
}
