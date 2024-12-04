/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:23:15 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 19:34:19 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_list_words(t_list_words **head)
{
	t_list_words	*current;
	t_list_words	*next;

	current = *head;
	*head = NULL;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
}

void	free_list_redir(t_list_redir **head)
{
	t_list_redir	*current;
	t_list_redir	*next;

	current = *head;
	*head = NULL;
	while (current)
	{
		next = current->next;
		free(current->target.filename);
		free(current->hd_del);
		free(current);
		current = next;
	}
}

void	free_simple_com(t_simple_com *cmd)
{
	free_list_words(&cmd->words);
	free_list_redir(&cmd->redir);
	ft_free_2d(cmd->argv);
	*cmd = (t_simple_com){0};
}

void	free_list_cmds(t_cmd_list **head)
{
	t_cmd_list	*current;
	t_cmd_list	*next;

	current = *head;
	*head = NULL;
	while (current)
	{
		next = current->next;
		free_simple_com(&current->cmd);
		free(current);
		current = next;
	}
}

/* There are no cases where ms->cmd && ms->cmds are empty.
Therefore this function is always freeing everything*/
void	ft_clear_ast(t_ms *ms)
{
	free_list_cmds(&ms->cmds);
}
