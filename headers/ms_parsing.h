/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:56:05 by maweiss           #+#    #+#             */
/*   Updated: 2024/10/31 12:14:31 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSING_H
# define MS_PARSING_H
# include "minishell.h"

// typedef struct s_word_desc {
// 	char	*word;
// 	int		flags;
// }				t_word_desc;

/*NOT USED ANYMORE:
enum	e_command_type {
	cmd_connection,
	cmd_simple,
	cmd_subshell
}; */

typedef struct s_list_words {
	struct s_list_words	*next;
	char				*word;
	int					flags;
}				t_list_words;


/*NOT USED ANYMORE!! command struct: the root node of any command.
	connection: && or ||
	simple_com: simple commands and redirects
typedef struct s_command {
	enum e_command_type	type;
	union {
		struct simple_com	*simple;
		struct connection	*connection;
	} u_value;
}				t_command; */

/* file redirects always get priority???*/
// [ ]	used to be a union doesn't work with the flag
typedef struct s_redir_aim {
	int			fd;
	char		*filename;
	int			flags;
}				t_redir_aim;

/* Instead of input use infile/inpipe to distinguish.*/
typedef enum	e_redir_type {
	redir_err,
	redir_append,
	redir_here_doc,
	redir_infile,
	redir_outfile,
	redir_inpipe,
	redir_outpipe
} e_redir_type;

typedef struct s_list_redir {
	struct s_list_redir	*next;
	e_redir_type	instruction;	/* what is to be done*/
	t_redir_aim			*target;	/* fd or variable to be redirected */
	char				*hd_del; /* EOF token string, after << */
	t_redir_aim			*hd_file;	/* hd tmp file fd and name*/
	int					rightmost;	/* valid redirection indicator*/
}				t_list_redir;

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
typedef struct s_simple_com {
	int				flags;			// Space for the general flags referring to the command (builtin path, ...)
	t_list_words	*words;
	t_list_redir	*redir;
	char			**argv;
	int				builtin_nr;
	int				prio_in;		// 0 = stdin, 1 = pipe, 2 = infile, 3 = here_doc; (init to 0)
	int				prio_out;		// // 0 = stdout, 1 = pipe, 2 = outfile, 3 = append; (init to 0)
	}				t_simple_com;

typedef struct s_cmd_list {
	t_simple_com		*cmd;
	struct s_cmd_list	*next;
}				t_cmd_list;


/* content of flags field in t_word_desc */
# define WORD_DOLLAR				1				/* (1 << 0) Dollar sign present. */
# define WORD_QUOTES_SINGLE			2				/* (1 << 1) Quoted parts */
# define WORD_QUOTES_DOUBLE			4				/* (1 << 2) Quoted parts */
# define WORD_VAR_ASSIGNMENT		8				/* (1 << 3) This word is a variable assignment. */
# define WORD_IS_BUILTIN			16				/* (1 << 4) word is a builtin command */
# define WORD_IS_EXEC				32				/* (1 << 5) word is an executable (lookup $PATH) */
# define WORD_IS_PATH				64				/* (1 << 6) word is an absolute or relative path */

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
