#include "../../../headers/minishell.h"
#include <stdbool.h>
#include <stddef.h>

// set flags like heredoc, redir->rightmost, ...
void	post_process_cmd(t_simple_com *cmd)
{
	t_list_redir	*redir;
	t_list_redir	*last_in;
	t_list_redir	*last_out;

	redir = cmd->redir;
	last_in = NULL;
	last_out = NULL;
	while (redir)
	{
		if (redir->instruction == redir_here_doc)
			cmd->heredoc = 1;
		if (redir->instruction == redir_infile || redir->instruction == redir_here_doc)
		{
			last_in = redir;
			redir->rightmost = false;
		}
		else if (redir->instruction == redir_outfile || redir->instruction == redir_append)
		{
			last_out = redir;
			redir->rightmost = false;
		}
		redir = redir->next;
	}
	if (last_in)
		last_in->rightmost = true;
	if (last_out)
		last_out->rightmost = true;
}

// do not use with OP_PIPE as it cant be mapped to a redirection
t_redir_type	op_to_redir(t_op op)
{
	static const t_redir_type	redir_map[] = {
		[OP_REDIRECT] = redir_outfile,
		[OP_INP_REDIRECT] = redir_infile,
		[OP_APPEND] = redir_append,
		[OP_HEREDOC] = redir_here_doc,
	};

	return (redir_map[op.ty]);
}

static void	list_add_redirection(t_simple_com *cmd, t_list_redir *redir)
{
	t_list_redir	*tmp;

	if (!cmd->redir)
	{
		cmd->redir = redir;
		return ;
	}
	tmp = cmd->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

static bool	add_redirection(t_simple_com *cmd, t_op *op)
{
	t_list_redir	*redir;

	if (op->ty == OP_PIPE)
	{
		perror("Pipe operator not supported in create_redirection");
		return (false);
	}
	redir = ft_calloc(sizeof(t_list_redir), 1);
	if (!redir)
		return (false);
	redir->target.fd = -1;
	redir->instruction = op_to_redir(*op);
	if (op->ty == OP_HEREDOC)
	{
		redir->hd_del = op->arg;
		redir->target.filename = NULL;
	}
	else
	{
		redir->hd_del = NULL;
		redir->target.filename = op->arg;
	}
	list_add_redirection(cmd, redir);
	op->arg = NULL;
	return (true);
}

static t_list_words *word_list_from_argv(char **cmd)
{
	t_list_words	*head;
	t_list_words	*current;
	t_list_words	*tmp;
	int				i;

	head = NULL;
	current = NULL;
	i = 0;
	while (cmd[i])
	{
		tmp = malloc(sizeof(t_list_words));
		if (!tmp)
		{
			free_list_words(&head);
			return (NULL);
		}
		tmp->word = ft_strdup(cmd[i]);
		tmp->next = NULL;
		if (!head)
			head = tmp;
		else
			current->next = tmp;
		current = tmp;
		i++;
	}
	return (head);
}

void	skip_pipe(t_ast *ast, size_t *i, size_t len)
{
	if (*i < len && ast[*i].ty == AST_OP && ast[*i].op.ty == OP_PIPE)
		(*i)++;
}

t_simple_com	com_from_ast(t_ast *ast, size_t *i, size_t len)
{
	t_simple_com	cmd;

	cmd = (t_simple_com){0};
	while (*i < len && (ast[*i].ty != AST_OP || ast[*i].op.ty != OP_PIPE))
	{
		if (ast[*i].ty == AST_CMD)
		{
			cmd.words = word_list_from_argv(ast[*i].cmd);
			if (cmd.words == NULL)
			{
				free_simple_com(&cmd);
				return ((t_simple_com){0});
			}
			cmd.argv = ast[*i].cmd;
			ast[*i].cmd = NULL;
		}
		else if (ast[*i].ty == AST_OP)
		{
			if (!add_redirection(&cmd, &ast[*i].op))
			{
				free_simple_com(&cmd);
				return ((t_simple_com){0});
			}
		}
		(*i)++;
	}
	post_process_cmd(&cmd);
	return (cmd);
}

/// input: ast with minimum one item
t_cmd_list	*ast_to_commands(t_vec *ast)
{
	t_cmd_list	*head;
	t_cmd_list	*current;
	size_t		i;

	head = NULL;
	i = 0;
	while (i < ast->len)
	{
		if (head != NULL)
		{
			current->next = ft_calloc(sizeof(t_cmd_list), 1);
			current = current->next;
		}
		else
		{
			current = ft_calloc(sizeof(t_cmd_list), 1);
			head = current;
		}
		current->cmd = com_from_ast(vec_get(ast), &i, ast->len);
		skip_pipe(vec_get(ast), &i, ast->len);
		DEBUG(debug_print_simple_com(STDERR, &current->cmd, true))
		if (current->cmd.words == NULL && current->cmd.redir == NULL)
		{
			free_list_cmds(&head);
			return (NULL);
		}
	}
	return (head);
}

#include <stdio.h>

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
