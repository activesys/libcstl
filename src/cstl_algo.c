/*
 *  The implementation of algorithm.
 *  Copyright (C)  2008,2009,2010  Wangbo
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
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "citerator.h"
#include "cstring.h"
#include "cfunctional.h"
/*#include "cstl_tools.h"*/
/*#include "cutility.h"*/

#include "cstl_algobase.h"
#include "cstl_algobase_private.h"
#include "cstl_heap.h"

#include "cstl_algo.h"
#include "cstl_algo_private.h"

/** local constant declaration and local macro section **/
#define _CSTL_SORT_THRESHOLD  16 /* the threshold of insert sort and quick sort */

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
/*
 * Partition with bidirectional_iterator_t.
 */
static bidirectional_iterator_t _partition_biditer(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    unary_function_t t_unary_op);

/*
 * Rotates the elements in the range [t_first, t_last).
 */
static void _rotate_forward(
    forward_iterator_t t_first,
    forward_iterator_t t_middle,
    forward_iterator_t t_last);

/*
 * The implement of insertion sort.
 */
static void _insertion_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op, char* pc_value);

/*
 * Return the median of three random_access_iterator_t
 */
static random_access_iterator_t _median_of_three_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op);

/*
 * Compute the logarithm of t_n.
 */
static size_t _lg(size_t t_n);

/*
 * The implement of intro sort.
 */
static void _intro_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op, size_t t_depth, char* pc_value);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
output_iterator_t algo_set_union(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result)
{
    return algo_set_union_if(t_first1, t_last1, t_first2, t_last2, t_result,
        _fun_get_binary(t_first1, _LESS_FUN));
}

output_iterator_t algo_set_union_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op)
{
    bool_t t_cmp = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));
    assert(_iterator_same_elem_type(t_first1, t_result));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }
    while(!iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_cmp);
        /* t_first1 < t_first2 */
        if(t_cmp)
        {
            iterator_set_value(t_result, iterator_get_pointer(t_first1));
            t_first1 = iterator_next(t_first1);
        }
        else
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_cmp);
            /* t_first2 < t_first1 */
            if(t_cmp)
            {
                iterator_set_value(t_result, iterator_get_pointer(t_first2));
                t_first2 = iterator_next(t_first2);
            }
            else /* t_first1 == t_first2 */
            {
                iterator_set_value(t_result, iterator_get_pointer(t_first1));
                t_first1 = iterator_next(t_first1);
                t_first2 = iterator_next(t_first2);
            }
        }
        t_result = iterator_next(t_result);
    }

    assert(iterator_equal(t_first1, t_last1) || iterator_equal(t_first2, t_last2));
    return algo_copy(t_first2, t_last2, algo_copy(t_first1, t_last1, t_result));
}

output_iterator_t algo_set_intersection(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result)
{
    return algo_set_intersection_if(t_first1, t_last1, t_first2, t_last2, t_result,
        _fun_get_binary(t_first1, _LESS_FUN));
}

output_iterator_t algo_set_intersection_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op)
{
    bool_t t_cmp = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));
    assert(_iterator_same_elem_type(t_first1, t_result));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }
    while(!iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_cmp);
        /* t_first1 < t_first2 */
        if(t_cmp)
        {
            t_first1 = iterator_next(t_first1);
        }
        else
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_cmp);
            /* t_first2 < t_first1 */
            if(t_cmp)
            {
                t_first2 = iterator_next(t_first2);
            }
            else /* t_first1 == t_first2 */
            {
                iterator_set_value(t_result, iterator_get_pointer(t_first1));
                t_first1 = iterator_next(t_first1);
                t_first2 = iterator_next(t_first2);
                t_result = iterator_next(t_result);
            }
        }
    }

    assert(iterator_equal(t_first1, t_last1) || iterator_equal(t_first2, t_last2));
    return t_result;
}

output_iterator_t algo_set_difference(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result)
{
    return algo_set_difference_if(t_first1, t_last1, t_first2, t_last2, t_result,
        _fun_get_binary(t_first1, _LESS_FUN));
}

output_iterator_t algo_set_difference_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op)
{
    bool_t t_cmp = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));
    assert(_iterator_same_elem_type(t_first1, t_result));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }
    while(!iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_cmp);
        /* t_first1 < t_first2 */
        if(t_cmp)
        {
            iterator_set_value(t_result, iterator_get_pointer(t_first1));
            t_first1 = iterator_next(t_first1);
            t_result = iterator_next(t_result);
        }
        else
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_cmp);
            /* t_first2 < t_first1 */
            if(t_cmp)
            {
                t_first2 = iterator_next(t_first2);
            }
            else /* t_first1 == t_first2 */
            {
                t_first1 = iterator_next(t_first1);
                t_first2 = iterator_next(t_first2);
            }
        }
    }

    assert(iterator_equal(t_first1, t_last1) || iterator_equal(t_first2, t_last2));
    return algo_copy(t_first1, t_last1, t_result);
}

output_iterator_t algo_set_symmetric_difference(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result)
{
    return algo_set_symmetric_difference_if(t_first1, t_last1, t_first2, t_last2, t_result,
        _fun_get_binary(t_first1, _LESS_FUN));
}

output_iterator_t algo_set_symmetric_difference_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result,
    binary_function_t t_binary_op)
{
    bool_t t_cmp = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));
    assert(_iterator_same_elem_type(t_first1, t_result));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }
    while(!iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_cmp);
        /* t_first1 < t_first2 */
        if(t_cmp)
        {
            iterator_set_value(t_result, iterator_get_pointer(t_first1));
            t_first1 = iterator_next(t_first1);
            t_result = iterator_next(t_result);
        }
        else
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_cmp);
            /* t_first2 < t_first1 */
            if(t_cmp)
            {
                iterator_set_value(t_result, iterator_get_pointer(t_first2));
                t_first2 = iterator_next(t_first2);
                t_result = iterator_next(t_result);
            }
            else /* t_first1 == t_first2 */
            {
                t_first1 = iterator_next(t_first1);
                t_first2 = iterator_next(t_first2);
            }
        }
    }

    assert(iterator_equal(t_first1, t_last1) || iterator_equal(t_first2, t_last2));
    return algo_copy(t_first2, t_last2, algo_copy(t_first1, t_last1, t_result));
}

forward_iterator_t algo_adjacent_find(
    forward_iterator_t t_first, forward_iterator_t t_last)
{
    return algo_adjacent_find_if(t_first, t_last, _fun_get_binary(t_first, _EQUAL_FUN));
}

forward_iterator_t algo_adjacent_find_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op)
{
    forward_iterator_t t_next;
    bool_t             t_result = false;
    bool_t             t_less = false;
    bool_t             t_greater = false;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));
    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _EQUAL_FUN);
    }

    if(iterator_equal(t_first, t_last))
    {
        return t_last;
    }

    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);

        t_next = t_first;
        t_next = iterator_next(t_next);
        while(!iterator_equal(t_next, t_last))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first), iterator_get_pointer(t_next), &t_less);
            (*t_binary_op)(
                iterator_get_pointer(t_next), iterator_get_pointer(t_first), &t_greater);
            if(!t_less && !t_greater)
            {
                return t_first;
            }

            t_first = t_next;
            t_next = iterator_next(t_next);
        }
    }
    else
    {
        t_next = t_first;
        t_next = iterator_next(t_next);
        while(!iterator_equal(t_next, t_last))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first), iterator_get_pointer(t_next), &t_result);
            if(t_result)
            {
                return t_first;
            }

            t_first = t_next;
            t_next = iterator_next(t_next);
        }
    }

    return t_last;
}

size_t _algo_count(input_iterator_t t_first, input_iterator_t t_last, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_last);

    return _algo_count_varg(t_first, t_last, val_elemlist);
}

size_t _algo_count_varg(
    input_iterator_t t_first, input_iterator_t t_last, va_list val_elemlist)
{
    void*             pv_value = NULL;
    bool_t            t_result = false;
    bool_t            t_less = false;
    bool_t            t_greater = false;
    size_t            t_count = 0;
    binary_function_t t_binary_op;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    t_binary_op = _fun_get_binary(t_first, _EQUAL_FUN);
    assert(t_binary_op != NULL);
    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            (*t_binary_op)(iterator_get_pointer(t_first), pv_value, &t_less);
            if(t_less)
            {
                continue;
            }
            (*t_binary_op)(pv_value, iterator_get_pointer(t_first), &t_greater);
            if(t_greater)
            {
                continue;
            }

            t_count++;
        }
    }
    else
    {
        if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
            {
                (*t_binary_op)(iterator_get_pointer(t_first), string_c_str((string_t*)pv_value), &t_result);
                if(t_result)
                {
                    t_count++;
                }
            }
        }
        else
        {
            for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
            {
                (*t_binary_op)(iterator_get_pointer(t_first), pv_value, &t_result);
                if(t_result)
                {
                    t_count++;
                }
            }
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_count;
}

size_t algo_count_if(
    input_iterator_t t_first, input_iterator_t t_last, unary_function_t t_unary_op)
{
    bool_t t_result = false;
    size_t t_count = 0;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }
    for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
    {
        (*t_unary_op)(iterator_get_pointer(t_first), &t_result);
        if(t_result)
        {
            t_count++;
        }
    }

    return t_count;
}

input_iterator_t _algo_find(
    input_iterator_t t_first, input_iterator_t t_last, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_last);

    return _algo_find_varg(t_first, t_last, val_elemlist);
}

input_iterator_t _algo_find_varg(
    input_iterator_t t_first, input_iterator_t t_last, va_list val_elemlist)
{
    void*             pv_value = NULL;
    bool_t            t_result = false;
    bool_t            t_less = false;
    bool_t            t_greater = false;
    binary_function_t t_binary_op;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    t_binary_op = _fun_get_binary(t_first, _EQUAL_FUN);
    assert(t_binary_op != NULL);
    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            (*t_binary_op)(iterator_get_pointer(t_first), pv_value, &t_less);
            if(t_less)
            {
                continue;
            }
            (*t_binary_op)(pv_value, iterator_get_pointer(t_first), &t_greater);
            if(t_greater)
            {
                continue;
            }

            break;
        }
    }
    else
    {
        if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
            {
                (*t_binary_op)(iterator_get_pointer(t_first), string_c_str((string_t*)pv_value), &t_result);
                if(t_result)
                {
                    break;
                }
            }
        }
        else
        {
            for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
            {
                (*t_binary_op)(iterator_get_pointer(t_first), pv_value, &t_result);
                if(t_result)
                {
                    break;
                }
            }
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_first;
}

input_iterator_t algo_find_if(
    input_iterator_t t_first, input_iterator_t t_last, unary_function_t t_unary_op)
{
    bool_t t_result = false;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }
    for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
    {
        (*t_unary_op)(iterator_get_pointer(t_first), &t_result);
        if(t_result)
        {
            break;
        }
    }

    return t_first;
}

input_iterator_t algo_find_first_of(
    input_iterator_t t_first1, input_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2)
{
    return algo_find_first_of_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _EQUAL_FUN));
}

input_iterator_t algo_find_first_of_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    iterator_t t_index;
    bool_t     t_result = false;
    bool_t     t_less = false;
    bool_t     t_greater = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _EQUAL_FUN);
    }

    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);

        for(; !iterator_equal(t_first1, t_last1); t_first1 = iterator_next(t_first1))
        {
            for(t_index = t_first2;
                !iterator_equal(t_index, t_last2);
                t_index = iterator_next(t_index))
            {
                (*t_binary_op)(
                    iterator_get_pointer(t_first1), iterator_get_pointer(t_index), &t_less);
                if(t_less)
                {
                    continue;
                }
                (*t_binary_op)(
                    iterator_get_pointer(t_index), iterator_get_pointer(t_first1), &t_greater);
                if(t_greater)
                {
                    continue;
                }

                return t_first1;
            }
        }
    }
    else
    {
        for(; !iterator_equal(t_first1, t_last1); t_first1 = iterator_next(t_first1))
        {
            for(t_index = t_first2;
                !iterator_equal(t_index, t_last2);
                t_index = iterator_next(t_index))
            {
                (*t_binary_op)(
                    iterator_get_pointer(t_first1), iterator_get_pointer(t_index), &t_result);
                if(t_result)
                {
                    return t_first1;
                }
            }
        }
    }

    return t_last1;
}

void algo_for_each(
    input_iterator_t t_first, input_iterator_t t_last, unary_function_t t_unary_op)
{
    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
    {
        (*t_unary_op)(iterator_get_pointer(t_first), NULL);
    }
}

forward_iterator_t algo_search(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2)
{
    return algo_search_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _EQUAL_FUN));
}

forward_iterator_t algo_search_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    bool_t     t_result = false;
    bool_t     t_less = false;
    bool_t     t_greater = false;
    iterator_t t_index1;
    iterator_t t_index2;
    size_t     t_len1 = 0;
    size_t     t_len2 = 0;

    assert(_iterator_valid_range(t_first1, t_last1, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _FORWARD_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _EQUAL_FUN);
    }

    t_len1 = iterator_distance(t_first1, t_last1);
    t_len2 = iterator_distance(t_first2, t_last2);
    if(t_len1 == 0 || t_len2 == 0 || t_len1 < t_len2)
    {
        return t_last1;
    }

    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);

        for(; !iterator_equal(t_first1, t_last1); t_first1 = iterator_next(t_first1))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_less);
            if(t_less)
            {
                continue;
            }
            (*t_binary_op)(
                iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_greater);
            if(t_greater)
            {
                continue;
            }

            for(t_index1 = t_first1, t_index1 = iterator_next(t_index1),
                t_index2 = t_first2, t_index2 = iterator_next(t_index2);
                !iterator_equal(t_index1, t_last1) && 
                !iterator_equal(t_index2, t_last2);
                t_index1 = iterator_next(t_index1), 
                t_index2 = iterator_next(t_index2))
            {
                (*t_binary_op)(
                    iterator_get_pointer(t_index1),
                    iterator_get_pointer(t_index2),
                    &t_less);
                if(t_less)
                {
                    break;
                }
                (*t_binary_op)(
                    iterator_get_pointer(t_index2),
                    iterator_get_pointer(t_index1),
                    &t_greater);
                if(t_greater)
                {
                    break;
                }
            }

            if(iterator_equal(t_index2, t_last2))
            {
                return t_first1;
            }
        }
    }
    else
    {
        for(; !iterator_equal(t_first1, t_last1); t_first1 = iterator_next(t_first1))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
            if(t_result)
            {
                for(t_index1 = t_first1, t_index1 = iterator_next(t_index1),
                    t_index2 = t_first2, t_index2 = iterator_next(t_index2);
                    !iterator_equal(t_index1, t_last1) && 
                    !iterator_equal(t_index2, t_last2);
                    t_index1 = iterator_next(t_index1), 
                    t_index2 = iterator_next(t_index2))
                {
                    (*t_binary_op)(
                        iterator_get_pointer(t_index1),
                        iterator_get_pointer(t_index2),
                        &t_result);
                    if(!t_result)
                    {
                        break;
                    }
                }

                if(iterator_equal(t_index2, t_last2))
                {
                    return t_first1;
                }
            }
        }
    }

    return t_last1;
}

forward_iterator_t _algo_search_n(
    forward_iterator_t t_first, forward_iterator_t t_last,
    size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);

    return _algo_search_n_if_varg(t_first, t_last, t_count,
        _fun_get_binary(t_first, _EQUAL_FUN), val_elemlist);
}

forward_iterator_t _algo_search_n_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    size_t t_count, binary_function_t t_binary_op, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_binary_op);

    return _algo_search_n_if_varg(
        t_first, t_last, t_count, t_binary_op, val_elemlist);
}

forward_iterator_t _algo_search_n_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    size_t t_count, binary_function_t t_binary_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    bool_t     t_result = false;
    bool_t     t_less = false;
    bool_t     t_greater = false;
    iterator_t t_index;
    size_t     t_i = 0;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_count == 0)
    {
        return t_last;
    }

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _EQUAL_FUN);
    }

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            (*t_binary_op)(iterator_get_pointer(t_first), pv_value, &t_less);
            if(t_less)
            {
                continue;
            }
            (*t_binary_op)(pv_value, iterator_get_pointer(t_first), &t_greater);
            if(t_greater)
            {
                continue;
            }

            for(t_i = 1, t_index = t_first, t_index = iterator_next(t_index);
                t_i < t_count && !iterator_equal(t_index, t_last);
                ++t_i, t_index = iterator_next(t_index))
            {
                (*t_binary_op)(iterator_get_pointer(t_index), pv_value, &t_less);
                if(t_less)
                {
                    break;
                }
                (*t_binary_op)(pv_value, iterator_get_pointer(t_index), &t_greater);
                if(t_greater)
                {
                    break;
                }
            }

            if(t_i == t_count)
            {
                break;
            }
        }
    }
    else
    {
        if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
            {
                (*t_binary_op)(iterator_get_pointer(t_first), string_c_str((string_t*)pv_value), &t_result);
                if(t_result)
                {
                    for(t_i = 1, t_index = t_first, t_index = iterator_next(t_index);
                        t_i < t_count && !iterator_equal(t_index, t_last);
                        ++t_i, t_index = iterator_next(t_index))
                    {
                        (*t_binary_op)(iterator_get_pointer(t_index), string_c_str((string_t*)pv_value), &t_result);
                        if(!t_result)
                        {
                            break;
                        }
                    }

                    if(t_i == t_count)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
            {
                (*t_binary_op)(iterator_get_pointer(t_first), pv_value, &t_result);
                if(t_result)
                {
                    for(t_i = 1, t_index = t_first, t_index = iterator_next(t_index);
                        t_i < t_count && !iterator_equal(t_index, t_last);
                        ++t_i, t_index = iterator_next(t_index))
                    {
                        (*t_binary_op)(iterator_get_pointer(t_index), pv_value, &t_result);
                        if(!t_result)
                        {
                            break;
                        }
                    }

                    if(t_i == t_count)
                    {
                        break;
                    }
                }
            }
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_first;
}

forward_iterator_t algo_search_end(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2)
{
    return algo_search_end_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _EQUAL_FUN));
}

forward_iterator_t algo_search_end_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    forward_iterator_t t_tmp;
    forward_iterator_t t_result;

    assert(_iterator_valid_range(t_first1, t_last1, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _FORWARD_ITERATOR));

    t_result = t_tmp = t_last1;
    for(;;)
    {
        t_tmp = algo_search_if(t_first1, t_last1, t_first2, t_last2, t_binary_op);
        if(iterator_equal(t_tmp, t_last1))
        {
            return t_result;
        }
        else
        {
            t_result = t_tmp;
            t_first1 = t_tmp;
            t_first1 = iterator_next(t_first1);
        }
    }
}

forward_iterator_t algo_find_end(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2)
{
    return algo_search_end(t_first1, t_last1, t_first2, t_last2);
}

forward_iterator_t algo_find_end_if(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2, forward_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    return algo_search_end_if(t_first1, t_last1, t_first2, t_last2, t_binary_op);
}

void algo_generate(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));
    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(t_first);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(t_first));
            (*t_unary_op)(string_c_str((string_t*)pv_value), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(t_first, string_c_str((string_t*)pv_value));
        }
    }
    else
    {
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            iterator_get_value(t_first, pv_value);
            (*t_unary_op)(pv_value, pv_value);
            iterator_set_value(t_first, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;
}

output_iterator_t algo_generate_n(
    output_iterator_t t_first, size_t t_count, unary_function_t t_unary_op)
{
    size_t t_index = 0;
    void* pv_value = NULL;

    assert(_iterator_limit_type(t_first, _OUTPUT_ITERATOR));
    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(t_first);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(t_index = 0; t_index < t_count; ++t_index, t_first = iterator_next(t_first))
        {
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(t_first));
            (*t_unary_op)(string_c_str((string_t*)pv_value), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(t_first, string_c_str((string_t*)pv_value));
        }
    }
    else
    {
        for(t_index = 0; t_index < t_count; ++t_index, t_first = iterator_next(t_first))
        {
            iterator_get_value(t_first, pv_value);
            (*t_unary_op)(pv_value, pv_value);
            iterator_set_value(t_first, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_first;
}

bool_t algo_includes(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2)
{
    return algo_includes_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _LESS_FUN));
}

bool_t algo_includes_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }

    while(!iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_result);
        /* *t_first2 < *t_first1 */
        if(t_result)
        {
            return false;
        }
        else
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
            /* *t_first1 < *t_first2 */
            if(t_result)
            {
                t_first1 = iterator_next(t_first1);
            }
            else /* *t_first1 == *t_first2 */
            {
                t_first1 = iterator_next(t_first1);
                t_first2 = iterator_next(t_first2);
            }
        }
    }

    if(iterator_equal(t_first2, t_last2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

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

output_iterator_t algo_merge(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result)
{
    return algo_merge_if(t_first1, t_last1, t_first2, t_last2, t_result,
        _fun_get_binary(t_first1, _LESS_FUN));
}

output_iterator_t algo_merge_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    output_iterator_t t_result, binary_function_t t_binary_op)
{
    bool_t t_cmp = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));
    assert(_iterator_same_elem_type(t_first1, t_result));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }

    while(!iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_cmp);
        /* *t_first2 < *t_first1 */
        if(t_cmp)
        {
            iterator_set_value(t_result, iterator_get_pointer(t_first2));
            t_first2 = iterator_next(t_first2);
        }
        else
        {
            iterator_set_value(t_result, iterator_get_pointer(t_first1));
            t_first1 = iterator_next(t_first1);
        }
        t_result = iterator_next(t_result);
    }

    return algo_copy(t_first2, t_last2, algo_copy(t_first1, t_last1, t_result));
}

forward_iterator_t algo_partition(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op)
{
    bool_t     t_result = false;
    iterator_t t_next;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));

    if((_GET_ITERATOR_TYPE(t_first) == _BIDIRECTIONAL_ITERATOR &&
        _GET_ITERATOR_TYPE(t_last) == _BIDIRECTIONAL_ITERATOR) ||
       (_GET_ITERATOR_TYPE(t_first) == _RANDOM_ACCESS_ITERATOR &&
        _GET_ITERATOR_TYPE(t_first) == _RANDOM_ACCESS_ITERATOR))
    {
        return _partition_biditer(t_first, t_last, t_unary_op);
    }

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    if(iterator_equal(t_first, t_last))
    {
        return t_first;
    }

    while(!iterator_equal(t_first, t_last))
    {
        (*t_unary_op)(iterator_get_pointer(t_first), &t_result);
        if(!t_result)
        {
            for(t_next = t_first, t_next = iterator_next(t_next);
                !iterator_equal(t_next, t_last);
                t_next = iterator_next(t_next))
            {
                (*t_unary_op)(iterator_get_pointer(t_next), &t_result);
                if(t_result)
                {
                    algo_iter_swap(t_first, t_next);
                    break;
                }
            }

            if(iterator_equal(t_next, t_last))
            {
                return t_first;
            }
        }

        t_first = iterator_next(t_first);
    }

    return t_first;
}

forward_iterator_t algo_stable_partition(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op)
{
    bool_t     t_result = false;
    iterator_t t_next;
    iterator_t t_index;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    if(iterator_equal(t_first, t_last))
    {
        return t_first;
    }

    while(!iterator_equal(t_first, t_last))
    {
        (*t_unary_op)(iterator_get_pointer(t_first), &t_result);
        if(!t_result)
        {
            for(t_next = t_first, t_next = iterator_next(t_next);
                !iterator_equal(t_next, t_last);
                t_next = iterator_next(t_next))
            {
                (*t_unary_op)(iterator_get_pointer(t_next), &t_result);
                if(t_result)
                {
                    t_index = t_first;
                    do
                    {
                        t_index = iterator_next(t_index);
                        algo_iter_swap(t_first, t_index);
                    }while(!iterator_equal(t_index, t_next));
                    break;
                }
            }

            if(iterator_equal(t_next, t_last))
            {
                return t_first;
            }
        }

        t_first = iterator_next(t_first);
    }

    return t_first;
}

output_iterator_t _algo_remove_copy(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_result);

    return _algo_remove_copy_varg(t_first, t_last, t_result, val_elemlist);
}

output_iterator_t _algo_remove_copy_varg(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, va_list val_elemlist)
{
    void*             pv_value = NULL;
    bool_t            t_cmp = false;
    bool_t            t_less = false;
    bool_t            t_greater = false;
    binary_function_t t_binary_op = NULL;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    t_binary_op = _fun_get_binary(t_first, _EQUAL_FUN);
    assert(t_binary_op != NULL);
    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            (*t_binary_op)(iterator_get_pointer(t_first), pv_value, &t_less);
            if(t_less)
            {
                iterator_set_value(t_result, iterator_get_pointer(t_first));
                t_result = iterator_next(t_result);
                continue;
            }
            (*t_binary_op)(pv_value, iterator_get_pointer(t_first), &t_greater);
            if(t_greater)
            {
                iterator_set_value(t_result, iterator_get_pointer(t_first));
                t_result = iterator_next(t_result);
                continue;
            }
        }
    }
    else
    {
        if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
        {
            for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
            {
                (*t_binary_op)(iterator_get_pointer(t_first), string_c_str((string_t*)pv_value), &t_cmp);
                if(!t_cmp)
                {
                    iterator_set_value(t_result, iterator_get_pointer(t_first));
                    t_result = iterator_next(t_result);
                }
            }
        }
        else
        {
            for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
            {
                (*t_binary_op)(iterator_get_pointer(t_first), pv_value, &t_cmp);
                if(!t_cmp)
                {
                    iterator_set_value(t_result, iterator_get_pointer(t_first));
                    t_result = iterator_next(t_result);
                }
            }
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_result;
}

forward_iterator_t _algo_remove(
    forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_last);

    return _algo_remove_varg(t_first, t_last, val_elemlist);
}

forward_iterator_t _algo_remove_varg(
    forward_iterator_t t_first, forward_iterator_t t_last, va_list val_elemlist)
{
    iterator_t t_next;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    t_first = _algo_find_varg(t_first, t_last, val_elemlist);

    if(iterator_equal(t_first, t_last))
    {
        return t_first;
    }
    else
    {
        t_next = iterator_next(t_first);
        return _algo_remove_copy_varg(t_next, t_last, t_first, val_elemlist);
    }
}

forward_iterator_t algo_remove_if(
    forward_iterator_t t_first, forward_iterator_t t_last, unary_function_t t_unary_op)
{
    iterator_t t_next;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    t_first = algo_find_if(t_first, t_last, t_unary_op);
    
    t_next = t_first;
    t_next = iterator_next(t_next);

    if(iterator_equal(t_first, t_last))
    {
        return t_first;
    }
    else
    {
        return algo_remove_copy_if(t_next, t_last, t_first, t_unary_op);
    }
}

output_iterator_t algo_remove_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op)
{
    bool_t t_cmp = false;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
    {
        (*t_unary_op)(iterator_get_pointer(t_first), &t_cmp);
        if(!t_cmp)
        {
            iterator_set_value(t_result, iterator_get_pointer(t_first));
            t_result = iterator_next(t_result);
        }
    }

    return t_result;
}

void _algo_replace_once(forward_iterator_t t_iterator, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_iterator);
    _algo_replace_once_varg(t_iterator, val_elemlist);
}

void _algo_replace_once_varg(
    forward_iterator_t t_iterator, va_list val_elemlist)
{
    void* pv_value = _iterator_allocate_init_elem(t_iterator);
    _type_get_varg_value(_iterator_get_typeinfo(t_iterator), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_iterator), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        iterator_set_value(t_iterator, string_c_str((string_t*)pv_value));
    }
    else
    {
        iterator_set_value(t_iterator, pv_value);
    }

    _iterator_deallocate_destroy_elem(t_iterator, pv_value);
    pv_value = NULL;
}

void _algo_replace_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_unary_op);
    _algo_replace_if_varg(t_first, t_last, t_unary_op, val_elemlist);
}

void _algo_replace_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    unary_function_t t_unary_op, va_list val_elemlist)
{
    void*  pv_value = NULL;
    bool_t t_result = false;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            (*t_unary_op)(iterator_get_pointer(t_first), &t_result);
            if(t_result)
            {
                iterator_set_value(t_first, string_c_str((string_t*)pv_value));
            }
        }
    }
    else
    {
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            (*t_unary_op)(iterator_get_pointer(t_first), &t_result);
            if(t_result)
            {
                iterator_set_value(t_first, pv_value);
            }
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;
}

output_iterator_t _algo_replace_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_unary_op);

    return _algo_replace_copy_if_varg(
        t_first, t_last, t_result, t_unary_op, val_elemlist);
}

output_iterator_t _algo_replace_copy_if_varg(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op,
    va_list val_elemlist)
{
    void*  pv_value = NULL;
    bool_t t_cmp = false;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            (*t_unary_op)(iterator_get_pointer(t_first), &t_cmp);
            if(t_cmp)
            {
                iterator_set_value(t_result, string_c_str((string_t*)pv_value));
            }
            else
            {
                iterator_set_value(t_result, iterator_get_pointer(t_first));
            }
            t_result = iterator_next(t_result);
        }
    }
    else
    {
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
        {
            (*t_unary_op)(iterator_get_pointer(t_first), &t_cmp);
            if(t_cmp)
            {
                iterator_set_value(t_result, pv_value);
            }
            else
            {
                iterator_set_value(t_result, iterator_get_pointer(t_first));
            }
            t_result = iterator_next(t_result);
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_result;
}

void algo_reverse(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last)
{
    assert(_iterator_valid_range(t_first, t_last, _BIDIRECTIONAL_ITERATOR));

    for(;;)
    {
        if(iterator_equal(t_first, t_last))
        {
            return;
        }
        t_last = iterator_prev(t_last);
        if(iterator_equal(t_first, t_last))
        {
            return;
        }

        algo_iter_swap(t_first, t_last);
        t_first = iterator_next(t_first);
    }
}

output_iterator_t algo_reverse_copy(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    output_iterator_t t_result)
{
    assert(_iterator_valid_range(t_first, t_last, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));

    while(!iterator_equal(t_first, t_last))
    {
        t_last = iterator_prev(t_last);
        iterator_set_value(t_result, iterator_get_pointer(t_last));
        t_result = iterator_next(t_result);
    }

    return t_result;
}

forward_iterator_t algo_rotate(
    forward_iterator_t t_first,
    forward_iterator_t t_middle,
    forward_iterator_t t_last)
{
    size_t t_distance = 0;

    assert(_iterator_valid_range(t_first, t_middle, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(t_middle, t_last, _FORWARD_ITERATOR));

    if(iterator_equal(t_first, t_middle) || 
       iterator_equal(t_middle, t_last))
    {
        return t_middle;
    }

    t_distance = iterator_distance(t_middle, t_last);

    if(_GET_ITERATOR_TYPE(t_first) == _FORWARD_ITERATOR &&
       _GET_ITERATOR_TYPE(t_middle) == _FORWARD_ITERATOR &&
       _GET_ITERATOR_TYPE(t_last) == _FORWARD_ITERATOR)
    {
        _rotate_forward(t_first, t_middle, t_last);
    }
    else
    {
        algo_reverse(t_first, t_middle);
        algo_reverse(t_middle, t_last);
        algo_reverse(t_first, t_last);
    }

    t_middle = t_first;
    t_middle = iterator_advance(t_middle, t_distance);

    return t_middle;
}

output_iterator_t algo_rotate_copy(
    forward_iterator_t t_first,
    forward_iterator_t t_middle,
    forward_iterator_t t_last,
    output_iterator_t t_result)
{
    assert(_iterator_valid_range(t_first, t_middle, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(t_middle, t_last, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));

    return algo_copy(t_first, t_middle, algo_copy(t_middle, t_last, t_result));
}

forward_iterator_t algo_swap_ranges(
    forward_iterator_t t_first1, forward_iterator_t t_last1,
    forward_iterator_t t_first2)
{
    assert(_iterator_valid_range(t_first1, t_last1, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));
    assert(_iterator_limit_type(t_first2, _FORWARD_ITERATOR));

    for(;
        !iterator_equal(t_first1, t_last1);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        algo_iter_swap(t_first1, t_first2);
    }

    return t_first2;
}

output_iterator_t algo_transform(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, unary_function_t t_unary_op)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(t_first);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(;
            !iterator_equal(t_first, t_last);
            t_first = iterator_next(t_first), t_result = iterator_next(t_result))
        {
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(t_first));
            (*t_unary_op)(iterator_get_pointer(t_first), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(t_result, string_c_str((string_t*)pv_value));
        }
    }
    else
    {
        for(;
            !iterator_equal(t_first, t_last);
            t_first = iterator_next(t_first), t_result = iterator_next(t_result))
        {
            (*t_unary_op)(iterator_get_pointer(t_first), pv_value);
            iterator_set_value(t_result, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_result;
}

output_iterator_t algo_transform_binary(
    input_iterator_t t_first1, input_iterator_t t_last1, 
    input_iterator_t t_first2, output_iterator_t t_result,
    binary_function_t t_binary_op)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));
    assert(_iterator_limit_type(t_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_result));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    pv_value = _iterator_allocate_init_elem(t_first1);

    if(strncmp(_iterator_get_typebasename(t_first1), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(;
            !iterator_equal(t_first1, t_last1);
            t_first1 = iterator_next(t_first1),
            t_first2 = iterator_next(t_first2),
            t_result = iterator_next(t_result))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2),
                (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(t_result, string_c_str((string_t*)pv_value));
        }
    }
    else
    {
        for(;
            !iterator_equal(t_first1, t_last1);
            t_first1 = iterator_next(t_first1),
            t_first2 = iterator_next(t_first2),
            t_result = iterator_next(t_result))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), pv_value);
            iterator_set_value(t_result, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(t_first1, pv_value);
    pv_value = NULL;

    return t_result;
}

forward_iterator_t algo_unique(
    forward_iterator_t t_first, forward_iterator_t t_last)
{
    return algo_unique_if(t_first, t_last, _fun_get_binary(t_first, _EQUAL_FUN));
}

forward_iterator_t algo_unique_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op)
{
    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    t_first = algo_adjacent_find_if(t_first, t_last, t_binary_op);
    return algo_unique_copy_if(t_first, t_last, t_first, t_binary_op);
}

output_iterator_t algo_unique_copy(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result)
{
    return algo_unique_copy_if(t_first, t_last, t_result,
        _fun_get_binary(t_first, _EQUAL_FUN));
}

output_iterator_t algo_unique_copy_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, binary_function_t t_binary_op)
{
    bool_t t_cmp = false;
    bool_t t_less = false;
    bool_t t_greater = false;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _EQUAL_FUN);
    }

    if(iterator_equal(t_first, t_last))
    {
        return t_result;
    }

    if(t_binary_op == fun_default_binary)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);

        iterator_set_value(t_result, iterator_get_pointer(t_first));
        t_first = iterator_next(t_first);
        while(!iterator_equal(t_first, t_last))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_result), iterator_get_pointer(t_first), &t_less);
            (*t_binary_op)(
                iterator_get_pointer(t_first), iterator_get_pointer(t_result), &t_greater);
            if(t_less || t_greater)
            {
                t_result = iterator_next(t_result);
                iterator_set_value(t_result, iterator_get_pointer(t_first));
            }

            t_first = iterator_next(t_first);
        }
    }
    else
    {
        iterator_set_value(t_result, iterator_get_pointer(t_first));
        t_first = iterator_next(t_first);
        while(!iterator_equal(t_first, t_last))
        {
            (*t_binary_op)(
                iterator_get_pointer(t_result), iterator_get_pointer(t_first), &t_cmp);
            if(!t_cmp)
            {
                t_result = iterator_next(t_result);
                iterator_set_value(t_result, iterator_get_pointer(t_first));
            }

            t_first = iterator_next(t_first);
        }
    }

    t_result = iterator_next(t_result);
    return t_result;
}

forward_iterator_t _algo_lower_bound(
    forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_last);

    return _algo_lower_bound_if_varg(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN), val_elemlist);
}

forward_iterator_t _algo_lower_bound_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_binary_op);

    return _algo_lower_bound_if_varg(t_first, t_last, t_binary_op, val_elemlist);
}

forward_iterator_t _algo_lower_bound_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    bool_t     t_result = false;
    size_t     t_len = 0;
    size_t     t_halflen = 0;
    iterator_t t_middle;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        t_len = iterator_distance(t_first, t_last);
        while(t_len > 0)
        {
            t_halflen = t_len >> 1;
            t_middle = t_first;
            t_middle = iterator_advance(t_middle, t_halflen);

            (*t_binary_op)(iterator_get_pointer(t_middle), string_c_str((string_t*)pv_value), &t_result);
            if(t_result) /* *t_middle < value */
            {
                t_first = t_middle;
                t_first = iterator_next(t_first);
                t_len = t_len - t_halflen - 1;
            }
            else
            {
                t_len = t_halflen;
            }
        }
    }
    else
    {
        t_len = iterator_distance(t_first, t_last);
        while(t_len > 0)
        {
            t_halflen = t_len >> 1;
            t_middle = t_first;
            t_middle = iterator_advance(t_middle, t_halflen);

            (*t_binary_op)(iterator_get_pointer(t_middle), pv_value, &t_result);
            if(t_result) /* *t_middle < value */
            {
                t_first = t_middle;
                t_first = iterator_next(t_first);
                t_len = t_len - t_halflen - 1;
            }
            else
            {
                t_len = t_halflen;
            }
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_first;
}

forward_iterator_t _algo_upper_bound(
    forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_last);

    return _algo_upper_bound_if_varg(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN), val_elemlist);
}

forward_iterator_t _algo_upper_bound_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_binary_op);

    return _algo_upper_bound_if_varg(t_first, t_last, t_binary_op, val_elemlist);
}

forward_iterator_t _algo_upper_bound_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    bool_t     t_result = false;
    size_t     t_len = 0;
    size_t     t_halflen = 0;
    iterator_t t_middle;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        t_len = iterator_distance(t_first, t_last);
        while(t_len > 0)
        {
            t_halflen = t_len >> 1;
            t_middle = t_first;
            t_middle = iterator_advance(t_middle, t_halflen);

            (*t_binary_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(t_middle), &t_result);
            if(t_result) /* value < *t_middle */
            {
                t_len = t_halflen;
            }
            else
            {
                t_first = t_middle;
                t_first = iterator_next(t_first);
                t_len = t_len - t_halflen - 1;
            }
        }
    }
    else
    {
        t_len = iterator_distance(t_first, t_last);
        while(t_len > 0)
        {
            t_halflen = t_len >> 1;
            t_middle = t_first;
            t_middle = iterator_advance(t_middle, t_halflen);

            (*t_binary_op)(pv_value, iterator_get_pointer(t_middle), &t_result);
            if(t_result) /* value < *t_middle */
            {
                t_len = t_halflen;
            }
            else
            {
                t_first = t_middle;
                t_first = iterator_next(t_first);
                t_len = t_len - t_halflen - 1;
            }
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    return t_first;
}

range_t _algo_equal_range(
    forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_last);

    return _algo_equal_range_if_varg(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN), val_elemlist);
}

range_t _algo_equal_range_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_binary_op);

    return _algo_equal_range_if_varg(t_first, t_last, t_binary_op, val_elemlist);
}

range_t _algo_equal_range_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    bool_t     t_result = false;
    bool_t     t_equal = false;
    size_t     t_len = 0;
    size_t     t_halflen = 0;
    iterator_t t_middle;
    iterator_t t_lower;
    iterator_t t_upper;
    range_t    t_range;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        t_len = iterator_distance(t_first, t_last);
        while(t_len > 0)
        {
            t_halflen = t_len >> 1;
            t_middle = t_first;
            t_middle = iterator_advance(t_middle, t_halflen);

            (*t_binary_op)(iterator_get_pointer(t_middle), string_c_str((string_t*)pv_value), &t_result);
            if(t_result) /* *t_middle < value */
            {
                t_first = t_middle;
                t_first = iterator_next(t_first);
                t_len = t_len - t_halflen - 1;
            }
            else
            {
                (*t_binary_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(t_middle), &t_result);
                if(t_result) /* value < *t_middle */
                {
                    t_len = t_halflen;
                }
                else
                {
                    t_lower = _algo_lower_bound_if_varg(
                        t_first, t_middle, t_binary_op, val_elemlist);
                    t_first = iterator_advance(t_first, t_len);
                    t_middle = iterator_next(t_middle);
                    t_upper = _algo_upper_bound_if_varg(
                        t_middle, t_first, t_binary_op, val_elemlist);

                    t_range.it_begin = t_lower;
                    t_range.it_end = t_upper;
                    t_equal = true;
                    break;
                }
            }
        }
    }
    else
    {
        t_len = iterator_distance(t_first, t_last);
        while(t_len > 0)
        {
            t_halflen = t_len >> 1;
            t_middle = t_first;
            t_middle = iterator_advance(t_middle, t_halflen);

            (*t_binary_op)(iterator_get_pointer(t_middle), pv_value, &t_result);
            if(t_result) /* *t_middle < value */
            {
                t_first = t_middle;
                t_first = iterator_next(t_first);
                t_len = t_len - t_halflen - 1;
            }
            else
            {
                (*t_binary_op)(pv_value, iterator_get_pointer(t_middle), &t_result);
                if(t_result) /* value < *t_middle */
                {
                    t_len = t_halflen;
                }
                else
                {
                    t_lower = _algo_lower_bound_if_varg(
                        t_first, t_middle, t_binary_op, val_elemlist);
                    t_first = iterator_advance(t_first, t_len);
                    t_middle = iterator_next(t_middle);
                    t_upper = _algo_upper_bound_if_varg(
                        t_middle, t_first, t_binary_op, val_elemlist);

                    t_range.it_begin = t_lower;
                    t_range.it_end = t_upper;
                    t_equal = true;
                    break;
                }
            }
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

    if(!t_equal)
    {
        t_range.it_begin = t_first;
        t_range.it_end = t_first;
    }
    return t_range;
}

bool_t _algo_binary_search(
    forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_last);

    return _algo_binary_search_if_varg(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN), val_elemlist);
}

bool_t _algo_binary_search_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_binary_op);

    return _algo_binary_search_if_varg(t_first, t_last, t_binary_op, val_elemlist);
}

bool_t _algo_binary_search_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    iterator_t t_lower;
    bool_t     t_cmp = false;
    bool_t     t_result = false;

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    t_lower = _algo_lower_bound_if_varg(t_first, t_last, t_binary_op, val_elemlist);
    pv_value = _iterator_allocate_init_elem(t_first);
    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_value);

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        if(!iterator_equal(t_lower, t_last))
        {
            (*t_binary_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(t_lower), &t_cmp);
            if(!t_cmp)
            {
                t_result = true;
            }
            else
            {
                t_result = false;
            }
        }
        else
        {
            t_result = false;
        }
    }
    else
    {
        if(!iterator_equal(t_lower, t_last))
        {
            (*t_binary_op)(pv_value, iterator_get_pointer(t_lower), &t_cmp);
            if(!t_cmp)
            {
                t_result = true;
            }
            else
            {
                t_result = false;
            }
        }
        else
        {
            t_result = false;
        }
    }

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;

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

void algo_random_shuffle(
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    algo_random_shuffle_if(t_first, t_last, fun_random_number);
}

void algo_random_shuffle_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    unary_function_t t_unary_op)
{
    iterator_t t_iterator;
    iterator_t t_tmp;
    size_t     t_len = 0;
    size_t     t_random = 0;

    assert(_iterator_valid_range(t_first, t_last, _RANDOM_ACCESS_ITERATOR));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    if(!iterator_equal(t_first, t_last))
    {
        for(t_iterator = t_first, t_iterator = iterator_next(t_iterator);
            !iterator_equal(t_iterator, t_last);
            t_iterator = iterator_next(t_iterator))
        {
            t_len = iterator_distance(t_first, t_iterator) + 1;
            (*t_unary_op)(&t_len, &t_random);
            if(t_len != 0)
            {
                t_random %= t_len;
            }
            t_tmp = t_first;
            t_tmp = iterator_advance(t_tmp, t_random);
            algo_iter_swap(t_iterator, t_tmp);
        }
    }
}

random_access_iterator_t algo_random_sample(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2)
{
    return algo_random_sample_if(
        t_first1, t_last1, t_first2, t_last2, fun_random_number);
}

random_access_iterator_t algo_random_sample_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2,
    unary_function_t t_unary_op)
{
    iterator_t t_in;
    iterator_t t_out;
    size_t     t_outlen = 0;
    size_t     t_inlen = 0;
    size_t     t_random = 0;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    for(t_in = t_first1, t_out = t_first2;
        !iterator_equal(t_in, t_last1) && !iterator_equal(t_out, t_last2);
        t_in = iterator_next(t_in), t_out = iterator_next(t_out))
    {
        iterator_set_value(t_out, iterator_get_pointer(t_in));
    }

    t_inlen = iterator_distance(t_first1, t_last1);
    t_outlen = iterator_distance(t_first2, t_last2);
    for(; !iterator_equal(t_in, t_last1); t_in = iterator_next(t_in))
    {
        t_inlen++;
        (*t_unary_op)(&t_inlen, &t_random);
        t_random %= t_inlen;
        if(t_random < t_outlen)
        {
            t_out = t_first2;
            t_out = iterator_advance(t_out, t_random);
            iterator_set_value(t_out, iterator_get_pointer(t_in));
        }
    }

    t_out = t_first2;
    t_out = iterator_advance(t_out, t_outlen < t_inlen ? t_outlen : t_inlen);

    return t_out;
}

output_iterator_t algo_random_sample_n(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, size_t t_count)
{
    return algo_random_sample_n_if(
        t_first, t_last, t_result, t_count, fun_random_number);
}

output_iterator_t algo_random_sample_n_if(
    input_iterator_t t_first, input_iterator_t t_last,
    output_iterator_t t_result, size_t t_count, unary_function_t t_unary_op)
{
    size_t t_len = 0;
    size_t t_tmp = 0;
    size_t t_random = 0;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    t_len = iterator_distance(t_first, t_last);
    t_tmp = t_count < t_len ? t_count : t_len;
    while(t_tmp > 0)
    {
        (*t_unary_op)(&t_len, &t_random);
        if(t_len != 0)
        {
            t_random %= t_len;
        }
        if(t_random < t_tmp)
        {
            iterator_set_value(t_result, iterator_get_pointer(t_first));
            t_result = iterator_next(t_result);
            t_tmp--;
        }
        t_first = iterator_next(t_first);
        t_len--;
    }

    return t_result;
}

void algo_partial_sort(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last)
{
    algo_partial_sort_if(t_first, t_middle, t_last,
        _fun_get_binary(t_first, _LESS_FUN));
}

void algo_partial_sort_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    iterator_t t_prev;
    iterator_t t_iterator;
    bool_t     t_result = false;

    assert(_iterator_valid_range(t_first, t_middle, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_valid_range(t_middle, t_last, _RANDOM_ACCESS_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    if(iterator_equal(t_first, t_middle))
    {
        return;
    }

    algo_make_heap_if(t_first, t_middle, t_binary_op);
    for(t_iterator = t_middle;
        !iterator_equal(t_iterator, t_last);
        t_iterator = iterator_next(t_iterator))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_iterator), iterator_get_pointer(t_first), &t_result);
        if(t_result)
        {
            algo_pop_heap_if(t_first, t_middle, t_binary_op);
            t_prev = t_middle;
            t_prev = iterator_prev(t_prev);
            algo_iter_swap(t_prev, t_iterator);
            algo_push_heap_if(t_first, t_middle, t_binary_op);
        }
    }
    algo_sort_heap_if(t_first, t_middle, t_binary_op);
}

random_access_iterator_t algo_partial_sort_copy(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2)
{
    return algo_partial_sort_copy_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _LESS_FUN));
}

random_access_iterator_t algo_partial_sort_copy_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    random_access_iterator_t t_first2, random_access_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    iterator_t t_iterator;
    iterator_t t_prev;
    bool_t     t_result = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }

    if(iterator_equal(t_first1, t_last1) || iterator_equal(t_first2, t_last2))
    {
        return t_first2;
    }

    for(t_iterator = t_first2;
        !iterator_equal(t_first1, t_last1) && !iterator_equal(t_iterator, t_last2);
        t_first1 = iterator_next(t_first1), t_iterator = iterator_next(t_iterator))
    {
        iterator_set_value(t_iterator, iterator_get_pointer(t_first1));
    }
    algo_make_heap_if(t_first2, t_iterator, t_binary_op);
    for(; !iterator_equal(t_first1, t_last1); t_first1 = iterator_next(t_first1))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(t_result) /* *t_first1 < *t_first2 */
        {
            algo_pop_heap_if(t_first2, t_iterator, t_binary_op);
            t_prev = t_iterator;
            t_prev = iterator_prev(t_prev);
            iterator_set_value(t_prev, iterator_get_pointer(t_first1));
            algo_push_heap_if(t_first2, t_iterator, t_binary_op);
        }
    }
    algo_sort_heap_if(t_first2, t_iterator, t_binary_op);

    return t_iterator;
}

void algo_sort(
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    algo_sort_if(t_first, t_last, _fun_get_binary(t_first, _LESS_FUN));
}

void algo_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    void*  pv_value = NULL;
    size_t t_len = 0;

    assert(_iterator_valid_range(t_first, t_last, _RANDOM_ACCESS_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    if(!iterator_equal(t_first, t_last))
    {
        pv_value = _iterator_allocate_init_elem(t_first);

        t_len = iterator_distance(t_first, t_last);
        if(t_len > _CSTL_SORT_THRESHOLD)
        {
            _intro_sort_if(t_first, t_last, t_binary_op, _lg(t_len)*2, pv_value);
        }
        else
        {
            _insertion_sort_if(t_first, t_last, t_binary_op, pv_value);
        }

        _iterator_deallocate_destroy_elem(t_first, pv_value);
        pv_value = NULL;
    }
}

void algo_inplace_merge(
    bidirectional_iterator_t t_first,
    bidirectional_iterator_t t_middle,
    bidirectional_iterator_t t_last)
{
    algo_inplace_merge_if(t_first, t_middle, t_last, _fun_get_binary(t_first, _LESS_FUN));
}

void algo_inplace_merge_if(
    bidirectional_iterator_t t_first,
    bidirectional_iterator_t t_middle,
    bidirectional_iterator_t t_last,
    binary_function_t t_binary_op)
{
    bool_t     t_result = false;
    void**      pc_buf = NULL;
    size_t     t_len1 = 0;
    size_t     t_i = 0;
    iterator_t t_index;

    assert(_iterator_valid_range(t_first, t_middle, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_valid_range(t_middle, t_last, _BIDIRECTIONAL_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    if(iterator_equal(t_first, t_middle) || iterator_equal(t_middle, t_last))
    {
        return;
    }

    t_len1 = iterator_distance(t_first, t_middle);
    pc_buf = (void**)malloc(sizeof(void*) * t_len1);
    if(pc_buf == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    /* copy elements of [t_first, t_middle) to buf */
    for(t_index = t_first, t_i = 0;
        !iterator_equal(t_index, t_middle);
        t_index = iterator_next(t_index), ++t_i)
    {
        pc_buf[t_i] = _iterator_allocate_init_elem(t_first);
        t_result = _iterator_get_typestyle(t_first);
        _iterator_get_typecopy(t_first)(pc_buf[t_i], iterator_get_pointer(t_index), &t_result);
        assert(t_result);
    }
    assert(t_i == t_len1);

    /* merge buf and [t_middle, t_last) to [t_first, t_last) */
    t_i = 0;
    while(!iterator_equal(t_middle, t_last) && t_i < t_len1)
    {
        (*t_binary_op)(iterator_get_pointer(t_middle), pc_buf[t_i], &t_result);
        if(t_result) /* t_middle < pc_buf */
        {
            iterator_set_value(t_first, iterator_get_pointer(t_middle));
            t_middle = iterator_next(t_middle);
        }
        else /* pc_buf <= t_middle */
        {
            iterator_set_value(t_first, pc_buf[t_i]);
            t_i++;
        }
        t_first = iterator_next(t_first);
    }

    if(iterator_equal(t_middle, t_last) && t_i < t_len1)
    {
        assert(!iterator_equal(t_first, t_last));
        for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first), ++t_i)
        {
            iterator_set_value(t_first, pc_buf[t_i]);
        }
    }
    assert(t_i == t_len1 && iterator_equal(t_first, t_middle));

    for(t_i = 0; t_i < t_len1; ++t_i)
    {
        _iterator_deallocate_destroy_elem(t_first, pc_buf[t_i]);
    }
    free(pc_buf);
    pc_buf = NULL;
}

void algo_nth_element(
    random_access_iterator_t t_first,
    random_access_iterator_t t_nth,
    random_access_iterator_t t_last)
{
    algo_nth_element_if(t_first, t_nth, t_last, _fun_get_binary(t_first, _LESS_FUN));
}

void algo_nth_element_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_nth,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    iterator_t t_pivot;
    iterator_t t_begin;
    iterator_t t_end;
    iterator_t t_prev;
    bool_t     t_result = false;
    void*      pv_value = NULL;

    assert(_iterator_valid_range(t_first, t_nth, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_valid_range(t_nth, t_last, _RANDOM_ACCESS_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(t_first);

    while(iterator_distance(t_first, t_last) > 3)
    {
        t_pivot = t_first;
        t_pivot = iterator_advance(t_pivot, iterator_distance(t_first, t_last) / 2);
        t_prev = t_last;
        t_prev = iterator_prev(t_prev);
        t_pivot = _median_of_three_if(t_first, t_pivot, t_prev, t_binary_op);
        iterator_get_value(t_pivot, pv_value);

        t_begin = t_first;
        t_end = t_last;
        for(;;)
        {
            /* move begin */
            (*t_binary_op)(iterator_get_pointer(t_begin), pv_value, &t_result);
            while(t_result)
            {
                t_begin = iterator_next(t_begin);
                (*t_binary_op)(iterator_get_pointer(t_begin), pv_value, &t_result);
            }
            /* move end */
            t_end = iterator_prev(t_end);
            (*t_binary_op)(pv_value, iterator_get_pointer(t_end), &t_result);
            while(t_result)
            {
                t_end = iterator_prev(t_end);
                (*t_binary_op)(pv_value, iterator_get_pointer(t_end), &t_result);
            }

            /* across */
            if(!iterator_less(t_begin, t_end))
            {
                t_pivot = t_begin;
                break;
            }
            else
            {
                algo_iter_swap(t_begin, t_end);
                t_begin = iterator_next(t_begin);
            }
        }

        if(iterator_less_equal(t_pivot, t_nth))
        {
            t_first = t_pivot;
        }
        else
        {
            t_last = t_pivot;
        }
    }

    _insertion_sort_if(t_first, t_last, t_binary_op, pv_value);

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;
}

bool_t algo_is_sorted(
    forward_iterator_t t_first, forward_iterator_t t_last)
{
    return algo_is_sorted_if(t_first, t_last, _fun_get_binary(t_first, _LESS_FUN));
}

bool_t algo_is_sorted_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op)
{
    bool_t     t_result = false;
    iterator_t t_next;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));
    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    if(iterator_equal(t_first, t_last))
    {
        return true;
    }

    for(t_next = t_first, t_next = iterator_next(t_next);
        !iterator_equal(t_next, t_last);
        t_first = t_next, t_next = iterator_next(t_next))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_next), iterator_get_pointer(t_first), &t_result);
        if(t_result) /* t_next < t_first */
        {
            return false;
        }
    }

    return true;
}

void algo_stable_sort(
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    algo_stable_sort_if(t_first, t_last, _fun_get_binary(t_first, _LESS_FUN));
}

void algo_stable_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    size_t t_len = 0;
    void*  pv_value = NULL;

    assert(_iterator_valid_range(t_first, t_last, _RANDOM_ACCESS_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    t_len = iterator_distance(t_first, t_last);
    if(t_len > _CSTL_SORT_THRESHOLD)
    {
        iterator_t t_middle = t_first;
        t_middle = iterator_advance(t_middle, t_len/2);

        algo_stable_sort_if(t_first, t_middle, t_binary_op);
        algo_stable_sort_if(t_middle, t_last, t_binary_op);
        algo_inplace_merge_if(t_first, t_middle, t_last, t_binary_op);
    }
    else
    {
        pv_value = _iterator_allocate_init_elem(t_first);

        _insertion_sort_if(t_first, t_last, t_binary_op, pv_value);

        _iterator_deallocate_destroy_elem(t_first, pv_value);
        pv_value = NULL;
    }
}

/** local function implementation section **/
static bidirectional_iterator_t _partition_biditer(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    unary_function_t t_unary_op)
{
    bool_t t_result = false;

    assert(_iterator_valid_range(t_first, t_last, _BIDIRECTIONAL_ITERATOR));

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    for(;;)
    {
        /* the first element that don't satisfy the t_unary_op */
        for(;;)
        {
            if(iterator_equal(t_first, t_last))
            {
                return t_first;
            }
            else
            {
                (*t_unary_op)(iterator_get_pointer(t_first), &t_result);
                if(t_result)
                {
                    t_first = iterator_next(t_first);
                }
                else
                {
                    break;
                }
            }
        }

        /* find the last element that satisfy the t_unary_op */
        t_last = iterator_prev(t_last);
        for(;;)
        {
            if(iterator_equal(t_first, t_last))
            {
                return t_first;
            }
            else
            {
                (*t_unary_op)(iterator_get_pointer(t_last), &t_result);
                if(!t_result)
                {
                    t_last = iterator_prev(t_last);
                }
                else
                {
                    break;
                }
            }
        }

        /* swap element */
        algo_iter_swap(t_first, t_last);
        t_first = iterator_next(t_first);
    }
}

static void _rotate_forward(
    forward_iterator_t t_first,
    forward_iterator_t t_middle,
    forward_iterator_t t_last)
{
    iterator_t t_iterator = t_middle;

    for(;;)
    {
        algo_iter_swap(t_first, t_iterator);
        t_first = iterator_next(t_first);
        t_iterator = iterator_next(t_iterator);

        /* the [t_first, t_middle) is end */
        if(iterator_equal(t_first, t_middle))
        {
            if(iterator_equal(t_iterator, t_last))
            {
                return;
            }

            t_middle = t_iterator;
        }
        /* the [t_middle, t_last) is end */
        else if(iterator_equal(t_iterator, t_last))
        {
            t_iterator = t_middle;
        }
    }
}

static void _insertion_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op, char* pc_value)
{
    iterator_t t_bound;
    bool_t     t_result = false;

    assert(pc_value != NULL);
    assert(t_binary_op != NULL);

    if(iterator_equal(t_first, t_last))
    {
        return;
    }

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        for(t_bound = t_first, t_bound = iterator_next(t_bound);
            !iterator_equal(t_bound, t_last);
            t_bound = iterator_next(t_bound))
        {
            string_assign_cstr((string_t*)pc_value, (char*)iterator_get_pointer(t_bound));

            (*t_binary_op)(string_c_str((string_t*)pc_value), iterator_get_pointer(t_first), &t_result);
            if(t_result) /* pc_value < *t_first */
            {
                iterator_t t_next = t_bound;
                t_next = iterator_next(t_next);
                algo_copy_backward(t_first, t_bound, t_next);
                iterator_set_value(t_first, string_c_str((string_t*)pc_value));
            }
            else
            {
                iterator_t t_tmp = t_bound;
                iterator_t t_prev = t_tmp;
                t_prev = iterator_prev(t_prev);
                (*t_binary_op)(string_c_str((string_t*)pc_value), iterator_get_pointer(t_prev), &t_result);
                while(t_result) /* pc_value < *t_prev */
                {
                    iterator_set_value(t_tmp, iterator_get_pointer(t_prev));
                    t_tmp = t_prev;
                    t_prev = iterator_prev(t_prev);

                    (*t_binary_op)(string_c_str((string_t*)pc_value), iterator_get_pointer(t_prev), &t_result);
                }

                iterator_set_value(t_tmp, string_c_str((string_t*)pc_value));
            }
        }
    }
    else
    {
        for(t_bound = t_first, t_bound = iterator_next(t_bound);
            !iterator_equal(t_bound, t_last);
            t_bound = iterator_next(t_bound))
        {
            iterator_get_value(t_bound, pc_value);

            (*t_binary_op)(pc_value, iterator_get_pointer(t_first), &t_result);
            if(t_result) /* pc_value < *t_first */
            {
                iterator_t t_next = t_bound;
                t_next = iterator_next(t_next);
                algo_copy_backward(t_first, t_bound, t_next);
                iterator_set_value(t_first, pc_value);
            }
            else
            {
                iterator_t t_tmp = t_bound;
                iterator_t t_prev = t_tmp;
                t_prev = iterator_prev(t_prev);
                (*t_binary_op)(pc_value, iterator_get_pointer(t_prev), &t_result);
                while(t_result) /* pc_value < *t_prev */
                {
                    iterator_set_value(t_tmp, iterator_get_pointer(t_prev));
                    t_tmp = t_prev;
                    t_prev = iterator_prev(t_prev);

                    (*t_binary_op)(pc_value, iterator_get_pointer(t_prev), &t_result);
                }

                iterator_set_value(t_tmp, pc_value);
            }
        }
    }
}

static random_access_iterator_t _median_of_three_if(
    random_access_iterator_t t_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(t_binary_op != NULL);

    (*t_binary_op)(
        iterator_get_pointer(t_first), iterator_get_pointer(t_middle), &t_result);
    if(t_result) /* t_first < t_middle */
    {
        (*t_binary_op)(
            iterator_get_pointer(t_middle), iterator_get_pointer(t_last), &t_result);
        if(t_result) /* t_first < t_middle < t_last */
        {
            return t_middle;
        }
        else /* t_last <= t_middle */
        {
            (*t_binary_op)(
                iterator_get_pointer(t_first), iterator_get_pointer(t_last), &t_result);
            if(t_result) /* t_first < t_last <= t_middle */
            {
                return t_last;
            }
            else /* t_last <= t_first <= t_middle */
            {
                return t_first;
            }
        }
    }
    else /* t_middle <= t_first */
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first), iterator_get_pointer(t_last), &t_result);
        if(t_result) /* t_middle <= t_first < t_last */
        {
            return t_first;
        }
        else /* t_last <= t_first */
        {
            (*t_binary_op)(
                iterator_get_pointer(t_middle), iterator_get_pointer(t_last), &t_result);
            if(t_result) /* t_middle < t_last <= t_first */
            {
                return t_last;
            }
            else /* t_last <= t_middle <= t_first */
            {
                return t_middle;
            }
        }
    }
}

static size_t _lg(size_t t_n)
{
    size_t t_k = 0;
    for(t_k = 0; t_n > 1; t_n >>= 1)
    {
        t_k++;
    }

    return t_k;
}

static void _intro_sort_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op, size_t t_depth, char* pc_value)
{
    iterator_t t_pivot;
    iterator_t t_begin;
    iterator_t t_end;
    iterator_t t_prev;
    iterator_t t_next;
    bool_t     t_result = false;

    assert(pc_value != NULL);
    assert(t_binary_op != NULL);

    t_next = t_first;
    t_next = iterator_next(t_next);
    if(iterator_equal(t_first, t_last) || iterator_equal(t_next, t_last))
    {
        return;
    }

    if(t_depth == 0)
    {
        /* do heap sort */
        algo_partial_sort_if(t_first, t_last, t_last, t_binary_op);
        return;
    }
    t_depth--;

    t_pivot = t_first;
    t_pivot = iterator_advance(t_pivot, iterator_distance(t_first, t_last) / 2);
    t_prev = t_last;
    t_prev = iterator_prev(t_prev);
    t_pivot = _median_of_three_if(t_first, t_pivot, t_prev, t_binary_op);

    /* the pc_value must be string_t type when the container type is char* */
    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        string_assign_cstr((string_t*)pc_value, (char*)iterator_get_pointer(t_pivot));
        t_begin = t_first;
        t_end = t_last;
        for(;;)
        {
            /* move begin */
            (*t_binary_op)(iterator_get_pointer(t_begin), string_c_str((string_t*)pc_value), &t_result);
            while(t_result)
            {
                t_begin = iterator_next(t_begin);
                (*t_binary_op)(iterator_get_pointer(t_begin), string_c_str((string_t*)pc_value), &t_result);
            }
            /* move end */
            t_end = iterator_prev(t_end);
            (*t_binary_op)(string_c_str((string_t*)pc_value), iterator_get_pointer(t_end), &t_result);
            while(t_result)
            {
                t_end = iterator_prev(t_end);
                (*t_binary_op)(string_c_str((string_t*)pc_value), iterator_get_pointer(t_end), &t_result);
            }

            /* across */
            if(!iterator_less(t_begin, t_end))
            {
                t_pivot = t_begin;
                break;
            }
            else
            {
                algo_iter_swap(t_begin, t_end);
                t_begin = iterator_next(t_begin);
            }
        }
    }
    else
    {
        iterator_get_value(t_pivot, pc_value);
        t_begin = t_first;
        t_end = t_last;
        for(;;)
        {
            /* move begin */
            (*t_binary_op)(iterator_get_pointer(t_begin), pc_value, &t_result);
            while(t_result)
            {
                t_begin = iterator_next(t_begin);
                (*t_binary_op)(iterator_get_pointer(t_begin), pc_value, &t_result);
            }
            /* move end */
            t_end = iterator_prev(t_end);
            (*t_binary_op)(pc_value, iterator_get_pointer(t_end), &t_result);
            while(t_result)
            {
                t_end = iterator_prev(t_end);
                (*t_binary_op)(pc_value, iterator_get_pointer(t_end), &t_result);
            }

            /* across */
            if(!iterator_less(t_begin, t_end))
            {
                t_pivot = t_begin;
                break;
            }
            else
            {
                algo_iter_swap(t_begin, t_end);
                t_begin = iterator_next(t_begin);
            }
        }
    }


    /* sort [t_first, t_pivot) */
    _intro_sort_if(t_first, t_pivot, t_binary_op, t_depth, pc_value);
    /* sort [t_pivot, t_last) */
    _intro_sort_if(t_pivot, t_last, t_binary_op, t_depth, pc_value);
}

/** eof **/

