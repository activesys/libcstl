/*
 *  The implementation of non-mutating algorithm.
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

#include <cstl/cstl_algo_nonmutating_private.h>
#include <cstl/cstl_algo_nonmutating.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Applies a unary function to each element in a range.
 */
void algo_for_each(input_iterator_t it_first, input_iterator_t it_last, unary_function_t ufun_op)
{
    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
        (*ufun_op)(iterator_get_pointer(it_first), NULL);
    }
}

/**
 * Locates the position of the first occurrence of an element in a range that satisfies a specified condition.
 */
input_iterator_t algo_find_if(input_iterator_t it_first, input_iterator_t it_last, unary_function_t ufun_op)
{
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }
    for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
        (*ufun_op)(iterator_get_pointer(it_first), &b_result);
        if (b_result) {
            break;
        }
    }

    return it_first;
}

/**
 * Searches for two adjacent elements that are equal.
 */
forward_iterator_t algo_adjacent_find(forward_iterator_t it_first, forward_iterator_t it_last)
{
    return algo_adjacent_find_if(it_first, it_last, _fun_get_binary(it_first, _EQUAL_FUN));
}

/**
 * Searches for two adjacent elements that satisfy a specificed condition.
 */
forward_iterator_t algo_adjacent_find_if(forward_iterator_t it_first, forward_iterator_t it_last, binary_function_t bfun_op)
{
    forward_iterator_t it_next;
    bool_t             b_result = false;
    bool_t             b_less = false;
    bool_t             b_greater = false;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _EQUAL_FUN);
    }

    if (iterator_equal(it_first, it_last)) {
        return it_last;
    }

    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);

        it_next = it_first;
        it_next = iterator_next(it_next);
        while (!iterator_equal(it_next, it_last)) {
            (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_next), &b_less);
            (*bfun_op)(iterator_get_pointer(it_next), iterator_get_pointer(it_first), &b_greater);
            if (!b_less && !b_greater) {
                return it_first;
            }

            it_first = it_next;
            it_next = iterator_next(it_next);
        }
    } else {
        it_next = it_first;
        it_next = iterator_next(it_next);
        while (!iterator_equal(it_next, it_last)) {
            (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_next), &b_result);
            if (b_result) {
                return it_first;
            }

            it_first = it_next;
            it_next = iterator_next(it_next);
        }
    }

    return it_last;
}

/**
 * Searches for the first occurrence of any of several values within a target range.
 */
input_iterator_t algo_find_first_of(
    input_iterator_t it_first1, input_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2)
{
    return algo_find_first_of_if(it_first1, it_last1, it_first2, it_last2, _fun_get_binary(it_first1, _EQUAL_FUN));
}

/**
 * Searches for the first occurrence of any of several elements that are equivalent in a sense specified by
 */
input_iterator_t algo_find_first_of_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    forward_iterator_t it_first2, forward_iterator_t it_last2,
    binary_function_t bfun_op)
{
    iterator_t it_index;
    bool_t     b_result = false;
    bool_t     b_less = false;
    bool_t     b_greater = false;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _EQUAL_FUN);
    }

    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);

        for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1)) {
            for (it_index = it_first2; !iterator_equal(it_index, it_last2); it_index = iterator_next(it_index)) {
                (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_index), &b_less);
                if (b_less) {
                    continue;
                }
                (*bfun_op)(iterator_get_pointer(it_index), iterator_get_pointer(it_first1), &b_greater);
                if (b_greater) {
                    continue;
                }

                return it_first1;
            }
        }
    } else {
        for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1)) {
            for (it_index = it_first2; !iterator_equal(it_index, it_last2); it_index = iterator_next(it_index)) {
                (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_index), &b_result);
                if (b_result) {
                    return it_first1;
                }
            }
        }
    }

    return it_last1;
}

/** eof **/

