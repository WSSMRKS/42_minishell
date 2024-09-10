/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/10 13:35:59 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_front_end(char *cmd)
{
	(void) cmd;
}

char	*choose_prompt(int mode)
{
	// (void) mode;
	if (mode == 0)
		return (readline("minishell$ "));
	else
		return (readline("> "));
	// return (NULL);
}

void	ft_repl(int argc, char **argv, char **envp)
{
	int				mode;
	t_ms			ms;

	(void)argc;
	(void)argv;
	(void)envp;
	mode = 0;
	ft_init_ms(&ms);
	ft_init_be(&ms, argc, argv, envp);
	while (1) // read eval print loop REPL
	{
		ms.cmd = choose_prompt(mode);
		printf("{%s}\n", ms.cmd);
		if (!ms.cmd)
			break ;
		add_history(ms.cmd);
		if (ms.cmd && ms.cmd[0] != '\0' && ms.cmd[ft_strlen(ms.cmd) - 1] == '\\')
			mode = 1;
		if (strcmp(ms.cmd, "exit") == 0) /* needs to be rewritten */
		{
			free(ms.cmd);
			break ;
		}
		ft_front_end(ms.cmd);
		ft_back_end(&ms);
		free(ms.cmd);
	}
	rl_clear_history();
	ft_cleanup_exit(&ms, 0);
}
