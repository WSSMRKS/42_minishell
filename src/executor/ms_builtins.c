/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:16:12 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/11 16:21:42 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
// #include "../array/ft_array.h"

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
		ft_printf_fd(2, "pwd: doesn't support arguments\n");
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

static int		ft_add_vars(t_ms *ms, t_cmd_list *curr)
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

void		ft_extract_keys(t_ms *ms, int lvl, char **sorted_array)
{
	t_symtab_stack		*tmp;
	t_symtab			*tmp2;
	int					i;
	int					j;

	j = 0;
	tmp = ms->be->global_symtabs;
	while (tmp)
	{
		if (tmp->level == lvl)
		{
			i = 0;
			while (i < tmp->size)
			{
				tmp2 = tmp->symtab[i];
				while (tmp2 != NULL)
				{
					sorted_array[j++] = tmp2->key;
					tmp2 = tmp2->next;
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}
int ft_strcmp_handler(const void *ptr1, const void *ptr2)
{
	char **str1 = (char **) ptr1;
	char **str2 = (char **) ptr2;
	return (ft_strcmp(*str1, *str2));
}

/*
Functionality:
- extract all the values in the hash table to an array. (without mallocing the keys&values)
- sort the array
- call ft_lookup value to print one after the other.
*/
void	ft_print_alpha(t_ms *ms)
{
	char	**sorted_array;
	int		i;

	i = 0;
	sorted_array = ft_calloc(sizeof(char*), ms->be->global_symtabs->used + 1);
	ft_extract_keys(ms, 1, sorted_array);
	arr_qsort(sorted_array, ms->be->global_symtabs->used, sizeof(char*), ft_strcmp_handler);
	while(sorted_array[i])
	{
		if (ft_lookup_symtab(ms->be->global_symtabs, sorted_array[i]) == NULL)
			printf("declare -x %s\n", sorted_array[i]);
		else
			printf("declare -x %s=\"%s\"\n", sorted_array[i], ft_lookup_symtab(ms->be->global_symtabs, sorted_array[i]));
		i++;
	}
	free(sorted_array);
}



int		ft_export(t_ms *ms, t_cmd_list *curr)
{
	(void) curr;

	if (curr->cmd->words->next != NULL)
		ft_add_vars(ms, curr);
	else
		ft_print_alpha(ms);
	return (0);
}
