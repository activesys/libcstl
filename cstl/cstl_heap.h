/*
 *  The interface of heap.
 *  Copyright (C)  2008 - 2012  Wangbo
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

#ifndef _CSTL_HEAP_H_
#define _CSTL_HEAP_H_

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
    random_access_iterator_t it_first, random_access_iterator_t it_last);
extern void algo_push_heap_if(
    random_access_iterator_t it_first, random_access_iterator_t it_last,
    binary_function_t bfun_op);
extern void algo_pop_heap(
    random_access_iterator_t it_first, random_access_iterator_t it_last);
extern void algo_pop_heap_if(
    random_access_iterator_t it_first, random_access_iterator_t it_last,
    binary_function_t bfun_op);
extern void algo_sort_heap(
    random_access_iterator_t it_first, random_access_iterator_t it_last);
extern void algo_sort_heap_if(
    random_access_iterator_t it_first, random_access_iterator_t it_last,
    binary_function_t bfun_op);

/**
 * Converts elements from a specified range into a heap in which the first element is the largest.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be converted into a heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be converted into a heap.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_make_heap(random_access_iterator_t it_first, random_access_iterator_t it_last);

/**
 * Converts elements from a specified range into a heap in which the first element is for which a sorting criterion may be specified with a binary predicate.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be converted into a heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be converted into a heap.
 * @param bfun_op       User-defined predicate function object that defines sense in which one element is less than another.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_make_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, binary_function_t bfun_op);

extern bool_t algo_is_heap(
    random_access_iterator_t it_first, random_access_iterator_t it_last);
extern bool_t algo_is_heap_if(
    random_access_iterator_t it_first, random_access_iterator_t it_last,
    binary_function_t bfun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HEAP_H_ */
/** eof **/

