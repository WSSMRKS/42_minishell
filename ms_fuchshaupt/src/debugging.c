/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:13 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:13 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_redirectionals(t_cmd_list *cmd)
{
	if (cmd)
	{
		//printf("cmd = %s\n", cmd->name_token->str);
		if (cmd->input_operator)
			printf("input: %s , ", cmd->input_operator->str);
		if (cmd->input_argument)
			printf("%s\n", cmd->input_argument->str);
		if (cmd->output_operator)
			printf("output: %s , ", cmd->output_operator->str);
		if (cmd->output_argument)
			printf("%s\n", cmd->output_argument->str);
		printf("\n");
	}
}

void	print_cmd_tokens(t_cmd_list *cmd)
{
	printf("print cmd tokens\n");
	t_cmd_list *tmp;
	t_token		*token;

	tmp = cmd;
	while (tmp)
	{
		token = tmp->first_token;
		printf("\ncmd name:\n");
		print_token(tmp->name_token);
		printf("\nargs\n");
		if (token)
			print_tokens(token);
		tmp = tmp->next;
	}
}

void	print_token(t_token *token)
{
	if (!token)
	{
		printf(GREEN_TEXT "No Token\n" RESET_COLOR);
	}
	else
	{
		printf(GREEN_TEXT "token->org: %s\n", token->original);
		printf("token->str: %s\n", token->str);
		printf("token->del: %d\n", token->delimiter);
		printf("token->env: %d\n", token->env);
		printf("token->quo: %d\n" RESET_COLOR, token->quotes);
	}
	
}

void print_tokens(t_token *head)
{
	t_token *current = head;
	while (current)
	{
		print_token(current);
		printf("\n");
		current = current->next;
	}
}

void	print_map(char **map)
{
	int	pos;

	pos = 0;
	printf("\nprinting map:\n");
	if (!map)
		return ;
	while (map[pos])
	{
		//printf("map[pos] = %p\n", map[pos]);
		printf("%d = '%s'\n", pos, map[pos]);
		pos ++;
	}
}

void	print_fds(t_data *data, t_cmd_list *cmd)
{
	printf("\033[0;34mprinting fd overview \033[0m\n");
	t_cmd_list *tmp;

	tmp = data->first_cmd;
	while (tmp != NULL)
	{
		printf(GREEN_TEXT "cmd: \t\t%d = %s\n", tmp->index, tmp->name_token->str);
		print_token(tmp->name_token);
		printf("pipe_fd: \t%d / %d\n", tmp->pipe_fds[0], tmp->pipe_fds[1]);
		printf("pipe_use:\t%d / %d\n", tmp->pipe_read_end_used, tmp->pipe_write_end_used);
		printf("fd_in / out: \t%d / %d" RESET_COLOR "\n", tmp->fd_in, tmp->fd_out);
		//printf("\n");
		print_redirectionals(tmp);
		printf("args\n");
		print_tokens(tmp->first_token);
		tmp = tmp->next;
		if (tmp)
			printf("\n");
		//break ;
	}
	tmp = cmd;
}
