/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/27 15:27:59 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_extr_key_val(char *env, char **key, char **val)
{
	int			i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] != '=')
		*val = NULL;
	else if (env[i] == '=' && env[i + 1] == '\0')
	{
		*val = ft_calloc(sizeof(char), 1);
		ft_mprotect((void *)*val);
	}
	else
	{
		*val = ft_strdup(&env[i + 1]);
		ft_mprotect((void *)*val);
	}
	*key = ft_substr(env, 0, i);
	ft_mprotect((void *)*key);
}

/* function to add a new val to the environmental variables
functionality:
1. Find the position of the equal sign in the string
2. Create a new string with the key
3. Create a new string with the val
4. Check if the load factor is greater than 0.7
5. If the load factor is greater than 0.7, resize the symbol table
6. Increment the used variable
7. Calculate the new load factor
8. Add the val to the symbol table
*/
void	ft_add_global_val(t_ms *ms, char *env)
{
	char		*key;
	char		*val;

	key = NULL;
	val = NULL;
	ft_extr_key_val(env, &key, &val);
	if (ft_validate_var(key) != NULL)
	{
		free(key);
		free(val);
		return ;
	}
	if (ft_lookup_key(ms->be->global_stabs, key) != NULL)
		ft_upd_stab_val(ms->be->global_stabs, key, val);
	else
		ft_add_to_stab(ms, ms->be->global_stabs, key, val);
	free(val);
	val = NULL;
	free(key);
	key = NULL;
}

/* function to add a new val to the symbol table
functionality:
1. Calculate the hash val of the key
2. Create a new symbol table entry
3. If the position in the symbol table is empty, add the val
4. If the position in the symbol table is not empty,
traverse the linked list and add the val
*/
void	ft_add_to_stab(t_ms *ms, t_stab_st *stab_lvl, char *key, char *val)
{
	unsigned long	hash;
	t_stab			*new;
	t_stab			*tmp;


	hash = ft_hash_function(stab_lvl, key);
	new = ft_calloc(sizeof(t_stab), 1);
	new->key = key;
	new->val = val;
	new->next = NULL;
	if (stab_lvl->stab[hash] == NULL)
	{
		stab_lvl->stab[hash] = new;
	}
	else
	{
		tmp = stab_lvl->stab[hash];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	stab_lvl->used++;
	stab_lvl->load_factor = (float)stab_lvl->used / (float)stab_lvl->size;
	if (stab_lvl->load_factor > 0.7)
		ft_resize_stab(ms, &stab_lvl);
}

void	ft_set_shell(t_ms *ms)
{
	char	*pwd;
	char	*filename;
	char	*shell;

	pwd = ft_lookup_stab(ms->be->global_stabs, "PWD");
	filename = ft_lookup_stab(ms->be->global_stabs, "_");
	if (!pwd || !filename)
	{
		ft_printf_fd(2, "minishell: unable to set $SHELL variable\n");
		return ;
	}
	shell = ft_strjoin(pwd, &filename[1]);
	if (!shell)
		ft_cleanup_exit(ms, 1);
	ft_upd_stab_val(ms->be->global_stabs, "SHELL", shell);
	free(shell);
}

/* function to initialize the environmental variables
functionality:
1. Create a new symbol table stack
2. Find the next prime number
3. Initialize the size of the symbol table
4. Initialize the load factor
5. Initialize the symbol table
6. Traverse the environmental variables and add them to the symbol table
*/
void	ft_init_stab(t_ms *ms)
{
	int		i;
	char	**env;

	i = 0;
	env = ms->be->envp;
	while (env[i])
		i++;
	ms->be->global_stabs = ft_calloc(sizeof(t_stab_st), 1);
	ms->be->global_stabs->size = ft_calc_stab_size(i);
	ms->be->global_stabs->load_factor = 0;
	ms->be->global_stabs->level = 1;
	ms->be->global_stabs->stab = ft_calloc(sizeof(char *),
	ms->be->global_stabs->size);
	i = 0;
	while (env[i])
	{
		ft_add_global_val(ms, env[i]);
		i++;
	}
	ft_set_shell(ms);
}

