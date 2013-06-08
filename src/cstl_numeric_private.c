/*
 *  The implementation of private numeric.
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
 * Assigns sequentially increasing values to a range.
 */
void _algo_iota(forward_iterator_t it_first, forward_iterator_t it_last, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, it_last);
    _algo_iota_varg(it_first, it_last, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Assigns sequentially increasing values to a range.
 */
void _algo_iota_varg(forward_iterator_t it_first, forward_iterator_t it_last, va_list val_elemlist)
{
    iterator_t       it_iter;
    void*            pv_value = NULL;
    ufun_t           ufun_op;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    pv_value = _iterator_allocate_init_elem(it_first);
    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_value);
    ufun_op = _fun_get_unary(it_first, _INCREASE_FUN);

    for (it_iter = it_first; !iterator_equal(it_iter, it_last); it_iter = iterator_next(it_iter)) {
        iterator_set_value(it_iter, pv_value);
        (*ufun_op)(pv_value, pv_value);
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;
}

/**
 * Computes the sum of all the elements in a specified range including some initial value by computing successive partial sums.
 */
void _algo_accumulate(input_iterator_t it_first, input_iterator_t it_last, void* pv_output, ...)
{
    va_list val_elemlist;

    if (_iterator_get_typestyle(it_first) == _TYPE_C_BUILTIN &&
        strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        va_start(val_elemlist, pv_output);
        _algo_accumulate_if_varg(it_first, it_last, _fun_get_binary(it_first, _PLUS_FUN), pv_output, val_elemlist);
        va_end(val_elemlist);
    }
}

/**
 * Computes the result of successive partial results similarly obtained from using a specified binary operation other than the sum.
 */
void _algo_accumulate_if(input_iterator_t it_first, input_iterator_t it_last, bfun_t bfun_op, void* pv_output, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pv_output);
    _algo_accumulate_if_varg(it_first, it_last, bfun_op, pv_output, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Computes the result of successive partial results similarly obtained from using a specified binary operation other than the sum.
 */
void _algo_accumulate_if_varg(input_iterator_t it_first, input_iterator_t it_last, bfun_t bfun_op, void* pv_output, va_list val_elemlist)
{
    iterator_t it_iter;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(pv_output != NULL);

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _PLUS_FUN);
    }

    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_output);
    for (it_iter = it_first; !iterator_equal(it_iter, it_last); it_iter = iterator_next(it_iter)) {
        (*bfun_op)(pv_output, iterator_get_pointer(it_iter), pv_output);
    }
}

/**
 * Computes the sum of the element-wise product of two ranges and adds it to a specified initial value.
 */
void _algo_inner_product(
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, void* pv_output, ...)
{
    va_list val_elemlist;

    if (_iterator_get_typestyle(it_first1) == _TYPE_C_BUILTIN &&
        strncmp(_iterator_get_typebasename(it_first1), _C_STRING_TYPE, _TYPE_NAME_SIZE) != 0) {
        va_start(val_elemlist, pv_output);
        _algo_inner_product_if_varg(
            it_first1, it_last1, it_first2, _fun_get_binary(it_first1, _PLUS_FUN),
            _fun_get_binary(it_first1, _MULTIPLIES_FUN), pv_output, val_elemlist);
        va_end(val_elemlist);
    }
}

/**
 * Computes the result of a generalized procedure where the sum and product binary operations are replaced by other specified binary operations.
 */
void _algo_inner_product_if(
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2,
    bfun_t bfun_op1, bfun_t bfun_op2, void* pv_output, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pv_output);
    _algo_inner_product_if_varg(it_first1, it_last1, it_first2, bfun_op1, bfun_op2, pv_output, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Computes the result of a generalized procedure where the sum and product binary operations are replaced by other specified binary operations.
 */
void _algo_inner_product_if_varg(
    input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2,
    bfun_t bfun_op1, bfun_t bfun_op2, void* pv_output, va_list val_elemlist)
{
    iterator_t it_index1;
    iterator_t it_index2;
    void*      pv_tmp = NULL;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));
    assert(pv_output != NULL);

    pv_tmp = _iterator_allocate_init_elem(it_first1);
    _type_get_varg_value(_iterator_get_typeinfo(it_first1), val_elemlist, pv_output);

    if (bfun_op1 == NULL) {
        bfun_op1 = _fun_get_binary(it_first1, _PLUS_FUN);
    }
    if (bfun_op2 == NULL) {
        bfun_op2 = _fun_get_binary(it_first1, _MULTIPLIES_FUN);
    }

    for (it_index1 = it_first1, it_index2 = it_first2;
         !iterator_equal(it_index1, it_last1);
         it_index1 = iterator_next(it_index1), it_index2 = iterator_next(it_index2)) {
        (*bfun_op2)(iterator_get_pointer(it_index1), iterator_get_pointer(it_index2), pv_tmp);
        (*bfun_op1)(pv_output, pv_tmp, pv_output);
    }

    _iterator_deallocate_destroy_elem(it_first1, pv_tmp);
}

/** local function implementation section **/

/** eof **/

