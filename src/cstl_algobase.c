/*
 *  The implementation of base algorithm.
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
#include "cfunctional.h"
#include "cstl_tools.h"
#include "cutility.h"

#include "cstl_algobase.h"
#include "cstl_algobase_private.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
/*
 * Copy and copy backward trivial.
 */
static output_iterator_t _algo_copy_trivial(
    input_iterator_t t_first, input_iterator_t t_last, output_iterator_t t_result);
static bidirectional_iterator_t _algo_copy_backward_trivial(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    bidirectional_iterator_t t_result);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
bool_t algo_equal(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2)
{
    char* s_typename = _tools_get_typename(t_first1);
    assert(s_typename != NULL);

    return algo_equal_if(
        t_first1, t_last1, t_first2, _fun_get_binary(s_typename, _EQUAL_FUN));
}

bool_t algo_equal_if(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_tools_valid_iterator_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_first2, _INPUT_ITERATOR));
    assert(_tools_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    for(;
        !iterator_equal(t_first1, t_last1);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(!t_result)
        {
            return false;
        }
    }

    return true;
}

void _algo_fill(
    forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_last);
    _algo_fill_varg(t_first, t_last, val_elemlist);
}

void _algo_fill_varg(
    forward_iterator_t t_first, forward_iterator_t t_last, va_list val_elemlist)
{
    char* pc_value = NULL;

    assert(_tools_valid_iterator_range(t_first, t_last, _FORWARD_ITERATOR));

    pc_value = (char*)malloc(_tools_get_typesize(t_first));
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    _get_varg_value(
        pc_value, val_elemlist,
        _tools_get_typesize(t_first), _tools_get_typename(t_first));

    for(; !iterator_equal(t_first, t_last); t_first = iterator_next(t_first))
    {
        iterator_set_value(t_first, pc_value);
    }

    free(pc_value);
    pc_value = NULL;
}

output_iterator_t _algo_fill_n(
    output_iterator_t t_first, size_t t_fillsize, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_fillsize);
    return _algo_fill_n_varg(t_first, t_fillsize, val_elemlist);
}

output_iterator_t _algo_fill_n_varg(
    output_iterator_t t_first, size_t t_fillsize, va_list val_elemlist)
{
    size_t t_index = 0;
    char*  pc_value = NULL;
 
    pc_value = (char*)malloc(_tools_get_typesize(t_first));
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    _get_varg_value(
        pc_value, val_elemlist,
        _tools_get_typesize(t_first), _tools_get_typename(t_first));

    for(t_index = 0; t_index < t_fillsize; ++t_index, t_first = iterator_next(t_first))
    {
        iterator_set_value(t_first, pc_value);
    }

    free(pc_value);
    pc_value = NULL;

    return t_first;
}

void algo_swap(forward_iterator_t t_first, forward_iterator_t t_second)
{
    algo_iter_swap(t_first, t_second);
}

void algo_iter_swap(forward_iterator_t t_first, forward_iterator_t t_second)
{
    char* pc_value = NULL;

    assert(_tools_same_elem_type(t_first, t_second));

    pc_value = (char*)malloc(_tools_get_typesize(t_first));
    if(pc_value == NULL)
    {
        fprintf(stderr, "CSTL FATAL ERROR: memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    iterator_get_value(t_first, pc_value);
    iterator_set_value(t_first, iterator_get_pointer(t_second));
    iterator_set_value(t_second, pc_value);

    free(pc_value);
    pc_value = NULL;
}

bool_t algo_lexicographical_compare(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2)
{
    char* s_typename = _tools_get_typename(t_first1);
    assert(s_typename != NULL);

    return algo_lexicographical_compare_if(
        t_first1, t_last1, t_first2, t_last2, _fun_get_binary(s_typename, _LESS_FUN));
}

bool_t algo_lexicographical_compare_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_tools_valid_iterator_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_tools_valid_iterator_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_tools_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }
    for(;
        !iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(t_result)
        {
            return true;
        }
        (*t_binary_op)(
            iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_result);
        if(t_result)
        {
            return false;
        }
    }

    if(iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int algo_lexicographical_compare_3way(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2)
{
    char* s_typename = _tools_get_typename(t_first1);
    assert(s_typename != NULL);

    return algo_lexicographical_compare_3way_if(
        t_first1, t_last1, t_first2, t_last2, _fun_get_binary(s_typename, _LESS_FUN));
}

int algo_lexicographical_compare_3way_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_tools_valid_iterator_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_tools_valid_iterator_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_tools_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }
    for(;
        !iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(t_result)
        {
            return -1;
        }
        (*t_binary_op)(
            iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_result);
        if(t_result)
        {
            return 1;
        }
    }

    if(iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        return -1;
    }
    else if(iterator_equal(t_first1, t_last1) && iterator_equal(t_first2, t_last2))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

input_iterator_t algo_max(input_iterator_t t_first, input_iterator_t t_second)
{
    char* s_typename = _tools_get_typename(t_first);
    assert(s_typename != NULL);

    return algo_max_if(t_first, t_second, _fun_get_binary(s_typename, _LESS_FUN));
}

input_iterator_t algo_max_if(
    input_iterator_t t_first, input_iterator_t t_second, binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_limit_type(t_first, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_second, _INPUT_ITERATOR));
    assert(_tools_same_elem_type(t_first, t_second));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    (*t_binary_op)(
        iterator_get_pointer(t_first), iterator_get_pointer(t_second), &t_result);
    if(!t_result)
    {
        return t_first;
    }
    else
    {
        return t_second;
    }
}

input_iterator_t algo_min(input_iterator_t t_first, input_iterator_t t_second)
{
    char* s_typename = _tools_get_typename(t_first);
    assert(s_typename != NULL);

    return algo_min_if(t_first, t_second, _fun_get_binary(s_typename, _LESS_FUN));
}

input_iterator_t algo_min_if(
    input_iterator_t t_first, input_iterator_t t_second, binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_limit_type(t_first, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_second, _INPUT_ITERATOR));
    assert(_tools_same_elem_type(t_first, t_second));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    (*t_binary_op)(
        iterator_get_pointer(t_first), iterator_get_pointer(t_second), &t_result);
    if(t_result)
    {
        return t_first;
    }
    else
    {
        return t_second;
    }
}

pair_t algo_mismatch(
    input_iterator_t t_first1,
    input_iterator_t t_last1,
    input_iterator_t t_first2)
{
    char* s_typename = _tools_get_typename(t_first1);
    assert(s_typename != NULL);

    return algo_mismatch_if(
        t_first1, t_last1, t_first2, _fun_get_binary(s_typename, _EQUAL_FUN));
}

pair_t algo_mismatch_if(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;
    pair_t t_pair = create_pair(input_iterator_t, input_iterator_t);

    assert(_tools_valid_iterator_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_first2, _INPUT_ITERATOR));
    assert(_tools_same_elem_type(t_first1, t_first1));

    pair_init(&t_pair);
    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }
    for(;
        !iterator_equal(t_first1, t_last1);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(!t_result)
        {
            break;
        }
    }

    pair_make(&t_pair, t_first1, t_first2);
    return t_pair;
}

output_iterator_t algo_copy(
    input_iterator_t t_first, input_iterator_t t_last, output_iterator_t t_result)
{
    assert(_tools_valid_iterator_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_tools_same_elem_type(t_first, t_result));

    if((_GET_CONTAINER_TYPE(t_first) == _VECTOR_CONTAINER ||
        _GET_CONTAINER_TYPE(t_first) == _BASIC_STRING_CONTAINER) &&
       (_GET_CONTAINER_TYPE(t_result) == _VECTOR_CONTAINER ||
        _GET_CONTAINER_TYPE(t_result) == _BASIC_STRING_CONTAINER))
    {
        return _algo_copy_trivial(t_first, t_last, t_result);
    }

    for(;
        !iterator_equal(t_first, t_last);
        t_first = iterator_next(t_first), t_result = iterator_next(t_result))
    {
        iterator_set_value(t_result, iterator_get_pointer(t_first));
    }

    return t_result;
}

output_iterator_t algo_copy_n(
    input_iterator_t t_first, size_t t_count, output_iterator_t t_result)
{
    input_iterator_t t_last = t_first;
    t_last = iterator_advance(t_last, t_count);

    return algo_copy(t_first, t_last, t_result);
}

bidirectional_iterator_t algo_copy_backward(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    bidirectional_iterator_t t_result)
{
    assert(_tools_valid_iterator_range(t_first, t_last, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_limit_type(t_result, _BIDIRECTIONAL_ITERATOR));
    assert(_tools_same_elem_type(t_first, t_result));

    if((_GET_CONTAINER_TYPE(t_first) == _VECTOR_CONTAINER ||
        _GET_CONTAINER_TYPE(t_first) == _BASIC_STRING_CONTAINER) &&
       (_GET_CONTAINER_TYPE(t_result) == _VECTOR_CONTAINER ||
        _GET_CONTAINER_TYPE(t_result) == _BASIC_STRING_CONTAINER))
    {
        return _algo_copy_backward_trivial(t_first, t_last, t_result);
    }

    while(!iterator_equal(t_first, t_last))
    {
        t_last = iterator_prev(t_last);
        t_result = iterator_prev(t_result);
        iterator_set_value(t_result, iterator_get_pointer(t_last));
    }

    return t_result;
}

/** local function implementation section **/
static output_iterator_t _algo_copy_trivial(
    input_iterator_t t_first, input_iterator_t t_last, output_iterator_t t_result)
{
    size_t t_len = iterator_distance(t_first, t_last) * _tools_get_typesize(t_first);

    memmove((void*)iterator_get_pointer(t_result), iterator_get_pointer(t_first), t_len);

    _GET_VECTOR_COREPOS(t_result) += t_len;

    return t_result;
}

static bidirectional_iterator_t _algo_copy_backward_trivial(
    bidirectional_iterator_t t_first, bidirectional_iterator_t t_last,
    bidirectional_iterator_t t_result)
{
    size_t t_len = iterator_distance(t_first, t_last) * _tools_get_typesize(t_first);

    _GET_VECTOR_COREPOS(t_result) -= t_len;

    memmove((void*)iterator_get_pointer(t_result), iterator_get_pointer(t_first), t_len);

    return t_result;
}

/** eof **/

