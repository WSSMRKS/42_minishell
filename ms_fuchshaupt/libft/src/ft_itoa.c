/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:08:46 by zblume            #+#    #+#             */
/*   Updated: 2024/06/21 13:59:44 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_get_number_length(int n)
{
	int	length;
	int	abs_val;

	length = 0;
	abs_val = n;
	if (abs_val < 0)
	{
		length++;
		abs_val = -abs_val;
	}
	while (abs_val > 0)
	{
		abs_val = abs_val / 10;
		length++;
	}
	return (length);
}

static void	ft_fill_string(char *str, int n, int length)
{
	int	i;
	int	cmp;

	i = length - 1;
	cmp = 0;
	length++;
	if (n < 0)
	{
		str[0] = 45;
		n = -n;
		cmp = 1;
	}
	while (i >= cmp)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	str[length -1] = '\0';
}

char	*ft_itoa(int n)
{
	int		length;
	char	*str;

	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	length = ft_get_number_length(n);
	str = (char *)ft_calloc(length + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_fill_string(str, n, length);
	return (str);
}
