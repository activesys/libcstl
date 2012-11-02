/*
 *  The implementation of sorting algorithm.
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

#include "cstl_algo_sorting_aux.h"

/** local constant declaration and local macro section **/
#define _CSTL_ALGO_SORT_THRESHOLD  16 /* the threshold of insert sort and quick sort */

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Check a specificed range is sorted or not.
 */
bool_t algo_is_sorted(forward_iterator_t it_first, forward_iterator_t it_last)
{
    return algo_is_sorted_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Check a specificed range is sorted or not according to an ordering critierion specified by a binary predicate.
 */
bool_t algo_is_sorted_if(forward_iterator_t it_first, forward_iterator_t it_last, binary_function_t bfun_op)
{
    bool_t     b_result = false;
    iterator_t it_next;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (iterator_equal(it_first, it_last)) {
        return true;
    }

    for (it_next = iterator_next(it_first);
         !iterator_equal(it_next, it_last);
         it_first = it_next, it_next = iterator_next(it_next)) {
        (*bfun_op)(iterator_get_pointer(it_next), iterator_get_pointer(it_first), &b_result);
        if (b_result) { /* it_next < it_first */
            return false;
        }
    }

    return true;
}

/**
 * Arranges a specified number of the smaller elements in a range into a nondescending order.
 */
void algo_partial_sort(
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last)
{
    algo_partial_sort_if(it_first, it_middle, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Arranges a specified number of the smaller elements in a range according to an ordering criterion specified by a binary predicate.
 */
void algo_partial_sort_if(
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last, binary_function_t bfun_op)
{
    iterator_t it_prev;
    iterator_t it_iter;
    bool_t     b_result = false;

    assert(_iterator_valid_range(it_first, it_middle, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_valid_range(it_middle, it_last, _RANDOM_ACCESS_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (iterator_equal(it_first, it_middle)) {
        return;
    }

    algo_make_heap_if(it_first, it_middle, bfun_op);
    for (it_iter = it_middle; !iterator_equal(it_iter, it_last); it_iter = iterator_next(it_iter)) {
        (*bfun_op)(iterator_get_pointer(it_iter), iterator_get_pointer(it_first), &b_result);
        if (b_result) {
            algo_pop_heap_if(it_first, it_middle, bfun_op);
            it_prev = iterator_prev(it_middle);
            algo_iter_swap(it_prev, it_iter);
            algo_push_heap_if(it_first, it_middle, bfun_op);
        }
    }
    algo_sort_heap_if(it_first, it_middle, bfun_op);
}

/**
 * Copies elements from a source range into a destination range where the source elements are ordered by less than.
 */
random_access_iterator_t algo_partial_sort_copy(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2)
{
    return algo_partial_sort_copy_if(it_first1, it_last1, it_first2, it_last2, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Copies elements from a source range into a destination range where the source elements are ordered by specified binary predicate.
 */
random_access_iterator_t algo_partial_sort_copy_if(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2, binary_function_t bfun_op)
{
    iterator_t it_iter;
    iterator_t it_prev;
    bool_t     b_result = false;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);
    }

    if (iterator_equal(it_first1, it_last1) || iterator_equal(it_first2, it_last2)) {
        return it_first2;
    }

    for (it_iter = it_first2;
         !iterator_equal(it_first1, it_last1) && !iterator_equal(it_iter, it_last2);
         it_first1 = iterator_next(it_first1), it_iter = iterator_next(it_iter)) {
        iterator_set_value(it_iter, iterator_get_pointer(it_first1));
    }
    algo_make_heap_if(it_first2, it_iter, bfun_op);
    for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1)) {
        (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_result);
        if (b_result) { /* *it_first1 < *it_first2 */
            algo_pop_heap_if(it_first2, it_iter, bfun_op);
            it_prev = iterator_prev(it_iter);
            iterator_set_value(it_prev, iterator_get_pointer(it_first1));
            algo_push_heap_if(it_first2, it_iter, bfun_op);
        }
    }
    algo_sort_heap_if(it_first2, it_iter, bfun_op);

    return it_iter;
}

/**
 * Arranges the elements in a specified range into a nondescending order.
 */
void algo_sort(random_access_iterator_t it_first, random_access_iterator_t it_last)
{
    algo_sort_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Arranges the elements in a specified range according to an ordering criterion specified by a binary predicate.
 */
void algo_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, binary_function_t bfun_op)
{
    void*  pv_value = NULL;
    size_t t_len = 0;

    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (!iterator_equal(it_first, it_last)) {
        pv_value = _iterator_allocate_init_elem(it_first);

        t_len = iterator_distance(it_first, it_last);
        if (t_len > _CSTL_ALGO_SORT_THRESHOLD) {
            _algo_intro_sort_if(it_first, it_last, bfun_op, _algo_lg(t_len)*2, pv_value);
        } else {
            _algo_insertion_sort_if(it_first, it_last, bfun_op, pv_value);
        }

        _iterator_deallocate_destroy_elem(it_first, pv_value);
        pv_value = NULL;
    }
}

/**
 * Combines all of the elements from two sorted source ranges into a single, sorted destination range.
 */
output_iterator_t algo_merge(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result)
{
    return algo_merge_if(it_first1, it_last1, it_first2, it_last2, it_result, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Combines all of the elements from two sorted source ranges into a single, sorted destination range, where the ordering criterion
 * may be specified by a binary predicate.
 */
output_iterator_t algo_merge_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, binary_function_t bfun_op)
{
    bool_t b_cmp = false;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));
    assert(_iterator_same_elem_type(it_first1, it_result));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);
    }

    while (!iterator_equal(it_first1, it_last1) && !iterator_equal(it_first2, it_last2)) {
        (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_cmp);
        /* *it_first2 < *it_first1 */
        if (b_cmp) {
            iterator_set_value(it_result, iterator_get_pointer(it_first2));
            it_first2 = iterator_next(it_first2);
        } else {
            iterator_set_value(it_result, iterator_get_pointer(it_first1));
            it_first1 = iterator_next(it_first1);
        }
        it_result = iterator_next(it_result);
    }

    return algo_copy(it_first2, it_last2, algo_copy(it_first1, it_last1, it_result));
}

/** eof **/

