/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:03:20 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:43:24 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;
	size_t	act_l;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (s_len < start)
		sub = malloc(sizeof(char));
	else
	{
		act_l = ft_strlen(&s[start]);
		if (s_len >= start && act_l < len)
			sub = malloc(sizeof(char) * (act_l + 1));
		else
			sub = malloc(sizeof(char) * (len + 1));
		if (!sub)
			return (NULL);
		while (act_l-- > 0 && len-- > 0)
			sub[i++] = s[start++];
	}
	if (!sub)
		return (NULL);
	sub[i] = '\0';
	return (sub);
}

/*
int	main(void)
{
	// static char	*str = "This is the string. This is the substring!";

	printf("%s\n", ft_substr("", 32, 15));
}
*/
