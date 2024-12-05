/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:25:28 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:25:28 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <bits/sigaction.h>
# include <asm-generic/signal-defs.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <termio.h>
# include <stdbool.h>

# include "../libft/inc/libft.h"
# include "colors.h"

# define INITIAL_TOKEN_SIZE 64
# define MAX_COMMANDS 10
# define MAX_ARGS 10
# define PROMPT "\001\033[1;35m\002minishell>\001\033[0m\002"

# define ENOF "Unexpected EOF"
# define MEM "Memory allocation failed"
# define CNF "Command not found"
# define EXF "Execve failed"
# define SPE "Error while searching through $PATH"
# define HNS "$HOME not set"
# define ONS "$OLDPWD not set"
# define NSD "No such directory"
# define NSF "No such file or directory"
# define SRF "Step towards root failed"
# define TMA "Too many arguments"

extern volatile sig_atomic_t	g_signal;

typedef struct s_exe
{
	char	**argv;
	char	**env;
}	t_exe;

typedef struct s_env
{
	struct s_env	*prev;
	struct s_env	*next;
	char			*value;
	char			*name;
	char			equal[2];
}	t_env;

typedef struct s_token
{
	char			*str;
	char			*original;
	struct s_token	*prev;
	struct s_token	*next;
	int				quotes;
	int				env;
	int				delimiter;
}	t_token;

typedef struct s_cmd_list
{
	struct s_cmd_list	*prev;
	struct s_cmd_list	*next;

	int					cmd_count;
	int					index;
	pid_t				pid;

	int					eof;
	char				*error;

	int					flag;
	char				*name;

	int					pipe_fds[2];
	int					pipe_write_end_used;
	int					pipe_read_end_used;
	int					fd_in;
	int					fd_out;

	t_env				*first_env;
	t_token				*first_token;
	t_token				*name_token;

	t_token				*input_argument;
	t_token				*input_operator;
	t_token				*output_operator;
	t_token				*output_argument;

	int					heredoc_pipe[2];
}	t_cmd_list;

typedef struct s_var
{
	int		pos;
	int		start;
	int		end;
	char	*new;
	int		env;
	int		sq;
	int		dq;
	int		hd;
}	t_var;

typedef struct s_data
{
	char		*input;
	int			command_count;
	t_cmd_list	*first_cmd;
	char		**tokens;
	char		**envp_original;
	t_env		*first_env;
	int			parent;
	int			status;
	int			pos;
	int			pos3;
	int			dont;
	t_exe		*exe;
	pid_t		pid;
	t_token		*first_token;
	t_var		*var;
}	t_data;

//cleanup_structs
void		free_red_tokens(t_cmd_list *del);
void		*cleanup_cmd(t_data *data);
void		*cleaunup_env(t_data *data);
void		*free_tokens(t_token *token);
void		*free_token(t_token *token);

//cleanup.c
int			small_cleanup(t_data *data);
void		wait_for_children(t_data *data);
int			cleanup(t_data *data);
void		*free_map(char **map);

//data_var.c
void		set_up_data(t_data *data, char **envp, int argc, char **argv);
void		var_init(t_data *data);
void		*free_var(t_data *data);

//env_expanding.c
void		get_env_name(t_data *data, t_var *var, char	*str, char **name);
void		switch_env(t_data *data, t_var *var, char *str);
void		env_expanding(t_data *data, t_var *var, char *str);
void		add_exit_status(t_data *data, t_var *var);
void		add_shell_pid(t_data *data, t_var *var);

//env_helpers.c
void		combine_env(t_env *tmp, char **env, int i);
int			get_name(t_data *data, t_env *new, char *envp);
int			set_empty_value(t_data *data, t_env *new);
int			get_value(t_data *data, t_env *new, char *envp, int pos);

//error_handling.c
int			exit_on_error(t_data *data, char *msg, int leave, int ret);

//exec.c
void		exec(t_data *data, t_cmd_list *cmd);
char		**get_paths(t_data *data, t_cmd_list *cmd);
void		check_access(t_data *data, t_cmd_list *cmd, char **paths, int pos);
void		create_pass_env(t_data *data, t_cmd_list *cmd, t_exe *pass);
void		create_pass_argv(t_data *data, t_cmd_list *cmd, t_exe *pass);

//execute_cd.c
int			cd_home(t_data *data);
int			cd_prev(t_data *data, t_cmd_list *cmd);
int			cd_home_sth(t_data *data, t_cmd_list *cmd);
int			cd_step_root(t_data *data, char *cwd);
int			delegate_cd(t_data *data, t_cmd_list *cmd, char *cwd);

//execute_env.c
void		update_pwd_envs(t_env *env, char *str);
int			handle_env(t_data *data, t_cmd_list *cmd);
int			handle_unset(t_data *data, t_cmd_list *cmd);
t_env		*get_env(t_env *envp, char *set);

//execute_exit.c
void		exit_atoi(t_data *data, char *nptr, unsigned char *nbr);
int			only_digits(char *str);
int			numeric(t_cmd_list *cmd);
int			handle_exit(t_data *data, t_cmd_list *cmd);

//execute_export.c
t_env		*check_existence(t_env *envp, char *set);
void		change_value(t_env	*env, char *str);
void		print_export(t_data *data, t_env *tmp, t_cmd_list *cmd);
int			valid_identifier(char *str);
int			handle_export(t_data *data, t_cmd_list *cmd);

//execute.c
int			handle_pwd(t_data *data, t_cmd_list *cmd);
int			handle_echo(t_cmd_list *cmd);
int			handle_cd(t_data *data, t_cmd_list *cmd);

//fd_handling.c
int			setup_pipes(t_cmd_list *cmd);
int			close_fd(int *fd);
int			close_all_fds(t_cmd_list *cmd);
void		set_pipe_flags(t_cmd_list *tmp);
void		prepare_fds(t_cmd_list *cmd);

//helpers.c
int			is_blank(char *s);
int			map_len(char **array);
int			is_whitespace(char c);
char		*join(char *first, char *second);
int			parent(t_data *data, char *name);

//input_setup.c
void		skip_quotes(char *str, int *pos, char *quote);
int			cmd_count(char *str);
int			input_setup(t_data *data);
int			token_main(t_data *data);

//lst_cmd
t_cmd_list	*cmd_lstlast(t_cmd_list *lst);
void		set_nulls(t_cmd_list *new);
t_cmd_list	*cmd_lst_new(t_data *data, int index, int cmd_count);
void		cmd_lstadd_back(t_cmd_list **lst, t_cmd_list *new);
int			list_init(t_data *data);

//lst_env
t_env		*env_lstlast(t_env *lst);
void		env_lstadd_back(t_env **lst, t_env *new);
void		del_variable(t_data *data, t_env *node);
void		env_init(t_data *data, char **env);
t_env		*env_new(t_data *data, char *envp);

//lst_token.c
t_token		*lst_token_last(t_token *head);
void		create_and_add_token(t_data *data, const char *start,
				size_t length, int *delimiter);
void		initialize_token_struct(t_data *data, char *input, t_var *var);

//main.c
int			unclosed(char *str);
int			last_pipe(char *str);
void		pipe_loop(t_data *data, char *in);
void		get_full_input_line(t_data *data);

//redirect_heredoc.c
char		*edit_heredoc(t_data *data, char *in, t_token *delimiter);
void		heredoc_loop(t_data *data, t_cmd_list *cmd);

//redirect_name.c
t_token		*move_name_redirectional(t_cmd_list *cmd, t_token *arg);
int			check_cmd_name(t_data *data, t_cmd_list *cmd);
t_token		*overwrite_name_token(t_cmd_list *cmd, t_token *arg);
void		overwrite_red_tokens(t_cmd_list *cmd, char c,
				t_token *op, t_token *arg);

//redirect_new.c
t_token		*move_input(t_cmd_list *cmd, t_token *arg, t_token *after,
				t_token *before);
t_token		*move_output(t_cmd_list *cmd, t_token *arg, t_token *after,
				t_token *before);
t_token		*move_red_arg(t_cmd_list *cmd, t_token *arg);
int			move_redirections(t_data *data, t_cmd_list *cmd);
int			new_red(t_data *data, t_cmd_list *cmd);

//redirection_helpers.c
int			is_redirectional(char *str, t_token *arg);
t_token		*get_next_arg(t_token *arg);

//redirections.c
int			redirect(t_data *data, t_cmd_list *tmp);
int			redirect_input(t_data *data, t_cmd_list *cmd);
int			heredoc(t_data *data, t_cmd_list *cmd);
int			redirect_output(t_data *data, t_cmd_list *cmd);
int			redirect_append(t_data *data, t_cmd_list *cmd);

//signal_heredoc.c
void		leave_heredoc(int sig);
void		set_signal_heredoc(void);
int			heredoc_checker(t_data *data, char *in, t_cmd_list *cmd);

//signal.c
void		ignore_sigquit(void);
void		signal_reset_prompt(int signal);
void		set_signals_interactive(void);
void		signal_print_newline(int signal);
void		set_signals_noninteractive(void);

//subshell.c
int			create_subshell(t_data *data);
int			subshell(t_data *data, int index);
int			delegate(t_data *data, t_cmd_list *cmd);

//assign tokens
t_token		*duplicate(t_data *data, t_token *token);
void		add_token_to_cmd(t_data *data, t_cmd_list *cmd, t_token *token);
int			assign_tokens(t_data *data);

//token.c
void		add_normal(t_data *data, char *str, t_var *var);
void		edit_tokens(t_data *data, t_token *current, t_var *var);
int			deal_sq(t_data *data, t_var *var, t_token *current, char c);
void		edit_quotes(t_data *data, t_token *current, t_var *var);

//tokenize_red.c
int			tokenize_in(t_data *data, const char *input, t_var *var);
int			tokenize_out(t_data *data, const char *input, t_var *var);
int			tokenize_redirectional(t_data *data, const char *input, t_var *var);
int			t_redirectional(char *input);

//debugging.c
void		print_fds(t_data *data, t_cmd_list *cmd);
void		print_args(t_cmd_list *cmd);
void		print_map(char **map);
void		print_cmd_tokens(t_cmd_list *cmd);
void		print_tokens(t_token *head);
void		print_token(t_token *token);
#endif
