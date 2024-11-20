#include "../../../headers/minishell.h"
#include <stdio.h>

static bool	is_word_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '"' || c == '\'');
}

bool	token_has_str(t_token *token)
{
	return (token->type == TK_DQUOTE || token->type == TK_LITERAL || token->type == TK_WORD);
}

/// @brief Removes leading whitespace from a stringview.
/// @param s The stringview to trim.
void	strsl_trim_start_delim(t_str_slice *s)
{
	while (s->len && is_word_delimiter(*s->str))
	{
		s->str++;
		s->len--;
	}
}

/// @brief Checks if the string is an operator.
/// @param str The string to check.
/// @param out (Null)Pointer for output.
/// @return true if the string is an operator, false otherwise.
bool	str_is_operator(t_str_slice str, t_op_ty *out)
{
	size_t						i;
	static const t_str_slice	OPERATORS[] = {
    [OP_PIPE]={"|", 1},
    [OP_REDIRECT]={">", 1},
    [OP_INP_REDIRECT]={"<", 1},
    [OP_APPEND]={">>", 2},
    [OP_HEREDOC]={"<<", 2},
    {NULL, 0}
	};

	i = 0;
	while (OPERATORS[i].str)
	{
		if (strsl_eq(str, OPERATORS[i]))
		{
			if (out)
				*out = (t_op_ty)i;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	str_starts_with_op(t_str_slice str, t_op_ty *out)
{
	size_t						i;
	static const t_op_ty	OPERATORS[5] = {
	OP_APPEND,
	OP_HEREDOC,
	OP_PIPE,
	OP_REDIRECT,
	OP_INP_REDIRECT
	};

	i = 0;
	while (i < 5)
	{
		if (strsl_starts_with(str, cstr_view(op_str(OPERATORS[i]))))
		{
			if (out)
				*out = OPERATORS[i];
			return (true);
		}
		i++;
	}
	return (false);
}

/// @brief Checks if the string starts with a specific opening character
/// and contains its closing character.
/// @param str The string to check.
/// @param open The opening character (e.g., '"', '\'', '(')
/// @param close The closing character (e.g., '"', '\'', ')')
/// @param out The length of the bounded substring including delimiters.
/// @return The length of the bounded substring.
/// Returns 0 if not found or unterminated.
size_t	bounded_token_len(const char *str, char open, char close, size_t *out)
{
	if (*str != open)
		return (0);
	*out = 1;
	while (str[*out])
	{
		if (str[*out] == '\\' && str[*out + 1] != 0)
			(*out) += 2;
		else if (str[(*out)++] == close)
			return (*out);
	}
	return (0);
}

/// if the first character is '#' the rest of the string is treated as comment and should be thrown out
size_t	comment_len(const char *str)
{
	if (*str != '#')
		return (0);
	return (ft_strlen(str));
}

/// @brief Gets the length of a word delimited by is_word_delimiter.
/// @param str The string to check.
/// @param out The length of the word. (nullpointer allowed)
/// @return The length of the word.
size_t	word_len(const char *str, size_t *out)
{
	size_t	len;
	size_t	total_len;

	total_len = ft_strlen(str);
	len = 0;
	if (is_word_delimiter(str[len]))
		len = 1;
	while (str[len])
	{
		if (str[len] == '\\')
		{
			if (str[len + 1] == 0)
			{
				if (len == 0)
					len++;
				break;
			}
			len += 2;
		}
		else if (!is_word_delimiter(str[len])
			&& !str_starts_with_op(cstr_slice(&str[len], usizemin(total_len - len, 2)), 0))
			len++;
		else
			break ;
	}
	if (out)
		*out = len;
	return (len);
}

size_t	var_len(const char *str, size_t *out)
{
	size_t	len;

	if (*str != '$')
		return (0);
	len = 1;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	if (out)
		*out = len;
	return (len);
}

void	vec_push_tk(t_vec *vec, t_token tk)
{
	vec_push(vec, &tk);
}

const char	*op_str(t_op_ty op)
{
	static const char	*OP_STR[] = {
		[OP_PIPE]="|",
		[OP_REDIRECT]=">",
		[OP_INP_REDIRECT]="<",
		[OP_APPEND]=">>",
		[OP_HEREDOC]="<<",
	};

	return (OP_STR[op]);
}

void	token_print(const t_token *token, int fd)
{
	const char	*ty;
	const char	*tk_str;

	// depending on token type put their respective type as str
	if (token->type == TK_WORD)
		ty = "WORD";
	else if (token->type == TK_LITERAL)
		ty = "LIT";
	else if (token->type == TK_DQUOTE)
		ty = "DQUO";
	else if (token->type == TK_OPERATOR)
		ty = "OP";
	else if (token->type == TK_CONTINUE_NL)
		ty = "CONT_NL";
	else if (token->type == TK_NL)
		ty = "NL";
	else
		ty = "SEP";
	tk_str = "";
	if (token->type == TK_WORD || token->type == TK_LITERAL
		|| token->type == TK_DQUOTE)
		tk_str = cstr_ref(&token->str);
	else if (token->type == TK_OPERATOR)
		tk_str = op_str(token->op);
	ft_printf_fd(fd, "%-4s: (%s)", ty, tk_str);
}

// prints CMD: cmd <arg1> <arg2> <...> or OP : opstr oparg
void	ast_print(const t_ast *ast, int fd)
{
	size_t	i;

	if (ast->ty == AST_CMD)
	{
		ft_printf_fd(fd, "CMD: %s", ast->cmd[0]);
		i = 1;
		while (ast->cmd[i] != NULL)
		{
			ft_printf_fd(fd, " <%s>", ast->cmd[i]);
			i++;
		}
	}
	else if (ast->ty == AST_OP)
		ft_printf_fd(fd, "OP : %s %s", op_str(ast->op.ty), ast->op.arg);
}
