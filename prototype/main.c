/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/14 22:24:26 by dkoca            ###   ########.fr       */
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
#include <sys/types.h>
#include <dirent.h>

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1) // read eval print loop REPL
	{
		cmd = readline("minishell$ ");
		if (!cmd)
			break ;
		printf("cmd = %s", cmd);
		if (strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			break ;
		}
		printf("cmd: %s\n", cmd);
		free(cmd);
	}
	return (0);
}
