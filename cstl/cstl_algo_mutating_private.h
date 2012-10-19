/*
 *  The interface of private mutating algorithm.
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

/**
 * Replace element that pointed by iterator with specific value.
 * @param it_iter       A forward iterator pointing to the element are being replaced.
 * @param ...           The new value being assigned to the elements with the old value.
 * @return  void.
 * @remarks The iterator must be valid, otherwise the behavior is undefined.
 */
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
extern void _algo_replace_if(forward_iterator_t it_first, forward_iterator_t it_last, unary_function_t ufun_op, ...);
extern void _algo_replace_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, unary_function_t ufun_op, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_MUTATING_PRIVATE_H_ */
/** eof **/

