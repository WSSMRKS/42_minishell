/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/19 13:11:01 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*choose_prompt(int mode)
{
	if (mode == 0)
		return (readline("minishell$ "));
	else
		return (readline("> "));
}

int	main(int argc, char **argv, char **envp)
{
	char			*cmd;
	int				mode;
	t_minishell		*minishell;

	(void)argc;
	(void)argv;
	(void)envp;
	mode = 0;
	ft_init_ms(*minishell, envp);
	while (1) // read eval print loop REPL
	{
		cmd = choose_prompt(mode);
		if (!cmd)
			break ;
		add_history(cmd);
		if (cmd[strlen(cmd) - 1] == '\\')
			mode = 1;
		if (strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			break ;
		}
		ft_front_end(cmd);
		printf("cmd: %s\n", cmd);
		free(cmd);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
