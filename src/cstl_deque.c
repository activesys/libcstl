/*
 *  The implement of deque module.
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
#include <stdarg.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"

#include "cstl_deque_iterator.h"
#include "cstl_deque_private.h"
#include "cstl_deque.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/
#define _DEQUE_MAP_COUNT                16
#define _DEQUE_MAP_GROW_STEP            8
#define _DEQUE_ELEM_COUNT               16

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _iterator_belong_to_deque(
    const deque_t* cpt_deque, deque_iterator_t t_iter);
static bool_t _same_deque_iterator_type(
    const deque_t* cpt_deque, deque_iterator_t t_iter);
static bool_t _same_deque_type(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond);
#endif /* NDEBUG */

/*
 * Expand deque_t.
 */
static deque_iterator_t _expand_at_back(
    deque_t* pt_deque, size_t t_expandsize, deque_iterator_t* pt_pos);
static deque_iterator_t _expand_at_front(
    deque_t* pt_deque, size_t t_expandsize, deque_iterator_t* pt_pos);

/*
 * Shrink deque_t.
 */
static void _shrink_at_back(deque_t* pt_deque, size_t t_shrinksize);
static void _shrink_at_front(deque_t* pt_deque, size_t t_shrinksize);

/*
 * Move element.
 */
static deque_iterator_t _move_elem_to_back(
    deque_t* pt_deque, deque_iterator_t t_begin, 
    deque_iterator_t t_end, size_t t_movesize);
static deque_iterator_t _move_elem_to_front(
    deque_t* pt_deque, deque_iterator_t t_begin, 
    deque_iterator_t t_end, size_t t_movesize);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* deque iterator function */
deque_iterator_t create_deque_iterator(void)
{
    deque_iterator_t t_newiterator;

    _GET_DEQUE_MAP_POINTER(t_newiterator) = NULL;
    _GET_DEQUE_FIRST_POS(t_newiterator) = NULL;
    _GET_DEQUE_AFTERLAST_POS(t_newiterator) = NULL;
    _GET_DEQUE_COREPOS(t_newiterator) = NULL;
    t_newiterator._pt_container = NULL;
    t_newiterator._t_containertype = _DEQUE_CONTAINER;
    t_newiterator._t_iteratortype = _RANDOM_ACCESS_ITERATOR;

    return t_newiterator;
}

bool_t _deque_iterator_equal(
    deque_iterator_t t_iterfirst, deque_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_DEQUE_CONTAINER(t_iterfirst) == _GET_DEQUE_CONTAINER(t_itersecond));
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_itersecond), t_itersecond));
    
    if(_GET_DEQUE_MAP_POINTER(t_iterfirst) == _GET_DEQUE_MAP_POINTER(t_itersecond) &&
       _GET_DEQUE_FIRST_POS(t_iterfirst) == _GET_DEQUE_FIRST_POS(t_itersecond) &&
       _GET_DEQUE_AFTERLAST_POS(t_iterfirst) == _GET_DEQUE_AFTERLAST_POS(t_itersecond) &&
       _GET_DEQUE_COREPOS(t_iterfirst) == _GET_DEQUE_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        /* 
         * if the start corepos equal to the after last node and the finish 
         * corepos equal to the first position, the two iterator equal to.
         */
        if(_GET_DEQUE_MAP_POINTER(t_iterfirst) < _GET_DEQUE_MAP_POINTER(t_itersecond))
        {
            if(_GET_DEQUE_MAP_POINTER(t_iterfirst) + 1 ==
                   _GET_DEQUE_MAP_POINTER(t_itersecond) &&
               _GET_DEQUE_COREPOS(t_iterfirst) ==
                   _GET_DEQUE_AFTERLAST_POS(t_iterfirst) &&
               _GET_DEQUE_COREPOS(t_itersecond) ==
                   _GET_DEQUE_FIRST_POS(t_itersecond))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(_GET_DEQUE_MAP_POINTER(t_itersecond) + 1 ==
                    _GET_DEQUE_MAP_POINTER(t_iterfirst) &&
               _GET_DEQUE_COREPOS(t_itersecond) ==
                   _GET_DEQUE_AFTERLAST_POS(t_itersecond) &&
               _GET_DEQUE_COREPOS(t_iterfirst) ==
                   _GET_DEQUE_FIRST_POS(t_iterfirst))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

void _deque_iterator_get_value(deque_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, deque_end(_GET_DEQUE_CONTAINER(t_iter))));

    if(_GET_DEQUE_COREPOS(t_iter) != _GET_DEQUE_AFTERLAST_POS(t_iter))
    {
        memcpy(pv_value, _GET_DEQUE_COREPOS(t_iter),
            _GET_DEQUE_CONTAINER(t_iter)->_t_typesize);
    }
    else
    {
        /* 
         * when the iterator is begin and the corepos equal to afterlast 
         * then get the first element in next container.
         */
        _mappointer_t t_nextcontainer = _GET_DEQUE_MAP_POINTER(t_iter) + 1;
        memcpy(pv_value, *t_nextcontainer, _GET_DEQUE_CONTAINER(t_iter)->_t_typesize);
    }
}

void _deque_iterator_set_value(deque_iterator_t t_iter, const void* cpv_value)
{
    assert(cpv_value != NULL);
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, deque_end(_GET_DEQUE_CONTAINER(t_iter))));

    if(_GET_DEQUE_COREPOS(t_iter) != _GET_DEQUE_AFTERLAST_POS(t_iter))
    {
        memcpy(_GET_DEQUE_COREPOS(t_iter), cpv_value,
            _GET_DEQUE_CONTAINER(t_iter)->_t_typesize);
    }
    else
    {
        /* 
         * when the iterator is begin and the corepos equal to afterlast 
         * then get the first element in next container.
         */
        _mappointer_t t_nextcontainer = _GET_DEQUE_MAP_POINTER(t_iter) + 1;
        memcpy(*t_nextcontainer, cpv_value, _GET_DEQUE_CONTAINER(t_iter)->_t_typesize);
    }
}

const void* _deque_iterator_get_pointer(deque_iterator_t t_iter)
{
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, deque_end(_GET_DEQUE_CONTAINER(t_iter))));

    if(_GET_DEQUE_COREPOS(t_iter) != _GET_DEQUE_AFTERLAST_POS(t_iter))
    {
        return _GET_DEQUE_COREPOS(t_iter);
    }
    else
    {
        /* 
         * when the iterator is begin and the corepos equal to afterlast 
         * then get the first element in next container.
         */
        _mappointer_t t_nextcontainer = _GET_DEQUE_MAP_POINTER(t_iter) + 1;
        return *t_nextcontainer;
    }
}

deque_iterator_t _deque_iterator_next(deque_iterator_t t_iter)
{
    size_t t_beyondsize = 0;
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    _GET_DEQUE_COREPOS(t_iter) += _GET_DEQUE_CONTAINER(t_iter)->_t_typesize;
    /* at the node after the last node */
    if(_GET_DEQUE_COREPOS(t_iter) >= _GET_DEQUE_AFTERLAST_POS(t_iter))
    {
        t_beyondsize = _GET_DEQUE_COREPOS(t_iter) - _GET_DEQUE_AFTERLAST_POS(t_iter);
        assert(t_beyondsize == 0 ||
               t_beyondsize == _GET_DEQUE_CONTAINER(t_iter)->_t_typesize);
        /* is the current pos is not the last pos of map */
        if(_GET_DEQUE_MAP_POINTER(t_iter) < 
           _GET_DEQUE_MAP_POINTER(_GET_DEQUE_CONTAINER(t_iter)->_t_finish))
        {
            _GET_DEQUE_MAP_POINTER(t_iter) += 1;
            _GET_DEQUE_FIRST_POS(t_iter) = *_GET_DEQUE_MAP_POINTER(t_iter);
            _GET_DEQUE_AFTERLAST_POS(t_iter) = 
                _GET_DEQUE_FIRST_POS(t_iter) + 
                _GET_DEQUE_CONTAINER(t_iter)->_t_typesize * _DEQUE_ELEM_COUNT;
            _GET_DEQUE_COREPOS(t_iter) = 
                _GET_DEQUE_FIRST_POS(t_iter) + t_beyondsize;
        }
    }

    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    return t_iter;
}

deque_iterator_t _deque_iterator_prev(deque_iterator_t t_iter)
{
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    _GET_DEQUE_COREPOS(t_iter) -= _GET_DEQUE_CONTAINER(t_iter)->_t_typesize;
    /* before the first node */
    if(_GET_DEQUE_COREPOS(t_iter) < _GET_DEQUE_FIRST_POS(t_iter))
    {
        /* is the current node is the first node */
        if(_GET_DEQUE_MAP_POINTER(t_iter) >
           _GET_DEQUE_MAP_POINTER(_GET_DEQUE_CONTAINER(t_iter)->_t_start))
        {
            _GET_DEQUE_MAP_POINTER(t_iter) -= 1;
            _GET_DEQUE_FIRST_POS(t_iter) = *_GET_DEQUE_MAP_POINTER(t_iter);
            _GET_DEQUE_AFTERLAST_POS(t_iter) = 
                _GET_DEQUE_FIRST_POS(t_iter) +
                _GET_DEQUE_CONTAINER(t_iter)->_t_typesize * _DEQUE_ELEM_COUNT;
            _GET_DEQUE_COREPOS(t_iter) = 
                _GET_DEQUE_AFTERLAST_POS(t_iter) -
                _GET_DEQUE_CONTAINER(t_iter)->_t_typesize;
        }
    }

    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    return t_iter;
}

void* _deque_iterator_at(deque_iterator_t t_iter, int n_index)
{
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));

    t_iter = iterator_next_n(t_iter, n_index);

    return _GET_DEQUE_COREPOS(t_iter);
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
                       _GET_DEQUE_CONTAINER(t_iterfirst)->_t_typesize;
        t_middlesize = t_mapnodesize * _DEQUE_ELEM_COUNT;
        t_endsize = (_GET_DEQUE_COREPOS(t_itersecond) -
                     _GET_DEQUE_FIRST_POS(t_itersecond)) / 
                     _GET_DEQUE_CONTAINER(t_itersecond)->_t_typesize;
               
        return -(t_beginsize + t_middlesize + t_endsize);
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
                       _GET_DEQUE_CONTAINER(t_itersecond)->_t_typesize;
        t_middlesize = t_mapnodesize * _DEQUE_ELEM_COUNT;
        t_endsize = (_GET_DEQUE_COREPOS(t_iterfirst) -
                     _GET_DEQUE_FIRST_POS(t_iterfirst)) / 
                     _GET_DEQUE_CONTAINER(t_iterfirst)->_t_typesize;
               
        return t_beginsize + t_middlesize + t_endsize;
    }
}

bool_t _deque_iterator_before(deque_iterator_t t_iterfirst, deque_iterator_t t_itersecond)
{
    return _deque_iterator_less(t_iterfirst, t_itersecond);
}

bool_t _deque_iterator_less(deque_iterator_t t_iterfirst, deque_iterator_t t_itersecond)
{
    deque_iterator_t t_i;

    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_DEQUE_CONTAINER(t_iterfirst) == _GET_DEQUE_CONTAINER(t_itersecond));
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_itersecond), t_itersecond));

    if(iterator_equal(t_iterfirst, t_itersecond))
    {
        return false;
    }

    for(t_i = t_iterfirst;
        !iterator_equal(t_i, _GET_DEQUE_CONTAINER(t_iterfirst)->_t_finish);
        t_i = iterator_next(t_i))
    {
        if(iterator_equal(t_i, t_itersecond))
        {
            return true;
        }
    }

    if(iterator_equal(t_itersecond, _GET_DEQUE_CONTAINER(t_iterfirst)->_t_finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* deque private function */
deque_t _create_deque(size_t t_typesize, const char* sz_typename)
{
    deque_t t_newdeque;

    assert(t_typesize > 0);
    assert(sz_typename != NULL);

    /* init type information */
    t_newdeque._t_typesize = t_typesize;
    memset(t_newdeque._sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(t_newdeque._sz_typename, sz_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_newdeque._t_typesize, t_newdeque._sz_typename);
    /* init map */
    t_newdeque._ppc_map = NULL;
    t_newdeque._t_mapsize = 0;
    /* init start and finish iterator */
    t_newdeque._t_start = create_deque_iterator();
    t_newdeque._t_finish = create_deque_iterator();
    /* init compare and destroy function */
    t_newdeque._pfun_cmp = NULL;

    return t_newdeque;
}

void _deque_push_back_varg(deque_t* pt_deque, va_list val_elemlist)
{
    deque_iterator_t t_oldend = _expand_at_back(pt_deque, 1, NULL);

    assert(_iterator_belong_to_deque(pt_deque, t_oldend));

    _get_varg_value(
        _GET_DEQUE_COREPOS(t_oldend), val_elemlist,
        pt_deque->_t_typesize, pt_deque->_sz_typename);
}

/* deque function */
void deque_init(deque_t* pt_deque)
{
    deque_init_n(pt_deque, 0);
}

void deque_init_n(deque_t* pt_deque, size_t t_count)
{
    deque_init_elem(pt_deque, t_count, 0x00);
}

void _deque_init_elem(deque_t* pt_deque, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _deque_init_elem_varg(pt_deque, t_count, val_elemlist);
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
    size_t t_index = 0;
    size_t t_startpos = 0;      /* the real map start pos */
    size_t t_mapcount = 0;      /* the map count */
    size_t t_validmapcount = 0; /* the valid count in map */
    size_t t_endelemcount = 0;  /* the element count in the last container */
    void*  pv_init_elem = NULL;
    
    assert(pt_deque != NULL);

    /* initialize the alloc */
    allocate_init(&pt_deque->_t_allocater);
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
                                  _DEQUE_MAP_GROW_STEP - 1) / 
                                  _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
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
    pt_deque->_ppc_map = allocate(&pt_deque->_t_allocater, sizeof(char*), t_mapcount);
    pt_deque->_t_mapsize = t_mapcount;
    assert(pt_deque->_ppc_map != NULL);
    memset(pt_deque->_ppc_map, 0x00, sizeof(char*)*t_mapcount);
    t_startpos = (t_mapcount - t_validmapcount) / 2;

    /* get varg value only once */
    pv_init_elem = allocate(&pt_deque->_t_allocater, pt_deque->_t_typesize, 1);
    assert(pv_init_elem != NULL);
    _get_varg_value(pv_init_elem, val_elemlist, pt_deque->_t_typesize, pt_deque->_sz_typename);
    for(t_index = t_startpos; t_index < t_startpos + t_validmapcount; ++t_index)
    {
        int i = 0;

        pt_deque->_ppc_map[t_index] = allocate(
            &pt_deque->_t_allocater, pt_deque->_t_typesize, _DEQUE_ELEM_COUNT);
        assert(pt_deque->_ppc_map[t_index] != NULL);

        for(i = 0; i < _DEQUE_ELEM_COUNT; ++i)
        {
            memcpy(
                pt_deque->_ppc_map[t_index] + i * pt_deque->_t_typesize, pv_init_elem,
                pt_deque->_t_typesize);
        }
    }
    deallocate(&pt_deque->_t_allocater, pv_init_elem, pt_deque->_t_typesize, 1);
    /* initialize the start iterator */
    _GET_CONTAINER(pt_deque->_t_start) = pt_deque;
    _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) = 
        pt_deque->_ppc_map + t_startpos;
    _GET_DEQUE_FIRST_POS(pt_deque->_t_start) = 
        *_GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
    _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start) = 
        _GET_DEQUE_FIRST_POS(pt_deque->_t_start) + 
        _DEQUE_ELEM_COUNT * pt_deque->_t_typesize;
    _GET_DEQUE_COREPOS(pt_deque->_t_start) = 
        _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start);
    /* initialize the finish iterator */
    _GET_CONTAINER(pt_deque->_t_finish) = pt_deque;
    _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) = 
        pt_deque->_ppc_map + t_startpos + t_validmapcount - 1;
    _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) = 
        *_GET_DEQUE_MAP_POINTER(pt_deque->_t_finish);
    _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_finish) = 
        _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) + 
        _DEQUE_ELEM_COUNT * pt_deque->_t_typesize;
    _GET_DEQUE_COREPOS(pt_deque->_t_finish) = 
        _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) + 
        t_endelemcount * pt_deque->_t_typesize;
    /* initialize the compare and destroy element function */
    pt_deque->_pfun_cmp = _get_cmp_function(pt_deque->_sz_typename);
}

void deque_destroy(deque_t* pt_deque)
{
    _mappointer_t    t_mappos = NULL;

    assert(_iterator_belong_to_deque(pt_deque, pt_deque->_t_start));
    assert(_iterator_belong_to_deque(pt_deque, pt_deque->_t_finish));


    /* destroy the all element container */
    for(t_mappos = _GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
        t_mappos != _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish);
        ++t_mappos)
    {
        deallocate(
            &pt_deque->_t_allocater, *t_mappos, pt_deque->_t_typesize, _DEQUE_ELEM_COUNT);
    }

    /* destroy the map */
    deallocate(
        &pt_deque->_t_allocater, pt_deque->_ppc_map, sizeof(char*), pt_deque->_t_mapsize);

    /* destroy the allocator */
    allocate_destroy(&pt_deque->_t_allocater);

    /* destroy the start and finish iterator */
    _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) = NULL;
    _GET_DEQUE_FIRST_POS(pt_deque->_t_start) = NULL;
    _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start) = NULL;
    _GET_DEQUE_COREPOS(pt_deque->_t_start) = NULL;
    _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) = NULL;
    _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) = NULL;
    _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_finish) = NULL;
    _GET_DEQUE_COREPOS(pt_deque->_t_finish) = NULL;

    /* destroy the compare and destroy function */
    pt_deque->_pfun_cmp = NULL;
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

    return (size_t)(-1) / cpt_deque->_t_typesize;
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
    deque_iterator_t t_iterator;

    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL && cpt_deque->_t_mapsize > 0);

    t_iterator = cpt_deque->_t_finish;
    t_iterator = iterator_prev(t_iterator);

    return t_iterator;
}

deque_reverse_iterator_t deque_rend(const deque_t* cpt_deque)
{
    deque_iterator_t t_iterator;

    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL && cpt_deque->_t_mapsize > 0);

    t_iterator = cpt_deque->_t_start;
    _GET_DEQUE_COREPOS(t_iterator) =
        _GET_DEQUE_COREPOS(cpt_deque->_t_start) - cpt_deque->_t_typesize;

    return t_iterator;
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

    assert(pt_dequedest != NULL && pt_dequedest->_ppc_map == NULL &&
           pt_dequedest->_t_mapsize == 0 && pt_dequedest->_pfun_cmp == NULL);
    assert(pt_dequedest->_t_typesize == _GET_DEQUE_CONTAINER(t_begin)->_t_typesize &&
           strncmp(pt_dequedest->_sz_typename,
               _GET_DEQUE_CONTAINER(t_begin)->_sz_typename, _ELEM_TYPE_NAME_SIZE) == 0);
    assert(iterator_equal(t_begin, t_end) || _deque_iterator_before(t_begin, t_end));

    /* init the dest deque with the distance between t_begin and t_end,
     * compare and element destroy function. */
    deque_init_n(pt_dequedest, iterator_distance(t_begin, t_end));
    /* copy the elements from src range to dest deque */
    for(t_dest = pt_dequedest->_t_start, t_src = t_begin;
        !iterator_equal(t_dest, pt_dequedest->_t_finish) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        memcpy(_GET_DEQUE_COREPOS(t_dest), _GET_DEQUE_COREPOS(t_src),
            pt_dequedest->_t_typesize);
    }
    assert(iterator_equal(t_dest, pt_dequedest->_t_finish) &&
           iterator_equal(t_src, t_end));
}

void deque_assign(deque_t* pt_dequedest, const deque_t* cpt_dequesrc)
{
    deque_assign_range(
        pt_dequedest, deque_begin(cpt_dequesrc), deque_end(cpt_dequesrc));
}

void _deque_assign_elem(deque_t* pt_deque, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _deque_assign_elem_varg(pt_deque, t_count, val_elemlist);
}

void _deque_assign_elem_varg(deque_t* pt_deque, size_t t_count, va_list val_elemlist)
{
    int (*pfun_cmp)(const void*, const void*);

    assert(pt_deque != NULL && pt_deque->_ppc_map != NULL && pt_deque->_t_mapsize > 0);

    pfun_cmp = pt_deque->_pfun_cmp;
    /* destroy the deque */
    deque_destroy(pt_deque);
    /* init the deque with the n_elemcount compare and element
     * destroy function itself. */
    _deque_init_elem_varg(pt_deque, t_count, val_elemlist);
}

void deque_assign_range(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end)
{
    deque_iterator_t t_dest;   /* the iterator of dest deque for iterate */
    deque_iterator_t t_src;    /* the iterator of src range for iterate */

    assert(_same_deque_iterator_type(pt_deque, t_begin));
    assert(iterator_equal(t_begin, t_end) || _deque_iterator_before(t_begin, t_end));

    /* destroy the dest deque */
    deque_destroy(pt_deque);
    /* init the dest deque with the distance between t_begin and t_end,
     * compare and element destroy function. */
    deque_init_n(pt_deque, iterator_distance(t_begin, t_end));
    /* copy the elements from src range to dest deque */
    for(t_dest = pt_deque->_t_start, t_src = t_begin;
        !iterator_equal(t_dest, pt_deque->_t_finish) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        memcpy(_GET_DEQUE_COREPOS(t_dest), _GET_DEQUE_COREPOS(t_src),
            pt_deque->_t_typesize);
    }
    assert(iterator_equal(t_dest, pt_deque->_t_finish) &&
           iterator_equal(t_src, t_end));
}

bool_t deque_equal(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    deque_iterator_t t_first;  /* the iterator to first deque for iterate */
    deque_iterator_t t_second; /* the iterator to second deque for iterate */

    assert(cpt_dequefirst != NULL && cpt_dequesecond != NULL &&
           cpt_dequefirst->_ppc_map != NULL && cpt_dequesecond->_ppc_map != NULL &&
           cpt_dequefirst->_t_mapsize > 0 && cpt_dequesecond->_t_mapsize > 0);

    if(cpt_dequefirst->_t_typesize != cpt_dequesecond->_t_typesize ||
       strncmp(cpt_dequefirst->_sz_typename, cpt_dequesecond->_sz_typename,
           _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }

    if(cpt_dequefirst->_pfun_cmp != cpt_dequesecond->_pfun_cmp)
    {
        return false;
    }

    if(deque_size(cpt_dequefirst) != deque_size(cpt_dequesecond))
    {
        return false;
    }

    if(cpt_dequefirst->_pfun_cmp != NULL)
    {
        for(t_first = cpt_dequefirst->_t_start,
            t_second = cpt_dequesecond->_t_start;
            !iterator_equal(t_first, cpt_dequefirst->_t_finish) &&
            !iterator_equal(t_second, cpt_dequesecond->_t_finish);
            t_first = iterator_next(t_first),
            t_second = iterator_next(t_second))
        {
            if((*cpt_dequefirst->_pfun_cmp)(
                _GET_DEQUE_COREPOS(t_first), _GET_DEQUE_COREPOS(t_second)) != 0)
            {
                return false;
            }
        }
    }
    else
    {
        for(t_first = cpt_dequefirst->_t_start,
            t_second = cpt_dequesecond->_t_start;
            !iterator_equal(t_first, cpt_dequefirst->_t_finish) &&
            !iterator_equal(t_second, cpt_dequesecond->_t_finish);
            t_first = iterator_next(t_first),
            t_second = iterator_next(t_second))
        {
            if(memcmp(_GET_DEQUE_COREPOS(t_first), _GET_DEQUE_COREPOS(t_second),
                cpt_dequefirst->_t_typesize) != 0)
            {
                return false;
            }
        }
    }
    assert(iterator_equal(t_first, cpt_dequefirst->_t_finish) &&
           iterator_equal(t_second, cpt_dequesecond->_t_finish));

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
    int              n_cmpresult = 0;

    assert(_same_deque_type(cpt_dequefirst, cpt_dequesecond));

    if(cpt_dequefirst->_pfun_cmp != NULL)
    {
        for(t_first = cpt_dequefirst->_t_start,
            t_second = cpt_dequesecond->_t_start;
            !iterator_equal(t_first, cpt_dequefirst->_t_finish) &&
            !iterator_equal(t_second, cpt_dequesecond->_t_finish);
            t_first = iterator_next(t_first),
            t_second = iterator_next(t_second))
        {
            n_cmpresult = (*cpt_dequefirst->_pfun_cmp)(
                _GET_DEQUE_COREPOS(t_first), _GET_DEQUE_COREPOS(t_second));
            if(n_cmpresult < 0)
            {
                return true;
            }
            else if(n_cmpresult > 0)
            {
                return false;
            }
        }
    }
    else
    {
        for(t_first = cpt_dequefirst->_t_start,
            t_second = cpt_dequesecond->_t_start;
            !iterator_equal(t_first, cpt_dequefirst->_t_finish) &&
            !iterator_equal(t_second, cpt_dequesecond->_t_finish);
            t_first = iterator_next(t_first),
            t_second = iterator_next(t_second))
        {
            n_cmpresult = memcmp(
                _GET_DEQUE_COREPOS(t_first), _GET_DEQUE_COREPOS(t_second),
                cpt_dequefirst->_t_typesize);
            if(n_cmpresult < 0)
            {
                return true;
            }
            else if(n_cmpresult > 0)
            {
                return false;
            }
        }
    }
    if(iterator_equal(t_first, cpt_dequefirst->_t_finish) &&
       !iterator_equal(t_second, cpt_dequesecond->_t_finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t deque_less_equal(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    return deque_less(cpt_dequefirst, cpt_dequesecond) ||
           deque_equal(cpt_dequefirst, cpt_dequesecond);
}

bool_t deque_great(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    return deque_less(cpt_dequesecond, cpt_dequefirst);
}

bool_t deque_great_equal(const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    return deque_great(cpt_dequefirst, cpt_dequesecond) ||
           deque_equal(cpt_dequefirst, cpt_dequesecond);
}

void* deque_at(const deque_t* cpt_deque, size_t t_pos)
{
    deque_iterator_t t_iterator;

    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL && cpt_deque->_t_mapsize > 0);
    assert(t_pos < deque_size(cpt_deque));

    t_iterator = cpt_deque->_t_start;
    t_iterator = iterator_next_n(t_iterator, t_pos);
    assert(_iterator_belong_to_deque(cpt_deque, t_iterator));

    return _GET_DEQUE_COREPOS(t_iterator);
}

void deque_swap(deque_t* pt_dequefirst, deque_t* pt_dequesecond)
{
    deque_t t_dequetmp;

    assert(_same_deque_type(pt_dequefirst, pt_dequesecond));

    t_dequetmp = *pt_dequefirst;
    *pt_dequefirst = *pt_dequesecond;
    *pt_dequesecond = t_dequetmp;

    /* the pointer to container must not be swap */
    _GET_CONTAINER(pt_dequefirst->_t_start) = pt_dequefirst;
    _GET_CONTAINER(pt_dequefirst->_t_finish) = pt_dequefirst;

    _GET_CONTAINER(pt_dequesecond->_t_start) = pt_dequesecond;
    _GET_CONTAINER(pt_dequesecond->_t_finish) = pt_dequesecond;
}

void _deque_push_back(deque_t* pt_deque, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_deque);
    _deque_push_back_varg(pt_deque, val_elemlist);
}

void deque_pop_back(deque_t* pt_deque)
{
    assert(deque_size(pt_deque) > 0);

    _shrink_at_back(pt_deque, 1);
}

void _deque_push_front(deque_t* pt_deque, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_deque);
    _deque_push_front_varg(pt_deque, val_elemlist);
}

void _deque_push_front_varg(deque_t* pt_deque, va_list val_elemlist)
{
    _expand_at_front(pt_deque, 1, NULL);
    _get_varg_value(
        _GET_DEQUE_COREPOS(pt_deque->_t_start), val_elemlist,
        pt_deque->_t_typesize, pt_deque->_sz_typename);
}

void deque_pop_front(deque_t* pt_deque)
{
    assert(deque_size(pt_deque) > 0);

    _shrink_at_front(pt_deque, 1);
}

deque_iterator_t _deque_insert_n(
    deque_t* pt_deque, deque_iterator_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    return _deque_insert_n_varg(pt_deque, t_pos, t_count, val_elemlist);
}

deque_iterator_t _deque_insert_n_varg(
    deque_t* pt_deque, deque_iterator_t t_pos, size_t t_count, va_list val_elemlist)
{
    deque_iterator_t t_result;
    void*            pv_init_elem = NULL;

    assert(_iterator_belong_to_deque(pt_deque, t_pos));

    /* get varg value only once */
    pv_init_elem = allocate(&pt_deque->_t_allocater, pt_deque->_t_typesize, 1);
    assert(pv_init_elem != NULL);
    _get_varg_value(
        pv_init_elem, val_elemlist, pt_deque->_t_typesize, pt_deque->_sz_typename);

    /* if the element number after insert pos is little 
     * then insert in front */
    if(iterator_distance(deque_begin(pt_deque), t_pos) < (int)deque_size(pt_deque)/2)
    {
        deque_iterator_t t_oldfront;
        deque_iterator_t t_gap;

        /* expand one element at front */
        t_oldfront = _expand_at_front(pt_deque, t_count, &t_pos);
        /* move the element range [oldfront, pos) to [newfront, pos) */
        t_result = t_gap = _move_elem_to_front(pt_deque, t_oldfront, t_pos, t_count);
        assert(iterator_distance(t_gap, t_pos) == (int)t_count);

        for(; !iterator_equal(t_gap, t_pos); t_gap = iterator_next(t_gap))
        {
            memcpy(_GET_DEQUE_COREPOS(t_gap), pv_init_elem, pt_deque->_t_typesize);
        }
        assert(iterator_equal(t_gap, t_pos));
    }
    /* else insert in back */
    else
    {
        size_t t_index = 0;
        deque_iterator_t t_oldend = _expand_at_back(pt_deque, t_count, &t_pos);
        deque_iterator_t t_gap = _move_elem_to_back(pt_deque, t_pos, t_oldend, t_count);
        t_result = t_gap;

        assert(iterator_equal(t_pos, t_gap));

        for(t_index = 0; t_index < t_count; ++t_index)
        {
            memcpy(_GET_DEQUE_COREPOS(t_pos), pv_init_elem, pt_deque->_t_typesize);
            t_pos = iterator_next(t_pos);
        }
    }
    deallocate(&pt_deque->_t_allocater, pv_init_elem, pt_deque->_t_typesize, 1);

    return t_result;
}

void deque_insert_range(
    deque_t* pt_deque, deque_iterator_t t_pos, 
    deque_iterator_t t_begin, deque_iterator_t t_end)
{
#ifdef NDEBUG
    deque_iterator_t t_avoidwarning;
#endif

    int n_elemcount = 0;

    assert(_iterator_belong_to_deque(pt_deque, t_pos));
    assert(_same_deque_iterator_type(pt_deque, t_begin));
    assert(iterator_equal(t_begin, t_end) || _deque_iterator_before(t_begin, t_end));

    n_elemcount = iterator_distance(t_begin, t_end);
    /* if the element number after insert pos is little 
     * then insert in front */
    if(iterator_distance(deque_begin(pt_deque), t_pos) < (int)deque_size(pt_deque)/2)
    {
        deque_iterator_t t_oldfront;
        deque_iterator_t t_gap;

        /* expand one element at front */
        t_oldfront = _expand_at_front(pt_deque, n_elemcount, &t_pos);
        /* move the element range [oldfront, pos) to [newfront, pos) */
        t_gap = _move_elem_to_front(pt_deque, t_oldfront, t_pos, n_elemcount);
        assert(iterator_distance(t_gap, t_pos) == n_elemcount);

        for(;
            iterator_less(t_gap, t_pos) && iterator_less(t_begin, t_end); 
            t_gap = iterator_next(t_gap), t_begin = iterator_next(t_begin))
        {
            memcpy(_GET_DEQUE_COREPOS(t_gap), _GET_DEQUE_COREPOS(t_begin),
                   pt_deque->_t_typesize);
        }
        assert(iterator_equal(t_gap, t_pos) && iterator_equal(t_begin, t_end));
    }
    /* else insert in back */
    else
    {
        int i = 0;
        deque_iterator_t t_oldend = _expand_at_back(pt_deque, n_elemcount, &t_pos);
        deque_iterator_t t_gap = 
            _move_elem_to_back(pt_deque, t_pos, t_oldend, n_elemcount);
#ifdef NDEBUG
        t_avoidwarning = t_gap;
#endif

        assert(iterator_equal(t_pos, t_gap));

        for(i = 0; 
            i < n_elemcount && iterator_less(t_begin, t_end); 
            ++i, t_begin = iterator_next(t_begin))
        {
            memcpy(_GET_DEQUE_COREPOS(t_pos), _GET_DEQUE_COREPOS(t_begin),
                   pt_deque->_t_typesize);
            t_pos = iterator_next(t_pos);
        }
    }
}

deque_iterator_t deque_erase(deque_t* pt_deque, deque_iterator_t t_pos)
{
    assert(_iterator_belong_to_deque(pt_deque, t_pos));

    if(iterator_equal(t_pos, deque_begin(pt_deque)))
    {
        deque_pop_front(pt_deque);
        return deque_begin(pt_deque);
    }
    else if(iterator_equal(t_pos, deque_end(pt_deque)))
    {
        deque_pop_back(pt_deque);
        return deque_end(pt_deque);
    }
    else
    {
        deque_iterator_t t_result = t_pos;

        t_pos = iterator_next(t_pos);
        _move_elem_to_front(pt_deque, t_pos, deque_end(pt_deque), 1);
        _shrink_at_back(pt_deque, 1);

        return t_result;
    }
}

deque_iterator_t deque_erase_range(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end)
{
    assert(_iterator_belong_to_deque(pt_deque, t_begin));
    assert(iterator_equal(t_begin, t_end) || _deque_iterator_before(t_begin, t_end));

    _move_elem_to_front(
        pt_deque, t_end, deque_end(pt_deque), iterator_distance(t_begin, t_end));
    _shrink_at_back(pt_deque, iterator_distance(t_begin, t_end));

    return t_begin;
}

void deque_resize(deque_t* pt_deque, size_t t_resize)
{
    deque_resize_elem(pt_deque, t_resize, 0x00);
}

void _deque_resize_elem(deque_t* pt_deque, size_t t_resize, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_resize);
    _deque_resize_elem_varg(pt_deque, t_resize, val_elemlist);
}

void _deque_resize_elem_varg(deque_t* pt_deque, size_t t_resize, va_list val_elemlist)
{
    void* pv_init_elem = NULL;

    if(t_resize < deque_size(pt_deque))
    {
        _shrink_at_back(pt_deque, deque_size(pt_deque) - t_resize);
    }
    else if(t_resize > deque_size(pt_deque))
    {
        deque_iterator_t t_oldend = 
            _expand_at_back(pt_deque, t_resize - deque_size(pt_deque), NULL);

        /* get varg value only once */
        pv_init_elem = allocate(&pt_deque->_t_allocater, pt_deque->_t_typesize, 1);
        assert(pv_init_elem != NULL);
        _get_varg_value(
            pv_init_elem, val_elemlist, pt_deque->_t_typesize, pt_deque->_sz_typename);
        for(;
            !iterator_equal(t_oldend, deque_end(pt_deque)); 
            t_oldend = iterator_next(t_oldend))
        {
            memcpy(_GET_DEQUE_COREPOS(t_oldend), pv_init_elem, pt_deque->_t_typesize);
        }
        deallocate(&pt_deque->_t_allocater, pv_init_elem, pt_deque->_t_typesize, 1);
    }
}

void deque_clear(deque_t* pt_deque)
{
    deque_erase_range(pt_deque, deque_begin(pt_deque), deque_end(pt_deque));
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _iterator_belong_to_deque(
    const deque_t* cpt_deque, deque_iterator_t t_iter)
{
    deque_iterator_t t_cur = create_deque_iterator();
    char*            pc_startpos = NULL;
    char*            pc_finishpos = NULL;

    /* test deque and deque map */
    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL && cpt_deque->_t_mapsize > 0);
    /* test start and finish iterator */
    assert(_GET_DEQUE_MAP_POINTER(cpt_deque->_t_start) != NULL &&
           _GET_DEQUE_FIRST_POS(cpt_deque->_t_start) != NULL &&
           _GET_DEQUE_AFTERLAST_POS(cpt_deque->_t_start) != NULL &&
           _GET_DEQUE_COREPOS(cpt_deque->_t_start) != NULL);
    assert(_GET_DEQUE_MAP_POINTER(cpt_deque->_t_finish) != NULL &&
           _GET_DEQUE_FIRST_POS(cpt_deque->_t_finish) != NULL &&
           _GET_DEQUE_AFTERLAST_POS(cpt_deque->_t_finish) != NULL &&
           _GET_DEQUE_COREPOS(cpt_deque->_t_finish) != NULL);
   
    /* the the map pointer is valid */
    for(_GET_DEQUE_MAP_POINTER(t_cur) = _GET_DEQUE_MAP_POINTER(cpt_deque->_t_start);
        _GET_DEQUE_MAP_POINTER(t_cur) <= _GET_DEQUE_MAP_POINTER(cpt_deque->_t_finish);
        _GET_DEQUE_MAP_POINTER(t_cur) += 1)
    {
        if(_GET_DEQUE_MAP_POINTER(t_cur) == _GET_DEQUE_MAP_POINTER(t_iter))
        {
            _GET_DEQUE_FIRST_POS(t_cur) = *_GET_DEQUE_MAP_POINTER(t_cur);
            _GET_DEQUE_AFTERLAST_POS(t_cur) = 
                _GET_DEQUE_FIRST_POS(t_cur) + cpt_deque->_t_typesize * _DEQUE_ELEM_COUNT;
            break;
        }
    }
    if(_GET_DEQUE_FIRST_POS(t_cur) == NULL)
    {
        return false;
    }

    /* test the iterator in suti with the map node */
    assert(_GET_DEQUE_FIRST_POS(t_cur) == _GET_DEQUE_FIRST_POS(t_iter) &&
           _GET_DEQUE_AFTERLAST_POS(t_cur) == _GET_DEQUE_AFTERLAST_POS(t_iter));

    /* test the element pointer is valid */
    /* 
     * if the current pos equal begin pos 
     * +-----------------------------------------+
     * |first|  ... ... | corepos | ... data ... | afterlast
     * +-----------------------------------------+
     * or corepos == afterlast
     */
    if(_GET_DEQUE_MAP_POINTER(t_cur) == _GET_DEQUE_MAP_POINTER(cpt_deque->_t_start))
    {
        /* the begin pointer point to afterlast and the t_cur is begin */
        if(_GET_DEQUE_COREPOS(cpt_deque->_t_start) ==
           _GET_DEQUE_AFTERLAST_POS(cpt_deque->_t_start))
        {
            if(_GET_DEQUE_COREPOS(t_iter) == _GET_DEQUE_AFTERLAST_POS(t_iter))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        /* in begin container and the begin pointer not point to afterlast */
        else
        {
            pc_startpos = _GET_DEQUE_COREPOS(cpt_deque->_t_start);
            pc_finishpos = _GET_DEQUE_AFTERLAST_POS(cpt_deque->_t_start) - 
                           cpt_deque->_t_typesize;
        }
    }
    /* if the current pos equal end pos 
     * +------------------------------------------+
     * |first|  ... data ... | corepos | ...  ... | afterlast
     * +------------------------------------------+
     */
    else if(_GET_DEQUE_MAP_POINTER(t_cur) == _GET_DEQUE_MAP_POINTER(cpt_deque->_t_finish))
    {
        pc_startpos = _GET_DEQUE_FIRST_POS(cpt_deque->_t_finish);
        pc_finishpos = _GET_DEQUE_COREPOS(cpt_deque->_t_finish);
    }
    else
    {
        pc_startpos = _GET_DEQUE_FIRST_POS(t_cur);
        pc_finishpos = _GET_DEQUE_AFTERLAST_POS(t_cur) - cpt_deque->_t_typesize;
    }

    for(_GET_DEQUE_COREPOS(t_cur) = pc_startpos;
        _GET_DEQUE_COREPOS(t_cur) <= pc_finishpos;
        _GET_DEQUE_COREPOS(t_cur) += cpt_deque->_t_typesize)
    {
        if(_GET_DEQUE_COREPOS(t_cur) == _GET_DEQUE_COREPOS(t_iter))
        {
            return true;
        }
    }

    return false;
}

static bool_t _same_deque_iterator_type(
    const deque_t* cpt_deque, deque_iterator_t t_iter)
{
    assert(cpt_deque != NULL && cpt_deque->_ppc_map != NULL &&cpt_deque->_t_mapsize > 0);
    assert(_GET_DEQUE_CONTAINER(t_iter) != NULL);
    assert(_GET_DEQUE_CONTAINER_TYPE(t_iter) == _DEQUE_CONTAINER &&
           _GET_DEQUE_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR);
    assert(cpt_deque->_t_typesize == _GET_DEQUE_CONTAINER(t_iter)->_t_typesize &&
           strncmp(cpt_deque->_sz_typename, _GET_DEQUE_CONTAINER(t_iter)->_sz_typename,
                _ELEM_TYPE_NAME_SIZE) == 0);
    assert(cpt_deque->_pfun_cmp == _GET_DEQUE_CONTAINER(t_iter)->_pfun_cmp);

    return true;
}

static bool_t _same_deque_type(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    assert(cpt_dequefirst != NULL && cpt_dequesecond != NULL &&
           cpt_dequefirst->_ppc_map != NULL && cpt_dequesecond->_ppc_map != NULL &&
           cpt_dequefirst->_t_mapsize > 0 && cpt_dequesecond->_t_mapsize > 0);
    assert(cpt_dequefirst->_pfun_cmp == cpt_dequesecond->_pfun_cmp);
    assert(cpt_dequefirst->_t_typesize == cpt_dequesecond->_t_typesize &&
           strncmp(cpt_dequefirst->_sz_typename, cpt_dequesecond->_sz_typename,
                   _ELEM_TYPE_NAME_SIZE) == 0);

    return true;
}
#endif /* NDEBUG */

static deque_iterator_t _expand_at_back(
    deque_t* pt_deque, size_t t_expandsize, deque_iterator_t* pt_pos)
{
    deque_iterator_t t_oldend = pt_deque->_t_finish;
    size_t           t_remainsize = 0; /* the remain size in last container */

    /* if the capacity of last container is enough for expand size */
    t_remainsize = (_GET_DEQUE_AFTERLAST_POS(t_oldend) -
                    _GET_DEQUE_COREPOS(t_oldend)) /
                    pt_deque->_t_typesize;
    if(t_expandsize < t_remainsize)
    {
        /* set the new end iterator */
        _GET_DEQUE_COREPOS(pt_deque->_t_finish) += t_expandsize * pt_deque->_t_typesize;
    }
    else
    {
        size_t t_nomemsize = 0;        /* the size that they have no memory */
        size_t t_containersize = 0;    /* the container for new element */
        size_t t_validendsize = 0;     /* the valid size in end container */
        size_t t_remainendmapsize = 0; /* the remain space at the map end */
        size_t t_remainmapsize = 0;    /* the remain space in the map */
        char** ppc_newcontainer = NULL;/* the pointer to new container */
        int    i = 0;

        /* caculate the expand container number */
        t_nomemsize = t_expandsize - t_remainsize;
        t_containersize = (t_nomemsize + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT;
        t_validendsize = t_nomemsize % _DEQUE_ELEM_COUNT;
        if(t_validendsize == 0)
        {
            t_containersize++;
        }

        t_remainendmapsize = (pt_deque->_ppc_map + pt_deque->_t_mapsize) - 
                             _GET_DEQUE_MAP_POINTER(t_oldend) - 1;
        t_remainmapsize = pt_deque->_t_mapsize - 
                          (_GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -
                           _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + 1);

        /* if container remain space is not enough for expand size
         * then grow the map for expand container */
        if(t_containersize > t_remainmapsize)
        {
            size_t t_validmapsize = 
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + 1;
            int n_newmapstartpos = 0;
            int n_oldmapstartpos = (pt_deque->_t_mapsize - t_validmapsize) / 2;
            /* the distance of pt_pos and map */
            int n_posdistance = 0;
            /* grow size multiple of eight */
            size_t t_growsize = 
                (t_containersize - t_remainmapsize + _DEQUE_MAP_GROW_STEP - 1)/
                _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
            /* save the old map */
            _mappointer_t t_oldmap = pt_deque->_ppc_map;
            size_t t_oldmapsize = pt_deque->_t_mapsize;

            /* new map */
            pt_deque->_t_mapsize += t_growsize;
            pt_deque->_ppc_map = allocate(
                &pt_deque->_t_allocater, sizeof(char*), pt_deque->_t_mapsize);
            assert(pt_deque->_ppc_map != NULL);
            memset(pt_deque->_ppc_map, 0x00, sizeof(char*)*pt_deque->_t_mapsize);

            /* copy the container pointer from old map to new map */
            n_newmapstartpos = 
                (pt_deque->_t_mapsize - (t_validmapsize + t_containersize)) / 2;
            memcpy(
                pt_deque->_ppc_map + n_newmapstartpos, t_oldmap + n_oldmapstartpos, 
                sizeof(char*) * t_validmapsize);
            /* get the pt_pos distance */
            if(pt_pos != NULL)
            {
                n_posdistance = 
                    _GET_DEQUE_MAP_POINTER(*pt_pos) - 
                    _GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
            }
            /* reset the start, finish and old front iterator */
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) = 
                pt_deque->_ppc_map + n_newmapstartpos;
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) = 
                pt_deque->_ppc_map + n_newmapstartpos + t_validmapsize - 1;
            _GET_DEQUE_MAP_POINTER(t_oldend) = 
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish);
            /** modify pt_pos **/
            if(pt_pos != NULL)
            {
                _GET_DEQUE_MAP_POINTER(*pt_pos) = 
                    _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + n_posdistance;
            }
            deallocate(&pt_deque->_t_allocater, t_oldmap, sizeof(char*), t_oldmapsize);
        }
        /* else if the container remain space is enough for expand size */
        else if(t_containersize > t_remainendmapsize && 
                t_containersize <= t_remainmapsize)
        {
            /* old vaild container count in old map */
            size_t t_oldvalidmapsize = 
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + 1;
            /* the valid container count in new map */
            size_t t_newvalidmapsize = t_oldvalidmapsize + t_containersize;
            /* the old container start pos in old map */
            size_t t_oldstartpossize = (pt_deque->_t_mapsize - t_oldvalidmapsize) / 2;
            /* the container start pos in new map */
            size_t t_newstartpossize = (pt_deque->_t_mapsize - t_newvalidmapsize) / 2;
            /* the distance of move */
            size_t t_movesize = t_oldstartpossize - t_newstartpossize;
            /* move the valid container pointer in map */
            memmove(
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) - t_movesize,
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start),
                sizeof(char*) * t_oldvalidmapsize);
            /* reset the start, finish and oldend iterator */
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) -= t_movesize;
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -= t_movesize;
            _GET_DEQUE_MAP_POINTER(t_oldend) -= t_movesize;
            if(pt_pos != NULL)
            {
                _GET_DEQUE_MAP_POINTER(*pt_pos) -= t_movesize;
            }
        }

        /* allocate the container */
        for(i = 0, ppc_newcontainer = _GET_DEQUE_MAP_POINTER(t_oldend) + 1;
            i < (int)t_containersize; 
            ++i, ++ppc_newcontainer)
        {
            *ppc_newcontainer = allocate(
                &pt_deque->_t_allocater, pt_deque->_t_typesize, _DEQUE_ELEM_COUNT);
            assert(*ppc_newcontainer != NULL);
        }

        /* set new end iterator */
        _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) = 
            _GET_DEQUE_MAP_POINTER(t_oldend) + t_containersize;
        _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) = 
            *_GET_DEQUE_MAP_POINTER(pt_deque->_t_finish);
        _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_finish) = 
            _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) + 
            _DEQUE_ELEM_COUNT * pt_deque->_t_typesize;
        _GET_DEQUE_COREPOS(pt_deque->_t_finish) = 
            _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) + 
            t_validendsize * pt_deque->_t_typesize;
    }

    return t_oldend;
}

static deque_iterator_t _expand_at_front(
    deque_t* pt_deque, size_t t_expandsize, deque_iterator_t* pt_pos)
{
    deque_iterator_t t_oldfront = pt_deque->_t_start;
    size_t           t_remainsize = 0; /* the remain size in first container */

    /* if the capacity of first container is enough for expand size */
    t_remainsize = 
       (_GET_DEQUE_COREPOS(t_oldfront) - _GET_DEQUE_FIRST_POS(t_oldfront)) /
       pt_deque->_t_typesize;
    if(t_expandsize < t_remainsize)
    {
        /* set the new begin iterator */
        _GET_DEQUE_COREPOS(pt_deque->_t_start) -= t_expandsize * pt_deque->_t_typesize;
    }
    else
    {
        size_t t_nomemsize = 0;        /* the size that they have no memory */
        size_t t_containersize = 0;    /* the container for new element */
        size_t t_validfrontsize = 0;     /* the valid size in front container */
        size_t t_remainfrontmapsize = 0; /* the remain space at the map begin */
        size_t t_remainmapsize = 0;    /* the remain space in the map */
        char** ppc_newcontainer = NULL;/* the pointer to new container */
        int    i = 0;

        /* caculate the expand container number */
        t_nomemsize = t_expandsize - t_remainsize;
        t_containersize = (t_nomemsize + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT;
        t_validfrontsize = t_nomemsize % _DEQUE_ELEM_COUNT;
        if(t_validfrontsize == 0)
        {
            t_containersize++;
        }

        t_remainfrontmapsize = 
            _GET_DEQUE_MAP_POINTER(t_oldfront) - pt_deque->_ppc_map;
        t_remainmapsize = 
            pt_deque->_t_mapsize - 
            (_GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -
             _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + 1);

        /* if container remain space is not enough for expand size
         * then grow the map for expand container */
        if(t_containersize > t_remainmapsize)
        {
            size_t t_validmapsize = 
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + 1;
            int n_newmapstartpos = 0;
            int n_oldmapstartpos = (pt_deque->_t_mapsize - t_validmapsize) / 2;
            int n_newposofoldcontainer = 0;
            /* the distance of pt_pos and map */
            int n_posdistance = 0;
            /* grow size multiple of eight */
            size_t t_growsize = 
                (t_containersize - t_remainmapsize + _DEQUE_MAP_GROW_STEP - 1)/
                _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
            /* old map */
            _mappointer_t t_oldmap = pt_deque->_ppc_map;
            size_t t_oldmapsize = pt_deque->_t_mapsize;

            /* new map */
            pt_deque->_t_mapsize += t_growsize;
            pt_deque->_ppc_map = allocate(
                &pt_deque->_t_allocater, sizeof(char*), pt_deque->_t_mapsize);
            assert(pt_deque->_ppc_map != NULL);
            memset(pt_deque->_ppc_map, 0x00, sizeof(char*)*pt_deque->_t_mapsize);

            /* copy the container pointer from old map to new map */
            n_newmapstartpos = 
                (pt_deque->_t_mapsize - (t_validmapsize + t_containersize)) / 2; 
            n_newposofoldcontainer = n_newmapstartpos + t_containersize;
            memcpy(
                pt_deque->_ppc_map + n_newposofoldcontainer, t_oldmap + n_oldmapstartpos,
                sizeof(char*) * t_validmapsize);
            /* get the pt_pos distance */
            if(pt_pos != NULL)
            {
                n_posdistance = 
                    _GET_DEQUE_MAP_POINTER(*pt_pos) - 
                    _GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
            }
            /* reset the start, finish and old front iterator */
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) = 
                pt_deque->_ppc_map + n_newposofoldcontainer;
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) = 
                pt_deque->_ppc_map + n_newposofoldcontainer + 
                t_validmapsize - 1;
            _GET_DEQUE_MAP_POINTER(t_oldfront) = 
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
            /** modify pt_pos **/
            if(pt_pos != NULL)
            {
                _GET_DEQUE_MAP_POINTER(*pt_pos) =
                    _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + n_posdistance;
            }
            deallocate(
                &pt_deque->_t_allocater, t_oldmap, sizeof(char*), t_oldmapsize);
        }
        /* else if the container remain space is enough for expand size */
        else if(t_containersize > t_remainfrontmapsize && 
                t_containersize <= t_remainmapsize)
        {
            /* old vaild container count in old map */
            size_t t_oldvalidmapsize = 
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + 1;
            /* the valid container count in new map */
            size_t t_newvalidmapsize = t_oldvalidmapsize + t_containersize;
            /* the old container start pos in old map */
            size_t t_oldstartpossize = (pt_deque->_t_mapsize - t_oldvalidmapsize) / 2;
            /* the container start pos in new map */
            size_t t_newstartpossize = (pt_deque->_t_mapsize - t_newvalidmapsize) / 2;
            /* the old container in new map pos */
            size_t t_newposofoldcontainer = t_newstartpossize + t_containersize;
            /* the distance of move */
            size_t t_movesize = t_newposofoldcontainer - t_oldstartpossize;
            /* move the valid container pointer in map */
            memmove(
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + t_movesize,
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start),
                sizeof(char*) * t_oldvalidmapsize);
            /* reset the start, finish and oldend iterator */
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) += t_movesize;
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) += t_movesize;
            _GET_DEQUE_MAP_POINTER(t_oldfront) += t_movesize;
            if(pt_pos != NULL)
            {
                _GET_DEQUE_MAP_POINTER(*pt_pos) += t_movesize;
            }
        }

        /* allocate the container */
        for(i = 0, ppc_newcontainer = _GET_DEQUE_MAP_POINTER(t_oldfront) - 1;
            i < (int)t_containersize; 
            ++i, --ppc_newcontainer)
        {
            *ppc_newcontainer = allocate(
                &pt_deque->_t_allocater, pt_deque->_t_typesize, _DEQUE_ELEM_COUNT);
            assert(*ppc_newcontainer != NULL);
        }

        /* set new start iterator */
        _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) = 
            _GET_DEQUE_MAP_POINTER(t_oldfront) - t_containersize;
        _GET_DEQUE_FIRST_POS(pt_deque->_t_start) = 
            *_GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
        _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start) = 
            _GET_DEQUE_FIRST_POS(pt_deque->_t_start) + 
            _DEQUE_ELEM_COUNT * pt_deque->_t_typesize;
        _GET_DEQUE_COREPOS(pt_deque->_t_start) = 
            _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start) - 
            t_validfrontsize * pt_deque->_t_typesize;
    }

    /* the old front is original front */
    if(_GET_DEQUE_COREPOS(t_oldfront) == _GET_DEQUE_AFTERLAST_POS(t_oldfront))
    {
        assert(*(_GET_DEQUE_MAP_POINTER(t_oldfront) + 1) != NULL);
        _GET_DEQUE_MAP_POINTER(t_oldfront) += 1;
        _GET_DEQUE_FIRST_POS(t_oldfront) = 
            *_GET_DEQUE_MAP_POINTER(t_oldfront);
        _GET_DEQUE_AFTERLAST_POS(t_oldfront) = 
            _GET_DEQUE_FIRST_POS(t_oldfront) + 
            _DEQUE_ELEM_COUNT * pt_deque->_t_typesize;
        _GET_DEQUE_COREPOS(t_oldfront) = 
            _GET_DEQUE_FIRST_POS(t_oldfront);
    }
    if(pt_pos != NULL &&
       _GET_DEQUE_COREPOS(*pt_pos) == _GET_DEQUE_AFTERLAST_POS(*pt_pos))
    {
        assert(*(_GET_DEQUE_MAP_POINTER(*pt_pos) + 1) != NULL);
        _GET_DEQUE_MAP_POINTER(*pt_pos) += 1;
        _GET_DEQUE_FIRST_POS(*pt_pos) = 
            *_GET_DEQUE_MAP_POINTER(*pt_pos);
        _GET_DEQUE_AFTERLAST_POS(*pt_pos) = 
            _GET_DEQUE_FIRST_POS(*pt_pos) + 
            _DEQUE_ELEM_COUNT * pt_deque->_t_typesize;
        _GET_DEQUE_COREPOS(*pt_pos) = 
            _GET_DEQUE_FIRST_POS(*pt_pos);
    }

    return t_oldfront;
}

static void _shrink_at_back(deque_t* pt_deque, size_t t_shrinksize)
{
    deque_iterator_t t_oldend = pt_deque->_t_finish;
    _mappointer_t    ppc_map = NULL;

    t_shrinksize = 
        t_shrinksize < deque_size(pt_deque) ? t_shrinksize : deque_size(pt_deque);
    pt_deque->_t_finish = iterator_prev_n(pt_deque->_t_finish, t_shrinksize);
    assert(_iterator_belong_to_deque(pt_deque, pt_deque->_t_finish));

    for(ppc_map = _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) + 1;
        ppc_map <= _GET_DEQUE_MAP_POINTER(t_oldend);
        ++ppc_map)
    {
        deallocate(
            &pt_deque->_t_allocater, *ppc_map, pt_deque->_t_typesize, _DEQUE_ELEM_COUNT);
        *ppc_map = NULL;
    }
}

static void _shrink_at_front(deque_t* pt_deque, size_t t_shrinksize)
{
    deque_iterator_t t_oldfront = pt_deque->_t_start;
    _mappointer_t    ppc_map = NULL;

    t_shrinksize = 
        t_shrinksize < deque_size(pt_deque) ? t_shrinksize : deque_size(pt_deque);
    pt_deque->_t_start = iterator_next_n(pt_deque->_t_start, t_shrinksize);
    assert(_iterator_belong_to_deque(pt_deque, pt_deque->_t_start));

    for(ppc_map = _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) - 1;
        ppc_map >= _GET_DEQUE_MAP_POINTER(t_oldfront);
        --ppc_map)
    {
        deallocate(
            &pt_deque->_t_allocater, *ppc_map, pt_deque->_t_typesize, _DEQUE_ELEM_COUNT);
        *ppc_map = NULL;
    }
}

static deque_iterator_t _move_elem_to_back(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end, size_t t_movesize)
{
    /* if t_begin != t_end then do move */
    if(!iterator_equal(t_begin, t_end))
    {
        /* the target range of move */
        deque_iterator_t t_targetbegin;
        deque_iterator_t t_targetend;

        assert(_iterator_belong_to_deque(pt_deque, t_begin));
        assert(_deque_iterator_before(t_begin, t_end));

        t_targetbegin = t_begin;
        t_targetend = t_end;
        t_targetbegin = iterator_next_n(t_targetbegin, t_movesize);
        t_targetend = iterator_next_n(t_targetend, t_movesize);
        assert(_deque_iterator_before(t_targetbegin, t_targetend));

        for(t_targetend = iterator_prev(t_targetend), t_end = iterator_prev(t_end);
            !iterator_less(t_targetend, t_targetbegin) && !iterator_less(t_end, t_begin);
            t_targetend = iterator_prev(t_targetend), t_end = iterator_prev(t_end))
        {
            memcpy(_GET_DEQUE_COREPOS(t_targetend), _GET_DEQUE_COREPOS(t_end),
                   pt_deque->_t_typesize);
        }

        t_targetend = iterator_next(t_targetend);
        t_end = iterator_next(t_end);
        assert(iterator_equal(t_begin, t_end) && 
               iterator_equal(t_targetbegin, t_targetend));
    }

    return t_begin;
}

static deque_iterator_t _move_elem_to_front(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end, size_t t_movesize)
{
    if(!iterator_equal(t_begin, t_end))
    {
        deque_iterator_t t_targetbegin;
        deque_iterator_t t_targetend;

        assert(_iterator_belong_to_deque(pt_deque, t_begin));
        assert(_deque_iterator_before(t_begin, t_end));

        t_targetbegin = t_begin;
        t_targetend = t_end;
        t_targetbegin = iterator_prev_n(t_targetbegin, t_movesize);
        t_targetend = iterator_prev_n(t_targetend, t_movesize);
        assert(_deque_iterator_before(t_targetbegin, t_targetend));

        for(;
            iterator_less(t_targetbegin, t_targetend) && iterator_less(t_begin, t_end);
            t_targetbegin = iterator_next(t_targetbegin), t_begin = iterator_next(t_begin))
        {
            memcpy(_GET_DEQUE_COREPOS(t_targetbegin), _GET_DEQUE_COREPOS(t_begin),
                   pt_deque->_t_typesize);
        }

        assert(iterator_equal(t_targetbegin, t_targetend) &&
               iterator_equal(t_begin, t_end));

        return t_targetend;
    }
    else
    {
        t_end = iterator_prev_n(t_end, t_movesize);
        return t_end;
    }
}

/** eof **/

