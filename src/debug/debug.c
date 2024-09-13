/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/13 17:47:15 by maweiss          ###   ########.fr       */
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
}

void	ft_deb_commands(t_ms *ms)
{
	int case_nb;

	case_nb = 0;
	setbuf(stdout, 0);

	if (case_nb == 0)
	{
		ms->cmd = ft_strdup("cat");
		ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
		ms->cmds->next = NULL;
		ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
		ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->word = ft_strdup("cat");
		ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
		ms->cmds->cmd->words->next->word = ft_strdup("./valgrind_line.txt");
		ms->cmds->cmd->words->next->next = NULL;
		ms->be->nb_cmds = 1;
		ms->cmds->cmd->flags = 0;
	}
	// else if (case_nb == 1)
	// {
	// 	ms->cmd = ft_strdup("ls -l | cat -e");
	// 	ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	// 	ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	// 	ms->cmds->next->next = NULL;
	// 	ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	// 	ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->cmd->words->word = ft_strdup("ls");
	// 	ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->cmd->words->next->word = ft_strdup("-l");
	// 	ms->cmds->cmd->words->next->next = NULL;
	// 	ms->cmds->cmd->flags = 0;
	// 	ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words->word = ft_strdup("cat");
	// 	ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words->next->word = ft_strdup("-e");
	// 	ms->cmds->next->cmd->words->next->next = NULL;
	// 	ms->cmds->next->cmd->flags = 0;
	// 	ms->be->nb_cmds = 2;
	// }
	// else if (case_nb == 2)
	// {
	// 	ms->cmd = ft_strdup("ls -l > file1 | cat -e > file2");
	// 	ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	// 	ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	// 	ms->cmds->next->next = NULL;
	// 	ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	// 	ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->cmd->words->word = ft_strdup("ls");
	// 	ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->cmd->words->next->word = ft_strdup("-l");
	// 	ms->cmds->cmd->words->next->next = NULL;
	// 	ms->cmds->cmd->flags = 0;
	// 	ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	// 	ms->cmds->cmd->redir->instruction = redir_outfile;
	// 	ms->cmds->cmd->redir->from = NULL;
	// 	ms->cmds->cmd->redir->to = ft_calloc(sizeof(t_redir_aim), 1); // [ ] free me
	// 	ms->cmds->cmd->redir->to->filename = ft_strdup("file1");
	// 	ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words->word = ft_strdup("cat");
	// 	ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words->next->word = ft_strdup("-e");
	// 	ms->cmds->next->cmd->words->next->next = NULL;
	// 	ms->cmds->next->cmd->flags = 0;
	// 	ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	// 	ms->cmds->next->cmd->redir->instruction = redir_outfile;
	// 	ms->cmds->next->cmd->redir->from = NULL;
	// 	ms->cmds->next->cmd->redir->to = ft_strdup("file2");
	// 	ms->be->nb_cmds = 2;
	// }
	// else if (case_nb == 3)
	// {
	// 	ms->cmd = ft_strdup("ls -l > file1 | cat -e > file2 | wc -l > file3");
	// 	ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	// 	ms->cmds->next = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	// 	ms->cmds->next->next = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	// 	ms->cmds->next->next->next = NULL;
	// 	ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	// 	ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->cmd->words->word = ft_strdup("ls");
	// 	ms->cmds->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->cmd->words->next->word = ft_strdup("-l");
	// 	ms->cmds->cmd->words->next->next = NULL;
	// 	ms->cmds->cmd->flags = 0;
	// 	ms->cmds->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	// 	ms->cmds->cmd->redir->instruction = redir_outfile;
	// 	ms->cmds->cmd->redir->from = NULL;
	// 	ms->cmds->cmd->redir->to = ft_strdup("file1");
	// 	ms->cmds->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words->word = ft_strdup("cat");
	// 	ms->cmds->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->next->cmd->words->next->word = ft_strdup("-e");
	// 	ms->cmds->next->cmd->words->next->next = NULL;
	// 	ms->cmds->next->cmd->flags = 0;
	// 	ms->cmds->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	// 	ms->cmds->next->cmd->redir->instruction = redir_oufile;
	// 	ms->cmds->next->cmd->redir->from = NULL;
	// 	ms->cmds->next->cmd->redir->to = ft_strdup("file2");
	// 	ms->cmds->next->next->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	// 	ms->cmds->next->next->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->next->next->cmd->words->word = ft_strdup("wc");
	// 	ms->cmds->next->next->cmd->words->next = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// 	ms->cmds->next->next->cmd->words->next->word = ft_strdup("-l");
	// 	ms->cmds->next->next->cmd->words->next->next = NULL;
	// 	ms->cmds->next->next->cmd->flags = 0;
	// 	ms->cmds->next->next->cmd->redir = ft_calloc(sizeof(t_list_redir), 1); // [ ] free me
	// 	ms->cmds->next->next->cmd->redir->instruction = redir_outfile;
	// 	ms->cmds->next->next->cmd->redir->from = NULL;
	// 	ms->cmds->next->next->cmd->redir->to = ft_strdup("file3");
	// 	ms->be->nb_cmds = 3;
	// }


	// printf("test for right priority if several redirects are present\n");
	// printf("test if heredocs and input redirects are prioritized right\n");
	// printf("test if redirects to pipes are still there?\n");
	// printf("test if one single command is executed correctly?\n");
	// printf("test if several commands are executed correctly?\n");
	// printf("test if single command with several redirects is executed correctly?\n");
	// printf("test if several commands with several redirects are executed correctly?\n");
	// ms->cmd = ft_strdup("ls");
	// ms->cmds = ft_calloc(sizeof(t_cmd_list), 1); // [ ] free me
	// ft_reinit_be(ms);
	// ms->cmds->cmd = ft_calloc(sizeof(t_simple_com), 1); // [ ] free me
	// ms->cmds->cmd->words = ft_calloc(sizeof(t_list_words), 1); // [ ] free me
	// ms->cmds->cmd->words->word = ft_strdup("ls");
	// ms->cmds->cmd->flags = 0;
	// ft_executor(ms);
	// free(ms->cmds->cmd->words->word);
	// free(ms->cmds->cmd->words);
	// free(ms->cmds->cmd);
	// free(ms->cmds);
	// free(ms->cmd);
}

void	ft_debug(t_ms *ms)
{
	char	*mode;

	printf("Debug cases:\n");
	printf("0 - here_doc\n");
	printf("1 - command_execution\n");
	mode = readline("Choose debug case: ");

	if (strncmp(mode, "0", 8) == 0 && ft_strlen(mode) == 1)
		ft_deb_here_doc(ms);
	else if (strncmp(mode, "1", 1) == 0
		&& ft_strlen(mode) == 1)
		ft_deb_commands(ms);
	else
		printf("Error: wrong selection\n");
}
