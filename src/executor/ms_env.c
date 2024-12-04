/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 15:44:28 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
Advantage of a hash table over a regular array or linkedlist.
finding a particular val in an array:
traverse through the array and strncmp the val with the string in the array.
time complexity O(n)
finding a particular val in a linked list:
traverse through the array and strncmp the val with the string in the array.
time complexity O(n)
finding a particular val in a hash table:
get the hash val multiplying the string with the hash function.
hash val % table size (should be prime) = position in the array.
time complexity O(1)
*/

/// @brief Hash function using the djb2 algorithm.
///        Functionality of the algorithm:
///        1. Initialize a variable to a prime number, 5381.
///        2. Iterate over the string, multiply the variable by 33,
///        and add the value of the character.
///        3. Return the value of the variable modulo the size of the hash table
/// @param current_stab Pointer to the current hash table structure
/// @param key The string key to be hashed.
/// @return The computed hash value as an unsigned long, modulo size of the hash
unsigned long	ft_hash_function(t_stab_st *current_stab, char *key)
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
	return (hash % (unsigned long) current_stab->size);
}

/// @brief Calculate the next prime number greater than or equal
///        to the given size multiplied by two.
///        Functionality:
///        1. If the size is greater than 1, double the size.
///        2. If the size is less than or equal to 1, set the size to 2.
///        3. Traverse numbers and check if each is prime.
///        4. Return the first prime number found.
/// @param size The initial size for the calculation.
/// @return The next prime number greater than or equal to the calculated size.
int	ft_calc_stab_size(int size)
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

/// @brief Check if a number is prime.
///        Functionality:
///        1. If the number is less than or equal to 1, return 0.
///        2. If the number is 2 or 3, return 1 (prime).
///        3. If the number is divisible by 2 or 3, return 0 (not prime).
///        4. Traverse numbers and check divisibility up to the square root
///        of the number.
///        5. Return 1 if the number is prime, otherwise return 0.
/// @param n The number to check.
/// @return 1 if the number is prime, 0 otherwise.
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

/// @brief Resize the symbol table by finding the next prime size
///        and rehashing all entries.
///        Functionality:
///        1. Find the next prime number for the new hash table size.
///        2. Create a new symbol table with the updated size.
///        3. Traverse the old symbol table and re-add all key-value pairs
///        to the new table.
///        4. Free the memory for the old symbol table.
///        5. Replace the old symbol table with the new one.
/// @param ms Pointer to the main structure containing global states.
/// @param stab_lvl Pointer to the pointer of the current symbol table
void	ft_resize_stab(t_ms *ms, t_stab_st **stab_lvl)
{
	int				i;
	t_stab_st		*new;
	t_stab			*tmp;

	i = 0;
	new = ft_calloc(sizeof(t_stab_st), 1);
	new->size = ft_calc_stab_size((*stab_lvl)->size);
	new->stab = ft_calloc(sizeof(char *), (new->size + 1));
	new->used = 0;
	new->level = 1;
	while (i < (*stab_lvl)->size)
	{
		tmp = (*stab_lvl)->stab[i];
		while (tmp)
		{
			ft_add_to_stab(ms, new, tmp->key, tmp->val);
			tmp = tmp->next;
		}
		i++;
	}
	new->load_factor = new->used / new->size;
	free((*stab_lvl)->stab);
	ms->be->global_stabs = new;
}

/// @brief Validate if a variable name is a valid identifier.
///        Functionality:
///        1. Check if the key is empty or starts with an invalid character.
///        2. Iterate through the string to ensure all characters are valid:
///           - Letters (a-z, A-Z), digits (0-9) except at the first position,
///             or underscores (_).
///        3. If invalid, print an error message
///        indicating the invalid character or key.
///        4. Return a pointer to the invalid character or NULL if valid.
/// @param key The variable name to validate.
/// @return A pointer to the first inv. character in the key, or NULL if valid.
char	*ft_validate_var(char *key)
{
	int	i;

	i = 0;
	if (key[i] == '\0')
	{
		ft_printf_fd(2, "export: `%c\': not a valid identifier\n", key[i]);
		return (&key[i]);
	}
	while (key && key[i])
	{
		if ((key[i] >= '0' && key[i] <= '9' && i != 0)
			|| (key[i] >= 'a' && key[i] <= 'z')
			|| (key[i] >= 'A' && key[i] <= 'Z') || key[i] == '_')
			i++;
		else
		{
			if ((key[i] >= '0' && key[i] <= '9'))
				ft_printf_fd(2, "export: `%s\': not a valid identifier\n", key);
			else
				ft_printf_fd(2, "export: `%c\': not a valid identifier\n",
					key[i]);
			return (&key[i]);
		}
	}
	return (NULL);
}
