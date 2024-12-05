/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:18 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:18 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_red_tokens(t_cmd_list *del)
{
	if (del->input_operator != NULL)
		del->input_operator = free_tokens(del->input_operator);
	if (del->input_argument != NULL)
		del->input_argument = free_tokens(del->input_argument);
	if (del->output_operator != NULL)
		del->output_operator = free_tokens(del->output_operator);
	if (del->output_argument != NULL)
		del->output_argument = free_tokens(del->output_argument);
}

void	*cleanup_cmd(t_data *data)
{
	t_cmd_list	*tmp;
	t_cmd_list	*del;

	del = cmd_lstlast(data->first_cmd);
	close_all_fds(data->first_cmd);
	while (del != NULL)
	{
		tmp = del->prev;
		if (del->first_token != NULL)
			del->first_token = free_tokens(del->first_token);
		free_red_tokens(del);
		if (del->name_token != NULL)
			del->name_token = free_tokens(del->name_token);
		if (tmp != NULL)
			tmp->next = NULL;
		if (del->flag == 1)
			free(del->name);
		free(del);
		del = tmp;
	}
	data->first_cmd = NULL;
	return (NULL);
}

void	*cleaunup_env(t_data *data)
{
	t_env	*tmp;
	t_env	*del;

	del = env_lstlast(data->first_env);
	while (del != NULL)
	{
		tmp = del->prev;
		if (del->name != NULL)
		{
			free(del->name);
			del->name = NULL;
		}
		if (del->value)
		{
			free(del->value);
			del->value = NULL;
		}
		if (tmp != NULL)
			tmp->next = NULL;
		free(del);
		del = tmp;
	}
	data->first_env = NULL;
	return (NULL);
}

void	*free_tokens(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	while (current)
	{
		next = current->next;
		current = free_token(current);
		current = next;
	}
	return (NULL);
}

void	*free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		if (token->original)
			free(token->original);
		free(token);
	}
	return (NULL);
}
