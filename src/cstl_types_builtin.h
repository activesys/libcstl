/*
 *  The implement of cstl type builtin functions.
 *  Copyright (C)  2008 - 2014  Wangbo
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  Author e-mail: activesys.wb@gmail.com
 *                 activesys@sina.com.cn
 */

#ifndef _CSTL_TYPES_BUILTIN_H_
#define _CSTL_TYPES_BUILTIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * The cstl builtin copy, compare destroy function for c builtin type and cstl builtins.
 * @param cpv_input    input parameter.
 * @param cpv_first    first input parameter.
 * @param cpv_second   second input parameter.
 * @param pv_output    output parameter.
 * @return void.
 * @remarks cpv_input, cpv_first, cpv_second and pv_output must not be NULL.
 */
/* c builtin */
/* char */
extern void _type_init_char(const void* cpv_input, void* pv_output);
extern void _type_copy_char(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_char(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_char(const void* cpv_input, void* pv_output);
/* unsigned char */
extern void _type_init_uchar(const void* cpv_input, void* pv_output);
extern void _type_copy_uchar(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_uchar(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_uchar(const void* cpv_input, void* pv_output);
/* short */
extern void _type_init_short(const void* cpv_input, void* pv_output);
extern void _type_copy_short(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_short(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_short(const void* cpv_input, void* pv_output);
/* unsigned short */
extern void _type_init_ushort(const void* cpv_input, void* pv_output);
extern void _type_copy_ushort(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_ushort(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_ushort(const void* cpv_input, void* pv_output);
/* int */
extern void _type_init_int(const void* cpv_input, void* pv_output);
extern void _type_copy_int(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_int(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_int(const void* cpv_input, void* pv_output);
/* unsigned int */
extern void _type_init_uint(const void* cpv_input, void* pv_output);
extern void _type_copy_uint(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_uint(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_uint(const void* cpv_input, void* pv_output);
/* long */
extern void _type_init_long(const void* cpv_input, void* pv_output);
extern void _type_copy_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_long(const void* cpv_input, void* pv_output);
/* unsigned long */
extern void _type_init_ulong(const void* cpv_input, void* pv_output);
extern void _type_copy_ulong(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_ulong(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_ulong(const void* cpv_input, void* pv_output);
/* float */
extern void _type_init_float(const void* cpv_input, void* pv_output);
extern void _type_copy_float(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_float(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_float(const void* cpv_input, void* pv_output);
/* double */
extern void _type_init_double(const void* cpv_input, void* pv_output);
extern void _type_copy_double(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_double(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_double(const void* cpv_input, void* pv_output);
/* long double */
extern void _type_init_long_double(const void* cpv_input, void* pv_output);
extern void _type_copy_long_double(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_long_double(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_long_double(const void* cpv_input, void* pv_output);
/* bool_t */
extern void _type_init_cstl_bool(const void* cpv_input, void* pv_output);
extern void _type_copy_cstl_bool(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_cstl_bool(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_cstl_bool(const void* cpv_input, void* pv_output);
/* char* */
extern void _type_init_cstr(const void* cpv_input, void* pv_output);
extern void _type_copy_cstr(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_cstr(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_cstr(const void* cpv_input, void* pv_output);
/* void* */
extern void _type_init_pointer(const void* cpv_input, void* pv_output);
extern void _type_copy_pointer(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_pointer(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_pointer(const void* cpv_input, void* pv_output);
/* cstl container */
/* vector_t */
extern void _type_init_vector(const void* cpv_input, void* pv_output);
extern void _type_copy_vector(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_vector(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_vector(const void* cpv_input, void* pv_output);
/* list_t */
extern void _type_init_list(const void* cpv_input, void* pv_output);
extern void _type_copy_list(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_list(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_list(const void* cpv_input, void* pv_output);
/* slist_t */
extern void _type_init_slist(const void* cpv_input, void* pv_output);
extern void _type_copy_slist(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_slist(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_slist(const void* cpv_input, void* pv_output);
/* deque_t */
extern void _type_init_deque(const void* cpv_input, void* pv_output);
extern void _type_copy_deque(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_deque(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_deque(const void* cpv_input, void* pv_output);
/* stack_t */
extern void _type_init_stack(const void* cpv_input, void* pv_output);
extern void _type_copy_stack(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_stack(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_stack(const void* cpv_input, void* pv_output);
/* queue_t */
extern void _type_init_queue(const void* cpv_input, void* pv_output);
extern void _type_copy_queue(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_queue(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_queue(const void* cpv_input, void* pv_output);
/* priority_queue_t */
extern void _type_init_priority_queue(const void* cpv_input, void* pv_output);
extern void _type_copy_priority_queue(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_priority_queue(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_priority_queue(const void* cpv_input, void* pv_output);
/* set_t */
extern void _type_init_set(const void* cpv_input, void* pv_output);
extern void _type_copy_set(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_set(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_set(const void* cpv_input, void* pv_output);
/* map_t */
extern void _type_init_map(const void* cpv_input, void* pv_output);
extern void _type_copy_map(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_map(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_map(const void* cpv_input, void* pv_output);
/* multiset_t */
extern void _type_init_multiset(const void* cpv_input, void* pv_output);
extern void _type_copy_multiset(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_multiset(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_multiset(const void* cpv_input, void* pv_output);
/* multimap_t */
extern void _type_init_multimap(const void* cpv_input, void* pv_output);
extern void _type_copy_multimap(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_multimap(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_multimap(const void* cpv_input, void* pv_output);
/* hash_set_t */
extern void _type_init_hash_set(const void* cpv_input, void* pv_output);
extern void _type_copy_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_hash_set(const void* cpv_input, void* pv_output);
/* hash_map_t */
extern void _type_init_hash_map(const void* cpv_input, void* pv_output);
extern void _type_copy_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_hash_map(const void* cpv_input, void* pv_output);
/* hash_multiset_t */
extern void _type_init_hash_multiset(const void* cpv_input, void* pv_output);
extern void _type_copy_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_hash_multiset(const void* cpv_input, void* pv_output);
/* hash_multimap_t */
extern void _type_init_hash_multimap(const void* cpv_input, void* pv_output);
extern void _type_copy_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_hash_multimap(const void* cpv_input, void* pv_output);
/* pair_t */
extern void _type_init_pair(const void* cpv_input, void* pv_output);
extern void _type_copy_pair(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_pair(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_pair(const void* cpv_input, void* pv_output);
/* string_t */
extern void _type_init_string(const void* cpv_input, void* pv_output);
extern void _type_copy_string(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_string(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_string(const void* cpv_input, void* pv_output);
/* iterator_t */
extern void _type_init_iterator(const void* cpv_input, void* pv_output);
extern void _type_copy_iterator(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_iterator(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_iterator(const void* cpv_input, void* pv_output);
/* range_t */
extern void _type_init_range(const void* cpv_input, void* pv_output);
extern void _type_copy_range(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_range(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_range(const void* cpv_input, void* pv_output);
/* basic_string_t */
extern void _type_init_basic_string(const void* cpv_input, void* pv_output);
extern void _type_copy_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_basic_string(const void* cpv_input, void* pv_output);

#ifndef _MSC_VER
/* _Bool */
extern void _type_init_bool(const void* cpv_input, void* pv_output);
extern void _type_copy_bool(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_bool(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_bool(const void* cpv_input, void* pv_output);
/* long long */
extern void _type_init_long_long(const void* cpv_input, void* pv_output);
extern void _type_copy_long_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_long_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_long_long(const void* cpv_input, void* pv_output);
/* unsigned long long */
extern void _type_init_ulong_long(const void* cpv_input, void* pv_output);
extern void _type_copy_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_ulong_long(const void* cpv_input, void* pv_output);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_TYPES_BUILTIN_H_ */
/** eof **/

