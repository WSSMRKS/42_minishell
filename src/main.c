#include "../headers/minishell.h"

void	symtab_add_value(t_symtab_stack *st, char *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	value = ft_strdup(&env[i + 1]);
	if (ft_lookup_symtab(st, key) != NULL)
	{
		ft_update_symtab_value(st, key, value);
		free(value);
		free(key);
	}
	else
		ft_add_to_symtab(st, key, value);
}

t_symtab_stack	init_symtab(char **envp)
{
	size_t			i;
	t_symtab_stack	st;

	i = 0;
	while (envp[i])
		i++;
	st = (t_symtab_stack){0};
	st.size = ft_calc_symtab_size(i);
	st.load_factor = 0;
	st.level = 1;
	st.symtab = ft_calloc(sizeof(char *), st.size);
	i = 0;
	while (envp[i])
		symtab_add_value(&st, envp[i++]);
	return (st);
}

void	print_all_tokens(t_vec *tokens)
{
	for (size_t i = 0; i < tokens->len; i++)
	{
		t_token *token = vec_get_at(tokens, i);
		token_print(token, STDOUT);
		if (!write(STDOUT, "\n", 1))
		{
			perror("write error");
			exit(1);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_vec			tokens;
	t_symtab_stack	st;


	(void)argc;
	(void)argv;
	(void)envp;
	st = init_symtab(envp);

    while (1)
    {
        input = readline(">>> ");
        if (!input)
        {
            break; // Exit on EOF (Ctrl+D)
        }

        if (*input)
        {
            add_history(input);
        }

		tokens = tokenize(cstr_view(input));
		ft_printf("You entered: (%s)\n", input);
		ft_printf("tokens: %lu\n", tokens.len);
		print_all_tokens(&tokens);
		expand_vars(&tokens, &st);
		ft_printf("--------------------------------\nEXPANDED\n");
		print_all_tokens(&tokens);
		unescape_chars(&tokens);
		ft_printf("--------------------------------\nUNESCAPED\n");
		print_all_tokens(&tokens);
        free(input);
    }

    return 0;
}
