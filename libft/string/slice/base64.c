/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:30:43 by kwurster          #+#    #+#             */
/*   Updated: 2024/06/28 02:22:27 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_slice.h"

t_str_slice	base64(void)
{
	return (cstr_slice(ATOZ_UPPER ATOZ_LOWER BASE10 "+/", 64));
}

t_str_slice	base64_url(void)
{
	return (cstr_slice(ATOZ_UPPER ATOZ_LOWER BASE10 "-_", 64));
}
