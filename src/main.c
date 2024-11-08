#include "../headers/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_vec	tokens;

	(void)argc;
	(void)argv;
	(void)envp;

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
		printf("You entered: (%s)\n", input);
		printf("tokens: %lu\n", tokens.len);
		for (size_t i = 0; i < tokens.len; i++)
		{
			t_token *token = vec_get_at(&tokens, i);
			token_print(token, STDOUT);
			if (!write(STDOUT, "\n", 1))
			{
				perror("write");
				exit(1);
			}
		}

        free(input);
    }

    return 0;
}
