/*
 *  The implementation of heap.
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
#include <cstl/calgorithm.h>

#include "cstl_heap_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Adds an element that is at the end of a range to an existing heap consisting of the prior elements in the range.
 */
void algo_push_heap(random_access_iterator_t it_first, random_access_iterator_t it_last)
{
    algo_push_heap_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Adds an element that is at the end of a range to an existing heap consisting of the prior elements in the range.
 */
void algo_push_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op)
{
    bool_t                   b_result = false;
    size_t                   t_pos = 0;
    random_access_iterator_t it_parent;
    random_access_iterator_t it_current;

    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    if(bfun_op == NULL)
    {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    /* not empty range */
    if (!iterator_equal(it_first, it_last)) {
        /* get position */
        t_pos = iterator_distance(it_first, it_last) - 1;
        t_pos = t_pos == 0 ? t_pos : (t_pos - 1) / 2;
        it_current = iterator_prev(it_last);
        it_parent = iterator_next_n(it_first, t_pos);
        while (!iterator_equal(it_current, it_first)) {
            (*bfun_op)(iterator_get_pointer(it_current), iterator_get_pointer(it_parent), &b_result);
            if (b_result) { /* it_current < it_parent */
                break;
            }

            algo_iter_swap(it_parent, it_current);
            t_pos = t_pos == 0 ? t_pos : (t_pos - 1) / 2;
            it_current = it_parent;
            it_parent = iterator_next_n(it_first, t_pos);
        }
    }
}

/**
 * Removes the largest element from the front of a heap to the next-to-last position in the range and then forms a new heap from the remaining elements.
 */
void algo_pop_heap(random_access_iterator_t it_first, random_access_iterator_t it_last)
{
    algo_pop_heap_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Removes the largest element from the front of a heap to the next-to-last position in the range and then forms a new heap from the remaining elements.
 */
void algo_pop_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op)
{
    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (!iterator_equal(it_first, it_last)) {
        /* swap the first and prev */
        it_last = iterator_prev(it_last);
        algo_iter_swap(it_first, it_last);

        _algo_adjust_heap(it_first, it_last, it_first, bfun_op);
    }
}

/**
 * Removes the largest element from the front of a heap to the next-to-last position in the range and then forms a new heap from the remaining elements.
 */
void algo_sort_heap(random_access_iterator_t it_first, random_access_iterator_t it_last)
{
    algo_sort_heap_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Removes the largest element from the front of a heap to the next-to-last position in the range and then forms a new heap from the remaining elements.
 */
void algo_sort_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op)
{
    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    for (; !iterator_equal(it_first, it_last); it_last = iterator_prev(it_last)) {
        algo_pop_heap_if(it_first, it_last, bfun_op);
    }
}

/**
 * Converts elements from a specified range into a heap in which the first element is the largest.
 */
void algo_make_heap(random_access_iterator_t it_first, random_access_iterator_t it_last)
{
    algo_make_heap_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Converts elements from a specified range into a heap in which the first element is for which a sorting criterion may be specified with a binary predicate.
 */
void algo_make_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op)
{
    size_t                   t_pos = 0;
    size_t                   t_len = 0;
    random_access_iterator_t it_parent;

    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    t_len = iterator_distance(it_first, it_last);
    if (t_len >= 2) {
        t_pos = (t_len - 2) / 2;

        for (;;) {
            it_parent = it_first;
            it_parent = iterator_next_n(it_parent, t_pos);
            _algo_adjust_heap(it_first, it_last, it_parent, bfun_op);

            if (t_pos == 0) {
                break;
            }

            t_pos--;
        }
    }
}

/**
 * Check the specified range is a heap.
 */
bool_t algo_is_heap(random_access_iterator_t it_first, random_access_iterator_t it_last)
{
    return algo_is_heap_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Check the specified range is a heap with user-defined predicate function.
 */
bool_t algo_is_heap_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op)
{
    bool_t                   b_result = false;
    size_t                   t_len = 0;
    size_t                   t_ppos = 0;
    size_t                   t_lpos = 0;
    size_t                   t_rpos = 0;
    random_access_iterator_t it_parent;
    random_access_iterator_t it_left;
    random_access_iterator_t it_right;

    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    t_len = iterator_distance(it_first, it_last);
    for (t_ppos = 0; t_ppos < t_len; ++t_ppos) {
        t_lpos = t_ppos * 2 + 1;
        t_rpos = t_ppos * 2 + 2;
        it_parent = iterator_next_n(it_first, t_ppos);

        if (t_lpos < t_len) {
            it_left = iterator_next_n(it_first, t_lpos);
            (*bfun_op)(iterator_get_pointer(it_parent), iterator_get_pointer(it_left), &b_result);
            if (b_result) { /* it_parent < it_left */
                return false;
            }
        }

        if (t_rpos < t_len) {
            it_right = iterator_next_n(it_first, t_rpos);
            (*bfun_op)(iterator_get_pointer(it_parent), iterator_get_pointer(it_right), &b_result);
            if (b_result) { /* it_parent < it_right */
                return false;
            }
        }
    }

    return true;
}

/** local function implementation section **/

/** eof **/

