/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/29 18:53:51 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_debug(t_ms *ms)
{
	(void) ms;

	// setvbuf(stdout, NULL, _IONBF, 0);
	ms->global_flags = 1;
	ms->cmds = malloc(sizeof(t_cmd_list) * 1); // [ ] free me
	ms->cmds->next = NULL;
	ms->cmds->cmd = malloc(sizeof(t_simple_com) * 1); // [ ] free me
	ms->cmds->cmd->flags = 1;
	ms->cmds->cmd->redir = malloc(sizeof(t_list_redir) * 1); // [ ] free me
	ms->cmds->cmd->redir->next = malloc(sizeof(t_list_redir) * 1); // [ ] free me
	ms->cmds->cmd->redir->next->next = malloc(sizeof(t_list_redir) * 1); // [ ] free me
	ms->cmds->cmd->redir->next->next->next = NULL;
	ms->cmds->cmd->redir->from = NULL;
	ms->cmds->cmd->redir->next->from = NULL;
	ms->cmds->cmd->redir->next->next->from = NULL;
	ms->cmds->cmd->redir->instruction = redir_here_doc;
	ms->cmds->cmd->redir->next->instruction = redir_here_doc;
	ms->cmds->cmd->redir->next->next->instruction = redir_here_doc;
	ms->cmds->cmd->redir->hd_del = ft_strdup("eof");
	ms->cmds->cmd->redir->next->hd_del = ft_strdup("eof");
	ms->cmds->cmd->redir->next->next->hd_del = ft_strdup("eof");
	ft_here_doc(ms);
}
