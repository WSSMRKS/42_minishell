/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:30:22 by maweiss           #+#    #+#             */
/*   Updated: 2023/12/05 14:42:51 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
	return ;
}

/*
static void	my_toupper_i(unsigned int i, char *c)
{
	(void)i;
	*c = (char)toupper((int)*c);
}

// static char	my_toupper(unsigned int i, char c)
// {
// 	(void)i;
// 	return ((char)toupper((int)c));
// }

int	main(void)
{
	// char const	*s4 = "string to set to uppercase.1234567890";
	// char		*mapres;

	// mapres = ft_strmapi(s4, (char (*)(unsigned int, char))my_toupper);
	// printf("%s\n\n", s4);
	// printf("%s\n\n", mapres);

	char s3[] = "string to set to uppercase.1234567890";

	printf("%s\n", s3);
    ft_striteri(s3, (void (*)(unsigned int, char*))my_toupper_i);
    printf("%s\n", s3);
}
*/
