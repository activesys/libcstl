/*
 *  The interface of sorting algorithm.
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

#ifndef _CSTL_ALGO_SORTING_H_
#define _CSTL_ALGO_SORTING_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Check a specificed range is sorted or not.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be checked.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be checked.
 * @return  If the range is sorted or not.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_is_sorted(forward_iterator_t it_first, forward_iterator_t it_last);

/**
 * Check a specificed range is sorted or not according to an ordering critierion specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be checked.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be checked.
 * @param bfun_op       User-defined predicate function that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @return  If the range is sorted or not.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_is_sorted_if(forward_iterator_t it_first, forward_iterator_t it_last, binary_function_t bfun_op);

/**
 * Arranges a specified number of the smaller elements in a range into a nondescending order.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be sorted.
 * @param it_middle     A random-access iterator addressing the position one past the final element in the subrange to be sorted.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be partially sorted.
 * @return  void.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern void algo_partial_sort(
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last);

/**
 * Arranges a specified number of the smaller elements in a range according to an ordering criterion specified by a binary predicate.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be sorted.
 * @param it_middle     A random-access iterator addressing the position one past the final element in the subrange to be sorted.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be partially sorted.
 * @param bfun_op       User-defined predicate function that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @return  void.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern void algo_partial_sort_if(
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last, binary_function_t bfun_op);

/**
 * Copies elements from a source range into a destination range where the source elements are ordered by less than.
 * @param it_first1     An input iterator addressing the position of the first element in the source range.
 * @param it_last1      An input iterator addressing the position one past the final element in the source range.
 * @param it_first2     A random-access iterator addressing the position of the first element in the sorted destination range.
 * @param it_last2      A random-access iterator addressing the position one past the final element in the sorted destination range.
 * @return  A random-access iterator addressing the element in the destination range one position beyond the last element inserted from the source range.
 * @remarks The source and destination ranges must not overlap and must be valid, otherwise the behavior is undefined.
 */
extern random_access_iterator_t algo_partial_sort_copy(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2);

/**
 * Copies elements from a source range into a destination range where the source elements are ordered by specified binary predicate.
 * @param it_first1     An input iterator addressing the position of the first element in the source range.
 * @param it_last1      An input iterator addressing the position one past the final element in the source range.
 * @param it_first2     A random-access iterator addressing the position of the first element in the sorted destination range.
 * @param it_last2      A random-access iterator addressing the position one past the final element in the sorted destination range.
 * @param bfun_op       User-defined predicate function object that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  A random-access iterator addressing the element in the destination range one position beyond the last element inserted from the source range.
 * @remarks The source and destination ranges must not overlap and must be valid, otherwise the behavior is undefined.
 */
extern random_access_iterator_t algo_partial_sort_copy_if(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2, binary_function_t bfun_op);
#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_SORTING_H_ */
/** eof **/

