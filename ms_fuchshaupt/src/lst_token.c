/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:16:54 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:16:54 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*lst_token_last(t_token *head)
{
	t_token	*current;

	current = head;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	create_and_add_token(t_data *data, const char *start,
	size_t length, int *delimiter)
{
	t_token	*new_token;
	t_token	*last;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		exit_on_error(data, MEM, 1, 1);
	new_token->str = malloc(length + 1);
	if (!new_token->str) 
		exit_on_error(data, MEM, 1, 1);
	ft_strlcpy(new_token->str, start, length + 1);
	new_token->original = ft_strdup(new_token->str);
	if (!new_token->original) 
		exit_on_error(data, MEM, 1, 1);
	last = lst_token_last(data->first_token);
	new_token->quotes = 0;
	new_token->env = 0;
	new_token->prev = last;
	new_token->next = NULL;
	new_token->delimiter = *delimiter;
	*delimiter = 0;
	if (last)
		last->next = new_token;
	else
		data->first_token = new_token;
}

void	initialize_token_struct(t_data *data, char *input, t_var *var)
{
	while (input[var->pos] != '\0')
	{
		if (input[var->pos] == '"' && !var->sq)
			var->dq = !var->dq;
		else if (input[var->pos] == '\'' && !var->dq)
			var->sq = !var->sq;
		else if (is_whitespace(input[var->pos]) && !var->dq && !var->sq)
		{
			if (var->pos > var->start)
				create_and_add_token(data, &input[var->start],
					var->pos - var->start, &var->hd);
			var->start = var->pos + 1;
		}
		else if (t_redirectional(input + var->pos) && !var->dq && !var->sq)
			var->hd = tokenize_redirectional(data, input, var);
		var->pos++;
	}
	if (var->pos > var->start)
		create_and_add_token(data, &input[var->start],
			var->pos - var->start, &var->hd);
}
