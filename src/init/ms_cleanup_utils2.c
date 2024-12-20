/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:23:15 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/11 11:58:36 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	ft_free_2d(ms->be->path);
	ms->be->path = NULL;
}

void	ft_clean_be(t_ms *ms)
{
	ft_free_2d(ms->be->builtins);
	free(ms->be->cwd);
	ft_free_2d(ms->be->path);
	ft_free_stab(ms->be->global_stabs);
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
	if (!isatty(STDIN))
		get_next_line_finish(STDIN);
	parser_destroy(&ms->parser);
	ft_clean_be(ms);
	free(ms->be);
	ms->be = NULL;
	exit(ex);
}
