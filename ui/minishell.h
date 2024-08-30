/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:42:03 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/28 12:26:19 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* General header file for minishell. All subsequent header files are included
in minishell.h */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ms_parsing.h"
# include "ms_symtab.h"
#include "libft/libft.h"
#include "tokenization.h"

#define FALSE 0
#define TRUE 1

#define PEEK_START -1

typedef struct s_cmd
{
	char *chr_itr;
	size_t len;
	// int pos;
} t_cmd;

/* minishell struct. Main struct that is passed throughout the whole program. */
typedef struct s_minishell {
	char			*cmd;
	t_symtab_stack	*global_symtab;
	t_command		*curr_comm;
}				t_minishell;

#endif
