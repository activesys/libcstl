/*
 *  The implementation of numeric.
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
#include <string.h>
#include <stdarg.h>

#include <cstl/cstl_alloc.h>
#include <cstl/cstl_types.h>
#include <cstl/citerator.h>
#include <cstl/cfunctional.h>

#include <cstl/cstl_numeric.h>
#include <cstl/cstl_numeric_private.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* numeric algorithm */
void _algo_accumulate(
    input_iterator_t t_first, input_iterator_t t_last, void* pv_output, ...)
{
    va_list val_elemlist;

    if(_iterator_get_typestyle(t_first) == _TYPE_C_BUILTIN &&
       strncmp(_iterator_get_typebasename(t_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0)
    {
        va_start(val_elemlist, pv_output);
        _algo_accumulate_if_varg(t_first, t_last, _fun_get_binary(t_first, _PLUS_FUN),
            pv_output, val_elemlist);
        va_end(val_elemlist);
    }
}

void _algo_accumulate_if(input_iterator_t t_first, input_iterator_t t_last,
    binary_function_t t_binary_op, void* pv_output, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pv_output);
    _algo_accumulate_if_varg(t_first, t_last, t_binary_op, pv_output, val_elemlist);
    va_end(val_elemlist);
}

void _algo_accumulate_if_varg(input_iterator_t t_first, input_iterator_t t_last,
    binary_function_t t_binary_op, void* pv_output, va_list val_elemlist)
{
    iterator_t t_iter;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(pv_output != NULL);

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _PLUS_FUN);
    }

    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pv_output);
    for(t_iter = t_first; !iterator_equal(t_iter, t_last); t_iter = iterator_next(t_iter))
    {
        (*t_binary_op)(pv_output, iterator_get_pointer(t_iter), pv_output);
    }
}

void _algo_inner_product(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    void* pv_output, ...)
{
    va_list val_elemlist;

    if(_iterator_get_typestyle(t_first1) == _TYPE_C_BUILTIN &&
       strncmp(_iterator_get_typebasename(t_first1), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0)
    {
        va_start(val_elemlist, pv_output);
        _algo_inner_product_if_varg(t_first1, t_last1, t_first2,
            _fun_get_binary(t_first1, _PLUS_FUN), _fun_get_binary(t_first1, _MULTIPLIES_FUN),
            pv_output, val_elemlist);
        va_end(val_elemlist);
    }
}

void _algo_inner_product_if(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    binary_function_t t_binary_op1, binary_function_t t_binary_op2, void* pv_output, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pv_output);
    _algo_inner_product_if_varg(t_first1, t_last1, t_first2,
        t_binary_op1, t_binary_op2, pv_output, val_elemlist);
    va_end(val_elemlist);
}

void _algo_inner_product_if_varg(
    input_iterator_t t_first1, input_iterator_t t_last1, input_iterator_t t_first2,
    binary_function_t t_binary_op1, binary_function_t t_binary_op2,
    void* pv_output, va_list val_elemlist)
{
    iterator_t t_index1;
    iterator_t t_index2;
    void*      pv_tmp = NULL;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));
    assert(pv_output != NULL);

    pv_tmp = _iterator_allocate_init_elem(t_first1);
    _type_get_varg_value(_iterator_get_typeinfo(t_first1), val_elemlist, pv_output);

    if(t_binary_op1 == NULL)
    {
        t_binary_op1 = _fun_get_binary(t_first1, _PLUS_FUN);
    }
    if(t_binary_op2 == NULL)
    {
        t_binary_op2 = _fun_get_binary(t_first1, _MULTIPLIES_FUN);
    }

    for(t_index1 = t_first1, t_index2 = t_first2;
        !iterator_equal(t_index1, t_last1);
        t_index1 = iterator_next(t_index1), t_index2 = iterator_next(t_index2))
    {
        (*t_binary_op2)(iterator_get_pointer(t_index1), iterator_get_pointer(t_index2), pv_tmp);
        (*t_binary_op1)(pv_output, pv_tmp, pv_output);
    }

    _iterator_deallocate_destroy_elem(t_first1, pv_tmp);
}

void algo_power(input_iterator_t t_iterator, size_t t_power, void* pv_output)
{
    algo_power_if(t_iterator, t_power,
        _fun_get_binary(t_iterator, _MULTIPLIES_FUN), pv_output);
}

void algo_power_if(input_iterator_t t_iterator, size_t t_power,
    binary_function_t t_binary_op, void* pv_output)
{
    size_t t_index = 0;
    bool_t t_result = false;

    assert(_iterator_limit_type(t_iterator, _INPUT_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_iterator, _MULTIPLIES_FUN);
    }

    t_result = _iterator_get_typesize(t_iterator);
    _iterator_get_typecopy(t_iterator)(pv_output, iterator_get_pointer(t_iterator), &t_result);
    assert(t_result);
    if(t_power > 0)
    {
        for(t_index = 1; t_index < t_power; ++t_index)
        {
            (*t_binary_op)(pv_output, iterator_get_pointer(t_iterator), pv_output);
        }
    }
}

output_iterator_t algo_adjacent_difference(
    input_iterator_t t_first, input_iterator_t t_last, output_iterator_t t_result)
{
    return algo_adjacent_difference_if(t_first, t_last, t_result,
        _fun_get_binary(t_first, _MINUS_FUN));
}

output_iterator_t algo_adjacent_difference_if(
    input_iterator_t t_first, input_iterator_t t_last, output_iterator_t t_result,
    binary_function_t t_binary_op)
{
    iterator_t t_index;
    bool_t     t_typesize = 0;
    char*      pc_value = NULL;
    char*      pc_tmp = NULL;
    char*      pc_result = NULL;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));

    if(iterator_equal(t_first, t_last))
    {
        return t_result;
    }

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _MINUS_FUN);
    }

    pc_value = _iterator_allocate_init_elem(t_first);
    pc_tmp = _iterator_allocate_init_elem(t_first);
    pc_result = _iterator_allocate_init_elem(t_first);

    iterator_get_value(t_first, pc_value);
    iterator_set_value(t_result, pc_value);
    for(t_index = t_first, t_index = iterator_next(t_index);
        !iterator_equal(t_index, t_last);
        t_index = iterator_next(t_index))
    {
        iterator_get_value(t_index, pc_tmp);
        (*t_binary_op)(pc_tmp, pc_value, pc_result);
        t_result = iterator_next(t_result);
        iterator_set_value(t_result, pc_result);

        t_typesize = _iterator_get_typesize(t_first);
        _iterator_get_typecopy(t_first)(pc_value, pc_tmp, &t_typesize);
        assert(t_typesize);
    }

    _iterator_deallocate_destroy_elem(t_first, pc_value);
    _iterator_deallocate_destroy_elem(t_first, pc_tmp);
    _iterator_deallocate_destroy_elem(t_first, pc_result);
    pc_value = NULL;
    pc_tmp = NULL;
    pc_result = NULL;

    t_result = iterator_next(t_result);
    return t_result;
}

output_iterator_t algo_partial_sum(
    input_iterator_t t_first, input_iterator_t t_last, output_iterator_t t_result)
{
    return algo_partial_sum_if(t_first, t_last, t_result,
        _fun_get_binary(t_first, _PLUS_FUN));
}

output_iterator_t algo_partial_sum_if(
    input_iterator_t t_first, input_iterator_t t_last, output_iterator_t t_result,
    binary_function_t t_binary_op)
{
    iterator_t t_index;
    char*      pc_value = NULL;

    assert(_iterator_valid_range(t_first, t_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(t_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first, t_result));

    if(iterator_equal(t_first, t_last))
    {
        return t_result;
    }

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first, _PLUS_FUN);
    }

    pc_value = _iterator_allocate_init_elem(t_first);

    iterator_get_value(t_first, pc_value);
    iterator_set_value(t_result, pc_value);
    for(t_index = t_first, t_index = iterator_next(t_index);
        !iterator_equal(t_index, t_last);
        t_index = iterator_next(t_index))
    {
        (*t_binary_op)(pc_value, iterator_get_pointer(t_index), pc_value);
        t_result = iterator_next(t_result);
        iterator_set_value(t_result, pc_value);
    }

    _iterator_deallocate_destroy_elem(t_first, pc_value);
    pc_value = NULL;

    t_result = iterator_next(t_result);
    return t_result;
}

void _algo_iota(forward_iterator_t t_first, forward_iterator_t t_last, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_last);
    _algo_iota_varg(t_first, t_last, val_elemlist);
    va_end(val_elemlist);
}

void _algo_iota_varg(
    forward_iterator_t t_first, forward_iterator_t t_last, va_list val_elemlist)
{
    iterator_t       t_index;
    char*            pc_value = NULL;
    unary_function_t t_unary_op;

    assert(_iterator_valid_range(t_first, t_last, _FORWARD_ITERATOR));

    pc_value = _iterator_allocate_init_elem(t_first);

    _type_get_varg_value(_iterator_get_typeinfo(t_first), val_elemlist, pc_value);
    t_unary_op = _fun_get_unary(t_first, _INCREASE_FUN);
    for(t_index = t_first;
        !iterator_equal(t_index, t_last);
        t_index = iterator_next(t_index))
    {
        iterator_set_value(t_index, pc_value);
        (*t_unary_op)(pc_value, pc_value);
    }

    _iterator_deallocate_destroy_elem(t_first, pc_value);
    pc_value = NULL;
}

/** local function implementation section **/

/** eof **/

