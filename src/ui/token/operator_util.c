/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:21:21 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 18:11:54 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "tk_util.h"

/// @brief Checks if the string is an operator.
/// @param str The string to check.
/// @param out (Null)Pointer for output.
/// @return true if the string is an operator, false otherwise.
bool	str_is_operator(t_str_slice str, t_op_ty *out)
{
	size_t						i;
	static const t_str_slice	operators[] = {
	[OP_PIPE] = {"|", 1},
	[OP_REDIRECT] = {">", 1},
	[OP_INP_REDIRECT] = {"<", 1},
	[OP_APPEND] = {">>", 2},
	[OP_HEREDOC] = {"<<", 2},
	{NULL, 0}
	};

	i = 0;
	while (operators[i].str)
	{
		if (strsl_eq(str, operators[i]))
		{
			if (out)
				*out = (t_op_ty)i;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	str_starts_with_op(t_str_slice str, t_op_ty *out)
{
	size_t					i;
	static const t_op_ty	operators[5] = {
		OP_APPEND,
		OP_HEREDOC,
		OP_PIPE,
		OP_REDIRECT,
		OP_INP_REDIRECT
	};

	i = 0;
	while (i < 5)
	{
		if (strsl_starts_with(str, cstr_view(op_str(operators[i]))))
		{
			if (out)
				*out = operators[i];
			return (true);
		}
		i++;
	}
	return (false);
}

const char	*op_str(t_op_ty op)
{
	static const char	*op_str[] = {
	[OP_PIPE] = "|",
	[OP_REDIRECT] = ">",
	[OP_INP_REDIRECT] = "<",
	[OP_APPEND] = ">>",
	[OP_HEREDOC] = "<<",
	};

	return (op_str[op]);
}
