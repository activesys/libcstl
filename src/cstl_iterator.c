/*
 *  The implement of iterator module.
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

#include <cstl/cstl_iterator.h>
#include <cstl/cstl_iterator_private.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cdeque.h>
#include <cstl/cslist.h>
#include <cstl/cset.h>
#include <cstl/cmap.h>
#include <cstl/chash_set.h>
#include <cstl/chash_map.h>
#include <cstl/cstring.h>

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
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_prev(t_iter);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_prev(t_iter);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_prev(t_iter);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_prev(t_iter);
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

    if(n_step == 0)
    {
        return t_iter;
    }

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

    if(n_step == 0)
    {
        return t_iter;
    }

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
    assert(_iterator_limit_type(t_itersecond, _INPUT_ITERATOR));

    if(t_iterfirst._t_containertype != t_itersecond._t_containertype)
    {
        return false;
    }

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

bool_t iterator_greater(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    return iterator_less(t_itersecond, t_iterfirst);
}

bool_t iterator_greater_equal(iterator_t t_iterfirst, iterator_t t_itersecond)
{
    if(iterator_greater(t_iterfirst, t_itersecond) ||
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

bool_t _iterator_valid_range(iterator_t t_first, iterator_t t_last, iteratortype_t t_type)
{
    return _iterator_same_type(t_first, t_last) &&
           _iterator_limit_type(t_first, t_type) &&
           (iterator_equal(t_first, t_last) || _iterator_before(t_first, t_last));
}

_typestyle_t _iterator_get_typestyle(iterator_t t_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(t_iter);

    if(pt_typeinfo != NULL)
    {
        return pt_typeinfo->_t_style;
    }
    else
    {
        return _TYPE_INVALID;
    }
}

const char* _iterator_get_typebasename(iterator_t t_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(t_iter);

    if(pt_typeinfo != NULL)
    {
        return pt_typeinfo->_pt_type->_sz_typename;
    }
    else
    {
        return NULL;
    }
}

_typeinfo_t* _iterator_get_typeinfo(iterator_t t_iter)
{
    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return &((vector_t*)t_iter._pt_container)->_t_typeinfo;
        break;
    case _DEQUE_CONTAINER:
        return &((deque_t*)t_iter._pt_container)->_t_typeinfo;
        break;
    case _BASIC_STRING_CONTAINER:
        return &((basic_string_t*)t_iter._pt_container)->_vec_base._t_typeinfo;
        break;
    case _LIST_CONTAINER:
        return &((list_t*)t_iter._pt_container)->_t_typeinfo;
        break;
    case _SLIST_CONTAINER:
        return &((slist_t*)t_iter._pt_container)->_t_typeinfo;
        break;
    case _SET_CONTAINER:
        return &((set_t*)t_iter._pt_container)->_t_tree._t_typeinfo;
        break;
    case _MULTISET_CONTAINER:
        return &((multiset_t*)t_iter._pt_container)->_t_tree._t_typeinfo;
        break;
    case _MAP_CONTAINER:
        return &((map_t*)t_iter._pt_container)->_t_tree._t_typeinfo;
        break;
    case _MULTIMAP_CONTAINER:
        return &((multimap_t*)t_iter._pt_container)->_t_tree._t_typeinfo;
        break;
    case _HASH_SET_CONTAINER:
        return &((hash_set_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo;
        break;
    case _HASH_MULTISET_CONTAINER:
        return &((hash_multiset_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo;
        break;
    case _HASH_MAP_CONTAINER:
        return &((hash_map_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo;
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return &((hash_multimap_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo;
        break;
    default:
        assert(false);
        return NULL;
        break;
    }
}

const char* _iterator_get_typename(iterator_t t_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(t_iter);

    if(pt_typeinfo != NULL)
    {
        return pt_typeinfo->_sz_typename;
    }
    else
    {
        return NULL;
    }
}

binary_function_t _iterator_get_typecopy(iterator_t t_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(t_iter);

    if(pt_typeinfo != NULL)
    {
        return pt_typeinfo->_pt_type->_t_typecopy;
    }
    else
    {
        return NULL;
    }
}

size_t _iterator_get_typesize(iterator_t t_iter)
{
    _typeinfo_t* pt_typeinfo = _iterator_get_typeinfo(t_iter);

    if(pt_typeinfo != NULL)
    {
        return pt_typeinfo->_pt_type->_t_typesize;
    }
    else
    {
        return 0;
    }
}

bool_t _iterator_same_elem_type(iterator_t t_first, iterator_t t_last)
{
    return _type_is_same(_iterator_get_typename(t_first), _iterator_get_typename(t_last));
}

void* _iterator_allocate_init_elem(iterator_t t_iter)
{
    void* pv_value = NULL;

    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        pv_value = _alloc_allocate(&((vector_t*)t_iter._pt_container)->_t_allocater,
            ((vector_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
        _vector_init_elem_auxiliary((vector_t*)t_iter._pt_container, pv_value);
        break;
    case _DEQUE_CONTAINER:
        pv_value = _alloc_allocate(&((deque_t*)t_iter._pt_container)->_t_allocater,
            ((deque_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
        _deque_init_elem_auxiliary((deque_t*)t_iter._pt_container, pv_value);
        break;
    case _BASIC_STRING_CONTAINER:
        pv_value = _alloc_allocate(&((basic_string_t*)t_iter._pt_container)->_vec_base._t_allocater,
            ((basic_string_t*)t_iter._pt_container)->_vec_base._t_typeinfo._pt_type->_t_typesize, 1);
        _basic_string_init_elem_auxiliary((basic_string_t*)t_iter._pt_container, pv_value);
        break;
    case _LIST_CONTAINER:
        pv_value = _alloc_allocate(&((list_t*)t_iter._pt_container)->_t_allocater,
            ((list_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
        _list_init_elem_auxiliary((list_t*)t_iter._pt_container, pv_value);
        break;
    case _SLIST_CONTAINER:
        pv_value = _alloc_allocate(&((slist_t*)t_iter._pt_container)->_t_allocater,
            ((slist_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
        _slist_init_elem_auxiliary((slist_t*)t_iter._pt_container, pv_value);
        break;
    case _SET_CONTAINER:
        pv_value = _alloc_allocate(&((set_t*)t_iter._pt_container)->_t_tree._t_allocater,
            ((set_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
        _set_init_elem_auxiliary((set_t*)t_iter._pt_container, pv_value);
        break;
    case _MULTISET_CONTAINER:
        pv_value = _alloc_allocate(&((multiset_t*)t_iter._pt_container)->_t_tree._t_allocater,
            ((set_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
        _multiset_init_elem_auxiliary((multiset_t*)t_iter._pt_container, pv_value);
        break;
    case _MAP_CONTAINER:
        pv_value = _alloc_allocate(&((map_t*)t_iter._pt_container)->_t_tree._t_allocater,
            ((map_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
        _map_init_elem_auxiliary((map_t*)t_iter._pt_container, pv_value);
        break;
    case _MULTIMAP_CONTAINER:
        pv_value = _alloc_allocate(&((multimap_t*)t_iter._pt_container)->_t_tree._t_allocater,
            ((multimap_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
        _multimap_init_elem_auxiliary((multimap_t*)t_iter._pt_container, pv_value);
        break;
    case _HASH_SET_CONTAINER:
        pv_value = _alloc_allocate(&((hash_set_t*)t_iter._pt_container)->_t_hashtable._t_allocater,
            ((hash_set_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
        _hash_set_init_elem_auxiliary((hash_set_t*)t_iter._pt_container, pv_value);
        break;
    case _HASH_MULTISET_CONTAINER:
        pv_value = _alloc_allocate(&((hash_multiset_t*)t_iter._pt_container)->_t_hashtable._t_allocater,
            ((hash_multiset_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
        _hash_multiset_init_elem_auxiliary((hash_multiset_t*)t_iter._pt_container, pv_value);
        break;
    case _HASH_MAP_CONTAINER:
        pv_value = _alloc_allocate(&((hash_map_t*)t_iter._pt_container)->_t_hashtable._t_allocater,
            ((hash_map_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
        _hash_map_init_elem_auxiliary((hash_map_t*)t_iter._pt_container, pv_value);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        pv_value = _alloc_allocate(&((hash_multimap_t*)t_iter._pt_container)->_t_hashtable._t_allocater,
            ((hash_multimap_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
        _hash_multimap_init_elem_auxiliary((hash_multimap_t*)t_iter._pt_container, pv_value);
        break;
    default:
        assert(false);
        pv_value = NULL;
        break;
    }

    return pv_value;
}

void _iterator_deallocate_destroy_elem(iterator_t t_iter, void* pv_value)
{
    bool_t t_result = false;

    assert(pv_value != NULL);

    switch(t_iter._t_containertype)
    {
    case _VECTOR_CONTAINER:
        ((vector_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((vector_t*)t_iter._pt_container)->_t_allocater, pv_value,
            ((vector_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _DEQUE_CONTAINER:
        ((deque_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((deque_t*)t_iter._pt_container)->_t_allocater, pv_value,
            ((deque_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _BASIC_STRING_CONTAINER:
        ((basic_string_t*)t_iter._pt_container)->_vec_base._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((basic_string_t*)t_iter._pt_container)->_vec_base._t_allocater, pv_value,
            ((basic_string_t*)t_iter._pt_container)->_vec_base._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _LIST_CONTAINER:
        ((list_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((list_t*)t_iter._pt_container)->_t_allocater, pv_value,
            ((list_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _SLIST_CONTAINER:
        ((slist_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((slist_t*)t_iter._pt_container)->_t_allocater, pv_value,
            ((slist_t*)t_iter._pt_container)->_t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _SET_CONTAINER:
        ((set_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((set_t*)t_iter._pt_container)->_t_tree._t_allocater, pv_value,
            ((set_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _MULTISET_CONTAINER:
        ((multiset_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((multiset_t*)t_iter._pt_container)->_t_tree._t_allocater, pv_value,
            ((set_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _MAP_CONTAINER:
        ((map_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((map_t*)t_iter._pt_container)->_t_tree._t_allocater, pv_value,
            ((map_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _MULTIMAP_CONTAINER:
        ((multimap_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((multimap_t*)t_iter._pt_container)->_t_tree._t_allocater, pv_value,
            ((multimap_t*)t_iter._pt_container)->_t_tree._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _HASH_SET_CONTAINER:
        ((hash_set_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((hash_set_t*)t_iter._pt_container)->_t_hashtable._t_allocater, pv_value,
            ((hash_set_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _HASH_MULTISET_CONTAINER:
        ((hash_multiset_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((hash_multiset_t*)t_iter._pt_container)->_t_hashtable._t_allocater, pv_value,
            ((hash_multiset_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _HASH_MAP_CONTAINER:
        ((hash_map_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((hash_map_t*)t_iter._pt_container)->_t_hashtable._t_allocater, pv_value,
            ((hash_map_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        ((hash_multimap_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typedestroy(
            pv_value, &t_result);
        assert(t_result);
        _alloc_deallocate(&((hash_multimap_t*)t_iter._pt_container)->_t_hashtable._t_allocater, pv_value,
            ((hash_multimap_t*)t_iter._pt_container)->_t_hashtable._t_typeinfo._pt_type->_t_typesize, 1);
        break;
    default:
        assert(false);
        break;
    }
}

/** local function implementation section **/

/** eof **/

