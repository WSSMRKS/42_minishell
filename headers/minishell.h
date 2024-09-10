/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:42:03 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/10 07:37:26 by maweiss          ###   ########.fr       */
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
# include <stdbool.h>
# include "../libft/libft.h"
# include "ms_symtab.h"
# include "ms_parsing.h"
# include "ms_garbage.h"
# include "ms_executor.h"

/* minishell struct. Main struct that is passed throughout the whole program.
	global flags: 1 = heredoc present	*/
typedef struct s_ms {
	char			*cmd;
	t_symtab_stack	*global_symtab;
	t_cmd_list		*cmds;
	int				global_flags;
	t_be			*be;
}				t_ms;

/* ms_cleanup_utils */
void	ft_clear_be(t_ms *ms);
void	ft_clean_be(t_ms *ms);
void	clean_garbage(void);
void	ft_lsthdgbdelone(t_list_hdfiles *lst, void (*del)(void *));
void	ft_delfree_hdgb(t_list_hdfiles **lst, void (*del)(void *));
void	ft_cleanup_exit(t_ms *ms, int ex);

/* ms_executor */
void	ft_close_all_fds(t_ms *ms);
char	*ft_search_cmd(t_ms *ms, t_cmd_list *curr);
void	ft_execute(t_ms *ms, t_cmd_list *curr);
void	ft_builtin(t_ms *ms, t_cmd_list *curr);
void	ft_fork_execute(t_ms *ms, t_cmd_list *curr, int *i);
void	ft_is_builtin(t_cmd_list *curr, t_ms *ms);
void	ft_executor(t_ms *ms);
void	ft_init_be(t_ms *ms, int argc, char **argv, char **envp);
void	ft_back_end(t_ms *ms);

/* ms_ex_redir */
void	ft_redir_handler(t_ms *ms, t_cmd_list *curr, int i);
void	ft_ex_prio(t_cmd_list *curr);

/* ms_heredoc */
char	*ft_search_tmp(void);
void	ft_garbage_add(char *filename, t_ms *ms);
char	*ft_tmp_name(t_ms *ms, int *fd);
void	ft_hd_input(char *hd_del, t_redir_aim *filename, t_ms *ms);
void	ft_here_doc(t_ms *ms);

/* ms_init */
char	**ft_grab_envp(char **envp);
void	ft_init_ms(t_ms *ms);

/* ms_ui */
void	ft_front_end(char *cmd);
char	*choose_prompt(int mode);
void	ft_repl(int argc, char **argv, char **envp);

/* ms_debug */
void	ft_deb_here_doc(t_ms *ms);
void	ft_deb_commands(t_ms *ms);
void	ft_debug(t_ms *ms);

#endif
