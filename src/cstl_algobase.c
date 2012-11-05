/*
 *  The implementation of base algorithm.
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
#include <cstl/cfunctional.h>
#include <cstl/cstring.h>

#include <cstl/cstl_algobase.h>
#include <cstl/cstl_algobase_private.h>
#include <cstl/cstl_algo_mutating_private.h>
#include <cstl/cstl_algo_mutating.h>

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
bool_t algo_lexicographical_compare(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2)
{
    return algo_lexicographical_compare_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _LESS_FUN));
}

bool_t algo_lexicographical_compare_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }
    for(;
        !iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(t_result)
        {
            return true;
        }
        (*t_binary_op)(
            iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_result);
        if(t_result)
        {
            return false;
        }
    }

    if(iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int algo_lexicographical_compare_3way(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2)
{
    return algo_lexicographical_compare_3way_if(t_first1, t_last1, t_first2, t_last2,
        _fun_get_binary(t_first1, _LESS_FUN));
}

int algo_lexicographical_compare_3way_if(
    input_iterator_t t_first1, input_iterator_t t_last1,
    input_iterator_t t_first2, input_iterator_t t_last2,
    binary_function_t t_binary_op)
{
    bool_t t_result = false;

    assert(_iterator_valid_range(t_first1, t_last1, _INPUT_ITERATOR));
    assert(_iterator_valid_range(t_first2, t_last2, _INPUT_ITERATOR));
    assert(_iterator_same_elem_type(t_first1, t_first2));

    if(t_binary_op == NULL)
    {
        t_binary_op = _fun_get_binary(t_first1, _LESS_FUN);
    }
    for(;
        !iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2);
        t_first1 = iterator_next(t_first1), t_first2 = iterator_next(t_first2))
    {
        (*t_binary_op)(
            iterator_get_pointer(t_first1), iterator_get_pointer(t_first2), &t_result);
        if(t_result)
        {
            return -1;
        }
        (*t_binary_op)(
            iterator_get_pointer(t_first2), iterator_get_pointer(t_first1), &t_result);
        if(t_result)
        {
            return 1;
        }
    }

    if(iterator_equal(t_first1, t_last1) && !iterator_equal(t_first2, t_last2))
    {
        return -1;
    }
    else if(iterator_equal(t_first1, t_last1) && iterator_equal(t_first2, t_last2))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/** local function implementation section **/

/** eof **/

