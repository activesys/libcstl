/*
 *  The interface of heap.
 *  Copyright (C)  2008 2009  Wangbo
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

#ifndef _CSTL_HEAP_H
#define _CSTL_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Heap algorithm functions.
 */
extern void algo_push_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern void algo_push_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);
extern void algo_pop_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern void algo_pop_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);
extern void algo_sort_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern void algo_sort_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);
extern void algo_make_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern void algo_make_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);
extern bool_t algo_is_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last);
extern bool_t algo_is_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HEAP_H */
/** eof **/

