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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

/** include section **/
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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
bool_t _iterator_same_type(
    iterator_t t_iteratorfirst, iterator_t t_iteratorsecond)
{
    if(t_iteratorfirst._t_containertype == t_iteratorsecond._t_containertype &&
       t_iteratorfirst._t_iteratortype == t_iteratorsecond._t_iteratortype)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _iterator_before(iterator_t t_iteratorfirst, iterator_t t_iteratorsecond)
{
    assert(_iterator_same_type(t_iteratorfirst, t_iteratorsecond));

    switch(t_iteratorfirst._t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _SET_CONTAINER:
        return _set_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_before(&t_iteratorfirst, &t_iteratorsecond);
        break;
    default:
        return false;
        break;
    }
}

bool_t _iterator_limit_type(
    iterator_t t_iterator, iteratortype_t t_limittype)
{
    /* check iterator type */
    switch(t_limittype)
    {
    case _INPUT_ITERATOR:
        if(t_iterator._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
           t_iterator._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
           t_iterator._t_iteratortype == _FORWARD_ITERATOR ||
           t_iterator._t_iteratortype == _INPUT_ITERATOR)
        {
            return true;
        }
        break;
    case _OUTPUT_ITERATOR:
        if(t_iterator._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
           t_iterator._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
           t_iterator._t_iteratortype == _FORWARD_ITERATOR ||
           t_iterator._t_iteratortype == _OUTPUT_ITERATOR)
        {
            return true;
        }
        break;
    case _FORWARD_ITERATOR:
        if(t_iterator._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
           t_iterator._t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
           t_iterator._t_iteratortype == _FORWARD_ITERATOR)
        {
            return true;
        }
        break;
    case _BIDIRECTIONAL_ITERATOR:
        if(t_iterator._t_iteratortype == _RANDOM_ACCESS_ITERATOR ||
           t_iterator._t_iteratortype == _BIDIRECTIONAL_ITERATOR)
        {
            return true;
        }
        break;
    case _RANDOM_ACCESS_ITERATOR:
        if(t_iterator._t_iteratortype == _RANDOM_ACCESS_ITERATOR)
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
void iterator_copy(iterator_t* pt_iterator, iterator_t t_iteratorsrc)
{
    assert(pt_iterator);

    pt_iterator->_t_iteratortype = t_iteratorsrc._t_iteratortype;
    pt_iterator->_t_containertype = t_iteratorsrc._t_containertype;
    pt_iterator->_pt_container = t_iteratorsrc._pt_container;
    /*pt_iterator->_pc_corepos = t_iteratorsrc._pc_corepos;*/
    memcpy(
        &pt_iterator->_t_pos, 
        &t_iteratorsrc._t_pos, 
        sizeof(pt_iterator->_t_pos));
}

void iterator_assign(iterator_t* pt_iterator, iterator_t t_iteratorsrc)
{
    /* if the pt_iterator is valid or not */
    assert(pt_iterator != NULL);
    /* if the container is valid */
    assert(t_iteratorsrc._pt_container != NULL);
    /* if the t_iteratorsrc is valid */
    /*assert(t_iteratorsrc._pc_corepos != NULL);*/

    if(pt_iterator->_t_iteratortype == t_iteratorsrc._t_iteratortype)
    {
        pt_iterator->_t_containertype = t_iteratorsrc._t_containertype;
        pt_iterator->_pt_container = t_iteratorsrc._pt_container;
        /*pt_iterator->_pc_corepos = t_iteratorsrc._pc_corepos;*/
        memcpy(
            &pt_iterator->_t_pos,
            &t_iteratorsrc._t_pos,
            sizeof(pt_iterator->_t_pos));
    }
}

void iterator_get_value(const iterator_t* cpt_iterator, void* pv_value)
{
    assert(cpt_iterator != NULL);
    assert(pv_value != NULL);
    assert(
        cpt_iterator->_t_iteratortype == _INPUT_ITERATOR ||
        cpt_iterator->_t_iteratortype == _FORWARD_ITERATOR ||
        cpt_iterator->_t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
        cpt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(cpt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        _vector_iterator_get_value(
            (struct _tagvector*)(cpt_iterator->_pt_container),  
            cpt_iterator, 
            pv_value);
        break;
    case _LIST_CONTAINER:
        _list_iterator_get_value(
            (struct _taglist*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _DEQUE_CONTAINER:
        _deque_iterator_get_value(
            (struct _tagdeque*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _SLIST_CONTAINER:
        _slist_iterator_get_value(
            (struct _tagslist*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _SET_CONTAINER:
        _set_iterator_get_value(
            (struct _tagset*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _MULTISET_CONTAINER:
        _multiset_iterator_get_value(
            (struct _tagmultiset*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _MAP_CONTAINER:
        _map_iterator_get_value(
            (struct _tagmap*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _MULTIMAP_CONTAINER:
        _multimap_iterator_get_value(
            (struct _tagmultimap*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _HASH_SET_CONTAINER:
        _hash_set_iterator_get_value(
            (struct _taghashset*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _HASH_MULTISET_CONTAINER:
        _hash_multiset_iterator_get_value(
            (struct _taghashmultiset*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _HASH_MAP_CONTAINER:
        _hash_map_iterator_get_value(
            (struct _taghashmap*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        _hash_multimap_iterator_get_value(
            (struct _taghashmultimap*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    case _BASIC_STRING_CONTAINER:
        _basic_string_iterator_get_value(
            (struct _tagbasicstring*)(cpt_iterator->_pt_container),
            cpt_iterator,
            pv_value);
        break;
    default:
        assert(false);
        break;
    }
}

void iterator_set_value(const iterator_t* cpt_iterator, const void* cpv_value)
{
    assert(cpt_iterator != NULL);
    assert(cpv_value != NULL);
    assert(
        cpt_iterator->_t_iteratortype == _OUTPUT_ITERATOR ||
        cpt_iterator->_t_iteratortype == _FORWARD_ITERATOR ||
        cpt_iterator->_t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
        cpt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);
 
    switch(cpt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        _vector_iterator_set_value(
            (struct _tagvector*)(cpt_iterator->_pt_container),
            cpt_iterator,
            cpv_value);
        break;
    case _LIST_CONTAINER:
        _list_iterator_set_value(
            (struct _taglist*)(cpt_iterator->_pt_container),
            cpt_iterator,
            cpv_value);
        break;
    case _DEQUE_CONTAINER:
        _deque_iterator_set_value(
            (struct _tagdeque*)(cpt_iterator->_pt_container),
            cpt_iterator,
            cpv_value);
        break;
    case _SLIST_CONTAINER:
        _slist_iterator_set_value(
            (struct _tagslist*)(cpt_iterator->_pt_container),
            cpt_iterator,
            cpv_value);
        break;
    case _BASIC_STRING_CONTAINER:
        _basic_string_iterator_set_value(
            (struct _tagbasicstring*)(cpt_iterator->_pt_container),
            cpt_iterator,
            cpv_value);
        break;
    default:
        assert(false);
        break;
    }
}

const void* iterator_get_pointer(const iterator_t* cpt_iterator)
{
    assert(cpt_iterator != NULL);
    assert(
        cpt_iterator->_t_iteratortype == _INPUT_ITERATOR ||
        cpt_iterator->_t_iteratortype == _FORWARD_ITERATOR ||
        cpt_iterator->_t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
        cpt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(cpt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_get_pointer(
            (struct _tagvector*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_get_pointer(
            (struct _taglist*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_get_pointer(
            (struct _tagdeque*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_get_pointer(
            (struct _tagslist*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _SET_CONTAINER:
        return _set_iterator_get_pointer(
            (struct _tagset*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_get_pointer(
            (struct _tagmultiset*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_get_pointer(
            (struct _tagmap*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_get_pointer(
            (struct _tagmultimap*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_get_pointer(
            (struct _taghashset*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_get_pointer(
            (struct _taghashmultiset*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_get_pointer(
            (struct _taghashmap*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_get_pointer(
            (struct _taghashmultimap*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_get_pointer(
            (struct _tagbasicstring*)(cpt_iterator->_pt_container), cpt_iterator);
        break;
    default:
        assert(false);
        return NULL;
        break;
    }
}

void iterator_next(iterator_t* pt_iterator)
{
    assert(pt_iterator != NULL);

    switch(pt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        _vector_iterator_next(
            (struct _tagvector*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _LIST_CONTAINER:
        _list_iterator_next(
            (struct _taglist*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _DEQUE_CONTAINER:
        _deque_iterator_next(
            (struct _tagdeque*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _SLIST_CONTAINER:
        _slist_iterator_next(
            (struct _tagslist*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _SET_CONTAINER:
        _set_iterator_next(
            (struct _tagset*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _MULTISET_CONTAINER:
        _multiset_iterator_next(
            (struct _tagmultiset*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _MAP_CONTAINER:
        _map_iterator_next(
            (struct _tagmap*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _MULTIMAP_CONTAINER:
        _multimap_iterator_next(
            (struct _tagmultimap*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _HASH_SET_CONTAINER:
        _hash_set_iterator_next(
            (struct _taghashset*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _HASH_MULTISET_CONTAINER:
        _hash_multiset_iterator_next(
            (struct _taghashmultiset*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _HASH_MAP_CONTAINER:
        _hash_map_iterator_next(
            (struct _taghashmap*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        _hash_multimap_iterator_next(
            (struct _taghashmultimap*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _BASIC_STRING_CONTAINER:
        _basic_string_iterator_next(
            (struct _tagbasicstring*)(pt_iterator->_pt_container), pt_iterator);
        break;
    default:
        assert(false);
        break;
    }
}

void iterator_prev(iterator_t* pt_iterator)
{
    assert(pt_iterator != NULL);
    assert(
        pt_iterator->_t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
        pt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(pt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        _vector_iterator_prev(
            (struct _tagvector*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _LIST_CONTAINER:
        _list_iterator_prev(
            (struct _taglist*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _DEQUE_CONTAINER:
        _deque_iterator_prev(
            (struct _tagdeque*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _SET_CONTAINER:
        _set_iterator_prev(
            (struct _tagset*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _MULTISET_CONTAINER:
        _multiset_iterator_prev(
            (struct _tagmultiset*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _MAP_CONTAINER:
        _map_iterator_prev(
            (struct _tagmap*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _MULTIMAP_CONTAINER:
        _multimap_iterator_prev(
            (struct _tagmultimap*)(pt_iterator->_pt_container), pt_iterator);
        break;
    case _BASIC_STRING_CONTAINER:
        _basic_string_iterator_prev(
            (struct _tagbasicstring*)(pt_iterator->_pt_container), pt_iterator);
        break;
    default:
        assert(false);
        break;
    }
}

bool_t iterator_equal(const iterator_t* cpt_iterator, iterator_t t_iterator)
{
    assert(cpt_iterator != NULL);
    assert(
        cpt_iterator->_t_iteratortype == _INPUT_ITERATOR ||
        cpt_iterator->_t_iteratortype == _FORWARD_ITERATOR ||
        cpt_iterator->_t_iteratortype == _BIDIRECTIONAL_ITERATOR ||
        cpt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(cpt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_equal(
            (struct _tagvector*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_equal(
            (struct _taglist*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_equal(
            (struct _tagdeque*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_equal(
            (struct _tagslist*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _SET_CONTAINER:
        return _set_iterator_equal(
            (struct _tagset*)(cpt_iterator->_pt_container), 
            cpt_iterator,
            t_iterator);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_equal(
            (struct _tagmultiset*)(cpt_iterator->_pt_container),
            cpt_iterator, 
            t_iterator);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_equal(
            (struct _tagmap*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_equal(
            (struct _tagmultimap*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_equal(
            (struct _taghashset*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_equal(
            (struct _taghashmultiset*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_equal(
            (struct _taghashmap*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_equal(
            (struct _taghashmultimap*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_equal(
            (struct _tagbasicstring*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    default:
        assert(false);
        return false;
        break;
    }
}

void* iterator_at(const iterator_t* cpt_iterator, unsigned int un_index)
{
    assert(cpt_iterator != NULL);
    assert(cpt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(cpt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_at(
            (struct _tagvector*)(cpt_iterator->_pt_container),
            cpt_iterator,
            un_index);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_at(
            (struct _tagdeque*)(cpt_iterator->_pt_container),
            cpt_iterator,
            un_index);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_at(
            (struct _tagbasicstring*)(cpt_iterator->_pt_container),
            cpt_iterator,
            un_index);
        break;
    default:
        assert(false);
        return NULL;
        break;
    }
}

void iterator_next_n(iterator_t* pt_iterator, int n_step)
{
    assert(pt_iterator != NULL);
    assert(pt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(pt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        _vector_iterator_next_n(
            (struct _tagvector*)(pt_iterator->_pt_container), 
            pt_iterator,
            n_step);
        break;
    case _DEQUE_CONTAINER:
        _deque_iterator_next_n(
            (struct _tagdeque*)(pt_iterator->_pt_container),
            pt_iterator,
            n_step);
        break;
    case _BASIC_STRING_CONTAINER:
        _basic_string_iterator_next_n(
            (struct _tagbasicstring*)(pt_iterator->_pt_container),
            pt_iterator,
            n_step);
        break;
    default:
        assert(false);
        break;
    }
}

void iterator_prev_n(iterator_t* pt_iterator, int n_step)
{
    assert(pt_iterator != NULL);
    assert(pt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(pt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        _vector_iterator_prev_n(
            (struct _tagvector*)(pt_iterator->_pt_container),
            pt_iterator,
            n_step);
        break;
    case _DEQUE_CONTAINER:
        _deque_iterator_prev_n(
            (struct _tagdeque*)(pt_iterator->_pt_container),
            pt_iterator,
            n_step);
        break;
    case _BASIC_STRING_CONTAINER:
        _basic_string_iterator_prev_n(
            (struct _tagbasicstring*)(pt_iterator->_pt_container),
            pt_iterator,
            n_step);
        break;
    default:
        assert(false);
        break;
    }
}

int iterator_minus(const iterator_t* cpt_iterator, iterator_t t_iterator)
{
    assert(cpt_iterator != NULL);
    assert(cpt_iterator->_t_iteratortype == t_iterator._t_iteratortype);
    assert(cpt_iterator->_t_containertype == t_iterator._t_containertype);
    assert(cpt_iterator->_pt_container == t_iterator._pt_container);
    assert(cpt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(cpt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_minus(
            (struct _tagvector*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_minus(
            (struct _tagdeque*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_minus(
            (struct _tagbasicstring*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    default:
        assert(false);
        return 0;
        break;
    }
}

bool_t iterator_less(
    const iterator_t* cpt_iterator, iterator_t t_iterator)
{
    assert(cpt_iterator != NULL);
    assert(cpt_iterator->_t_iteratortype == t_iterator._t_iteratortype);
    assert(cpt_iterator->_t_containertype == t_iterator._t_containertype);
    assert(cpt_iterator->_pt_container == t_iterator._pt_container);
    assert(cpt_iterator->_t_iteratortype == _RANDOM_ACCESS_ITERATOR);

    switch(cpt_iterator->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        return _vector_iterator_less(
            (struct _tagvector*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _DEQUE_CONTAINER:
        return _deque_iterator_less(
            (struct _tagdeque*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    case _BASIC_STRING_CONTAINER:
        return _basic_string_iterator_less(
            (struct _tagbasicstring*)(cpt_iterator->_pt_container),
            cpt_iterator,
            t_iterator);
        break;
    default:
        assert(false);
        return false;
        break;
    }
}

bool_t iterator_less_equal(
    const iterator_t* cpt_iterator, iterator_t t_iterator)
{
    if(iterator_less(cpt_iterator, t_iterator) ||
       iterator_equal(cpt_iterator, t_iterator))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* the auxiliary function of iterator */
void iterator_advance(iterator_t* pt_iterator, int n_step)
{
    int i = 0;

    if(n_step > 0 ||
       (pt_iterator->_t_iteratortype != _RANDOM_ACCESS_ITERATOR &&
        pt_iterator->_t_iteratortype != _BIDIRECTIONAL_ITERATOR))
    {
        for(i = 0; i < abs(n_step); ++i)
        {
            iterator_next(pt_iterator);
        }
    }
    else
    {
        for(i = 0; i < abs(n_step); ++i)
        {
            iterator_prev(pt_iterator);
        }
    }
}

int iterator_distance(iterator_t t_iteratorfirst, iterator_t t_iteratorsecond)
{
    assert(_iterator_same_type(t_iteratorfirst, t_iteratorsecond));

    switch(t_iteratorfirst._t_containertype)
    {
    case _VECTOR_CONTAINER:
    case _DEQUE_CONTAINER:
    case _BASIC_STRING_CONTAINER:
        return iterator_minus(&t_iteratorsecond, t_iteratorfirst);
        break;
    case _LIST_CONTAINER:
        return _list_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _SLIST_CONTAINER:
        return _slist_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _SET_CONTAINER:
        return _set_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _MULTISET_CONTAINER:
        return _multiset_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _MAP_CONTAINER:
        return _map_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _MULTIMAP_CONTAINER:
        return _multimap_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _HASH_SET_CONTAINER:
        return _hash_set_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _HASH_MULTISET_CONTAINER:
        return _hash_multiset_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _HASH_MAP_CONTAINER:
        return _hash_map_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        return _hash_multimap_iterator_distance(&t_iteratorfirst, &t_iteratorsecond);
        break;
    default:
        assert(false);
        return 0;
        break;
    }
}

/** local function implementation section **/

/** eof **/

