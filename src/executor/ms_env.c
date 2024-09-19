/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:41:22 by maweiss           #+#    #+#             */
/*   Updated: 2024/09/19 16:14:15 by maweiss          ###   ########.fr       */
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
*/
