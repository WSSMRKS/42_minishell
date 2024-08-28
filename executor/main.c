/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/28 16:45:35 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_init_ms(t_ms *ms, char **envp)
{
	(void) ms;
	(void) envp;

	ms->global_symtab = NULL;
	ms->cmds = NULL;
	ms->cmd = NULL;
	ms->garbage = malloc(sizeof(t_garbage) * 1);  //[ ] free me
	ms->garbage->nb_heredocs = 0;
}

void	ft_front_end(char *cmd)
{
	(void) cmd;
}

char	*choose_prompt(int mode)
{
	if (mode == 0)
		return (readline("minishell$ "));
	else
		return (readline("> "));
}

void	ft_debug(t_ms *ms)
{
	(void) ms;

	ms->global_flags = 1;
	ms->cmds = malloc(sizeof(t_cmd_list) * 1); // [ ] free me
	ms->cmds->next = NULL;
	ms->cmds->cmd = malloc(sizeof(t_simple_com) * 1); // [ ] free me
	ms->cmds->cmd->flags &= 1;
	ms->cmds->cmd->redir = malloc(sizeof(t_list_redir) * 1); // [ ] free me
	ms->cmds->cmd->redir->next = malloc(sizeof(t_list_redir) * 1); // [ ] free me
	ms->cmds->cmd->redir->next->next = malloc(sizeof(t_list_redir) * 1); // [ ] free me
	ms->cmds->cmd->redir->instruction = redir_here_doc;
	ms->cmds->cmd->redir->next->instruction = redir_here_doc;
	ms->cmds->cmd->redir->next->next->instruction = redir_here_doc;
	ms->cmds->cmd->redir->hd_del = ft_strdup("eof");
	ms->cmds->cmd->redir->next->hd_del = ft_strdup("eof");
	ms->cmds->cmd->redir->next->next->hd_del = ft_strdup("eof");
	printf("we are here\n");
	ft_here_doc(ms);
}

int	main(int argc, char **argv, char **envp)
{
	int				mode;
	t_ms			ms;

	(void)argc;
	(void)argv;
	(void)envp;
	mode = 0;
	ft_init_ms(&ms, envp);
	while (1) // read eval print loop REPL
	{
		ms.cmd = choose_prompt(mode);
		if (!ms.cmd)
			break ;
		add_history(ms.cmd);
		if (ms.cmd[strlen(ms.cmd) - 1] == '\\')
			mode = 1;
		if (strcmp(ms.cmd, "exit") == 0)
		{
			free(ms.cmd);
			break ;
		}
		if (strcmp(ms.cmd, "ms_debug") == 0)
		{
			ft_debug(&ms);
		}
		ft_front_end(ms.cmd);
		printf("cmd: %s\n", ms.cmd);
		free(ms.cmd);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
