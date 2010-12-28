/*
 *  The implement of deque module.
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

/* deque function */
void deque_init(deque_t* pt_deque)
{
    deque_init_n(pt_deque, 0);
}

void deque_init_n(deque_t* pt_deque, size_t t_count)
{
    size_t     t_index = 0;
    size_t     t_startpos = 0;      /* the real map start pos */
    size_t     t_mapcount = 0;      /* the map count */
    size_t     t_validmapcount = 0; /* the valid count in map */
    size_t     t_endelemcount = 0;  /* the element count in the last container */
    iterator_t t_iter;
    
    assert(pt_deque != NULL);

    /* initialize the alloc */
    /*_alloc_init(&pt_deque->_t_allocater);*/
    /* initialize the map and element container */
    /* if element count > 0 */
    if(t_count > 0)
    {
        /* get the element container count */
        t_validmapcount = (t_count + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT;
        t_endelemcount = t_count % _DEQUE_ELEM_COUNT;
        /* the last container has element */
        if(t_endelemcount != 0)
        {
            t_validmapcount += 1;
        }
        /* the last container has no element */
        else
        {
            t_validmapcount += 2;
        }

        if(t_validmapcount > _DEQUE_MAP_COUNT)
        {
            size_t t_growcount = (t_validmapcount - _DEQUE_MAP_COUNT +
                _DEQUE_MAP_GROW_STEP - 1) / _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
            t_mapcount = _DEQUE_MAP_COUNT + t_growcount;
        }
        else
        {
            t_mapcount = _DEQUE_MAP_COUNT;
        }
    }
    else
    {
        t_validmapcount = 2;
        t_endelemcount = 0;
        t_mapcount = _DEQUE_MAP_COUNT;
    }
    /* allocate memory for each container */
    pt_deque->_ppc_map = _alloc_allocate(&pt_deque->_t_allocater, sizeof(char*), t_mapcount);
    pt_deque->_t_mapsize = t_mapcount;
    assert(pt_deque->_ppc_map != NULL);
    memset(pt_deque->_ppc_map, 0x00, sizeof(char*)*t_mapcount);
    t_startpos = (t_mapcount - t_validmapcount) / 2;

    for(t_index = t_startpos; t_index < t_startpos + t_validmapcount; ++t_index)
    {
        pt_deque->_ppc_map[t_index] = _alloc_allocate(&pt_deque->_t_allocater,
            _GET_DEQUE_TYPE_SIZE(pt_deque), _DEQUE_ELEM_COUNT);
        assert(pt_deque->_ppc_map[t_index] != NULL);
    }

    /* initialize the start iterator */
    _GET_CONTAINER(pt_deque->_t_start) = pt_deque;
    _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) = pt_deque->_ppc_map + t_startpos;
    _GET_DEQUE_FIRST_POS(pt_deque->_t_start) = *_GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
    _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start) = _GET_DEQUE_FIRST_POS(pt_deque->_t_start) + 
        _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pt_deque);
    _GET_DEQUE_COREPOS(pt_deque->_t_start) = _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start);
    /* initialize the finish iterator */
    _GET_CONTAINER(pt_deque->_t_finish) = pt_deque;
    _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) = 
        pt_deque->_ppc_map + t_startpos + t_validmapcount - 1;
    _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) = *_GET_DEQUE_MAP_POINTER(pt_deque->_t_finish);
    _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_finish) = _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) +
        _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pt_deque);
    _GET_DEQUE_COREPOS(pt_deque->_t_finish) = _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) + 
        t_endelemcount * _GET_DEQUE_TYPE_SIZE(pt_deque);

    for(t_iter = deque_begin(pt_deque);
        !iterator_equal(t_iter, deque_end(pt_deque));
        t_iter = iterator_next(t_iter))
    {
        _deque_init_elem_auxiliary(pt_deque, _deque_iterator_get_pointer_auxiliary(t_iter));
    }
}

void deque_init_copy(deque_t* pt_dequedest, const deque_t* cpt_dequesrc)
{
    deque_init_copy_range(
        pt_dequedest, deque_begin(cpt_dequesrc), deque_end(cpt_dequesrc));
}

void deque_init_copy_range(
    deque_t* pt_dequedest, deque_iterator_t t_begin, deque_iterator_t t_end)
{
    deque_iterator_t t_dest;   /* the iterator of dest deque for iterate */
    deque_iterator_t t_src;    /* the iterator of src range for iterate */
    bool_t           t_result = false;

    assert(_deque_same_deque_iterator_type(pt_dequedest, t_begin));
    assert(iterator_equal(t_begin, t_end) || _deque_iterator_before(t_begin, t_end));

    /* init the dest deque with the distance between t_begin and t_end */
    deque_init_n(pt_dequedest, iterator_distance(t_begin, t_end));

    /* copy the elements from src range to dest deque */
    for(t_dest = pt_dequedest->_t_start, t_src = t_begin;
        !iterator_equal(t_dest, pt_dequedest->_t_finish) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        t_result = _GET_DEQUE_TYPE_SIZE(pt_dequedest);
        _GET_DEQUE_TYPE_COPY_FUNCTION(pt_dequedest)(
            _deque_iterator_get_pointer_auxiliary(t_dest),
            _deque_iterator_get_pointer_auxiliary(t_src), &t_result);
        assert(t_result);
    }
    assert(iterator_equal(t_dest, pt_dequedest->_t_finish) && iterator_equal(t_src, t_end));
}

void deque_destroy(deque_t* pt_deque)
{
    _deque_destroy_auxiliary(pt_deque);
    free(pt_deque);
}

bool_t deque_empty(const deque_t* cpt_deque)
{
    return iterator_equal(cpt_deque->_t_start, cpt_deque->_t_finish);
}

size_t deque_size(const deque_t* cpt_deque)
{
    return iterator_distance(cpt_deque->_t_start, cpt_deque->_t_finish);
}

size_t deque_max_size(const deque_t* cpt_deque)
{
    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL && cpt_deque->_t_mapsize > 0);

    return (size_t)(-1) / _GET_DEQUE_TYPE_SIZE(cpt_deque);
}

void* deque_front(const deque_t* cpt_deque)
{
    if(deque_empty(cpt_deque))
    {
        return NULL;
    }
    else
    {
        return deque_at(cpt_deque, 0);
    }
}

void* deque_back(const deque_t* cpt_deque)
{
    if(deque_empty(cpt_deque))
    {
        return NULL;
    }
    else
    {
        return deque_at(cpt_deque, deque_size(cpt_deque) - 1);
    }
}

deque_iterator_t deque_begin(const deque_t* cpt_deque)
{
    return cpt_deque->_t_start;
}

deque_iterator_t deque_end(const deque_t* cpt_deque)
{
    return cpt_deque->_t_finish;
}

deque_reverse_iterator_t deque_rbegin(const deque_t* cpt_deque)
{
    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL && cpt_deque->_t_mapsize > 0);

    return iterator_prev(cpt_deque->_t_finish);
}

deque_reverse_iterator_t deque_rend(const deque_t* cpt_deque)
{
    deque_iterator_t t_iterator;

    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL && cpt_deque->_t_mapsize > 0);

    t_iterator = cpt_deque->_t_start;
    _GET_DEQUE_COREPOS(t_iterator) =
        _GET_DEQUE_COREPOS(cpt_deque->_t_start) - _GET_DEQUE_TYPE_SIZE(cpt_deque);

    return t_iterator;
}

void deque_assign(deque_t* pt_dequedest, const deque_t* cpt_dequesrc)
{
    deque_assign_range(pt_dequedest, deque_begin(cpt_dequesrc), deque_end(cpt_dequesrc));
}

void deque_assign_range(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end)
{
    deque_iterator_t t_dest;   /* the iterator of dest deque for iterate */
    deque_iterator_t t_src;    /* the iterator of src range for iterate */
    bool_t           t_result = false;

    assert(_deque_same_deque_iterator_type(pt_deque, t_begin));
    assert(iterator_equal(t_begin, t_end) || _deque_iterator_before(t_begin, t_end));

    /* init the dest deque with the distance between t_begin and t_end,
     * compare and element destroy function. */
    deque_resize(pt_deque, iterator_distance(t_begin, t_end));
    /* copy the elements from src range to dest deque */
    for(t_dest = pt_deque->_t_start, t_src = t_begin;
        !iterator_equal(t_dest, pt_deque->_t_finish) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
            _deque_iterator_get_pointer_auxiliary(t_dest),
            _deque_iterator_get_pointer_auxiliary(t_src), &t_result);
        assert(t_result);
    }
    assert(iterator_equal(t_dest, pt_deque->_t_finish) && iterator_equal(t_src, t_end));
}

bool_t deque_equal(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    deque_iterator_t t_first;  /* the iterator to first deque for iterate */
    deque_iterator_t t_second; /* the iterator to second deque for iterate */
    bool_t           t_less = false;
    bool_t           t_greater = false;

    assert(cpt_dequefirst != NULL && cpt_dequesecond != NULL &&
           cpt_dequefirst->_ppc_map != NULL && cpt_dequesecond->_ppc_map != NULL &&
           cpt_dequefirst->_t_mapsize > 0 && cpt_dequesecond->_t_mapsize > 0);

    if(!_deque_same_type(cpt_dequefirst, cpt_dequesecond))
    {
        return false;
    }

    if(deque_size(cpt_dequefirst) != deque_size(cpt_dequesecond))
    {
        return false;
    }

    for(t_first = deque_begin(cpt_dequefirst),
        t_second = deque_begin(cpt_dequesecond);
        !iterator_equal(t_first, deque_end(cpt_dequefirst)) &&
        !iterator_equal(t_second, deque_end(cpt_dequesecond));
        t_first = iterator_next(t_first),
        t_second = iterator_next(t_second))
    {
        t_less = t_greater = _GET_DEQUE_TYPE_SIZE(cpt_dequefirst);
        _GET_DEQUE_TYPE_LESS_FUNCTION(cpt_dequefirst)(
            _deque_iterator_get_pointer_auxiliary(t_first),
            _deque_iterator_get_pointer_auxiliary(t_second), &t_less);
        _GET_DEQUE_TYPE_LESS_FUNCTION(cpt_dequefirst)(
            _deque_iterator_get_pointer_auxiliary(t_second),
            _deque_iterator_get_pointer_auxiliary(t_first), &t_greater);
        if(t_less || t_greater)
        {
            return false;
        }
    }
    assert(iterator_equal(t_first, deque_end(cpt_dequefirst)) &&
           iterator_equal(t_second, deque_end(cpt_dequesecond)));

    return true;
}

bool_t deque_not_equal(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    return !deque_equal(cpt_dequefirst, cpt_dequesecond);
}

bool_t deque_less(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    deque_iterator_t t_first;
    deque_iterator_t t_second;
    bool_t           t_result = false;

    assert(_deque_same_type(cpt_dequefirst, cpt_dequesecond));

    for(t_first = deque_begin(cpt_dequefirst),
        t_second = deque_begin(cpt_dequesecond);
        !iterator_equal(t_first, deque_end(cpt_dequefirst)) &&
        !iterator_equal(t_second, deque_end(cpt_dequesecond));
        t_first = iterator_next(t_first),
        t_second = iterator_next(t_second))
    {
        t_result = _GET_DEQUE_TYPE_SIZE(cpt_dequefirst);
        _GET_DEQUE_TYPE_LESS_FUNCTION(cpt_dequefirst)(
            _deque_iterator_get_pointer_auxiliary(t_first),
            _deque_iterator_get_pointer_auxiliary(t_second), &t_result);
        if(t_result)
        {
            return true;
        }

        t_result = _GET_DEQUE_TYPE_SIZE(cpt_dequefirst);
        _GET_DEQUE_TYPE_LESS_FUNCTION(cpt_dequefirst)(
            _deque_iterator_get_pointer_auxiliary(t_second),
            _deque_iterator_get_pointer_auxiliary(t_first), &t_result);
        if(t_result)
        {
            return false;
        }
    }

    return deque_size(cpt_dequefirst) < deque_size(cpt_dequesecond) ? true : false;
}

bool_t deque_less_equal(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    return (deque_less(cpt_dequefirst, cpt_dequesecond) ||
           deque_equal(cpt_dequefirst, cpt_dequesecond)) ? true : false;
}

bool_t deque_greater(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    return deque_less(cpt_dequesecond, cpt_dequefirst);
}

bool_t deque_greater_equal(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    return (deque_greater(cpt_dequefirst, cpt_dequesecond) ||
           deque_equal(cpt_dequefirst, cpt_dequesecond)) ? true : false;
}

void* deque_at(const deque_t* cpt_deque, size_t t_pos)
{
    deque_iterator_t t_iter;

    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL && cpt_deque->_t_mapsize > 0);
    assert(t_pos < deque_size(cpt_deque));

    t_iter = iterator_next_n(deque_begin(cpt_deque), t_pos);
    assert(_deque_iterator_belong_to_deque(cpt_deque, t_iter));

    return (void*)iterator_get_pointer(t_iter);
}

void deque_swap(deque_t* pt_dequefirst, deque_t* pt_dequesecond)
{
    deque_t t_dequetmp;

    assert(_deque_same_type(pt_dequefirst, pt_dequesecond));

    t_dequetmp = *pt_dequefirst;
    *pt_dequefirst = *pt_dequesecond;
    *pt_dequesecond = t_dequetmp;

    /* the pointer to container must not be swap */
    _GET_CONTAINER(pt_dequefirst->_t_start) = pt_dequefirst;
    _GET_CONTAINER(pt_dequefirst->_t_finish) = pt_dequefirst;

    _GET_CONTAINER(pt_dequesecond->_t_start) = pt_dequesecond;
    _GET_CONTAINER(pt_dequesecond->_t_finish) = pt_dequesecond;
}

void deque_pop_back(deque_t* pt_deque)
{
    assert(deque_size(pt_deque) > 0);
    _deque_shrink_at_end(pt_deque, 1);
}

void deque_pop_front(deque_t* pt_deque)
{
    assert(deque_size(pt_deque) > 0);
    _deque_shrink_at_begin(pt_deque, 1);
}


void deque_insert_range(
    deque_t* pt_deque, deque_iterator_t t_pos, 
    deque_iterator_t t_begin, deque_iterator_t t_end)
{
    int    n_elemcount = 0;
    bool_t t_result = false;

    assert(_deque_iterator_belong_to_deque(pt_deque, t_pos));
    assert(_deque_same_deque_iterator_type(pt_deque, t_begin));
    assert(iterator_equal(t_begin, t_end) || _deque_iterator_before(t_begin, t_end));

    n_elemcount = iterator_distance(t_begin, t_end);
    /* if the element number after insert pos is little 
     * then insert in front */
    if(iterator_distance(deque_begin(pt_deque), t_pos) < (int)deque_size(pt_deque)/2)
    {
        deque_iterator_t t_oldbegin;
        deque_iterator_t t_gap;

        /* expand one element at front */
        t_oldbegin = _deque_expand_at_begin(pt_deque, n_elemcount, &t_pos);
        /* move the element range [oldfront, pos) to [newfront, pos) */
        t_gap = _move_elem_to_begin(pt_deque, t_oldbegin, t_pos, n_elemcount);
        assert(iterator_distance(t_gap, t_pos) == n_elemcount);

        for(;
            !iterator_equal(t_gap, t_pos) && !iterator_equal(t_begin, t_end); 
            t_gap = iterator_next(t_gap), t_begin = iterator_next(t_begin))
        {
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_gap),
                _deque_iterator_get_pointer_auxiliary(t_begin), &t_result);
            assert(t_result);
        }
        assert(iterator_equal(t_gap, t_pos) && iterator_equal(t_begin, t_end));
    }
    /* else insert in back */
    else
    {
        deque_iterator_t t_oldend = _deque_expand_at_end(pt_deque, n_elemcount, &t_pos);
        _move_elem_to_end(pt_deque, t_pos, t_oldend, n_elemcount);

        for(; !iterator_equal(t_begin, t_end);
            t_pos = iterator_next(t_pos), t_begin = iterator_next(t_begin))
        {
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_pos),
                _deque_iterator_get_pointer_auxiliary(t_begin), &t_result);
            assert(t_result);
        }
    }
}

deque_iterator_t deque_erase(deque_t* pt_deque, deque_iterator_t t_pos)
{
    assert(_deque_iterator_belong_to_deque(pt_deque, t_pos));
    assert(!iterator_equal(t_pos, deque_end(pt_deque)));

    if(iterator_equal(t_pos, deque_begin(pt_deque)))
    {
        deque_pop_front(pt_deque);
        return deque_begin(pt_deque);
    }
    else if(iterator_equal(t_pos, iterator_prev(deque_end(pt_deque))))
    {
        deque_pop_back(pt_deque);
        return deque_end(pt_deque);
    }
    else
    {
        deque_iterator_t t_result = t_pos;

        t_pos = iterator_next(t_pos);
        _move_elem_to_begin(pt_deque, t_pos, deque_end(pt_deque), 1);
        _deque_shrink_at_end(pt_deque, 1);

        return t_result;
    }
}

deque_iterator_t deque_erase_range(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end)
{
    assert(_deque_iterator_belong_to_deque(pt_deque, t_begin));
    assert(iterator_equal(t_begin, t_end) || _deque_iterator_before(t_begin, t_end));

    _move_elem_to_begin(pt_deque, t_end, deque_end(pt_deque),
        iterator_distance(t_begin, t_end));
    _deque_shrink_at_end(pt_deque, iterator_distance(t_begin, t_end));

    return t_begin;
}

void deque_resize(deque_t* pt_deque, size_t t_resize)
{
    if(t_resize < deque_size(pt_deque))
    {
        _deque_shrink_at_end(pt_deque, deque_size(pt_deque) - t_resize);
    }
    else if(t_resize > deque_size(pt_deque))
    {
        _deque_expand_at_end(pt_deque, t_resize - deque_size(pt_deque), NULL);
    }
}

void deque_clear(deque_t* pt_deque)
{
    deque_erase_range(pt_deque, deque_begin(pt_deque), deque_end(pt_deque));
}

/** local function implementation section **/

/** eof **/

