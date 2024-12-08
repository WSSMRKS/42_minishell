/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwurster <kwurster@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 06:19:16 by kwurster          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:34 by kwurster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H
# pragma once

# include "../libft.h"

typedef void	(*t_vec_map)(const void *from, void *to);
typedef void	(*t_vec_mapi)(const t_vec *from, t_vec *to, size_t i,
		void *extra);
typedef void	(*t_vec_iter)(void *element);
typedef void	(*t_vec_iteri)(t_vec *vec, size_t i, void *extra);

void			*vec_get(const t_vec *vec);
void			*vec_get_at(const t_vec *vec, size_t index);
void			*vec_get_last(const t_vec *vec);
void			*vec_take(t_vec *vec);
void			*vec_get_cloned(const t_vec *vec);

size_t			vec_capacity(const t_vec *vec);
void			vec_clear(t_vec *vec);
t_vec			vec_clone(const t_vec *vec);
t_vec			vec_clone_sized(const t_vec *vec, size_t new_len);
bool			vec_contains(const t_vec *vec, bool (*test)(const void *));
void			vec_copy(t_vec *dst, const t_vec *src);
void			vec_copy_sized(t_vec *dst, const t_vec *src, size_t new_len);
size_t			vec_count(const t_vec *vec, size_t (*count)(const void *));
void			vec_cat(t_vec *dst, const t_vec *src);
void			vec_cat_sized(t_vec *dst, const t_vec *src, size_t n);
bool			vec_cmp(const t_vec *vec1, const t_vec *vec2);
t_str			vec_debug(t_vec *vec, void (*debug)(const void *, t_str *));
void			vec_destroy(t_vec *vec, t_vec_iter destroy);
t_str			vec_display(t_vec *vec, void (*display)(const void *, t_str *));
t_vec			vec_empty(size_t element_size);
t_vec			vec_empty_with_capacity(size_t element_size, size_t n);
t_vec			vec_extract_range(t_vec *vec, size_t start, size_t end);
bool			vec_find(const t_vec *vec, bool (*test)(const void *),
					size_t *at);
bool			vec_identical(const t_vec *vec1, const t_vec *vec2);
bool			vec_insert(t_vec *vec, size_t index, void *data);
void			vec_insertarr(t_vec *vec, size_t index, void *arr, size_t len);
bool			vec_insertn(t_vec *vec, size_t index, void *data, size_t n);
void			vec_insertvec(t_vec *vec, size_t index, const t_vec *data);
void			vec_insertvec_sized(t_vec *vec, size_t index, const t_vec *data,
					size_t n);
void			vec_iter(t_vec *vec, t_vec_iter iter);
void			vec_iteri(t_vec *vec, t_vec_iteri iteri, void *extra);
t_str			vec_join_strs(const t_vec *vec, const t_str_slice *seperator);
t_vec			vec_map(const t_vec *vec, t_vec_map map, size_t element_size);
t_vec			vec_mapi(const t_vec *vec, t_vec_mapi mapi, size_t element_size,
					void *extra);
t_vec			vec_new_clone(const void *arr, size_t element_size, size_t len);
t_vec			vec_new_from(void *arr, size_t element_size, size_t len);
t_vec			vec_new_repeat(void *arr, size_t element_size, size_t len,
					size_t n);
t_vec			vec_pop(t_vec *vec);
t_vec			vec_pop_front(t_vec *vec);
bool			vec_push(t_vec *vec, void *data);
bool			vec_push_front(t_vec *vec, void *data);
void			vec_pusharr(t_vec *vec, void *arr, size_t len);
void			vec_pusharr_front(t_vec *vec, void *arr, size_t len);
void			vec_pusharrn(t_vec *vec, void *arr, size_t len, size_t n);
void			vec_pusharrn_front(t_vec *vec, void *arr, size_t len, size_t n);
void			vec_pushn(t_vec *vec, void *data, size_t n);
void			vec_pushn_front(t_vec *vec, void *data, size_t n);
void			vec_pushvec(t_vec *vec, const t_vec *data);
void			vec_pushvec_front(t_vec *vec, const t_vec *data);
void			vec_pushvec_front_sized(t_vec *vec, const t_vec *data,
					size_t len);
void			vec_pushvec_sized(t_vec *vec, const t_vec *data, size_t len);
void			vec_pushvecn(t_vec *vec, const t_vec *data, size_t n);
void			vec_pushvecn_front(t_vec *vec, const t_vec *data, size_t n);
void			vec_pushvecn_front_sized(t_vec *vec, const t_vec *data,
					size_t len, size_t n);
void			vec_pushvecn_sized(t_vec *vec, const t_vec *data, size_t len,
					size_t n);
void			vec_remove(t_vec *vec, const void *element);
void			vec_remove_first_n_iterative(t_vec *vec, const void *element,
					size_t n);
void			vec_remove_first_n_recursive(t_vec *vec, const void *element,
					size_t n);
void			vec_remove_last_n(t_vec *vec, const void *element, size_t n);
void			vec_remove_at(t_vec *vec, size_t index);
void			vec_remove_last(t_vec *vec);
void			vec_remove_range(t_vec *vec, size_t start, size_t end);
void			vec_reverse(t_vec *vec);
bool			vec_rotate(t_vec *vec, size_t n);
bool			vec_rrotate(t_vec *vec, size_t n);
void			vec_shiftleft(t_vec *vec, size_t n);
void			vec_shiftright(t_vec *vec, size_t n);
bool			vec_shrink_to_fit(t_vec *vec);
void			vec_swap(t_vec *vec1, t_vec *vec2);
void			vec_swap_at(t_vec *vec1, size_t index1, t_vec *vec2,
					size_t index2);
void			vec_trunc(t_vec *vec, size_t n);
bool			vec_try_grow(t_vec *vec, size_t min_growth);
bool			vec_try_set_capacity(t_vec *vec, size_t n);

void			iter_str_destroy(void *ele);
void			iter_ptr_free(void *ptr);

void			*vec_get_next_uninit(t_vec *vec);
void			*vec_get_next_uninit_incr_len(t_vec *vec);
bool			vec_push_null(t_vec *vec);

void			map_cstr_into_str(const void *from, void *to);
void			map_cstr_to_cloned_str(const void *from, void *to);
void			map_str_into_cstr(const void *from, void *to);
void			map_str_to_aliased_cstr(const void *from, void *to);
void			map_str_to_str_slice(const void *from, void *to);
void			map_strsl_to_cloned_cstr(const void *from, void *to);
void			map_strsl_to_cloned_str(const void *from, void *to);
void			map_cstr_clone(const void *from, void *to);
void			map_str_clone(const void *from, void *to);
bool			vec_cstrs_into_strs(t_vec *cstrs);
bool			vec_cstrs_to_cloned_strs(const t_vec *cstrs, t_vec *out);
bool			vec_strs_into_cstrs(t_vec *strs);
bool			vec_strs_to_str_slices(const t_vec *strs, t_vec *out);
bool			vec_strs_to_aliased_cstrs(const t_vec *strs, t_vec *out);
bool			vec_strsls_to_cloned_cstrs(const t_vec *slices, t_vec *out);
bool			vec_strsls_to_cloned_strs(const t_vec *slices, t_vec *out);
bool			vec_cstrs_clone(const t_vec *cstrs, t_vec *out);
bool			vec_strs_clone(const t_vec *strs, t_vec *out);

void			iter_str_append(t_vec *vec, size_t i, void *to_append);
bool			vec_strs_append_to_all(t_vec *strs, t_str_slice to_append);

#endif
