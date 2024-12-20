/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:56:05 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/12 11:57:23 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSING_H
# define MS_PARSING_H
# include "minishell.h"

typedef char			*(*t_read_input)(bool append_mode, void *data);
typedef t_stab_st		*(*t_get_stab)(void *data);
typedef int				(*t_get_last_ret)(void *data);

typedef struct s_parser
{
	t_vec			tokens;
	t_read_input	read_input;
	t_get_stab		get_stab;
	t_get_last_ret	get_last_ret;
	void			*data;
	t_str			last_input;
}					t_parser;

typedef enum e_ms_status
{
	MS_ERROR,
	MS_EOF,
	MS_OK
}	t_ms_status;

typedef struct s_list_words
{
	struct s_list_words	*next;
	char				*word;
}				t_list_words;

typedef struct s_redir_aim
{
	int			fd;
	char		*filename;
}				t_redir_aim;

typedef enum e_redir_type
{
	redir_append,
	redir_here_doc,
	redir_infile,
	redir_outfile,
}	t_redir_type;

typedef struct s_list_redir
{
	struct s_list_redir	*next;
	t_redir_type		instruction;
	t_redir_aim			target;
	char				*hd_del;
	bool				rightmost;
}						t_list_redir;

typedef struct s_simple_com
{
	bool			heredoc: 1;
	bool			builtin: 1;
	t_list_words	*words;
	t_list_redir	*redir;
	char			**argv;
	int				builtin_nr;
	int				prio_in;
}	t_simple_com;

typedef struct s_cmd_list
{
	t_simple_com		cmd;
	struct s_cmd_list	*next;
}	t_cmd_list;

void			debug_print_simple_com(int fd, t_simple_com *cmd, bool parser);
t_parser		parser_init(void *data, t_read_input read_input,
					t_get_stab get_stab, t_get_last_ret get_last_ret);
t_ms_status		parse_next_command(t_parser *p, t_cmd_list	**out);
void			parser_destroy(t_parser *p);

#endif
