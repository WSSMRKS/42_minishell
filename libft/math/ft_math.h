/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:37:35 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H
# pragma once

# include "../libft.h"

# ifndef SSIZE_MAX
#  define SSIZE_MAX PTRDIFF_MAX
# endif
# ifndef SSIZE_MIN
#  define SSIZE_MIN PTRDIFF_MIN
# endif

int8_t		i8abs(int8_t num);
int16_t		i16abs(int16_t num);
int32_t		i32abs(int32_t num);
int64_t		i64abs(int64_t num);
ssize_t		isizeabs(ssize_t num);

int8_t		i8max(int8_t var1, int8_t var2);
int16_t		i16max(int16_t var1, int16_t var2);
int32_t		i32max(int32_t var1, int32_t var2);
int64_t		i64max(int64_t var1, int64_t var2);
ssize_t		isizemax(ssize_t var1, ssize_t var2);
uint8_t		u8max(uint8_t var1, uint8_t var2);
uint16_t	u16max(uint16_t var1, uint16_t var2);
uint32_t	u32max(uint32_t var1, uint32_t var2);
uint64_t	u64max(uint64_t var1, uint64_t var2);
size_t		usizemax(size_t var1, size_t var2);

int8_t		i8min(int8_t var1, int8_t var2);
int16_t		i16min(int16_t var1, int16_t var2);
int32_t		i32min(int32_t var1, int32_t var2);
int64_t		i64min(int64_t var1, int64_t var2);
ssize_t		isizemin(ssize_t var1, ssize_t var2);
uint8_t		u8min(uint8_t var1, uint8_t var2);
uint16_t	u16min(uint16_t var1, uint16_t var2);
uint32_t	u32min(uint32_t var1, uint32_t var2);
uint64_t	u64min(uint64_t var1, uint64_t var2);
size_t		usizemin(size_t var1, size_t var2);

bool		i8mult(int8_t var1, int8_t var2, int8_t *out);
bool		i16mult(int16_t var1, int16_t var2, int16_t *out);
bool		i32mult(int32_t var1, int32_t var2, int32_t *out);
bool		i64mult(int64_t var1, int64_t var2, int64_t *out);
bool		isizemult(ssize_t var1, ssize_t var2, ssize_t *out);
bool		u8mult(uint8_t var1, uint8_t var2, uint8_t *out);
bool		u16mult(uint16_t var1, uint16_t var2, uint16_t *out);
bool		u32mult(uint32_t var1, uint32_t var2, uint32_t *out);
bool		u64mult(uint64_t var1, uint64_t var2, uint64_t *out);
bool		usizemult(size_t var1, size_t var2, size_t *out);

#endif
