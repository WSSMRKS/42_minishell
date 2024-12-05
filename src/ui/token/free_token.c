/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:02:00 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 13:13:42 by kwurster         ###   ########.fr       */
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
