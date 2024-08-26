/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/26 19:18:52 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_scan_cmds(t_ms *ms)
{
	if (ms->global_flags == 1) // has here_doc
		ft_here_doc(ms);
	if (!ms->cmds->next)
		ft_single_cmd(ms);
	else if (!ms->cmds->next->next)
		ft_two_cmds(ms);
	else
		ft_several_cmds(ms);
}

void	ft_single_cmd(t_ms *ms)
{

}

void	ft_two_cmds(t_ms *ms);
{

}

void	ft_several_cmds(t_ms *ms)
{

}

void	ft_here_doc(t_ms *ms)
{
	// handle all here_docs. here doc tempfiles need to be stored in a linked list?
}
