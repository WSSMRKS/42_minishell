#include "../../../headers/minishell.h"

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

bool	add_redirection(t_simple_com *cmd, t_op *op)
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
