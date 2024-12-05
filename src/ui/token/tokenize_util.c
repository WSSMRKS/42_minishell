/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:00:38 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 17:59:31 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	vec_push_tk(t_vec *vec, t_token tk)
{
	vec_push(vec, &tk);
}

bool	is_word_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == DOUBLE_QUO || c == SINGLE_QUO);
}

/// @brief Removes leading whitespace from a stringview.
/// @param s The stringview to trim.
void	strsl_trim_start_delim(t_str_slice *s)
{
	while (s->len && is_word_delimiter(*s->str))
	{
		s->str++;
		s->len--;
	}
}

/// prints
/// ```
/// minishell syntax error: <error message>\n
/// echo hello "world\n
///            ^
/// ```
/// input is allowed to be multiline, though only the affected line will print
void	span_printerr(t_str_slice s, size_t err_i, const char *err)
{
	size_t	i;
	t_vec	lines;

	ft_printf_fd(STDERR, "minishell syntax error: %s\n", err);
	lines = strsl_split(s, cstr_slice("\n", 1));
	if (lines.mem_err)
		return ;
	i = 0;
	while (i < lines.len)
	{
		s = *(t_str_slice *)vec_get_at(&lines, i++);
		if (err_i < s.len)
		{
			ft_putstrsl_fd(s, STDERR);
			write(STDERR, "\n", 1);
			break ;
		}
		err_i -= s.len + 1;
	}
	ft_putfill_fd(' ', STDERR, err_i);
	ft_putchar_fd('^', STDERR);
	ft_putchar_fd('\n', STDERR);
	vec_destroy(&lines, NULL);
}
