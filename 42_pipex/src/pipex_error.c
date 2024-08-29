/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:52:06 by maweiss           #+#    #+#             */
/*   Updated: 2024/06/16 13:25:11 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/* Function to handle the different exitstatus of pipex for err 127*/
void	ft_errno_127(t_pipex *pipex, int i, int *err)
{
	if (WEXITSTATUS(pipex->child_ret[i]) == 127)
	{
		ft_printf_err("%s: command not found\n", pipex->cmds[i]);
		if (i != 0)
			*err = 1;
		if (i == pipex->nb_cmds - 1)
			*err = 127;
	}
}

/* Function to handle the different exitstatus of pipex for err 1, 2, 13*/
void	ft_errno_1_2_13(t_pipex *pipex, int i, int *err)
{
	char	*filename;

	if (WEXITSTATUS(pipex->child_ret[i]) == 13
		|| WEXITSTATUS(pipex->child_ret[i]) == 2)
	{
		if (i == 0)
			filename = pipex->infile;
		else if (i == 0 && pipex->mode == here_doc)
			filename = TEMP_FILE;
		else
		{
			filename = pipex->outfile;
			*err = 1;
		}
		ft_printf_err("pipex: %s: %s\n", filename,
			strerror(WEXITSTATUS(pipex->child_ret[i])));
	}
	else if (WEXITSTATUS(pipex->child_ret[i]) == 1 && i == 0)
		*err = 0;
	else if (WEXITSTATUS(pipex->child_ret[i]) == 1 && i != 0)
		*err = 1;
}

void	ft_wait_error(t_pipex *pipex)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < pipex->nb_cmds)
	{
		pipex->child_ret[i] = 0;
		waitpid(pipex->child_pids[i], &(pipex->child_ret[i]), 0);
		if (WIFEXITED(pipex->child_ret[i]))
		{
			ft_errno_127(pipex, i, &err);
			ft_errno_1_2_13(pipex, i, &err);
		}
		i++;
	}
	ft_cleanup_exit(pipex, err);
}
