/*
 *  The implementation of sorting algorithm.
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
#include <cstl/clist.h>
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
bool_t algo_is_sorted_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op)
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
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last, bfun_t bfun_op)
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
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2, bfun_t bfun_op)
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
void algo_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op)
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
    output_iterator_t it_result, bfun_t bfun_op)
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

/**
 * Combines the elements from two consecutive sorted ranges into a single sorted range.
 */
void algo_inplace_merge(
    bidirectional_iterator_t it_first, bidirectional_iterator_t it_middle, bidirectional_iterator_t it_last)
{
    algo_inplace_merge_if(it_first, it_middle, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Combines the elements from two consecutive sorted ranges into a single sorted range, where the ordering criterion may be specified by a binary predicate.
 */
void algo_inplace_merge_if(
    bidirectional_iterator_t it_first, bidirectional_iterator_t it_middle, bidirectional_iterator_t it_last, bfun_t bfun_op)
{
    iterator_t it_iter;
    list_t*    plist_buffer = NULL;

    assert(_iterator_valid_range(it_first, it_middle, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_valid_range(it_middle, it_last, _BIDIRECTIONAL_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (iterator_equal(it_first, it_middle) || iterator_equal(it_middle, it_last)) {
        return;
    }

    /*
     * Create buffer accroding to type name of range and the list creation failure if and only if the type is unregistered.
     * The type came from referenced range must be regitstered, so the list creation must be not failure.
     */
    plist_buffer = _create_list(_iterator_get_typename(it_first));
    assert(plist_buffer != NULL);

    list_init_n(plist_buffer, iterator_distance(it_first, it_middle));
    it_iter = algo_copy(it_first, it_middle, list_begin(plist_buffer));
    algo_merge_if(list_begin(plist_buffer), it_iter, it_middle, it_last, it_first, bfun_op);

    list_destroy(plist_buffer);
}

/**
 * Arranges the elements in a specified range into a nondescending order.
 */
void algo_stable_sort(random_access_iterator_t it_first, random_access_iterator_t it_last)
{
    algo_stable_sort_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Arranges the elements in a specified range into a nondescending order or according to an ordering criterion
 * specified by a binary predicate and preserves the relative ordering of equivalent elements.
 */
void algo_stable_sort_if(random_access_iterator_t it_first, random_access_iterator_t it_last, bfun_t bfun_op)
{
    size_t t_len = 0;
    void*  pv_value = NULL;

    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    t_len = iterator_distance(it_first, it_last);
    if (t_len > _CSTL_ALGO_SORT_THRESHOLD) {
        iterator_t it_middle = it_first;
        it_middle = iterator_advance(it_middle, t_len/2);

        algo_stable_sort_if(it_first, it_middle, bfun_op);
        algo_stable_sort_if(it_middle, it_last, bfun_op);
        algo_inplace_merge_if(it_first, it_middle, it_last, bfun_op);
    } else {
        pv_value = _iterator_allocate_init_elem(it_first);
        _algo_insertion_sort_if(it_first, it_last, bfun_op, pv_value);
        _iterator_deallocate_destroy_elem(it_first, pv_value);
        pv_value = NULL;
    }
}

/**
 * Partitions a range of elements, correctly locating the nth element of the sequence in the range so that all the elements in front of it are less than or equal to it and
 * all the elements that follow it in the sequence are greater than or equal to it.
 */
void algo_nth_element(random_access_iterator_t it_first, random_access_iterator_t it_nth, random_access_iterator_t it_last)
{
    algo_nth_element_if(it_first, it_nth, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Partitions a range of elements, correctly locating the nth element of the sequence in the range so that all the elements in front of it are less than or equal to it and
 * all the elements that follow it in the sequence are greater than or equal to it.
 */
void algo_nth_element_if(random_access_iterator_t it_first, random_access_iterator_t it_nth, random_access_iterator_t it_last, bfun_t bfun_op)
{
    iterator_t it_pivot;
    iterator_t it_begin;
    iterator_t it_end;
    iterator_t it_prev;
    bool_t     b_result = false;
    void*      pv_value = NULL;

    assert(_iterator_valid_range(it_first, it_nth, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_valid_range(it_nth, it_last, _RANDOM_ACCESS_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    pv_value = _iterator_allocate_init_elem(it_first);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        while (iterator_distance(it_first, it_last) > 3) {
            it_pivot = iterator_advance(it_first, iterator_distance(it_first, it_last) / 2);
            it_prev = iterator_prev(it_last);
            it_pivot = _algo_median_of_three_if(it_first, it_pivot, it_prev, bfun_op);
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

            if (iterator_less_equal(it_pivot, it_nth)) {
                it_first = it_pivot;
            } else {
                it_last = it_pivot;
            }
        }
    } else {
        while (iterator_distance(it_first, it_last) > 3) {
            it_pivot = iterator_advance(it_first, iterator_distance(it_first, it_last) / 2);
            it_prev = iterator_prev(it_last);
            it_pivot = _algo_median_of_three_if(it_first, it_pivot, it_prev, bfun_op);
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

            if (iterator_less_equal(it_pivot, it_nth)) {
                it_first = it_pivot;
            } else {
                it_last = it_pivot;
            }
        }
    }

    _algo_insertion_sort_if(it_first, it_last, bfun_op, pv_value);

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;
}

/**
 * Tests whether one sorted range contains all the elements contained in a second sorted range.
 */
bool_t algo_includes(input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, input_iterator_t it_last2)
{
    return algo_includes_if(it_first1, it_last1, it_first2, it_last2, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Tests whether one sorted range contains all the elements contained in a second sorted range, where the ordering or
 * equivalence criterion between elements may be specified by a binary predicate.
 */
bool_t algo_includes_if(input_iterator_t it_first1, input_iterator_t it_last1, input_iterator_t it_first2, input_iterator_t it_last2, bfun_t bfun_op)
{
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);
    }

    while (!iterator_equal(it_first1, it_last1) && !iterator_equal(it_first2, it_last2)) {
        (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_result);
        if (b_result) {     /* *it_first2 < *it_first1 */
            return false;
        } else {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_result);
            if (b_result){  /* *it_first1 < *it_first2 */
                it_first1 = iterator_next(it_first1);
            } else {        /* *it_first1 == *it_first2 */
                it_first1 = iterator_next(it_first1);
                it_first2 = iterator_next(it_first2);
            }
        }
    }

    return iterator_equal(it_first2, it_last2) ? true : false;
}

/**
 * Unites all of the elements that belong to at least one of two sorted source ranges into a single, sorted destination range.
 */
output_iterator_t algo_set_union(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result)
{
    return algo_set_union_if(it_first1, it_last1, it_first2, it_last2, it_result, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Unites all of the elements that belong to at least one of two sorted source ranges into a single, sorted destination range,
 * sorted destination range, where the ordering criterion may be specified by a binary predicate.
 */
output_iterator_t algo_set_union_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, bfun_t bfun_op)
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
        (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_cmp);
        if (b_cmp) {        /* it_first1 < it_first2 */
            iterator_set_value(it_result, iterator_get_pointer(it_first1));
            it_first1 = iterator_next(it_first1);
        } else {
            (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_cmp);
            if (b_cmp) {    /* it_first2 < it_first1 */
                iterator_set_value(it_result, iterator_get_pointer(it_first2));
                it_first2 = iterator_next(it_first2);
            } else {        /* it_first1 == it_first2 */
                iterator_set_value(it_result, iterator_get_pointer(it_first1));
                it_first1 = iterator_next(it_first1);
                it_first2 = iterator_next(it_first2);
            }
        }
        it_result = iterator_next(it_result);
    }

    assert(iterator_equal(it_first1, it_last1) || iterator_equal(it_first2, it_last2));
    return algo_copy(it_first2, it_last2, algo_copy(it_first1, it_last1, it_result));
}

/**
 * Unites all of the elements that belong to both sorted source ranges into a single, sorted destination range.
 */
output_iterator_t algo_set_intersection(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result)
{
    return algo_set_intersection_if(it_first1, it_last1, it_first2, it_last2, it_result, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Unites all of the elements that belong to both sorted source ranges into a single, sorted destination range,
 * where the ordering criterion may be specified by a binary predicate.
 */
output_iterator_t algo_set_intersection_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, bfun_t bfun_op)
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
        (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_cmp);
        if (b_cmp) {        /* it_first1 < it_first2 */
            it_first1 = iterator_next(it_first1);
        } else {
            (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_cmp);
            if (b_cmp) {    /* it_first2 < it_first1 */
                it_first2 = iterator_next(it_first2);
            } else {        /* it_first1 == it_first2 */
                iterator_set_value(it_result, iterator_get_pointer(it_first1));
                it_first1 = iterator_next(it_first1);
                it_first2 = iterator_next(it_first2);
                it_result = iterator_next(it_result);
            }
        }
    }

    assert(iterator_equal(it_first1, it_last1) || iterator_equal(it_first2, it_last2));
    return it_result;
}

/**
 * Unites all of the elements that belong to one sorted source range, but not to a second sorted source range, into a single, sorted destination range.
 */
output_iterator_t algo_set_difference(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result)
{
    return algo_set_difference_if(it_first1, it_last1, it_first2, it_last2, it_result, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Unites all of the elements that belong to one sorted source range, but not to a second sorted source range, into a single, sorted destination range,
 * where the ordering criterion may be specified by a binary predicate.
 */
output_iterator_t algo_set_difference_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, bfun_t bfun_op)
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
        (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_cmp);
        if (b_cmp) {        /* it_first1 < it_first2 */
            iterator_set_value(it_result, iterator_get_pointer(it_first1));
            it_first1 = iterator_next(it_first1);
            it_result = iterator_next(it_result);
        } else {
            (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_cmp);
            if (b_cmp) {    /* it_first2 < it_first1 */
                it_first2 = iterator_next(it_first2);
            } else {        /* it_first1 == it_first2 */
                it_first1 = iterator_next(it_first1);
                it_first2 = iterator_next(it_first2);
            }
        }
    }

    assert(iterator_equal(it_first1, it_last1) || iterator_equal(it_first2, it_last2));
    return algo_copy(it_first1, it_last1, it_result);
}

/**
 * Unites all of the elements that belong to one, but not both, of the sorted source ranges into a single, sorted destination range.
 */
output_iterator_t algo_set_symmetric_difference(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result)
{
    return algo_set_symmetric_difference_if(it_first1, it_last1, it_first2, it_last2, it_result, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Unites all of the elements that belong to one, but not both, of the sorted source ranges into a single, sorted destination range,
 * where the ordering criterion may be specified by a binary predicate.
 */
output_iterator_t algo_set_symmetric_difference_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    output_iterator_t it_result, bfun_t bfun_op)
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
        (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_cmp);
        if (b_cmp) {        /* it_first1 < it_first2 */
            iterator_set_value(it_result, iterator_get_pointer(it_first1));
            it_first1 = iterator_next(it_first1);
            it_result = iterator_next(it_result);
        } else {
            (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_cmp);
            if (b_cmp) {    /* it_first2 < it_first1 */
                iterator_set_value(it_result, iterator_get_pointer(it_first2));
                it_first2 = iterator_next(it_first2);
                it_result = iterator_next(it_result);
            } else {        /* it_first1 == it_first2 */
                it_first1 = iterator_next(it_first1);
                it_first2 = iterator_next(it_first2);
            }
        }
    }

    assert(iterator_equal(it_first1, it_last1) || iterator_equal(it_first2, it_last2));
    return algo_copy(it_first2, it_last2, algo_copy(it_first1, it_last1, it_result));
}

/**
 * Compares two elements and returns the larger of the two.
 */
input_iterator_t algo_max(input_iterator_t it_first, input_iterator_t it_second)
{
    return algo_max_if(it_first, it_second, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Compares two elements and returns the larger of the two, where the ordering criterion may be specified by a binary predicate.
 */
input_iterator_t algo_max_if(input_iterator_t it_first, input_iterator_t it_second, bfun_t bfun_op)
{
    bool_t b_result = false;

    assert(_iterator_limit_type(it_first, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_second, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_second));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_second), &b_result);
    return b_result ? it_second : it_first;
}

/**
 * Compares two elements and returns the lesser of the two.
 */
input_iterator_t algo_min(input_iterator_t it_first, input_iterator_t it_second)
{
    return algo_min_if(it_first, it_second, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Compares two elements and returns the lesser of the two, where the ordering criterion may be specified by a binary predicate.
 */
input_iterator_t algo_min_if(input_iterator_t it_first, input_iterator_t it_second, bfun_t bfun_op)
{
    bool_t b_result = false;

    assert(_iterator_limit_type(it_first, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_second, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_second));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_second), &b_result);
    return b_result ? it_first : it_second;
}

/**
 * Finds the first occurrence of largest element in a specified range.
 */
forward_iterator_t algo_max_element(forward_iterator_t it_first, forward_iterator_t it_last)
{
    return algo_max_element_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Finds the first occurrence of largest element in a specified range where the ordering criterion specified by a binary predicate.
 */
forward_iterator_t algo_max_element_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op)
{
    iterator_t it_result;
    bool_t     b_cmp = false;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (iterator_equal(it_first, it_last)) {
        return it_first;
    }

    it_result = it_first;
    for (it_first = iterator_next(it_first);
         !iterator_equal(it_first, it_last);
         it_first = iterator_next(it_first)) {
        (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_result), &b_cmp);
        /* *it_first >= *it_result */
        if (!b_cmp) {
            it_result = it_first;
        }
    }

    return it_result;
}

/**
 * Finds the first occurrence of smallest element in a specified range.
 */
forward_iterator_t algo_min_element(forward_iterator_t it_first, forward_iterator_t it_last)
{
    return algo_min_element_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Finds the first occurrence of smallest element in a specified range where the ordering criterion specified by a binary predicate.
 */
forward_iterator_t algo_min_element_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op)
{
    iterator_t it_result;
    bool_t     b_cmp = false;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (iterator_equal(it_first, it_last)) {
        return it_first;
    }

    it_result = it_first;
    for (it_first = iterator_next(it_first);
         !iterator_equal(it_first, it_last);
         it_first = iterator_next(it_first)) {
        (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_result), &b_cmp);
        /* *it_first < *it_result */
        if (b_cmp) {
            it_result = it_first;
        }
    }

    return it_result;
}

/**
 * Compares element by element between two sequences to determine which is lesser of the two.
 */
bool_t algo_lexicographical_compare(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2)
{
    return algo_lexicographical_compare_if(it_first1, it_last1, it_first2, it_last2, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Compares element by element between two sequences to determine which is lesser of the two.
 */
bool_t algo_lexicographical_compare_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    bfun_t bfun_op)
{
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);
    }
    for (;
         !iterator_equal(it_first1, it_last1) && !iterator_equal(it_first2, it_last2);
         it_first1 = iterator_next(it_first1), it_first2 = iterator_next(it_first2)) {
        (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_result);
        if (b_result) {
            return true;
        }
        (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_result);
        if (b_result) {
            return false;
        }
    }

    return iterator_equal(it_first1, it_last1) && !iterator_equal(it_first2, it_last2) ? true : false;
}

/**
 * Compares element by element between two sequences to determine the relation is less or equal or greater.
 */
int algo_lexicographical_compare_3way(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2)
{
    return algo_lexicographical_compare_3way_if(it_first1, it_last1, it_first2, it_last2, _fun_get_binary(it_first1, _LESS_FUN));
}

/**
 * Compares element by element between two sequences to determine the relation is less or equal or greater.
 */
int algo_lexicographical_compare_3way_if(
    input_iterator_t it_first1, input_iterator_t it_last1,
    input_iterator_t it_first2, input_iterator_t it_last2,
    bfun_t bfun_op)
{
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first1, _LESS_FUN);
    }
    for (;
         !iterator_equal(it_first1, it_last1) && !iterator_equal(it_first2, it_last2);
         it_first1 = iterator_next(it_first1), it_first2 = iterator_next(it_first2)) {
        (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), &b_result);
        if (b_result) {
            return -1;
        }
        (*bfun_op)(iterator_get_pointer(it_first2), iterator_get_pointer(it_first1), &b_result);
        if (b_result) {
            return 1;
        }
    }

    if (iterator_equal(it_first1, it_last1) && !iterator_equal(it_first2, it_last2)) {
        return -1;
    } else if(iterator_equal(it_first1, it_last1) && iterator_equal(it_first2, it_last2)) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * Reorders the elements in a range so that the original ordering is replaced by the lexicographically next greater permutation if it exists.
 */
bool_t algo_next_permutation(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last)
{
    return algo_next_permutation_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Reorders the elements in a range so that the original ordering is replaced by the lexicographically next greater permutation if it exists,
 * where the sense of next specified with a binary predicate.
 */
bool_t algo_next_permutation_if(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, bfun_t bfun_op)
{
    iterator_t it_begin;
    iterator_t it_next;
    iterator_t it_end;
    bool_t     b_result = false;

    assert(_iterator_valid_range(it_first, it_last, _BIDIRECTIONAL_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (iterator_equal(it_first, it_last)) {
        return false;
    }
    it_begin = iterator_next(it_first);
    if (iterator_equal(it_begin, it_last)) {
        return false;
    }

    it_begin = iterator_prev(it_last);
    for (;;) {
        it_next = it_begin;
        it_begin = iterator_prev(it_begin);

        (*bfun_op)(iterator_get_pointer(it_begin), iterator_get_pointer(it_next), &b_result);
        if (b_result) {
            it_end = iterator_prev(it_last);
            (*bfun_op)(iterator_get_pointer(it_begin), iterator_get_pointer(it_end), &b_result);
            while (!b_result) {
                it_end = iterator_prev(it_end);
                (*bfun_op)(iterator_get_pointer(it_begin), iterator_get_pointer(it_end), &b_result);
            }
            algo_iter_swap(it_begin, it_end);
            algo_reverse(it_next, it_last);
            return true;
        }

        if (iterator_equal(it_begin, it_first)) {
            algo_reverse(it_first, it_last);
            return false;
        }
    }
}

/**
 * Reorders the elements in a range so that the original ordering is replaced by the lexicographically previous permutation if it exists.
 */
bool_t algo_prev_permutation(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last)
{
    return algo_prev_permutation_if(it_first, it_last, _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Reorders the elements in a range so that the original ordering is replaced by the lexicographically previous permutation if it exists,
 * where the sense of next specified with a binary predicate.
 */
bool_t algo_prev_permutation_if(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, bfun_t bfun_op)
{
    iterator_t it_begin;
    iterator_t it_next;
    iterator_t it_end;
    bool_t     b_result = false;

    assert(_iterator_valid_range(it_first, it_last, _BIDIRECTIONAL_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if (iterator_equal(it_first, it_last)) {
        return false;
    }
    it_begin = iterator_next(it_first);
    if (iterator_equal(it_begin, it_last)) {
        return false;
    }

    it_begin = iterator_prev(it_last);
    for (;;) {
        it_next = it_begin;
        it_begin = iterator_prev(it_begin);

        (*bfun_op)(iterator_get_pointer(it_next), iterator_get_pointer(it_begin), &b_result);
        if (b_result) {
            it_end = iterator_prev(it_last);
            (*bfun_op)(iterator_get_pointer(it_end), iterator_get_pointer(it_begin), &b_result);
            while (!b_result) {
                it_end = iterator_prev(it_end);
                (*bfun_op)(iterator_get_pointer(it_end), iterator_get_pointer(it_begin), &b_result);
            }
            algo_iter_swap(it_begin, it_end);
            algo_reverse(it_next, it_last);
            return true;
        }

        if (iterator_equal(it_begin, it_first)) {
            algo_reverse(it_first, it_last);
            return false;
        }
    }
}

/** eof **/

