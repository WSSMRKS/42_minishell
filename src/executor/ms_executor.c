/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 14:59:37 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// char *ft_complete_path(t_ms *ms, t_cmd_list *curr, char *input)
// {
// 	// if(input[0] == '.' && input[1] == '/')
// 	// 	return ()
// }

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
	while (ms->be->path[i])
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

// void	ft_prnt_stderr(char *name, char *cmd, int err)
// {
// 	int	storage;

// 	storage = dup(STDOUT_FILENO);
// 	dup2(STDERR_FILENO, STDOUT_FILENO);
// 	if (name == NULL)
// 		printf("%s: command not found\n", cmd);
// 	else
// 		printf("%s: %s: %s\n", name, cmd, strerror(err));
// 	dup2(storage, STDOUT_FILENO);
// 	close(storage);
// }

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


void	ft_execute(t_ms *ms, t_cmd_list *curr)
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
	ft_clear_ast(ms); // [ ] take care of this in case of not a child!!
	ft_clear_be(ms); // [ ] take care of this in case of not a child!!
	ft_cleanup_exit(ms, err);
}

int	ft_builtin(t_ms *ms, t_cmd_list *curr)
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
	else if (curr->cmd.builtin_nr == 8)
		ret = ft_status(ms, curr);
	else if (curr->cmd.builtin_nr == 9)
		ret = ft_resize(ms, curr);
	return (ret);
}

void	ft_create_argv(t_cmd_list *curr)
{
	t_list_words	*words;
	char			**argv;
	int				i;

	words = curr->cmd.words;
	i = 0;
	while (words)
	{
		i++;
		words = words->next;
	}
	argv = ft_calloc(sizeof(char *), i + 1);
	words = curr->cmd.words;
	i = 0;
	while (words)
	{
		argv[i++] = ft_strdup(words->word);
		words = words->next;
	}
	curr->cmd.argv = argv;
}

void	ft_safe_std(t_ms *ms)
{
	ms->be->saved_std[0] = dup(STDIN_FILENO);
	ms->be->saved_std[1] = dup(STDOUT_FILENO);
}

int	ft_grab_pid()
{
	int		fd;
	char	buffer[256];
	ssize_t bytes_read;
	int		pid;
	char	**split;

	pid = 0;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	bytes_read = read(fd, &buffer, sizeof(buffer) -1);
	if (bytes_read < 0)
	{
		perror("read");
		close(fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	split = ft_split(buffer, ' ');
	pid = ft_atoi(split[0]);
	ft_free_2d(split);
	return (pid);
}

void	ft_ex_prep(t_ms *ms, t_cmd_list *curr, int *i)
{
	ft_redir_handler(ms, curr, *i);
	ft_create_argv(curr);
}

void	ft_pipe_reset(t_ms *ms, int *i)
{
	if (close(ms->be->pipes[(*i-1) & 1][0])
	|| close(ms->be->pipes[(*i-1) & 1][1]))
		perror("ms");
	pipe(ms->be->pipes[(*i-1) & 1]);
}

void	ft_fork_execute(t_ms *ms, t_cmd_list *curr, int *i)
{

	int	err;

	if (!curr->cmd.builtin || ms->be->nb_cmds > 1)
		ms->be->child_pids[*i] = fork();
	else
	{
		ms->be->child_pids[*i] = ft_grab_pid();
		ft_safe_std(ms);
	}
	if (ms->be->child_pids[*i] < 0)
	{
		perror("fork failed");
		ft_cleanup_exit(ms, EPIPE); // find nice way for error handling
	}
	if(ms->be->child_pids[*i] == 0 || (curr->cmd.builtin && ms->be->nb_cmds == 1))
		ft_ex_prep(ms, curr, i);
	if (ms->be->child_pids[*i] == 0)
	{
		ft_close_all_fds(ms);
		if (curr->cmd.builtin == true)
		{
			err = ft_builtin(ms, curr);
			ft_clear_ast(ms); // [ ] take care of this in case of not a child!!
			ft_clear_be(ms); // [ ] take care of this in case of not a child!!
			ft_cleanup_exit(ms, err);
		}
		else
			ft_execute(ms, curr);
	}
	else if (curr->cmd.builtin && ms->be->nb_cmds == 1)
	{
	if(ms->be->redir_err == 0)
	{
		ms->be->last_ret = ft_builtin(ms, curr);
		dup2(ms->be->saved_std[0], STDIN_FILENO);
		dup2(ms->be->saved_std[1], STDOUT_FILENO);
	}
	close(ms->be->saved_std[0]);
	close(ms->be->saved_std[1]);
	}
	if (*i > 0 && ms->be->child_pids[*i] != 0)
		ft_pipe_reset(ms, i);
}

void	ft_is_builtin(t_cmd_list *curr, t_ms *ms)
{
	int		i;
	int		len;

	i = -1;
	while (ms->cmds->cmd.words && ms->be->builtins[++i])
	{
		len = ft_strlen(ms->be->builtins[i]);
		if (ft_strncmp(curr->cmd.words->word, ms->be->builtins[i], len) == 0
			&& (int) ft_strlen(curr->cmd.words->word) == len)
		{
			curr->cmd.builtin = true;
			curr->cmd.builtin_nr = i + 1;
		}
	}
}

void	ft_executor(t_ms *ms)
{
	t_cmd_list			*curr;
	int					i;

	curr = ms->cmds;
	i = 0;
	while (curr)
	{
		ft_is_builtin(curr, ms);
		ft_fork_execute(ms, curr, &i);
		curr = curr->next;
		i++;
	}
}

void	ft_back_end(t_ms *ms)
{
	ft_reinit_be(ms);
	if (ms->global_flags == 1)
		ft_here_doc(ms);
	if(ms->cmds)
	{
		ft_executor(ms);
		ft_close_all_fds(ms);
		ft_wait_error(ms);
		ft_clear_ast(ms);
	}
	ft_clear_be(ms);
}
