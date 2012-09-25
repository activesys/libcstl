/*
 *  The implementation of private non-mutating algorithm.
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
 * Locates the position of the first occurrence of an element in a range that has a specified value.
 */
input_iterator_t _algo_find(input_iterator_t it_first, input_iterator_t it_last, ...)
{
    input_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, it_last);
    it_iter = _algo_find_varg(it_first, it_last, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Locates the position of the first occurrence of an element in a range that has a specified value.
 */
input_iterator_t _algo_find_varg(input_iterator_t it_first, input_iterator_t it_last, va_list val_elemlist)
{
    void*             pv_value = NULL;
    bool_t            b_result = false;
    bool_t            b_less = false;
    bool_t            b_greater = false;
    binary_function_t bfun_op;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));

    pv_value = _iterator_allocate_init_elem(it_first);
    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_value);

    bfun_op = _fun_get_binary(it_first, _EQUAL_FUN);
    assert(bfun_op != NULL);
    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
            (*bfun_op)(iterator_get_pointer(it_first), pv_value, &b_less);
            if (b_less) {
                continue;
            }
            (*bfun_op)(pv_value, iterator_get_pointer(it_first), &b_greater);
            if (b_greater) {
                continue;
            }

            break;
        }
    } else {
        if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
                (*bfun_op)(iterator_get_pointer(it_first), string_c_str((string_t*)pv_value), &b_result);
                if (b_result) {
                    break;
                }
            }
        } else {
            for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
                (*bfun_op)(iterator_get_pointer(it_first), pv_value, &b_result);
                if (b_result) {
                    break;
                }
            }
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return it_first;
}

/** eof **/

