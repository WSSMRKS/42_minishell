/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:52:47 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:04 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int32_t	ft_isalnum(int32_t c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}