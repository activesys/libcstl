/*
 *  The interface of non-mutating algorithm.
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

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Applies a unary function to each element in a range.
 * @param it_first		An input iterator addressing the position of the first element in the range to be operated on.
 * @param it_last       An input iterator addressing the position one past the final element in the range operated on.
 * @param ufun_op       User-defined unary function that is applied to each element in the range.
 * @return void.
 * @remarks the range must be valid, other the behavior is undefined. if unfun_op == NULL, then the default unary function
 *          that do nothing will be used. the range must be not belong to relation container, when the unary function
 *          that modify element in the range is used in this alogrithm function.
 */
extern void algo_for_each(
	input_iterator_t it_first, input_iterator_t it_last, unary_function_t ufun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_NONMUTATING_H_ */
/** eof **/

