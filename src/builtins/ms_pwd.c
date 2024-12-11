/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/11 14:02:41 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_ms *ms, t_cmd_list *curr)
{
	char	*pwd_var;

	if (curr->cmd.words->next != NULL)
	{
		ft_printf_fd(2, "pwd: doesn't support arguments\n");
		return (1);
	}
	ms->be->cwd = getcwd(ms->be->cwd, PATH_MAX);
	if (ms->be->cwd == NULL)
	{
		pwd_var = ft_lookup_stab(ms->be->global_stabs, "PWD");
		if (pwd_var != NULL && *pwd_var != '\0')
			ft_printf("%s\n", pwd_var);
		else
		{
			ft_printf_fd(2, "pwd: getcwd: cannot access parent directories: \
No such file or directory\n");
			ft_printf_fd(2, "pwd: PWD: variable not set\n");
			return (1);
		}
		return (0);
	}
	ft_printf("%s\n", ms->be->cwd);
	ft_memset(ms->be->cwd, '\0', PATH_MAX);
	return (0);
}

