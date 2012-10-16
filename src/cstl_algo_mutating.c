/*
 *  The implementation of mutating algorithm.
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

#include <cstl/cstl_algo_mutating_private.h>
#include <cstl/cstl_algo_mutating.h>

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

/** eof **/

