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

/*
#include <cstl/cstl_algo_nonmutating_private.h>
#include <cstl/cstl_algo_nonmutating.h>
#include <cstl/cstl_algo_mutating_private.h>
#include <cstl/cstl_algo_mutating.h>

#include <cstl/cstl_algobase.h>
#include <cstl/cstl_algobase_private.h>
#include <cstl/cstl_heap.h>

#include <cstl/cstl_algo.h>
#include <cstl/cstl_algo_private.h>

#include "cstl_algo_mutating_aux.h"
*/

/** local constant declaration and local macro section **/

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
    random_access_iterator_t it_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t it_last)
{
    algo_partial_sort_if(it_first, t_middle, it_last,
        _fun_get_binary(it_first, _LESS_FUN));
}

/**
 * Arranges a specified number of the smaller elements in a range according to an ordering criterion specified by a binary predicate.
 */
void algo_partial_sort_if(
    random_access_iterator_t it_first,
    random_access_iterator_t t_middle,
    random_access_iterator_t it_last,
    binary_function_t bfun_op)
{
    iterator_t t_prev;
    iterator_t t_iterator;
    bool_t     b_result = false;

    assert(_iterator_valid_range(it_first, t_middle, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_valid_range(t_middle, it_last, _RANDOM_ACCESS_ITERATOR));

    if(bfun_op == NULL)
    {
        bfun_op = _fun_get_binary(it_first, _LESS_FUN);
    }

    if(iterator_equal(it_first, t_middle))
    {
        return;
    }

    algo_make_heap_if(it_first, t_middle, bfun_op);
    for(t_iterator = t_middle;
        !iterator_equal(t_iterator, it_last);
        t_iterator = iterator_next(t_iterator))
    {
        (*bfun_op)(
            iterator_get_pointer(t_iterator), iterator_get_pointer(it_first), &b_result);
        if(b_result)
        {
            algo_pop_heap_if(it_first, t_middle, bfun_op);
            t_prev = t_middle;
            t_prev = iterator_prev(t_prev);
            algo_iter_swap(t_prev, t_iterator);
            algo_push_heap_if(it_first, t_middle, bfun_op);
        }
    }
    algo_sort_heap_if(it_first, t_middle, bfun_op);
}

/** eof **/

