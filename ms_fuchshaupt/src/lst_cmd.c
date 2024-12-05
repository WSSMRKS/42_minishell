/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:28:47 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:28:47 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd_list	*cmd_lstlast(t_cmd_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	set_nulls(t_cmd_list *new)
{
	new->prev = NULL;
	new->next = NULL;
	new->error = NULL;
	new->name = NULL;
	new->first_env = NULL;
	new->first_token = NULL;
	new->name_token = NULL;
	new->input_operator = NULL;
	new->input_argument = NULL;
	new->output_operator = NULL;
	new->output_argument = NULL;
}

t_cmd_list	*cmd_lst_new(t_data *data, int index, int cmd_count)
{
	t_cmd_list	*new;

	new = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!new)
		exit_on_error(data, MEM, 1, 1);
	set_nulls(new);
	new->cmd_count = cmd_count;
	new->index = index;
	new->pipe_fds[0] = -1;
	new->pipe_fds[1] = -1;
	new->heredoc_pipe[0] = -1;
	new->heredoc_pipe[1] = -1;
	new->pipe_read_end_used = 0;
	new->pipe_write_end_used = 0;
	new->fd_in = -1;
	new->fd_out = -1;
	new->flag = 0;
	new->eof = 0;
	return (new);
}

void	cmd_lstadd_back(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*last;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			last = cmd_lstlast(*lst);
			last->next = new;
			new->prev = last;
		}
	}
}

int	list_init(t_data *data)
{
	t_cmd_list	*new;
	int			i;

	data->first_cmd = NULL;
	i = 0;
	while (i < data->command_count)
	{
		new = cmd_lst_new(data, i, data->command_count);
		new->first_env = data->first_env;
		cmd_lstadd_back(&(data->first_cmd), new);
		i ++;
	}
	if (setup_pipes(data->first_cmd) == 1)
		exit_on_error(data, "pipe Setup failed.", 1, 1);
	return (0);
}
