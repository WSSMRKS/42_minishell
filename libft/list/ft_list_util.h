/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_util.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:40:09 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:12:08 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_UTIL_H
# define FT_LIST_UTIL_H

# include "ft_list.h"

t_node	*create_node(const void *data);
void	update_skip_pointers_after_add(t_list *list, t_node *new_node,
			size_t index);
void	update_skip_pointers_before_remove(t_list *list, t_node *node,
			size_t index);

#endif
