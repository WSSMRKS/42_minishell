/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:54:45 by sgramsch          #+#    #+#             */
/*   Updated: 2024/11/27 10:54:45 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*move_input(t_cmd_list *cmd, t_token *op, t_token *arg, t_token *before)
{
	t_token	*after;

	after = arg;
	if (after)
		after = after->next;
	overwrite_red_tokens(cmd, 'i', op, arg);
	if (after)
		after->prev = before;
	if (before)
		before->next = after;
	else
		cmd->first_token = after;
	return (after);
}

t_token	*move_output(t_cmd_list *cmd, t_token *op, t_token *arg,
	t_token *before)
{
	t_token	*after;

	after = arg;
	if (after)
		after = after->next;
	overwrite_red_tokens(cmd, 'o', op, arg);
	if (after)
		after->prev = before;
	if (before)
		before->next = after;
	else
		cmd->first_token = after;
	return (after);
}

t_token	*move_red_arg(t_cmd_list *cmd, t_token *arg)
{
	t_token	*before;
	t_token	*after;

	before = arg->prev;
	after = arg->next;
	if (ft_strncmp(arg->str, "<", 1) == 0 || ft_strncmp(arg->str, "<<", 2) == 0)
		after = move_input(cmd, arg, after, before);
	else if (ft_strncmp(arg->str, ">", 1) == 0 
		|| ft_strncmp(arg->str, ">>", 2) == 0)
		after = move_output(cmd, arg, after, before);
	return (after);
}

int	move_redirections(t_data *data, t_cmd_list *cmd)
{
	t_token	*arg;

	arg = cmd->first_token;
	while (arg)
	{
		if (arg->str != NULL)
		{
			if (is_redirectional(arg->str, arg) == 1)
			{
				arg = move_red_arg(cmd, arg);
				if (redirect(data, cmd) == 1)
					return (1);
				if (cmd->error != NULL)
					return (0);
			}
			else
				arg = arg->next;
		}
		else
			arg = arg->next;
	}
	return (0);
}

int	new_red(t_data *data, t_cmd_list *cmd)
{
	if (check_cmd_name(data, cmd) == 1)
		return (exit_on_error(data, "Syntax error", 0, 1));
	return (move_redirections(data, cmd));
}
