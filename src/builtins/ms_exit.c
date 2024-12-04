/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 18:50:21 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_validate_num(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if ((i == 0 && input[i] == '-')
			|| (input[i] >= '0' && input[i] <= '9'))
			i++;
		else
		{
			ft_printf_fd(2, "exit: %s: not a valid argument\n", input);
			return (EIO);
		}
	}
	if (i < 10)
		return (0);
	else
		return (EIO);
}

int	ft_exit(t_ms *ms, t_cmd_list *curr)
{
	int		ex;

	ex = 0;
	if (curr->cmd.words->next != NULL)
	{
		if (ft_validate_num(curr->cmd.words->next->word) == 0)
			ex = ft_atoi(curr->cmd.words->next->word);
		else
			return (EIO);
	}
	if (isatty(STDIN_FILENO))
		ft_printf("exit\n");
	ft_clear_ast(ms);
	ft_clear_be(ms);
	ft_cleanup_exit(ms, ex);
	return (0);
}
