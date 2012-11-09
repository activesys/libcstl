/*
 *  The implement of list iterator.
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
#include <cstl/clist.h>

#include "cstl_list_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create list iterator.
 */
list_iterator_t _create_list_iterator(void)
{
    list_iterator_t it_iter;

    _LIST_ITERATOR_COREPOS(it_iter) = NULL;
    _ITERATOR_CONTAINER(it_iter) = NULL;
    _LIST_ITERATOR_CONTAINER_TYPE(it_iter) = _LIST_CONTAINER;
    _LIST_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Get data value referenced by iterator.
 */
void _list_iterator_get_value(list_iterator_t it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, list_end(_LIST_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_LIST_TYPE_BASENAME(_LIST_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        *(char**)pv_value = (char*)string_c_str((string_t*)((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        bool_t b_result = _GET_LIST_TYPE_SIZE(_LIST_ITERATOR_CONTAINER(it_iter));
        _GET_LIST_TYPE_COPY_FUNCTION(_LIST_ITERATOR_CONTAINER(it_iter))(
            pv_value, ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pby_data, &b_result);
        assert(b_result);
    }
}

/**
 * Set data value referenced by iterator.
 */
void _list_iterator_set_value(list_iterator_t it_iter, const void* cpv_value)
{
    assert(cpv_value != NULL);
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, list_end(_LIST_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_LIST_TYPE_BASENAME(_LIST_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        string_assign_cstr((string_t*)((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pby_data, (char*)cpv_value);
    } else {
        bool_t b_result = _GET_LIST_TYPE_SIZE(_LIST_ITERATOR_CONTAINER(it_iter));
        _GET_LIST_TYPE_COPY_FUNCTION(_LIST_ITERATOR_CONTAINER(it_iter))(
            ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pby_data, cpv_value, &b_result);
        assert(b_result);
    }
}

/**
 * Get data value pointer referenced by iterator.
 */
const void* _list_iterator_get_pointer(list_iterator_t it_iter)
{
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, list_end(_LIST_ITERATOR_CONTAINER(it_iter))));

    /* char* */
    if (strncmp(_GET_LIST_TYPE_BASENAME(_LIST_ITERATOR_CONTAINER(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return string_c_str((string_t*)((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        return ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pby_data;
    }
}

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 */
const void* _list_iterator_get_pointer_ignore_cstr(list_iterator_t it_iter)
{
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, list_end(_LIST_ITERATOR_CONTAINER(it_iter))));

    return ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pby_data;
}

/**
 * Return iterator reference next element.
 */
list_iterator_t _list_iterator_next(list_iterator_t it_iter)
{
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, list_end(_LIST_ITERATOR_CONTAINER(it_iter))));

    _LIST_ITERATOR_COREPOS(it_iter) = (_byte_t*)(((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pt_next);

    return it_iter;
}

/**
 * Return iterator reference previous element.
 */
list_iterator_t _list_iterator_prev(list_iterator_t it_iter)
{
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, list_begin(_LIST_ITERATOR_CONTAINER(it_iter))));

    _LIST_ITERATOR_COREPOS(it_iter) = (_byte_t*)(((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pt_prev);

    return it_iter;
}

/**
 * Test the two list iterator are equal.
 */
bool_t _list_iterator_equal(list_iterator_t it_first, list_iterator_t it_second)
{
    assert(_iterator_same_type(it_first, it_second));
    assert(_LIST_ITERATOR_CONTAINER(it_first) == _LIST_ITERATOR_CONTAINER(it_second));
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_first), it_first));
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_second), it_second));

    return _LIST_ITERATOR_COREPOS(it_first) == _LIST_ITERATOR_COREPOS(it_second) ? true : false;
}

/**
 * Calculate distance between two iterators.
 */
int _list_iterator_distance(list_iterator_t it_first, list_iterator_t it_second)
{
    _listnode_t* pt_node = NULL;    /* the iterate pointer */
    int          n_distance = 0;    /* the distance of two iterator */

    assert(_iterator_same_type(it_first, it_second));
    assert(_LIST_ITERATOR_CONTAINER(it_first) == _LIST_ITERATOR_CONTAINER(it_second));
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_first), it_first));
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_second), it_second));

    /* if the end > begin then distance is greater zero */
    if (_list_iterator_before(it_first, it_second)) {
        for (pt_node = (_listnode_t*)_LIST_ITERATOR_COREPOS(it_first);
             pt_node != (_listnode_t*)_LIST_ITERATOR_COREPOS(it_second);
             pt_node = pt_node->_pt_next) {
            n_distance++;
        }
        return n_distance;
    } else if (_list_iterator_before(it_second, it_first)) {
        for (pt_node = (_listnode_t*)_LIST_ITERATOR_COREPOS(it_second);
             pt_node != (_listnode_t*)_LIST_ITERATOR_COREPOS(it_first);
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
bool_t _list_iterator_before(list_iterator_t it_first, list_iterator_t it_second)
{
    _listnode_t* pt_node = NULL; /* current list node pointer */

    assert(_iterator_same_type(it_first, it_second));
    assert(_LIST_ITERATOR_CONTAINER(it_first) == _LIST_ITERATOR_CONTAINER(it_second));
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_first), it_first));
    assert(_list_iterator_belong_to_list(_LIST_ITERATOR_CONTAINER(it_second), it_second));

    /* if the first node equal to second node is false */
    if (_LIST_ITERATOR_COREPOS(it_first) == _LIST_ITERATOR_COREPOS(it_second)) {
        return false;
    }

    /* loop from first iterator */
    for (pt_node = (_listnode_t*)_LIST_ITERATOR_COREPOS(it_first);
         pt_node != _LIST_ITERATOR_CONTAINER(it_first)->_pt_node;
         pt_node = pt_node->_pt_next) {
        /* if meet the second iterator then the first before second */
        if (pt_node == (_listnode_t*)_LIST_ITERATOR_COREPOS(it_second)) {
            return true;
        }
    }

    /* if second iterator is end the return true */
    return (_listnode_t*)_LIST_ITERATOR_COREPOS(it_second) == _LIST_ITERATOR_CONTAINER(it_second)->_pt_node ? true : false;
}

/** local function implementation section **/

/** eof **/

