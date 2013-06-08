/*
 *  The implementation of numeric.
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

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/citerator.h>
#include <cstl/cfunctional.h>
#include <cstl/cnumeric.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Power is generalized exponentiation: it raises the value x to the power n, where n is a non-negative integer.
 */
void algo_power(input_iterator_t it_iter, size_t t_power, void* pv_output)
{
    algo_power_if(it_iter, t_power, _fun_get_binary(it_iter, _MULTIPLIES_FUN), pv_output);
}

/**
 * Power is generalized exponentiation: it raises the value x to the power n, where n is a non-negative integer.
 */
void algo_power_if(input_iterator_t it_iter, size_t t_power, bfun_t bfun_op, void* pv_output)
{
    size_t i = 0;
    bool_t b_result = false;

    assert(_iterator_limit_type(it_iter, _INPUT_ITERATOR));
    assert(pv_output != NULL);

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_iter, _MULTIPLIES_FUN);
    }

    b_result = _iterator_get_typesize(it_iter);
    _iterator_get_typecopy(it_iter)(pv_output, iterator_get_pointer(it_iter), &b_result);
    assert(b_result);
    if (t_power > 0) {
        for (i = 1; i < t_power; ++i) {
            (*bfun_op)(pv_output, iterator_get_pointer(it_iter), pv_output);
        }
    }
}

/**
 * Computes the successive differences between each element and its predecessor in an input range and outputs the results to a destination range.
 */
output_iterator_t algo_adjacent_difference(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result)
{
    return algo_adjacent_difference_if(it_first, it_last, it_result, _fun_get_binary(it_first, _MINUS_FUN));
}

/**
 * Computes the result of a generalized procedure where the difference operation is replaced by another, specified binary operation.
 */
output_iterator_t algo_adjacent_difference_if(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, bfun_t bfun_op)
{
    iterator_t it_index;
    bool_t     b_typesize = false;
    void*      pv_value = NULL;
    void*      pv_tmp = NULL;
    void*      pv_result = NULL;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    if (iterator_equal(it_first, it_last)) {
        return it_result;
    }

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _MINUS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(it_first);
    pv_tmp = _iterator_allocate_init_elem(it_first);
    pv_result = _iterator_allocate_init_elem(it_first);

    iterator_get_value(it_first, pv_value);
    iterator_set_value(it_result, pv_value);
    for (it_index = iterator_next(it_first); !iterator_equal(it_index, it_last); it_index = iterator_next(it_index)) {
        iterator_get_value(it_index, pv_tmp);
        (*bfun_op)(pv_tmp, pv_value, pv_result);
        it_result = iterator_next(it_result);
        iterator_set_value(it_result, pv_result);

        b_typesize = _iterator_get_typesize(it_first);
        _iterator_get_typecopy(it_first)(pv_value, pv_tmp, &b_typesize);
        assert(b_typesize);
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    _iterator_deallocate_destroy_elem(it_first, pv_tmp);
    _iterator_deallocate_destroy_elem(it_first, pv_result);
    pv_value = NULL;
    pv_tmp = NULL;
    pv_result = NULL;

    it_result = iterator_next(it_result);
    return it_result;
}

/**
 * Computes a series of sums in an input range from the first element through the ith element and stores the result of each such sum in the ith element of a destination range.
 */
output_iterator_t algo_partial_sum(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result)
{
    return algo_partial_sum_if(it_first, it_last, it_result, _fun_get_binary(it_first, _PLUS_FUN));
}

/**
 * Computes the result of a generalized procedure where the sum operation is replaced by another specified binary operation.
 */
output_iterator_t algo_partial_sum_if(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, bfun_t bfun_op)
{
    iterator_t it_index;
    void*      pv_value = NULL;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    if (iterator_equal(it_first, it_last)) {
        return it_result;
    }

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _PLUS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(it_first);

    iterator_get_value(it_first, pv_value);
    iterator_set_value(it_result, pv_value);
    for (it_index = iterator_next(it_first); !iterator_equal(it_index, it_last); it_index = iterator_next(it_index)) {
        (*bfun_op)(pv_value, iterator_get_pointer(it_index), pv_value);
        it_result = iterator_next(it_result);
        iterator_set_value(it_result, pv_value);
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    it_result = iterator_next(it_result);
    return it_result;
}

/** local function implementation section **/

/** eof **/

