/*
 *  The interface of numeric.
 *  Copyright (C)  2008 2009  Wangbo
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _CSTL_NUMERIC_H
#define _CSTL_NUMERIC_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* iota */
#define algo_iota(t_first, t_last, elem)\
    _algo_iota((t_first), (t_last), (elem))
/* accumulate */
#define algo_accumulate(t_first, t_last, elem, pv_output)\
    _algo_accumulate((t_first), (t_last), (pv_output), (elem))
#define algo_accumulate_if(t_first, t_last, elem, t_binary_op, pv_output)\
    _algo_accumulate_if((t_first), (t_last), (t_binary_op), (pv_output), (elem))
/* inner product */
#define algo_inner_product(t_first1, t_last1, t_first2, elem, pv_output)\
    _algo_inner_product((t_first1), (t_last1), (t_first2), (pv_output), (elem))
#define algo_inner_product_if(\
    t_first1, t_last1, t_first2, elem, t_binary_op1, t_binary_op2, pv_output)\
    _algo_inner_product_if(\
        (t_first1), (t_last1), (t_first2),\
        (t_binary_op1), (t_binary_op2),\
        (pv_output), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_power
 *        Parameters: in) t_iterator: iterator_t
 *                        the initialize iterator
 *                    in) t_power: size_t
 *                        the power count.
 *                    out) pv_output: void*
 *                        the output value.
 *           Returns: void
 *       Description: exponenitation.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_power(iterator_t t_iterator, size_t t_power, void* pv_output);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_power_if
 *        Parameters: in) t_iterator: t_iterator.
 *                        the initialize value.
 *                    in) t_power: size_t
 *                        the power count.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *                    out) pv_output: void*
 *                        the output value.
 *           Returns: void
 *       Description: exponenitation.
 *
 * ----------------------------------------------------------------------------
 */
extern void algo_power_if(
    iterator_t t_iterator,
    size_t t_power,
    binary_function_t t_binary_op,
    void* pv_output);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_adjacent_difference
 *        Parameters: in) t_first: t_iterator.
 *                        the first iterator.
 *                    in) t_last: iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *           Returns: output_iterator_t
 *       Description: calculate the difference of adjacent elements in the range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_adjacent_difference(
    input_iterator_t t_first,
    input_iterator_t t_last,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_adjacent_difference_if
 *        Parameters: in) t_first: t_iterator.
 *                        the first iterator.
 *                    in) t_last: iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: output_iterator_t
 *       Description: calculate the difference of adjacent elements in the range
 *                    [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_adjacent_difference_if(
    input_iterator_t t_first,
    input_iterator_t t_last,
    output_iterator_t t_result,
    binary_function_t t_binary_op);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_partial_sum
 *        Parameters: in) t_first: t_iterator.
 *                        the first iterator.
 *                    in) t_last: iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *           Returns: output_iterator_t
 *       Description: calculate the partial sum in the range [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_partial_sum(
    input_iterator_t t_first,
    input_iterator_t t_last,
    output_iterator_t t_result);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: algo_partial_sum_if
 *        Parameters: in) t_first: t_iterator.
 *                        the first iterator.
 *                    in) t_last: iterator_t
 *                        the last iterator.
 *                    in) t_result: output_iterator_t
 *                        the output iterator.
 *                    in) t_binary_op: binary_function_t
 *                        binary function.
 *           Returns: output_iterator_t
 *       Description: calculate the partial sum in the range [t_first, t_last).
 *
 * ----------------------------------------------------------------------------
 */
extern output_iterator_t algo_partial_sum_if(
    input_iterator_t t_first,
    input_iterator_t t_last,
    output_iterator_t t_result,
    binary_function_t t_binary_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_NUMERIC_H */
/** eof **/

