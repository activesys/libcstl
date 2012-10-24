/*
 *  The interface of auxiliary mutating algorithm.
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

#ifndef _CSTL_ALGO_MUTATING_AUX_H_
#define _CSTL_ALGO_MUTATING_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Exchanges the elements in two adjacent ranges with forward iterator type.
 * @param it_first      A forward iterator addressing the position of the first element in the range to be rotated.
 * @param it_middle     A forward iterator defining the boundary within the range that addresses the position of the first element
 *                      in the second part of the range whose elements are to be exchanged with those in the first part of the range.
 * @param it_last       A forward iterator addressing the position one past the final element in the range to be rotated.
 * @return  void.
 * @remarks The ranges referenced must be valid, otherwise the behavior is undefined.
 */
extern void _algo_rotate_forward(forward_iterator_t it_first, forward_iterator_t it_middle, forward_iterator_t it_last);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_MUTATING_AUX_H_ */
/** eof **/

