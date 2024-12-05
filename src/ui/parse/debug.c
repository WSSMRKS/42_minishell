/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:48:22 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/05 18:11:18 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
#include "parse_util.h"
#include "../token/tk_util.h"

void	print_all_tokens(t_vec *tokens)
{
	for (size_t i = 0; i < tokens->len; i++)
	{
		t_token *token = vec_get_at(tokens, i);
		token_print(token, STDERR);
		if (!write(STDERR, "\n", 1))
			perror("write error");
	}
}

void	ast_printstr(t_vec *ast)
{
	size_t	i;
	t_str	ast_line;

	i = 0;
	ast_line = str_empty();
	while (i < ast->len)
	{
		str_push_ast(&ast_line, vec_get_at(ast, i), i == 0);
		i++;
	}
	write(2, "[DBG] parsed AST: ", 18);
	write(2, cstr_ref(&ast_line), ast_line.len);
	write(2, "\n", 1);
	str_destroy(&ast_line);
}

void	debug_print_simple_com(int fd, t_simple_com *cmd, bool parser)
{
	t_list_words *word_ptr;
	t_list_redir *redir_ptr;
	int i;

	if (!cmd)
	{
		dprintf(fd, "NULL simple command\n");
		return;
	}

	// Print flags and builtin info
	dprintf(fd, "Simple Command:\n");
	dprintf(fd, "├─ Heredoc flag: %d\n", cmd->heredoc);
	if (!parser)
	{
		dprintf(fd, "├─ Builtin flag: %d\n", cmd->builtin);
		dprintf(fd, "├─ Builtin number: %d\n", cmd->builtin_nr);
		dprintf(fd, "├─ Priority in: %d\n", cmd->prio_in);
	}
	// dprintf(fd, "├─ Priority out: %d\n", cmd->prio_out);

	// Print words list
	dprintf(fd, "├─ Words:\n");
	word_ptr = cmd->words;
	while (word_ptr)
	{
		dprintf(fd, "│  ├─ '%s'\n", word_ptr->word);
		word_ptr = word_ptr->next;
	}

	// Print argv array
	dprintf(fd, "├─ Argv:\n");
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			dprintf(fd, "│  ├─ [%d]: '%s'\n", i, cmd->argv[i]);
			i++;
		}
	}
	else
		dprintf(fd, "│  └─ NULL\n");

	// Print redirections
	dprintf(fd, "└─ Redirections:\n");
	redir_ptr = cmd->redir;
	while (redir_ptr)
	{
		dprintf(fd, "   ├─ Type: ");
		switch (redir_ptr->instruction)
		{
			case redir_append:
				dprintf(fd, "APPEND\n");
				break;
			case redir_here_doc:
				dprintf(fd, "HEREDOC\n");
				break;
			case redir_infile:
				dprintf(fd, "INFILE\n");
				break;
			case redir_outfile:
				dprintf(fd, "OUTFILE\n");
				break;
		}
		if (redir_ptr->target.filename)
		{
			if (!parser)
				dprintf(fd, "   │  ├─ Target FD: %d\n", redir_ptr->target.fd);
			dprintf(fd, "   │  └─ Filename: %s\n", redir_ptr->target.filename);
		}
		if (redir_ptr->hd_del)
			dprintf(fd, "   │  └─ Heredoc delimiter: %s\n", redir_ptr->hd_del);
		dprintf(fd, "   │  └─ Rightmost: %d\n", redir_ptr->rightmost);
		redir_ptr = redir_ptr->next;
	}
	fflush(0);
}
