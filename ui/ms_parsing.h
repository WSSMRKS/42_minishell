/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:56:05 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/20 13:11:43 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ms_parsing.h: Header file responsible for all the structures necessary to
 create the abstract symbol table (ast). */

#ifndef MS_PARSING_H
# define MS_PARSING_H

typedef struct s_word_desc {
	char	*word;
	int		flags;
}				t_word_desc;

enum	e_command_type {
	cmd_connection,
	cmd_simple,
	cmd_subshell
};

typedef struct s_list_words {
	struct s_list_words	*next;
	t_word_desc			*word;
}				t_list_words;


/*command struct: the root node of any command.
	connection: && or ||
	simple_com: simple commands and redirects */
typedef struct s_command {
	enum e_command_type	type;
	union {
		struct simple_com	*simple;
		struct connection	*connection;
	} u_value;
}				t_command;

typedef union u_redir_aim {
	int			fd;
	t_word_desc	*filename;
}				t_redir_aim;

enum	e_redir_type {
	redir_output,
	redir_input,
	redir_append,
	redir_here_doc
};

typedef struct s_redir {
	struct s_redir		*next;
	t_redir_aim			*from;
	enum e_redir_type	instruction;
	t_redir_aim			*to;
	char				*here_doc_del;
}				t_redir;

/*simple command struct: all commands that are without subshells and connections
	flags:
	words: words the command consists of.
	redirects: redirects of the command.*/
typedef struct s_simple_com {
	int				flags;
	t_list_words	*words;
	t_redir			*redirects;
}				t_simple_com;


/* content of flags field in t_word_desc */
# define WORD_DOLLAR			1		/* (1 << 0)		Dollar sign present. */
# define WORD_QUOTED			2		/* (1 << 1)		Quoted parts */
# define WORD_VAR_ASSIGNMENT	4		/* (1 << 2)		This word is a variable assignment. */
# define WORD_SPLITSPACE		8		/* (1 << 3)		Split " " ignore IFS */
# define WORD_NOSPLIT			16		/* (1 << 4)		Do not perform word splitting on this word because ifs is empty string. */
# define WORD_NOGLOB			32		/* (1 << 5)		Do not perform globbing on this word. */
# define WORD_NOSPLIT2			64		/* (1 << 6)		Don't split word except for $@ expansion (using spaces) because context does not allow it. */
# define WORD_TILDEEXP			128		/* (1 << 7)		Tilde expand this assignment word */
# define WORD_ASSIGNRHS			256		/* (1 << 8)		Word is rhs of an assignment statement */
# define WORD_NOTILDE			512		/* (1 << 9)		Don't perform tilde expansion on this word */
# define WORD_NOASSNTILDE		1024	/* (1 << 10)	don't do tilde expansion like an assignment statement */
# define WORD_ASSNBLTIN			2048	/* (1 << 11)	word is a builtin command that takes assignments */
# define WORD_ASSIGNARG			4096	/* (1 << 12)	word is assignment argument to command */
# define WORD_HASQUOTEDNULL		8192	/* (1 << 13)	word contains a quoted null character */
# define WORD_SAWQUOTEDNULL		16384	/* (1 << 14)	word contained a quoted null that was removed */

#endif
