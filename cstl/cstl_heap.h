/*
 *  The interface of heap.
 *  Copyright (C)  2008 - 2013  Wangbo
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
/**
 * Adds an element that is at the end of a range to an existing heap consisting of the prior elements in the range.
 * @param it_first      A random-access iterator addressing the position of the first element in the heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be converted into a heap.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_push_heap(random_access_iterator_t it_first, random_access_iterator_t it_last);

/**
 * Adds an element that is at the end of a range to an existing heap consisting of the prior elements in the range.
 * @param it_first      A random-access iterator addressing the position of the first element in the heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be converted into a heap.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_push_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op);

/**
 * Removes the largest element from the front of a heap to the next-to-last position in the range and then forms a new heap from the remaining elements.
 * @param it_first      A random-access iterator addressing the position of the first element in the heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the heap.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_pop_heap(random_access_iterator_t it_first, random_access_iterator_t it_last);

/**
 * Removes the largest element from the front of a heap to the next-to-last position in the range and then forms a new heap from the remaining elements.
 * @param it_first      A random-access iterator addressing the position of the first element in the heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the heap.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_pop_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op);

/**
 * Removes the largest element from the front of a heap to the next-to-last position in the range and then forms a new heap from the remaining elements.
 * @param it_first      A random-access iterator addressing the position of the first element in the heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the heap.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_sort_heap(random_access_iterator_t it_first, random_access_iterator_t it_last);

/**
 * Removes the largest element from the front of a heap to the next-to-last position in the range and then forms a new heap from the remaining elements.
 * @param it_first      A random-access iterator addressing the position of the first element in the heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the heap.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_sort_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op);

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
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void algo_make_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op);

/**
 * Check the specified range is a heap.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be checked.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be checked.
 * @return  Is heap or not.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_is_heap(random_access_iterator_t it_first, random_access_iterator_t it_last);

/**
 * Check the specified range is a heap with user-defined predicate function.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be checked.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be checked.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  Is heap or not.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_is_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HEAP_H_ */
/** eof **/

