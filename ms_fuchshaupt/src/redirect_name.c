/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:18:51 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:18:51 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*move_name_redirectional(t_cmd_list *cmd, t_token *arg)
{
	t_token	*ret;

	ret = get_next_arg(arg);
	if (ft_strncmp(cmd->name_token->str, "<", 1) == 0 
		|| ft_strncmp(cmd->name_token->str, "<<", 2) == 0)
		overwrite_red_tokens(cmd, 'i', cmd->name_token, arg);
	else if (ft_strncmp(cmd->name_token->str, ">", 1) == 0
		|| ft_strncmp(cmd->name_token->str, ">>", 2) == 0)
		overwrite_red_tokens(cmd, 'o', cmd->name_token, arg);
	return (ret);
}

void	overwrite_red_tokens(t_cmd_list *cmd, char c, t_token *op, t_token *arg)
{
	if (c == 'i')
	{
		free_token(cmd->input_operator);
		cmd->input_operator = op;
		free_token(cmd->input_argument);
		cmd->input_argument = arg;
	}
	if (c == 'o')
	{
		free_token(cmd->output_operator);
		cmd->output_operator = op;
		free_token(cmd->output_argument);
		cmd->output_argument = arg;
	}
	if (op)
	{
		op->prev = NULL;
		op->next = NULL;
	}
	if (arg)
	{
		arg->prev = NULL;
		arg->next = NULL;
	}
}

t_token	*overwrite_name_token(t_cmd_list *cmd, t_token *arg)
{
	if (arg != NULL)
	{
		cmd->name_token = arg;
		arg = get_next_arg(arg);
		cmd->name_token->prev = NULL;
		cmd->name_token->next = NULL;
		if (arg != NULL)
			arg->prev = NULL;
	}
	else
		cmd->name_token = NULL;
	return (arg);
}

int	check_cmd_name(t_data *data, t_cmd_list *cmd)
{
	t_token	*arg;
	int		flag;

	arg = cmd->first_token;
	flag = 0;
	while (cmd->name_token
		&& is_redirectional(cmd->name_token->str, cmd->name_token) == 1)
	{
		if (arg == NULL)
			return (1);
		arg = move_name_redirectional(cmd, arg);
		if (flag == 0)
			flag = redirect(data, cmd);
		arg = overwrite_name_token(cmd, arg);
		cmd->first_token = arg;
	}
	return (flag);
}
