/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:20:37 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:20:37 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tokenize_in(t_data *data, const char *input, t_var *var)
{
	if (input[var->pos + 1] == '<')
	{
		var->pos = var->pos + 1;
		create_and_add_token(data, &(input[var->start]),
			var->pos + 1 - var->start, &var->hd);
		var->start = var->pos + 1;
		return (1);
	}
	else
	{
		create_and_add_token(data, &(input[var->start]),
			var->pos + 1 - var->start, &var->hd);
		var->start = var->pos + 1;
	}
	return (0);
}

int	tokenize_out(t_data *data, const char *input, t_var *var)
{
	if (input[var->pos + 1] == '>')
	{
		var->pos = var->pos + 1;
		create_and_add_token(data, &(input[var->start]),
			var->pos + 1 - var->start, &var->hd);
		var->start = var->pos + 1;
	}
	else
	{
		create_and_add_token(data, &(input[var->start]),
			var->pos + 1 - var->start, &var->hd);
		var->start = var->pos + 1;
	}
	return (0);
}

int	tokenize_redirectional(t_data *data, const char *input, t_var *var)
{
	if (var->start < var->pos)
		create_and_add_token(data, &(input[var->start]),
			var->pos - var->start, &var->hd);
	var->start = var->pos;
	if (input[var->pos] == '<')
		return (tokenize_in(data, input, var));
	else if (input[var->pos] == '>')
		return (tokenize_out(data, input, var));
	else if (input[var->pos] == '|')
	{
		create_and_add_token(data, &(input[var->start]),
			var->pos + 1 - var->start, &var->hd);
		var->start = var->pos + 1;
	}
	return (0);
}

int	t_redirectional(char *input)
{
	if (*input == '<' || *input == '>' || *input == '|')
		return (1);
	return (0);
}
