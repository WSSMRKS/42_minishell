/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/12 20:16:38 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/// @brief Extract the key and value from an environmental variable string.
///        Functionality:
///        1. Find the position of the '=' character.
///        2. Create the key as a substring up to the '='.
///        3. Create the value as a substring after the '='
///        or handle NULL values appropriately.
/// @param env The environmental variable string in the form "KEY=VALUE".
/// @param key Pointer to store the extracted key.
/// @param val Pointer to store the extracted value.
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

/// @brief Add a new value to the global environmental variables.
///        Functionality:
///        1. Extract the key and value from the input string.
///        2. Validate the key as a valid identifier.
///        3. Check if the key exists; update or add it to the
///        global symbol table.
/// @param ms Pointer to the main structure containing global states.
/// @param env The environmental variable string to be added.
bool	ft_add_global_val(t_ms *ms, char *env)
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
		return (false);
	}
	if (ft_lookup_key(ms->be->global_stabs, key) != NULL)
	{
		ft_upd_stab_val(ms->be->global_stabs, key, val);
		free(key);
	}
	else
		ft_add_to_stab(ms, ms->be->global_stabs, key, val);
	return (true);
}

/// @brief Add a new key-value pair to the symbol table.
///        Functionality:
///        1. Calculate the hash value of the key.
///        2. Create a new entry in the symbol table.
///        3. Add the entry to the table or its linked list.
///        4. Update the load factor and resize if necessary.
/// @param ms Pointer to the main structure.
/// @param stab_lvl The symbol table to which the key-value pair is added.
/// @param key The key string.
/// @param val The value string.
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

/// @brief Set the $SHELL variable using the current PWD and filename.
///        Functionality:
///        1. Retrieve the current PWD and the program's filename.
///        2. Construct the $SHELL variable and update its value.
///        3. Handle errors if the required variables are missing.
/// @param ms Pointer to the main structure containing global states.
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

/// @brief Initialize the global environmental variables symbol table.
///        Functionality:
///        1. Create a new symbol table.
///        2. Calculate the appropriate size (next prime number).
///        3. Initialize symbol table properties and allocate memory.
///        4. Traverse the environmental variables and add them to the table.
///        5. Set the $SHELL variable.
/// @param ms Pointer to the main structure containing global states.
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
	ft_upd_shlvl(ms);
}
