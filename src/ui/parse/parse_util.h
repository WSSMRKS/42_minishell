/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:51 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 18:10:55 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTIL_H
# define PARSE_UTIL_H
# include "../../../headers/minishell.h"

void			debug_print_simple_com(int fd, t_simple_com *cmd, bool parser);
bool			ast_has_integrity(t_vec *ast);
void			str_push_ast(t_str *str, t_ast *ast, bool first);
void			ast_printerr(t_vec *ast, size_t err_i, const char *err);

t_redir_type	op_to_redir(t_op op);
bool			add_redirection(t_simple_com *cmd, t_op *op);

#endif
