/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:05:44 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/11 11:01:30 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**ft_grab_envp(char **envp)
{
	int		i;
	char	**paths;
	char	*tmp;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_split(&envp[i][5], ':');
	if (paths == NULL)
		return (NULL); // [ ] free propperly;
	i = -1;
	while (paths[++i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			tmp = paths[i];
			paths[i] = ft_strjoin(paths[i], "/\0");
			free(tmp);
		}
	}
	return (paths);
}

void	ft_init_ms(t_ms *ms)
{
	ms->global_symtab = NULL;
	ms->global_flags = 0;
	ms->cmds = NULL;
	ms->cmd = NULL;
}

void	ft_reinit_be(t_ms *ms)
{
	t_cmd_list	*curr;
	int			i;

	ms->be->garbage = ft_calloc(sizeof(t_garbage), 1);  //[ ] free me
	ms->be->garbage->heredoc = NULL;
	ms->be->garbage->nb_heredocs = 0;
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
}

void	ft_init_be(t_ms *ms, int argc, char **argv, char **envp)
{
	ms->be = ft_calloc(sizeof(t_be), 1);
	ms->be->argc = argc;
	ms->be->argv = argv;
	ms->be->envp = envp;
	ms->be->path = ft_grab_envp(envp);
	if (pipe(ms->be->pipes[0]) == -1 || pipe(ms->be->pipes[1]) == -1)
	{
		strerror(32);
		exit (32);
	}
	ms->be->builtins = ft_calloc(sizeof(char *), 8);
	ms->be->builtins[0] = ft_strdup("echo");
	ms->be->builtins[1] = ft_strdup("cd");
	ms->be->builtins[2] = ft_strdup("pwd");
	ms->be->builtins[3] = ft_strdup("export");
	ms->be->builtins[4] = ft_strdup("unset");
	ms->be->builtins[5] = ft_strdup("env");
	ms->be->builtins[6] = ft_strdup("exit");
}
