/*
 *  The private interface of base algorithm.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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

#ifndef _CSTL_ALGOBASE_PRIVATE_H
#define _CSTL_ALGOBASE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Fill algorithm.
 */
extern void _algo_fill(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);
extern void _algo_fill_varg(
    forward_iterator_t t_first, forward_iterator_t t_last, va_list val_elemlist);
extern output_iterator_t _algo_fill_n(
    forward_iterator_t t_first, size_t t_fillsize, ...);
extern output_iterator_t _algo_fill_n_varg(
    forward_iterator_t t_first, size_t t_fillsize, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGOBASE_PRIVATE_H */
/** eof **/

