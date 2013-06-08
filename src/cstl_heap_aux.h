/*
 *  The interface of auxiliary heap.
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

#ifndef _CSTL_HEAP_AUX_H_
#define _CSTL_HEAP_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Adjust specific position element into a heap.
 * @param it_first      A random-access iterator addressing the position of the first element in the range to be converted into a heap.
 * @param it_last       A random-access iterator addressing the position one past the final element in the range to be converted into a heap.
 * @param it_parent     A random-access iterator addressing the position of the parent element in the range to be converted into a heap.
 * @param bfun_op       User-defined predicate function object that defines sense in which one element is less than another.
 * @return  void.
 * @remarks The referenced range must be valid, it_parent must belong to [it_first, it_last), otherwise the behavior is undefined.
 */
extern void _algo_adjust_heap(
    random_access_iterator_t it_first, random_access_iterator_t it_last, random_access_iterator_t it_parent, bfun_t bfun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HEAP_AUX_H_ */
/** eof **/

