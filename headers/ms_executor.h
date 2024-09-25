/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:50:51 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/25 15:16:44 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTOR_H
# define MS_EXECUTOR_H
# include "minishell.h"
# define IS_BUILTIN 2

typedef struct s_be {
	t_garbage		*garbage;		/*clear after every execution, realloc after every execution*/
	int				argc;
	char			**argv;			/*no need to free*/
	char			**envp;			/*no need to free*/
	char			**path;			/*clear at exit*/
	int				nb_cmds;		/*clear after every execution*/
	int				pipes[2][2];	/*reinit after every execution*/
	int				*child_pids;	/*clear after every execution, realloc after every execution*/
	int				*child_ret;		/*return values of the childs*/
	char			**builtins;		/*clear at exit*/
	t_symtab_stack	*global_symtabs;
}				t_be;

#endif
