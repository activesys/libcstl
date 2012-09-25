/*
 *  The implementation of non-mutating algorithm.
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

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Applies a unary function to each element in a range.
 */
void algo_for_each(input_iterator_t it_first, input_iterator_t it_last, unary_function_t ufun_op)
{
    assert(_iterator_valid_range(it_first, it_last, _INPUT_ITERATOR));

    if(ufun_op == NULL) {
        ufun_op = fun_default_unary;
    }

    for(; !iterator_equal(it_first, it_last); it_first = iterator_next(it_first)) {
        (*ufun_op)(iterator_get_pointer(it_first), NULL);
    }
}

/** eof **/

