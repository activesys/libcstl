/*
 *  The implement of deque private function.
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

/* deque private function */
deque_t* _create_deque(const char* s_typename)
{
    deque_t*    pt_newdeque = NULL;

    /* alloc memory for deque_t */
    if((pt_newdeque = (deque_t*)malloc(sizeof(deque_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_deque_auxiliary(pt_newdeque, s_typename))
    {
        free(pt_newdeque);
        return NULL;
    }

    return pt_newdeque;
}

bool_t _create_deque_auxiliary(deque_t* pt_deque, const char* s_typename)
{
    assert(pt_deque != NULL && s_typename != NULL);

    _type_get_type(&pt_deque->_t_typeinfo, s_typename);
    if(pt_deque->_t_typeinfo._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pt_deque->_ppc_map = NULL;
    pt_deque->_t_mapsize = 0;
    pt_deque->_t_start = _create_deque_iterator();
    pt_deque->_t_finish = _create_deque_iterator();

    _alloc_init(&pt_deque->_t_allocater);
    return true;
}

void _deque_init_elem(deque_t* pt_deque, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _deque_init_elem_varg(pt_deque, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _deque_init_elem_varg(deque_t* pt_deque, size_t t_count, va_list val_elemlist)
{
    /*  _t_start
     *  +---+-----------+ _pc_afterlast
     *  |   |   |   |   +------------------------------------+
     *  +-+-+-+-+-+-+---+                                    |
     *    |   |   | _pc_corepos                              V
     *    |   |   +------------------------------------------+
     *    |   | _pc_first                                    V
     *    |   +------------------->+-------------------------+
     *    |                 +----->|                         |
     *    |                 |      +-------------------------+
     *    |                 |
     *    | _ppc_mappos     |
     *    +---------------+ |                  +-------------------------+
     *                    | |   +------------->|                         |
     *                    | |   |              +-------------------------+
     *                    V |   |              ^   _pc_corepos           ^
     *             +------+-+-+-+-+--------+   +-------+                 |
     * _ppc_map--->|      |   |   |        |   |       |    _pc_afterlast|
     *             +------+---+---+--------+   +---+   |     +-----------+
     *                          ^         _pc_first|   |     |
     *                          |            +---+-+-+-+-+-+-+
     *                          +------------+   |   |   |   | _t_finish
     *                         _ppc_mappos   +---+---+---+---+
     * ********************************************************************
     * the state of initialized deque
     */
    size_t     t_index = 0;
    size_t     t_startpos = 0;      /* the real map start pos */
    size_t     t_mapcount = 0;      /* the map count */
    size_t     t_validmapcount = 0; /* the valid count in map */
    size_t     t_endelemcount = 0;  /* the element count in the last container */
    void*      pv_varg = NULL;
    bool_t     t_result = false;
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
    /* else element count <= 0 */
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

    /* get varg value only once */
    pv_varg = _alloc_allocate(&pt_deque->_t_allocater, _GET_DEQUE_TYPE_SIZE(pt_deque), 1);
    assert(pv_varg != NULL);
    _deque_get_varg_value_auxiliary(pt_deque, val_elemlist, pv_varg);

    for(t_iter = deque_begin(pt_deque);
        !iterator_equal(t_iter, deque_end(pt_deque));
        t_iter = iterator_next(t_iter))
    {
        /* initialize all elements */
        _deque_init_elem_auxiliary(pt_deque, _deque_iterator_get_pointer_auxiliary(t_iter));

        /* copy element for varg value */
        t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
            _deque_iterator_get_pointer_auxiliary(t_iter), pv_varg, &t_result);
        assert(t_result);
    }

    _deque_destroy_varg_value_auxiliary(pt_deque, pv_varg);
    _alloc_deallocate(&pt_deque->_t_allocater, pv_varg, _GET_DEQUE_TYPE_SIZE(pt_deque), 1);
}

void _deque_destroy_auxiliary(deque_t* pt_deque)
{
    _mappointer_t    t_mappos = NULL;
    bool_t           t_result = false;
    deque_iterator_t t_iter;

    /*assert(_deque_iterator_belong_to_deque(pt_deque, pt_deque->_t_start));*/
    /*assert(_deque_iterator_belong_to_deque(pt_deque, pt_deque->_t_finish));*/

    if(_deque_is_inited(pt_deque))
    {
        /* destroy all elements */
        for(t_iter = deque_begin(pt_deque);
            !iterator_equal(t_iter, deque_end(pt_deque));
            t_iter = iterator_next(t_iter))
        {
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_DESTROY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_iter), &t_result);
            assert(t_result);
        }

        /* destroy the all element container */
        for(t_mappos = _GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
            t_mappos <= _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish);
            ++t_mappos)
        {
            _alloc_deallocate(&pt_deque->_t_allocater, *t_mappos,
                _GET_DEQUE_TYPE_SIZE(pt_deque), _DEQUE_ELEM_COUNT);
        }

        /* destroy the map */
        _alloc_deallocate(&pt_deque->_t_allocater, pt_deque->_ppc_map,
            sizeof(char*), pt_deque->_t_mapsize);

        /* destroy the allocator */
        _alloc_destroy(&pt_deque->_t_allocater);

        /* destroy the start and finish iterator */
        _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) = NULL;
        _GET_DEQUE_FIRST_POS(pt_deque->_t_start) = NULL;
        _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start) = NULL;
        _GET_DEQUE_COREPOS(pt_deque->_t_start) = NULL;
        _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) = NULL;
        _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) = NULL;
        _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_finish) = NULL;
        _GET_DEQUE_COREPOS(pt_deque->_t_finish) = NULL;
    }
    else
    {
        _alloc_destroy(&pt_deque->_t_allocater);
    }
}

void _deque_assign_elem(deque_t* pt_deque, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _deque_assign_elem_varg(pt_deque, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _deque_assign_elem_varg(deque_t* pt_deque, size_t t_count, va_list val_elemlist)
{
    deque_iterator_t t_iter;   /* the iterator of dest deque for iterate */
    void*            pv_varg = NULL;
    bool_t           t_result = false;

    assert(pt_deque != NULL);

    /* init the dest deque with the distance between t_begin and t_end,
     * compare and element destroy function. */
    deque_resize(pt_deque, t_count);

    if(t_count > 0)
    {
        pv_varg = _alloc_allocate(&pt_deque->_t_allocater, _GET_DEQUE_TYPE_SIZE(pt_deque), 1);
        assert(pv_varg != NULL);
        _deque_get_varg_value_auxiliary(pt_deque, val_elemlist, pv_varg);

        /* copy the elements from src range to dest deque */
        for(t_iter = deque_begin(pt_deque);
            !iterator_equal(t_iter, deque_end(pt_deque));
            t_iter = iterator_next(t_iter))
        {
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_iter), pv_varg, &t_result);
            assert(t_result);
        }

        _deque_destroy_varg_value_auxiliary(pt_deque, pv_varg);
        _alloc_deallocate(&pt_deque->_t_allocater, pv_varg, _GET_DEQUE_TYPE_SIZE(pt_deque), 1);
    }
}

void _deque_push_back(deque_t* pt_deque, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_deque);
    _deque_push_back_varg(pt_deque, val_elemlist);
    va_end(val_elemlist);
}

void _deque_push_back_varg(deque_t* pt_deque, va_list val_elemlist)
{
    deque_iterator_t t_oldend = _expand_at_end(pt_deque, 1, NULL);
    assert(_deque_iterator_belong_to_deque(pt_deque, t_oldend));

    /* get value from varg */
    _type_get_varg_value(&pt_deque->_t_typeinfo, val_elemlist,
        _deque_iterator_get_pointer_auxiliary(t_oldend));
}

void _deque_push_front(deque_t* pt_deque, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_deque);
    _deque_push_front_varg(pt_deque, val_elemlist);
    va_end(val_elemlist);
}

void _deque_push_front_varg(deque_t* pt_deque, va_list val_elemlist)
{
    _expand_at_begin(pt_deque, 1, NULL);
    /* get value from varg */
    _type_get_varg_value(&pt_deque->_t_typeinfo, val_elemlist,
        _deque_iterator_get_pointer_auxiliary(deque_begin(pt_deque)));
}

deque_iterator_t _deque_insert_n(
    deque_t* pt_deque, deque_iterator_t t_pos, size_t t_count, ...)
{
    deque_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    t_iter = _deque_insert_n_varg(pt_deque, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

deque_iterator_t _deque_insert_n_varg(
    deque_t* pt_deque, deque_iterator_t t_pos, size_t t_count, va_list val_elemlist)
{
    deque_iterator_t t_resultpos;
    void*            pv_varg = NULL;
    bool_t           t_result = false;

    assert(_deque_iterator_belong_to_deque(pt_deque, t_pos));

    /* get varg value only once */
    pv_varg = _alloc_allocate(&pt_deque->_t_allocater, _GET_DEQUE_TYPE_SIZE(pt_deque), 1);
    assert(pv_varg != NULL);
    _deque_get_varg_value_auxiliary(pt_deque, val_elemlist, pv_varg);

    /* if the element number after insert pos is little 
     * then insert in front */
    if(iterator_distance(deque_begin(pt_deque), t_pos) < (int)deque_size(pt_deque)/2)
    {
        deque_iterator_t t_oldbegin;
        deque_iterator_t t_gap;

        /* expand one element at front */
        t_oldbegin = _expand_at_begin(pt_deque, t_count, &t_pos);
        /* move the element range [oldfront, pos) to [newfront, pos) */
        t_resultpos = t_gap = _move_elem_to_begin(pt_deque, t_oldbegin, t_pos, t_count);
        assert(iterator_distance(t_gap, t_pos) == (int)t_count);

        for(; !iterator_equal(t_gap, t_pos); t_gap = iterator_next(t_gap))
        {
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_gap), pv_varg, &t_result);
            assert(t_result);
        }
        assert(iterator_equal(t_gap, t_pos));
    }
    /* else insert in back */
    else
    {
        size_t t_index = 0;
        deque_iterator_t t_oldend = _expand_at_end(pt_deque, t_count, &t_pos);
        deque_iterator_t t_gap = _move_elem_to_end(pt_deque, t_pos, t_oldend, t_count);
        t_resultpos = t_gap;

        assert(iterator_equal(t_pos, t_gap));

        for(t_index = 0; t_index < t_count; ++t_index)
        {
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_pos), pv_varg, &t_result);
            t_pos = iterator_next(t_pos);
            assert(t_result);
        }
    }

    _deque_destroy_varg_value_auxiliary(pt_deque, pv_varg);
    _alloc_deallocate(&pt_deque->_t_allocater, pv_varg, _GET_DEQUE_TYPE_SIZE(pt_deque), 1);

    return t_resultpos;
}

void _deque_resize_elem(deque_t* pt_deque, size_t t_resize, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_resize);
    _deque_resize_elem_varg(pt_deque, t_resize, val_elemlist);
    va_end(val_elemlist);
}

void _deque_resize_elem_varg(deque_t* pt_deque, size_t t_resize, va_list val_elemlist)
{
    void*  pv_varg = NULL;
    bool_t t_result = false;

    if(t_resize < deque_size(pt_deque))
    {
        _shrink_at_end(pt_deque, deque_size(pt_deque) - t_resize);
    }
    else if(t_resize > deque_size(pt_deque))
    {
        deque_iterator_t t_oldend =
            _expand_at_end(pt_deque, t_resize - deque_size(pt_deque), NULL);

        /* get varg value only once */
        pv_varg = _alloc_allocate(&pt_deque->_t_allocater, _GET_DEQUE_TYPE_SIZE(pt_deque), 1);
        assert(pv_varg != NULL);
        _deque_get_varg_value_auxiliary(pt_deque, val_elemlist, pv_varg);
        for(;
            !iterator_equal(t_oldend, deque_end(pt_deque)); 
            t_oldend = iterator_next(t_oldend))
        {
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_oldend), pv_varg, &t_result);
            assert(t_result);
        }
        _deque_destroy_varg_value_auxiliary(pt_deque, pv_varg);
        _alloc_deallocate(&pt_deque->_t_allocater, pv_varg, _GET_DEQUE_TYPE_SIZE(pt_deque), 1);
    }
}

void _deque_init_elem_auxiliary(deque_t* pt_deque, void* pv_elem)
{
    assert(pt_deque != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_DEQUE_TYPE_STYLE(pt_deque) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_DEQUE_TYPE_NAME(pt_deque), s_elemtypename);

        _GET_DEQUE_TYPE_INIT_FUNCTION(pt_deque)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_TYPE_INIT_FUNCTION(pt_deque)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/

/** eof **/

