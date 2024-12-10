/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/10 13:07:11 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <stdbool.h>
#include <stddef.h>

char	*ft_search_tmp(void)
{
	int		nb;
	char	*filename;
	char	*number;

	nb = 1;
	while (nb < INT_MAX)
	{
		number = ft_itoa(nb);
		filename = ft_strjoin("/tmp/ms_tmp_", number);
		free(number);
		number = NULL;
		if (access(filename, F_OK) != 0)
			break ;
		free(filename);
		filename = NULL;
		nb++;
	}
	return (filename);
}

void	ft_garbage_add(char *filename, t_ms *ms)
{
	int				i;
	t_list_hdfiles	*curr;

	i = 1;
	curr = ms->be->garbage->heredoc;
	if (ms->be->garbage->nb_heredocs == 0)
	{
		curr = ft_calloc(sizeof(t_list_hdfiles), 1);
		curr->next = NULL;
		ms->be->garbage->heredoc = curr;
	}
	else
	{
		while (i++ < ms->be->garbage->nb_heredocs)
			curr = curr->next;
		curr->next = ft_calloc(sizeof(t_list_hdfiles), 1);
		curr->next->next = NULL;
		curr = curr->next;
	}
	curr->filename = ft_strdup(filename);
	ms->be->garbage->nb_heredocs += 1;
}

char	*ft_tmp_name(t_ms *ms, int *fd)
{
	char		*filename;

	filename = ft_search_tmp();
	*fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*fd < 1)
		exit(EBADF);
	else
		ft_garbage_add(filename, ms);
	return (filename);
}

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

bool	char_is_escaped(const char *str, size_t i)
{
	size_t	escaped;

	escaped = 0;
	while (i > 0 && str[i - 1] == '\\')
	{
		escaped++;
		i--;
	}
	return (escaped % 2);
}

static void	str_expand_vars2(t_str *str, t_stab_st *st, int last_ret)
{
	t_str	var_str;
	size_t	var_size;
	size_t	i;
	char	*buf;
	t_str_slice var;

	i = 0;
	while (i < str->len)
	{
		buf = cstr_mut(str);
		if (buf[i] == '$' && !char_is_escaped(cstr_ref(str), i))
		{
			var_str = str_clone_from(cstr_slice(&buf[i+1], var_len(&buf[i], &var_size) - 1));
			if (var_size == 0)
			{
				i++;
				continue;
			}
			str_remove_range(str, i, i + var_size);
			if (strsl_eq(str_view(&var_str), cstr_slice("?", 1)))
				str_insert_itoa(last_ret, base10(), str, i);
			else
			{
				var = cstr_view(ft_lookup_stab(st, (char *)cstr_ref(&var_str)));
				if (var.str)
				{
					str_insertstr(str, i, var);
					i += var.len;
				}
			}
			str_destroy(&var_str);
		}
		else
			i++;
	}
}

/// Returns NULL if there was a malloc error
char	*ft_hd_var_expansion(t_ms *ms, char *l)
{
	t_str	wrapped;

	wrapped = str_from2(l);
	str_expand_vars2(&wrapped, ms->be->global_stabs, g_signal);
	str_unescape_chars2(&wrapped);
	return (cstr_take(&wrapped));
}

void	ft_hd_input(t_list_redir *cl, t_ms *ms)
{
	char		*l;
	int			l_nb;
	int			ldel;
	int			fd;

	l_nb = 0;
	fd = -1;
	ldel = ft_strlen(cl->hd_del);
	while (true && g_signal != 130)
	{
		l = readline("> ");
		if (!cl->target.filename)
			cl->target.filename = ft_tmp_name(ms, &fd);
		if (g_signal == 130)
			break ;
		if (!l && ft_printf_fd(2, "minishell: warning: here-document at line %d \
delimited by end-of-file (wanted `%s')\n", l_nb, cl->hd_del) != 0)
			break ;
		if (ft_strncmp(cl->hd_del, l, ldel) == 0 && (int) ft_strlen(l) == ldel)
			break ;
		l = ft_hd_var_expansion(ms, l);
		if (l == NULL || ft_putstr_fd(l, fd) < 0 || ft_putstr_fd("\n", fd) < 0)
		{
			free(l);
			exit(errno);
		}
		l_nb++;
		free(l);
		l = NULL;
	}
	free(l);
	close(fd);
}

void	handle_sigint_hd(int sig)
{
	(void)sig;
	g_signal = 128 + SIGINT;
	rl_replace_line("", 0);
	ioctl(STDOUT_FILENO, TIOCSTI, "\n");
}

/*heredoc insights:
	- several heredocs in one command are handled left to right.
	  only the most left here doc is handled.
	- even over several pipes heredoc is handled left to right.
*/
void	ft_here_doc(t_ms *ms)
{
	t_cmd_list			*cmd_list;
	t_list_redir		*curr_redir;
	struct sigaction	sa_int_hd;

	sa_int_hd.sa_handler = &handle_sigint_hd;
	sa_int_hd.sa_flags = SA_RESTART;
	sigemptyset(&sa_int_hd.sa_mask);
	sigaction(SIGINT, &sa_int_hd, NULL);
	cmd_list = ms->cmds;
	while ((ms->global_flags & 1) != 0 && cmd_list != NULL && g_signal != 130)
	{
		curr_redir = cmd_list->cmd.redir;
		while (cmd_list->cmd.heredoc && curr_redir != NULL && g_signal != 130)
		{
			if (curr_redir->instruction == redir_here_doc)
			{
				ft_hd_input(curr_redir, ms);
			}
			curr_redir = curr_redir->next;
		}
		cmd_list = cmd_list->next;
	}
	if (!signal(SIGINT, SIG_DFL))
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
}
