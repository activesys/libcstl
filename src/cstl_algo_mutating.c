/*
 *  The implementation of mutating algorithm.
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

#include "cstl_algo_mutating_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a forward direction.
 */
output_iterator_t algo_copy(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result)
{
    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first), it_result = iterator_next(it_result)) {
        iterator_set_value(it_result, iterator_get_pointer(it_first));
    }

    return it_result;
}

/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a forward direction.
 */
output_iterator_t algo_copy_n(input_iterator_t it_first, size_t t_count, output_iterator_t it_result)
{
    return algo_copy(it_first, iterator_advance(it_first, t_count), it_result);
}

/**
 * Assigns the values of elements from a source range to a destination range, iterating through the source sequence of elements and
 * assigning them new positions in a backward direction.
 */
bidirectional_iterator_t algo_copy_backward(
    bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, bidirectional_iterator_t it_result)
{
    assert(_iterator_valid_range(it_first, it_last, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_limit_type(it_result, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    while (!iterator_equal(it_first, it_last)) {
        it_last = iterator_prev(it_last);
        it_result = iterator_prev(it_result);
        iterator_set_value(it_result, iterator_get_pointer(it_last));
    }

    return it_result;
}

/**
 * Exchanges two values referred to by a pair of specified iterators.
 */
void algo_swap(forward_iterator_t it_first, forward_iterator_t it_second)
{
    algo_iter_swap(it_first, it_second);
}

/**
 * Exchanges two values referred to by a pair of specified iterators.
 */
void algo_iter_swap(forward_iterator_t it_first, forward_iterator_t it_second)
{
    void* pv_value = NULL;

    assert(_iterator_limit_type(it_first, _FORWARD_ITERATOR));
    assert(_iterator_limit_type(it_second, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_second));

    if (!iterator_equal(it_first, it_second)) {
        pv_value = _iterator_allocate_init_elem(it_first);

        if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
            string_assign_cstr((string_t*)pv_value, iterator_get_pointer(it_first));
            iterator_set_value(it_first, iterator_get_pointer(it_second));
            iterator_set_value(it_second, string_c_str((string_t*)pv_value));
        } else {
            iterator_get_value(it_first, pv_value);
            iterator_set_value(it_first, iterator_get_pointer(it_second));
            iterator_set_value(it_second, pv_value);
        }

        _iterator_deallocate_destroy_elem(it_first, pv_value);
        pv_value = NULL;
    }
}

/**
 * Exchanges the elements of one range with the elements of another, equal sized range.
 */
forward_iterator_t algo_swap_ranges(forward_iterator_t it_first1, forward_iterator_t it_last1, forward_iterator_t it_first2)
{
    assert(_iterator_valid_range(it_first1, it_last1, _FORWARD_ITERATOR));
    assert(_iterator_limit_type(it_first2, _FORWARD_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    for (; !iterator_equal(it_first1, it_last1); it_first1 = iterator_next(it_first1), it_first2 = iterator_next(it_first2)) {
        algo_iter_swap(it_first1, it_first2);
    }

    return it_first2;
}

/**
 * Applies a specified function object to each element in a source range and copies the return values of the function object into a destination range.
 */
output_iterator_t algo_transform(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, ufun_t ufun_op)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(it_first);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first), it_result = iterator_next(it_result)) {
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(it_first));
            (*ufun_op)(iterator_get_pointer(it_first), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(it_result, string_c_str((string_t*)pv_value));
        }
    } else {
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first), it_result = iterator_next(it_result)) {
            (*ufun_op)(iterator_get_pointer(it_first), pv_value);
            iterator_set_value(it_result, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return it_result;
}

/**
 * Applies a specified function object to a pair of elements from two source ranges and copies the return values of the function into a destination range.
 */
output_iterator_t algo_transform_binary(
    input_iterator_t it_first1, input_iterator_t it_last1, 
    input_iterator_t it_first2, output_iterator_t it_result,
    bfun_t bfun_op)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));
    assert(_iterator_limit_type(it_first2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_result));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));

    if (bfun_op == NULL) {
        bfun_op = fun_default_binary;
    }

    pv_value = _iterator_allocate_init_elem(it_first1);

    if (strncmp(_iterator_get_typebasename(it_first1), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (;
             !iterator_equal(it_first1, it_last1);
             it_first1 = iterator_next(it_first1),
             it_first2 = iterator_next(it_first2),
             it_result = iterator_next(it_result)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(it_result, string_c_str((string_t*)pv_value));
        }
    } else {
        for (;
             !iterator_equal(it_first1, it_last1);
             it_first1 = iterator_next(it_first1),
             it_first2 = iterator_next(it_first2),
             it_result = iterator_next(it_result)) {
            (*bfun_op)(iterator_get_pointer(it_first1), iterator_get_pointer(it_first2), pv_value);
            iterator_set_value(it_result, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(it_first1, pv_value);
    pv_value = NULL;

    return it_result;
}

/**
 * Assigns the values generated by a unary function to each element in a range.
 */
void algo_generate(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op)
{
    void* pv_value = NULL;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(it_first);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(it_first));
            (*ufun_op)(string_c_str((string_t*)pv_value), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(it_first, string_c_str((string_t*)pv_value));
        }
    } else {
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
            iterator_get_value(it_first, pv_value);
            (*ufun_op)(pv_value, pv_value);
            iterator_set_value(it_first, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;
}

/**
 * Assigns the values generated by a unary function to a specified number of element in a range and returns to the position one past the last assigned value.
 */
output_iterator_t algo_generate_n(output_iterator_t it_first, size_t t_count, ufun_t ufun_op)
{
    size_t i = 0;
    void* pv_value = NULL;

    assert(_iterator_limit_type(it_first, _OUTPUT_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    pv_value = _iterator_allocate_init_elem(it_first);

    if (strncmp(_iterator_get_typebasename(it_first), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        for (i = 0; i < t_count; ++i, it_first = iterator_next(it_first)) {
            string_assign_cstr((string_t*)pv_value, (char*)iterator_get_pointer(it_first));
            (*ufun_op)(string_c_str((string_t*)pv_value), (char*)string_c_str((string_t*)pv_value));
            iterator_set_value(it_first, string_c_str((string_t*)pv_value));
        }
    } else {
        for (i = 0; i < t_count; ++i, it_first = iterator_next(it_first)) {
            iterator_get_value(it_first, pv_value);
            (*ufun_op)(pv_value, pv_value);
            iterator_set_value(it_first, pv_value);
        }
    }

    _iterator_deallocate_destroy_elem(it_first, pv_value);
    pv_value = NULL;

    return it_first;
}

/**
 * Eliminates elements that satisfy a predicate from a given range without disturbing the order of the remaining elements and
 * returning the end of a new range free of the specified value.
 */
forward_iterator_t algo_remove_if(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op)
{
    iterator_t it_next;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    it_first = algo_find_if(it_first, it_last, ufun_op);
    if (iterator_equal(it_first, it_last)) {
        return it_first;
    } else {
        it_next = iterator_next(it_first);
        return algo_remove_copy_if(it_next, it_last, it_first, ufun_op);
    }
}

/**
 * Copies elements from a source range to a destination range, except that satisfying a predicate are not copied, without disturbing the order of the remaining
 * elements and returning the end of a new destination range.
 */
output_iterator_t algo_remove_copy_if(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, ufun_t ufun_op)
{
    bool_t b_cmp = false;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
        (*ufun_op)(iterator_get_pointer(it_first), &b_cmp);
        if (!b_cmp) {
            iterator_set_value(it_result, iterator_get_pointer(it_first));
            it_result = iterator_next(it_result);
        }
    }

    return it_result;
}

/**
 * Removes duplicate elements that are adjacent to each other in a specified range.
 */
forward_iterator_t algo_unique(forward_iterator_t it_first, forward_iterator_t it_last)
{
    return algo_unique_if(it_first, it_last, _fun_get_binary(it_first, _EQUAL_FUN));
}

/**
 * Removes duplicate elements that are adjacent to each other in a specified range.
 */
forward_iterator_t algo_unique_if(forward_iterator_t it_first, forward_iterator_t it_last, bfun_t bfun_op)
{
    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    it_first = algo_adjacent_find_if(it_first, it_last, bfun_op);
    return algo_unique_copy_if(it_first, it_last, it_first, bfun_op);
}

/**
 * Copies elements from a source range into a destination range except for the duplicate elements that are adjacent to each other.
 */
output_iterator_t algo_unique_copy(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result)
{
    return algo_unique_copy_if(it_first, it_last, it_result, _fun_get_binary(it_first, _EQUAL_FUN));
}

/**
 * Copies elements from a source range into a destination range except for the duplicate elements that are adjacent to each other.
 */
output_iterator_t algo_unique_copy_if(input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, bfun_t bfun_op)
{
    bool_t b_cmp = false;
    bool_t b_less = false;
    bool_t b_greater = false;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    if (bfun_op == NULL) {
        bfun_op = _fun_get_binary(it_first, _EQUAL_FUN);
    }

    if (iterator_equal(it_first, it_last)) {
        return it_result;
    }

    if (bfun_op == fun_default_binary) {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);

        iterator_set_value(it_result, iterator_get_pointer(it_first));
        it_first = iterator_next(it_first);
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
            (*bfun_op)(iterator_get_pointer(it_result), iterator_get_pointer(it_first), &b_less);
            if (b_less) {
                it_result = iterator_next(it_result);
                iterator_set_value(it_result, iterator_get_pointer(it_first));
                continue;
            }
            (*bfun_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_result), &b_greater);
            if (b_greater) {
                it_result = iterator_next(it_result);
                iterator_set_value(it_result, iterator_get_pointer(it_first));
                continue;
            }
        }
    } else {
        iterator_set_value(it_result, iterator_get_pointer(it_first));
        it_first = iterator_next(it_first);
        for (; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
            (*bfun_op)(iterator_get_pointer(it_result), iterator_get_pointer(it_first), &b_cmp);
            if (!b_cmp) {
                it_result = iterator_next(it_result);
                iterator_set_value(it_result, iterator_get_pointer(it_first));
            }
        }
    }

    it_result = iterator_next(it_result);
    return it_result;
}

/**
 * Reverses the order of the elements within a range.
 */
void algo_reverse(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last)
{
    assert(_iterator_valid_range(it_first, it_last, _BIDIRECTIONAL_ITERATOR));

    for (;;) {
        if (iterator_equal(it_first, it_last)) {
            return;
        }
        it_last = iterator_prev(it_last);
        if (iterator_equal(it_first, it_last)) {
            return;
        }

        algo_iter_swap(it_first, it_last);
        it_first = iterator_next(it_first);
    }
}

/**
 * Reverses the order of the elements within a source range while copying them into a destination range
 */
output_iterator_t algo_reverse_copy(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, output_iterator_t it_result)
{
    assert(_iterator_valid_range(it_first, it_last, _BIDIRECTIONAL_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    while (!iterator_equal(it_first, it_last)) {
        it_last = iterator_prev(it_last);
        iterator_set_value(it_result, iterator_get_pointer(it_last));
        it_result = iterator_next(it_result);
    }

    return it_result;
}

/**
 * Exchanges the elements in two adjacent ranges.
 */
forward_iterator_t algo_rotate(forward_iterator_t it_first, forward_iterator_t it_middle, forward_iterator_t it_last)
{
    size_t t_distance = 0;

    assert(_iterator_valid_range(it_first, it_middle, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(it_middle, it_last, _FORWARD_ITERATOR));

    if (iterator_equal(it_first, it_middle) || iterator_equal(it_middle, it_last)) {
        return it_middle;
    }

    t_distance = iterator_distance(it_middle, it_last);

    if (_ITERATOR_ITERATOR_TYPE(it_first) == _FORWARD_ITERATOR &&
        _ITERATOR_ITERATOR_TYPE(it_middle) == _FORWARD_ITERATOR &&
        _ITERATOR_ITERATOR_TYPE(it_last) == _FORWARD_ITERATOR) {
        _algo_rotate_forward(it_first, it_middle, it_last);
    } else {
        algo_reverse(it_first, it_middle);
        algo_reverse(it_middle, it_last);
        algo_reverse(it_first, it_last);
    }

    it_middle = iterator_advance(it_first, t_distance);

    return it_middle;
}

/**
 * Exchanges the elements in two adjacent ranges within a source range and copies the result to a destination range.
 */
output_iterator_t algo_rotate_copy(forward_iterator_t it_first, forward_iterator_t it_middle, forward_iterator_t it_last, output_iterator_t it_result)
{
    assert(_iterator_valid_range(it_first, it_middle, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(it_middle, it_last, _FORWARD_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    return algo_copy(it_first, it_middle, algo_copy(it_middle, it_last, it_result));
}

/**
 * Rearranges a sequence of N elements in a range into one of N! possible arrangements selected at random.
 */
void algo_random_shuffle(random_access_iterator_t it_first, random_access_iterator_t it_last)
{
    algo_random_shuffle_if(it_first, it_last, fun_random_number);
}

/**
 * Rearranges a sequence of N elements in a range into one of N! possible arrangements selected at random.
 */
void algo_random_shuffle_if(random_access_iterator_t it_first, random_access_iterator_t it_last, ufun_t ufun_op)
{
    iterator_t it_iter;
    iterator_t it_tmp;
    size_t     t_len = 0;
    size_t     t_random = 0;

    assert(_iterator_valid_range(it_first, it_last, _RANDOM_ACCESS_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    if (!iterator_equal(it_first, it_last)) {
        for (it_iter = iterator_next(it_first); !iterator_equal(it_iter, it_last); it_iter = iterator_next(it_iter)) {
            t_len = iterator_distance(it_first, it_iter) + 1;
            (*ufun_op)(&t_len, &t_random);
            if (t_len != 0) {
                t_random %= t_len;
            }
            it_tmp = iterator_advance(it_first, t_random);
            algo_iter_swap(it_iter, it_tmp);
        }
    }
}

/**
 * Copy a sample of the elements from the range [it_first1, it_last1) into the range [it_first2, it_last2).
 */
random_access_iterator_t algo_random_sample(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2)
{
    return algo_random_sample_if(it_first1, it_last1, it_first2, it_last2, fun_random_number);
}

/**
 * Copy a sample of the elements from the range [it_first1, it_last1) into the range [it_first2, it_last2).
 */
random_access_iterator_t algo_random_sample_if(
    input_iterator_t it_first1, input_iterator_t it_last1, random_access_iterator_t it_first2, random_access_iterator_t it_last2, ufun_t ufun_op)
{
    iterator_t it_in;
    iterator_t it_out;
    size_t     t_outlen = 0;
    size_t     t_inlen = 0;
    size_t     t_random = 0;

    assert(_iterator_valid_range(it_first1, it_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(it_first2, it_last2, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_same_elem_type(it_first1, it_first2));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    for (it_in = it_first1, it_out = it_first2;
         !iterator_equal(it_in, it_last1) && !iterator_equal(it_out, it_last2);
         it_in = iterator_next(it_in), it_out = iterator_next(it_out)) {
        iterator_set_value(it_out, iterator_get_pointer(it_in));
    }

    t_inlen = iterator_distance(it_first1, it_last1);
    t_outlen = iterator_distance(it_first2, it_last2);
    for (; !iterator_equal(it_in, it_last1); it_in = iterator_next(it_in)) {
        t_inlen++;
        (*ufun_op)(&t_inlen, &t_random);
        t_random %= t_inlen;
        if (t_random < t_outlen) {
            it_out = iterator_advance(it_first2, t_random);
            iterator_set_value(it_out, iterator_get_pointer(it_in));
        }
    }

    return iterator_advance(it_first2, t_outlen < t_inlen ? t_outlen : t_inlen);
}

/**
 * Copy a sample of the elements from the range [it_first1, it_last1) into the range [it_first2, it_first2 + t_count).
 */
output_iterator_t algo_random_sample_n(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, size_t t_count)
{
    return algo_random_sample_n_if(it_first, it_last, it_result, t_count, fun_random_number);
}

/**
 * Copy a sample of the elements from the range [it_first1, it_last1) into the range [it_first2, it_first2 + t_count).
 */
output_iterator_t algo_random_sample_n_if(
    input_iterator_t it_first, input_iterator_t it_last, output_iterator_t it_result, size_t t_count, ufun_t ufun_op)
{
    size_t t_len = 0;
    size_t t_tmp = 0;
    size_t t_random = 0;

    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));
    assert(_iterator_limit_type(it_result, _OUTPUT_ITERATOR));
    assert(_iterator_same_elem_type(it_first, it_result));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    t_len = iterator_distance(it_first, it_last);
    t_tmp = t_count < t_len ? t_count : t_len;
    while (t_tmp > 0) {
        (*ufun_op)(&t_len, &t_random);
        if (t_len != 0) {
            t_random %= t_len;
        }
        if (t_random < t_tmp) {
            iterator_set_value(it_result, iterator_get_pointer(it_first));
            it_result = iterator_next(it_result);
            t_tmp--;
        }
        it_first = iterator_next(it_first);
        t_len--;
    }

    return it_result;
}

/**
 * Classifies elements in a range into two disjoint sets, with those elements satisfying a unary predicate preceding those that fail to satisfy it.
 */
forward_iterator_t algo_partition(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op)
{
    bool_t     b_result = false;
    iterator_t it_next;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if ((_ITERATOR_ITERATOR_TYPE(it_first) == _BIDIRECTIONAL_ITERATOR && _ITERATOR_ITERATOR_TYPE(it_last) == _BIDIRECTIONAL_ITERATOR) ||
        (_ITERATOR_ITERATOR_TYPE(it_first) == _RANDOM_ACCESS_ITERATOR && _ITERATOR_ITERATOR_TYPE(it_first) == _RANDOM_ACCESS_ITERATOR)) {
        return _algo_partition_biditer(it_first, it_last, ufun_op);
    }

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    if (iterator_equal(it_first, it_last)) {
        return it_first;
    }

    while (!iterator_equal(it_first, it_last)) {
        (*ufun_op)(iterator_get_pointer(it_first), &b_result);
        if (!b_result) {
            for (it_next = iterator_next(it_first); !iterator_equal(it_next, it_last); it_next = iterator_next(it_next)) {
                (*ufun_op)(iterator_get_pointer(it_next), &b_result);
                if (b_result) {
                    algo_iter_swap(it_first, it_next);
                    break;
                }
            }

            if (iterator_equal(it_next, it_last)) {
                return it_first;
            }
        }

        it_first = iterator_next(it_first);
    }

    return it_first;
}

/**
 * Classifies elements in a range into two disjoint sets, with those elements satisfying a unary predicate preceding those that fail to satisfy it,
 * preserving the relative order of equivalent elements.
 */
forward_iterator_t algo_stable_partition(forward_iterator_t it_first, forward_iterator_t it_last, ufun_t ufun_op)
{
    bool_t     b_result = false;
    iterator_t it_next;
    iterator_t it_index;

    assert(_iterator_valid_range(it_first, it_last, _FORWARD_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    if (iterator_equal(it_first, it_last)) {
        return it_first;
    }

    while (!iterator_equal(it_first, it_last)) {
        (*ufun_op)(iterator_get_pointer(it_first), &b_result);
        if (!b_result) {
            for (it_next = iterator_next(it_first); !iterator_equal(it_next, it_last); it_next = iterator_next(it_next)) {
                (*ufun_op)(iterator_get_pointer(it_next), &b_result);
                if (b_result) {
                    it_index = it_first;
                    do {
                        it_index = iterator_next(it_index);
                        algo_iter_swap(it_first, it_index);
                    } while (!iterator_equal(it_index, it_next));
                    break;
                }
            }

            if (iterator_equal(it_next, it_last)) {
                return it_first;
            }
        }

        it_first = iterator_next(it_first);
    }

    return it_first;
}

/** eof **/

