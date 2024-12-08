/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:56:16 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fs.h"
#include <errno.h>

/// @brief Creates a vec of t_str containing the given file once and
/// the given dirs joined with the file.
/// @param path The file to join with the dirs.
/// @param dirs The directories to join with the file (vec of string slices).
/// @param out_joined_dirs The resulting vec of t_str.
/// @return True if the operation was successful, false otherwise.
static bool	prep_find_file(t_str_slice path, const t_vec *dirs,
		t_vec *out_joined_dirs)
{
	t_str	path_owned;

	if (!dirs_join_file(dirs, path, out_joined_dirs))
		return (false);
	path_owned = str_clone_from(path);
	if (path_owned.mem_err)
	{
		vec_destroy(out_joined_dirs, iter_str_destroy);
		str_destroy(&path_owned);
		return (false);
	}
	vec_push_front(out_joined_dirs, &path_owned);
	if (out_joined_dirs->mem_err)
	{
		vec_destroy(out_joined_dirs, iter_str_destroy);
		str_destroy(&path_owned);
		return (false);
	}
	return (true);
}

/// @brief Searches for a file in the given directories and
/// the current working directory.
/// @param path The file to search for.
/// @param dirs The directories to search in (vec of string slices).
/// @param mode The mode to check the file access with.
/// @param out The resulting full path to the file.
/// @return True if the file was found and the access was successful,
/// false otherwise.
/// @note If the file was found, but is missing access perms
/// (`errno` = `EACCES`), then `out` will contain the file path
/// but the function will still return false.
bool	find_file(t_str_slice path, const t_vec *dirs, int32_t mode, t_str *out)
{
	t_vec	try_files;
	t_str	*i_file;
	size_t	i;

	*out = str_empty();
	if (!prep_find_file(path, dirs, &try_files))
		return (false);
	i_file = vec_get(&try_files);
	i = 0;
	while (i < try_files.len)
	{
		if (access(cstr_ref(i_file), mode) == 0 || errno == EACCES)
		{
			*out = *i_file;
			*i_file = str_empty();
			break ;
		}
		i++;
		i_file++;
	}
	vec_destroy(&try_files, iter_str_destroy);
	return (out->len > 0 && errno != EACCES);
}

/// @brief Searches for a file in the PATH directories and
/// the current working directory.
/// @param path The file to search for.
/// @param envp The environment variables.
/// @param mode The mode to check the file access with.
/// @param out The resulting full path to the file.
/// @return True if the file was found and the access was successful,
/// false otherwise.
/// @note If the file was found, but is missing access perms
/// (`errno` = `EACCES`), then `out` will contain the file path
/// but the function will still return false.
bool	find_file_on_path(t_str_slice path, char *const *envp, int32_t mode,
		t_str *out)
{
	t_vec	env_path_dirs;
	bool	found;

	*out = str_empty();
	if (!get_env_path_dirs(envp, &env_path_dirs))
		return (false);
	found = find_file(path, &env_path_dirs, mode, out);
	vec_destroy(&env_path_dirs, 0);
	return (found);
}

/// @brief Joins the given directories with the given file.
/// e.g. (["/etc"], "passwd" -> ["/etc/passwd"])
/// @param dirs The directories to join with the file. (vec of string slices)
/// @param file The file to join with the directories.
/// @param out The resulting vec of t_str.
/// @return True if the operation was successful, false otherwise.
bool	dirs_join_file(const t_vec *dirs, t_str_slice file, t_vec *out)
{
	t_str	slash_file;

	slash_file = str_empty_with_capacity(file.len + 2);
	str_pushstr(&slash_file, cstr_slice("/", 1));
	str_pushstr(&slash_file, file);
	if (slash_file.mem_err)
	{
		str_destroy(&slash_file);
		return (false);
	}
	if (!vec_strsls_to_cloned_strs(dirs, out))
	{
		str_destroy(&slash_file);
		return (false);
	}
	if (!vec_strs_append_to_all(out, str_view(&slash_file)))
	{
		vec_destroy(out, iter_str_destroy);
		str_destroy(&slash_file);
		return (false);
	}
	str_destroy(&slash_file);
	return (true);
}
