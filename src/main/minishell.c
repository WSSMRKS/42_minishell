/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:17:01 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/15 15:19:45 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <signal.h>
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

// Signal handler for SIGCHLD (when child processes exit)
void handle_sigchld(int sig) {
    (void) sig;
	int status;
    pid_t pid;

    // Wait for all child processes that have exited
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("\nChild process %d terminated\n", pid);
    }
}

int	main(int argc, char **argv, char **envp)
{
	// Install the SIGINT handler
	struct sigaction	sa_int;
	sa_int.sa_handler = &handle_sigint;
	sa_int.sa_flags = SA_RESTART; // Restart interrupted system calls
	sigemptyset(&sa_int.sa_mask); // Don't block additional signals
	sigaction(SIGINT, &sa_int, NULL);

	// Install the SIGCHLD handler
	struct sigaction sa_chld;
	sa_chld.sa_handler = handle_sigchld;
	sa_chld.sa_flags = SA_RESTART;
	sigemptyset(&sa_chld.sa_mask);
	sigaction(SIGCHLD, &sa_chld, NULL);

	if (argc > 1)
	{
		ft_printf("Input arguments not supported, use Bash ;)\n");
		return (1);
	}
	repl(argc, argv, envp);
}
