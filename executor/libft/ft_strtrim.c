/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:19:11 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/07 12:19:36 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(char const *s1, char const *set)
{
	while (*set)
	{
		if (*s1 == *set)
			return (1);
		else
			set++;
	}
	return (0);
}

static const char	*ft_calc_len(const char *s1, const char *set, size_t *len)
{
	int			i;
	const char	*end;
	const char	*start;

	i = 0;
	start = s1;
	end = &s1[ft_strlen(s1) - 1];
	while (*s1 && ft_checkset(s1, set))
		start = ++s1;
	while (end && ft_checkset(end, set))
		end--;
	while ((start + i) <= end)
		i++;
	*len = i;
	return (start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ret;
	size_t		len;
	size_t		i;
	const char	*start;

	i = 0;
	len = 0;
	if (*s1 != 0)
	{
		start = ft_calc_len(s1, set, &len);
	}
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	while (len-- > 0)
		ret[i++] = *start++;
	ret[i] = 0;
	return (ret);
}

/*
#include <stdio.h>

int	main(void)
{
	static char	*str = "lorem \n ipsum \t dolor \n sit \t amet";
	static char	*set = " ";

	printf("\"%s\"", ft_strtrim(str, set));
}
*/
