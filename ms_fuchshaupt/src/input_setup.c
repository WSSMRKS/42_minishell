/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:28:52 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:28:52 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	skip_quotes(char *str, int *pos, char *quote)
{
	*quote = str[*pos];
	(*pos)++;
	while (str[*pos] && str[*pos] != *quote)
		(*pos)++;
	if (str[*pos] == *quote)
		(*pos)++;
}

int	cmd_count(char *str)
{
	int		count;
	int		pos;
	char	quote;

	quote = '\0';
	count = 0;
	pos = 0;
	while (str[pos] && str[pos] != '\n')
	{
		if (str[pos] == '\'' || str[pos] == '\"')
		{
			skip_quotes(str, &pos, &quote);
			continue ;
		}
		if (str[pos] == '|')
			count++;
		pos++;
	}
	if (count > 0 || (count == 0 && pos > 0))
		count++;
	return (count);
}

int	input_setup(t_data *data)
{
	t_cmd_list	*tmp;

	if (data->input[0] == '\0')
		return (0);
	list_init(data);
	if (token_main(data) != 0)
		return (1);
	tmp = data->first_cmd;
	while (tmp != NULL)
	{
		if (new_red(data, tmp) == 1)
			return (1);
		if (tmp->name_token)
			tmp->name = tmp->name_token->str;
		tmp = tmp->next;
	}
	prepare_fds(data->first_cmd);
	return (0);
}

int	token_main(t_data *data)
{
	var_init(data);
	initialize_token_struct(data, data->input, data->var);
	var_init(data);
	edit_tokens(data, data->first_token, data->var);
	var_init(data);
	edit_quotes(data, data->first_token, data->var);
	free_var(data);
	return (assign_tokens(data));
}
