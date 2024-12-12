/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:25:35 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:30:09 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool			add_argv(char ***dst, char ***argv);
bool			add_word_list(t_list_words **head, char **cmd);
bool			add_redirection(t_simple_com *cmd, t_op *op);
/// set flags like heredoc, redir->rightmost, ...
void			post_process_cmd(t_simple_com *cmd);

static void	skip_pipe(t_ast *ast, size_t *i, size_t len)
{
	if (*i < len && ast[*i].ty == AST_OP && ast[*i].op.ty == OP_PIPE)
		(*i)++;
}

static void	com_from_ast(t_ast *ast, size_t *i, size_t len, t_simple_com *cmd)
{
	while (*i < len && (ast[*i].ty != AST_OP || ast[*i].op.ty != OP_PIPE))
	{
		if (ast[*i].ty == AST_CMD)
		{
			if (!add_word_list(&cmd->words, ast[*i].cmd)
				|| !add_argv(&cmd->argv, &ast[*i].cmd))
			{
				free_simple_com(cmd);
				return ;
			}
		}
		else if (ast[*i].ty == AST_OP)
		{
			if (!add_redirection(cmd, &ast[*i].op))
			{
				free_simple_com(cmd);
				return ;
			}
		}
		(*i)++;
	}
	post_process_cmd(cmd);
}

/// input: ast with minimum one item
t_cmd_list	*ast_to_commands(t_vec *ast)
{
	t_cmd_list	*head;
	t_cmd_list	*current;
	size_t		i;

	head = NULL;
	i = 0;
	while (i < ast->len && (i == 0 || head != NULL))
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
		com_from_ast(vec_get(ast), &i, ast->len, &current->cmd);
		skip_pipe(vec_get(ast), &i, ast->len);
		if (current->cmd.words == NULL && current->cmd.redir == NULL)
			free_list_cmds(&head);
	}
	return (head);
}
