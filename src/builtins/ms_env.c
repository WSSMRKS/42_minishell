/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 16:19:22 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_env(t_ms *ms, t_cmd_list *curr)
{
	t_stab_st	*global_stab;
	int			i;
	t_stab		*entry;

	if (curr->cmd.words->next != NULL)
	{
		ft_printf_fd(2, "env: doesn't support arguments\n");
		return (1);
	}
	i = -1;
	global_stab = ms->be->global_stabs;
	while (++i < global_stab->size)
	{
		if (global_stab->stab[i] != NULL)
		{
			entry = global_stab->stab[i];
			while (entry)
			{
				if (entry->val != NULL)
					ft_printf("%s=%s\n", entry->key, entry->val);
				entry = entry->next;
			}
		}
	}
	return (0);
}
