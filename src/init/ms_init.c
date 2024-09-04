/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:05:44 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/04 14:11:54 by maweiss          ###   ########.fr       */
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

void	ft_init_ms(t_ms *ms, int argc, char **argv, char **envp)
{
	(void) ms;
	(void) envp;

	ms->be->argc = argc;
	ms->be->argv = argv;
	ms->be->envp = envp;
	ms->global_symtab = NULL;
	ms->cmds = NULL;
	ms->cmd = NULL;
	ms->be->garbage = malloc(sizeof(t_garbage) * 1);  //[ ] free me
	ms->be->garbage->heredoc = NULL;
	ms->be->garbage->nb_heredocs = 0;
	ms->be->path = ft_grab_envp(ms->be->envp);
}
