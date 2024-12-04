/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 15:51:46 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_ms *ms, t_cmd_list *curr)
{
	if (curr->cmd.words->next != NULL)
	{
		ft_printf_fd(2, "pwd: doesn't support arguments\n");
		return (1);
	}
	ms->be->cwd = getcwd(ms->be->cwd, PATH_MAX);
	printf("%s\n", ms->be->cwd);
	ft_memset(ms->be->cwd, '\0', PATH_MAX);
	return (0);
}
