/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/01 19:24:51 by dkoca            ###   ########.fr       */
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
		return (readline("minishell$ "));
	else
		return (readline("> "));
}

int last_is_escaped(char *cmd)
{
	int len;
	len = ft_strlen(cmd);
	if (cmd[len - 1] == '\\')
	{
		if (len >= 2 && cmd[len - 2] == '\\')
		{
			printf("last 2 chrs = %c and %c\n", cmd[len -1], cmd[len -2]);
			return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
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
	// ft_init_ms(minishell, envp);
	mode = 0;
	while (1) // read eval print loop REPL
	{
		cmd = choose_prompt(mode);
		if (!cmd)
			break ;
		add_history(cmd);
		if (last_is_escaped(cmd) == TRUE)
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
