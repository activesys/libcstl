/*
 *  The implementation of private non-mutating algorithm.
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
#include <cstl/cstring.h>
#include <cstl/cfunctional.h>
#include <cstl/calgorithm.h>

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
    bfun_t            bfun_op;

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

/**
 * Returns the number of elements in a range whose values match a specified value.
 */
size_t _algo_count(input_iterator_t it_first, input_iterator_t it_last, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, it_last);
    t_count = _algo_count_varg(it_first, it_last, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Returns the number of elements in a range whose values match a specified value.
 */
size_t _algo_count_varg(input_iterator_t it_first, input_iterator_t it_last, va_list val_elemlist)
{
    void*             pv_value = NULL;
    bool_t            b_result = false;
    bool_t            b_less = false;
    bool_t            b_greater = false;
    size_t            t_count = 0;
    bfun_t            bfun_op;

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

            t_count++;
        }
    } else {
        if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
                (*bfun_op)(iterator_get_pointer(it_first), string_c_str((string_t*)pv_value), &b_result);
                if (b_result) {
                    t_count++;
                }
            }
        } else {
            for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
                (*bfun_op)(iterator_get_pointer(it_first), pv_value, &b_result);
                if (b_result) {
                    t_count++;
                }
            }
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return t_count;
}

/**
 * Searches for the first subsequence in a range that of a specified number of elements having a particular value.
 */
forward_iterator_t _algo_search_n(forward_iterator_t it_first, forward_iterator_t it_last, size_t t_count, ...)
{
    forward_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    it_iter = _algo_search_n_if_varg(it_first, it_last, t_count, _fun_get_binary(it_first, _EQUAL_FUN), val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Searches for the first subsequence in a range that of a specified number of elements having a relation to that value as specified by a binary predicate.
 */
forward_iterator_t _algo_search_n_if(
    forward_iterator_t it_first, forward_iterator_t it_last, size_t t_count, bfun_t bfun_op, ...)
{
    forward_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, bfun_op);
    it_iter = _algo_search_n_if_varg(it_first, it_last, t_count, bfun_op, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Searches for the first subsequence in a range that of a specified number of elements having a relation to that value as specified by a binary predicate.
 */
forward_iterator_t _algo_search_n_if_varg(
    forward_iterator_t it_first, forward_iterator_t it_last, size_t t_count, bfun_t bfun_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    bool_t     b_result = false;
    bool_t     b_less = false;
    bool_t     b_greater = false;
    iterator_t it_index;
    size_t     i = 0;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (t_count == 0) {
        return it_first;
    }

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _EQUAL_FUN);
    }

    pv_value = _iterator_allocate_init_elem(it_first);
    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_value);

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

            for (i = 1, it_index = iterator_next(it_first);
                 i < t_count && !iterator_equal(it_index, it_last);
                 ++i, it_index = iterator_next(it_index)) {
                (*bfun_op)(iterator_get_pointer(it_index), pv_value, &b_less);
                if (b_less) {
                    break;
                }
                (*bfun_op)(pv_value, iterator_get_pointer(it_index), &b_greater);
                if (b_greater) {
                    break;
                }
            }

            if (i == t_count) {
                break;
            }
        }
    } else {
        if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
                (*bfun_op)(iterator_get_pointer(it_first), string_c_str((string_t*)pv_value), &b_result);
                if (b_result) {
                    for (i = 1, it_index = iterator_next(it_first);
                         i < t_count && !iterator_equal(it_index, it_last);
                         ++i, it_index = iterator_next(it_index)) {
                        (*bfun_op)(iterator_get_pointer(it_index), string_c_str((string_t*)pv_value), &b_result);
                        if (!b_result) {
                            break;
                        }
                    }

                    if (i == t_count) {
                        break;
                    }
                }
            }
        } else {
            for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
                (*bfun_op)(iterator_get_pointer(it_first), pv_value, &b_result);
                if (b_result) {
                    for (i = 1, it_index = iterator_next(it_first);
                         i < t_count && !iterator_equal(it_index, it_last);
                         ++i, it_index = iterator_next(it_index)) {
                        (*bfun_op)(iterator_get_pointer(it_index), pv_value, &b_result);
                        if (!b_result) {
                            break;
                        }
                    }

                    if (i == t_count) {
                        break;
                    }
                }
            }
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return it_first;
}

/** eof **/

