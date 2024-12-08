/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 01:35:46 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:15:13 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdlib.h>

/// Initializes a list.
/// @param destructor The function to call on data when it is removed.
/// For example free() or NULL.
/// @param list The list to initialize.
void	list_init(t_list_destructor_fn destructor, t_list *list)
{
	if (list == NULL)
		return ;
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	list->destructor = destructor;
}

t_list	list_init2(t_list_destructor_fn destructor)
{
	t_list	list;

	list_init(destructor, &list);
	return (list);
}

/// Clears a list and calls its destructor on each item.
/// @param list The list to destroy.
void	list_clear(t_list *list)
{
	t_node	*current;
	t_node	*next;

	if (list == NULL)
		return ;
	current = list->head;
	while (current != NULL)
	{
		next = current->next;
		if (list->destructor && current->data)
			list->destructor(current->data);
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
}

/// Creates a list on the heap.
/// @param destructor The function to call on data when it is removed.
/// For example free() or NULL.
/// @param list The list to create.
/// @return true if the list was created, false otherwise.
bool	list_create(t_list_destructor_fn destructor, t_list **list)
{
	if (list == NULL)
		return (false);
	*list = malloc(sizeof(t_list));
	if (*list == NULL)
		return (false);
	list_init(destructor, *list);
	return (true);
}

/// Frees a list and calls its destructor on each item.
/// @param list The list to destroy.
/// @note The list pointer is set to NULL.
void	list_free(t_list **list)
{
	if (list == NULL || *list == NULL)
		return ;
	list_clear(*list);
	free(*list);
	*list = NULL;
}
