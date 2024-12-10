/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:00:12 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/19 00:00:16 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int32_t	ft_isspace(int32_t c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v'
		|| c == '\t' || c == '\f');
}