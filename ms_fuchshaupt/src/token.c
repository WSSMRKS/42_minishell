/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:20:26 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:20:26 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_normal(t_data *data, char *str, t_var *var)
{
	char	*add;

	add = NULL;
	if (var->end < var->start)
		return ;
	add = malloc(var->end - var->start + 2);
	if (!add)
		exit_on_error(data, MEM, 1, 1);
	ft_strlcpy(add, str + var->start, var->end - var->start + 2);
	var->new = join(var->new, add);
	var->start = var->end + 1;
}

void	edit_tokens(t_data *data, t_token *current, t_var *var)
{
	while (current)
	{
		var_init(data);
		var = data->var;
		while (current->str[var->pos])
		{
			if (current->str[var->pos] == '\'')
				var->sq = !var->sq;
			else if (current->str[var->pos] == '$' && !current->delimiter)
				env_expanding(data, var, current->str);
			var->pos ++;
		}
		if (var->start < var->pos)
		{
			var->end = var->pos - 1;
			add_normal(data, current->str, var);
		}
		free(current->str);
		current->str = var->new;
		current->env = var->env;
		var->new = NULL;
		current = current->next;
	}
}

int	deal_sq(t_data *data, t_var *var, t_token *current, char c)
{
	var->end = var->pos -1;
	add_normal(data, current->str, var);
	if (c == '\'')
		var->sq = !var->sq;
	else
		var->dq = !var->dq;
	var->start ++;
	return (1);
}

void	edit_quotes(t_data *data, t_token *current, t_var *var)
{
	while (current)
	{
		var_init(data);
		var = data->var;
		while (current->str && current->str[var->pos])
		{
			if (current->str[var->pos] == '\'' && !var->dq)
				current->quotes = deal_sq(data, var, current, '\'');
			else if (current->str[var->pos] == '\"' && !var->sq)
				current->quotes = deal_sq(data, var, current, '\"');
			var->pos ++;
		}
		if (var->start < var->pos)
		{
			var->end = var->pos - 1;
			add_normal(data, current->str, var);
		}
		free(current->str);
		current->str = var->new;
		var->new = NULL;
		current = current->next;
	}
}
