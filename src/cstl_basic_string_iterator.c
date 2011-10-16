/*
 *  The implementation of basic_string iterator functions.
 *  Copyright (C)  2008,2009,2010,2011  Wangbo
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
#include <cstl/cvector.h>

#include <cstl/cstl_basic_string_iterator.h>
#include <cstl/cstl_basic_string_private.h>
#include <cstl/cstl_basic_string.h>

#include "cstl_basic_string_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create new basic_string iterator.
 */
basic_string_iterator_t _create_basic_string_iterator(void)
{
    basic_string_iterator_t it_new = _create_vector_iterator();
    _GET_BASIC_STRING_CONTAINER_TYPE(it_new) = _BASIC_STRING_CONTAINER;

    return it_new;
}

/**
 * Compare two iterators for equality.
 */
bool_t _basic_string_iterator_equal(basic_string_iterator_t it_first, basic_string_iterator_t it_second)
{
    bool_t b_result;

    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_first) == _BASIC_STRING_CONTAINER);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_second) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_first) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(it_second) = _VECTOR_CONTAINER;

    b_result = _vector_iterator_equal(it_first, it_second);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_first) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(it_second) = _BASIC_STRING_CONTAINER;

    return b_result;
}

/**
 * Get iterator reference data.
 */
void _basic_string_iterator_get_value(basic_string_iterator_t it_iter, void* pv_value)
{
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;

    _vector_iterator_get_value(it_iter, pv_value);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;
}

/**
 * Set iterator reference data.
 */
void _basic_string_iterator_set_value(basic_string_iterator_t it_iter, const void* cpv_value)
{
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;

    _vector_iterator_set_value(it_iter, cpv_value);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;
}

/**
 * Get the pointer that point to the iterator reference data.
 */
const void* _basic_string_iterator_get_pointer(basic_string_iterator_t it_iter)
{
    void* pv_pointer = NULL;

    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;

    pv_pointer = (void*)_vector_iterator_get_pointer(it_iter);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;

    return pv_pointer;
}

/**
 * Get the iterator that reference next data.
 */
basic_string_iterator_t _basic_string_iterator_next(basic_string_iterator_t it_iter)
{
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;

    it_iter = _vector_iterator_next(it_iter);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;

    return it_iter;
}

/**
 * Get the iterator that reference previous data.
 */
basic_string_iterator_t _basic_string_iterator_prev(basic_string_iterator_t it_iter)
{
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;

    it_iter = _vector_iterator_prev(it_iter);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;

    return it_iter;
}

/**
 * Access iterator reference data randomly with subscript.
 */
void* _basic_string_iterator_at(basic_string_iterator_t it_iter, int n_index)
{
    void* pv_value = NULL;

    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;

    pv_value = _vector_iterator_at(it_iter, n_index);
    assert(pv_value != NULL);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;

    return pv_value;
}

/**
 * Get the iterator that reference next n data.
 */
basic_string_iterator_t _basic_string_iterator_next_n(basic_string_iterator_t it_iter, int n_step)
{
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;

    it_iter = _vector_iterator_next_n(it_iter, n_step);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;

    return it_iter;
}

/**
 * Get the iterator that reference previous n data.
 */
basic_string_iterator_t _basic_string_iterator_prev_n(basic_string_iterator_t it_iter, int n_step)
{
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_iter) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;

    it_iter = _vector_iterator_prev_n(it_iter, n_step);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;

    return it_iter;
}

/**
 * Calculate the distance between two iterators.
 */
int _basic_string_iterator_minus(basic_string_iterator_t it_first, basic_string_iterator_t it_second)
{
    int n_distance = 0;

    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_first) == _BASIC_STRING_CONTAINER);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_second) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_first) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(it_second) = _VECTOR_CONTAINER;

    n_distance = _vector_iterator_minus(it_first, it_second);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_first) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(it_second) = _BASIC_STRING_CONTAINER;

    return n_distance;
}

/**
 * Testing of the first iterator is less than the second iterator.
 */
bool_t _basic_string_iterator_less(basic_string_iterator_t it_first, basic_string_iterator_t it_second)
{
    bool_t b_result;

    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_first) == _BASIC_STRING_CONTAINER);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_second) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_first) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(it_second) = _VECTOR_CONTAINER;

    b_result = _vector_iterator_less(it_first, it_second);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_first) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(it_second) = _BASIC_STRING_CONTAINER;

    return b_result;   
}

/**
 * Testing of the first iterator is located in front of the second iterator.
 */
bool_t _basic_string_iterator_before(basic_string_iterator_t it_first, basic_string_iterator_t it_second)
{
    bool_t b_result;

    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_first) == _BASIC_STRING_CONTAINER);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(it_second) == _BASIC_STRING_CONTAINER);

    _GET_VECTOR_CONTAINER_TYPE(it_first) = _VECTOR_CONTAINER;
    _GET_VECTOR_CONTAINER_TYPE(it_second) = _VECTOR_CONTAINER;

    b_result = _vector_iterator_before(it_first, it_second);

    _GET_BASIC_STRING_CONTAINER_TYPE(it_first) = _BASIC_STRING_CONTAINER;
    _GET_BASIC_STRING_CONTAINER_TYPE(it_second) = _BASIC_STRING_CONTAINER;

    return b_result;
}

/** local function implementation section **/

/** eof **/

