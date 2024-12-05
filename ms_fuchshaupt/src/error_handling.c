/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zblume <zblume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:29:11 by zblume            #+#    #+#             */
/*   Updated: 2024/10/29 14:29:11 by zblume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exit_on_error(t_data *data, char *msg, int leave, int ret)
{
	write(STDERR_FILENO, "\033[31m", 5);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "\033[0m", 4);
	if (leave == 1)
	{
		printf("exiting %d\n", ret);
		cleanup(data);
		exit(ret);
	}
	return (ret);
}
