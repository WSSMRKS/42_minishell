/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:13:28 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/18 17:13:45 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../libft.h"

/// @brief Reads the hostname from the file /etc/hostname.
/// @return The hostname or NULL if the file could not be read.
char	*ft_hostname(void)
{
	t_str	hostname;
	char	*tmp;
	int		hostname_file;

	hostname = str_empty();
	hostname_file = open("/etc/hostname", O_RDONLY);
	if (hostname_file < 0)
		return (NULL);
	while (get_next_line2(hostname_file, &tmp))
	{
		str_pushstr(&hostname, cstr_view(tmp));
		free(tmp);
	}
	close(hostname_file);
	if (hostname.mem_err)
		str_destroy(&hostname);
	if (hostname.len == 0)
		return (NULL);
	return (cstr_take(&hostname));
}
