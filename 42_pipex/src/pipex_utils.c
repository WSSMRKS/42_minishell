/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:19:29 by maweiss           #+#    #+#             */
/*   Updated: 2024/06/14 19:44:44 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_close_all_fds(t_pipex *pipex)
{
	if (close(pipex->pipe[0][0]) || close(pipex->pipe[0][1])
		|| close(pipex->pipe[1][0]) || close(pipex->pipe[1][1]))
		perror("pipex");
}

void	ft_init_env(t_pipex *pipex, int *argc, char **argv, char **envp)
{
	pipex->argc = *argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->path = NULL;
	pipex->cmds = NULL;
	pipex->cmd_args = NULL;
	pipex->mode = 0;
	pipex->delimiter = NULL;
	pipex->infile = NULL;
	pipex->outfile = NULL;
	pipex->nb_cmds = 0;
}

void	ft_pipex_init(t_pipex *pipex)
{
	if (pipe(pipex->pipe[0]) == -1 || pipe(pipex->pipe[1]) == -1)
	{
		strerror(32);
		exit (32);
	}
	ft_validate_args(pipex);
	if (ft_parse_cmds(pipex) == -1)
		ft_cleanup_exit(pipex, 1);
	pipex->path = ft_grab_envp(pipex->envp);
	if (pipex->mode == here_doc)
		ft_here_doc_inp(pipex);
}

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
		return (NULL);
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

void	ft_cleanup_exit(t_pipex *pipex, int ex)
{
	if (pipex->delimiter)
		free(pipex->delimiter);
	if (pipex->infile)
		free(pipex->infile);
	if (pipex->outfile)
		free(pipex->outfile);
	if (pipex->cmds)
		ft_free_2d(pipex->cmds);
	if (pipex->cmd_ret)
		free(pipex->cmd_ret);
	if (pipex->child_pids)
		free(pipex->child_pids);
	if (pipex->child_ret)
		free(pipex->child_ret);
	if (pipex->path)
		ft_free_2d(pipex->path);
	if (pipex->cmd_args)
		ft_free_3d(pipex->cmd_args);
	if (pipex->mode == here_doc)
	{
		unlink(TEMP_FILE);
		if (!access(TEMP_FILE, F_OK))
			ft_printf_err("pipex: could not delete tempfile\n");
	}
	exit(ex);
}
