/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:23:15 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/26 10:22:07 by maweiss          ###   ########.fr       */
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
		if(to_free->target)
		{
			if (to_free->target->filename)
			{
				free(to_free->target->filename);
				to_free->target->filename = NULL;
			}
			free(to_free->target);
			to_free->target = NULL;
		}
		if(to_free->hd_del)
		{
			free(to_free->hd_del);
			to_free->hd_del = NULL;
		}
		if(to_free->target)
		{
			free(to_free->target);
			to_free->target = NULL;
		}
		if(to_free->target)
		{
			if (to_free->target->filename)
			{
				free(to_free->target->filename);
				to_free->target->filename = NULL;
			}
			free(to_free->target);
			to_free->target = NULL;
		}
		free(to_free);
		to_free = NULL;
	}
}

void	ft_clear_words(t_list_words	*words)
{
	t_list_words	*to_free;

	while (words)
	{
		to_free = words;
		words = words->next;
		if(to_free->word)
		{
			free(to_free->word);
			to_free->word = NULL;
		}
		free(to_free);
		to_free = NULL;
	}
}

/* There are no cases where ms->cmd && ms->cmds are empty. Therefore this function is always freeing everything*/
void	ft_clear_ast(t_ms *ms)
{
	t_cmd_list *subject;
	t_cmd_list *to_free;

	subject = ms->cmds;

	while (subject)
	{
		to_free = subject;
		subject = subject->next;
		if(to_free->cmd)
		{
			ft_clear_redir(to_free->cmd->redir);
			ft_clear_words(to_free->cmd->words);
			ft_free_2d(to_free->cmd->argv);
			free(to_free->cmd);
			to_free->cmd = NULL;
		}
		free(to_free);
	}
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
	ft_free_symtab_stack(ms->be->global_symtabs);
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
