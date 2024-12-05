/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:22 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 17:57:52 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "util.h"

void	parser_destroy(t_parser *p)
{
	vec_destroy(&p->tokens, NULL);
	str_destroy(&p->last_input);
}

t_parser	parser_init(void *data, t_read_input read_input,
	t_get_stab get_stab, t_get_last_ret get_last_ret)
{
	t_parser	p;

	p.tokens = vec_empty(sizeof(t_token));
	p.read_input = read_input;
	p.get_stab = get_stab;
	p.get_last_ret = get_last_ret;
	p.data = data;
	p.last_input = str_empty();
	return (p);
}
