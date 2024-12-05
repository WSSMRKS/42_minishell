/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:24:54 by sgramsch          #+#    #+#             */
/*   Updated: 2024/10/29 14:24:54 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unclosed(char *str)
{
	int	pos;
	int	single;
	int	duble;

	pos = 0;
	single = 0;
	duble = 0;
	while (str[pos])
	{
		if (str[pos] == '\'')
		{
			if (duble % 2 == 0)
				single ++;
		}
		else if (str[pos] == '\"')
		{
			if (single % 2 == 0)
				duble ++;
		}
		pos ++;
	}
	if (single % 2 != 0 || duble % 2 != 0)
		return (1);
	return (0);
}

int	last_pipe(char *str)
{
	int	pos;

	pos = ft_strlen(str) - 1;
	while (str[pos])
	{
		if (str[pos] == '|')
			return (1);
		else if (!is_whitespace(str[pos]))
			return (0);
		pos --;
	}
	return (0);
}

void	pipe_loop(t_data *data, char *in)
{
	while (last_pipe(data->input))
	{
		set_signal_heredoc();
		in = readline(">");
		set_signals_noninteractive();
		if (g_signal == SIGINT)
		{
			if (in)
				free(in);
			if (data->input)
				free(data->input);
			data->input = NULL;
			return ;
		}
		if (in == NULL)
			exit_on_error(data, ENOF, 1, data->status);
		data->input = join(data->input, in);
	}
	if (unclosed(data->input))
	{
		free(data->input);
		data->input = NULL;
		printf("\033[31mInvalid input. Close quotes please!\n\033[0m");
	}
}

void	get_full_input_line(t_data *data)
{
	if (g_signal == SIGINT || g_signal == SIGQUIT)
		data->status = 128 + g_signal;
	set_signals_interactive();
	data->input = readline(PROMPT);
	set_signals_noninteractive();
	if (data->input == NULL)
		exit_on_error(data, ENOF, 1, 0);
	if (unclosed(data->input))
	{
		free(data->input);
		data->input = NULL;
		printf("\033[31mInvalid input. Close quotes please!\n\033[0m");
		return ;
	}
	if (last_pipe(data->input))
	{
		pipe_loop(data, NULL);
		return ;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	set_up_data(&data, envp, argc, argv);
	while (1)
	{
		data.parent = 0;
		get_full_input_line(&data);
		if (g_signal == SIGINT || g_signal == SIGQUIT)
			data.status = 128 + g_signal;
		if (data.input == NULL || is_blank(data.input))
		{
			small_cleanup(&data);
			continue ;
		}
		add_history(data.input);
		data.command_count = cmd_count(data.input);
		if (input_setup(&data) != 1 && data.dont == 0)
			create_subshell(&data);
		else if (data.dont == 0)
			data.status = 2;
		small_cleanup(&data);
	}
	data.parent = 0;
	cleanup(&data);
	return (0);
}
