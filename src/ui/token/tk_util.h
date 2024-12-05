/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_util.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:40:44 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 18:11:02 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TK_UTIL_H
# define TK_UTIL_H
# include "../../../headers/minishell.h"

void		span_printerr(t_str_slice s, size_t err_i, const char *err);
void		token_print(const t_token *token, int fd);
const char	*op_str(t_op_ty op);

void		vec_push_tk(t_vec *vec, t_token tk);
t_token		tk_empty(t_token_ty ty);
t_token		tk_word(t_str_slice word);
t_token		tk_op(t_op_ty op);
t_token		tk_lit(t_str_slice quoted);
t_token		tk_dquote(t_str_slice quoted);
bool		token_has_str(t_token *token);

bool		is_word_delimiter(char c);
void		strsl_trim_start_delim(t_str_slice *s);
size_t		bounded_token_len(const char *str, char bounds, size_t *out);
size_t		word_len(const char *str, size_t *out);
size_t		comment_len(const char *str);
size_t		var_len(const char *str, size_t *out);
bool		str_is_operator(t_str_slice str, t_op_ty *out);
bool		str_starts_with_op(t_str_slice str, t_op_ty *out);

void		remove_dup_seperators(t_vec *tokens);
bool		is_redundant_separator(t_vec *tokens, size_t i);
void		remove_redundant_separators(t_vec *tokens);
void		merge_chained_word_tokens(t_vec *tokens);
void		remove_all_seperators(t_vec *tokens);

#endif
