/*
 *  The private interface of numeric.
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

#ifndef _CSTL_NUMERIC_PRIVATE_H_
#define _CSTL_NUMERIC_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Private numeric algorithm functions.
 */
extern void _algo_iota(forward_iterator_t t_first, forward_iterator_t t_last, ...);
extern void _algo_iota_varg(
    forward_iterator_t t_first, forward_iterator_t t_last, va_list val_elemlist);
extern void _algo_accumulate(
    input_iterator_t t_first, input_iterator_t t_last, void* pv_output, ...);
extern void _algo_accumulate_if(
    input_iterator_t t_first, input_iterator_t t_last, binary_function_t t_binary_op,
    void* pv_output, ...);
extern void _algo_accumulate_if_varg(
    input_iterator_t t_first, input_iterator_t t_last, binary_function_t t_binary_op,
    void* pv_output, va_list val_elemlist);
extern void _algo_inner_product(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    void* pv_output, ...);
extern void _algo_inner_product_if(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    binary_function_t t_binary_op1, binary_function_t t_binary_op2, void* pv_output, ...);
extern void _algo_inner_product_if_varg(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    binary_function_t t_binary_op1, binary_function_t t_binary_op2,
    void* pv_output, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_NUMERIC_PRIVATE_H_ */
/** eof **/

