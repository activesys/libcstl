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
 * @param bfun_op       User-defined predicate function that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  A random-access iterator addressing the element in the destination range one position beyond the last element inserted from the source range.
 * @remarks The source and destination ranges must not overlap and must be valid, otherwise the behavior is undefined.
 */
extern random_access_iterator_t algo_partial_sort_copy_if(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2, binary_function_t bfun_op);

/**
 * Arranges the elements in a specified range into a nondescending order.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be sorted.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be sorted.
 * @return  void.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern void algo_sort(random_access_iterator_t it_first, random_access_iterator_t it_last);

/**
 * Arranges the elements in a specified range according to an ordering criterion specified by a binary predicate.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be sorted.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be sorted.
 * @param bfun_op       User-defined predicate function that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @return  void.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern void algo_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, binary_function_t bfun_op);

/**
 * Combines all of the elements from two sorted source ranges into a single, sorted destination range.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges to be combined
 *                      and sorted into a single range.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges to be combined
 *                      and sorted into a single range.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges to be combined
 *                      and sorted into a single range.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges to be combined
 *                      and sorted into a single range.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be combined into a single sorted range.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range.
 * @remarks The sorted source ranges referenced must be valid. The destination range should not overlap either of the source ranges
 *          and should be large enough to contain the destination range.
 */
extern output_iterator_t algo_merge(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result);

/**
 * Combines all of the elements from two sorted source ranges into a single, sorted destination range, where the ordering criterion
 * may be specified by a binary predicate.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges to be combined
 *                      and sorted into a single range.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges to be combined
 *                      and sorted into a single range.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges to be combined
 *                      and sorted into a single range.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges to be combined
 *                      and sorted into a single range.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be combined into a single sorted range.
 * @param bfun_op       User-defined predicate function that defines the sense in which one element is greater than another. 
 * @return  An output iterator addressing the position one past the last element in the sorted destination range.
 * @remarks The sorted source ranges referenced must be valid. The destination range should not overlap either of the source ranges
 *          and should be large enough to contain the destination range.
 */
extern output_iterator_t algo_merge_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, binary_function_t bfun_op);

/**
 * Combines the elements from two consecutive sorted ranges into a single sorted range.
 * @param it_first      A bidirectional iterator addressing the position of the first element in the first of two consecutive
 *                      sorted ranges to be combined and sorted into a single range.
 * @param it_middle     A bidirectional iterator addressing the position of the first element in the second of two consecutive
 *                      sorted ranges to be combined and sorted into a single range.
 * @param it_last       A bidirectional iterator addressing the position one past the last element in the second of two consecutive
 *                      sorted ranges to be combined and sorted into a single range.
 * @return  void.
 * @remarks The sorted consecutive ranges referenced must be valid, otherwsie the behavior is undefined.
 */
extern void algo_inplace_merge(
    bidirectional_iterator_t it_first, bidirectional_iterator_t it_middle, bidirectional_iterator_t it_last);

/**
 * Combines the elements from two consecutive sorted ranges into a single sorted range, where the ordering criterion may be specified by a binary predicate.
 * @param it_first      A bidirectional iterator addressing the position of the first element in the first of two consecutive
 *                      sorted ranges to be combined and sorted into a single range.
 * @param it_middle     A bidirectional iterator addressing the position of the first element in the second of two consecutive
 *                      sorted ranges to be combined and sorted into a single range.
 * @param it_last       A bidirectional iterator addressing the position one past the last element in the second of two consecutive
 *                      sorted ranges to be combined and sorted into a single range.
 * @param bfun_op       User-defined predicate function that defines the sense in which one element is greater than another.
 * @return  void.
 * @remarks The sorted consecutive ranges referenced must be valid, otherwsie the behavior is undefined.
 */
extern void algo_inplace_merge_if(
    bidirectional_iterator_t it_first, bidirectional_iterator_t it_middle, bidirectional_iterator_t it_last, binary_function_t bfun_op);

/**
 * Arranges the elements in a specified range into a nondescending order.
 * @param it_first      A bidirectional iterator addressing the position of the first element in the range to be sorted.
 * @param it_last       A bidirectional iterator addressing the position one past the final element in the range to be sorted.
 * @return  void.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern void algo_stable_sort(random_access_iterator_t it_first, random_access_iterator_t it_last);

/**
 * Arranges the elements in a specified range into a nondescending order or according to an ordering criterion
 * specified by a binary predicate and preserves the relative ordering of equivalent elements.
 * @param it_first      A bidirectional iterator addressing the position of the first element in the range to be sorted.
 * @param it_last       A bidirectional iterator addressing the position one past the final element in the range to be sorted.
 * @param bfun_op       User-defined predicate function that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @return  void.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern void algo_stable_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, binary_function_t bfun_op);

/**
 * Partitions a range of elements, correctly locating the nth element of the sequence in the range so that all the elements in front of it are less than or equal to it and
 * all the elements that follow it in the sequence are greater than or equal to it.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be partitioned.
 * @param it_nth        A random-access iterator addressing the position of element to be correctly ordered on the boundary of the partition.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be partitioned.
 * @return  void.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern void algo_nth_element(random_access_iterator_t it_first, random_access_iterator_t it_nth, random_access_iterator_t it_last);

/**
 * Partitions a range of elements, correctly locating the nth element of the sequence in the range so that all the elements in front of it are less than or equal to it and
 * all the elements that follow it in the sequence are greater than or equal to it.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be partitioned.
 * @param it_nth        A random-access iterator addressing the position of element to be correctly ordered on the boundary of the partition.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be partitioned.
 * @param bfun_op       User-defined predicate function that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @return  void.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern void algo_nth_element_if(random_access_iterator_t it_first, random_access_iterator_t it_nth, random_access_iterator_t it_last, binary_function_t bfun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_SORTING_H_ */
/** eof **/

