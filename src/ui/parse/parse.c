#include "../../../headers/minishell.h"

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

static t_list_redir *create_redirection(t_op op)
{
	t_list_redir	*redir;

	if (op.ty == OP_PIPE)
	{
		perror("Pipe operator not supported in create_redirection");
		return (NULL);
	}
	redir = calloc(sizeof(t_list_redir), 1);
	if (!redir)
		return (NULL);
	redir->target = malloc(sizeof(t_redir_aim));
	if (!redir->target)
	{
		free(redir);
		return (NULL);
	}
	redir->target->fd = -1;
	redir->target->filename = op.arg;
	redir->instruction = op_to_redir(op);
	if (op.ty != OP_HEREDOC)
		return (redir);
	redir->hd_del = redir->target->filename;
	redir->target->filename = NULL;
	return (redir);
}

void	free_list_words(t_list_words *head)
{
	t_list_words *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->word);
		free(tmp);
	}
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
			free_list_words(head);
			return NULL;
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
	return head;
}

void	free_list_redir(t_list_redir *redir)
{
	t_list_redir *tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->target)
		{
			free(tmp->target->filename);
			free(tmp->target);
		}
		free(tmp->hd_del);
		free(tmp);
	}
}

void	free_2d(char **strs);

void	free_simple_command(t_simple_com *cmd)
{
	free_list_words(cmd->words);
	free_list_redir(cmd->redir);
	free_2d(cmd->argv);
	free(cmd);
}

void	free_list_commands(t_cmd_list *head)
{
	t_cmd_list *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_simple_command(tmp->cmd);
		free(tmp);
	}
}

static t_simple_com	*create_simple_command(char **cmd)
{
	t_simple_com	*simple;

	simple = calloc(sizeof(t_simple_com), 1);
	if (!simple)
		return NULL;
	simple->words = word_list_from_argv(cmd);
	simple->argv = cmd;
	return simple;
}

t_cmd_list	*ast_to_commands(t_vec *ast)
{
	t_cmd_list		*head;
	t_cmd_list		*prev;
	t_cmd_list		*current;
	t_list_redir	*redir_head;
	t_list_redir	*redir_prev;
	t_list_redir	*redir_current;
	t_ast			*current_ast;
	size_t			i;

	head = NULL;
	prev = NULL;
	redir_head = NULL;
	redir_prev = NULL;
	i = 0;
	redir_current = NULL;
	current = NULL;
	while (i < ast->len)
	{
		current_ast = vec_get_at(ast, i);
		if (current_ast->ty == AST_CMD)
		{
			current = ft_calloc(sizeof(t_cmd_list), 1);
			if (!current)
			{
				free_list_commands(head);
				free_list_redir(redir_head);
				return (NULL);
			}
			current->cmd = create_simple_command(current_ast->cmd);
			if (current->cmd == NULL)
			{
				free_list_commands(head);
				free_list_redir(redir_head);
				return (NULL);
			}
			if (!head)
				head = current;
			else
				prev->next = current;
			prev = current;
		}
		else if (current_ast->ty == AST_OP && current_ast->op.ty != OP_PIPE)
		{
			redir_current = create_redirection(current_ast->op);
			if (!redir_current)
			{
				free_list_commands(head);
				free_list_redir(redir_head);
				return (NULL);
			}
			if (!redir_head)
				redir_head = redir_current;
			else
				redir_prev->next = redir_current;
			redir_prev = redir_current;
		}
		if (redir_head && current)
		{
			if (!current->cmd->redir)
				current->cmd->redir = redir_head;
			else
			{
				redir_current = current->cmd->redir;
				while (redir_current->next)
					redir_current = redir_current->next;
				redir_current->next = redir_head;
			}
			redir_head = NULL;
		}
		if (current)
			post_process_cmd(current->cmd);
		i++;
	}
	return (head);
}

#include <stdio.h>

void	debug_print_simple_com(int fd, t_simple_com *cmd)
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
	dprintf(fd, "├─ Builtin flag: %d\n", cmd->builtin);
	dprintf(fd, "├─ Builtin number: %d\n", cmd->builtin_nr);
	dprintf(fd, "├─ Priority in: %d\n", cmd->prio_in);
	dprintf(fd, "├─ Priority out: %d\n", cmd->prio_out);

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
		if (redir_ptr->target)
		{
			dprintf(fd, "   │  ├─ Target FD: %d\n", redir_ptr->target->fd);
			dprintf(fd, "   │  └─ Filename: %s\n", redir_ptr->target->filename);
		}
		if (redir_ptr->hd_del)
			dprintf(fd, "   │  └─ Heredoc delimiter: %s\n", redir_ptr->hd_del);
		dprintf(fd, "   │  └─ Rightmost: %d\n", redir_ptr->rightmost);
		redir_ptr = redir_ptr->next;
	}
	fflush(0);
}
