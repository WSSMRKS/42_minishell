#include "../../../headers/minishell.h"

static void	strip_empty_word_tokens(t_vec *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_WORD && token->str.len == 0)
			vec_remove_at(tokens, i);
		else
			i++;
	}
}

static void	insert_var(t_stab_st *st, t_str *var_str, t_str *str, size_t i)
{
	t_str_slice	var;

	var = cstr_view(ft_lookup_stab(st, (char *)cstr_ref(var_str)));
	if (var.str)
	{
		str_insertstr(str, i, var);
		i += var.len;
	}
}

static void	get_var_and_del_chars(t_str *str, size_t *var_size, t_str *var_str, size_t i)
{
	char	*buf;

	buf = cstr_mut(str);
	*var_str = str_clone_from(cstr_slice(&buf[i+1],
				usizemax(var_len(&buf[i], var_size), 1) - 1));
	if (var_size != 0)
		str_remove_range(str, i, i + *var_size);
}

void	str_expand_vars(t_str *str, t_stab_st *st, int last_ret)
{
	t_str	var_str;
	size_t	var_size;
	size_t	i;

	i = 0;
	while (i < str->len)
	{
		if (cstr_mut(str)[i] == '$' && !char_is_escaped(cstr_ref(str), i))
		{
			get_var_and_del_chars(str, &var_size, &var_str, i);
			if (var_size == 0)
			{
				i++;
				continue;
			}
			if (strsl_eq(str_view(&var_str), cstr_slice("?", 1)))
				str_insert_itoa(last_ret, base10(), str, i);
			else
				insert_var(st, &var_str, str, i);
			str_destroy(&var_str);
		}
		else
			i++;
	}
}

void	expand_vars(t_vec *tokens, t_stab_st *st, int last_ret)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		token = vec_get_at(tokens, i);
		if (token->type == TK_WORD || token->type == TK_DQUOTE)
			str_expand_vars(&token->str, st, last_ret);
		i++;
	}
	strip_empty_word_tokens(tokens);
}
