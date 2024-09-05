/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:21:53 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/05 14:29:16 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/* Function checks minimum number of arguments and if here_doc flag is set.*/
void	ft_validate_args(t_pipex *pipex)
{
	if (pipex->argc < 5)
	{
		ft_printf_err("Error: Wrong number of arguments\n");
		pipex->mode = error_case;
		exit(1);
	}
	else if (ft_strncmp(pipex->argv[1], "here_doc", 8) == 0)
	{
		if (pipex->argc == 6)
			pipex->mode = here_doc;
		else
		{
			ft_printf_err("Error: Wrong number of arguments for here_doc\n");
			exit(2);
		}
	}
	else
		pipex->mode = regular_case;
}

/* Function allocates memory for the dynamic elements of the t_pipex struct*/
int	ft_alloc_t_pipex(t_pipex *pipex)
{
	int	ret;

	ret = 0;
	pipex->cmd_ret = ft_calloc(sizeof(int), pipex->nb_cmds + 2);
	if (pipex->cmd_ret == NULL)
		ret = -1;
	pipex->child_ret = ft_calloc(sizeof(int), pipex->nb_cmds - pipex->mode + 2);
	if (pipex->child_ret == NULL)
		ret = -1;
	pipex->child_pids = ft_calloc(sizeof(int),
			pipex->nb_cmds - pipex->mode + 2);
	if (pipex->child_pids == NULL)
		ret = -1;
	pipex->outfile = ft_strdup(pipex->argv[pipex->argc - 1]);
	if (pipex->outfile == NULL)
		ret = -1;
	pipex->cmd_args = ft_calloc(sizeof(char **), pipex->nb_cmds + 1);
	if (pipex->cmd_args == NULL)
		ret = -1;
	pipex->cmds = ft_calloc(sizeof(char *), pipex->nb_cmds + 1);
	if (pipex->cmds == NULL)
		ret = -1;
	return (ret);
}

/* Preparing the environment for the actual passing of the argument.
(due to too many function lines in ft_parse_cmds)*/
int	ft_set_parse_env(t_pipex *pipex, int *offset)
{
	*offset = 2;
	pipex->nb_cmds = pipex->argc - 3;
	if (pipex->mode == here_doc)
	{
		*offset += 1;
		pipex->nb_cmds -= 1;
		pipex->delimiter = ft_strdup(pipex->argv[2]);
		if (!pipex->delimiter)
			return (-1);
	}
	else
	{
		pipex->infile = ft_strdup(pipex->argv[1]);
		if (!pipex->infile)
			return (-1);
	}
	return (0);
}

/* Function to destinguish between cases, parse as well as
allocate the commands, args and the in-/outfile */
int	ft_parse_cmds(t_pipex *pipex)
{
	int	i;
	int	offset;

	if (ft_set_parse_env(pipex, &offset) || ft_alloc_t_pipex(pipex))
		ft_cleanup_exit(pipex, ENOMEM);
	i = -1;
	while (++i < pipex->nb_cmds)
	{
		pipex->cmd_args[i] = ft_split(pipex->argv[i + offset], ' ');
		if (pipex->cmd_args[i] == NULL || pipex->cmd_args[i][0] == NULL)
			return (ENOMEM);
		else
		{
			pipex->cmds[i] = ft_strdup(pipex->cmd_args[i][0]);
			if (!pipex->cmds[i])
				return (ENOMEM);
		}
	}
	pipex->cmd_args[i] = NULL;
	pipex->cmds[i] = NULL;
	return (0);
}

/* Function checks if the command built from the environmental variable
and the pipex argument is valid by using the access function*/
char	*ft_search_cmd(t_pipex *pipex, int nbcmd)
{
	int		i;
	char	*path;

	i = 0;
	while (pipex->path[i])
	{
		path = ft_strjoin(pipex->path[i], pipex->cmds[nbcmd - 1]);
		if (path == NULL)
		{
			perror("malloc fail!\n");
			ft_cleanup_exit(pipex, ENOMEM);
		}
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
