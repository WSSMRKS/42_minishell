/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:25:46 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:39:08 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	ast_printerr(t_vec *ast, size_t err_i, const char *err);

/// @brief
/// @param ast
/// @param i
/// @return false if given ast at i is no pipe.
/// If it is a pipe it will return true if the pipe has no argument.
static bool	is_pipe_without_arg_at(t_vec *ast, size_t i)
{
	t_ast	*pipe;
	t_ast	*next;

	pipe = vec_get_at(ast, i);
	if (pipe->ty != AST_OP || pipe->op.ty != OP_PIPE)
		return (false);
	if (i == 0 || i + 1 >= ast->len)
		return (true);
	next = vec_get_at(ast, i + 1);
	if (next->ty == AST_OP && next->op.ty == OP_PIPE)
		return (true);
	return (false);
}

/// @brief
/// @param ast
/// @param i
/// @return false if given ast at i is no op
static bool	is_op_without_arg_at(t_vec *ast, size_t i)
{
	t_ast	*op;

	op = vec_get_at(ast, i);
	if (op->ty != AST_OP || op->op.ty == OP_PIPE)
		return (false);
	return (op->op.arg == NULL);
}

bool	ast_has_integrity(t_parser *p, t_vec *ast)
{
	size_t	i;
	bool	ok;

	i = 0;
	ok = true;
	while (i < ast->len)
	{
		if (is_pipe_without_arg_at(ast, i)
			|| is_op_without_arg_at(ast, i))
		{
			ast_printerr(ast, i, "operator is missing an argument");
			ok = false;
		}
		i++;
	}
	if (!ok)
	{
		vec_destroy(ast, free_ast);
		((t_ms *)p->data)->be->last_ret = 2;
	}
	return (ok);
}
