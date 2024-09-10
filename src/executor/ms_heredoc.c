/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/10 10:44:23 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
		if (access(filename, F_OK) != 0)
			break ;
		free(filename);
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
	curr->filename = filename;
	ms->be->garbage->nb_heredocs += 1;
}

/* [ ] Tempfile behaviour over several instances of minishell? One global tmpfile listing the current tempfile count?
		do we need to handle the splitsecond between searching and writing?*/
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

void	ft_hd_input(char *hd_del, t_redir_aim *from, t_ms *ms)
{
	char		*line;
	int			ldel;
	int			fd;
	int			line_nb;

	line_nb = 0;
	ldel = ft_strlen(hd_del);
	while (1)
	{
		line = readline("> ");
		if (!line)
			ft_cleanup_exit(ms, EIO); //readline error;
		if (!from)
		{
			from = ft_calloc(sizeof(t_redir_aim), 1);
			from->filename = ft_tmp_name(ms, &fd);
			from->flags = 0;
		}
		if (ft_strncmp(hd_del, line, ldel) == 0 && (int) ft_strlen(line) == ldel)
			break ;
		if ((ft_putstr_fd_ret(line, fd) < 0 || ft_putstr_fd_ret("\n", fd) < 0))
			exit(errno);
		line_nb++;
		free(line);
	}
	close(fd);
}

/*heredoc insights:
	- several heredocs in one command are handled left to right.
	  only the most left here doc is handled.
	- even over several pipes heredoc is handled left to right.
*/
void	ft_here_doc(t_ms *ms)
{
	t_cmd_list		*cmd_list;
	t_list_redir	*curr_redir;

	cmd_list = ms->cmds;
	while ((ms->global_flags & 1) != 0 && cmd_list != NULL)
	{
		curr_redir = cmd_list->cmd->redir;
		while ((cmd_list->cmd->flags & 1) != 0 && curr_redir != NULL)
		{
			if (curr_redir->instruction == redir_here_doc)
			{
				ft_hd_input(curr_redir->hd_del, curr_redir->from, ms);
			}
			curr_redir = curr_redir->next;
		}
		cmd_list = cmd_list->next;
	}
}
