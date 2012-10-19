/*
 *  The private interface of algorithm.
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

#ifndef _CSTL_ALGO_PRIVATE_H_
#define _CSTL_ALGO_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * Remove algorithm.
 */
extern output_iterator_t _algo_remove_copy(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, ...);
extern output_iterator_t _algo_remove_copy_varg(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, va_list val_elemlist);
extern forward_iterator_t _algo_remove(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);
extern forward_iterator_t _algo_remove_varg(
    forward_iterator_t t_first, forward_iterator_t t_last, va_list val_elemlist);

/*
 * Replace algorithm.
 */
extern void _algo_replace_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op, ...);
extern void _algo_replace_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op, va_list val_elemlist);
extern output_iterator_t _algo_replace_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op, ...);
extern output_iterator_t _algo_replace_copy_if_varg(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op,
    va_list val_elemlist);

/*
 * Lower bound, upper bound and equal range algorithm.
 */
extern forward_iterator_t _algo_lower_bound(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);
extern forward_iterator_t _algo_lower_bound_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...);
extern forward_iterator_t _algo_lower_bound_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist);
extern forward_iterator_t _algo_upper_bound(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);
extern forward_iterator_t _algo_upper_bound_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...);
extern forward_iterator_t _algo_upper_bound_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist);
extern range_t _algo_equal_range(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);
extern range_t _algo_equal_range_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...);
extern range_t _algo_equal_range_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist);

/*
 * Search algorithm.
 */
extern bool_t _algo_binary_search(
    forward_iterator_t t_first, forward_iterator_t t_last, ...);
extern bool_t _algo_binary_search_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...);
extern bool_t _algo_binary_search_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_ALGO_PRIVATE_H_ */
/** eof **/

