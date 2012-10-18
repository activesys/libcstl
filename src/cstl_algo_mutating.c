/*
 *  The implementation of mutating algorithm.
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

/** include section **/
#include <cstl/cstl_def.h>
#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/citerator.h>
#include <cstl/cstring.h>
#include <cstl/cfunctional.h>

#include <cstl/cstl_algo_mutating_private.h>
#include <cstl/cstl_algo_mutating.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a forward direction.
 */
output_iterator_t algo_copy(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result)
{
    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first), it_result = iterator_next(it_result)) {
        iterator_set_value(it_result, iterator_get_pointer(it_first));
    }

    return it_result;
}

/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a forward direction.
 */
output_iterator_t algo_copy_n(input_iterator_t it_first, size_t t_count, output_iterator_t it_result)
{
    return algo_copy(it_first, iterator_advance(it_first, t_count), it_result);
}

/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a backward direction.
 */
bidirectional_iterator_t algo_copy_backward(
    bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, bidirectional_iterator_t it_result)
{
    assert(_iterator_valid_range(it_first, it_last, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_limit_type(it_result, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    while (!iterator_equal(it_first, it_last)) {
        it_last = iterator_prev(it_last);
        it_result = iterator_prev(it_result);
        iterator_set_value(it_result, iterator_get_pointer(it_last));
    }

    return it_result;
}

/**
 * Exchanges two values referred to by a pair of specified iterators.
 */
void algo_swap(forward_iterator_t it_first, forward_iterator_t it_second)
{
    algo_iter_swap(it_first, it_second);
}

/**
 * Exchanges two values referred to by a pair of specified iterators.
 */
void algo_iter_swap(forward_iterator_t it_first, forward_iterator_t it_second)
{
    void* pv_value = NULL;

    assert(_iterator_limit_type(it_first, _FORWARD_ITERATOR));
    assert(_iterator_limit_type(it_second, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_second));

    if (!iterator_equal(it_first, it_second)) {
        pv_value = _iterator_allocate_init_elem(it_first);

        if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            string_assign_cstr((string_t*)pv_value, iterator_get_pointer(it_first));
            iterator_set_value(it_first, iterator_get_pointer(it_second));
            iterator_set_value(it_second, string_c_str((string_t*)pv_value));
        } else {
            iterator_get_value(it_first, pv_value);
            iterator_set_value(it_first, iterator_get_pointer(it_second));
            iterator_set_value(it_second, pv_value);
        }

        _iterator_deallocate_destroy_elem(it_first, pv_value);
        pv_value = NULL;
    }
}

/**
 * Exchanges the elements of one range with the elements of another, equal sized range.
 */
forward_iterator_t algo_swap_ranges(forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2)
{
    assert(_iterator_valid_range(it_first1, it_last1, _FORWARD_ITERATOR));
    assert(_iterator_limit_type(it_first2, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1), it_first2 = iterator_next(it_first2)) {
        algo_iter_swap(it_first1, it_first2);
    }

    return it_first2;
}

/**
 * Applies a specified function object to each element in a source range and copies the return values of the function object into a destination range.
 */
output_iterator_t algo_transform(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, unary_function_t ufun_op)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(it_first);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first), it_result = iterator_next(it_result)) {
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(it_first));
            (*ufun_op)(iterator_get_pointer(it_first), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(it_result, string_c_str((string_t*)pv_value));
        }
    } else {
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first), it_result = iterator_next(it_result)) {
            (*ufun_op)(iterator_get_pointer(it_first), pv_value);
            iterator_set_value(it_result, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return it_result;
}

/**
 * Applies a specified function object to a pair of elements from two source ranges and copies the return values of the function into a destination range.
 */
output_iterator_t algo_transform_binary(
    input_iterator_t it_first1, input_iterator_t it_last1, 
    input_iterator_t it_first2, output_iterator_t it_result,
    binary_function_t bfun_op)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));
    assert(_iterator_limit_type(it_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_result));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = fun_default_binary;
    }

    pv_value = _iterator_allocate_init_elem(it_first1);

    if (strncmp(_iterator_get_typebasename(it_first1), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (;
             !iterator_equal(it_first1, it_last1);
             it_first1 = iterator_next(it_first1),
             it_first2 = iterator_next(it_first2),
             it_result = iterator_next(it_result)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(it_result, string_c_str((string_t*)pv_value));
        }
    } else {
        for (;
             !iterator_equal(it_first1, it_last1);
             it_first1 = iterator_next(it_first1),
             it_first2 = iterator_next(it_first2),
             it_result = iterator_next(it_result)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), pv_value);
            iterator_set_value(it_result, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(it_first1, pv_value);
    pv_value = NULL;

    return it_result;
}

/** eof **/

