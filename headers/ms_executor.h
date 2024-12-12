/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:50:51 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/12 19:04:21 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTOR_H
# define MS_EXECUTOR_H
# include "minishell.h"

typedef struct s_be
{
	t_garbage		*garbage;
	int				argc;
	char			**argv;
	char			**envp;
	char			**path;
	int				redir_err;
	int				nb_cmds;
	int				pipes[2][2];
	int				saved_std[2];
	int				*child_pids;
	int				*child_ret;
	int				last_ret;
	char			**builtins;
	char			*cwd;
	t_stab_st		*global_stabs;
	t_stab			*alphabetic_vars;
}				t_be;

#endif
