/*
 *  The implementation of private sorting algorithm.
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
 * Finds the position of the first element in an ordered range that has a value greater than or equivalent to a specified value.
 */
forward_iterator_t _algo_lower_bound(forward_iterator_t it_first, forward_iterator_t it_last, ...)
{
    forward_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, it_last);
    it_iter = _algo_lower_bound_if_varg(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN), val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Finds the position of the first element in an ordered range that has a value greater than or equivalent to a specified value,
 * where the ordering criterion may be specified by a binary predicate.
 */
forward_iterator_t _algo_lower_bound_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, ...)
{
    forward_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, bfun_op);
    it_iter = _algo_lower_bound_if_varg(it_first, it_last, bfun_op, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Finds the position of the first element in an ordered range that has a value greater than or equivalent to a specified value,
 * where the ordering criterion may be specified by a binary predicate.
 */
forward_iterator_t _algo_lower_bound_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    bool_t     b_result = false;
    size_t     t_len = 0;
    size_t     t_halflen = 0;
    iterator_t it_middle;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(it_first);
    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_value);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        t_len = iterator_distance(it_first, it_last);
        while (t_len > 0) {
            t_halflen = t_len >> 1;
            it_middle = iterator_advance(it_first, t_halflen);

            (*bfun_op)(iterator_get_pointer(it_middle), string_c_str((string_t*)pv_value), &b_result);
            if (b_result) { /* *it_middle < value */
                it_first = iterator_next(it_middle);
                t_len = t_len - t_halflen - 1;
            } else {
                t_len = t_halflen;
            }
        }
    } else {
        t_len = iterator_distance(it_first, it_last);
        while (t_len > 0) {
            t_halflen = t_len >> 1;
            it_middle = iterator_advance(it_first, t_halflen);

            (*bfun_op)(iterator_get_pointer(it_middle), pv_value, &b_result);
            if (b_result) { /* *it_middle < value */
                it_first = iterator_next(it_middle);
                t_len = t_len - t_halflen - 1;
            } else {
                t_len = t_halflen;
            }
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return it_first;
}

/**
 * Finds the position of the first element in an ordered range that has a value that is greater than a specified value.
 */
forward_iterator_t _algo_upper_bound(forward_iterator_t it_first, forward_iterator_t it_last, ...)
{
    forward_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, it_last);
    it_iter = _algo_upper_bound_if_varg(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN), val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Finds the position of the first element in an ordered range that has a value that is greater than a specified value,
 * where the ordering criterion may be specified by a binary predicate.
 */
forward_iterator_t _algo_upper_bound_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, ...)
{
    forward_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, bfun_op);
    it_iter = _algo_upper_bound_if_varg(it_first, it_last, bfun_op, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Finds the position of the first element in an ordered range that has a value that is greater than a specified value,
 * where the ordering criterion may be specified by a binary predicate.
 */
forward_iterator_t _algo_upper_bound_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    bool_t     b_result = false;
    size_t     t_len = 0;
    size_t     t_halflen = 0;
    iterator_t it_middle;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(it_first);
    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_value);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        t_len = iterator_distance(it_first, it_last);
        while (t_len > 0) {
            t_halflen = t_len >> 1;
            it_middle = iterator_advance(it_first, t_halflen);

            (*bfun_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(it_middle), &b_result);
            if (b_result) { /* value < *it_middle */
                t_len = t_halflen;
            } else {
                it_first = iterator_next(it_middle);
                t_len = t_len - t_halflen - 1;
            }
        }
    } else {
        t_len = iterator_distance(it_first, it_last);
        while (t_len > 0) {
            t_halflen = t_len >> 1;
            it_middle = iterator_advance(it_first, t_halflen);

            (*bfun_op)(pv_value, iterator_get_pointer(it_middle), &b_result);
            if (b_result) { /* value < *it_middle */
                t_len = t_halflen;
            } else {
                it_first = iterator_next(it_middle);
                t_len = t_len - t_halflen - 1;
            }
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return it_first;
}

/**
 * Finds a pair of positions in an ordered range, the first less than or equivalent to the position of a specified element and
 * the second greater than the element's position.
 */
range_t _algo_equal_range(forward_iterator_t it_first, forward_iterator_t it_last, ...)
{
    range_t r_result;
    va_list val_elemlist;

    va_start(val_elemlist, it_last);
    r_result = _algo_equal_range_if_varg(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN), val_elemlist);
    va_end(val_elemlist);

    return r_result;
}

/**
 * Finds a pair of positions in an ordered range, the first less than or equivalent to the position of a specified element and
 * the second greater than the element's position, where the sense of equivalence or ordering used to establish the positions
 * in the sequence may be specified by a binary predicate.
 */
range_t _algo_equal_range_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, ...)
{
    range_t r_result;
    va_list val_elemlist;

    va_start(val_elemlist, bfun_op);
    r_result = _algo_equal_range_if_varg(it_first, it_last, bfun_op, val_elemlist);
    va_end(val_elemlist);

    return r_result;
}

/**
 * Finds a pair of positions in an ordered range, the first less than or equivalent to the position of a specified element and
 * the second greater than the element's position, where the sense of equivalence or ordering used to establish the positions
 * in the sequence may be specified by a binary predicate.
 */
range_t _algo_equal_range_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    bool_t     b_result = false;
    bool_t     t_equal = false;
    size_t     t_len = 0;
    size_t     t_halflen = 0;
    iterator_t it_middle;
    iterator_t it_lower;
    iterator_t it_upper;
    range_t    t_range;
    va_list    val_elemlist_copy; /* copy val_elemlist for lower bound and upper bound*/

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(it_first);
    va_copy(val_elemlist_copy, val_elemlist);
    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_value);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        t_len = iterator_distance(it_first, it_last);
        while (t_len > 0) {
            t_halflen = t_len >> 1;
            it_middle = iterator_advance(it_first, t_halflen);

            (*bfun_op)(iterator_get_pointer(it_middle), string_c_str((string_t*)pv_value), &b_result);
            if(b_result) { /* *it_middle < value */
                it_first = iterator_next(it_middle);
                t_len = t_len - t_halflen - 1;
            } else {
                (*bfun_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(it_middle), &b_result);
                if (b_result) { /* value < *it_middle */
                    t_len = t_halflen;
                } else {
                    va_list val_lower_bound; /* copy val_elemlist for lower bound */
                    va_list val_upper_bound; /* copy val_elemlist for upper bound */

                    va_copy(val_lower_bound, val_elemlist_copy);
                    va_copy(val_upper_bound, val_elemlist_copy);

                    it_lower = _algo_lower_bound_if_varg(it_first, it_middle, bfun_op, val_lower_bound);
                    it_first = iterator_advance(it_first, t_len);
                    it_middle = iterator_next(it_middle);
                    it_upper = _algo_upper_bound_if_varg(it_middle, it_first, bfun_op, val_upper_bound);

                    va_end(val_lower_bound);
                    va_end(val_upper_bound);

                    t_range.it_begin = it_lower;
                    t_range.it_end = it_upper;
                    t_equal = true;
                    break;
                }
            }
        }
    } else {
        t_len = iterator_distance(it_first, it_last);
        while (t_len > 0) {
            t_halflen = t_len >> 1;
            it_middle = iterator_advance(it_first, t_halflen);

            (*bfun_op)(iterator_get_pointer(it_middle), pv_value, &b_result);
            if (b_result) { /* *it_middle < value */
                it_first = iterator_next(it_middle);
                t_len = t_len - t_halflen - 1;
            } else {
                (*bfun_op)(pv_value, iterator_get_pointer(it_middle), &b_result);
                if (b_result) { /* value < *it_middle */
                    t_len = t_halflen;
                } else {
                    va_list val_lower_bound; /* copy val_elemlist for lower bound */
                    va_list val_upper_bound; /* copy val_elemlist for upper bound */

                    va_copy(val_lower_bound, val_elemlist_copy);
                    va_copy(val_upper_bound, val_elemlist_copy);

                    it_lower = _algo_lower_bound_if_varg(it_first, it_middle, bfun_op, val_lower_bound);
                    it_first = iterator_advance(it_first, t_len);
                    it_middle = iterator_next(it_middle);
                    it_upper = _algo_upper_bound_if_varg(it_middle, it_first, bfun_op, val_upper_bound);

                    va_end(val_lower_bound);
                    va_end(val_upper_bound);

                    t_range.it_begin = it_lower;
                    t_range.it_end = it_upper;
                    t_equal = true;
                    break;
                }
            }
        }
    }

    va_end(val_elemlist_copy);
    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    if (!t_equal) {
        t_range.it_begin = it_first;
        t_range.it_end = it_first;
    }
    return t_range;
}

/**
 * Tests whether there is an element in a sorted range that is equal to a specified value.
 */
bool_t _algo_binary_search(forward_iterator_t it_first, forward_iterator_t it_last, ...)
{
    bool_t b_result = false;
    va_list val_elemlist;

    va_start(val_elemlist, it_last);
    b_result = _algo_binary_search_if_varg(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN), val_elemlist);
    va_end(val_elemlist);

    return b_result;
}

/**
 * Tests whether there is an element in a sorted range that is equivalent to it in a sense specified by a binary predicate.
 */
bool_t _algo_binary_search_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, ...)
{
    bool_t b_result = false;
    va_list val_elemlist;

    va_start(val_elemlist, bfun_op);
    b_result = _algo_binary_search_if_varg(it_first, it_last, bfun_op, val_elemlist);
    va_end(val_elemlist);

    return b_result;
}

/**
 * Tests whether there is an element in a sorted range that is equivalent to it in a sense specified by a binary predicate.
 */
bool_t _algo_binary_search_if_varg(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op, va_list val_elemlist)
{
    void*      pv_value = NULL;
    iterator_t it_lower;
    bool_t     b_cmp = false;
    bool_t     b_result = false;
    va_list    val_elemlist_copy; /* copy val_elemlist for lower bound */

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    va_copy(val_elemlist_copy, val_elemlist);
    it_lower = _algo_lower_bound_if_varg(it_first, it_last, bfun_op, val_elemlist_copy);
    va_end(val_elemlist_copy);

    pv_value = _iterator_allocate_init_elem(it_first);
    _type_get_varg_value(_iterator_get_typeinfo(it_first), val_elemlist, pv_value);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        b_result = iterator_equal(it_lower, it_last) ?
            false : ((*bfun_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(it_lower), &b_cmp), !b_cmp);
    } else {
        b_result = iterator_equal(it_lower, it_last) ?
            false : ((*bfun_op)(pv_value, iterator_get_pointer(it_lower), &b_cmp), !b_cmp);
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return b_result;
}

/** eof **/

