/*
 *  The implementation of auxiliary mutating algorithm.
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

#include "cstl_algo_mutating_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Exchanges the elements in two adjacent ranges with forward iterator type.
 */
void _algo_rotate_forward(forward_iterator_t it_first, forward_iterator_t it_middle, forward_iterator_t it_last)
{
    iterator_t it_iter = it_middle;

    assert(_iterator_valid_range(it_first, it_middle, _FORWARD_ITERATOR));
    assert(_iterator_valid_range(it_middle, it_last, _FORWARD_ITERATOR));
    assert(_ITERATOR_ITERATOR_TYPE(it_first) == _FORWARD_ITERATOR &&
           _ITERATOR_ITERATOR_TYPE(it_middle) == _FORWARD_ITERATOR &&
           _ITERATOR_ITERATOR_TYPE(it_last) == _FORWARD_ITERATOR);
    assert(!iterator_equal(it_first, it_middle) && !iterator_equal(it_middle, it_last));

    for (;;) {
        algo_iter_swap(it_first, it_iter);
        it_first = iterator_next(it_first);
        it_iter = iterator_next(it_iter);

        if (iterator_equal(it_first, it_middle)) {      /* the [it_first, it_middle) is empty */
            if (iterator_equal(it_iter, it_last)) {
                return;
            }

            it_middle = it_iter;
        } else if (iterator_equal(it_iter, it_last)) {  /* the [it_middle, it_last) is empty */
            it_iter = it_middle;
        }
    }
}

/**
 * Classifies elements in a range into two disjoint sets, with those elements satisfying a unary predicate preceding those that fail to satisfy it.
 */
bidirectional_iterator_t _algo_partition_biditer(bidirectional_iterator_t it_first, bidirectional_iterator_t it_last, ufun_t ufun_op)
{
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first, it_last, _BIDIRECTIONAL_ITERATOR));

    if (ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    for (;;) {
        /* the first element that don't satisfy the ufun_op */
        for (;;) {
            if (iterator_equal(it_first, it_last)) {
                return it_first;
            } else {
                (*ufun_op)(iterator_get_pointer(it_first), &b_result);
                if (b_result) {
                    it_first = iterator_next(it_first);
                } else {
                    break;
                }
            }
        }

        /* find the last element that satisfy the ufun_op */
        it_last = iterator_prev(it_last);
        for (;;) {
            if (iterator_equal(it_first, it_last)) {
                return it_first;
            } else {
                (*ufun_op)(iterator_get_pointer(it_last), &b_result);
                if (!b_result) {
                    it_last = iterator_prev(it_last);
                } else {
                    break;
                }
            }
        }

        /* swap element */
        algo_iter_swap(it_first, it_last);
        it_first = iterator_next(it_first);
    }
}

/** eof **/

