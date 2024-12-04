/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:49:59 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 15:52:27 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_unset(t_ms *ms, t_cmd_list *curr)
{
	t_list_words	*words;

	words = curr->cmd.words;
	while (words)
	{
		ft_rem_fr_stab(ms->be->global_stabs, words->word);
		words = words->next;
	}
	return (0);
}
