/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:21:56 by maweiss           #+#    #+#             */
/*   Updated: 2024/06/12 11:35:34 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **tofree)
{
	int	i;

	if (!tofree)
		return ;
	i = 0;
	while (tofree[i])
	{
		free((void *)tofree[i]);
		i++;
	}
	free((void *)tofree);
	return ;
}

static size_t	ft_str_len_count(char *str, char del, int mode)
{
	size_t	a;
	size_t	i;

	if (mode == 1)
	{
		i = 0;
		str++;
		while (*str)
		{
			if (*str == del && *(str - 1) != del)
				i++;
			str++;
		}
		if (*str == '\0' && *(str - 1) != del)
			i++;
		return (i);
	}
	a = 0;
	while (*str != del && *str != '\0')
	{
		a++;
		str++;
	}
	return (a);
}

static char	*ft_strdup_split(char *arr, char *s, char c, int *k)
{
	int		i;
	int		len;

	len = ft_str_len_count(&s[*k], c, 2);
	if (len > 0)
	{
		arr = ft_calloc(sizeof(char), len + 1);
		if (!arr)
			return (s);
	}
	i = 0;
	while (s[*k] != c && s[*k] != '\0')
	{
		arr[i++] = s[*k];
		*k += 1;
	}
	if (i == 0)
		arr = NULL;
	else
		arr[i] = '\0';
	return (arr);
}

static int	ft_core(char **arr, int count, char *s, char c)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (count > 0)
	{
		if (s[k] == c && c != '\0')
			k++;
		else
		{
			arr[i] = ft_strdup_split(arr[i], (char *)s, c, &k);
			if (arr[i] == s)
			{
				arr[i] = NULL;
				return (10);
			}
			i++;
			count--;
		}
	}
	if (count == 0)
		arr[i] = NULL;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**arr;

	if (*s == '\0')
		count = 0;
	else
		count = ft_str_len_count((char *)s, c, 1);
	arr = ft_calloc(sizeof(char *), count + 1);
	if (!arr)
	{
		free((void *) arr);
		return (NULL);
	}
	if (ft_core(arr, count, (char *)s, c) > 0)
	{
		ft_free(arr);
		return (NULL);
	}
	return (arr);
}

/*
#include <stdio.h>

int	main(void)
{
	static char	*test = "";
	static char	c = '^';
	char		**split;
	size_t		i;

	i = 0;
	split = ft_split(test, c);
	if (split == NULL)
		printf("error");
	if (split && split[0] == NULL)
		printf("error2");
	while (split[i] != NULL)
	{
		printf("%s\n", split[i]);
		i++;
	}
	ft_free(split);
	return (0);
}
*/
