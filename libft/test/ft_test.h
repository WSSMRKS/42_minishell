/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:43:16 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/26 08:39:47 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TEST_H
# define FT_TEST_H
# pragma once

# include "../libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>

typedef bool	(*t_test_fn)(void);

# define ARR_QSORT_U8_TCOUNT 5000

typedef struct s_test
{
	char		*name;
	t_test_fn	test;
}				t_test;

bool		test_arr_qsort(void);

#endif
