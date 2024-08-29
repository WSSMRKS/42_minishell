/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/29 13:03:01 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_init_ms(t_ms *ms, char **envp)
{
	(void) ms;
	(void) envp;

	ms->global_symtab = NULL;
	ms->cmds = NULL;
	ms->cmd = NULL;
	ms->garbage = malloc(sizeof(t_garbage) * 1);  //[ ] free me
	ms->garbage->heredoc = NULL;
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

int	ft_repl(int argc, char **argv, char **envp)
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
