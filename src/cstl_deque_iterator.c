/*
 *  The implement of deque iterator.
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
#include <cstl/cdeque.h>

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

    _DEQUE_ITERATOR_MAP_POINTER(it_iter) = NULL;
    _DEQUE_ITERATOR_FIRST_POS(it_iter) = NULL;
    _DEQUE_ITERATOR_AFTERLAST_POS(it_iter) = NULL;
    _DEQUE_ITERATOR_COREPOS(it_iter) = NULL;
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
    assert(_DEQUE_ITERATOR_CONTAINER(it_first) == _DEQUE_ITERATOR_CONTAINER(it_second));
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_first), it_first));
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_second), it_second));
    
    if (_DEQUE_ITERATOR_MAP_POINTER(it_first) == _DEQUE_ITERATOR_MAP_POINTER(it_second) &&
        _DEQUE_ITERATOR_FIRST_POS(it_first) == _DEQUE_ITERATOR_FIRST_POS(it_second) &&
        _DEQUE_ITERATOR_AFTERLAST_POS(it_first) == _DEQUE_ITERATOR_AFTERLAST_POS(it_second) &&
        _DEQUE_ITERATOR_COREPOS(it_first) == _DEQUE_ITERATOR_COREPOS(it_second)) {
        return true;
    } else {
        /* 
         * if the start corepos equal to the after last node and the finish 
         * corepos equal to the first position, the two iterator equal to.
         */
        if (_DEQUE_ITERATOR_MAP_POINTER(it_first) < _DEQUE_ITERATOR_MAP_POINTER(it_second)) {
            if (_DEQUE_ITERATOR_MAP_POINTER(it_first) + 1 == _DEQUE_ITERATOR_MAP_POINTER(it_second) &&
                _DEQUE_ITERATOR_COREPOS(it_first) == _DEQUE_ITERATOR_AFTERLAST_POS(it_first) &&
                _DEQUE_ITERATOR_COREPOS(it_second) == _DEQUE_ITERATOR_FIRST_POS(it_second)) {
                /* the it_first must be deque_begin. */
                assert(_DEQUE_ITERATOR_MAP_POINTER(it_first) == _DEQUE_ITERATOR_MAP_POINTER(_DEQUE_ITERATOR_CONTAINER(it_first)->_t_start));
                return true;
            } else {
                return false;
            }
        } else {
            if (_DEQUE_ITERATOR_MAP_POINTER(it_second) + 1 == _DEQUE_ITERATOR_MAP_POINTER(it_first) &&
                _DEQUE_ITERATOR_COREPOS(it_second) == _DEQUE_ITERATOR_AFTERLAST_POS(it_second) &&
                _DEQUE_ITERATOR_COREPOS(it_first) == _DEQUE_ITERATOR_FIRST_POS(it_first)) {
                /* the it_second must be deque_begin. */
                assert(_DEQUE_ITERATOR_MAP_POINTER(it_second) == _DEQUE_ITERATOR_MAP_POINTER(_DEQUE_ITERATOR_CONTAINER(it_second)->_t_start));
                return true;
            } else {
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
    assert(_DEQUE_ITERATOR_CONTAINER(it_first) == _DEQUE_ITERATOR_CONTAINER(it_second));
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_first), it_first));
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_second), it_second));

    if (_DEQUE_ITERATOR_MAP_POINTER(it_first) < _DEQUE_ITERATOR_MAP_POINTER(it_second)) {
        /* it_first and it_second are deque_begin(); */
        if (_DEQUE_ITERATOR_COREPOS(it_first) == _DEQUE_ITERATOR_AFTERLAST_POS(it_first) &&
            _DEQUE_ITERATOR_COREPOS(it_second) == _DEQUE_ITERATOR_FIRST_POS(it_second) &&
            _DEQUE_ITERATOR_MAP_POINTER(it_first) + 1 == _DEQUE_ITERATOR_MAP_POINTER(it_second)) {
            return false;
        } else {
            return true;
        }
    } else if (_DEQUE_ITERATOR_MAP_POINTER(it_first) == _DEQUE_ITERATOR_MAP_POINTER(it_second)) {
        return _DEQUE_ITERATOR_COREPOS(it_first) < _DEQUE_ITERATOR_COREPOS(it_second) ? true : false;
    } else {
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
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, deque_end(_DEQUE_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_DEQUE_TYPE_BASENAME(_DEQUE_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        *(char**)pv_value = (char*)string_c_str((string_t*)_deque_iterator_get_pointer_auxiliary(it_iter));
    } else {
        b_result = _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter));
        _GET_DEQUE_TYPE_COPY_FUNCTION(_DEQUE_ITERATOR_CONTAINER(it_iter))(
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
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, deque_end(_DEQUE_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_DEQUE_TYPE_BASENAME(_DEQUE_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        string_assign_cstr((string_t*)_deque_iterator_get_pointer_auxiliary(it_iter), (char*)cpv_value);
    } else {
        b_result = _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter));
        _GET_DEQUE_TYPE_COPY_FUNCTION(_DEQUE_ITERATOR_CONTAINER(it_iter))(
            _deque_iterator_get_pointer_auxiliary(it_iter), cpv_value, &b_result);
        assert(b_result);
    }
}

/**
 * Get the pointer that point to the iterator reference data.
 */
const void* _deque_iterator_get_pointer(deque_iterator_t it_iter)
{
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, deque_end(_DEQUE_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_DEQUE_TYPE_BASENAME(_DEQUE_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return string_c_str((string_t*)_deque_iterator_get_pointer_auxiliary(it_iter));
    } else {
        return _deque_iterator_get_pointer_auxiliary(it_iter);
    }
}

/**
 * Get the pointer that point to the iterator reference data, but ignore char*
 */
const void* _deque_iterator_get_pointer_ignore_cstr(deque_iterator_t it_iter)
{
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, deque_end(_DEQUE_ITERATOR_CONTAINER(it_iter))));

    return _deque_iterator_get_pointer_auxiliary(it_iter);
}

/**
 * Get the iterator that reference next data.
 */
deque_iterator_t _deque_iterator_next(deque_iterator_t it_iter)
{
    size_t t_beyondsize = 0;
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));

    _DEQUE_ITERATOR_COREPOS(it_iter) += _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter));
    /* at the node after the last node */
    if (_DEQUE_ITERATOR_COREPOS(it_iter) >= _DEQUE_ITERATOR_AFTERLAST_POS(it_iter)) {
        t_beyondsize = _DEQUE_ITERATOR_COREPOS(it_iter) - _DEQUE_ITERATOR_AFTERLAST_POS(it_iter);
        assert(t_beyondsize == 0 || t_beyondsize == _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter)));
        /* is the current pos is not the last pos of map */
        if (_DEQUE_ITERATOR_MAP_POINTER(it_iter) < _DEQUE_ITERATOR_MAP_POINTER(_DEQUE_ITERATOR_CONTAINER(it_iter)->_t_finish)) {
            _DEQUE_ITERATOR_MAP_POINTER(it_iter) += 1;
            _DEQUE_ITERATOR_FIRST_POS(it_iter) = *_DEQUE_ITERATOR_MAP_POINTER(it_iter);
            _DEQUE_ITERATOR_AFTERLAST_POS(it_iter) = _DEQUE_ITERATOR_FIRST_POS(it_iter) + 
                _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter)) * _DEQUE_ELEM_COUNT;
            _DEQUE_ITERATOR_COREPOS(it_iter) = _DEQUE_ITERATOR_FIRST_POS(it_iter) + t_beyondsize;
        }
    }

    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Get the iterator that reference previous data.
 */
deque_iterator_t _deque_iterator_prev(deque_iterator_t it_iter)
{
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));

    _DEQUE_ITERATOR_COREPOS(it_iter) -= _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter));
    /* before the first pos */
    if (_DEQUE_ITERATOR_COREPOS(it_iter) < _DEQUE_ITERATOR_FIRST_POS(it_iter)) {
        /* is the current node is not the first node */
        if (_DEQUE_ITERATOR_MAP_POINTER(it_iter) > _DEQUE_ITERATOR_MAP_POINTER(_DEQUE_ITERATOR_CONTAINER(it_iter)->_t_start)) {
            _DEQUE_ITERATOR_MAP_POINTER(it_iter) -= 1;
            _DEQUE_ITERATOR_FIRST_POS(it_iter) = *_DEQUE_ITERATOR_MAP_POINTER(it_iter);
            _DEQUE_ITERATOR_AFTERLAST_POS(it_iter) = _DEQUE_ITERATOR_FIRST_POS(it_iter) +
                _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter)) * _DEQUE_ELEM_COUNT;
            _DEQUE_ITERATOR_COREPOS(it_iter) = _DEQUE_ITERATOR_AFTERLAST_POS(it_iter) -
                _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter));
        }
    }

    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Get the iterator that reference next n data.
 */
deque_iterator_t _deque_iterator_next_n(deque_iterator_t it_iter, int n_step)
{
    int      n_offset = 0;
    int      n_span = 0;
    deque_t* pdeq_deque = NULL;

    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));

    if (n_step == 0) {
        return it_iter;
    }

    /*
     * n_step > 0
     * |<----                       n_offset                         ---->|
     *        it_iter ->|<----              n_step                   ---->|
     * +----------------+--------+   +-----------------+     +------------+-------------+
     * |                         |   |                 | ... |                          |
     * +----------------+--------+   +-----------------+     +------------+-------------+
     * ^                             ^                       ^
     * +--------------------+     +--+        +--------------+
     *            +-------+-+--+--+--+-----+--+--+----------+
     *      map   |       |    |     | ... |     |          |
     *            +-------+----+-----+-----+-----+----------+
     *                    |<--  n_span  -->|
     *
     * ====================================================================================
     * n_step < 0
     *                  |<----        n_offset          ---->|
     *                  |<----              n_step                   ---->|<- it_iter
     * +----------------+--------+   +-----------------+     +------------+-------------+
     * |                         |   |                 | ... |                          |
     * +----------------+--------+   +-----------------+     +------------+-------------+
     * ^                             ^                       ^
     * +--------------------+     +--+        +--------------+
     *            +-------+-+--+--+--+-----+--+--+----------+
     *      map   |       |    |     | ... |     |          |
     *            +-------+----+-----+-----+-----+----------+
     *                    |<--  n_span  -->|
     */
    pdeq_deque = _DEQUE_ITERATOR_CONTAINER(it_iter);
    n_offset = n_step + (_DEQUE_ITERATOR_COREPOS(it_iter) - _DEQUE_ITERATOR_FIRST_POS(it_iter)) / _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    if (n_offset >= 0 && n_offset <= _DEQUE_ELEM_COUNT) {
        _DEQUE_ITERATOR_COREPOS(it_iter) += n_step * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    } else {
        n_span =  n_offset > 0 ?
            (n_offset + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT - 1 :
            -((-n_offset + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT);
        _DEQUE_ITERATOR_MAP_POINTER(it_iter) += n_span;
        _DEQUE_ITERATOR_FIRST_POS(it_iter) = *_DEQUE_ITERATOR_MAP_POINTER(it_iter);
        _DEQUE_ITERATOR_AFTERLAST_POS(it_iter) = _DEQUE_ITERATOR_FIRST_POS(it_iter) +
            _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter)) * _DEQUE_ELEM_COUNT;
        _DEQUE_ITERATOR_COREPOS(it_iter) = _DEQUE_ITERATOR_FIRST_POS(it_iter) +
            (n_offset - n_span * _DEQUE_ELEM_COUNT) * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    }

    /* corepos == afterlast and current chunk is't last chunk */
    if (_DEQUE_ITERATOR_COREPOS(it_iter) == _DEQUE_ITERATOR_AFTERLAST_POS(it_iter) &&
        _DEQUE_ITERATOR_MAP_POINTER(it_iter) != _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish)) {
        _DEQUE_ITERATOR_MAP_POINTER(it_iter) += 1;
        _DEQUE_ITERATOR_FIRST_POS(it_iter) = *_DEQUE_ITERATOR_MAP_POINTER(it_iter);
        _DEQUE_ITERATOR_AFTERLAST_POS(it_iter) = _DEQUE_ITERATOR_FIRST_POS(it_iter) +
            _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_iter)) * _DEQUE_ELEM_COUNT;
        _DEQUE_ITERATOR_COREPOS(it_iter) = _DEQUE_ITERATOR_FIRST_POS(it_iter);
    }

    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));

    return it_iter;
}

/**
 * Get the iterator that reference previous n data.
 */
deque_iterator_t _deque_iterator_prev_n(deque_iterator_t it_iter, int n_step)
{
    return iterator_next_n(it_iter, -n_step);
}

/**
 * Access iterator reference data randomly with subscript.
 */
void* _deque_iterator_at(deque_iterator_t it_iter, int n_index)
{
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));

    it_iter = iterator_next_n(it_iter, n_index);
    return (void*)_deque_iterator_get_pointer(it_iter);
}

/**
 * Calculate the distance between two iterators.
 */
int _deque_iterator_minus(deque_iterator_t it_first, deque_iterator_t it_second)
{
    int n_span = 0;
    int n_prefix = 0;
    int n_suffix = 0;

    assert(_DEQUE_ITERATOR_CONTAINER(it_first) == _DEQUE_ITERATOR_CONTAINER(it_second));
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_first), it_first));
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_second), it_second));

    if (_deque_iterator_equal(it_first, it_second)) {
        return 0;
    } else if (_deque_iterator_before(it_first, it_second)) {
        n_span = (_DEQUE_ITERATOR_MAP_POINTER(it_second) - _DEQUE_ITERATOR_MAP_POINTER(it_first) - 1) * _DEQUE_ELEM_COUNT;
        n_prefix = (_DEQUE_ITERATOR_AFTERLAST_POS(it_first) - _DEQUE_ITERATOR_COREPOS(it_first)) /
            _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_first));
        n_suffix = (_DEQUE_ITERATOR_COREPOS(it_second) - _DEQUE_ITERATOR_FIRST_POS(it_second)) / 
            _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_second));
               
        return -(n_prefix + n_span + n_suffix);
    } else {
        n_span = (_DEQUE_ITERATOR_MAP_POINTER(it_first) - _DEQUE_ITERATOR_MAP_POINTER(it_second) - 1) * _DEQUE_ELEM_COUNT;
        n_prefix = (_DEQUE_ITERATOR_AFTERLAST_POS(it_second) - _DEQUE_ITERATOR_COREPOS(it_second)) /
            _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_second));
        n_suffix = (_DEQUE_ITERATOR_COREPOS(it_first) - _DEQUE_ITERATOR_FIRST_POS(it_first)) / 
            _GET_DEQUE_TYPE_SIZE(_DEQUE_ITERATOR_CONTAINER(it_first));
               
        return n_prefix + n_span + n_suffix;
    }
}

/** local function implementation section **/

/** eof **/

