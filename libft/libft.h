/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wssmrks <wssmrks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:17:57 by kwurster          #+#    #+#             */
/*   Updated: 2024/12/08 17:24:19 by wssmrks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
// clangd seems to not recognize classic header guards
# pragma once

# include "ft_types.h"
# include "string/ft_str.h"
# include "env/ft_env.h"
# include "fs/ft_fs.h"
# include "vec/ft_vec.h"
# include "array/ft_array.h"
# include "img/ft_img.h"
# include "geo/ft_geo.h"
# include "math/ft_math.h"
# include "list/ft_list.h"

/*
	LIBC
*/

int32_t			ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int32_t			ft_isalnum(int32_t c);
int32_t			ft_isalpha(int32_t c);
int32_t			ft_isascii(int32_t c);
int32_t			ft_isdigit(int32_t c);
int32_t			ft_isprint(int32_t c);
int32_t			ft_isspace(int32_t c);
void			*ft_memchr(const void *s, int32_t c, size_t n);
int32_t			ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_memswap(void *b1, void *b2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memdup(const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
uint64_t		*ft_memset64(uint64_t *dest, uint64_t src, size_t n);
uint32_t		*ft_memset32(uint32_t *dest, uint32_t src, size_t n);
uint16_t		*ft_memset16(uint16_t *dest, uint16_t src, size_t n);
void			*ft_memset(void *dest, uint8_t src, size_t n);
void			*ft_realloc(void *ptr, size_t from, size_t to);
void			*ft_reallocarray(void *ptr, size_t from, size_t nmemb,
					size_t size);
char			*ft_reallocstring(char *ptr, size_t to);
int32_t			ft_tolower(int32_t c);
int32_t			ft_toupper(int32_t c);

/*
	GNL
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char			*get_next_line(int32_t fd);
void			get_next_line_finish(int32_t fd);
bool			get_next_line2(int32_t fd, char **out);

/*
	OTHER
*/

ssize_t			ft_putchar_fd(char c, int32_t fd);
ssize_t			ft_putendl_fd(const char *s, int32_t fd);
ssize_t			ft_putfill_fd(char c, int32_t fd, size_t fill);
ssize_t			ft_putnbr_fd(int32_t n, int32_t fd);
ssize_t			ft_putstr_fd(const char *s, int32_t fd);
ssize_t			ft_putstrsl_fd(t_str_slice strsl, int32_t fd);
bool			ptr_is_null(const void *ptr);
bool			ptr_ptr_is_null(const void *ptr);
bool			ft_rand(uint8_t *bytes, size_t n);

/*
	CSTRING
*/

char			*ft_itoa(int32_t n);
char			**ft_split(const char *s, char c);
char			*ft_str_notchr(const char *s, int32_t c);
char			*ft_strchr(const char *s, int32_t c);
int32_t			ft_strcmp(const char *s1, const char *s2);
size_t			ft_strdist(const char *start, const char *end);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(uint32_t, char *));
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(const char *s, char (*f)(uint32_t, char));
int32_t			ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strndup(const char *s, size_t len);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strr_notchr(const char *s, int32_t c);
char			*ft_strrchr(const char *s, int32_t c);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_substr(const char *s, uint32_t start, size_t len);

/*
	FT_PRINTF
*/

int32_t			ft_printf(const char *s, ...);
int32_t			ft_printf_fd(int32_t fd, const char *s, ...);

/*
	MS_ADDON
*/

int				ft_free_2d(char **tofree);
int				ft_free_3d(char ***tofree);
char			*ft_multistrjoin(int nb_strings, char const *s1, ...);

#endif
