/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:26:39 by maweiss           #+#    #+#             */
/*   Updated: 2024/06/14 20:27:43 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_first_child(t_pipex *pipex)
{
	int		fdin;
	char	*cmdpath;
	int		err;

	fdin = open(pipex->infile, O_RDONLY);
	if (fdin < 0)
		ft_cleanup_exit(pipex, errno);
	dup2(fdin, STDIN_FILENO);
	dup2(pipex->pipe[1][1], STDOUT_FILENO);
	close(fdin);
	ft_close_all_fds(pipex);
	cmdpath = ft_search_cmd(pipex, 1);
	if (cmdpath == NULL)
		err = 127;
	else
		err = execve(cmdpath, pipex->cmd_args[0], pipex->envp);
	ft_cleanup_exit(pipex, err);
}

void	ft_child(t_pipex *pipex, int nb_cmd)
{
	char	*cmdpath;
	int		err;

	dup2(pipex->pipe[(nb_cmd - 1) & 1][0], STDIN_FILENO);
	dup2(pipex->pipe[nb_cmd & 1][1], STDOUT_FILENO);
	ft_close_all_fds(pipex);
	cmdpath = ft_search_cmd(pipex, nb_cmd);
	if (cmdpath == NULL)
		err = 127;
	else
		err = execve(cmdpath, pipex->cmd_args[nb_cmd - 1], pipex->envp);
	ft_cleanup_exit(pipex, err);
}

void	ft_parent_process(t_pipex *pipex)
{
	char	*cmdpath;
	int		fdout;
	int		err;

	if (pipex->mode == here_doc)
		fdout = open(pipex->outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fdout = open(pipex->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fdout < 0)
		ft_cleanup_exit(pipex, errno);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	dup2(pipex->pipe[(pipex->nb_cmds -1) & 1][0], STDIN_FILENO);
	ft_close_all_fds(pipex);
	cmdpath = ft_search_cmd(pipex, pipex->nb_cmds);
	if (cmdpath == NULL)
		err = 127;
	else
		err = execve(cmdpath, pipex->cmd_args[pipex->nb_cmds - 1], pipex->envp);
	ft_cleanup_exit(pipex, err);
}

/* Function responsible for the first fork and starting the first child*/
void	ft_fork_first_child(t_pipex *pipex, int *i)
{
	pipex->child_pids[*i] = fork();
	if (pipex->child_pids[*i] < 0)
	{
		strerror(EPIPE);
		ft_cleanup_exit(pipex, EPIPE);
	}
	if (pipex->mode == here_doc && pipex->child_pids[*i] == 0)
		ft_here_doc(pipex);
	else if (pipex->child_pids[*i] == 0)
		ft_first_child(pipex);
}

/* Function for bonus handling all the childs in between*/
void	ft_malcolm(t_pipex *pipex, int *i)
{
	while (pipex->child_pids[(*i)++] != 0 && *i < pipex->nb_cmds - 1)
	{
		pipex->child_pids[*i] = fork();
		if (pipex->child_pids[*i] == 0)
			ft_child(pipex, *i + 1);
		if (close(pipex->pipe[*i & 1][0])
			|| close(pipex->pipe[*i & 1][1]))
			perror("pipex");
		pipe(pipex->pipe[*i & 1]);
	}
}
