/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:04:48 by sgramsch          #+#    #+#             */
/*   Updated: 2024/12/05 12:34:25 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*edit_heredoc(t_data *data, char *in, t_token *delimiter)
{
	t_var	*var;

	var_init(data);
	var = data->var;
	while (in[var->pos])
	{
		if (in[var->pos] == '$' && !delimiter->quotes)
			env_expanding(data, var, in);
		var->pos ++;
	}
	if (var->start < var->pos)
	{
		var->end = var->pos - 1;
		add_normal(data, in, var);
	}
	free(in);
	in = var->new;
	var->new = NULL;
	var = free_var(data);
	return (in);
}

void	heredoc_loop(t_data *data, t_cmd_list *cmd)
{
	char	*in;

	set_signal_heredoc();
	in = readline("heredoc> ");
	if (heredoc_checker(data, in, cmd) == 1)
	{
		free(in);
		return ;
	}
	while (ft_strncmp(in, cmd->input_argument->str,
			ft_strlen(cmd->input_argument->str)) != 0)
	{
		if (cmd->input_argument->quotes == 0)
			in = edit_heredoc(data, in, cmd->input_argument);
		write(cmd->heredoc_pipe[1], in, ft_strlen(in));
		write(cmd->heredoc_pipe[1], "\n", 1);
		free(in);
		set_signal_heredoc();
		in = readline("heredoc> ");
		set_signals_noninteractive();
		if (heredoc_checker(data, in, cmd) == 1)
			break ;
	}
	free(in);
}
