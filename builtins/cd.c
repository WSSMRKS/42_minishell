/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:04:35 by dkoca             #+#    #+#             */
/*   Updated: 2024/08/15 20:06:52 by dkoca            ###   ########.fr       */
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
	char *dir;
	int ret = 0;
	char *cur_dir;
	
		// go back to the previous cd (could look up in readline history?)
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
		path = ft_strjoin("/home/", get_env_var("USER"));
	else if (**cmd == '-' && get_env_var("OLDPWD") != NULL)
		path = get_env_var("OLDPWD");
	else
		path = *cmd;
	return (_cd(path));
}

int main()
{
	// _cd("testdir");
	char *cmd[3] = {"ls", "-l"};
	char *path[3] = {"cd", "-"};
	printf("user = %s\n", getenv("OLDPWD"));
	printf("ret = %i\n", builtin_cwd(path));
	// execvp("/usr/bin/ls", cmd);
	return (0);
}