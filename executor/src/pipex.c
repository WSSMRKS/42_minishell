/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:47:54 by maweiss           #+#    #+#             */
/*   Updated: 2024/06/16 13:22:38 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/* 	main function of project pipex.
	Input syntax: ./pipex infile cmd1 ... cmdn outfile
	alternative: ./pipex here_doc LIMITER cmd1 cmd2 outfile
*/
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	ft_init_env(&pipex, &argc, argv, envp);
	ft_pipex_init(&pipex);
	i = 0;
	ft_fork_first_child(&pipex, &i);
	if (pipex.nb_cmds > 2)
		ft_malcolm(&pipex, &i);
	else
		i++;
	pipex.child_pids[i] = fork();
	if (pipex.child_pids[i] == 0)
		ft_parent_process(&pipex);
	ft_close_all_fds(&pipex);
	ft_wait_error(&pipex);
}
