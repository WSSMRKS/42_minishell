/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:10:30 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/15 15:24:16 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char *read_input(bool append_mode, void *data)
{
	char		*input;

	(void)data;
	if (append_mode)
		input = readline("> ");
	else
		input = readline("minishell$ ");
	return (input);
}

static t_symtab_stack	*get_symtab(void *data)
{
	t_ms	*ms;

	ms = (t_ms *)data;
	return (ms->be->global_symtabs);
}

static bool	cmdlist_has_heredoc(t_cmd_list *cmds)
{
	t_cmd_list	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->cmd->heredoc)
			return (true);
		curr = curr->next;
	}
	return (false);
}

static t_ms_status	evaluate(t_ms *ms)
{
	if (strcmp("ms_debug", ms->cmds->cmd->argv[0]) == 0)
		ft_debug(ms);
	if (strcmp("exit", ms->cmds->cmd->argv[0]) == 0)
		return (MS_EOF);
	if(ms->cmds)
	{
		ms->global_flags = cmdlist_has_heredoc(ms->cmds);
		ft_back_end(ms);
	}
	return (MS_OK);
}

void	repl(int argc, char **argv, char **envp)
{
	t_ms		ms;
	t_ms_status	status;

	ms.parser = parser_init(&ms, read_input, get_symtab);
	ft_init_ms(&ms);
	ft_init_be(&ms, argc, argv, envp);
	while (true) // read eval print loop REPL
	{
		status = parse_next_command(&ms.parser, &ms.cmds);
		if (status == MS_EOF)
			break ;
		else if (status == MS_ERROR)
		{
			perror("parse (memory) error");
			break ;
		}
		if (ms.parser.last_input.len > 0)
			add_history(cstr_ref(&ms.parser.last_input));
		status = evaluate(&ms);
		if (status != MS_OK)
			break ;
	}
	if (status == MS_EOF)
		ft_printf("exit\n");
	ft_cleanup_exit(&ms, 0);
}

