/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/06 16:22:04 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_exit(t_ms *ms, t_cmd_list *curr)
{
	int		ex;

	if (curr->cmd.words->next != NULL)
	{
		if (!strsl_atoi(cstr_view(curr->cmd.words->next->word), base10(), &ex, OFB_ERROR))
		{
			ft_printf_fd(2, "exit: %s: not a valid argument\n", curr->cmd.words->next->word);
			return (EIO);
		}
	}
	if (isatty(STDIN_FILENO))
		ft_printf("exit\n");
	close(ms->be->saved_std[0]);
	close(ms->be->saved_std[1]);
	ft_close_all_fds(ms);
	ft_clear_ast(ms);
	ft_clear_be(ms);
	ft_cleanup_exit(ms, ex + g_signal);
	return (0);
}
