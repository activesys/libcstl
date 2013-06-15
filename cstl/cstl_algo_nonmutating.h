/*
 *  The interface of non-mutating algorithm.
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

#ifndef _CSTL_ALGO_NONMUTATING_H_
#define _CSTL_ALGO_NONMUTATING_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/**
 * Locates the position of the first occurrence of an element in a range that has a specified value.
 * @param it_first      An input iterator addressing the position of the first element in the range to be searched
 *                      for the specified value.
 * @param it_last       An input iterator addressing the position one past the final element in the range to be
 *                      searched for the specified value.
 * @param elem          The value to be searched for.
 * @return An input iterator addressing the first occurrence of the specified value in the range being searched.
 *         Returns it_last if no such iterator exists.
 * @remarks This algorithm use equal operation for type of specificed value.
 */
#define algo_find(it_first, it_last, elem) _algo_find((it_first), (it_last), (elem))

/**
 * Returns the number of elements in a range whose values match a specified value.
 * @param it_first      An input iterator addressing the position of the first element in the range to be traversed.
 * @param it_last       An input iterator addressing the position one past the final element in the range to be traversed.
 * @param elem          The value of the elements to be counted.
 * @return  The number of elements in the range whose values match a specified value.
 * @remarks This algorithm use equal operation for type of specificed value.
 */
#define algo_count(it_first, it_last, elem) _algo_count((it_first), (it_last), (elem))

/**
 * Searches for the first subsequence in a range that of a specified number of elements having a particular value.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param t_count       The size of the subsequence being searched for.
 * @param elem          The value of the elements in the sequence being searched for.
 * @return  A forward iterator addressing the position of the first element of the first subsequence that matches the specified sequence.
 * @remarks The range must be valid, otherwise the behavior is undefined.
 */
#define algo_search_n(it_first, it_last, t_count, elem) _algo_search_n((it_first), (it_last), (t_count), (elem))

/**
 * Searches for the first subsequence in a range that of a specified number of elements having a relation to that value as specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param t_count       The size of the subsequence being searched for.
 * @param bfun_op       User-defined predicate function object that defines the condition to be satisfied if two elements are to be taken as equivalent. 
 * @param elem          The value of the elements in the sequence being searched for.
 * @return  A forward iterator addressing the position of the first element of the first subsequence that is equivalent in a sense specified by a binary predicate.
 * @remarks The range must be valid, otherwise the behavior is undefined.
 */
#define algo_search_n_if(it_first, it_last, t_count, elem, bfun_op) _algo_search_n_if((it_first), (it_last), (t_count), (bfun_op), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Applies a unary function to each element in a range.
 * @param it_first        An input iterator addressing the position of the first element in the range to be operated on.
 * @param it_last       An input iterator addressing the position one past the final element in the range operated on.
 * @param ufun_op       User-defined unary function that is applied to each element in the range.
 * @return void.
 * @remarks the range must be valid, other the behavior is undefined. if unfun_op == NULL, then the default unary function
 *          that do nothing will be used. the range must be not belong to relation container, when the unary function
 *          that modify element in the range is used in this alogrithm function.
 */
extern void algo_for_each(input_iterator_t it_first, input_iterator_t it_last, ufun_t ufun_op);

/**
 * Locates the position of the first occurrence of an element in a range that satisfies a specified condition.
 * @param it_first      An input iterator addressing the position of the first element in the range to be searched.
 * @param it_second     An input iterator addressing the position one past the final element in the range to be searched.
 * @param ufun_op       User-defined predicate function that defines the condition to be satisfied by the element being searched for.
 * @return  An input iterator that addresses the first element in the range that satisfies the condition specified by the predicate.
 * @remarks The range must be valid, otherwise the behavior is undefined. if ufun_op == NULL, then default unary function that
 *          do nothing will be used. The predicate function must be not modify element of the range, otherwise the behavior is
 *          undefined.
 */
extern input_iterator_t algo_find_if(input_iterator_t it_first, input_iterator_t it_last, ufun_t ufun_op);

/**
 * Searches for two adjacent elements that are equal.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @return  A forward iterator to the first element of the adjacent pair that are equal to each other. Otherwise, an iterator
 *          pointing to it_last is returned.
 * @remarks The range must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_adjacent_find(forward_iterator_t it_first, forward_iterator_t it_last);

/**
 * Searches for two adjacent elements that satisfy a specificed condition.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param bfun_op       The binary predicate giving the condition to be satisfied by the values of the adjacent elements
 *                      in the range being searched.
 * @return  A forward iterator to the first element of the adjacent pair that satisfy the condition that given by the binary
 *          predicate. Otherwise, an iterator pointing to it_last is returned.
 * @remarks The range must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_adjacent_find_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op);

/**
 * Searches for the first occurrence of any of several values within a target range.
 * @param it_first1     A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last1      A forward iterator addressing the position one past the final element in the range to be searched.
 * @param it_first2     A forward iterator addressing the position of the first element in the range to be matched.
 * @param it_last2      A forward iterator addressing the position one past the final element in the range to be matched.
 * @return  A forward iterator addressing the position of the first element of the first subsequence that matches the specified sequence.
 * @remakrs The range to be searched and the range to be matched must be valid, otherwise the behavior is undefined. 
 */
extern input_iterator_t algo_find_first_of(
    input_iterator_t it_first1, input_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2);

/**
 * Searches for the first occurrence of any of several elements that are equivalent in a sense specified by
 * a binary predicate to a specified set of the elements.
 * @param it_first1     A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last1      A forward iterator addressing the position one past the final element in the range to be searched.
 * @param it_first2     A forward iterator addressing the position of the first element in the range to be matched.
 * @param it_last2      A forward iterator addressing the position one past the final element in the range to be matched.
 * @param bfun_op       User-defined predicate function that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  A forward iterator addressing the position of the first element of the first subsequence that matches the specified sequence.
 * @remakrs The range to be searched and the range to be matched must be valid, otherwise the behavior is undefined. 
 */
extern input_iterator_t algo_find_first_of_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2,
    bfun_t bfun_op);

/**
 * Returns the number of elements in a range whose values satisfy a specified condition.
 * @param it_first      An input iterator addressing the position of the first element in the range to be searched.
 * @param it_last       An input iterator addressing the position one past the final element in the range to be searched.
 * @param ufun_op       User-defined predicate function that defines the condition to be satisfied if an element is to be counted.
 * @return  The number of elements that satisfy the condition specified by the predicate.
 * @remarks The range must be valid, otherwise the behavior is undefined.
 */
extern size_t algo_count_if(input_iterator_t it_first, input_iterator_t it_last, ufun_t ufun_op);

/**
 * Compares two ranges element by element either for equality and locates the first position where a difference occurs.
 * @param it_first1     An input iterator addressing the position of the first element in the first range to be tested.
 * @param it_last1      An input iterator addressing the position one past the final element in the first range to be tested.
 * @param it_first2     An input iterator addressing the position of the first element in the second range to be tested.
 * @return  A range of iterators addressing the positions of the mismatch in the two ranges, the it_begin of the result
 *          range point to the position in the first range, and the it_end of the result range point to the position
 *          in the second range. If there is no difference between two input range, then the it_begin of the result
 *          range equal to it_last1.
 * @remarks Two input range must be valid, and must be contain same element type, otherwise the behavior is undefined. The second
 *          input reange must be large enough, if its length is less then the first, the behavior is undefined.
 */
extern range_t algo_mismatch(input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2);

/**
 * Compares two ranges element by element either for equivalent in a sense specified by a binary predicate and locates
 * the first position where a difference occurs.
 * @param it_first1     An input iterator addressing the position of the first element in the first range to be tested.
 * @param it_last1      An input iterator addressing the position one past the final element in the first range to be tested.
 * @param it_first2     An input iterator addressing the position of the first element in the second range to be tested.
 * @param bfun_op       User-defined predicate function that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  A range of iterators addressing the positions of the mismatch in the two ranges, the it_begin of the result
 *          range point to the position in the first range, and the it_end of the result range point to the position
 *          in the second range. If there is no difference between two input range, then the it_begin of the result
 *          range equal to it_last1.
 * @remarks Two input range must be valid, and must be contain same element type, otherwise the behavior is undefined. The second
 *          input reange must be large enough, if its length is less then the first, the behavior is undefined.
 */
extern range_t algo_mismatch_if(
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, bfun_t bfun_op);

/**
 * Compares two ranges element by element either for equality.
 * @param it_first1     An input iterator addressing the position of the first element in the first range to be tested.
 * @param it_last1      An input iterator addressing the position one past the final element in the first range to be tested.
 * @param it_first1     An input iterator addressing the position of the first element in the second range to be tested.
 * @return  true if and only if the ranges are identical; otherwise, false.
 * @remarks Two input range must be valid, and must be contain same element type, otherwise the behavior is undefined. The second
 *          input range must be large enough, if its length is less then the first, the behavior is undefined.
 */
extern bool_t algo_equal(input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2);

/**
 * Compares two ranges element by element either for equivalence in a sense specified by a binary predicate.
 * @param it_first1     An input iterator addressing the position of the first element in the first range to be tested.
 * @param it_last1      An input iterator addressing the position one past the final element in the first range to be tested.
 * @param it_first1     An input iterator addressing the position of the first element in the second range to be tested.
 * @param bfun_op       User-defined predicate function that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  true if and only if the ranges are equivalent under the binary predicate when compared element by element; otherwise, false.
 * @remarks Two input range must be valid, and must be contain same element type, otherwise the behavior is undefined. The second
 *          input range must be large enough, if its length is less then the first, the behavior is undefined.
 */
extern bool_t algo_equal_if(
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, bfun_t bfun_op);

/**
 * Searches for the first occurrence of a sequence within a target range whose elements are equal to those in a given sequence.
 * @param it_first1     A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last1      A forward iterator addressing the position one past the final element in the range to be searched.
 * @param it_first2     A forward iterator addressing the position of the first element in the range to be matched.
 * @param it_last2      A forward iterator addressing the position one past the final element in the range to be matched.
 * @return  A forward iterator addressing the position of the first element of the first subsequence that matches the specified sequence.  
 * @remarks Two input range must be valid, and must be contain same element type, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_search(
    forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2, forward_iterator_t it_last2);

/**
 * Searches for the first occurrence of a sequence within a target range whose elements or whose elements are equivalent in a sense specified
 * by a binary predicate to the elements in the given sequence.
 * @param it_first1     A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last1      A forward iterator addressing the position one past the final element in the range to be searched.
 * @param it_first2     A forward iterator addressing the position of the first element in the range to be matched.
 * @param it_last2      A forward iterator addressing the position one past the final element in the range to be matched.
 * @param bfun_op       User-defined predicate function object that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  A forward iterator addressing the position of the first element of the first subsequence that is equivalent in a sense specified
 *          by a binary predicate.
 * @remarks Two input range must be valid, and must be contain same element type, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_search_if(
    forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2, forward_iterator_t it_last2,
    bfun_t bfun_op);

/**
 * Looks in a range for the last subsequence that is identical to a specified sequence.
 * @param it_first1     A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last1      A forward iterator addressing the position one past the final element in the range to be searched.
 * @param it_first2     A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last2      A forward iterator addressing the position one past the final element in the range to be searched.
 * @return  A forward iterator addressing the position of the first element of the last subsequence that matches the specified sequence.
 * @remarks Two input ranges must be valid, and must be contain same element type, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_search_end(
    forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2, forward_iterator_t it_last2);
extern forward_iterator_t algo_find_end(
    forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2, forward_iterator_t it_last2);

/**
 * Looks in a range for the last subsequence that is equivalent in a sense specified by a binary predicate.
 * @param it_first1     A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last1      A forward iterator addressing the position one past the final element in the range to be searched.
 * @param it_first2     A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last2      A forward iterator addressing the position one past the final element in the range to be searched.
 * @param bfun_op       User-defined predicate function object that defines the condition to be satisfied if two elements are to be taken as equivalent.
 * @return  A forward iterator addressing the position of the first element of the last subsequence that is equivalent in a sense specified by a binary predicate.
 * @remarks Two input ranges must be valid, and must be contain same element type, otherwise the behavior is undefined.
 */
extern forward_iterator_t algo_search_end_if(
    forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2, forward_iterator_t it_last2,
    bfun_t bfun_op);
extern forward_iterator_t algo_find_end_if(
    forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2, forward_iterator_t it_last2,
    bfun_t bfun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_NONMUTATING_H_ */
/** eof **/

