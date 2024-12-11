/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/11 17:26:40 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// for double quotes only unescape <‘$’, ‘"’, ‘\’, newline>.
static void	str_unescape_chars2(t_str *str)
{
	size_t	i;
	char	*buf;

	i = 0;
	while (true)
	{
		buf = cstr_mut(str);
		if (buf[i] == 0)
			break ;
		if (buf[i] == '\\' && buf[i + 1] != 0
			&& ft_strchr("\\$", buf[i + 1]))
			str_remove(str, i);
		i++;
	}
}

void	str_expand_vars(t_str *str, t_stab_st *st, int last_ret);

/// Returns NULL if there was a malloc error
char	*ft_hd_var_expansion(t_ms *ms, char *l)
{
	t_str	wrapped;

	wrapped = str_from2(l);
	str_expand_vars(&wrapped, ms->be->global_stabs, g_signal);
	str_unescape_chars2(&wrapped);
	return (cstr_take(&wrapped));
}

void	ft_hd_cleanup_exit(t_ms *ms, char *line, int fd)
{
	free(line);
	close(fd);
	if (ms->be->saved_std[0] != 0 || ms->be->saved_std[1] != 0)
	{
		close(ms->be->saved_std[0]);
		close(ms->be->saved_std[1]);
	}
	ft_close_all_fds(ms);
	ft_clear_ast(ms);
	ft_clear_be(ms);
	ft_cleanup_exit(ms, errno);
}

void	ft_hd_input(t_list_redir *cl, t_ms *ms)
{
	char		*l;
	int			l_nb;
	size_t		ldel;
	int			fd;

	l_nb = 0;
	fd = -1;
	ldel = ft_strlen(cl->hd_del);
	while (true && g_signal != 130 && l_nb++ > -1)
	{
		l = readline("> ");
		if (!cl->target.filename)
			cl->target.filename = ft_tmp_name(ms, &fd);
		if (g_signal == 130 || (!l && ft_printf_fd(2, "minishell: warning: here-document at line %d \
delimited by end-of-file (wanted `%s')\n", l_nb, cl->hd_del) != 0)
			|| (ft_strncmp(cl->hd_del, l, ldel) == 0 && ft_strlen(l) == ldel))
			break ;
		l = ft_hd_var_expansion(ms, l);
		if (l == NULL || ft_putstr_fd(l, fd) < 0 || ft_putstr_fd("\n", fd) < 0)
			ft_hd_cleanup_exit(ms, l, fd);
		free(l);
		l = NULL;
	}
	free(l);
	close(fd);
}
