/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unescape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:26:16 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:34:11 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

// for double quotes only unescape <‘$’, ‘"’, ‘\’, newline>.
static void	str_unescape_chars(t_str *str, t_token_ty tk_ty)
{
	size_t	i;
	char	*buf;

	i = 0;
	while (true)
	{
		buf = cstr_mut(str);
		if (buf[i] == 0)
			break ;
		if (buf[i] == '\\' && buf[i + 1] != 0
			&& (tk_ty != TK_DQUOTE || ft_strchr("\"\\$", buf[i + 1])))
			str_remove(str, i);
		i++;
	}
}

void	unescape_chars(t_vec *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_WORD || token->type == TK_DQUOTE)
			str_unescape_chars(&token->str, token->type);
		i++;
	}
}
