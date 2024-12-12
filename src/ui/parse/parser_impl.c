#include "../../../headers/minishell.h"

static char *read_input(bool append_mode, void *data)
{
	char		*prompt;
	char		*input;

	if (!isatty(STDIN))
	{
		input = get_next_line(STDIN);
		if (input && *input && input[ft_strlen(input) - 1] == '\n')
			input[ft_strlen(input) - 1] = '\0';
		return (input);
	}
	prompt = get_prompt(data);
	if (append_mode)
		input = readline("> ");
	else
		input = readline(prompt);
	free(prompt);
	return (input);
}

static t_stab_st	*get_stab(void *data)
{
	t_ms	*ms;

	ms = (t_ms *)data;
	return (ms->be->global_stabs);
}

static int	get_last_ret(void *data)
{
	t_ms	*ms;

	ms = (t_ms *)data;
	if (g_signal != 0)
		return (g_signal);
	else
		return (ms->be->last_ret);
}

t_parser	ms_parser_init(t_ms *ms)
{
	return (parser_init(ms, read_input, get_stab, get_last_ret));
}
