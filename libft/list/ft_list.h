/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 23:43:29 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:11:51 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include "../libft.h"

/*
	LIST
*/

/* Creation and destruction */
void	list_init(t_list_destructor_fn destructor, t_list *list);
t_list	list_init2(t_list_destructor_fn destructor);
void	list_clear(t_list *list);
/* Creation and destruction of heap allocated lists */
bool	list_create(t_list_destructor_fn destructor, t_list **list);
void	list_free(t_list **list);

/* Add (nullable) data and deconstruct data on failure */
bool	list_push0_back(t_list *list, void *data);
bool	list_push0_front(t_list *list, void *data);
bool	list_insert0_at(t_list *list, size_t index, void *data);
/* Add data and deconstruct data on failure */
bool	list_push_back(t_list *list, void *data);
bool	list_push_front(t_list *list, void *data);
bool	list_insert_at(t_list *list, size_t index, void *data);
/* Add (nullable) data and dont deconstruct data on failure */
bool	list_push0_back_ref(t_list *list, const void *data);
bool	list_push0_front_ref(t_list *list, const void *data);
bool	list_insert0_at_ref(t_list *list, size_t index, const void *data);
/* Add data and dont deconstruct data on failure */
bool	list_push_back_ref(t_list *list, const void *data);
bool	list_push_front_ref(t_list *list, const void *data);
bool	list_insert_at_ref(t_list *list, size_t index, const void *data);

/* Extract data and store at given location */
bool	list_pop_back(t_list *list, void **out);
bool	list_pop_front(t_list *list, void **out);
bool	list_pop_at(t_list *list, size_t index, void **out);
/* Extract data and return */
void	*list_pop2_back(t_list *list);
void	*list_pop2_front(t_list *list);
void	*list_pop2_at(t_list *list, size_t index);

/* Delete data */
bool	list_remove_head(t_list *list);
bool	list_remove_tail(t_list *list);
bool	list_remove_at(t_list *list, size_t index);
bool	list_remove_range(t_list *list, size_t start, size_t end);

/* Get data at specific positions and store at given location */
bool	list_get_front(const t_list *list, void **out);
bool	list_get_back(const t_list *list, void **out);
bool	list_get_at(const t_list *list, size_t index, void **out);
/* Get data at specific positions and return */
void	*list_get2_front(const t_list *list);
void	*list_get2_back(const t_list *list);
void	*list_get2_at(const t_list *list, size_t index);

/* Get nodes at specific positions and store at given location */
bool	list_get_head(const t_list *list, t_node **out);
bool	list_get_tail(const t_list *list, t_node **out);
bool	list_get_node_at(const t_list *list, size_t index, t_node **out);
/* Get nodes at specific positions and return */
t_node	*list_get2_head(const t_list *list);
t_node	*list_get2_tail(const t_list *list);
t_node	*list_get2_node_at(const t_list *list, size_t index);

/* Find and store at given location */
bool	list_find(const t_list *list, const void *key,
			t_list_find_fn cmp, void **out);
bool	list_find_node(const t_list *list, const void *key,
			t_list_find_fn cmp, t_node **out);
bool	list_find_index(const t_list *list, const void *key,
			t_list_find_fn cmp, size_t *out);

/* Find and return */
void	*list_find2(const t_list *list, const void *key,
			t_list_find_fn cmp);
t_node	*list_find2_node(const t_list *list, const void *key,
			t_list_find_fn cmp);
size_t	list_find2_index(const t_list *list, const void *key,
			t_list_find_fn cmp);

/*
	LIST ITERATOR
*/

/* Iterator initialization */
void	list_iter_init(t_list *list);
void	list_iter_init_reverse(t_list *list);
void	list_iter_init_custom(t_list *list, t_list_iter *iter);

/* Basic iterator operations */
bool	list_iter_next(t_list_iter *iter);
bool	list_iter_prev(t_list_iter *iter);
bool	list_iter_advance(t_list_iter *iter, size_t n, bool rev);
bool	list_iter_end(t_list_iter *iter);
bool	list_iter_start(t_list_iter *iter);
/* Basic iterator operations with fuse */
bool	list_iter_next_fused(t_list_iter *iter);
bool	list_iter_prev_fused(t_list_iter *iter);
bool	list_iter_advance_fused(t_list_iter *iter, size_t n, bool rev);

/* Iterator peek and store node at given location */
bool	list_iter_peek_next(t_list_iter *iter, t_node **out);
bool	list_iter_peek_prev(t_list_iter *iter, t_node **out);
bool	list_iter_peek(t_list_iter *iter, size_t n, bool rev, t_node **out);
/* Iterator peek and return */
t_node	*list_iter_peek2_next(t_list_iter *iter);
t_node	*list_iter_peek2_prev(t_list_iter *iter);
t_node	*list_iter_peek2(t_list_iter *iter, size_t n, bool rev);

#endif
