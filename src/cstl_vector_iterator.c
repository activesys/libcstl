/*
 *  The implement of vector iterator.
 *  Copyright (C)  2008,2009,2010  Wangbo
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
#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator_private.h>

#include <cstl/cstl_vector_iterator.h>
#include <cstl/cstl_vector_private.h>
#include <cstl/cstl_vector.h>

#include <cstl/cstring.h>

#include "cstl_vector_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create new vector iterator.
 */
vector_iterator_t _create_vector_iterator(void)
{
    vector_iterator_t it_iter;

    _GET_VECTOR_COREPOS(it_iter) = NULL;
    _GET_CONTAINER(it_iter) = NULL;
    _GET_VECTOR_CONTAINER_TYPE(it_iter) = _VECTOR_CONTAINER;
    _GET_VECTOR_ITERATOR_TYPE(it_iter) = _RANDOM_ACCESS_ITERATOR;

    return it_iter;
}

/**
 * Compare two iterators for equality.
 */
bool_t _vector_iterator_equal(vector_iterator_t it_first, vector_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_GET_VECTOR_CONTAINER(it_first) == _GET_VECTOR_CONTAINER(it_second));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_first), it_first));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_second), it_second));

    return _GET_VECTOR_COREPOS(it_first) == _GET_VECTOR_COREPOS(it_second) ? true : false;
}

/**
 * Get iterator reference data.
 */
void _vector_iterator_get_value(vector_iterator_t it_iter, void* pv_value)
{
    bool_t b_result = false;

    assert(pv_value != NULL);
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));
    assert(!_vector_iterator_equal(it_iter, vector_end(_GET_VECTOR_CONTAINER(it_iter))));

    /* char* */
    if(strncmp(_GET_VECTOR_TYPE_BASENAME(_GET_VECTOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str((string_t*)_GET_VECTOR_COREPOS(it_iter));
    }
    else
    {
        b_result = _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(it_iter));
        _GET_VECTOR_TYPE_COPY_FUNCTION(_GET_VECTOR_CONTAINER(it_iter))(pv_value, _GET_VECTOR_COREPOS(it_iter), &b_result);
        assert(b_result);
    }
}

/**
 * Set iterator reference data.
 */
void _vector_iterator_set_value(vector_iterator_t it_iter, const void* cpv_value)
{
    bool_t b_result = false;

    assert(cpv_value != NULL);
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));
    assert(!_vector_iterator_equal(it_iter, vector_end(_GET_VECTOR_CONTAINER(it_iter))));

    /* char* */
    if(strncmp(_GET_VECTOR_TYPE_BASENAME(_GET_VECTOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        string_assign_cstr((string_t*)_GET_VECTOR_COREPOS(it_iter), (char*)cpv_value);
    }
    else
    {
        b_result = _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(it_iter));
        _GET_VECTOR_TYPE_COPY_FUNCTION(_GET_VECTOR_CONTAINER(it_iter))(_GET_VECTOR_COREPOS(it_iter), cpv_value, &b_result);
        assert(b_result);
    }
}

/**
 * Get the pointer that point to the iterator reference data.
 */
const void* _vector_iterator_get_pointer(vector_iterator_t it_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));
    assert(!_vector_iterator_equal(it_iter, vector_end(_GET_VECTOR_CONTAINER(it_iter))));

    /* char* */
    if(strncmp(_GET_VECTOR_TYPE_BASENAME(_GET_VECTOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return string_c_str((string_t*)_GET_VECTOR_COREPOS(it_iter));
    }
    else
    {
        return _GET_VECTOR_COREPOS(it_iter);
    }
}

/**
 * Get the iterator that reference next data.
 */
vector_iterator_t _vector_iterator_next(vector_iterator_t it_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));
    _GET_VECTOR_COREPOS(it_iter) += _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(it_iter));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Get the iterator that reference previous data.
 */
vector_iterator_t _vector_iterator_prev(vector_iterator_t it_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));
    _GET_VECTOR_COREPOS(it_iter) -= _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(it_iter));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Access iterator reference data randomly with subscript.
 */
void* _vector_iterator_at(vector_iterator_t it_iter, int n_index)
{
    it_iter = _vector_iterator_next_n(it_iter, n_index);
    return (void*)_vector_iterator_get_pointer(it_iter);
}

/**
 * Get the iterator that reference next n data.
 */
vector_iterator_t _vector_iterator_next_n(vector_iterator_t it_iter, int n_step)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));
    _GET_VECTOR_COREPOS(it_iter) += _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(it_iter)) * n_step;
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Get the iterator that reference previous n data.
 */
vector_iterator_t _vector_iterator_prev_n(vector_iterator_t it_iter, int n_step)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));
    _GET_VECTOR_COREPOS(it_iter) -= _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(it_iter)) * n_step;
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Calculate the distance between two iterators.
 */
int _vector_iterator_minus(vector_iterator_t it_first, vector_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_GET_VECTOR_CONTAINER(it_first) == _GET_VECTOR_CONTAINER(it_second));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_first), it_first));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_second), it_second));

    return (_GET_VECTOR_COREPOS(it_first) - _GET_VECTOR_COREPOS(it_second)) / 
           (int)_GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(it_first));
}

/**
 * Testing of the first iterator is less than the second iterator.
 */
bool_t _vector_iterator_less(vector_iterator_t it_first, vector_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_GET_VECTOR_CONTAINER(it_first) == _GET_VECTOR_CONTAINER(it_second));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_first), it_first));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(it_second), it_second));

    return _GET_VECTOR_COREPOS(it_first) < _GET_VECTOR_COREPOS(it_second) ? true : false;
}

/**
 * Testing of the first iterator is located in front of the second iterator.
 */
bool_t _vector_iterator_before(vector_iterator_t it_first, vector_iterator_t it_second)
{
    return _vector_iterator_less(it_first, it_second);
}

/** local function implementation section **/

/** eof **/

