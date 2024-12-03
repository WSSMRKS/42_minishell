/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:23:15 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/27 13:50:29 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_list_words(t_list_words **head)
{
	t_list_words *current;
	t_list_words *next;

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
	t_list_redir *current;
	t_list_redir *next;

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
	t_cmd_list *current;
	t_cmd_list *next;

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

/* There are no cases where ms->cmd && ms->cmds are empty. Therefore this function is always freeing everything*/
void	ft_clear_ast(t_ms *ms)
{
	free_list_cmds(&ms->cmds);
}

void	ft_clear_be(t_ms *ms)
{
	if (ms->be->garbage)
	{
		if (ms->be->garbage->heredoc)
			ft_delfree_hdgb(&ms->be->garbage->heredoc, &free);
		free(ms->be->garbage);
		ms->be->garbage = NULL;
	}
	free(ms->be->child_pids);
	ms->be->child_pids = NULL;
	free(ms->be->child_ret);
	ms->be->nb_cmds = 0;
	ms->be->child_ret = NULL;
}


void	ft_clean_be(t_ms *ms)
{
	ft_free_2d(ms->be->builtins);
	free(ms->be->cwd);
	ft_free_2d(ms->be->path); /* [ ] maybe rewrite due to changeable variables*/
	ft_free_stab_stack(ms->be->global_stabs);
}


void	clean_garbage(void)
{
	(void) 1;
}

void	ft_lsthdgbdelone(t_list_hdfiles *lst, void (*del)(void *))
{
	if (lst)
	{
		if (del && lst->filename)
			(del)(lst->filename);
		free(lst);
		lst = NULL;
	}
}

void	ft_delfree_hdgb(t_list_hdfiles **lst, void (*del)(void *))
{
	t_list_hdfiles	*tlst;
	t_list_hdfiles	*nlst;

	if (lst)
	{
		tlst = *lst;
		while (tlst)
		{
			nlst = tlst->next;
			unlink(tlst->filename);
			if (!access(tlst->filename, F_OK))
				ft_printf_fd(2, "minishell: could not delete tempfile\"%s\"\n",
					tlst->filename);
			ft_lsthdgbdelone(tlst, (del));
			tlst = nlst;
		}
		*lst = NULL;
	}
}

void	ft_cleanup_exit(t_ms *ms, int ex)
{
	rl_clear_history();
	ft_clean_be(ms);
	free(ms->be);
	ms->be = NULL;
	exit(ex);
}

void	ft_mprotect(void *subject)
{
	if (!subject)
	{
		ft_printf_fd(STDERR_FILENO, "malloc fail");
		exit(ENOMEM);
	}
}
