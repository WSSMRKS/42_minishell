#include "../headers/minishell.h"
#include <stdio.h>

void	stab_add_val(t_ms *ms, t_stab_st *st, char *env)
{
	char	*key;
	char	*val;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	val = ft_strdup(&env[i + 1]);
	if (ft_lookup_stab(st, key) != NULL)
	{
		ft_upd_stab_val(st, key, val);
		free(val);
		free(key);
	}
	else
		ft_add_to_stab(ms, st, key, val);
}

t_stab_st	init_stab(char **envp)
{
	size_t			i;
	t_stab_st	st;

	i = 0;
	while (envp[i])
		i++;
	st = (t_stab_st){0};
	st.size = ft_calc_stab_size(i);
	st.load_factor = 0;
	st.level = 1;
	st.stab = ft_calloc(sizeof(char *), st.size);
	i = 0;
	while (envp[i])
		stab_add_val(&st, envp[i++]);
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

void	print_all_ast(t_vec *ast)
{
	for (size_t i = 0; i < ast->len; i++)
	{
		t_ast *node = vec_get_at(ast, i);
		ast_print(node, STDOUT);
		if (!write(STDOUT, "\n", 1))
		{
			perror("write error");
			exit(1);
		}
	}
}

void    debug_print_simple_com(int fd, t_simple_com *cmd);

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_vec			tokens;
	t_vec			tmp;
	t_vec			ast;
	t_stab_st	st;
	t_cmd_list		*cmd_list;

	(void)argc;
	(void)argv;
	(void)envp;
	st = init_stab(envp);

	tokens = vec_empty(sizeof(t_token));
	while (1)
	{
		if (tokens.len == 0)
			input = readline(">>> ");
		else
			input = readline("> ");
		if (!input)
			break; // Exit on EOF (Ctrl+D)
		if (*input)
			add_history(input);
		tmp = tokenize(cstr_view(input));
		ft_printf("You entered: (%s)\n", input);
		free(input);
		ft_printf("tokens: %lu\n", tmp.len);
		print_all_tokens(&tmp);
		expand_vars(&tmp, &st);
		ft_printf("--------------------------------\nEXPANDED\n");
		print_all_tokens(&tmp);
		unescape_chars(&tmp);
		ft_printf("--------------------------------\nUNESCAPED\n");
		print_all_tokens(&tmp);
		vec_pushvec(&tokens, &tmp);
		if (tokens.len > 0 && ((t_token *)vec_get_last(&tokens))->type == TK_CONTINUE_NL)
			((t_token *)vec_get_last(&tokens))->type = TK_SEPERATOR;
		else // use vec_destroy instead
		{
			tokens_normalize(&tokens);
			ft_printf("--------------------------------\nNORMALIZED\n");
			print_all_tokens(&tokens);
			if (!tokens_to_ast(&tokens, &ast))
				perror("tokens to ast memerr");
			ft_printf("--------------------------------\nAST\n");
			print_all_ast(&ast);
			cmd_list = ast_to_commands(&ast);
			while (cmd_list)
			{
				debug_print_simple_com(STDOUT, cmd_list->cmd);
				cmd_list = cmd_list->next;
			}
			tokens = vec_empty(sizeof(t_token));
		}
    }

    return 0;
}
