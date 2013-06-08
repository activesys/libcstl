/*
 *  The interface of private mutating algorithm.
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

#ifndef _CSTL_ALGO_MUTATING_PRIVATE_H_
#define _CSTL_ALGO_MUTATING_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Replace element that pointed by iterator with specific value.
 * @param it_iter       A forward iterator pointing to the element are being replaced.
 * @param ...           The new value being assigned to the elements with the old value.
 * @return  void.
 * @remarks The iterator must be valid, otherwise the behavior is undefined.
 */
extern void _algo_replace_once(forward_iterator_t it_iter, ...);
extern void _algo_replace_once_varg(forward_iterator_t it_iter, va_list val_elemlist);

/**
 * Examines each element in a range and replaces it if it satisfies a specified predicate.
 * @param it_first      A forward iterator pointing to the position of the first element in the range from which elements are being replaced.
 * @param it_last       An iterator pointing to the position one past the final element in the range from which elements are being replaced.
 * @param ufun_op       The unary predicate that must be satisfied is the value of an element is to be replaced.
 * @param ...           The new value being assigned to the elements whose old value satisfies the predicate.
 * @return  void.
 * @remarks The range referenced must be valid, otherwise the behavior is undefined.
 */
extern void _algo_replace_if(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op, ...);
extern void _algo_replace_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op, va_list val_elemlist);

/**
 * Examines each element in a source range and replaces it if it satisfies a specified predicate while copying the result into a new destination range.
 * @param it_first      An input iterator pointing to the position of the first element in the range from which elements are being replaced.
 * @param it_last       An input iterator pointing to the position one past the final element in the range from which elements are being replaced.
 * @param it_result     An output iterator pointing to the position of the first element in the destination range to which elements are being copied.
 * @param ufun_op       The unary predicate that must be satisfied is the value of an element is to be replaced.
 * @param ...          The new value being assigned to the elements whose old value satisfies the predicate.
 * @return  An output iterator pointing to the position one past the final element in the destination range to where the altered sequence of elements is being copied.
 * @remarks The source and destination ranges referenced must not overlap and must both be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t _algo_replace_copy_if(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, ufun_t ufun_op, ...);
extern output_iterator_t _algo_replace_copy_if_varg(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, ufun_t ufun_op, va_list val_elemlist);

/**
 * Assigns the same new value to every element in a specified range.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be traversed.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be traversed.
 * @param ...           The value to be assigned to elements in the range [it_first, it_last).
 * @return  void.
 * @remarks The destination range must be valid, otherwise the behavior is undefined.
 */
extern void _algo_fill(forward_iterator_t it_first, forward_iterator_t it_last, ...);
extern void _algo_fill_varg(forward_iterator_t it_first, forward_iterator_t it_last, va_list val_elemlist);

/**
 * Assigns a new value to a specified number of elements in a range beginning with a particular element.
 * @param it_first      An output iterator addressing the position of the first element in the range to be assigned the value elem.
 * @param t_fillsize    The number of elements to be assigned the value.
 * @param ...           The value to be assigned to elements in the range [it_first, it_first + t_fillsize).
 * @return  An output iterator pointing to the position one past the final element in the destination range to where the altered sequence of elements is being filled.
 * @remarks The destination range must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t _algo_fill_n(forward_iterator_t it_first, size_t t_fillsize, ...);
extern output_iterator_t _algo_fill_n_varg(forward_iterator_t it_first, size_t t_fillsize, va_list val_elemlist);

/**
 * Eliminates a specified value from a given range without disturbing the order of the remaining elements and returning the end of a new range free of the specified value.
 * @param it_first      A forward iterator addressing the position of the first element in the range from which elements are being removed.
 * @param it_last       A forward iterator addressing the position one past the final element in the range from which elements are being removed.
 * @param ...           The value that is to be removed from the range.
 * @return  A forward iterator addressing the new end position of the modified range, one past the final element of the remnant sequence free of the specified value.
 * @remarks The destination range must be valid, otherwise the behavior is undefined.
 */
extern forward_iterator_t _algo_remove(forward_iterator_t it_first, forward_iterator_t it_last, ...);
extern forward_iterator_t _algo_remove_varg(forward_iterator_t it_first, forward_iterator_t it_last, va_list val_elemlist);

/**
 * Copies elements from a source range to a destination range, except that elements of a specified value are not copied,
 * without disturbing the order of the remaining elements and returning the end of a new destination range.
 * @param it_first      An input iterator addressing the position of the first element in the range from which elements are being removed.
 * @param it_last       An input iterator addressing the position one past the final element in the range from which elements are being removed.
 * @param it_result     An output iterator addressing the position of the first element in the destination range to which elements are being removed.
 * @param ...           The value that is to be removed from the range.
 * @return  A forward iterator addressing the new end position of the destination range, one past the final element of the copy of the remnant 
 *          sequence free of the specified value.
 * @remarks The source and destination ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t _algo_remove_copy(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, ...);
extern output_iterator_t _algo_remove_copy_varg(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_MUTATING_PRIVATE_H_ */
/** eof **/

