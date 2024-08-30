/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/28 15:52:41 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_ms(t_minishell *minishell, char **envp)
{
	(void) minishell;
	(void) envp;
}

void	ft_front_end(char *cmd)
{
	// (void) cmd;
	tokenizer(cmd);
}

char	*choose_prompt(int mode)
{
	if (mode == 0)
		return (readline("minishell$"));
	else
		return (readline("> "));
}

int	main(int argc, char **argv, char **envp)
{
	char			*cmd;
	int				mode;
	t_minishell		*minishell;

	(void)argc;
	if (argc >= 2)
	{
		return (127);
		// save exit code? 127?
	}
	(void)argv;
	(void)envp;
	(void)minishell;
	mode = 0;
	// ft_init_ms(minishell, envp);
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
