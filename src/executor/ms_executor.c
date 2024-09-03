/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/03 16:46:55 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_redir_handler(t_ms *ms, t_cmd_list *curr)
{
	t_list_redir	*rd;

	rd = curr->cmd->redir;
	while (rd)
	{
		if (curr->cmd->prio_in == 3 && rd->instruction == redir_here_doc
			&& rd->rightmost == true)
			ft_infile();
		else if (curr->cmd->prio_in == 2
			&& rd->instruction == redir_infile && rd->rightmost == true)
			ft_infile();
		else if (curr->cmd->prio_in == 1
			&& rd->instruction == redir_inpipe)
			ft_inpipe();
		if (curr->cmd->prio_out == 3 && rd->instruction == redir_append
			&& rd->rightmost == true)
			ft_outfile();
		else if (curr->cmd->prio_out == 2
			&& rd->instruction == redir_outfile && rd->rightmost == true)
			ft_outfile();
		else if (curr->cmd->prio_out == 1
			&& rd->instruction == redir_outpipe)
			ft_outpipe();
		rd = rd->next;
	}
}

void	ft_ex_prio(t_ms *ms, t_cmd_list *curr)
{
	t_list_redir	*rd;

	rd = curr->cmd->redir;
	while (rd)
	{
		if (rd->instruction == redir_infile
			&& rd->rightmost == true)
			curr->cmd->prio_in = 2;
		else if (rd->instruction == redir_here_doc
			&& rd->rightmost == true)
			curr->cmd->prio_in = 3;
		else if (rd->instruction == redir_inpipe
			&& (curr->cmd->prio_in != 3 || curr->cmd->prio_in != 2))
			curr->cmd->prio_in = 1;
		if (rd->instruction == redir_outfile
			&& rd->rightmost == true)
			curr->cmd->prio_out = 2;
		else if (rd->instruction == redir_append
			&& rd->rightmost == true)
			curr->cmd->prio_out = 3;
		else if (rd->instruction == redir_outpipe
			&& (curr->cmd->prio_out != 3 || curr->cmd->prio_out != 2))
			curr->cmd->prio_out = 1;
		rd = rd->next;
	}
}

void	ft_fork_execute(t_ms *ms, t_cmd_list *curr, int *i)
{
	if ((curr->cmd->flags & IS_BUILTIN) != 1)
		ms->be->child_pids[*i] = fork();
	else
		ms->be->child_pids[*i] = INT_MAX;
	if (ms->be->child_pids[*i] < 0)
	{
		strerror(EPIPE);
		ft_cleanup_exit(ms, EPIPE); // [ ] not yet accurate
	}
	if (ms->be->child_pids[*i] == 0 || ms->be->child_pids[*i] == INT_MAX)
	{
		ft_redir_handler(ms, curr);
		if (ms->be->child_pids[*i] == INT_MAX)
			ft_builtin(curr);
		else if (ms->be->child_pids[*i] == 0)
			ft_execute(curr);
	}
}

void	ft_is_builtin(t_cmd_list *curr, t_ms *ms)
{
	int		i;
	int		len;

	i = -1;
	while (ms->be->builtins[++i])
	{
		len = ft_strlen(ms->be->builtins[i]);
		if (strncmp(curr->cmd->words->word->word, ms->be->builtins[i], len) == 0
			&& ft_strlen(curr->cmd->words->word->word) == len)
		{
			curr->cmd->flags & IS_BUILTIN;
			curr->cmd->builtin_nr = i;
		}
	}
}


void	ft_executor(t_ms *ms)
{
	t_cmd_list			*curr;
	int					i;

	curr = ms->cmds;
	i = 0;
	while (curr)
	{
		ft_is_builtin(curr, ms);
		if (curr->cmd->redir)
		{
			ft_ex_prio(ms, curr);
			ft_fork_execute(ms, curr, &i);
		}
		curr = curr->next;
	}
}

void	ft_init_be(t_ms *ms)
{
	t_cmd_list	*curr;
	int			nb_cmds;

	nb_cmds = 0;
	curr = ms->cmds;
	while (curr)
	{
		nb_cmds++;
		curr = curr->next;
	}
	ms->be->child_pids = ft_calloc(sizeof(int), (size_t) nb_cmds + 1);
	ms->be->builtins = ft_calloc(sizeof(char *), 8);
	ms->be->builtins[0] = ft_strdup("echo");
	ms->be->builtins[1] = ft_strdup("cd");
	ms->be->builtins[2] = ft_strdup("pwd");
	ms->be->builtins[3] = ft_strdup("export");
	ms->be->builtins[4] = ft_strdup("unset");
	ms->be->builtins[5] = ft_strdup("env");
	ms->be->builtins[6] = ft_strdup("exit");
}

void	ft_back_end(t_ms *ms)
{
	ft_init_be(ms);
	if (ms->global_flags == 1)
		ft_here_doc(ms);
	ft_executor(ms);
	ft_clean_be(ms);
}
