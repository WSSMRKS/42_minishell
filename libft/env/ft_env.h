/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:57:41 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/18 17:14:15 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H
# pragma once

# include "../libft.h"

bool		get_env_path_dirs(char *const *envp, t_vec *out);
bool		split_env_path(t_str_slice path_value, t_vec *out);
t_str_slice	get_var(char *const *envp, t_str_slice var);
t_str_slice	get_value(t_str_slice env_var);

char		*ft_hostname(void);

#endif
