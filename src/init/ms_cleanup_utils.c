/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:23:15 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/13 14:27:20 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_clear_redir(t_list_redir	*redir)
{
	t_list_redir	*to_free;

	while (redir)
	{
		to_free = redir;
		redir = redir->next;
		if(to_free->from)
		{
			if (to_free->from->filename)
				free(to_free->from->filename);
			free(to_free->from);
		}
		if(to_free->hd_del)
			free(to_free->hd_del);
		if(to_free->hd_file)
			free(to_free->hd_file);
		if(to_free->to)
		{
			if (to_free->to->filename)
				free(to_free->to->filename);
			free(to_free->to);
		}
		free(to_free);
	}
}

void	ft_clear_words(t_list_words	*words)
{
	t_list_words	*to_free;

	while (words)
	{
		to_free = words;
		words = words->next;
		free(to_free);
	}
}

/* There are no cases where ms->cmd && ms->cmds are empty. Therefore this function is always freeing everything*/
void	ft_clear_ast(t_ms *ms)
{
	t_cmd_list *cmds;
	t_cmd_list *to_free;

	cmds = ms->cmds;

	while (cmds)
	{
		to_free = cmds;
		cmds = cmds->next;
		if(to_free->cmd)
		{
			ft_clear_redir(to_free->cmd->redir);
			ft_clear_words(to_free->cmd->words);
			free(to_free->cmd);
		}
	}
	free(ms->cmds);
	free(ms->cmd);
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
	free(ms->be->child_ret);
	ms->be->nb_cmds = 0;
}


void	ft_clean_be(t_ms *ms)
{
	ft_free_2d(ms->be->builtins);
	ft_free_2d(ms->be->path); /* [ ] maybe rewrite due to changeable variables*/
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
				ft_printf_err("minishell: could not delete tempfile\"%s\"\n",
					tlst->filename);
			ft_lsthdgbdelone(tlst, (del));
			tlst = nlst;
		}
		*lst = NULL;
	}
}

void	ft_cleanup_exit(t_ms *ms, int ex)
{
	ft_clean_be(ms);
	free(ms->be);
	exit(ex);
}
