/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:25:49 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/13 11:21:40 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static t_vec	vec_strs_from_nullterm(char **argv)
{
	t_vec	vec;
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	vec = vec_new_from(argv, sizeof(char *), i);
	return (vec);
}

static bool	combine_argv(char ***dst, char ***argv)
{
	t_vec	dst_vec;
	t_vec	src_vec;
	t_vec	combined;

	dst_vec = vec_strs_from_nullterm(*dst);
	src_vec = vec_strs_from_nullterm(*argv);
	combined = vec_empty_with_capacity(sizeof(char *),
			dst_vec.len + src_vec.len + 1);
	if (combined.mem_err)
		return (false);
	vec_pushvec(&combined, &dst_vec);
	vec_pushvec(&combined, &src_vec);
	vec_push_null(&combined);
	*dst = vec_take(&combined);
	if (*dst == NULL)
	{
		*dst = vec_take(&dst_vec);
		return (false);
	}
	free(vec_take(&dst_vec));
	free(vec_take(&src_vec));
	*argv = NULL;
	return (true);
}

bool	add_argv(char ***dst, char ***argv)
{
	if (*dst == NULL)
	{
		*dst = *argv;
		*argv = NULL;
	}
	else
	{
		if (!combine_argv(dst, argv))
			return (false);
	}
	return (true);
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
		if (redir->instruction == redir_infile
			|| redir->instruction == redir_here_doc)
			last_in = redir;
		else if (redir->instruction == redir_outfile
			|| redir->instruction == redir_append)
			last_out = redir;
		redir = redir->next;
	}
	if (last_in)
		last_in->rightmost = true;
	if (last_out)
		last_out->rightmost = true;
}
