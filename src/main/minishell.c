/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:17:01 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/03 14:33:27 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
	(void) sig;
	// printf("\nCaught signal %d (SIGINT), ignoring Ctrl+C\n", sig);
	printf("\n");
	// Re-prompt the user after ignoring SIGINT
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

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


int	main(int argc, char **argv, char **envp)
{
	int	file_in;
	// Install the SIGINT handler
	struct sigaction	sa_int;
	sa_int.sa_handler = &handle_sigint;
	sa_int.sa_flags = SA_RESTART; // Restart interrupted system calls
	sigemptyset(&sa_int.sa_mask); // Don't block additional signals
	sigaction(SIGINT, &sa_int, NULL);
	// // Install the SIGCHLD handler
	// struct sigaction sa_chld;
	// sa_chld.sa_handler = handle_sigchld;
	// sa_chld.sa_flags = SA_RESTART;
	// sigemptyset(&sa_chld.sa_mask);
	// sigaction(SIGCHLD, &sa_chld, NULL);
	file_in = redirect_stdin(argc, argv);
	if (file_in == -1)
		return (1);
	if (argc > 1 && file_in == 0)
	{
		ft_printf("Input arguments not supported, use Bash ;)\n");
		return (1);
	}
	repl(argc, argv, envp);
}
