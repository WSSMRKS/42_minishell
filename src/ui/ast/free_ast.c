#include "../../../headers/minishell.h"

void	free_ast(void *ast_node)
{
	t_ast	*ast;

	ast = ast_node;
	if (ast->ty == AST_CMD)
	{
		ft_free_2d(ast->cmd);
		ast->cmd = NULL;
	}
	else
	{
		free(ast->op.arg);
		ast->op.arg = NULL;
	}
}
