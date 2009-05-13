/*
 *  The implement of iterator module.
 *  Copyright (C)  2008 2009  Wangbo
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
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cstl_alloc.h"
#include "cstl_types.h"

#include "cstl_iterator.h"
#include "cstl_iterator_private.h"
#include "cstl_vector_iterator.h"
#include "cstl_list_iterator.h"
#include "cstl_deque_iterator.h"
#include "cstl_slist_iterator.h"
#include "cstl_set_iterator.h"
#include "cstl_multiset_iterator.h"
#include "cstl_map_iterator.h"
#include "cstl_multimap_iterator.h"
#include "cstl_hash_set_iterator.h"
#include "cstl_hash_multiset_iterator.h"
#include "cstl_hash_map_iterator.h"
#include "cstl_hash_multimap_iterator.h"
#include "cstl_basic_string_iterator.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* private iterator function */
bool_t _iterator_same_type(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    if(t_iterfirst._t_containertype == t_itersecond._t_containertype &&
       t_iterfirst._t_iteratortype == t_itersecond._t_iteratortype)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _iterator_before(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));

    switch(t_iterfirst._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _SET_CONTAINER:
        return _set_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_before(t_iterfirst, t_itersecond);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_before(t_iterfirst, t_itersecond);
        break;
    default:
        return false;
        break;
    }
}

bool_t _iterator_limit_type(iterator_t t_iter, iteratortype_t t_limittype)
{
    /* check iterator type */
    switch(t_limittype)
    {
    case _INPUT_ITERATOR:
        if(t_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
           t_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
           t_iter._t_iteratortype == _FORWARD_ITERATOR ||
           t_iter._t_iteratortype == _INPUT_ITERATOR)
        {
            return true;
        }
        break;
    case _OUTPUT_ITERATOR:
        if(t_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
           t_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
           t_iter._t_iteratortype == _FORWARD_ITERATOR ||
           t_iter._t_iteratortype == _OUTPUT_ITERATOR)
        {
            return true;
        }
        break;
    case _FORWARD_ITERATOR:
        if(t_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
           t_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
           t_iter._t_iteratortype == _FORWARD_ITERATOR)
        {
            return true;
        }
        break;
    case _BIDIRECTIONAL_ITERATOR:
        if(t_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
           t_iter._t_iteratortype == _BIDIRECTIONAL_ITERATOR)
        {
            return true;
        }
        break;
    case _RANDOM_ACCESS_ITERATOR:
        if(t_iter._t_iteratortype == _RANDOM_ACCESS_ITERATOR)
        {
            return true;
        }
        break;
    default:
        return false;
        break;
    }

    return false;
}

/* the handler of iterator */
void iterator_get_value(iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_iterator_limit_type(t_iter, _INPUT_ITERATOR));

    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        _vector_iterator_get_value(t_iter, pv_value);
        break;
    case _LIST_CONTAINER:
        _list_iterator_get_value(t_iter, pv_value);
        break;
    case _DEQUE_CONTAINER:
        _deque_iterator_get_value(t_iter, pv_value);
        break;
    case _SLIST_CONTAINER:
        _slist_iterator_get_value(t_iter, pv_value);
        break;
    case _SET_CONTAINER:
        _set_iterator_get_value(t_iter, pv_value);
        break;
    case _MULTISET_CONTAINER:
        _multiset_iterator_get_value(t_iter, pv_value);
        break;
    case _MAP_CONTAINER:
        _map_iterator_get_value(t_iter, pv_value);
        break;
    case _MULTIMAP_CONTAINER:
        _multimap_iterator_get_value(t_iter, pv_value);
        break;
    case _HASH_SET_CONTAINER:
        _hash_set_iterator_get_value(t_iter, pv_value);
        break;
    case _HASH_MULTISET_CONTAINER:
        _hash_multiset_iterator_get_value(t_iter, pv_value);
        break;
    case _HASH_MAP_CONTAINER:
        _hash_map_iterator_get_value(t_iter, pv_value);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        _hash_multimap_iterator_get_value(t_iter, pv_value);
        break;
    case _BASIC_STRING_CONTAINER:
        _basic_string_iterator_get_value(t_iter, pv_value);
        break;
    default:
        assert(false);
        break;
    }
}

void iterator_set_value(iterator_t t_iter, const void* cpv_value)
{
    assert(cpv_value != NULL);
    assert(_iterator_limit_type(t_iter, _OUTPUT_ITERATOR));
 
    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        _vector_iterator_set_value(t_iter, cpv_value);
        break;
    case _LIST_CONTAINER:
        _list_iterator_set_value(t_iter, cpv_value);
        break;
    case _DEQUE_CONTAINER:
        _deque_iterator_set_value(t_iter, cpv_value);
        break;
    case _SLIST_CONTAINER:
        _slist_iterator_set_value(t_iter, cpv_value);
        break;
    case _BASIC_STRING_CONTAINER:
        _basic_string_iterator_set_value(t_iter, cpv_value);
        break;
    default:
        assert(false);
        break;
    }
}

const void* iterator_get_pointer(iterator_t t_iter)
{
    assert(_iterator_limit_type(t_iter, _INPUT_ITERATOR));

    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_get_pointer(t_iter);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_get_pointer(t_iter);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_get_pointer(t_iter);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_get_pointer(t_iter);
        break;
    case _SET_CONTAINER:
        return _set_iterator_get_pointer(t_iter);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_get_pointer(t_iter);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_get_pointer(t_iter);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_get_pointer(t_iter);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_get_pointer(t_iter);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_get_pointer(t_iter);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_get_pointer(t_iter);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_get_pointer(t_iter);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_get_pointer(t_iter);
        break;
    default:
        assert(false);
        return NULL;
        break;
    }
}

iterator_t iterator_next(iterator_t t_iter)
{
    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_next(t_iter);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_next(t_iter);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_next(t_iter);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_next(t_iter);
        break;
    case _SET_CONTAINER:
        return _set_iterator_next(t_iter);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_next(t_iter);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_next(t_iter);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_next(t_iter);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_next(t_iter);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_next(t_iter);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_next(t_iter);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_next(t_iter);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_next(t_iter);
        break;
    default:
        assert(false);
        return t_iter;
        break;
    }
}

iterator_t iterator_prev(iterator_t t_iter)
{
    assert(_iterator_limit_type(t_iter, _BIDIRECTIONAL_ITERATOR));

    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_prev(t_iter);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_prev(t_iter);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_prev(t_iter);
        break;
    case _SET_CONTAINER:
        return _set_iterator_prev(t_iter);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_prev(t_iter);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_prev(t_iter);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_prev(t_iter);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_prev(t_iter);
        break;
    default:
        assert(false);
        return t_iter;
        break;
    }
}

iterator_t iterator_next_n(iterator_t t_iter, int n_step)
{
    assert(_iterator_limit_type(t_iter, _RANDOM_ACCESS_ITERATOR));

    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_next_n(t_iter, n_step);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_next_n(t_iter, n_step);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_next_n(t_iter, n_step);
        break;
    default:
        assert(false);
        return t_iter;
        break;
    }
}

iterator_t iterator_prev_n(iterator_t t_iter, int n_step)
{
    assert(_iterator_limit_type(t_iter, _RANDOM_ACCESS_ITERATOR));

    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_prev_n(t_iter, n_step);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_prev_n(t_iter, n_step);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_prev_n(t_iter, n_step);
        break;
    default:
        assert(false);
        return t_iter;
        break;
    }
}

bool_t iterator_equal(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    assert(_iterator_limit_type(t_iterfirst, _INPUT_ITERATOR));

    switch(t_iterfirst._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _SET_CONTAINER:
        return _set_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_equal(t_iterfirst, t_itersecond);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_equal(t_iterfirst, t_itersecond);
        break;
    default:
        assert(false);
        return false;
        break;
    }
}

bool_t iterator_not_equal(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    return !iterator_equal(t_iterfirst, t_itersecond);
}

bool_t iterator_less(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    assert(_iterator_limit_type(t_iterfirst, _RANDOM_ACCESS_ITERATOR));

    switch(t_iterfirst._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_less(t_iterfirst, t_itersecond);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_less(t_iterfirst, t_itersecond);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_less(t_iterfirst, t_itersecond);
        break;
    default:
        assert(false);
        return false;
        break;
    }
}

bool_t iterator_less_equal(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    if(iterator_less(t_iterfirst, t_itersecond) ||
       iterator_equal(t_iterfirst, t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t iterator_great(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    return iterator_less(t_itersecond, t_iterfirst);
}

bool_t iterator_great_equal(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    if(iterator_great(t_iterfirst, t_itersecond) ||
       iterator_equal(t_iterfirst, t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void* iterator_at(iterator_t t_iter, int n_index)
{
    assert(_iterator_limit_type(t_iter, _RANDOM_ACCESS_ITERATOR));

    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_at(t_iter, n_index);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_at(t_iter, n_index);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_at(t_iter, n_index);
        break;
    default:
        assert(false);
        return NULL;
        break;
    }
}


int iterator_minus(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    assert(_iterator_limit_type(t_iterfirst, _RANDOM_ACCESS_ITERATOR));

    switch(t_iterfirst._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_minus(t_iterfirst, t_itersecond);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_minus(t_iterfirst, t_itersecond);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_minus(t_iterfirst, t_itersecond);
        break;
    default:
        assert(false);
        return 0;
        break;
    }
}


/* the auxiliary function of iterator */
iterator_t iterator_advance(iterator_t t_iter, int n_step)
{
    int i = 0;

    if(n_step > 0 ||
       (t_iter._t_iteratortype != _RANDOM_ACCESS_ITERATOR &&
        t_iter._t_iteratortype != _BIDIRECTIONAL_ITERATOR))
    {
        for(i = 0; i < abs(n_step); ++i)
        {
            t_iter = iterator_next(t_iter);
        }
    }
    else
    {
        for(i = 0; i < abs(n_step); ++i)
        {
            t_iter = iterator_prev(t_iter);
        }
    }

    return t_iter;
}

int iterator_distance(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));

    switch(t_iterfirst._t_containertype)
    {
    case _VECTOR_CONTAINER:
    case _DEQUE_CONTAINER:
    case _BASIC_STRING_CONTAINER:
        return iterator_minus(t_itersecond, t_iterfirst);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _SET_CONTAINER:
        return _set_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_distance(t_iterfirst, t_itersecond);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_distance(t_iterfirst, t_itersecond);
        break;
    default:
        assert(false);
        return 0;
        break;
    }
}

/** local function implementation section **/

/** eof **/

