/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:06:30 by dkoca             #+#    #+#             */
/*   Updated: 2024/09/10 17:30:56 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_list_words *make_word(t_tok_span *word_info)
{
	t_list_words *new_word;
	
	new_word = ft_calloc(1, sizeof(t_list_words));
	new_word->word = ft_calloc(word_info->len + 1, sizeof(char));

	ft_strlcpy(new_word->word, word_info->start, word_info->len + 1);
	/*handle flags here*/
	return (new_word);
}

t_list_words **make_word_list(t_tok_span *word_info, t_list_words ***tail)
{
	t_list_words *new;

	new = make_word(word_info);
	**tail = new;
	return (&new->next);	
}