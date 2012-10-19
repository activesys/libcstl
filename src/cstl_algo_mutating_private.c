/*
 *  The implementation of private mutating algorithm.
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
 * Replace element that pointed by iterator with specific value.
 */
void _algo_replace_once(forward_iterator_t it_iter, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, it_iter);
    _algo_replace_once_varg(it_iter, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Replace element that pointed by iterator with specific value.
 */
void _algo_replace_once_varg(forward_iterator_t it_iter, va_list val_elemlist)
{
    void* pv_value = _iterator_allocate_init_elem(it_iter);

    assert(_iterator_limit_type(it_iter, _FORWARD_ITERATOR));

    _type_get_varg_value(_iterator_get_typeinfo(it_iter), val_elemlist, pv_value);
    if (strncmp(_iterator_get_typebasename(it_iter), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        iterator_set_value(it_iter, string_c_str((string_t*)pv_value));
    } else {
        iterator_set_value(it_iter, pv_value);
    }

    _iterator_deallocate_destroy_elem(it_iter, pv_value);
    pv_value = NULL;
}

/**
 * Examines each element in a range and replaces it if it satisfies a specified predicate.
 */
void _algo_replace_if(forward_iterator_t it_first, forward_iterator_t it_last, unary_function_t ufun_op, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, ufun_op);
    _algo_replace_if_varg(it_first, it_last, ufun_op, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Examines each element in a range and replaces it if it satisfies a specified predicate.
 */
void _algo_replace_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, unary_function_t ufun_op, va_list val_elemlist)
{
    void*  pv_value = NULL;
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(it_first);
    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_value);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
            (*ufun_op)(iterator_get_pointer(it_first), &b_result);
            if (b_result) {
                iterator_set_value(it_first, string_c_str((string_t*)pv_value));
            }
        }
    } else {
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
            (*ufun_op)(iterator_get_pointer(it_first), &b_result);
            if (b_result) {
                iterator_set_value(it_first, pv_value);
            }
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;
}

/** eof **/

