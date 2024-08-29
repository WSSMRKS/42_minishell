/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/29 13:03:58 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_scan_cmds(t_ms *ms)
{
	if (ms->global_flags == 1) // has here_doc
		ft_here_doc(ms);
	if (!ms->cmds->next)
		ft_single_cmd(ms);
	else if (!ms->cmds->next->next)
		ft_two_cmds(ms);
	else
		ft_several_cmds(ms);
}

void	ft_single_cmd(t_ms *ms)
{
	(void) ms;
}

void	ft_two_cmds(t_ms *ms)
{
	(void) ms;
}

void	ft_several_cmds(t_ms *ms)
{
	(void) ms;
}

char	*ft_search_tmp(void)
{
	int		nb;
	int		found;
	char	*filename;
	char	*number;

	nb = 1;
	found = 0;
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

	if (!ms->garbage->heredoc)
	{
		ms->garbage->heredoc = malloc(sizeof(t_list_hdfiles) * 1);
		ms->garbage->heredoc->next = NULL;
	}
	curr = ms->garbage->heredoc;
	while (i < ms->garbage->nb_heredocs)
		curr = curr->next;
	ms->garbage->nb_heredocs += 1;
	curr->next = malloc(sizeof(t_list_hdfiles) * 1);
	curr->next->filename = filename;
	curr->next->next = NULL;
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

void	ft_hd_input(char *hd_del, t_redir_aim *filename, t_ms *ms)
{
	char		*line;
	int			ldel;
	int			fd;
	int			aux1;

	aux1 = 0;
	ldel = ft_strlen(hd_del);
	ms->garbage->nb_heredocs += 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
			ft_cleanup_exit(ms); //readline error;
		if (ft_strncmp(hd_del, line, ldel) == 0 && (int) ft_strlen(line) == ldel)
			break ;
		aux1++;
		printf("aux1 is %d", aux1);
		if (!filename)
		{
			filename = malloc(sizeof(t_redir_aim) * 1);
			filename->filename = malloc(sizeof(t_word_desc) * 1);
			filename->filename->word = ft_tmp_name(ms, &fd);
			filename->filename->flags = 0;
		}
		if (ft_putstr_fd_ret(line, fd) < 1 || ft_putstr_fd_ret("\n", fd) < 1)
			exit(errno);
		printf("line = %s\n", line);
		free(line);
	}
	close(fd);
	printf("still running");
	return ;
}

/*heredoc insights:
	- several heredocs in one command are handled left to right. only the most left here doc is handled.
	- even over several pipes heredoc is handled left to right.
*/
void	ft_here_doc(t_ms *ms)
{
	t_cmd_list		*cmd_list;
	t_list_redir	*curr_redir;

	cmd_list = ms->cmds;
	while((ms->global_flags & 1) != 0 && cmd_list != NULL) // loop through commands
	{
		curr_redir = cmd_list->cmd->redir;
		while ((cmd_list->cmd->flags & 1) != 0 &&	curr_redir != NULL)
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
