/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:16:12 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/30 12:16:31 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			ft_echo(t_ms *ms, t_cmd_list *curr)
{
	bool			newline;
	t_list_words	*words;
	int				i;

	i = 0;
	if (ft_strncmp(curr->cmd->words->next->word, "-n\0", 3) == 0)
	{
		newline = true;
		words = curr->cmd->words->next->next;
	}
	else
		words = curr->cmd->words->next;
	while(words)
	{
		if (i != 0)
			printf(" ");
		if(words->flags == WORD_DOLLAR)
			printf("%s", ft_lookup_symtab(ms->be->global_symtabs, words->word));
		else
			printf("%s", words->word);
		words = words->next;
		i++;
	}
	return (0);
}
