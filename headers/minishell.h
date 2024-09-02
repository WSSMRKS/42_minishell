/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:42:03 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/02 12:43:47 by dkoca            ###   ########.fr       */
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
# include <fcntl.h>
# include <limits.h>
# include "../libft/libft.h"
# include "ms_symtab.h"
# include "ms_parsing.h"
# include "ms_garbage.h"
# include "ms_executor.h"
# include "tokenization.h" 

#define FALSE 0
#define TRUE 1

/* minishell struct. Main struct that is passed throughout the whole program.
	global flags: 1 = heredoc present	*/
typedef struct s_ms {
	char			*cmd;
	t_symtab_stack	*global_symtab;
	t_cmd_list		*cmds;
	int				global_flags;
	t_garbage		*garbage;
	int				argc;
	char			**argv;
	char			**envp;
	char			**path;
	int				pipe[2][2];
}				t_ms;

/* ms_cleanup_utils */
void	ft_cleanup_exit(t_ms *ms, int ex);
void	clean_garbage(void);

/* ms_executor */
void	ft_scan_cmds(t_ms *ms);
void	ft_single_cmd(t_ms *ms);
void	ft_two_cmds(t_ms *ms);
void	ft_several_cmds(t_ms *ms);
char	*ft_search_tmp(void);
void	ft_garbage_add(char *filename, t_ms *ms);
char	*ft_tmp_name(t_ms *ms, int *fd);
void	ft_hd_input(char *hd_del, t_redir_aim *filename, t_ms *ms);
void	ft_here_doc(t_ms *ms);

/* ms_init */
char	**ft_grab_envp(char **envp);
void	ft_init_ms(t_ms *ms, int argc, char **argv, char **envp);

/* ms_ui */
void	ft_front_end(char *cmd);
char	*choose_prompt(int mode);
void	ft_repl(int argc, char **argv, char **envp);

/* ms_debug */
void	ft_debug(t_ms *ms);

#endif
