/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:15:36 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/05 11:45:23 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_back_end(t_ms *ms)
{
	ft_reinit_be(ms);
	if (ms->global_flags == 1)
		ft_here_doc(ms);
	if (ms->cmds)
	{
		ft_execution(ms);
		ft_close_all_fds(ms);
		ft_wait_error(ms);
		ft_clear_ast(ms);
	}
	ft_clear_be(ms);
}
