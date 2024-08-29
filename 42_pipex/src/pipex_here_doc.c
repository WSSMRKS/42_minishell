/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:54:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/29 19:01:04 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_here_doc_inp(t_pipex *pipex)
{
	int		fdin;
	char	*buff;

	fdin = open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fdin < 0)
	{
		ft_printf_err("here_doc: Failed to open temporary file\n");
		ft_cleanup_exit(pipex, errno);
	}
	buff = ft_get_next_line(0);
	while (buff != NULL
		&& ft_strncmp(pipex->delimiter, buff, ft_strlen(pipex->delimiter)) != 0)
	{
		ft_fprintf(fdin, "%s", buff);
		free(buff);
		buff = ft_get_next_line(0);
	}
	if (buff)
		free(buff);
	close(fdin);
	return (0);
}

void	ft_here_doc(t_pipex *pipex)
{
	int		fdin;
	char	*cmdpath;
	int		err;

	fdin = open(TEMP_FILE, O_RDONLY);
	if (fdin < 0)
	{
		ft_printf_err("Failed to reopen .pipex_temp: %s\n", strerror(errno));
		ft_cleanup_exit(pipex, errno);
	}
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
