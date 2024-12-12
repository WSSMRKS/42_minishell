/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:17:01 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/12 12:02:17 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

int	g_signal = 0;

void	put_cmd_to_stdin(char *cmd)
{
	int	pipes[2];

	if (pipe(pipes) == -1)
		return ;
	dup2(pipes[0], STDIN);
	close(pipes[0]);
	ft_putstr_fd(cmd, pipes[1]);
	close(pipes[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	if (signal(SIGQUIT, SIG_IGN))
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
		put_cmd_to_stdin(argv[2]);
	else if (argc > 1)
	{
		ft_printf_fd(STDOUT, "Usage: %s -c <command>\n", argv[0]);
		return (1);
	}
	ft_init_ms(&ms);
	ft_init_be(&ms, argc, argv, envp);
	repl(&ms);
}
