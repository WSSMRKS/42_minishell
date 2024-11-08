/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/08 16:15:19 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_front_end(char *cmd)
{
	(void) cmd;
	// t_token *tokens;
	// // t_cmd_list *cmd_list;
	// // (void) cmd;
	// tokenizer(cmd, &tokens);
	// printf("first token = ");
	// print_token(tokens);
	// // parse(tokens);
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
	int				i;

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
	i = 0;
	ft_init_ms(&ms);
	ft_init_be(&ms, argc, argv, envp);
	while (1) // read eval print loop REPL
	{
		ms.cmd = choose_prompt(mode);
		if (!ms.cmd)
		{
			printf("exit\n");
			break ;
		}
		else
			printf("{%s}\n", ms.cmd);
		add_history(ms.cmd);
		if (last_is_escaped(ms.cmd) == TRUE)
			mode = 1;
		if (strcmp(ms.cmd, "ms_debug") == 0)
			ft_debug(&ms);
		if (strcmp(ms.cmd, "exit") == 0) /* needs to be rewritten */
		{
			free(ms.cmd);
			ms.cmd = NULL;
			break ;
		}
		ft_front_end(ms.cmd);
		if(ms.cmds)
			ft_back_end(&ms);
		i++;
	}
	ft_cleanup_exit(&ms, 0);
}

