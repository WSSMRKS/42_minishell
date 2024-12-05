/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:26:38 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:14:38 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	leave_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_done = 1;
	ioctl(STDOUT_FILENO, TIOCSTI, "");
	g_signal = SIGINT;
}

void	set_signal_heredoc(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &leave_heredoc; 
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
}

int	heredoc_checker(t_data *data, char *in, t_cmd_list *cmd)
{
	set_signals_noninteractive();
	if (in == NULL || g_signal == SIGINT)
	{
		if (g_signal == SIGINT)
		{
			data->dont = 1;
			return (1);
		}
		else
		{
			g_signal = EOF;
			cmd->eof = 1;
		}
		return (1);
	}
	return (0);
}
