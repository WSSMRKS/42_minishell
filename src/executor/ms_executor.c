/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/05 12:47:02 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_close_all_fds(t_ms *ms)
{
	if (close(ms->be->pipes[0][0]) || close(ms->be->pipes[0][1])
		|| close(ms->be->pipes[1][0]) || close(ms->be->pipes[1][1]))
	{
		perror("minishell");
	}
}

char	*ft_search_cmd(t_ms *ms, t_cmd_list *curr)
{
	int		i;
	char	*path;

	i = 0;
	if (ft_strchr(curr->cmd.words->word, '/') != NULL)
	{
		path = ft_strdup(curr->cmd.words->word);
		return (path);
	}
	while (ms->be->path && ms->be->path[i])
	{
		path = ft_strjoin(ms->be->path[i], curr->cmd.words->word);
		if (path == NULL)
		{
			perror("malloc fail!\n");
			ft_cleanup_exit(ms, ENOMEM);
		}
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

void	ft_prnt_stderr(char *name, char *cmd, int err)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (name == NULL)
		printf("%s: command not found\n", cmd);
	else
		printf("%s: %s: %s\n", name, cmd, strerror(err));
	close(STDOUT_FILENO);
	open("/dev/tty", O_WRONLY);
}

void	ft_ms_execve(t_ms *ms, t_cmd_list *curr)
{
	int		err;
	char	*cmdpath;
	char	**envp;

	cmdpath = ft_search_cmd(ms, curr);
	err = 0;
	if (cmdpath == NULL)
	{
		err = 127;
		ft_prnt_stderr(NULL, curr->cmd.words->word, 2);
	}
	else
	{
		envp = ft_create_envp(ms);
		if (execve(cmdpath, curr->cmd.argv, envp) == -1)
			err = 127;
		ft_prnt_stderr("minishell", curr->cmd.words->word, errno);
		ft_free_2d(envp);
	}
	ft_clear_ast(ms);
	ft_clear_be(ms);
	ft_cleanup_exit(ms, err);
}

int	ft_builtin(t_ms *ms, t_cmd_list *curr, int *i)
{
	int		ret;

	ret = 0;
	if (curr->cmd.builtin_nr == 1)
		ret = ft_echo(ms, curr);
	else if (curr->cmd.builtin_nr == 2)
		ret = ft_cd(ms, curr);
	else if (curr->cmd.builtin_nr == 3)
		ret = ft_pwd(ms, curr);
	else if (curr->cmd.builtin_nr == 4)
		ret = ft_export(ms, curr);
	else if (curr->cmd.builtin_nr == 5)
		ret = ft_unset(ms, curr);
	else if (curr->cmd.builtin_nr == 6)
		ret = ft_env(ms, curr);
	else if (curr->cmd.builtin_nr == 7)
		ret = ft_exit(ms, curr);
	if (ms->be->child_pids[*i] == 0)
	{
		ft_clear_ast(ms);
		ft_clear_be(ms);
		ft_cleanup_exit(ms, ret);
	}
	return (ret);
}
