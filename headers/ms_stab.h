/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_stab.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:56:05 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/25 12:20:48 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ms_stab.h: Header file responsible for all 
the structures necessary to work with the symbol table. */

#ifndef MS_STAB_H
# define MS_STAB_H
# include "minishell.h"

typedef struct s_stab
{
	char				*key;
	char				*val;
	struct s_stab		*next;
}				t_stab;

typedef struct s_stab_stack
{
	int						level;
	t_stab					**stab;
	int						size;
	int						used;
	float					load_factor;
	struct s_stab_stack		*next;
}				t_stab_st;

#endif
