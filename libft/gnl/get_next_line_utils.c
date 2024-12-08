/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:17:26 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:02:59 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	del_state(void *content)
{
	t_state	*st;

	st = content;
	if (st->buf)
		free(st->buf);
	free(st);
}

t_state	*new_state(int32_t fd)
{
	t_state	*out;

	out = malloc(sizeof(t_state));
	if (!out)
		return (0);
	out->buf = 0;
	out->buf_pos = out->buf;
	out->remaining = 0;
	out->fd = fd;
	return (out);
}

char	*read_into_buf(t_state *st)
{
	if (!st->buf)
	{
		st->remaining = -1;
		st->buf = malloc(BUFFER_SIZE);
		if (!st->buf)
			return (0);
	}
	st->remaining = read(st->fd, st->buf, BUFFER_SIZE);
	if (st->remaining <= 0)
	{
		free(st->buf);
		st->buf = 0;
		return (0);
	}
	st->buf_pos = st->buf;
	return (st->buf);
}

/**
 *  Creates a new string with new_len + 1 bytes,
 *  fills it from the back with max str_len bytes.
 *
 *  ```
 *  (str = "abc", str_len = 3, new_len = 5):
 *
 *  buf = malloc(5 + 1);
 *  _____i: 0 1 2 3 4 5
 *  buf[i]: - - a b c 0
 *  _______/\
 *  _______||
 *  _______out
 *  ```
 */
char	*new_str_fill_back(char *str, size_t str_len, size_t new_len)
{
	char	*out;

	out = malloc(new_len + 1);
	if (!out)
		return (0);
	out[new_len] = 0;
	ft_memcpy(out + new_len - str_len, str, str_len);
	return (out);
}

// returns length until nl (including nl)
// returns 0 if no nl
size_t	len_until_nl(char *str, size_t str_len)
{
	size_t	len;
	char	*nl_pos;

	len = 0;
	nl_pos = ft_memchr(str, '\n', str_len);
	if (nl_pos)
		len = 1 + nl_pos - str;
	return (len);
}
