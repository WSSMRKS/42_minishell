/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/16 10:37:18 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*choose_prompt(int mode)
{
	if (mode == 0)
		return(readline("minishell$ "));
	else
		return(readline("> "));
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	int		mode;

	(void)argc;
	(void)argv;
	(void)envp;
	mode = 0;
	while (1) // read eval print loop REPL
	{

		cmd = choose_prompt(mode);
		if (!cmd)
			break ;
		if (cmd[strlen(cmd) - 1] == '\\')
			mode = 1;
		if (strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			break ;
		}
		printf("cmd: %s\n", cmd);
		free(cmd);
	}
	exit(EXIT_SUCCESS);
}
