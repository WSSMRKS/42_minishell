/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_garbage.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:51:33 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/12 12:00:25 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_GARBAGE_H
# define MS_GARBAGE_H

typedef struct s_list_hdfiles
{
	char					*filename;
	struct s_list_hdfiles	*next;
}				t_list_hdfiles;

typedef struct s_garbage
{
	int					nb_heredocs;
	t_list_hdfiles		*heredoc;
}				t_garbage;

#endif
