#include "../../../headers/minishell.h"

static void	str_expand_vars(t_str *str, t_symtab_stack *st)
{
	t_str	var_str;
	size_t	var_size;
	size_t	i;
	char	*buf;
	t_str_slice var;

	i = 0;
	while (i < str->len)
	{
		buf = cstr_mut(str);
		if (buf[i] == '$')
		{
			var_str = str_clone_from(cstr_slice(&buf[i+1], var_len(&buf[i], &var_size) - 1));
			var = cstr_view(ft_lookup_symtab(st, (char *)cstr_ref(&var_str)));
			str_remove_range(str, i, i + var_size);
			if (var.str)
			{
				str_insertstr(str, i, var);
				i += var.len;
			}
		}
		else
			i++;
	}
}

void	expand_vars(t_vec *tokens, t_symtab_stack *st)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TOKEN_WORD || token->type == TOKEN_DQUOTE)
			str_expand_vars(&token->str, st);
		i++;
	}
}
