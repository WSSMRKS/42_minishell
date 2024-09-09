/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/09 15:46:45 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_close_all_fds(t_ms *ms)
{
	if (close(ms->be->pipes[0][0]) || close(ms->be->pipes[0][1])
		|| close(ms->be->pipes[1][0]) || close(ms->be->pipes[1][1]))
		perror("minishell");
}

char	*ft_search_cmd(t_ms *ms, t_cmd_list *curr)
{
	int		i;
	char	*path;

	i = 0;
	while (ms->be->path[i])
	{
		path = ft_strjoin(ms->be->path[i], curr->cmd->words->word->word);
		if (path == NULL)
		{
			perror("malloc fail!\n");
			ft_cleanup_exit(ms, ENOMEM);
		}
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	ft_execute(t_ms *ms, t_cmd_list *curr)
{
	int		err;
	char	*cmdpath;

	cmdpath = ft_search_cmd(ms, curr);
	if (cmdpath == NULL)
		err = 127;
	else
		err = execve(cmdpath, &ms->cmds->cmd->words->word->word, NULL);
	ft_cleanup_exit(ms, err);
}

void	ft_builtin(t_ms *ms, t_cmd_list *curr)
{
	(void) ms;
	(void) curr;
}


void	ft_fork_execute(t_ms *ms, t_cmd_list *curr, int *i)
{
	if ((curr->cmd->flags & IS_BUILTIN) != 1 || ms->be->nb_cmds > 1)
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
		ft_redir_handler(ms, curr, *i);
		ft_close_all_fds(ms);  // [ ] not yet accurate
		if (ms->be->child_pids[*i] == INT_MAX)
			ft_builtin(ms, curr);
		else if (ms->be->child_pids[*i] == 0)
			ft_execute(ms, curr);
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
			&& (int) ft_strlen(curr->cmd->words->word->word) == len)
		{
			curr->cmd->flags &= IS_BUILTIN;
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
			ft_ex_prio(curr);
			ft_fork_execute(ms, curr, &i);
		}
		curr = curr->next;
		i++;
	}
}

void	ft_init_be(t_ms *ms, int argc, char **argv, char **envp)
{
	t_cmd_list	*curr;
	int			i;

	i = 0;
	curr = ms->cmds;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	ms->be->nb_cmds = i;
	ms->be->envp = envp;
	ms->be->argc = argc;
	ms->be->argv = argv;
	if (pipe(ms->be->pipes[0]) == -1 || pipe(ms->be->pipes[1]) == -1)
	{
		strerror(32);
		exit (32);
	}
	ms->be->child_pids = ft_calloc(sizeof(int), (size_t) ms->be->nb_cmds + 1);
	ms->be->builtins = ft_calloc(sizeof(char *), 8);
	ms->be->builtins[0] = ft_strdup("echo");
	ms->be->builtins[1] = ft_strdup("cd");
	ms->be->builtins[2] = ft_strdup("pwd");
	ms->be->builtins[3] = ft_strdup("export");
	ms->be->builtins[4] = ft_strdup("unset");
	ms->be->builtins[5] = ft_strdup("env");
	ms->be->builtins[6] = ft_strdup("exit");
	ms->be->path = ft_grab_envp(ms->be->envp);
}

void	ft_back_end(t_ms *ms, int argc, char **argv, char **envp)
{
	ft_init_be(ms, argc, argv, envp);
	if (ms->global_flags == 1)
		ft_here_doc(ms);
	ft_executor(ms);
	ft_clean_be(ms);
}
