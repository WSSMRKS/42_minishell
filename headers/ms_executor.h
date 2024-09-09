/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:50:51 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/09 13:09:23 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXECUTOR_H
# define MS_EXECUTOR_H
# include "minishell.h"
# define IS_BUILTIN 2


typedef struct s_be {
	t_garbage		*garbage;
	int				argc;
	char			**argv;
	char			**envp;
	char			**path;
	int				pipes[2][2];
	int				*child_pids;
	char			**builtins;
	int				nb_cmds;
}				t_be;



#endif
