/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maweiss <maweiss@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:23:15 by maweiss           #+#    #+#             */
/*   Updated: 2024/12/04 19:34:53 by maweiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_mprotect(void *subject)
{
	if (!subject)
	{
		ft_printf_fd(STDERR_FILENO, "malloc fail");
		exit(ENOMEM);
	}
}
