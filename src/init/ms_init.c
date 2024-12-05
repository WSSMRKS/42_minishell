/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:05:44 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/05 17:57:52 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**ft_split_path(char **paths)
{
	int		i;
	char	*tmp;

	i = -1;
	while (paths[++i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			tmp = paths[i];
			paths[i] = ft_strjoin(paths[i], "/\0");
			free(tmp);
			tmp = NULL;
		}
	}
	return (paths);
}

char	**ft_grab_envp(char **envp)
{
	int		i;
	char	**paths;

	i = -1;
	paths = NULL;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
	}
	if (envp && envp[i] && envp[i][5])
		paths = ft_split(&envp[i][5], ':');
	else
		ft_printf_fd(2, "minishell: unable to set $PATH variable\n");
	if (paths == NULL)
		return (NULL);
	return (ft_split_path(paths));
}

void	ft_init_ms(t_ms *ms)
{
	ms->global_flags = 0;
	ms->cmds = NULL;
}

void	ft_reinit_be(t_ms *ms)
{
	t_cmd_list	*curr;
	int			i;

	ms->be->garbage = ft_calloc(sizeof(t_garbage), 1);
	ms->be->garbage->heredoc = NULL;
	ms->be->garbage->nb_heredocs = 0;
	ms->be->redir_err = 0;
	i = 0;
	curr = ms->cmds;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	ms->be->nb_cmds = i;
	ms->be->child_pids = ft_calloc(sizeof(int), (size_t) ms->be->nb_cmds + 1);
	ms->be->child_ret = ft_calloc(sizeof(int), (size_t) ms->be->nb_cmds + 1);
	if (pipe(ms->be->pipes[0]) == -1 || pipe(ms->be->pipes[1]) == -1)
	{
		strerror(32);
		exit (32);
	}
}

void	ft_init_be(t_ms *ms, int argc, char **argv, char **envp)
{
	ms->be = ft_calloc(sizeof(t_be), 1);
	ms->be->argc = argc;
	ms->be->argv = argv;
	ms->be->envp = envp;
	ms->be->path = ft_grab_envp(envp);
	ms->be->builtins = ft_calloc(sizeof(char *), 8);
	ms->be->builtins[0] = ft_strdup("echo");
	ms->be->builtins[1] = ft_strdup("cd");
	ms->be->builtins[2] = ft_strdup("pwd");
	ms->be->builtins[3] = ft_strdup("export");
	ms->be->builtins[4] = ft_strdup("unset");
	ms->be->builtins[5] = ft_strdup("env");
	ms->be->builtins[6] = ft_strdup("exit");
	ms->be->builtins[7] = NULL;
	ms->be->cwd = ft_calloc(sizeof(char), PATH_MAX);
	ms->be->global_stabs = NULL;
	ms->be->last_ret = 0;
	ms->be->redir_err = 0;
	ft_init_stab(ms);
}
