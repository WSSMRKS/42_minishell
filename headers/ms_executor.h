/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:50:51 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/03 16:36:20 by maweiss          ###   ########.fr       */
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
	int				**pipes;
	int				**child_pids;
	char			**builtins;
}				t_be;



#endif
