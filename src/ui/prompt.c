/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 04:26:23 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/12 04:26:24 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	is_dot(const char *c)
{
	return (*c == '.');
}

static t_str	get_trunc_hostname(void)
{
	t_str	hostname;
	size_t	hostname_colon;

	hostname = str_from2(ft_hostname());
	str_trim(&hostname);
	if (str_find(&hostname, is_dot, &hostname_colon))
		str_remove_range(&hostname, hostname_colon, hostname.len);
	return (hostname);
}

static void	add_user_hostname(t_ms *ms, t_str *prompt_out, t_str *user_home_out)
{
	t_str_slice	user;
	t_str		hostname;

	str_pushstr(prompt_out, cstr_view(GREEN));
	user = cstr_view(ft_lookup_stab(ms->be->global_stabs, "USER"));
	if (user.len == 0)
		user = cstr_slice("?", 1);
	*user_home_out = str_clone_from(cstr_slice("/home/", 6));
	str_pushstr(user_home_out, user);
	str_pushstr(prompt_out, user);
	str_pushstr(prompt_out, cstr_slice("@", 1));
	hostname = get_trunc_hostname();
	if (hostname.len == 0)
		str_push(&hostname, '?');
	str_pushstr(prompt_out, str_view(&hostname));
	str_destroy(&hostname);
	str_pushstr(prompt_out, cstr_view(RESET));
	str_push(prompt_out, ':');
}

/// @brief Get the prompt string for the REPL
/// @param ms The minishell struct
/// @return The prompt string "ms/$USER@<hostname>:$PWD$ "
char	*get_prompt(t_ms *ms)
{
	t_str		out;
	t_str		user_home;
	t_str		pwd;

	out = str_clone_from(cstr_slice("ms/", 3));
	add_user_hostname(ms, &out, &user_home);
	str_pushstr(&out, cstr_view(GREEN));
	pwd = str_clone_from(cstr_view(
				ft_lookup_stab(ms->be->global_stabs, "PWD")));
	if (pwd.len == 0)
		str_push(&out, '?');
	if (str_starts_with(&pwd, &user_home))
	{
		str_remove_range(&pwd, 0, user_home.len);
		str_push_front(&pwd, '~');
	}
	str_destroy(&user_home);
	str_pushstr(&out, str_view(&pwd));
	str_destroy(&pwd);
	str_pushstr(&out, cstr_view(RESET));
	str_pushstr(&out, cstr_slice("$ ", 2));
	return (cstr_take(&out));
}
