/*
 *  The implementation of auxiliary sorting algorithm.
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
    random_access_iterator_t it_first, random_access_iterator_t it_middle, random_access_iterator_t it_last, binary_function_t t_binary_op)
{
    bool_t b_result = false;

    assert(_iterator_valid_range(it_first, it_middle, _RANDOM_ACCESS_ITERATOR));
    assert(_iterator_valid_range(it_middle, it_last, _RANDOM_ACCESS_ITERATOR));
    assert(t_binary_op != NULL);

    (*t_binary_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_middle), &b_result);
    if (b_result) {             /* it_first < it_middle */
        (*t_binary_op)(iterator_get_pointer(it_middle), iterator_get_pointer(it_last), &b_result);
        if (b_result){          /* it_first < it_middle < it_last */
            return it_middle;
        } else {                /* it_last <= it_middle */
            (*t_binary_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_last), &b_result);
            if (b_result) {     /* it_first < it_last <= it_middle */
                return it_last;
            }else {             /* it_last <= it_first <= it_middle */
                return it_first;
            }
        }
    } else {                    /* it_middle <= it_first */
        (*t_binary_op)(iterator_get_pointer(it_first), iterator_get_pointer(it_last), &b_result);
        if (b_result) {         /* it_middle <= it_first < it_last */
            return it_first;
        } else {                /* it_last <= it_first */
            (*t_binary_op)(iterator_get_pointer(it_middle), iterator_get_pointer(it_last), &b_result);
            if (b_result) {     /* it_middle < it_last <= it_first */
                return it_last;
            } else {            /* it_last <= it_middle <= it_first */
                return it_middle;
            }
        }
    }
}

/** eof **/

