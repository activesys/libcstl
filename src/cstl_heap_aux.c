/*
 *  The implementation of auxiliary heap.
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
 * Adjust specific position element into a heap.
 */
void _algo_adjust_heap(
    random_access_iterator_t it_first, random_access_iterator_t it_last, random_access_iterator_t it_parent, bfun_t bfun_op)
{
    bool_t                   b_result = false;
    size_t                   t_len = 0;
    size_t                   t_ppos = 0;
    size_t                   t_lpos = 0;
    size_t                   t_rpos = 0;
    random_access_iterator_t it_left;
    random_access_iterator_t it_right;

    assert(_iterator_valid_range(it_first, it_parent, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_valid_range(it_parent, it_last, _RANDOM_ACCESS_ITERATOR));
    assert(bfun_op != NULL);

    if (!iterator_equal(it_first, it_last)) {
        /* get left child and right child */
        t_len = iterator_distance(it_first, it_last);
        t_ppos = iterator_distance(it_first, it_parent);
        t_lpos = t_ppos * 2 + 1;
        t_rpos = t_ppos * 2 + 2;

        while (t_lpos < t_len) {
            if (t_rpos < t_len) {
                it_left = it_right = it_first;
                it_left = iterator_next_n(it_left, t_lpos);
                it_right = iterator_next_n(it_right, t_rpos);

                (*bfun_op)(iterator_get_pointer(it_right), iterator_get_pointer(it_left), &b_result);
                if (b_result) { /* it_right < it_left */
                    (*bfun_op)(iterator_get_pointer(it_left), iterator_get_pointer(it_parent), &b_result);
                    if (b_result) { /* it_left < it_parent */
                        break;
                    } else {        /* it_left >= it_parent */
                        algo_iter_swap(it_parent, it_left);
                        it_parent = it_left;
                        t_ppos = t_lpos;
                    }
                } else {        /* it_right >= t_lef */
                    (*bfun_op)(iterator_get_pointer(it_right), iterator_get_pointer(it_parent), &b_result);
                    if (b_result) { /* it_right < it_parent */
                        break;
                    } else {        /* it_right >= it_parent */
                        algo_iter_swap(it_parent, it_right);
                        it_parent = it_right;
                        t_ppos = t_rpos;
                    }
                }
            } else {    /* don't have right child */
                it_left = it_first;
                it_left = iterator_next_n(it_left, t_lpos);

                (*bfun_op)(iterator_get_pointer(it_left), iterator_get_pointer(it_parent), &b_result);
                if (b_result) { /* it_left < it_parent */
                    break;
                } else {        /* it_left >= it_parent */
                    algo_iter_swap(it_parent, it_left);
                    it_parent = it_left;
                    t_ppos = t_lpos;
                }
            }

            t_lpos = t_ppos * 2 + 1;
            t_rpos = t_ppos * 2 + 2;
        }
    }
}

/** local function implementation section **/

/** eof **/

