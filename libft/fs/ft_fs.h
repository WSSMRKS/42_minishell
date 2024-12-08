/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:16:25 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FS_H
# define FT_FS_H
# pragma once

# include "../libft.h"

// bool	path_exists(const char *path);
// bool	file_exists(const char *file);
// bool	dir_exists(const char *dir);

// bool	is_dir(const char *path);
// bool	is_file(const char *path);

// bool	is_readable(const char *path);
// bool	is_writable(const char *path);
// bool	is_executable(const char *path);

bool	find_file(t_str_slice path, const t_vec *dirs, int32_t mode,
			t_str *out);
bool	find_file_perror(t_str_slice path, const t_vec *dirs, int32_t mode,
			t_str *out);
bool	find_file_on_path(t_str_slice path, char *const *envp, int32_t mode,
			t_str *out);
bool	find_file_on_path_perror(t_str_slice path, char *const *envp,
			int32_t mode, t_str *out);
bool	dirs_join_file(const t_vec *dirs, t_str_slice file, t_vec *out);

#endif
