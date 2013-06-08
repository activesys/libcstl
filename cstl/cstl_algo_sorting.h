/*
 *  The interface of sorting algorithm.
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

#ifndef _CSTL_ALGO_SORTING_H_
#define _CSTL_ALGO_SORTING_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Finds the position of the first element in an ordered range that has a value greater than or equivalent to a specified value.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param elem          The value whose first position or possible first position is being searched for in the ordered range.
 * @return  A forward iterator at the position of the first element in an ordered range with a value that is greater than or equivalent to a specified value.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_lower_bound(it_first, it_last, elem) _algo_lower_bound((it_first), (it_last), (elem))

/**
 * Finds the position of the first element in an ordered range that has a value greater than or equivalent to a specified value,
 * where the ordering criterion may be specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param elem          The value whose first position or possible first position is being searched for in the ordered range.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  A forward iterator at the position of the first element in an ordered range with a value that is greater than or equivalent to a specified value.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_lower_bound_if(it_first, it_last, elem, bfun_op) _algo_lower_bound_if((it_first), (it_last), (bfun_op), (elem))

/**
 * Finds the position of the first element in an ordered range that has a value that is greater than a specified value.
 * @param it_first      The position of the first element in the range to be searched.
 * @param it_last       The position one past the final element in the range to be searched.
 * @param elem          The value in the ordered range that needs to be exceeded by the value of the element addressed by the iterator returned.
 * @return  A forward iterator to the position of the first element that has a value greater than a specified value.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_upper_bound(it_first, it_last, elem) _algo_upper_bound((it_first), (it_last), (elem))

/**
 * Finds the position of the first element in an ordered range that has a value that is greater than a specified value,
 * where the ordering criterion may be specified by a binary predicate.
 * @param it_first      The position of the first element in the range to be searched.
 * @param it_last       The position one past the final element in the range to be searched.
 * @param elem          The value in the ordered range that needs to be exceeded by the value of the element addressed by the iterator returned.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  A forward iterator to the position of the first element that has a value greater than a specified value.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_upper_bound_if(it_first, it_last, elem, bfun_op) _algo_upper_bound_if((it_first), (it_last), (bfun_op), (elem))

/**
 * Finds a pair of positions in an ordered range, the first less than or equivalent to the position of a specified element and
 * the second greater than the element's position.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param elem          The value in the ordered range that needs to be equivalent to the value of the element
 *                      addressed by the first component of the pair returned and that needs to be less than the value of the element
 *                      addressed by the second component of that pair returns.
 * @return  A range of forward iterators addressing two positions in an ordered range in which the first component of the range refers to the position
 *          where an element is or would be if it had a value that is less than or equivalent to a specified value and the second component of the range
 *          refers to the first position where an element has a value that is greater than the value specified.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_equal_range(it_first, it_last, elem) _algo_equal_range((it_first), (it_last), (elem))

/**
 * Finds a pair of positions in an ordered range, the first less than or equivalent to the position of a specified element and
 * the second greater than the element's position, where the sense of equivalence or ordering used to establish the positions
 * in the sequence may be specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param elem          The value in the ordered range that needs to be equivalent to the value of the element
 *                      addressed by the first component of the pair returned and that needs to be less than the value of the element
 *                      addressed by the second component of that pair returns.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  A range of forward iterators addressing two positions in an ordered range in which the first component of the range refers to the position
 *          where an element is or would be if it had a value that is less than or equivalent to a specified value and the second component of the range
 *          refers to the first position where an element has a value that is greater than the value specified, where the sense of equivalence or ordering
 *          may be specified by a binary predicate.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_equal_range_if(it_first, it_last, elem, bfun_op) _algo_equal_range_if((it_first), (it_last), (bfun_op), (elem))

/**
 * Tests whether there is an element in a sorted range that is equal to a specified value.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param elem          The value required to be matched by the value of the element.
 * @return  true if an element is found in the range that is equal or equivalent to the specified value; otherwise, false.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_binary_search(it_first, it_last, elem) _algo_binary_search((it_first), (it_last), (elem))

/**
 * Tests whether there is an element in a sorted range that is equivalent to it in a sense specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param elem          The value that must satisfy the condition with the element value specified by the binary predicate.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  true if an element is found in the range that is equal or equivalent to the specified value; otherwise, false.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
#define algo_binary_search_if(it_first, it_last, elem, bfun_op) _algo_binary_search_if((it_first), (it_last), (bfun_op), (elem))

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
extern bool_t algo_is_sorted_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op);

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
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last, bfun_t bfun_op);

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
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2, bfun_t bfun_op);

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
extern void algo_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op);

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
    output_iterator_t it_result, bfun_t bfun_op);

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
    bidirectional_iterator_t it_first, bidirectional_iterator_t it_middle, bidirectional_iterator_t it_last, bfun_t bfun_op);

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
extern void algo_stable_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op);

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
extern void algo_nth_element_if(random_access_iterator_t it_first, random_access_iterator_t it_nth, random_access_iterator_t it_last, bfun_t bfun_op);

/**
 * Tests whether one sorted range contains all the elements contained in a second sorted range.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be tested for whether all the elements of the second are contained in the first.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be tested for whether all the elements of the second are contained in the first.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be tested for whether all the elements of the second are contained in the first.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be tested for whether all the elements of the second are contained in the first.
 * @return  true if the first sorted range contains all the elements in the second sorted range; otherwise, false.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_includes(input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, input_iterator_t it_last2);

/**
 * Tests whether one sorted range contains all the elements contained in a second sorted range, where the ordering or
 * equivalence criterion between elements may be specified by a binary predicate.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be tested for whether all the elements of the second are contained in the first.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be tested for whether all the elements of the second are contained in the first.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be tested for whether all the elements of the second are contained in the first.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be tested for whether all the elements of the second are contained in the first.
 * @return  true if the first sorted range contains all the elements in the second sorted range; otherwise, false.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_includes_if(input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, input_iterator_t it_last2, bfun_t bfun_op);

/**
 * Unites all of the elements that belong to at least one of two sorted source ranges into a single, sorted destination range.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the union of the two source ranges.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the union of the two source ranges.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the union of the two source ranges.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the union of the two source ranges.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be united into a single sorted range representing the union of the two source ranges.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range representing the union of the two source ranges.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_set_union(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result);

/**
 * Unites all of the elements that belong to at least one of two sorted source ranges into a single, sorted destination range,
 * sorted destination range, where the ordering criterion may be specified by a binary predicate.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the union of the two source ranges.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the union of the two source ranges.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the union of the two source ranges.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the union of the two source ranges.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be united into a single sorted range representing the union of the two source ranges.
 * @param bfun_op       User-defined predicate function that defines the sense in which one element is greater than another.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range representing the union of the two source ranges.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_set_union_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, bfun_t bfun_op);

/**
 * Unites all of the elements that belong to both sorted source ranges into a single, sorted destination range.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the intersection of the two source ranges.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the intersection of the two source ranges.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the intersection of the two source ranges.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the intersection of the two source ranges.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be united into a single sorted range representing the intersection of the two source ranges.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range representing the intersection of the two source ranges.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_set_intersection(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result);

/**
 * Unites all of the elements that belong to both sorted source ranges into a single, sorted destination range,
 * where the ordering criterion may be specified by a binary predicate.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the intersection of the two source ranges.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the intersection of the two source ranges.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the intersection of the two source ranges.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the intersection of the two source ranges.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be united into a single sorted range representing the intersection of the two source ranges.
 * @param bfun_op       User-defined predicate function that defines the sense in which one element is greater than another.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range representing the intersection of the two source ranges.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_set_intersection_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, bfun_t bfun_op);

/**
 * Unites all of the elements that belong to one sorted source range, but not to a second sorted source range, into a single, sorted destination range.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the difference of the two source ranges.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the difference of the two source ranges.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the difference of the two source ranges.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the difference of the two source ranges.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be united into a single sorted range representing the difference of the two source ranges.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range representing the difference of the two source ranges.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_set_difference(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result);

/**
 * Unites all of the elements that belong to one sorted source range, but not to a second sorted source range, into a single, sorted destination range,
 * where the ordering criterion may be specified by a binary predicate.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the difference of the two source ranges.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the difference of the two source ranges.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the difference of the two source ranges.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the difference of the two source ranges.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be united into a single sorted range representing the difference of the two source ranges.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range representing the difference of the two source ranges.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_set_difference_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, bfun_t bfun_op);

/**
 * Unites all of the elements that belong to one, but not both, of the sorted source ranges into a single, sorted destination range.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the symmetric difference of the two source ranges.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the symmetric difference of the two source ranges.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the symmetric difference of the two source ranges.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the symmetric difference of the two source ranges.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be united into a single sorted range representing the symmetric difference of the two source ranges.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range representing the symmetric difference of the two source ranges.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_set_symmetric_difference(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result);

/**
 * Unites all of the elements that belong to one, but not both, of the sorted source ranges into a single, sorted destination range,
 * where the ordering criterion may be specified by a binary predicate.
 * @param it_first1     An input iterator addressing the position of the first element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the symmetric difference of the two source ranges.
 * @param it_last1      An input iterator addressing the position one past the last element in the first of two sorted source ranges
 *                      to be united and sorted into a single range representing the symmetric difference of the two source ranges.
 * @param it_first2     An input iterator addressing the position of the first element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the symmetric difference of the two source ranges.
 * @param it_last2      An input iterator addressing the position one past the last element in second of two consecutive sorted source ranges
 *                      to be united and sorted into a single range representing the symmetric difference of the two source ranges.
 * @param it_result     An output iterator addressing the position of the first element in the destination range where the two source ranges
 *                      are to be united into a single sorted range representing the symmetric difference of the two source ranges.
 * @param bfun_op       User-defined predicate function that defines the sense in which one element is greater than another.
 * @return  An output iterator addressing the position one past the last element in the sorted destination range representing the symmetric difference of the two source ranges.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_set_symmetric_difference_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, bfun_t bfun_op);

/**
 * Compares two elements and returns the larger of the two.
 * @param it_first      An input iterator addressing the first element.
 * @param it_second     An input iterator addressing the second element.
 * @return  An input iterator addressing the larger element.
 * @remarks The two iterators must be have same element type.
 */
extern input_iterator_t algo_max(input_iterator_t it_first, input_iterator_t it_second);

/**
 * Compares two elements and returns the larger of the two, where the ordering criterion may be specified by a binary predicate.
 * @param it_first      An input iterator addressing the first element.
 * @param it_second     An input iterator addressing the second element.
 * @param bfun_op       A binary predicate used to compare the two elements.
 * @return  An input iterator addressing the larger element.
 * @remarks The two iterators must be have same element type.
 */
extern input_iterator_t algo_max_if(input_iterator_t it_first, input_iterator_t it_second, bfun_t bfun_op);

/**
 * Compares two elements and returns the lesser of the two.
 * @param it_first      An input iterator addressing the first element.
 * @param it_second     An input iterator addressing the second element.
 * @return  An input iterator addressing the lesser element.
 * @remarks The two iterators must be have same element type.
 */
extern input_iterator_t algo_min(input_iterator_t it_first, input_iterator_t it_second);

/**
 * Compares two elements and returns the lesser of the two, where the ordering criterion may be specified by a binary predicate.
 * @param it_first      An input iterator addressing the first element.
 * @param it_second     An input iterator addressing the second element.
 * @param bfun_op       A binary predicate used to compare the two elements.
 * @return  An input iterator addressing the lesser element.
 * @remarks The two iterators must be have same element type.
 */
extern input_iterator_t algo_min_if(input_iterator_t it_first, input_iterator_t it_second, bfun_t bfun_op);

/**
 * Finds the first occurrence of largest element in a specified range.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched for the largest element.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched for the largest element.
 * @return  A forward iterator addressing the position of the first occurrence of the largest element in the range searched.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_max_element(forward_iterator_t it_first, forward_iterator_t it_last);

/**
 * Finds the first occurrence of largest element in a specified range where the ordering criterion specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched for the largest element.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched for the largest element.
 * @param bfun_op       User-defined predicate function that defines the sense in which one element is greater than another.
 * @return  A forward iterator addressing the position of the first occurrence of the largest element in the range searched.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_max_element_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op);

/**
 * Finds the first occurrence of smallest element in a specified range.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched for the largest element.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched for the largest element.
 * @return  A forward iterator addressing the position of the first occurrence of the smallest element in the range searched.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_min_element(forward_iterator_t it_first, forward_iterator_t it_last);

/**
 * Finds the first occurrence of smallest element in a specified range where the ordering criterion specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched for the largest element.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched for the largest element.
 * @param bfun_op       User-defined predicate function that defines the sense in which one element is greater than another.
 * @return  A forward iterator addressing the position of the first occurrence of the smallest element in the range searched.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_min_element_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op);

/**
 * Compares element by element between two sequences to determine which is lesser of the two.
 * @param it_first1     An input iterator addressing the position of the first element in the first range to be compared.
 * @param it_last1      An input iterator addressing the position one past the final element in the first range to be compared.
 * @param it_first2     An input iterator addressing the position of the first element in the second range to be compared.
 * @param it_last2      An input iterator addressing the position one past the final element in the second range to be compared.
 * @return  true if the first range is lexicographically less than the second range; otherwise false.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_lexicographical_compare(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2);

/**
 * Compares element by element between two sequences to determine which is lesser of the two.
 * @param it_first1     An input iterator addressing the position of the first element in the first range to be compared.
 * @param it_last1      An input iterator addressing the position one past the final element in the first range to be compared.
 * @param it_first2     An input iterator addressing the position of the first element in the second range to be compared.
 * @param it_last2      An input iterator addressing the position one past the final element in the second range to be compared.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  true if the first range is lexicographically less than the second range; otherwise false.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_lexicographical_compare_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    bfun_t bfun_op);

/**
 * Compares element by element between two sequences to determine the relation is less or equal or greater.
 * @param it_first1     An input iterator addressing the position of the first element in the first range to be compared.
 * @param it_last1      An input iterator addressing the position one past the final element in the first range to be compared.
 * @param it_first2     An input iterator addressing the position of the first element in the second range to be compared.
 * @param it_last2      An input iterator addressing the position one past the final element in the second range to be compared.
 * @return  negative number if the first range is lexicographically less than the second range;
 *          positive number if the first range is lexicographically greater than the second range;
 *          0 if the first range is lexicographically equal to the second range.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern int algo_lexicographical_compare_3way(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2);

/**
 * Compares element by element between two sequences to determine the relation is less or equal or greater.
 * @param it_first1     An input iterator addressing the position of the first element in the first range to be compared.
 * @param it_last1      An input iterator addressing the position one past the final element in the first range to be compared.
 * @param it_first2     An input iterator addressing the position of the first element in the second range to be compared.
 * @param it_last2      An input iterator addressing the position one past the final element in the second range to be compared.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @return  negative number if the first range is lexicographically less than the second range;
 *          positive number if the first range is lexicographically greater than the second range;
 *          0 if the first range is lexicographically equal to the second range.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern int algo_lexicographical_compare_3way_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    bfun_t bfun_op);

/**
 * Reorders the elements in a range so that the original ordering is replaced by the lexicographically next greater permutation if it exists.
 * @param it_first      A bidirectional iterator pointing to the position of the first element in the range to be permuted.
 * @param it_last       A bidirectional iterator pointing to the position one past the final element in the range to be permuted.
 * @return  true if the lexicographically next permutation exists and has replaced the original ordering of the range; otherwise false,
 *          in which case the ordering is transformed into the lexicographically smallest permutation.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_next_permutation(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last);

/**
 * Reorders the elements in a range so that the original ordering is replaced by the lexicographically next greater permutation if it exists,
 * where the sense of next specified with a binary predicate.
 * @param it_first      A bidirectional iterator pointing to the position of the first element in the range to be permuted.
 * @param it_last       A bidirectional iterator pointing to the position one past the final element in the range to be permuted.
 * @param bfun_op       User-defined predicate function that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @return  true if the lexicographically next permutation exists and has replaced the original ordering of the range; otherwise false,
 *          in which case the ordering is transformed into the lexicographically smallest permutation.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_next_permutation_if(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, bfun_t bfun_op);

/**
 * Reorders the elements in a range so that the original ordering is replaced by the lexicographically previous permutation if it exists.
 * @param it_first      A bidirectional iterator pointing to the position of the first element in the range to be permuted.
 * @param it_last       A bidirectional iterator pointing to the position one past the final element in the range to be permuted.
 * @return  true if the lexicographically next permutation exists and has replaced the original ordering of the range; otherwise false,
 *          in which case the ordering is transformed into the lexicographically largest permutation.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_prev_permutation(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last);

/**
 * Reorders the elements in a range so that the original ordering is replaced by the lexicographically previous permutation if it exists,
 * where the sense of next specified with a binary predicate.
 * @param it_first      A bidirectional iterator pointing to the position of the first element in the range to be permuted.
 * @param it_last       A bidirectional iterator pointing to the position one past the final element in the range to be permuted.
 * @param bfun_op       User-defined predicate function that defines the comparison criterion to be satisfied by successive elements in the ordering.
 * @return  true if the lexicographically next permutation exists and has replaced the original ordering of the range; otherwise false,
 *          in which case the ordering is transformed into the lexicographically largest permutation.
 * @remarks The range referened must be valid, otherwise the behavior is undefined.
 */
extern bool_t algo_prev_permutation_if(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, bfun_t bfun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_SORTING_H_ */
/** eof **/

