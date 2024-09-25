/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/25 12:34:35 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* Environmental variables implementation steps:
[x] - Create a new struct that holds the environmental variables
[x] - Create a new function that initializes the environmental variables given by the system
[x] - Create a function that initializes the hash table for the environmental variables
[x] - Create a function that initializes the hash table for the local variables
[x] - Create a new function that frees the environmental variables
[x] - Create a new function that prints the environmental variables
[x] - Create a new function that adds a new environmental variable
[x] - Create a new function that deletes/unsets an environmental variable
[x] - Create a new function that searches for an environmental variable
[x] - Create a new function that updates an environmental variable
[x] - Create a new function that creates **envp out of the current state of the environmental variables // [x] not yet including the equal sign!!
[x] - Create a new function that takes a local variable and makes it global
[x] - Create a new function that takes **envp and updates one particular variable



Advantage of a hash table over a regular array or linkedlist.
finding a particular value in an array:
traverse through the array and strncmp the value with the string in the array. time complexity O(n)
finding a particular value in a linked list:
traverse through the array and strncmp the value with the string in the array. time complexity O(n)
finding a particular value in a hash table:
get the hash value multiplying the string with the hash function. hash value % table size (should be prime) = position in the array.
time complexity O(1)
*/

/* hash function: djb2
functionality of the algorithm:
1. Initialize a variable to a prime number, 5381.
2. Iterate over the string and multiply the variable by 33 and add the value of the character.
3. Return the value of the variable modulo the size of the hash table.
*/
unsigned long	ft_hash_function(t_symtab_stack *current_symtab, char *key)
{
	int				i;
	unsigned long	hash;

	i = 0;
	hash = 5381;
	while (key[i])
	{
		hash = ((hash << 5) + hash) + key[i];
		i++;
	}
	return (hash % (unsigned long) current_symtab->size);
}

/* function to resize the symbol table
functionality:
1. Find the next prime number
2. Create a new symbol table
3. Traverse the old symbol table and add the values to the new symbol table
4. Free the old symbol table
5. Set the new symbol table to the old symbol table
*/
void	ft_resize_symtab(t_symtab_stack **symtab_lvl)
{
	int				i;
	t_symtab_stack	*new;
	t_symtab		*tmp;

	i = 0;
	new = ft_calloc(sizeof(t_symtab_stack), 1);
	ft_find_next_prime((*symtab_lvl)->size);
	new->size = (*symtab_lvl)->size;
	new->load_factor = 0;
	new->symtab = ft_calloc(sizeof(char *), new->size);
	while (i < (*symtab_lvl)->size)
	{
		tmp = (*symtab_lvl)->symtab[i];
		while (tmp)
		{
			ft_add_to_symtab(new, tmp->key, tmp->value);
			tmp = tmp->next;
		}
		i++;
	}
	free((*symtab_lvl)->symtab);
	(*symtab_lvl)->symtab = new->symtab;
	free(new);
}

/* function to add a new value to the environmental variables
functionality:
1. Find the position of the equal sign in the string
2. Create a new string with the key
3. Create a new string with the value
4. Check if the load factor is greater than 0.7
5. If the load factor is greater than 0.7, resize the symbol table
6. Increment the used variable
7. Calculate the new load factor
8. Add the value to the symbol table
*/
void	ft_add_global_value(t_ms *ms, char *env)
{
	char	*key;
	char	*value;
	int		i;
	t_symtab_stack	*global;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	value = ft_strdup(&env[i + 1]);
	global = ms->be->global_symtabs;
	if (global->load_factor > 0.7)
		ft_resize_symtab(&global);
	global->used++;
	global->load_factor = (float)global->used / (float)global->size;
	ft_add_to_symtab(global, key, value);
}

/* function to add a new value to the local variables
functionality:
1. Find the position of the equal sign in the string
2. Create a new string with the key
3. Create a new string with the value
4. Check if the load factor is greater than 0.7
5. If the load factor is greater than 0.7, resize the symbol table
6. Increment the used variable
7. Calculate the new load factor
8. Add the value to the symbol table
*/
void	ft_add_local_value(t_ms *ms, char *env)
{
	char	*key;
	char	*value;
	int		i;
	t_symtab_stack	*local;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	value = ft_strdup(&env[i + 1]);
	if (ms->be->global_symtabs->next == NULL)
		ft_add_local_symtab(ms);
	local = ms->be->global_symtabs->next;
	if (local->load_factor > 0.7)
		ft_resize_symtab(&local);
	local->used++;
	local->load_factor = (float)local->used / (float)local->size;
	ft_add_to_symtab(local, key, value);
}

/* function to add a new value to the symbol table
functionality:
1. Calculate the hash value of the key
2. Create a new symbol table entry
3. If the position in the symbol table is empty, add the value
4. If the position in the symbol table is not empty, traverse the linked list and add the value
*/
void	ft_add_to_symtab(t_symtab_stack *symtab_lvl, char *key, char *value)
{
	unsigned long	hash;
	t_symtab		*new;
	t_symtab		*tmp;


	hash = ft_hash_function(symtab_lvl, key);
	new = ft_calloc(sizeof(t_symtab), 1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (symtab_lvl->symtab[hash] == NULL)
	{
		symtab_lvl->symtab[hash] = new;
	}
	else
	{
		tmp = symtab_lvl->symtab[hash];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	symtab_lvl->used++;
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
void	ft_init_symtab(t_ms *ms)
{
	int		i;
	char	**env;

	i = 0;
	env = ms->be->envp;
	while (env[i])
		i++;
	ms->be->global_symtabs = ft_calloc(sizeof(t_symtab_stack), 1);
	ft_find_next_prime(ms->be->global_symtabs->size);
	ms->be->global_symtabs->load_factor = 0;
	ms->be->global_symtabs->symtab = ft_calloc(sizeof(char *), ms->be->global_symtabs->size);
	i = 0;
	while (env[i])
		ft_add_value(ms, env[i++]);
}

/* function to add a value to the symbol table
functionality:
1. Find the position of the equal sign in the string
2. Create a new string with the key
3. Create a new string with the value
4. Add the value to the symbol table
*/
void	ft_add_value(t_ms *ms, char *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	value = ft_strdup(&env[i + 1]);
	ft_add_to_symtab(ms->be->global_symtabs, key, value);
}

/* function to add the local symtab
functionality:
1. Add the local symbol table to the global symbol table
*/
void	ft_add_local_symtab(t_ms *ms)
{
	t_symtab_stack	*local;

	local = ft_calloc(sizeof(t_symtab_stack), 1);
	ms->be->global_symtabs->next = local;
	local->symtab = ft_calloc(sizeof(char *), ms->be->global_symtabs->size);
	local->size = ms->be->global_symtabs->size;
	local->used = 0;
	local->load_factor = 0;
	local->level = ms->be->global_symtabs->level + 1;
}

/* function to lookup a value in the symbol table
functionality:
1. Calculate the hash value of the key
2. If the position in the symbol table is empty, return NULL
3. If the position in the symbol table is not empty, traverse the linked list and return the value
*/
char	*ft_lookup_symtab(t_symtab_stack *symtab_lvl, char *key)
{
	unsigned long	hash;
	t_symtab		*tmp;

	hash = ft_hash_function(symtab_lvl, key);
	if (symtab_lvl->symtab[hash] == NULL)
		return (NULL);
	tmp = symtab_lvl->symtab[hash];
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/* function to create **envp out of the current state of the environmental variables
functionality:
1. Traverse the global symbol table and count the number of variables
2. Create a new **envp with the size of the number of variables + 1
3. Traverse the global symbol table and add the variables to the **envp
4. Return the **envp
*/
char	**ft_create_envp(t_ms *ms)
{
	int				i;
	int				j;
	char			**envp;
	t_symtab_stack	*global;
	t_symtab		*tmp;

	i = 0;
	j = 0;
	global = ms->be->global_symtabs;
	envp = ft_calloc(sizeof(char *), global->used + 1);
	global = ms->be->global_symtabs;
	while (global)
	{
		i = 0;
		while (i < global->size)
		{
			tmp = global->symtab[i];
			while (tmp)
			{
				envp[j++] = ft_multistrjoin(3, tmp->key, "=", tmp->value);
				tmp = tmp->next;
			}
			i++;
		}
		global = global->next;
	}
	return (envp);
}

/* function that makes a local variable global
functionality:
1. search the variable in the local symtab
2. if variable is found remove the value and add it to the global symtab.
3. if the variable is not found return -1
*/
int	ft_make_global(t_ms *ms, char *key)
{
	char			*value;
	t_symtab_stack	*local;
	t_symtab_stack	*global;

	local = ms->be->global_symtabs->next;
	global = ms->be->global_symtabs;
	value = ft_lookup_symtab(local, key);
	if (value == NULL)
		return (-1);
	ft_add_to_symtab(global, key, value);
	ft_remove_from_symtab(local, key);
	return (0);
}

/* function to alter one particular value when executing a command
functionality:
1. take actual **envp
2. find the stated value
3. If value is there update
4. If value is not there add
*/
char	**ft_update_envp_runtime(char **envp, char *key, char *value)
{
	int		i;
	char	*tmp;
	char	**tmp2;

	i = -1;
	if (!envp)
		return (NULL);
	tmp = ft_multistrjoin(3, key, "=", value);
	if (!tmp)
		return (NULL);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], tmp, ft_strlen(key) + 1))
		{
			free(envp[i]);
			envp[i] = tmp;
			return (envp);
		}
	}
	tmp2 = ft_calloc(sizeof(char *), i + 2);
	i = -1;
	while (envp[++i])
		tmp2[i] = envp[i];
	tmp2[i] = tmp;
	free(envp);
	return (tmp2);
}

/* function that removes a variable from the symtab
functionality:
1. Calculate the hash value of the key
2. If the position in the symbol table is empty, return 1
3. If the position in the symbol table is not empty, traverse the linked list and remove the value
4. Return 0
*/
int	ft_remove_from_symtab(t_symtab_stack *symtab_lvl, char *key)
{
	unsigned long	hash;
	t_symtab		*tmp;
	t_symtab		*prev;

	hash = ft_hash_function(symtab_lvl, key);
	if (symtab_lvl->symtab[hash] == NULL)
		return (1);
	tmp = symtab_lvl->symtab[hash];
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			if (prev)
				prev->next = tmp->next;
			else
				symtab_lvl->symtab[hash] = tmp->next;
			free(tmp->key);
			tmp->key = NULL;
			free(tmp->value);
			tmp->value = NULL;
			free(tmp);
			tmp = NULL;
			symtab_lvl->used--;
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

/* function that updates a value in the symtab
functionality:
1. Calculate the hash value of the key
2. If the position in the symbol table is empty, return 1
3. If the position in the symbol table is not empty, traverse the linked list and update the value
4. Return 0
*/
int	ft_update_symtab(t_symtab_stack *symtab_lvl, char *key, char *value)
{
	unsigned long	hash;
	t_symtab		*tmp;

	hash = ft_hash_function(symtab_lvl, key);
	if (symtab_lvl->symtab[hash] == NULL)
		return (1);
	tmp = symtab_lvl->symtab[hash];
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

/* function to print the contents of either the local or the global symbol table
functionality:
1. Traverse the selected symbol table and print the key and value
*/
void	ft_print_symtab(t_ms *ms, int lvl)
{
	t_symtab_stack	*tmp;
	t_symtab			*tmp2;
	int					i;

	tmp = ms->be->global_symtabs;
	while (tmp)
	{
		if (tmp->level == lvl)
		{
			i = 0;
			while (i < tmp->size)
			{
				tmp2 = tmp->symtab[i];
				while (tmp2)
				{
					printf("key: %s, value: %s\n", tmp2->key, tmp2->value);
					tmp2 = tmp2->next;
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}

/* function to free the whole symtab_stack
functionality:
1. Traverse the symbol table stack and free the symbol table
2. Free the symbol table stack
*/
void	ft_free_symtab_stack(t_symtab_stack *symtab_stack)
{
	t_symtab_stack		*tmp;
	t_symtab			*tmp2;
	t_symtab			*tmp3;
	int					i;

	while (symtab_stack)
	{
		i = 0;
		while (i < symtab_stack->size)
		{
			tmp2 = symtab_stack->symtab[i];
			while (tmp2)
			{
				tmp3 = tmp2;
				free(tmp2->key);
				tmp2->key = NULL;
				free(tmp2->value);
				tmp2->value = NULL;
				tmp2 = tmp2->next;
				free(tmp3);
				tmp3 = NULL;
			}
			i++;
		}
		free(symtab_stack->symtab);
		tmp = symtab_stack;
		symtab_stack = symtab_stack->next;
		free(tmp);
		tmp = NULL;
	}
}

/* function to find the next prime number
functionality:
1. If the size is greater than 1, double the size
2. If the size is less than or equal to 1, set the size to 2
3. Traverse the numbers and check if the number is prime
4. Return the prime number
*/
int	ft_find_next_prime(int size)
{
	int	i;

	if (size > 1)
		i = size * 2;
	else
		i = 2;
	while (!ft_is_prime(i))
	{
		i++;
	}

	return (i);
}

/* function to check if a number is prime
functionality:
1. If the number is less than or equal to 1, return 0
2. If the number is 2 or 3, return 1
3. If the number is divisible by 2 or 3, return 0
4. Traverse the numbers and check if the number is divisible by the number or the number + 2
5. Return 1 if the number is prime
*/
int	ft_is_prime(int n)
{
	int	i;

	if (n <= 1)
		return (0);
	if (n == 2 || n == 3)
		return (1);
	if (n % 2 == 0 || n % 3 == 0)
		return (0);
	i = 5;
	while (i * i <= n)
	{
		if (n % i == 0 || n % (i + 2) == 0)
			return (0);
		i += 6;
	}
	return (1);
}
