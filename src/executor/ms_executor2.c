/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/06 13:47:05 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

int	ft_extract_pid(char *buffer)
{
	char	**split;
	int		pid;

	split = ft_split(buffer, ' ');
	pid = ft_atoi(split[0]);
	ft_free_2d(split);
	return (pid);
}

int	ft_grab_pid(void)
{
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	bytes_read = read(fd, &buffer, sizeof(buffer) - 1);
	if (bytes_read < 0)
	{
		perror("read");
		close(fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	return (ft_extract_pid(buffer));
}

void	ft_ex_prep(t_ms *ms, t_cmd_list *curr, int *i)
{
	ft_redir_handler(ms, curr, *i);
	ft_create_argv(curr);
}
