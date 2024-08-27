/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/27 15:34:04 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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

}

void	ft_two_cmds(t_ms *ms);
{

}

void	ft_several_cmds(t_ms *ms)
{

}

void	ft_tmp_write(char *line, t_ms *ms, t_word_desc *filename)
{

}

void	ft_hd_input(char *hd_del, t_word_desc *filename, t_ms *ms)
{
	int		reading;
	char	*line;
	int		ldel;

	reading = 1;
	ldel = ft_strlen(hd_del);
	ms->garbage->nb_heredocs += 1;
	while (reading != 0)
	{
		line = readline("> ");
		if (!line)
			ft_cleanup_exit(ms, line);			//readline error;
		if (ft_strncmp(*hd_del, line, ldel) && ft_strlen(line) == ldel)
			reading = 0;
		ft_tmp_write(line, ms, filename);
		free(line);
	}
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
	while(ms->global_flags & 1 != 0 && cmd_list != NULL) // loop through commands
	{
		curr_redir = cmd_list->cmd->redir;
		while (cmd_list->cmd->flags & 1 != 0 &&	curr_redir != NULL)
		{
			if (curr_redir->instruction == redir_here_doc)
			{
				ft_hd_input(curr_redir->hd_del, curr_redir->from, ms);
			}
			curr_redir = curr_redir->next;
		}
		cmd_list = cmd_list->next;
	}

	// handle all here_docs. here doc tempfiles need to be stored in a linked list?
}
