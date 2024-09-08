/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/07 20:04:57 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_front_end(char *cmd)
{
	t_token *tokens;
	t_cmd_list *cmd_list;
	// (void) cmd;
	tokenizer(cmd, &tokens);
	printf("first token = ");
	print_token(tokens);
	
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

void	ft_repl(int argc, char **argv, char **envp)
{
	int				mode;
	t_ms			ms;

	(void)argc;
	// if (argc >= 2)
	// {
		// return (127);
		// save exit code? 127?
	// }
	(void)argv;
	(void)envp;
	// ft_init_ms(minishell, envp);
	mode = 0;
	ft_init_ms(&ms, argc, argv, envp);
	while (1) // read eval print loop REPL
	{
		ms.cmd = choose_prompt(mode);
		printf("{%s}\n", ms.cmd);
		if (!ms.cmd)
			break ;
		add_history(ms.cmd);
		if (last_is_escaped(ms.cmd) == TRUE)
			mode = 1;
		if (strcmp(ms.cmd, "exit") == 0)
		{
			free(ms.cmd);
			break ;
		}
		if (strcmp(ms.cmd, "ms_debug") == 0)
		{
			ft_debug(&ms);
		}
		ft_front_end(ms.cmd);
		free(ms.cmd);
	}
	rl_clear_history();
	ft_cleanup_exit(&ms, 0);
}
