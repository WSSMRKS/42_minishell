/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:17:32 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 18:11:33 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "parse_util.h"

// set flags like heredoc, redir->rightmost, ...
void	post_process_cmd(t_simple_com *cmd)
{
	t_list_redir	*redir;
	t_list_redir	*last_in;
	t_list_redir	*last_out;

	redir = cmd->redir;
	last_in = NULL;
	last_out = NULL;
	while (redir)
	{
		if (redir->instruction == redir_here_doc)
			cmd->heredoc = 1;
		if (redir->instruction == redir_infile
			|| redir->instruction == redir_here_doc)
		{
			last_in = redir;
			redir->rightmost = false;
		}
		else if (redir->instruction == redir_outfile
			|| redir->instruction == redir_append)
		{
			last_out = redir;
			redir->rightmost = false;
		}
		redir = redir->next;
	}
	if (last_in)
		last_in->rightmost = true;
	if (last_out)
		last_out->rightmost = true;
}

static t_list_words	*word_list_from_argv(char **cmd)
{
	t_list_words	*head;
	t_list_words	*current;
	t_list_words	*tmp;
	int				i;

	head = NULL;
	current = NULL;
	i = 0;
	while (cmd[i])
	{
		tmp = malloc(sizeof(t_list_words));
		if (!tmp)
		{
			free_list_words(&head);
			return (NULL);
		}
		tmp->word = ft_strdup(cmd[i]);
		tmp->next = NULL;
		if (!head)
			head = tmp;
		else
			current->next = tmp;
		current = tmp;
		i++;
	}
	return (head);
}

void	skip_pipe(t_ast *ast, size_t *i, size_t len)
{
	if (*i < len && ast[*i].ty == AST_OP && ast[*i].op.ty == OP_PIPE)
		(*i)++;
}

t_simple_com	com_from_ast(t_ast *ast, size_t *i, size_t len)
{
	t_simple_com	cmd;

	cmd = (t_simple_com){0};
	while (*i < len && (ast[*i].ty != AST_OP || ast[*i].op.ty != OP_PIPE))
	{
		if (ast[*i].ty == AST_CMD)
		{
			cmd.words = word_list_from_argv(ast[*i].cmd);
			if (cmd.words == NULL)
			{
				free_simple_com(&cmd);
				return ((t_simple_com){0});
			}
			cmd.argv = ast[*i].cmd;
			ast[*i].cmd = NULL;
		}
		else if (ast[*i].ty == AST_OP)
		{
			if (!add_redirection(&cmd, &ast[*i].op))
			{
				free_simple_com(&cmd);
				return ((t_simple_com){0});
			}
		}
		(*i)++;
	}
	post_process_cmd(&cmd);
	return (cmd);
}

/// input: ast with minimum one item
t_cmd_list	*ast_to_commands(t_vec *ast)
{
	t_cmd_list	*head;
	t_cmd_list	*current;
	size_t		i;

	head = NULL;
	i = 0;
	while (i < ast->len)
	{
		if (head != NULL)
		{
			current->next = ft_calloc(sizeof(t_cmd_list), 1);
			current = current->next;
		}
		else
		{
			current = ft_calloc(sizeof(t_cmd_list), 1);
			head = current;
		}
		current->cmd = com_from_ast(vec_get(ast), &i, ast->len);
		skip_pipe(vec_get(ast), &i, ast->len);
		DEBUG(debug_print_simple_com(STDERR, &current->cmd, true));
		if (current->cmd.words == NULL && current->cmd.redir == NULL)
		{
			free_list_cmds(&head);
			return (NULL);
		}
	}
	return (head);
}
