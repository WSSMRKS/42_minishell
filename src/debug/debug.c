/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/10 13:43:11 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_deb_here_doc(t_ms *ms)
{
	setbuf(stdout, 0);
	ms->global_flags = 1;
	ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	ms->cmds->next = NULL;
	ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	ms->cmds->cmd->flags = 1;
	ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	ms->cmds->cmd->redir->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	ms->cmds->cmd->redir->next->next = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
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

void	ft_deb_commands(t_ms *ms)
{
	(void) ms;

	ms->cmd = ft_strdup("cat");
	ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	ms->cmds->cmd->words->word = ft_strdup("cat");
	ms->cmds->cmd->flags = 0;
	ft_executor(ms);

	printf("test for right priority if several redirects are present\n");
	printf("test if heredocs and input redirects are prioritized right\n");
	printf("test if redirects to pipes are still there?\n");
	printf("test if one single command is executed correctly?\n");
	printf("test if several commands are executed correctly?\n");
	printf("test if single command with several redirects is executed correctly?\n");
	printf("test if several commands with several redirects are executed correctly?\n");
	free(ms->cmds->cmd->words->word);
	free(ms->cmds->cmd->words);
	free(ms->cmds->cmd);
	free(ms->cmds);
	free(ms->cmd);
	ft_clear_be(ms);
	ms->cmd = ft_strdup("ls");
	ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	ft_reinit_be(ms);
	ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	ms->cmds->cmd->words->word = ft_strdup("ls");
	ms->cmds->cmd->flags = 0;
	ft_executor(ms);
	free(ms->cmds->cmd->words->word);
	free(ms->cmds->cmd->words);
	free(ms->cmds->cmd);
	free(ms->cmds);
	free(ms->cmd);
}

void	ft_debug(t_ms *ms)
{
	char	*mode;

	printf("Debug cases:\n");
	printf("- here_doc\n");
	printf("- command_execution\n");
	mode = readline("Choose debug case: ");
	if (strncmp(mode, "here_doc", 8) == 0 && ft_strlen(mode) == 8)
		ft_deb_here_doc(ms);
	else if (strncmp(mode, "command_execution", 17) == 0
		&& ft_strlen(mode) == 17)
		ft_deb_commands(ms);
}
