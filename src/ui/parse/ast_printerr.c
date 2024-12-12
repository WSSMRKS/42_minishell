/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printerr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:25:28 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:25:29 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	str_push_ast(t_str *str, t_ast *ast, bool first)
{
	size_t	i;

	if (ast->ty == AST_OP)
	{
		if (!first)
			str_push(str, ' ');
		str_pushstr(str, cstr_view(op_str(ast->op.ty)));
		if (ast->op.arg)
		{
			str_push(str, ' ');
			str_pushstr(str, cstr_view(ast->op.arg));
		}
		return ;
	}
	i = 0;
	while (ast->cmd[i])
	{
		if (!first || i > 0)
			str_push(str, ' ');
		str_pushstr(str, cstr_view(ast->cmd[i]));
		i++;
	}
}

static void	print_err(t_str *ast_line, t_str *err_line, const char *err)
{
	ft_printf_fd(STDERR, "minishell syntax error: %s\n", err);
	ft_putendl_fd(cstr_ref(ast_line), STDERR);
	ft_putendl_fd(cstr_ref(err_line), STDERR);
}

void	ast_printerr(t_vec *ast, size_t err_i, const char *err)
{
	size_t	i;
	t_str	ast_line;
	t_str	err_line;

	i = 0;
	ast_line = str_empty();
	err_line = str_empty();
	while (i < ast->len)
	{
		if (i == err_i)
		{
			str_pushn(&err_line, ' ', ast_line.len);
			str_push_ast(&ast_line, vec_get_at(ast, i), i == 0);
			if (i != 0)
				str_push(&err_line, ' ');
			str_pushn(&err_line, '^', ast_line.len - err_line.len);
		}
		else
			str_push_ast(&ast_line, vec_get_at(ast, i), i == 0);
		i++;
	}
	print_err(&ast_line, &err_line, err);
	str_destroy(&ast_line);
	str_destroy(&err_line);
}
