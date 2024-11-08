/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:16:12 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/08 18:44:49 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		ft_echo(t_ms *ms, t_cmd_list *curr)
{
	bool			newline;
	t_list_words	*words;
	int				i;

	i = 0;
	newline = true;
	if (ft_strncmp(curr->cmd->words->next->word, "-n\0", 3) == 0)
	{
		newline = false;
		words = curr->cmd->words->next->next;
	}
	else
		words = curr->cmd->words->next;
	while(words)
	{
		if (i != 0)
			printf(" ");
		if(words->flags == WORD_DOLLAR)
			printf("%s", ft_lookup_symtab(ms->be->global_symtabs, words->word));
		else
			printf("%s", words->word);
		words = words->next;
		i++;
	}
	if (newline == true)
		printf("\n");
	return (0);
}

int		ft_pwd(t_ms *ms, t_cmd_list *curr)
{
	if (curr->cmd->words->next != NULL)
	{
		ft_printf_err("pwd: doesn't support arguments\n");
		return (1);
	}
	ms->be->cwd = getcwd(ms->be->cwd, PATH_MAX);
	//kann ich das wenn NULL returned wird noch freeen?
	printf("%s\n", ms->be->cwd);
	ft_memset(ms->be->cwd, '\0', PATH_MAX);
	return (0);
}

int		ft_cd(t_ms *ms, t_cmd_list *curr)
{
	if (chdir(curr->cmd->words->next->word) != 0)

	ms->be->cwd = getcwd(ms->be->cwd, PATH_MAX);
	ft_update_symtab_value(ms->be->global_symtabs, "PWD", ms->be->cwd);
	ft_memset(ms->be->cwd, '\0', PATH_MAX);
	return (0);
}

int		ft_unset(t_ms *ms, t_cmd_list *curr)
{
	ft_remove_from_symtab(ms->be->global_symtabs, curr->cmd->words->word);
	return (0);
}

int		ft_add_vars(t_ms *ms, t_cmd_list *curr)
{
	t_list_words *words;

	words = curr->cmd->words->next;

	while(words)
	{
		ft_add_global_value(ms, words->word);
		words = words->next;
	}
	return (0);
}

int		ft_export(t_ms *ms, t_cmd_list *curr)
{
	(void) curr;

	if (curr->cmd->words->next != NULL)
		ft_add_vars(ms, curr);
	// else
	// 	ft_print_vars();

	ft_print_symtab(ms, 1);
	return (0);
}
