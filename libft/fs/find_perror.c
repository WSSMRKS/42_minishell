/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_perror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:22:37 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fs.h"
#include <errno.h>
#include <stdio.h>

/// @brief Searches for a file in the given directories and
/// the current working directory.
/// @param path The file to search for.
/// @param dirs The directories to search in (vec of string slices).
/// @param mode The mode to check the file access with.
/// @param out The resulting full path to the file.
/// @return True if the file was found and the access was successful,
/// false otherwise.
/// @note Different from `find_file` in that `out` will only
/// be set when returning true.
bool	find_file_perror(t_str_slice path, const t_vec *dirs, int32_t mode,
		t_str *out)
{
	if (!find_file(path, dirs, mode, out))
	{
		if (errno == EACCES)
		{
			perror(cstr_ref(out));
			str_destroy(out);
		}
		else
		{
			ft_putstrsl_fd(path, 2);
			ft_putstr_fd(": ", 2);
			perror(0);
		}
		return (false);
	}
	return (true);
}

/// @brief Searches for a file in the PATH directories and
/// the current working directory.
/// @param path The file to search for.
/// @param envp The environment variables.
/// @param mode The mode to check the file access with.
/// @param out The resulting full path to the file.
/// @return True if the file was found and the access was successful,
/// false otherwise.
/// @note Different from `find_file` in that `out` will only
/// be set when returning true.
bool	find_file_on_path_perror(t_str_slice path, char *const *envp,
		int32_t mode, t_str *out)
{
	if (!find_file_on_path(path, envp, mode, out))
	{
		if (errno == EACCES)
		{
			perror(cstr_ref(out));
			str_destroy(out);
		}
		else
		{
			ft_putstrsl_fd(path, 2);
			ft_putstr_fd(": ", 2);
			perror(0);
		}
		return (false);
	}
	return (true);
}
