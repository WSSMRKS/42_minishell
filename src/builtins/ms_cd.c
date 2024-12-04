/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 15:52:05 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_cd(t_ms *ms, t_cmd_list *curr)
{
	int	ret;

	if (!curr->cmd.words->next)
		ret = chdir(ft_lookup_stab(ms->be->global_stabs, "HOME"));
	else
		ret = chdir(curr->cmd.words->next->word);
	if (ret != 0)
	{
		if (!curr->cmd.words->next)
			ft_printf_fd(2, "ms: cd: %s: %s\n",
				ft_lookup_stab(ms->be->global_stabs, "HOME"), strerror(errno));
		else
			ft_printf_fd(2, "ms: cd: %s: %s\n",
				curr->cmd.words->next->word, strerror(errno));
		return (ret);
	}
	ms->be->cwd = getcwd(ms->be->cwd, PATH_MAX);
	ft_upd_stab_val(ms->be->global_stabs, "PWD", ms->be->cwd);
	ft_memset(ms->be->cwd, '\0', PATH_MAX);
	return (0);
}
