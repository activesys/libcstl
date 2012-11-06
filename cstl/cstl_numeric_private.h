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
/**
 * Assigns sequentially increasing values to a range.
 * @param it_first      A forward iterator addressing the first element int the range to be assigned.
 * @param it_last       A forward iterator addressing the last element int the range to be assigned.
 * @param ...           Assigned value.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void _algo_iota(forward_iterator_t it_first, forward_iterator_t it_last, ...);
extern void _algo_iota_varg(forward_iterator_t it_first, forward_iterator_t it_last, va_list val_elemlist);

/**
 * Computes the sum of all the elements in a specified range including some initial value by computing successive partial sums or
 * computes the result of successive partial results similarly obtained from using a specified binary operation other than the sum.
 * @param it_first      An input iterator addressing the first element in the range to be summed or combined according to a specified binary operation.
 * @param it_last       An input iterator addressing the last element in the range to be summed or combined according to a specified binary operation
 *                      that is one position beyond the final element actually included in the iterated accumulation.
 * @param pv_output     A sum result.
 * @param ...           An initial value to which each element is in turn added or combined with according to a specified binary operation.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void _algo_accumulate(input_iterator_t it_first, input_iterator_t it_last, void* pv_output, ...);

/**
 * Computes the sum of all the elements in a specified range including some initial value by computing successive partial sums or
 * computes the result of successive partial results similarly obtained from using a specified binary operation other than the sum.
 * @param it_first      An input iterator addressing the first element in the range to be summed or combined according to a specified binary operation.
 * @param it_last       An input iterator addressing the last element in the range to be summed or combined according to a specified binary operation
 *                      that is one position beyond the final element actually included in the iterated accumulation.
 * @param bfun_op       The binary operation that is to be applied to the each element in the specified range and the result of its previous applications.
 * @param pv_output     A sum result.
 * @param ...           An initial value to which each element is in turn added or combined with according to a specified binary operation.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern void _algo_accumulate_if(input_iterator_t it_first, input_iterator_t it_last, binary_function_t bfun_op, void* pv_output, ...);
extern void _algo_accumulate_if_varg(input_iterator_t it_first, input_iterator_t it_last, binary_function_t bfun_op, void* pv_output, va_list val_elemlist);

extern void _algo_inner_product(
    input_iterator_t t_first1, input_iterator_t it_last1, input_iterator_t t_first2,
    void* pv_output, ...);
extern void _algo_inner_product_if(
    input_iterator_t t_first1, input_iterator_t it_last1, input_iterator_t t_first2,
    binary_function_t bfun_op1, binary_function_t bfun_op2, void* pv_output, ...);
extern void _algo_inner_product_if_varg(
    input_iterator_t t_first1, input_iterator_t it_last1, input_iterator_t t_first2,
    binary_function_t bfun_op1, binary_function_t bfun_op2,
    void* pv_output, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_NUMERIC_PRIVATE_H_ */
/** eof **/

