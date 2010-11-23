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

void _vector_iterator_get_value(vector_iterator_t t_iter, void* pv_value)
{
    bool_t t_result = false;

    assert(pv_value != NULL);
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_VECTOR_TYPE_BASENAME(_GET_VECTOR_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str((string_t*)_GET_VECTOR_COREPOS(t_iter));
    }
    else
    {
        t_result = _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter));
        _GET_VECTOR_TYPE_COPY_FUNCTION(_GET_VECTOR_CONTAINER(t_iter))(
            pv_value, _GET_VECTOR_COREPOS(t_iter), &t_result);
        assert(t_result);
    }
}

void _vector_iterator_set_value(vector_iterator_t t_iter, const void* cpv_value)
{
    bool_t t_result = false;

    assert(cpv_value != NULL);
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_VECTOR_TYPE_BASENAME(_GET_VECTOR_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        string_assign_cstr((string_t*)_GET_VECTOR_COREPOS(t_iter), (char*)cpv_value);
    }
    else
    {
        t_result = _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter));
        _GET_VECTOR_TYPE_COPY_FUNCTION(_GET_VECTOR_CONTAINER(t_iter))(
            _GET_VECTOR_COREPOS(t_iter), cpv_value, &t_result);
        assert(t_result);
    }
}

const void* _vector_iterator_get_pointer(vector_iterator_t t_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, vector_end(_GET_VECTOR_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_VECTOR_TYPE_BASENAME(_GET_VECTOR_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return string_c_str((string_t*)_GET_VECTOR_COREPOS(t_iter));
    }
    else
    {
        return _GET_VECTOR_COREPOS(t_iter);
    }
}

vector_iterator_t _vector_iterator_next(vector_iterator_t t_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) += _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

vector_iterator_t _vector_iterator_prev(vector_iterator_t t_iter)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) -= _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter));
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

void* _vector_iterator_at(vector_iterator_t t_iter, int n_index)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) +=
        _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter)) * n_index;
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    /* char* */
    if(strncmp(_GET_VECTOR_TYPE_BASENAME(_GET_VECTOR_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str((string_t*)_GET_VECTOR_COREPOS(t_iter));
    }
    else
    {
        return _GET_VECTOR_COREPOS(t_iter);
    }
}

vector_iterator_t _vector_iterator_next_n(vector_iterator_t t_iter, int n_step)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) +=
        _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter)) * n_step;
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

vector_iterator_t _vector_iterator_prev_n(vector_iterator_t t_iter, int n_step)
{
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));
    _GET_VECTOR_COREPOS(t_iter) -=
        _GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iter)) * n_step;
    assert(_vector_iterator_belong_to_vector(_GET_VECTOR_CONTAINER(t_iter), t_iter));

    return t_iter;
}

int _vector_iterator_minus(vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_VECTOR_CONTAINER(t_iterfirst) == _GET_VECTOR_CONTAINER(t_itersecond));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_itersecond), t_itersecond));

    return (_GET_VECTOR_COREPOS(t_iterfirst) - _GET_VECTOR_COREPOS(t_itersecond)) / 
           (int)_GET_VECTOR_TYPE_SIZE(_GET_VECTOR_CONTAINER(t_iterfirst));
}

bool_t _vector_iterator_less(vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_VECTOR_CONTAINER(t_iterfirst) == _GET_VECTOR_CONTAINER(t_itersecond));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_vector_iterator_belong_to_vector(
        _GET_VECTOR_CONTAINER(t_itersecond), t_itersecond));

    return _GET_VECTOR_COREPOS(t_iterfirst) < _GET_VECTOR_COREPOS(t_itersecond) ?
        true : false;
}

bool_t _vector_iterator_before(
    vector_iterator_t t_iterfirst, vector_iterator_t t_itersecond)
{
    return _vector_iterator_less(t_iterfirst, t_itersecond);
}

/** local function implementation section **/

/** eof **/

