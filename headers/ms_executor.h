/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:50:51 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/26 15:15:20 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTOR_H
# define MS_EXECUTOR_H
# include "minishell.h"

typedef struct s_be {
	t_garbage		*garbage;		/*clear after every execution, realloc after every execution*/
	int				argc;
	char			**argv;			/*no need to free*/
	char			**envp;			/*no need to free*/
	char			**path;			/*clear at exit*/
	int				redir_err;		/*error in redirects*/
	int				nb_cmds;		/*clear after every execution*/
	int				pipes[2][2];	/*reinit after every execution*/
	int				saved_std[2];	/*close after every execution*/
	int				*child_pids;	/*clear after every execution, realloc after every execution*/
	int				*child_ret;		/*return values of the childs*/
	int				last_ret;		/*return value of the last command*/
	char			**builtins;		/*clear at exit*/
	char			*cwd;			/*clear at exit*/
	t_symtab_stack	*global_symtabs;
	t_symtab		*alphabetic_vars;
}				t_be;

#endif
