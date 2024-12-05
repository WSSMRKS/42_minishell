/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:06:34 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:22:33 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*get_next_arg(t_token *arg)
{
	t_token	*tmp;

	if (arg == NULL)
		return (NULL);
	tmp = arg->next;
	return (tmp);
}

int	is_redirectional(char *str, t_token *arg)
{
	if (ft_strncmp(str, ">", 1) == 0 && !arg->env && !arg->quotes)
		return (1);
	if (ft_strncmp(str, ">>", 2) == 0 && !arg->env && !arg->quotes)
		return (1);
	if (ft_strncmp(str, "<", 1) == 0 && !arg->env && !arg->quotes)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0 && !arg->env && !arg->quotes)
		return (1);
	return (0);
}
