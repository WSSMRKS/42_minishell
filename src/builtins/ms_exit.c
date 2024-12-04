/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 16:20:50 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_exit(t_ms *ms, t_cmd_list *curr)
{
	int		i;
	char	*input;
	int		ex;

	ex = 0;
	i = 0;
	if (curr->cmd.words->next != NULL)
	{
		input = curr->cmd.words->next->word;
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
			ex = ft_atoi(input);
	}
	ft_clear_ast(ms);
	ft_clear_be(ms);
	ft_cleanup_exit(ms, ex);
	return (0);
}
