/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:17:32 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 18:11:49 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "tk_util.h"

static void	strip_empty_word_tokens(t_vec *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_WORD && token->str.len == 0)
			vec_remove_at(tokens, i);
		else
			i++;
	}
}

static void	str_expand_vars(t_str *str, t_stab_st *st, int last_ret)
{
	t_str		var_str;
	size_t		var_size;
	size_t		i;
	char		*buf;
	t_str_slice	var;

	i = 0;
	while (i < str->len)
	{
		buf = cstr_mut(str);
		if (buf[i] == '$' && (i == 0 || buf[i - 1] != '\\'))
		{
			var_str = str_clone_from(cstr_slice(&buf[i +1],
						var_len(&buf[i], &var_size) - 1));
			if (var_size == 0)
			{
				i++;
				continue ;
			}
			str_remove_range(str, i, i + var_size);
			if (strsl_eq(str_view(&var_str), cstr_slice("?", 1)))
				str_insert_itoa(last_ret, base10(), str, i);
			else
			{
				var = cstr_view(ft_lookup_stab(st,
							(char *)cstr_ref(&var_str)));
				if (var.str)
				{
					str_insertstr(str, i, var);
					i += var.len;
				}
			}
			str_destroy(&var_str);
		}
		else
			i++;
	}
}

void	expand_vars(t_vec *tokens, t_stab_st *st, int last_ret)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_WORD || token->type == TK_DQUOTE)
			str_expand_vars(&token->str, st, last_ret);
		i++;
	}
	strip_empty_word_tokens(tokens);
}
