/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:37:35 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:37:54 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	cmdlist_has_heredoc(t_cmd_list *cmds)
{
	t_cmd_list	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->cmd.heredoc)
			return (true);
		curr = curr->next;
	}
	return (false);
}
