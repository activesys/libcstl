/*
 *  The implementation of basic_string iterator functions.
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
    basic_string_iterator_t it_iter;

    _BASIC_STRING_ITERATOR_COREPOS(it_iter) = NULL;
    _ITERATOR_CONTAINER(it_iter) = NULL;
    _BASIC_STRING_ITERATOR_CONTAINER_TYPE(it_iter) = _BASIC_STRING_CONTAINER;
    _BASIC_STRING_ITERATOR_ITERATOR_TYPE(it_iter) = _RANDOM_ACCESS_ITERATOR;

    return it_iter;
}

/**
 * Compare two iterators for equality.
 */
bool_t _basic_string_iterator_equal(basic_string_iterator_t it_first, basic_string_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_BASIC_STRING_ITERATOR_CONTAINER(it_first) == _BASIC_STRING_ITERATOR_CONTAINER(it_second));
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_first), it_first));
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_second), it_second));

    return _BASIC_STRING_ITERATOR_COREPOS(it_first) == _BASIC_STRING_ITERATOR_COREPOS(it_second) ? true : false;
}

/**
 * Get iterator reference data.
 */
void _basic_string_iterator_get_value(basic_string_iterator_t it_iter, void* pv_value)
{
    bool_t b_result = false;

    assert(pv_value != NULL);
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!_basic_string_iterator_equal(it_iter, basic_string_end(_BASIC_STRING_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(_BASIC_STRING_ITERATOR_CONTAINER(it_iter)),
                _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        *(char**)pv_value = (char*)string_c_str((string_t*)_BASIC_STRING_ITERATOR_COREPOS(it_iter));
    } else {
        b_result = _GET_BASIC_STRING_TYPE_SIZE(_BASIC_STRING_ITERATOR_CONTAINER(it_iter));
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(_BASIC_STRING_ITERATOR_CONTAINER(it_iter))(
            pv_value, _BASIC_STRING_ITERATOR_COREPOS(it_iter), &b_result);
        assert(b_result);
    }
}

/**
 * Set iterator reference data.
 */
void _basic_string_iterator_set_value(basic_string_iterator_t it_iter, const void* cpv_value)
{
    bool_t b_result = false;

    assert(cpv_value != NULL);
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!_basic_string_iterator_equal(it_iter, basic_string_end(_BASIC_STRING_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(_BASIC_STRING_ITERATOR_CONTAINER(it_iter)),
                _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        string_assign_cstr((string_t*)_BASIC_STRING_ITERATOR_COREPOS(it_iter), (char*)cpv_value);
    } else {
        b_result = _GET_BASIC_STRING_TYPE_SIZE(_BASIC_STRING_ITERATOR_CONTAINER(it_iter));
        _GET_BASIC_STRING_TYPE_COPY_FUNCTION(_BASIC_STRING_ITERATOR_CONTAINER(it_iter))(
            _BASIC_STRING_ITERATOR_COREPOS(it_iter), cpv_value, &b_result);
        assert(b_result);
    }
}

/**
 * Get the pointer that point to the iterator reference data.
 */
const void* _basic_string_iterator_get_pointer(basic_string_iterator_t it_iter)
{
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!_basic_string_iterator_equal(it_iter, basic_string_end(_BASIC_STRING_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_BASIC_STRING_TYPE_BASENAME(_BASIC_STRING_ITERATOR_CONTAINER(it_iter)),
                _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return string_c_str((string_t*)_BASIC_STRING_ITERATOR_COREPOS(it_iter));
    } else {
        return _BASIC_STRING_ITERATOR_COREPOS(it_iter);
    }
}

/**
 * Get the pointer that point to the iterator reference data, but ignore char*.
 */
const void* _basic_string_iterator_get_pointer_ignore_cstr(basic_string_iterator_t it_iter)
{
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!_basic_string_iterator_equal(it_iter, basic_string_end(_BASIC_STRING_ITERATOR_CONTAINER(it_iter))));

    return _BASIC_STRING_ITERATOR_COREPOS(it_iter);
}

/**
 * Get the iterator that reference next data.
 */
basic_string_iterator_t _basic_string_iterator_next(basic_string_iterator_t it_iter)
{
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));
    _BASIC_STRING_ITERATOR_COREPOS(it_iter) += _GET_BASIC_STRING_TYPE_SIZE(_BASIC_STRING_ITERATOR_CONTAINER(it_iter));
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Get the iterator that reference previous data.
 */
basic_string_iterator_t _basic_string_iterator_prev(basic_string_iterator_t it_iter)
{
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));
    _BASIC_STRING_ITERATOR_COREPOS(it_iter) -= _GET_BASIC_STRING_TYPE_SIZE(_BASIC_STRING_ITERATOR_CONTAINER(it_iter));
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Access iterator reference data randomly with subscript.
 */
void* _basic_string_iterator_at(basic_string_iterator_t it_iter, int n_index)
{
    return (void*)_basic_string_iterator_get_pointer(_basic_string_iterator_next_n(it_iter, n_index));
}

/**
 * Get the iterator that reference next n data.
 */
basic_string_iterator_t _basic_string_iterator_next_n(basic_string_iterator_t it_iter, int n_step)
{
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));
    _BASIC_STRING_ITERATOR_COREPOS(it_iter) += _GET_BASIC_STRING_TYPE_SIZE(_BASIC_STRING_ITERATOR_CONTAINER(it_iter)) * n_step;
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Get the iterator that reference previous n data.
 */
basic_string_iterator_t _basic_string_iterator_prev_n(basic_string_iterator_t it_iter, int n_step)
{
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));
    _BASIC_STRING_ITERATOR_COREPOS(it_iter) -= _GET_BASIC_STRING_TYPE_SIZE(_BASIC_STRING_ITERATOR_CONTAINER(it_iter)) * n_step;
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Calculate the distance between two iterators.
 */
int _basic_string_iterator_minus(basic_string_iterator_t it_first, basic_string_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_BASIC_STRING_ITERATOR_CONTAINER(it_first) == _BASIC_STRING_ITERATOR_CONTAINER(it_second));
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_first), it_first));
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_second), it_second));

    return (_BASIC_STRING_ITERATOR_COREPOS(it_first) - _BASIC_STRING_ITERATOR_COREPOS(it_second)) /
           (int)_GET_BASIC_STRING_TYPE_SIZE(_BASIC_STRING_ITERATOR_CONTAINER(it_first));
}

/**
 * Testing of the first iterator is less than the second iterator.
 */
bool_t _basic_string_iterator_less(basic_string_iterator_t it_first, basic_string_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_BASIC_STRING_ITERATOR_CONTAINER(it_first) == _BASIC_STRING_ITERATOR_CONTAINER(it_second));
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_first), it_first));
    assert(_basic_string_iterator_belong_to_basic_string(_BASIC_STRING_ITERATOR_CONTAINER(it_second), it_second));

    return _BASIC_STRING_ITERATOR_COREPOS(it_first) < _BASIC_STRING_ITERATOR_COREPOS(it_second) ? true : false;
}

/**
 * Testing of the first iterator is located in front of the second iterator.
 */
bool_t _basic_string_iterator_before(basic_string_iterator_t it_first, basic_string_iterator_t it_second)
{
    return _basic_string_iterator_less(it_first, it_second);
}

/** local function implementation section **/

/** eof **/

