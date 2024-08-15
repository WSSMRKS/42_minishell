/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:04:35 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/15 23:24:04 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../libft/libft.h"

char *get_env_var(const char *name)
{
	char *var;

	if (*name && *name == '$')
		name++;
	var = getenv(name);
	if (var)
		return (var);
	return (NULL);
} 
  
int _cd(const char *path)
{
	int ret = 0;
	char *cur_dir;
	
	ret = chdir(path);
	if (ret != 0)
	{
		ft_printf("Minishell: cd: %s: No such file or directory", path);
		return (ret);
	}
	cur_dir = getcwd(NULL, 0);
	printf("cur dir = %s\n", cur_dir);
	return (ret);
}

int builtin_cwd(char **cmd)
{
	char *path;

	cmd++;
	if (cmd[1])
		ft_printf("minishell: cd: too many arguments");
	while (cmd && *cmd && ft_isspace(**cmd))
		cmd[0]++;	
	if ((*cmd == NULL || **cmd == '~' || **cmd == '\0') && get_env_var("USER") != NULL)
	{
		if (*cmd != NULL && (*cmd)++)
			path = ft_strjoin(get_env_var("HOME"), *cmd);
		else
			path = ft_strdup(get_env_var("HOME"));
	}
	else if (**cmd == '-' && get_env_var("OLDPWD") != NULL)
		path = get_env_var("OLDPWD");
	else
		path = *cmd;
	return (_cd(path));
}

int main()
{
	// _cd("testdir");
	// char *cmd[3] = {"ls", "-l"};
	char *path[3] = {"cd", "~"};
	// printf("user = %s\n", getenv("~"));
	printf("ret = %i\n", builtin_cwd(path));
	// execvp("/usr/bin/ls", cmd);
	return (0);
}