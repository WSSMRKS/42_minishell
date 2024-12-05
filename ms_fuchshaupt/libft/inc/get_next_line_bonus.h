/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:34:34 by zblume            #+#    #+#             */
/*   Updated: 2024/06/21 15:52:01 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char		*get_next_line(int fd);
size_t		gnl_strlen(char *s);
char		*ft_gnl_strjoin(char *left_str, char *buff);
char		*ft_gnl_strchr(char *s, int c);
void		clean_pointer(char **ptr);

#endif
