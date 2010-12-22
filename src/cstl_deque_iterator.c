/*
 *  The implement of deque iterator.
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

#include <cstl/cstl_deque_iterator.h>
#include <cstl/cstl_deque_private.h>
#include <cstl/cstl_deque.h>

#include <cstl/cstring.h>

#include "cstl_deque_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create new deque iterator.
 */
deque_iterator_t _create_deque_iterator(void)
{
    deque_iterator_t it_iter;

    _GET_DEQUE_MAP_POINTER(it_iter) = NULL;
    _GET_DEQUE_FIRST_POS(it_iter) = NULL;
    _GET_DEQUE_AFTERLAST_POS(it_iter) = NULL;
    _GET_DEQUE_COREPOS(it_iter) = NULL;
    it_iter._pt_container = NULL;
    it_iter._t_containertype = _DEQUE_CONTAINER;
    it_iter._t_iteratortype = _RANDOM_ACCESS_ITERATOR;

    return it_iter;
}

/**
 * Compare two iterators for equality.
 */
bool_t _deque_iterator_equal(deque_iterator_t it_first, deque_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_GET_DEQUE_CONTAINER(it_first) == _GET_DEQUE_CONTAINER(it_second));
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(it_first), it_first));
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(it_second), it_second));
    
    if(_GET_DEQUE_MAP_POINTER(it_first) == _GET_DEQUE_MAP_POINTER(it_second) &&
       _GET_DEQUE_FIRST_POS(it_first) == _GET_DEQUE_FIRST_POS(it_second) &&
       _GET_DEQUE_AFTERLAST_POS(it_first) == _GET_DEQUE_AFTERLAST_POS(it_second) &&
       _GET_DEQUE_COREPOS(it_first) == _GET_DEQUE_COREPOS(it_second))
    {
        return true;
    }
    else
    {
        /* 
         * if the start corepos equal to the after last node and the finish 
         * corepos equal to the first position, the two iterator equal to.
         */
        if(_GET_DEQUE_MAP_POINTER(it_first) < _GET_DEQUE_MAP_POINTER(it_second))
        {
            if(_GET_DEQUE_MAP_POINTER(it_first) + 1 == _GET_DEQUE_MAP_POINTER(it_second) &&
               _GET_DEQUE_COREPOS(it_first) == _GET_DEQUE_AFTERLAST_POS(it_first) &&
               _GET_DEQUE_COREPOS(it_second) == _GET_DEQUE_FIRST_POS(it_second))
            {
                /* the it_first must be deque_begin. */
                assert(_GET_DEQUE_MAP_POINTER(it_first) == _GET_DEQUE_MAP_POINTER(_GET_DEQUE_CONTAINER(it_first)->_t_start));
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(_GET_DEQUE_MAP_POINTER(it_second) + 1 == _GET_DEQUE_MAP_POINTER(it_first) &&
               _GET_DEQUE_COREPOS(it_second) == _GET_DEQUE_AFTERLAST_POS(it_second) &&
               _GET_DEQUE_COREPOS(it_first) == _GET_DEQUE_FIRST_POS(it_first))
            {
                /* the it_second must be deque_begin. */
                assert(_GET_DEQUE_MAP_POINTER(it_second) == _GET_DEQUE_MAP_POINTER(_GET_DEQUE_CONTAINER(it_second)->_t_start));
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

/**
 * Testing of the first iterator is less than the second iterator.
 */
bool_t _deque_iterator_less(deque_iterator_t it_first, deque_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_GET_DEQUE_CONTAINER(it_first) == _GET_DEQUE_CONTAINER(it_second));
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(it_first), it_first));
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(it_second), it_second));

    if(_GET_DEQUE_MAP_POINTER(it_first) < _GET_DEQUE_MAP_POINTER(it_second))
    {
        /* it_first and it_second are deque_begin(); */
        if(_GET_DEQUE_COREPOS(it_first) == _GET_DEQUE_AFTERLAST_POS(it_first) &&
           _GET_DEQUE_COREPOS(it_second) == _GET_DEQUE_FIRST_POS(it_second))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else if(_GET_DEQUE_MAP_POINTER(it_first) == _GET_DEQUE_MAP_POINTER(it_second))
    {
        return _GET_DEQUE_COREPOS(it_first) < _GET_DEQUE_COREPOS(it_second) ? true : false;
    }
    else
    {
        return false;
    }
}

/**
 * Testing of the first iterator is located in front of the second iterator.
 */
bool_t _deque_iterator_before(deque_iterator_t it_first, deque_iterator_t it_second)
{
    return _deque_iterator_less(it_first, it_second);
}

/**
 * Get iterator reference data.
 */
void _deque_iterator_get_value(deque_iterator_t it_iter, void* pv_value)
{
    bool_t b_result = false;

    assert(pv_value != NULL);
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, deque_end(_GET_DEQUE_CONTAINER(it_iter))));

    /* char* */
    if(strncmp(_GET_DEQUE_TYPE_BASENAME(_GET_DEQUE_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str((string_t*)_deque_iterator_get_pointer_auxiliary(it_iter));
    }
    else
    {
        b_result = _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(it_iter));
        _GET_DEQUE_TYPE_COPY_FUNCTION(_GET_DEQUE_CONTAINER(it_iter))(
            pv_value, _deque_iterator_get_pointer_auxiliary(it_iter), &b_result);
        assert(b_result);
    }
}

/**
 * Set iterator reference data.
 */
void _deque_iterator_set_value(deque_iterator_t it_iter, const void* cpv_value)
{
    bool_t b_result = false;

    assert(cpv_value != NULL);
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, deque_end(_GET_DEQUE_CONTAINER(it_iter))));

    /* char* */
    if(strncmp(_GET_DEQUE_TYPE_BASENAME(_GET_DEQUE_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        string_assign_cstr((string_t*)_deque_iterator_get_pointer_auxiliary(it_iter), (char*)cpv_value);
    }
    else
    {
        b_result = _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(it_iter));
        _GET_DEQUE_TYPE_COPY_FUNCTION(_GET_DEQUE_CONTAINER(it_iter))(
            _deque_iterator_get_pointer_auxiliary(it_iter), cpv_value, &b_result);
        assert(b_result);
    }
}

const void* _deque_iterator_get_pointer(deque_iterator_t t_iter)
{
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, deque_end(_GET_DEQUE_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_DEQUE_TYPE_BASENAME(_GET_DEQUE_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return string_c_str((string_t*)_deque_iterator_get_pointer_auxiliary(t_iter));
    }
    else
    {
        return _deque_iterator_get_pointer_auxiliary(t_iter);
    }
}

deque_iterator_t _deque_iterator_next(deque_iterator_t t_iter)
{
    size_t t_beyondsize = 0;
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    _GET_DEQUE_COREPOS(t_iter) += _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_iter));
    /* at the node after the last node */
    if(_GET_DEQUE_COREPOS(t_iter) >= _GET_DEQUE_AFTERLAST_POS(t_iter))
    {
        t_beyondsize = _GET_DEQUE_COREPOS(t_iter) - _GET_DEQUE_AFTERLAST_POS(t_iter);
        assert(t_beyondsize == 0 ||
               t_beyondsize == _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_iter)));
        /* is the current pos is not the last pos of map */
        if(_GET_DEQUE_MAP_POINTER(t_iter) < 
           _GET_DEQUE_MAP_POINTER(_GET_DEQUE_CONTAINER(t_iter)->_t_finish))
        {
            _GET_DEQUE_MAP_POINTER(t_iter) += 1;
            _GET_DEQUE_FIRST_POS(t_iter) = *_GET_DEQUE_MAP_POINTER(t_iter);
            _GET_DEQUE_AFTERLAST_POS(t_iter) = _GET_DEQUE_FIRST_POS(t_iter) + 
                _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_iter)) * _DEQUE_ELEM_COUNT;
            _GET_DEQUE_COREPOS(t_iter) = _GET_DEQUE_FIRST_POS(t_iter) + t_beyondsize;
        }
    }

    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    return t_iter;
}

deque_iterator_t _deque_iterator_prev(deque_iterator_t t_iter)
{
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    _GET_DEQUE_COREPOS(t_iter) -= _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_iter));
    /* before the first node */
    if(_GET_DEQUE_COREPOS(t_iter) < _GET_DEQUE_FIRST_POS(t_iter))
    {
        /* is the current node is the first node */
        if(_GET_DEQUE_MAP_POINTER(t_iter) >
           _GET_DEQUE_MAP_POINTER(_GET_DEQUE_CONTAINER(t_iter)->_t_start))
        {
            _GET_DEQUE_MAP_POINTER(t_iter) -= 1;
            _GET_DEQUE_FIRST_POS(t_iter) = *_GET_DEQUE_MAP_POINTER(t_iter);
            _GET_DEQUE_AFTERLAST_POS(t_iter) = _GET_DEQUE_FIRST_POS(t_iter) +
                _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_iter)) * _DEQUE_ELEM_COUNT;
            _GET_DEQUE_COREPOS(t_iter) = _GET_DEQUE_AFTERLAST_POS(t_iter) -
                _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_iter));
        }
    }

    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    return t_iter;
}

void* _deque_iterator_at(deque_iterator_t t_iter, int n_index)
{
    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    t_iter = iterator_next_n(t_iter, n_index);

    /* char* */
    if(strncmp(_GET_DEQUE_TYPE_BASENAME(_GET_DEQUE_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str((string_t*)_GET_DEQUE_COREPOS(t_iter));
    }
    else
    {
        return _GET_DEQUE_COREPOS(t_iter);
    }
}

deque_iterator_t _deque_iterator_next_n(deque_iterator_t t_iter, int n_step)
{
    int i = 0;

    if(n_step >= 0)
    {
        for(i = 0; i < n_step; ++i)
        {
            t_iter = iterator_next(t_iter);
        }
    }
    else
    {
        for(i = 0; i < -n_step; ++i)
        {
            t_iter = iterator_prev(t_iter);
        }
    }

    return t_iter;
}

deque_iterator_t _deque_iterator_prev_n(deque_iterator_t t_iter, int n_step)
{
    return iterator_next_n(t_iter, -n_step);
}

int _deque_iterator_minus(deque_iterator_t t_iterfirst, deque_iterator_t t_itersecond)
{
    size_t t_mapnodesize = 0;
    size_t t_beginsize = 0;
    size_t t_middlesize = 0;
    size_t t_endsize = 0;

    if(_iterator_before(t_iterfirst, t_itersecond))
    {
        t_mapnodesize = _GET_DEQUE_MAP_POINTER(t_itersecond) -
            _GET_DEQUE_MAP_POINTER(t_iterfirst) - 1;
        t_beginsize = (_GET_DEQUE_AFTERLAST_POS(t_iterfirst) -
            _GET_DEQUE_COREPOS(t_iterfirst)) /
            _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_iterfirst));
        t_middlesize = t_mapnodesize * _DEQUE_ELEM_COUNT;
        t_endsize = (_GET_DEQUE_COREPOS(t_itersecond) -
            _GET_DEQUE_FIRST_POS(t_itersecond)) / 
            _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_itersecond));
               
        return -(int)(t_beginsize + t_middlesize + t_endsize);
    }
    else if(iterator_equal(t_iterfirst, t_itersecond))
    {
        return 0;
    }
    else
    {
        t_mapnodesize = _GET_DEQUE_MAP_POINTER(t_iterfirst) -
            _GET_DEQUE_MAP_POINTER(t_itersecond) - 1;
        t_beginsize = (_GET_DEQUE_AFTERLAST_POS(t_itersecond) -
            _GET_DEQUE_COREPOS(t_itersecond)) /
            _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_itersecond));
        t_middlesize = t_mapnodesize * _DEQUE_ELEM_COUNT;
        t_endsize = (_GET_DEQUE_COREPOS(t_iterfirst) -
            _GET_DEQUE_FIRST_POS(t_iterfirst)) / 
            _GET_DEQUE_TYPE_SIZE(_GET_DEQUE_CONTAINER(t_iterfirst));
               
        return t_beginsize + t_middlesize + t_endsize;
    }
}

/** local function implementation section **/

/** eof **/

