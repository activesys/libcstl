/*
 *  The interface of numeric.
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
#define algo_accumulate_if(it_first, it_last, elem, bfun_op, pv_output) _algo_accumulate_if((it_first), (it_last), (bfun_op), (pv_output), (elem))

/**
 * Computes the sum of the element-wise product of two ranges and adds it to a specified initial value.
 * @param it_first1     An input iterator addressing the first element in the first range whose inner product or
 *                      generalized inner product with the second range is to be computed.
 * @param it_last1      An input iterator addressing the last element in the first range whose inner product or
 *                      generalized inner product with the second range is to be computed.
 * @param it_first2     An input iterator addressing the first element in the second range whose inner product or
 *                      generalized inner product with the first range is to be computed.
 * @param elem          An initial value to which the inner product or generalized inner product between the ranges is to be added.
 * @param pv_output     A product result.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
#define algo_inner_product(it_first1, it_last1, it_first2, elem, pv_output)\
    _algo_inner_product((it_first1), (it_last1), (it_first2), (pv_output), (elem))

/**
 * Computes the result of a generalized procedure where the sum and product binary operations are replaced by other specified binary operations.
 * @param it_first1     An input iterator addressing the first element in the first range whose inner product or
 *                      generalized inner product with the second range is to be computed.
 * @param it_last1      An input iterator addressing the last element in the first range whose inner product or
 *                      generalized inner product with the second range is to be computed.
 * @param it_first2     An input iterator addressing the first element in the second range whose inner product or
 *                      generalized inner product with the first range is to be computed.
 * @param elem          An initial value to which the inner product or generalized inner product between the ranges is to be added.
 * @param bfun_op1      The binary operation that replaces the inner product operation of sum applied to the element-wise products in the generalization of the inner product.
 * @param bfun_op2      The binary operation that replaces the inner product element-wise operation of multiply in the generalization of the inner product.
 * @param pv_output     A product result.
 * @return  void.
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
#define algo_inner_product_if(it_first1, it_last1, it_first2, elem, bfun_op1, bfun_op2, pv_output)\
    _algo_inner_product_if((it_first1), (it_last1), (it_first2), (bfun_op1), (bfun_op2), (pv_output), (elem))

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Power is generalized exponentiation: it raises the value x to the power n, where n is a non-negative integer.
 * @param it_first      A input iterator addressing the value x.
 * @param t_power       Power.
 * @param pv_output     Power result.
 * @return  void.
 * remarks  The iterator must be valid, otherwise the behavior is undefined.
 */
extern void algo_power(input_iterator_t it_iter, size_t t_power, void* pv_output);

/**
 * Power is generalized exponentiation: it raises the value x to the power n, where n is a non-negative integer.
 * @param it_first      A input iterator addressing the value x.
 * @param t_power       Power.
 * @param bfun_op       The binary operation that is to be applied power.
 * @param pv_output     Power result.
 * @return  void.
 * remarks  The iterator must be valid, otherwise the behavior is undefined.
 */
extern void algo_power_if(input_iterator_t it_iter, size_t t_power, bfun_t bfun_op, void* pv_output);

/**
 * Computes the successive differences between each element and its predecessor in an input range and outputs the results to a destination range.
 * @param it_first      An input iterator addressing the first element in the input range whose elements are to be differenced with their respective predecessors.
 * @param it_last       An input iterator addressing the last element in the input range whose elements are to be differenced with their respective predecessors.
 * @param it_result     An output iterator addressing the first element a destination range where the series of differences.
 * @return  An output iterator addressing the end of the destination range: it_result + (it_last - it_first).
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_adjacent_difference(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result);

/**
 * Computes the result of a generalized procedure where the difference operation is replaced by another, specified binary operation.
 * @param it_first      An input iterator addressing the first element in the input range whose elements are to be differenced with their respective predecessors.
 * @param it_last       An input iterator addressing the last element in the input range whose elements are to be differenced with their respective predecessors.
 * @param it_result     An output iterator addressing the first element a destination range where the series of differences.
 * @param bfun_op       The binary operation that is to be applied in the generalized operation replacing the operation of subtraction in the differencing procedure.
 * @return  An output iterator addressing the end of the destination range: it_result + (it_last - it_first).
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_adjacent_difference_if(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, bfun_t bfun_op);

/**
 * Computes a series of sums in an input range from the first element through the ith element and stores the result of each such sum in the ith element of a destination range.
 * @param it_first      An input iterator addressing the first element in the range to be partially summed or combined according to a specified binary operation.
 * @param it_last       An input iterator addressing the last element in the range to be partially summed or combined according to a specified binary operation
 *                      that is one position beyond the final element actually included in the iterated accumulation.
 * @param it_result     An output iterator addressing the first element a destination range where the series of partial sums or the results of the specified operation is to be stored.
 * @return  An output iterator addressing the end of the destination range: it_result + (it_last - it_first).
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_partial_sum(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result);

/**
 * Computes the result of a generalized procedure where the sum operation is replaced by another specified binary operation.
 * @param it_first      An input iterator addressing the first element in the range to be partially summed or combined according to a specified binary operation.
 * @param it_last       An input iterator addressing the last element in the range to be partially summed or combined according to a specified binary operation
 *                      that is one position beyond the final element actually included in the iterated accumulation.
 * @param it_result     An output iterator addressing the first element a destination range where the series of partial sums or the results of the specified operation is to be stored.
 * @param bfun_op       The binary operation that is to be applied in the generalized operation replacing the operation of sum in the partial sum procedure.
 * @return  An output iterator addressing the end of the destination range: it_result + (it_last - it_first).
 * @remarks The referenced range must be valid, otherwise the behavior is undefined.
 */
extern output_iterator_t algo_partial_sum_if(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, bfun_t bfun_op);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_NUMERIC_H_ */
/** eof **/

