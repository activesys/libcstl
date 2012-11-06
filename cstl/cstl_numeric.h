/*
 *  The interface of numeric.
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

#ifndef _CSTL_NUMERIC_H_
#define _CSTL_NUMERIC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * NOTE : The numeric algorithm functions are valid for c built-in types except c-string!
 *        You can't use numeric algorithm functions with cstl built-in types and user-defined
 *        types that whose numeric operation functions was not overwritted, but you can use
 *        _if style numeric algorithm functions that use user-defined numeric operation
 *        functions for that types.
 */

/** include section **/

/** constant declaration and macro section **/
/**
 * Assigns sequentially increasing values to a range.
 * @param it_first      A forward iterator addressing the first element int the range to be assigned.
 * @param it_last       A forward iterator addressing the last element int the range to be assigned.
 * @param elem          Assigned value.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
#define algo_iota(it_first, it_last, elem) _algo_iota((it_first), (it_last), (elem))

/**
 * Computes the sum of all the elements in a specified range including some initial value by computing successive partial sums or
 * computes the result of successive partial results similarly obtained from using a specified binary operation other than the sum.
 * @param it_first      An input iterator addressing the first element in the range to be summed or combined according to a specified binary operation.
 * @param it_last       An input iterator addressing the last element in the range to be summed or combined according to a specified binary operation
 *                      that is one position beyond the final element actually included in the iterated accumulation.
 * @param elem          An initial value to which each element is in turn added or combined with according to a specified binary operation.
 * @param pv_output     A sum result.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
#define algo_accumulate(it_first, it_last, elem, pv_output) _algo_accumulate((it_first), (it_last), (pv_output), (elem))

/**
 * Computes the sum of all the elements in a specified range including some initial value by computing successive partial sums or
 * computes the result of successive partial results similarly obtained from using a specified binary operation other than the sum.
 * @param it_first      An input iterator addressing the first element in the range to be summed or combined according to a specified binary operation.
 * @param it_last       An input iterator addressing the last element in the range to be summed or combined according to a specified binary operation
 *                      that is one position beyond the final element actually included in the iterated accumulation.
 * @param elem          An initial value to which each element is in turn added or combined with according to a specified binary operation.
 * @param bfun_op       The binary operation that is to be applied to the each element in the specified range and the result of its previous applications.
 * @param pv_output     A sum result.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
#define algo_accumulate_if(it_first, it_last, elem, t_binary_op, pv_output) _algo_accumulate_if((it_first), (it_last), (t_binary_op), (pv_output), (elem))
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
 * Numeric algorithm functions.
 */
extern void algo_power(iterator_t t_iterator, size_t t_power, void* pv_output);
extern void algo_power_if(
    iterator_t t_iterator, size_t t_power, binary_function_t t_binary_op, void* pv_output);
extern output_iterator_t algo_adjacent_difference(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t t_result);
extern output_iterator_t algo_adjacent_difference_if(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t t_result,
    binary_function_t t_binary_op);
extern output_iterator_t algo_partial_sum(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t t_result);
extern output_iterator_t algo_partial_sum_if(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t t_result,
    binary_function_t t_binary_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_NUMERIC_H_ */
/** eof **/

