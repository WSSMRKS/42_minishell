/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 15:51:22 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_echo(t_ms *ms, t_cmd_list *curr)
{
	bool			newline;
	t_list_words	*words;
	int				i;

	(void) ms;
	i = 0;
	newline = true;
	words = curr->cmd.words->next;
	if (words && ft_strncmp(curr->cmd.words->next->word, "-n\0", 3) == 0)
	{
		newline = false;
		words = words->next;
	}
	while (words)
	{
		if (i++ != 0)
			ft_printf(" ");
		ft_printf("%s", words->word);
		words = words->next;
	}
	if (newline == true)
		ft_printf("\n");
	return (0);
}
