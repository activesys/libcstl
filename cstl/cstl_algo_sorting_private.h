/*
 *  The interface of private sorting algorithm.
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

#ifndef _CSTL_ALGO_SORTING_PRIVATE_H_
#define _CSTL_ALGO_SORTING_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Finds the position of the first element in an ordered range that has a value greater than or equivalent to a specified value.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param ...           The value whose first position or possible first position is being searched for in the ordered range.
 * @return  A forward iterator at the position of the first element in an ordered range with a value that is greater than or equivalent to a specified value.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t _algo_lower_bound(forward_iterator_t it_first, forward_iterator_t it_last, ...);

/**
 * Finds the position of the first element in an ordered range that has a value greater than or equivalent to a specified value,
 * where the ordering criterion may be specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @param ...           The value whose first position or possible first position is being searched for in the ordered range.
 * @return  A forward iterator at the position of the first element in an ordered range with a value that is greater than or equivalent to a specified value.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t _algo_lower_bound_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, ...);
extern forward_iterator_t _algo_lower_bound_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, va_list val_elemlist);

/**
 * Finds the position of the first element in an ordered range that has a value that is greater than a specified value.
 * @param it_first      The position of the first element in the range to be searched.
 * @param it_last       The position one past the final element in the range to be searched.
 * @param ...           The value in the ordered range that needs to be exceeded by the value of the element addressed by the iterator returned.
 * @return  A forward iterator to the position of the first element that has a value greater than a specified value.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t _algo_upper_bound(forward_iterator_t it_first, forward_iterator_t it_last, ...);

/**
 * Finds the position of the first element in an ordered range that has a value that is greater than a specified value,
 * where the ordering criterion may be specified by a binary predicate.
 * @param it_first      The position of the first element in the range to be searched.
 * @param it_last       The position one past the final element in the range to be searched.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @param ...           The value in the ordered range that needs to be exceeded by the value of the element addressed by the iterator returned.
 * @return  A forward iterator to the position of the first element that has a value greater than a specified value.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t _algo_upper_bound_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, ...);
extern forward_iterator_t _algo_upper_bound_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, va_list val_elemlist);

/**
 * Finds a pair of positions in an ordered range, the first less than or equivalent to the position of a specified element and
 * the second greater than the element's position.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param ...           The value in the ordered range that needs to be equivalent to the value of the element
 *                      addressed by the first component of the pair returned and that needs to be less than the value of the element
 *                      addressed by the second component of that pair returns.
 * @return  A range of forward iterators addressing two positions in an ordered range in which the first component of the range refers to the position
 *          where an element is or would be if it had a value that is less than or equivalent to a specified value and the second component of the range
 *          refers to the first position where an element has a value that is greater than the value specified.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
extern range_t _algo_equal_range(forward_iterator_t it_first, forward_iterator_t it_last, ...);

/**
 * Finds a pair of positions in an ordered range, the first less than or equivalent to the position of a specified element and
 * the second greater than the element's position, where the sense of equivalence or ordering used to establish the positions
 * in the sequence may be specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param ...           The value in the ordered range that needs to be equivalent to the value of the element
 *                      addressed by the first component of the pair returned and that needs to be less than the value of the element
 *                      addressed by the second component of that pair returns.
 * @return  A range of forward iterators addressing two positions in an ordered range in which the first component of the range refers to the position
 *          where an element is or would be if it had a value that is less than or equivalent to a specified value and the second component of the range
 *          refers to the first position where an element has a value that is greater than the value specified, where the sense of equivalence or ordering
 *          may be specified by a binary predicate.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
extern range_t _algo_equal_range_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, ...);
extern range_t _algo_equal_range_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, va_list val_elemlist);

/**
 * Tests whether there is an element in a sorted range that is equal to a specified value.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param ...           The value required to be matched by the value of the element.
 * @return  true if an element is found in the range that is equal or equivalent to the specified value; otherwise, false.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
extern bool_t _algo_binary_search(forward_iterator_t it_first, forward_iterator_t it_last, ...);

/**
 * Tests whether there is an element in a sorted range that is equivalent to it in a sense specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param bfun_op       User-defined predicate function that defines sense in which one element is less than another.
 * @param ...           The value that must satisfy the condition with the element value specified by the binary predicate.
 * @return  true if an element is found in the range that is equal or equivalent to the specified value; otherwise, false.
 * @remarks The sorted source range referenced must be valid, otherwise the behavior is undefined.
 */
extern bool_t _algo_binary_search_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, ...);
extern bool_t _algo_binary_search_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_SORTING_PRIVATE_H_ */
/** eof **/

