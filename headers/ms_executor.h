/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:50:51 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/12 11:55:24 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTOR_H
# define MS_EXECUTOR_H
# include "minishell.h"

typedef struct s_be
{
	t_garbage		*garbage;		/*clear and realloc after every execution*/
	int				argc;
	char			**argv;			/*no need to free*/
	char			**envp;			/*no need to free*/
	char			**path;			/*clear at exit*/
	int				redir_err;		/*error in redirects*/
	int				nb_cmds;		/*clear after every execution*/
	int				pipes[2][2];	/*reinit after every execution*/
	int				saved_std[2];	/*close after every execution*/
	int				*child_pids;	/*clear and realloc after every execution*/
	int				*child_ret;		/*return vals of the childs*/
	int				last_ret;		/*return val of the last command*/
	char			**builtins;		/*clear at exit*/
	char			*cwd;			/*clear at exit*/
	t_stab_st		*global_stabs;
	t_stab			*alphabetic_vars;
}				t_be;

#endif
