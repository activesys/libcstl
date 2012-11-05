/*
 *  The implementation of algorithm.
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
#include <cstl/calgorithm.h>

#include "cstl_algo_mutating_aux.h"
#include "cstl_algo_sorting_aux.h"

/** local constant declaration and local macro section **/
#define _CSTL_ALGO_SORT_THRESHOLD 16

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
forward_iterator_t algo_max_element(
    forward_iterator_t t_first, forward_iterator_t t_last)
{
    return algo_max_element_if(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN));
}

forward_iterator_t algo_max_element_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op)
{
    iterator_t t_result;
    bool_t     t_cmp = false;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    if(iterator_equal(t_first, t_last))
    {
        return t_first;
    }

    t_result = t_first;
    for(t_first = iterator_next(t_first);
        !iterator_equal(t_first, t_last);
        t_first = iterator_next(t_first))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first), iterator_get_pointer(t_result), &t_cmp);
        /* *t_first >= *t_result */
        if(!t_cmp)
        {
            t_result = t_first;
        }
    }

    return t_result;
}

forward_iterator_t algo_min_element(
    forward_iterator_t t_first, forward_iterator_t t_last)
{
    return algo_min_element_if(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN));
}

forward_iterator_t algo_min_element_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op)
{
    iterator_t t_result;
    bool_t     t_cmp = false;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    if(iterator_equal(t_first, t_last))
    {
        return t_first;
    }

    t_result = t_first;
    for(t_first = iterator_next(t_first);
        !iterator_equal(t_first, t_last);
        t_first = iterator_next(t_first))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first), iterator_get_pointer(t_result), &t_cmp);
        /* *t_first < *t_result */
        if(t_cmp)
        {
            t_result = t_first;
        }
    }

    return t_result;
}

bool_t algo_next_permutation(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last)
{
    return algo_next_permutation_if(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN));
}

bool_t algo_next_permutation_if(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    binary_function_t t_binary_op)
{
    iterator_t t_i;
    iterator_t t_ii;
    iterator_t t_j;
    bool_t     t_result = false;

    assert(_iterator_valid_range(t_first, t_last, _BIDIRECTIONAL_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    if(iterator_equal(t_first, t_last))
    {
        return false;
    }
    t_i = t_first;
    t_i = iterator_next(t_i);
    if(iterator_equal(t_i, t_last))
    {
        return false;
    }

    t_i = t_last;
    t_i = iterator_prev(t_i);
    for(;;)
    {
        t_ii = t_i;
        t_i = iterator_prev(t_i);

        (*t_binary_op)(
            iterator_get_pointer(t_i), iterator_get_pointer(t_ii), &t_result);
        if(t_result)
        {
            t_j = t_last;
            t_j = iterator_prev(t_j);
            (*t_binary_op)(
                iterator_get_pointer(t_i), iterator_get_pointer(t_j), &t_result);
            while(!t_result)
            {
                t_j = iterator_prev(t_j);
                (*t_binary_op)(
                    iterator_get_pointer(t_i), iterator_get_pointer(t_j), &t_result);
            }
            algo_iter_swap(t_i, t_j);
            algo_reverse(t_ii, t_last);
            return true;
        }

        if(iterator_equal(t_i, t_first))
        {
            algo_reverse(t_first, t_last);
            return false;
        }
    }
}

bool_t algo_prev_permutation(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last)
{
    return algo_prev_permutation_if(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN));
}

bool_t algo_prev_permutation_if(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    binary_function_t t_binary_op)
{
    iterator_t t_i;
    iterator_t t_ii;
    iterator_t t_j;
    bool_t     t_result = false;

    assert(_iterator_valid_range(t_first, t_last, _BIDIRECTIONAL_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    if(iterator_equal(t_first, t_last))
    {
        return false;
    }
    t_i = t_first;
    t_i = iterator_next(t_i);
    if(iterator_equal(t_i, t_last))
    {
        return false;
    }

    t_i = t_last;
    t_i = iterator_prev(t_i);
    for(;;)
    {
        t_ii = t_i;
        t_i = iterator_prev(t_i);

        (*t_binary_op)(
            iterator_get_pointer(t_ii), iterator_get_pointer(t_i), &t_result);
        if(t_result)
        {
            t_j = t_last;
            t_j = iterator_prev(t_j);
            (*t_binary_op)(
                iterator_get_pointer(t_j), iterator_get_pointer(t_i), &t_result);
            while(!t_result)
            {
                t_j = iterator_prev(t_j);
                (*t_binary_op)(
                    iterator_get_pointer(t_j), iterator_get_pointer(t_i), &t_result);
            }
            algo_iter_swap(t_i, t_j);
            algo_reverse(t_ii, t_last);
            return true;
        }

        if(iterator_equal(t_i, t_first))
        {
            algo_reverse(t_first, t_last);
            return false;
        }
    }
}

/** local function implementation section **/

/** eof **/

