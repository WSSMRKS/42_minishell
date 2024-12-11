/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wssmrks <wssmrks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:17:01 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/07 23:46:43 by wssmrks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

int	g_signal = 0;

char	*in_file_ref(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '\0')
        {
            // Check if there's a next argument (file name)
            if (i + 1 < argc)
                return (argv[i + 1]);
            return (NULL);
        }
        i++;
    }
    return (NULL);
}


int	redirect_stdin(int argc, char **argv)
{
    char	*filename;
    int		fd;

    filename = in_file_ref(argc, argv);
    if (!filename)
        return (0); // No file specified, keep using standard input

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (-1);
    }

    // Duplicate fd to STDIN (fd 0)
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("Error redirecting stdin");
        close(fd);
        return (-1);
    }

    // Close the original fd as it's no longer needed
    close(fd);
    return (1);
}

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
	if (signal(SIGQUIT, SIG_IGN)) {
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
	repl(argc, argv, envp);
}
