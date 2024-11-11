#include "../../headers/minishell.h"



t_vec	tokens_to_ast(t_vec *tokens)
{
	// we need to go through the tokens until we find that a new node is beginning or that we reach the end
	// if our list of tokens contains an operator, the node becomes an operator node and we remove the operator from the list
	// else we have a command node
	// next we merge the tokens which can be merged into strings
	// for the command we just take the first string and use it as command and the rest are arguments
	// for the operator we just take all the strings and use them as arguments (they are correctly parsed in the last parsing step)
}
