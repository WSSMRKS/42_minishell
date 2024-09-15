/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:27:04 by dkoca             #+#    #+#             */
/*   Updated: 2024/09/14 18:09:01 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_token *has_single_quotes(char **chr_itr, t_token *prev_token)
{
	t_token *new_token;
	char *start;
	int len;

	new_token = NULL;
	start = NULL;
	len = 0;
	if (!is_quoted(**chr_itr, '\''))
		return (NULL);
	start = ++(*chr_itr);
	while (!is_end(*chr_itr) && **chr_itr != '\'')
	{
		(*chr_itr)++;
		len++;
	}
	if (len > 0 && !is_end(start))
	{
		if (ft_strchr(start, '\''))
			new_token = get_token(start, TOKEN_WORD_SQUOTE, len, &prev_token);
		else if (start == NULL && !ft_strchr(start, '\''))
			new_token = get_token(start, TOKEN_ERR, len, &prev_token);
	}
	return (new_token);
}

t_token *has_double_quotes(char **chr_itr, t_token *prev_token)
{
	t_token *new_token;
	char *start;
	int len;

	new_token = NULL;
	start = NULL;
	len = 0;
	if (!is_quoted(**chr_itr, '\"'))
		return (NULL);
	start = ++(*chr_itr);
	while (!is_end(*chr_itr) && **chr_itr != '\"')
	{
		(*chr_itr)++;
		len++;
	}
	if (len > 0 && !is_end(start))
	{
		if (ft_strchr(start, '\"'))
			new_token = get_token(start, TOKEN_WORD_DQUOTE, len, &prev_token);
		else if (!ft_strchr(start, '\"'))
			new_token = get_token(start, TOKEN_ERR, len, &prev_token);
	}
	return (new_token);
}