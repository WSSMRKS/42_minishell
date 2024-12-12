#include "../../../headers/minishell.h"

t_list_words *word_list_from_argv(char **cmd)
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
			last_in = redir;
		else if (redir->instruction == redir_outfile || redir->instruction == redir_append)
			last_out = redir;
		redir = redir->next;
	}
	if (last_in)
		last_in->rightmost = true;
	if (last_out)
		last_out->rightmost = true;
}
