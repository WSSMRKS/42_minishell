/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:00:27 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:18:41 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

/// @brief Get the directories from the PATH env var.
/// @param envp The env vars.
/// @param out The output t_vec of t_str_slice.
/// @return True if the directories were extracted successfully.
bool	get_env_path_dirs(char *const *envp, t_vec *out)
{
	return (split_env_path(get_value(get_var(envp, cstr_slice("PATH", 4))),
			out));
}

/// @brief Get a specific env var.
/// @param envp The env vars.
/// @param var The name of the env var.
/// @return The env var or a null str_slice.
t_str_slice	get_var(char *const *envp, t_str_slice var)
{
	while (*envp)
	{
		if (ft_memcmp(*envp, var.str, var.len) == 0)
			return (cstr_slice(*envp, ft_strlen(*envp)));
		envp++;
	}
	return (strsl_null());
}

/// @brief Extract the value of the env var (the part after the '=').
/// @param env_var The env var. (e.g. "PATH=/usr/bin:/usr/sbin")
/// @param out The value. (e.g. "/usr/bin:/usr/sbin")
/// @return The value of the env var or a null str_slice.
t_str_slice	get_value(t_str_slice env_var)
{
	const char	*env_var_value;
	ptrdiff_t	ptrdiff;

	env_var_value = strsl_chr(env_var, '=');
	if (!env_var_value)
		return (strsl_null());
	env_var_value++;
	ptrdiff = env_var_value - env_var.str;
	return (cstr_slice(env_var_value, env_var.len - ptrdiff));
}

static void	rm_trailing_slash_iter(void *element)
{
	t_str_slice	*dir;

	dir = element;
	while (strsl_ends_with(*dir, cstr_slice("/", 1)))
		*dir = strsl_trunc(*dir, dir->len - 1);
}

/// @brief Split the PATH env var value into directories.
/// @param path_value The value of the PATH env var.
/// @param out The output t_vec of t_str_slice.
/// @return True if the path was split successfully, false otherwise.
bool	split_env_path(t_str_slice path_value, t_vec *out)
{
	if (path_value.str == 0)
	{
		*out = vec_empty(sizeof(t_str_slice));
		return (false);
	}
	*out = strsl_split(path_value, cstr_slice(":", 1));
	if (out->len == 0 || out->mem_err)
	{
		vec_destroy(out, 0);
		return (false);
	}
	vec_iter(out, rm_trailing_slash_iter);
	return (true);
}
