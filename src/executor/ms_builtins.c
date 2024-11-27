/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:16:12 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/27 14:52:20 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		ft_echo(t_ms *ms, t_cmd_list *curr)
{
	bool			newline;
	t_list_words	*words;
	int				i;

	(void) ms;
	i = 0;
	newline = true;
	words = curr->cmd->words->next;
	if (words && ft_strncmp(curr->cmd->words->next->word, "-n\0", 3) == 0)
	{
		newline = false;
		words = words->next;
	}
	while(words)
	{
		if (i++ != 0)
			printf(" ");
		printf("%s", words->word);
		words = words->next;
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
	int	ret;
	
	if (!curr->cmd->words->next)
		ret = chdir(ft_lookup_stab(ms->be->global_stabs, "HOME"));
	else
		ret = chdir(curr->cmd->words->next->word);
	if (ret != 0)
	{
		if(!curr->cmd->words->next)
			ft_printf_fd(2, "ms: cd: %s: %s\n", ft_lookup_stab(ms->be->global_stabs, "HOME"), strerror(errno));
		else
			ft_printf_fd(2, "ms: cd: %s: %s\n", curr->cmd->words->next->word, strerror(errno));
		return (ret);
	}
	ms->be->cwd = getcwd(ms->be->cwd, PATH_MAX);
	ft_upd_stab_val(ms->be->global_stabs, "PWD", ms->be->cwd);
	ft_memset(ms->be->cwd, '\0', PATH_MAX);
	return (0);
}

/*all cases where unset returns a return val other then 0 are not part of the minishell scope.*/
int		ft_unset(t_ms *ms, t_cmd_list *curr)
{
	t_list_words	*words;
	words = curr->cmd->words;
	while (words)
	{
		ft_rem_fr_stab(ms->be->global_stabs, words->word);
		words = words->next;
	}
	return (0);
}

static int		ft_add_vars(t_ms *ms, t_cmd_list *curr)
{
	t_list_words *words;

	words = curr->cmd->words->next;

	while(words)
	{
		ft_add_global_val(ms, words->word);
		words = words->next;
	}
	return (0);
}

static void		ft_extract_keys(t_ms *ms, int lvl, char **sorted_array)
{
	t_stab_st		*tmp;
	t_stab			*tmp2;
	int					i;
	int					j;

	j = 0;
	tmp = ms->be->global_stabs;
	while (tmp)
	{
		if (tmp->level == lvl)
		{
			i = 0;
			while (i < tmp->size)
			{
				tmp2 = tmp->stab[i];
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
static int ft_strcmp_handler(const void *ptr1, const void *ptr2)
{
	char **str1 = (char **) ptr1;
	char **str2 = (char **) ptr2;
	return (ft_strcmp(*str1, *str2));
}

/*
Functionality:
- extract all the vals in the hash table to an array. (without mallocing the keys&vals)
- sort the array
- call ft_lookup val to print one after the other.
*/
static void	ft_print_alpha(t_ms *ms)
{
	char	**sorted_array;
	int		i;

	i = 0;
	sorted_array = ft_calloc(sizeof(char*), ms->be->global_stabs->used + 1);
	ft_extract_keys(ms, 1, sorted_array);
	arr_qsort(sorted_array, ms->be->global_stabs->used, sizeof(char*), ft_strcmp_handler);
	while(sorted_array[i])
	{
		if (ft_lookup_stab(ms->be->global_stabs, sorted_array[i]) == NULL)
			printf("declare -x %s\n", sorted_array[i]);
		else
			printf("declare -x %s=\"%s\"\n", sorted_array[i], ft_lookup_stab(ms->be->global_stabs, sorted_array[i]));
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

/* env is not printing empty variables!!*/
int		ft_env(t_ms *ms, t_cmd_list *curr)
{
	t_stab_st	*global_stab;
	int				i;
	int				printed;
	t_stab		*entry;

	if (curr->cmd->words->next != NULL)
	{
		ft_printf_fd(2, "env: doesn't support arguments\n");
		return (1);
	}
	i = 0;
	printed = 0;
	global_stab = ms->be->global_stabs;
	while(printed < global_stab->used)
	{
		if (global_stab->stab[i] != NULL)
		{
			entry = global_stab->stab[i];
			while(entry)
			{
				if(entry->val != NULL)
					printf("%s=%s\n", entry->key, entry->val);
				printed++;
				entry = entry->next;
			}
		}
		i++;
	}
	return (0);
}

int		ft_status(t_ms *ms, t_cmd_list *curr)
{
	char	*print;

	(void) curr;
	print = ft_itoa(ms->be->last_ret);
	printf("%s\n", ft_itoa(ms->be->last_ret));
	free(print);
	return (0);
}

int		ft_resize(t_ms *ms, t_cmd_list *curr)
{
	(void) curr;
	ft_resize_stab(ms, &ms->be->global_stabs);
	return (0);
}

int	ft_exit(t_ms *ms, t_cmd_list *curr)
{
	int		i;
	char	*input;
	int		ex;

	ex = 0;
	i = 0;
	if (curr->cmd->words->next != NULL)
	{
		input = curr->cmd->words->next->word;
		while (input && input[i])
		{
			if ((i == 0 && input[i] == '-') || (input[i] >= '0' && input[i] <= '9'))
				i++;
			else
			{
				ft_printf_fd(2, "exit: %s: not a valid argument\n", input);
				return (EIO);
			}
		}
		if (i < 10)
			ex = ft_atoi(input);
	}
	ft_clear_ast(ms); // [ ] take care of this in case of not a child!!
	ft_clear_be(ms); // [ ] take care of this in case of not a child!!
	ft_cleanup_exit(ms, ex);
	return (0);
}
