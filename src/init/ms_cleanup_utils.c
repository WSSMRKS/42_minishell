/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:23:15 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/03 16:36:20 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_clean_be(t_ms ms)
{
	(void) ms;
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
	if (ms->be->garbage)
	{
		if (ms->be->garbage->heredoc)
			ft_delfree_hdgb(&ms->be->garbage->heredoc, &free);
		free(ms->be->garbage);
	}
	exit(ex);
}
