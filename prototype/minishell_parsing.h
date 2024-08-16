/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:56:05 by maweiss           #+#    #+#             */
/*   Updated: 2024/08/16 16:43:55 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H



enum	e_command_type {
	cmd_connection,
	cmd_simple,
	cmd_subshell
};


/*command struct: the root node of any command.
	connection: && or ||
	simple_com: simple commands and redirects
	subshell_com: subshell commands --> new child */
typedef struct s_command {
	enum e_command_type	type;
	int					flags;
	union {
		struct simple_com	*simple;
		struct connection	*connection;
		struct subshell_com	*subshell;
	} u_value;
}				t_command;

/*simple command struct: all commands that are without subshells and connections
	flags:
	words: words the command consists of.
	redirects: redirects of the command.*/
typedef struct s_simple_com {
	int				flags;
	t_list_words	*words;
	t_redir			*redirects;
}				t_simple_com;

typedef struct s_list_words {
	struct s_list_words	*next;
	t_word_desc			*word;
}				t_list_words;

typedef struct s_word_desc {
	char	*word;
	int		flags;
}				t_word_desc;

typedef struct s_redir {
	struct s_redir		*next;
	t_redir_aim			*from;
	int					rflags;
	int					flags;
	enum e_redir_type	instruction;
	t_redir_aim			*to;
	char				*here_doc_del;
}				t_redir;

enum	e_redir_type {
	redir_output,
	redir_input,
	redir_append,
	redir_here_doc
};

typedef union u_redir_aim {
	int			fd;
	t_word_desc	*filename;
}				t_redir_aim;

#endif
