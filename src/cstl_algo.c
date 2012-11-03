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

forward_iterator_t _algo_lower_bound(
    forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    forward_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_last);
    t_iter = _algo_lower_bound_if_varg(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN), val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

forward_iterator_t _algo_lower_bound_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...)
{
    forward_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_binary_op);
    t_iter = _algo_lower_bound_if_varg(t_first, t_last, t_binary_op, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
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
    forward_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_last);
    t_iter = _algo_upper_bound_if_varg(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN), val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

forward_iterator_t _algo_upper_bound_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...)
{
    forward_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_binary_op);
    t_iter = _algo_upper_bound_if_varg(t_first, t_last, t_binary_op, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
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
    range_t t_range;
    va_list val_elemlist;

    va_start(val_elemlist, t_last);
    t_range = _algo_equal_range_if_varg(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN), val_elemlist);
    va_end(val_elemlist);

    return t_range;
}

range_t _algo_equal_range_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...)
{
    range_t t_range;
    va_list val_elemlist;

    va_start(val_elemlist, t_binary_op);
    t_range = _algo_equal_range_if_varg(t_first, t_last, t_binary_op, val_elemlist);
    va_end(val_elemlist);

    return t_range;
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
    va_list    val_elemlist_copy; /* copy val_elemlist for lower bound and upper bound*/

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(t_first);
    va_copy(val_elemlist_copy, val_elemlist);
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
                    va_list val_elemlist_lb_copy; /* copy val_elemlist for lower bound */
                    va_list val_elemlist_ub_copy; /* copy val_elemlist for upper bound */

                    va_copy(val_elemlist_lb_copy, val_elemlist_copy);
                    va_copy(val_elemlist_ub_copy, val_elemlist_copy);

                    t_lower = _algo_lower_bound_if_varg(
                        t_first, t_middle, t_binary_op, val_elemlist_lb_copy);
                    t_first = iterator_advance(t_first, t_len);
                    t_middle = iterator_next(t_middle);
                    t_upper = _algo_upper_bound_if_varg(
                        t_middle, t_first, t_binary_op, val_elemlist_ub_copy);

                    va_end(val_elemlist_lb_copy);
                    va_end(val_elemlist_ub_copy);

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
                    va_list val_elemlist_lb_copy; /* copy val_elemlist for lower bound */
                    va_list val_elemlist_ub_copy; /* copy val_elemlist for upper bound */

                    va_copy(val_elemlist_lb_copy, val_elemlist_copy);
                    va_copy(val_elemlist_ub_copy, val_elemlist_copy);

                    t_lower = _algo_lower_bound_if_varg(
                        t_first, t_middle, t_binary_op, val_elemlist_lb_copy);
                    t_first = iterator_advance(t_first, t_len);
                    t_middle = iterator_next(t_middle);
                    t_upper = _algo_upper_bound_if_varg(
                        t_middle, t_first, t_binary_op, val_elemlist_ub_copy);

                    va_end(val_elemlist_lb_copy);
                    va_end(val_elemlist_ub_copy);

                    t_range.it_begin = t_lower;
                    t_range.it_end = t_upper;
                    t_equal = true;
                    break;
                }
            }
        }
    }

    va_end(val_elemlist_copy);
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
    bool_t t_result = false;
    va_list val_elemlist;

    va_start(val_elemlist, t_last);
    t_result = _algo_binary_search_if_varg(t_first, t_last,
        _fun_get_binary(t_first, _LESS_FUN), val_elemlist);
    va_end(val_elemlist);

    return t_result;
}

bool_t _algo_binary_search_if(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, ...)
{
    bool_t t_result = false;
    va_list val_elemlist;

    va_start(val_elemlist, t_binary_op);
    t_result = _algo_binary_search_if_varg(t_first, t_last, t_binary_op, val_elemlist);
    va_end(val_elemlist);

    return t_result;
}

bool_t _algo_binary_search_if_varg(
    forward_iterator_t t_first, forward_iterator_t t_last,
    binary_function_t t_binary_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    iterator_t t_lower;
    bool_t     t_cmp = false;
    bool_t     t_result = false;
    va_list    val_elemlist_copy; /* copy val_elemlist for lower bound */

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _LESS_FUN);
    }

    va_copy(val_elemlist_copy, val_elemlist);
    t_lower = _algo_lower_bound_if_varg(t_first, t_last, t_binary_op, val_elemlist_copy);
    va_end(val_elemlist_copy);

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

    if(strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        while(iterator_distance(t_first, t_last) > 3)
        {
            t_pivot = t_first;
            t_pivot = iterator_advance(t_pivot, iterator_distance(t_first, t_last) / 2);
            t_prev = t_last;
            t_prev = iterator_prev(t_prev);
            t_pivot = _algo_median_of_three_if(t_first, t_pivot, t_prev, t_binary_op);
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(t_pivot));

            t_begin = t_first;
            t_end = t_last;
            for(;;)
            {
                /* move begin */
                (*t_binary_op)(iterator_get_pointer(t_begin), string_c_str((string_t*)pv_value), &t_result);
                while(t_result)
                {
                    t_begin = iterator_next(t_begin);
                    (*t_binary_op)(iterator_get_pointer(t_begin), string_c_str((string_t*)pv_value), &t_result);
                }
                /* move end */
                t_end = iterator_prev(t_end);
                (*t_binary_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(t_end), &t_result);
                while(t_result)
                {
                    t_end = iterator_prev(t_end);
                    (*t_binary_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(t_end), &t_result);
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
    }
    else
    {
        while(iterator_distance(t_first, t_last) > 3)
        {
            t_pivot = t_first;
            t_pivot = iterator_advance(t_pivot, iterator_distance(t_first, t_last) / 2);
            t_prev = t_last;
            t_prev = iterator_prev(t_prev);
            t_pivot = _algo_median_of_three_if(t_first, t_pivot, t_prev, t_binary_op);
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
    }

    _algo_insertion_sort_if(t_first, t_last, t_binary_op, pv_value);

    _iterator_deallocate_destroy_elem(t_first, pv_value);
    pv_value = NULL;
}

/** local function implementation section **/

/** eof **/

