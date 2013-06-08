/*
 *  The implementation of auxiliary sorting algorithm.
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

#include "cstl_algo_sorting_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Compute logarithm of 2
 */
size_t _algo_lg(size_t t_base)
{
    size_t t_power = 0;
    for (; t_base > 1; t_base >>= 1) {
        t_power++;
    }

    return t_power;
}

/**
 * Return the median of three random_access_iterator_t
 */
random_access_iterator_t _algo_median_of_three_if(
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last, bfun_t bfun_op)
{
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first, it_middle, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_valid_range(it_middle, it_last, _RANDOM_ACCESS_ITERATOR));
    assert(bfun_op != NULL);

    (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_middle), &b_result);
    if (b_result) {             /* it_first < it_middle */
        (*bfun_op)(iterator_get_pointer(it_middle), iterator_get_pointer(it_last), &b_result);
        if (b_result){          /* it_first < it_middle < it_last */
            return it_middle;
        } else {                /* it_last <= it_middle */
            (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_last), &b_result);
            if (b_result) {     /* it_first < it_last <= it_middle */
                return it_last;
            }else {             /* it_last <= it_first <= it_middle */
                return it_first;
            }
        }
    } else {                    /* it_middle <= it_first */
        (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_last), &b_result);
        if (b_result) {         /* it_middle <= it_first < it_last */
            return it_first;
        } else {                /* it_last <= it_first */
            (*bfun_op)(iterator_get_pointer(it_middle), iterator_get_pointer(it_last), &b_result);
            if (b_result) {     /* it_middle < it_last <= it_first */
                return it_last;
            } else {            /* it_last <= it_middle <= it_first */
                return it_middle;
            }
        }
    }
}

/**
 * Insertion sort for specify range.
 */
void _algo_insertion_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op, void* pv_value)
{
    iterator_t it_bound;
    iterator_t it_next;
    iterator_t it_tmp;
    iterator_t it_prev;
    bool_t     b_result = false;

    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));
    assert(pv_value != NULL);
    assert(bfun_op != NULL);

    if (iterator_equal(it_first, it_last)) {
        return;
    }

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (it_bound = iterator_next(it_first); !iterator_equal(it_bound, it_last); it_bound = iterator_next(it_bound)) {
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(it_bound));
            (*bfun_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(it_first), &b_result);
            if (b_result) { /* pv_value < *it_first */
                it_next = iterator_next(it_bound);
                algo_copy_backward(it_first, it_bound, it_next);
                iterator_set_value(it_first, string_c_str((string_t*)pv_value));
            } else {
                it_tmp = it_bound;
                it_prev = iterator_prev(it_tmp);
                (*bfun_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(it_prev), &b_result);
                while (b_result) {  /* pv_value < *it_prev */
                    iterator_set_value(it_tmp, iterator_get_pointer(it_prev));
                    it_tmp = it_prev;
                    it_prev = iterator_prev(it_prev);
                    (*bfun_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(it_prev), &b_result);
                }

                iterator_set_value(it_tmp, string_c_str((string_t*)pv_value));
            }
        }
    } else {
        for (it_bound = iterator_next(it_first); !iterator_equal(it_bound, it_last); it_bound = iterator_next(it_bound)) {
            iterator_get_value(it_bound, pv_value);
            (*bfun_op)(pv_value, iterator_get_pointer(it_first), &b_result);
            if (b_result) { /* pv_value < *it_first */
                it_next = iterator_next(it_bound);
                algo_copy_backward(it_first, it_bound, it_next);
                iterator_set_value(it_first, pv_value);
            } else {
                it_tmp = it_bound;
                it_prev = iterator_prev(it_tmp);
                (*bfun_op)(pv_value, iterator_get_pointer(it_prev), &b_result);
                while (b_result) {  /* pv_value < *it_prev */
                    iterator_set_value(it_tmp, iterator_get_pointer(it_prev));
                    it_tmp = it_prev;
                    it_prev = iterator_prev(it_prev);

                    (*bfun_op)(pv_value, iterator_get_pointer(it_prev), &b_result);
                }

                iterator_set_value(it_tmp, pv_value);
            }
        }
    }
}

/**
 * Quick sort or heap sort for specify range.
 */
void _algo_intro_sort_if(
    random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op, size_t t_depth, void* pv_value)
{
    iterator_t it_pivot;
    iterator_t it_begin;
    iterator_t it_end;
    iterator_t it_prev;
    bool_t     b_result = false;

    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));
    assert(pv_value != NULL);
    assert(bfun_op != NULL);

    if (iterator_distance(it_first, it_last) < 2) {
        return;
    }

    if (t_depth == 0){
        /* do heap sort */
        algo_partial_sort_if(it_first, it_last, it_last, bfun_op);
        return;
    }
    t_depth--;

    it_pivot = iterator_advance(it_first, iterator_distance(it_first, it_last) / 2);
    it_prev = iterator_prev(it_last);
    it_pivot = _algo_median_of_three_if(it_first, it_pivot, it_prev, bfun_op);

    /* the pv_value must be string_t type when the container type is char* */
    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(it_pivot));
        it_begin = it_first;
        it_end = it_last;

        for (;;) {
            /* move begin */
            (*bfun_op)(iterator_get_pointer(it_begin), string_c_str((string_t*)pv_value), &b_result);
            while (b_result) {
                it_begin = iterator_next(it_begin);
                (*bfun_op)(iterator_get_pointer(it_begin), string_c_str((string_t*)pv_value), &b_result);
            }
            /* move end */
            it_end = iterator_prev(it_end);
            (*bfun_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(it_end), &b_result);
            while (b_result) {
                it_end = iterator_prev(it_end);
                (*bfun_op)(string_c_str((string_t*)pv_value), iterator_get_pointer(it_end), &b_result);
            }

            /* across */
            if (!iterator_less(it_begin, it_end)) {
                it_pivot = it_begin;
                break;
            } else {
                algo_iter_swap(it_begin, it_end);
                it_begin = iterator_next(it_begin);
            }
        }
    } else {
        iterator_get_value(it_pivot, pv_value);
        it_begin = it_first;
        it_end = it_last;

        for (;;) {
            /* move begin */
            (*bfun_op)(iterator_get_pointer(it_begin), pv_value, &b_result);
            while (b_result) {
                it_begin = iterator_next(it_begin);
                (*bfun_op)(iterator_get_pointer(it_begin), pv_value, &b_result);
            }
            /* move end */
            it_end = iterator_prev(it_end);
            (*bfun_op)(pv_value, iterator_get_pointer(it_end), &b_result);
            while (b_result) {
                it_end = iterator_prev(it_end);
                (*bfun_op)(pv_value, iterator_get_pointer(it_end), &b_result);
            }

            /* across */
            if (!iterator_less(it_begin, it_end)) {
                it_pivot = it_begin;
                break;
            } else {
                algo_iter_swap(it_begin, it_end);
                it_begin = iterator_next(it_begin);
            }
        }
    }

    /* sort [it_first, it_pivot) */
    _algo_intro_sort_if(it_first, it_pivot, bfun_op, t_depth, pv_value);
    /* sort [it_pivot, it_last) */
    _algo_intro_sort_if(it_pivot, it_last, bfun_op, t_depth, pv_value);
}

/** eof **/

