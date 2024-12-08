/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 08:32:18 by kwurster          #+#    #+#             */
/*   Updated: 2024/04/30 16:11:08 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_str	percent_char(va_list *args, t_fmt fmt)
{
	(void)args;
	(void)fmt;
	return (str_clone_from(cstr_slice("%", 1)));
}
