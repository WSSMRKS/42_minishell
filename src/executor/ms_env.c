/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/19 16:38:30 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* Environmental variables implementation steps:
- Create a new struct that holds the environmental variables
- Create a new function that initializes the environmental variables given by the system
- Create a function that initializes the hash table for the environmental variables
- Create a function that initializes the hash table for the local variables
- Create a new function that frees the environmental variables
- Create a new function that prints the environmental variables
- Create a new function that adds a new environmental variable
- Create a new function that deletes/unsets an environmental variable
- Create a new function that searches for an environmental variable
- Create a new function that updates an environmental variable
- Create a new function that exports the environmental variables

Advantage of a hash table over a regular array or linkedlist.

finding a particular value in an array:
traverse through the array and strncmp the value with the string in the array. time complexity O(n)
finding a particular value in a linked list:
traverse through the array and strncmp the value with the string in the array. time complexity O(n)
finding a particular value in a hash table:
get the hash value multiplying the string with the hash function. hash value % table size (should be prime) = position in the array.
time complexity O(1)

*/
