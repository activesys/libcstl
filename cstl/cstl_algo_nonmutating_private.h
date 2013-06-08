/*
 *  The interface of private non-mutating algorithm.
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

#ifndef _CSTL_ALGO_NONMUTATING_PRIVATE_H_
#define _CSTL_ALGO_NONMUTATING_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Locates the position of the first occurrence of an element in a range that has a specified value.
 * @param it_first      An input iterator addressing the position of the first element in the range to be searched
 *                      for the specified value.
 * @param it_last       An input iterator addressing the position one past the final element in the range to be
 *                      searched for the specified value.
 * @param ...           The value to be searched for.
 * @return An input iterator addressing the first occurrence of the specified value in the range being searched.
 *         Returns it_last if no such iterator exists.
 * @remarks This algorithm use equal operation for type of specificed value.
 */
extern input_iterator_t _algo_find(input_iterator_t it_first, input_iterator_t it_last, ...);
extern input_iterator_t _algo_find_varg(input_iterator_t it_first, input_iterator_t it_last, va_list val_elemlist);

/**
 * Returns the number of elements in a range whose values match a specified value.
 * @param it_first      An input iterator addressing the position of the first element in the range to be traversed.
 * @param it_last       An input iterator addressing the position one past the final element in the range to be traversed.
 * @param ...           The value of the elements to be counted.
 * @return  The number of elements in the range whose values match a specified value.
 * @remarks This algorithm use equal operation for type of specificed value.
 */
extern size_t _algo_count(input_iterator_t it_first, input_iterator_t it_last, ...);
extern size_t _algo_count_varg(input_iterator_t it_first, input_iterator_t it_last, va_list val_elemlist);

/**
 * Searches for the first subsequence in a range that of a specified number of elements having a particular value.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param t_count       The size of the subsequence being searched for.
 * @param ...           The value of the elements in the sequence being searched for.
 * @return  A forward iterator addressing the position of the first element of the first subsequence that matches the specified sequence.
 * @remarks The range must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t _algo_search_n(forward_iterator_t it_first, forward_iterator_t it_last, size_t t_count, ...);

/**
 * Searches for the first subsequence in a range that of a specified number of elements having a relation to that value as specified by a binary predicate.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be searched.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be searched.
 * @param t_count       The size of the subsequence being searched for.
 * @param bfun_op       User-defined predicate function object that defines the condition to be satisfied if two elements are to be taken as equivalent. 
 * @param ...           The value of the elements in the sequence being searched for.
 * @return  A forward iterator addressing the position of the first element of the first subsequence that is equivalent in a sense specified by a binary predicate.
 * @remarks The range must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t _algo_search_n_if(
    forward_iterator_t it_first, forward_iterator_t it_last, size_t t_count, bfun_t bfun_op, ...);
extern forward_iterator_t _algo_search_n_if_varg(
    forward_iterator_t it_first, forward_iterator_t it_last, size_t t_count, bfun_t bfun_op, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_NONMUTATING_PRIVATE_H_ */
/** eof **/

