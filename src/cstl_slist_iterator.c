/*
 *  The implementation of slist iterator.
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
#include <cstl/cslist.h>

#include "cstl_slist_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create slist iterator.
 */
slist_iterator_t _create_slist_iterator(void)
{
    slist_iterator_t it_iter;

    _SLIST_ITERATOR_ITERATOR_TYPE(it_iter) = _FORWARD_ITERATOR;
    _SLIST_ITERATOR_CONTAINER_TYPE(it_iter) = _SLIST_CONTAINER;
    _ITERATOR_CONTAINER(it_iter) = NULL;
    _SLIST_ITERATOR_COREPOS(it_iter) = NULL;

    return it_iter;
}

/**
 * Get data value referenced by iterator.
 */
void _slist_iterator_get_value(slist_iterator_t it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, slist_end(_SLIST_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_SLIST_TYPE_BASENAME(_SLIST_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        *(char**)pv_value = (char*)string_c_str((string_t*)((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        bool_t b_result = _GET_SLIST_TYPE_SIZE(_SLIST_ITERATOR_CONTAINER(it_iter));
        _GET_SLIST_TYPE_COPY_FUNCTION(_SLIST_ITERATOR_CONTAINER(it_iter))(
            pv_value, ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, &b_result);
        assert(b_result);
    }
}

/**
 * Set data value referenced by iterator.
 */
void _slist_iterator_set_value(slist_iterator_t it_iter, const void* cpv_value)
{
    assert(cpv_value != NULL);
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, slist_end(_SLIST_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_SLIST_TYPE_BASENAME(_SLIST_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        string_assign_cstr((string_t*)((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, (char*)cpv_value);
    } else {
        bool_t b_result = _GET_SLIST_TYPE_SIZE(_SLIST_ITERATOR_CONTAINER(it_iter));
        _GET_SLIST_TYPE_COPY_FUNCTION(_SLIST_ITERATOR_CONTAINER(it_iter))(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, cpv_value, &b_result);
        assert(b_result);
    }
}

/**
 * Test the two slist iterator are equal.
 */
bool_t _slist_iterator_equal(slist_iterator_t it_first, slist_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_SLIST_ITERATOR_CONTAINER(it_first) == _SLIST_ITERATOR_CONTAINER(it_second));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_first), it_first));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_second), it_second));

    return _SLIST_ITERATOR_COREPOS(it_first) == _SLIST_ITERATOR_COREPOS(it_second) ? true : false;
}

/**
 * Get data value pointer referenced by iterator.
 */
const void* _slist_iterator_get_pointer(slist_iterator_t it_iter)
{
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, slist_end(_SLIST_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_SLIST_TYPE_BASENAME(_SLIST_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return string_c_str((string_t*)((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        return ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data;
    }
}

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 */
const void* _slist_iterator_get_pointer_ignore_cstr(slist_iterator_t it_iter)
{
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, slist_end(_SLIST_ITERATOR_CONTAINER(it_iter))));

    return ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data;
}

/**
 * Return iterator reference next element.
 */
slist_iterator_t _slist_iterator_next(slist_iterator_t it_iter)
{
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, slist_end(_SLIST_ITERATOR_CONTAINER(it_iter))));

    _SLIST_ITERATOR_COREPOS(it_iter) = (_byte_t*)(((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pt_next);

    return it_iter;
}

/**
 * Calculate distance between two iterators.
 */
int _slist_iterator_distance(slist_iterator_t it_first, slist_iterator_t it_second)
{
    int           n_distance = 0;
    _slistnode_t* pt_node = NULL;

    assert(_iterator_same_type(it_first, it_second));
    assert(_SLIST_ITERATOR_CONTAINER(it_first) == _SLIST_ITERATOR_CONTAINER(it_second));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_first), it_first));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_second), it_second));

    if (_slist_iterator_before(it_first, it_second)) {
        for (pt_node = (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_first);
             pt_node != (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_second);
             pt_node = pt_node->_pt_next) {
            n_distance++;
        }

        return n_distance;
    } else if (_slist_iterator_before(it_second, it_first)) {
        for (pt_node = (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_second);
             pt_node != (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_first);
             pt_node = pt_node->_pt_next) {
            n_distance++;
        }

        return -n_distance;
    } else {
        return 0;
    }
}

/**
 * Test the first iterator is before the second.
 */
bool_t _slist_iterator_before(slist_iterator_t it_first, slist_iterator_t it_second)
{
    _slistnode_t* pt_node = NULL;

    assert(_iterator_same_type(it_first, it_second));
    assert(_SLIST_ITERATOR_CONTAINER(it_first) == _SLIST_ITERATOR_CONTAINER(it_second));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_first), it_first));
    assert(_slist_iterator_belong_to_slist(_SLIST_ITERATOR_CONTAINER(it_second), it_second));

    if (_SLIST_ITERATOR_COREPOS(it_first) == _SLIST_ITERATOR_COREPOS(it_second)) {
        return false;
    }

    for (pt_node = (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_first); pt_node != NULL; pt_node = pt_node->_pt_next) {
        if (pt_node == (_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_second)) {
            return true;
        }
    }

    return _SLIST_ITERATOR_COREPOS(it_second) == NULL ? true : false;
}

/** local function implementation section **/

/** eof **/

