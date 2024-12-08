/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:37:19 by maweiss           #+#    #+#             */
/*   Updated: 2024/11/11 16:04:46 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "stdlib.h"

int	ft_free_3d(char ***tofree)
{
	int	i;
	int	j;

	i = 0;
	if (tofree == NULL)
		return (1);
	while (tofree[i])
	{
		j = 0;
		while (tofree[i] && tofree[i][j])
		{
			free(tofree[i][j]);
			tofree[i][j] = NULL;
			j++;
		}
		free(tofree[i]);
		tofree[i] = NULL;
		i++;
	}
	free(tofree);
	return (0);
}
