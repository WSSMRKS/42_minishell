/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:56:05 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/10 09:33:51 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ms_parsing.h: Header file responsible for all the structures necessary to
 create the abstract symbol table (ast). */

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

/* file redirects always get priority??? */
typedef union u_redir_aim {
	int			fd;
	char		*filename;
	int			flags;
}				t_redir_aim;

/* Instead of input use infile/inpipe to distinguish.*/
enum	e_redir_type {
	// redir_output,
	// redir_input,
	redir_append,
	redir_here_doc,
	redir_infile,
	redir_outfile,
	redir_inpipe,
	redir_outpipe
};

typedef struct s_list_redir {
	struct s_list_redir	*next;
	enum e_redir_type	instruction;
	t_redir_aim			*from;
	t_redir_aim			*to;
	char				*hd_del;
	t_redir_aim			*hd_file;
	int					rightmost;
}				t_list_redir;

/*simple command struct: all commands that are without subshells and connections
	flags:
	1 = heredoc;

	words: words the command consists of.
	redirects: redirects of the command.*/
typedef struct s_simple_com {
	int				flags;
	t_list_words	*words;
	t_list_redir	*redir;
	int				builtin_nr;
	int				prio_in;		// 0 = stdin, 1 = pipe, 2 = infile, 3 = here_doc; (init to 0)
	int				prio_out;		// // 0 = stdout, 1 = pipe, 2 = outfile, 3 = append; (init to 0)
	}				t_simple_com;

typedef struct s_cmd_list {
	t_simple_com		*cmd;
	struct s_cmd_list	*next;
}				t_cmd_list;


/* content of flags field in t_word_desc */
# define WORD_DOLLAR			1		/* (1 << 0)		Dollar sign present. */
# define WORD_QUOTES_SINGLE		2		/* (1 << 1)		Quoted parts */
# define WORD_QUOTES_DOUBLE		4		/* (1 << 2)		Quoted parts */
# define WORD_VAR_ASSIGNMENT	8		/* (1 << 3)		This word is a variable assignment. */
# define WORD_SPLITSPACE		16		/* (1 << 4)		Split " " ignore IFS */
# define WORD_NOSPLIT			32		/* (1 << 5)		Do not perform word splitting on this word because ifs is empty string. */
# define WORD_NOGLOB			64		/* (1 << 6)		Do not perform globbing on this word. */
# define WORD_NOSPLIT2			128		/* (1 << 7)		Don't split word except for $@ expansion (using spaces) because context does not allow it. */
# define WORD_TILDEEXP			256		/* (1 << 8)		Tilde expand this assignment word */
# define WORD_ASSIGNRHS			512		/* (1 << 9)		Word is rhs of an assignment statement */
# define WORD_NOTILDE			1024	/* (1 << 10)		Don't perform tilde expansion on this word */
# define WORD_NOASSNTILDE		2048	/* (1 << 11)	don't do tilde expansion like an assignment statement */
# define WORD_ASSNBLTIN			4096	/* (1 << 12)	word is a builtin command that takes assignments */
# define WORD_ASSIGNARG			8192	/* (1 << 13)	word is assignment argument to command */
# define WORD_HASQUOTEDNULL		16384	/* (1 << 14)	word contains a quoted null character */
# define WORD_SAWQUOTEDNULL		32468	/* (1 << 15)	word contained a quoted null that was removed */

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
