/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wssmrks <wssmrks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:56:05 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/25 15:33:51 by wssmrks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSING_H
# define MS_PARSING_H
# include "minishell.h"

# define DEBUG_PARSER (false)
# define DBG_PARSER(x) if(DEBUG_PARSER) {x;}

typedef char			*(*t_read_input)(bool append_mode, void *data);
typedef t_symtab_stack	*(*t_get_symtab)(void *data);
typedef int				(*t_get_last_ret)(void *data);

typedef struct s_parser {
	t_vec			tokens;
	t_read_input	read_input;
	t_get_symtab	get_symtab;
	t_get_last_ret	get_last_ret;
	void			*data;
	t_str			last_input;
}					t_parser;

typedef enum e_ms_status {
	MS_ERROR,
	MS_EOF,
	MS_OK
}	t_ms_status;

typedef struct s_list_words {
	struct s_list_words	*next;
	char				*word;
}				t_list_words;


typedef struct s_redir_aim {
	int			fd;
	char		*filename;
}				t_redir_aim;

typedef enum	e_redir_type {
	redir_append,
	redir_here_doc,
	redir_infile,
	redir_outfile,
}	t_redir_type;

typedef struct s_list_redir {
	struct s_list_redir	*next;
	t_redir_type		instruction;	/* what is to be done*/
	t_redir_aim			*target;	/* fd or variable to be redirected */
	char				*hd_del; /* EOF token string, after << */
	int					rightmost;	/* valid redirection indicator*/
}				t_list_redir;

// typedef struct s_list_redir {
// 	struct s_list_redir	*next;
// 	enum e_redir_type	instruction;
// 	t_redir_aim			*from;
// 	t_redir_aim			*to;
// 	char				*hd_del;
// 	t_redir_aim			*hd_file;
// 	int					rightmost;
// }				t_list_redir;

/*simple command struct: all commands that are without subshells and connections
	flags:
	1 = heredoc;
	2 = is builtin;
	4 = is executable
	8 = is path (contains /)

	builtin_nr:
	1 = echo
	2 = cd
	3 = pwd
	4 = export
	5 = unset
	6 = env
	7 = exit

	words: words the command consists of.
	redirects: redirects of the command.*/
typedef struct	s_simple_com {
	bool			heredoc: 1;
	bool			builtin: 1;
	t_list_words	*words;
	t_list_redir	*redir;
	char			**argv;
	int				builtin_nr;
	int				prio_in;		// 0 = no_infiles, 1 = infiles_present; (init to 0)
}	t_simple_com;

typedef struct	s_cmd_list {
	t_simple_com		*cmd;
	struct s_cmd_list	*next;
}	t_cmd_list;

void		debug_print_simple_com(int fd, t_simple_com *cmd);
t_parser	parser_init(void *data, t_read_input read_input,
		t_get_symtab get_symtab, t_get_last_ret get_last_ret);
t_ms_status	parse_next_command(t_parser *p, t_cmd_list	**out);

#endif


/*example commands

cat >infile.txt
This is an infile.
This line should be visible when using grep bla
This line should be visible as well using grep bla
This line will not show up.
That is our infile.

"<infile.txt cat | grep bla >outfile"

representation in the AST:
t_command		cmd;
t_simple_com	simple;
t_list_words	words;


cmd.type = cmd_simple;
cmd.simple = ;

first.flags = ??
first.words =

typedef struct s_simple_com {
	int				flags;
	t_list_words	*words;
	t_redir			*redirects;
}				t_simple_com;

typedef struct s_list_words {
	struct s_list_words	*next;
	t_word_desc			*word;
}				t_list_words;

*/
