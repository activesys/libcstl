/*
 *  The implement of deque private function.
 *  Copyright (C)  2008 - 2014  Wangbo
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
 * Create deque container.
 */
deque_t* _create_deque(const char* s_typename)
{
    deque_t*    pdeq_new = NULL;

    assert(s_typename != NULL);

    /* alloc memory for deque_t */
    if ((pdeq_new = (deque_t*)malloc(sizeof(deque_t))) == NULL) {
        return NULL;
    }

    if (!_create_deque_auxiliary(pdeq_new, s_typename)) {
        free(pdeq_new);
        return NULL;
    }

    return pdeq_new;
}

/**
 * Create deque container auxiliary function.
 */
bool_t _create_deque_auxiliary(deque_t* pdeq_deque, const char* s_typename)
{
    assert(pdeq_deque != NULL);
    assert(s_typename != NULL);

    _type_get_type(&pdeq_deque->_t_typeinfo, s_typename);
    if (pdeq_deque->_t_typeinfo._t_style == _TYPE_INVALID) {
        return false;
    }

    pdeq_deque->_ppby_map = NULL;
    pdeq_deque->_t_mapsize = 0;
    pdeq_deque->_t_start = _create_deque_iterator();
    pdeq_deque->_t_finish = _create_deque_iterator();

    _alloc_init(&pdeq_deque->_t_allocator);
    return true;
}

/**
 * Initialize deque with specified element.
 */
void _deque_init_elem(deque_t* pdeq_deque, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pdeq_deque != NULL);
    assert(_deque_is_created(pdeq_deque));

    va_start(val_elemlist, t_count);
    _deque_init_elem_varg(pdeq_deque, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Initialize deque with variable argument list of specified element.
 */
void _deque_init_elem_varg(deque_t* pdeq_deque, size_t t_count, va_list val_elemlist)
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
    size_t     i = 0;
    size_t     t_startpos = 0;      /* the real map start pos */
    size_t     t_mapcount = 0;      /* the map count */
    size_t     t_validmapcount = 0; /* the valid count in map */
    size_t     t_endelemcount = 0;  /* the element count in the last container */
    void*      pv_varg = NULL;
    bool_t     b_result = false;
    iterator_t it_iter;
    iterator_t it_begin;
    iterator_t it_end;
    
    assert(pdeq_deque != NULL);
    assert(_deque_is_created(pdeq_deque));

    /* initialize the map and element container */
    if (t_count > 0) {
        /* get the element container count */
        t_validmapcount = (t_count + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT;
        t_endelemcount = t_count % _DEQUE_ELEM_COUNT;
        /* the last container has element */
        if (t_endelemcount != 0) {
            t_validmapcount += 1;
        } else { /* the last container has no element */
            t_validmapcount += 2;
        }

        if (t_validmapcount > _DEQUE_MAP_COUNT) {
            size_t t_growcount = (t_validmapcount - _DEQUE_MAP_COUNT + _DEQUE_MAP_GROW_STEP - 1) /
                _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
            t_mapcount = _DEQUE_MAP_COUNT + t_growcount;
        } else {
            t_mapcount = _DEQUE_MAP_COUNT;
        }
    } else {
        /* start and finish are empty */
        t_validmapcount = 2;
        t_endelemcount = 0;
        t_mapcount = _DEQUE_MAP_COUNT;
    }

    /* allocate memory for each chunk */
    pdeq_deque->_ppby_map = _alloc_allocate(&pdeq_deque->_t_allocator, sizeof(_byte_t*), t_mapcount);
    pdeq_deque->_t_mapsize = t_mapcount;
    assert(pdeq_deque->_ppby_map != NULL);
    memset(pdeq_deque->_ppby_map, 0x00, sizeof(_byte_t*) * t_mapcount);
    t_startpos = (t_mapcount - t_validmapcount) / 2;

    for (i = t_startpos; i < t_startpos + t_validmapcount; ++i) {
        pdeq_deque->_ppby_map[i] = _alloc_allocate(
            &pdeq_deque->_t_allocator, _GET_DEQUE_TYPE_SIZE(pdeq_deque), _DEQUE_ELEM_COUNT);
        assert(pdeq_deque->_ppby_map[i] != NULL);
    }

    /* initialize the start iterator */
    _ITERATOR_CONTAINER(pdeq_deque->_t_start) = pdeq_deque;
    _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) = pdeq_deque->_ppby_map + t_startpos;
    _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_start) = *_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start);
    _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_start) = _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_start) +
        _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_start) = _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_start);
    /* initialize the finish iterator */
    _ITERATOR_CONTAINER(pdeq_deque->_t_finish) = pdeq_deque;
    _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) = pdeq_deque->_ppby_map + t_startpos + t_validmapcount - 1;
    _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) = *_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish);
    _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_finish) = _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) +
        _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_finish) = _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) + 
        t_endelemcount * _GET_DEQUE_TYPE_SIZE(pdeq_deque);

    /* get varg value only once */
    pv_varg = _alloc_allocate(&pdeq_deque->_t_allocator, _GET_DEQUE_TYPE_SIZE(pdeq_deque), 1);
    assert(pv_varg != NULL);
    _deque_get_varg_value_auxiliary(pdeq_deque, val_elemlist, pv_varg);

    it_begin = deque_begin(pdeq_deque);
    it_end = deque_end(pdeq_deque);
    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        /* initialize all elements */
        _deque_init_elem_auxiliary(pdeq_deque, _deque_iterator_get_pointer_auxiliary(it_iter));

        /* copy element for varg value */
        b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_iter), pv_varg, &b_result);
        assert(b_result);
    }

    _deque_destroy_varg_value_auxiliary(pdeq_deque, pv_varg);
    _alloc_deallocate(&pdeq_deque->_t_allocator, pv_varg, _GET_DEQUE_TYPE_SIZE(pdeq_deque), 1);
}

/**
 * Destroy deque container auxiliary function.
 */
void _deque_destroy_auxiliary(deque_t* pdeq_deque)
{
    _mappointer_t    ppby_mappos = NULL;
    bool_t           b_result = false;
    deque_iterator_t it_iter;
    deque_iterator_t it_begin;
    deque_iterator_t it_end;

    assert(pdeq_deque != NULL);

    if (_deque_is_inited(pdeq_deque)) {
        /* destroy all elements */
        it_begin = deque_begin(pdeq_deque);
        it_end = deque_end(pdeq_deque);

        for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_DESTROY_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_iter), &b_result);
            assert(b_result);
        }

        /* destroy the all element container */
        for (ppby_mappos = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start);
             ppby_mappos <= _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish);
             ++ppby_mappos) {
            _alloc_deallocate(&pdeq_deque->_t_allocator, *ppby_mappos, _GET_DEQUE_TYPE_SIZE(pdeq_deque), _DEQUE_ELEM_COUNT);
        }

        /* destroy the map */
        _alloc_deallocate(&pdeq_deque->_t_allocator, pdeq_deque->_ppby_map, sizeof(_byte_t*), pdeq_deque->_t_mapsize);
        pdeq_deque->_ppby_map = NULL;
        pdeq_deque->_t_mapsize = 0;

        /* destroy the allocator */
        _alloc_destroy(&pdeq_deque->_t_allocator);

        /* destroy the start and finish iterator */
        _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) = NULL;
        _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_start) = NULL;
        _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_start) = NULL;
        _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_start) = NULL;
        _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) = NULL;
        _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) = NULL;
        _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_finish) = NULL;
        _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_finish) = NULL;
    } else {
        assert(_deque_is_created(pdeq_deque));
        _alloc_destroy(&pdeq_deque->_t_allocator);
    }
}

/**
 * Assign deque with specificed element.
 */
void _deque_assign_elem(deque_t* pdeq_deque, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    va_start(val_elemlist, t_count);
    _deque_assign_elem_varg(pdeq_deque, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Assign deque with variable argument of specificed element.
 */
void _deque_assign_elem_varg(deque_t* pdeq_deque, size_t t_count, va_list val_elemlist)
{
    deque_iterator_t it_iter;   /* the iterator of dest deque for iterate */
    deque_iterator_t it_begin;
    deque_iterator_t it_end;
    void*            pv_varg = NULL;
    bool_t           b_result = false;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    /* init the dest deque with the distance between t_begin and t_end, compare and element destroy function. */
    deque_resize(pdeq_deque, t_count);
    if (t_count > 0) {
        pv_varg = _alloc_allocate(&pdeq_deque->_t_allocator, _GET_DEQUE_TYPE_SIZE(pdeq_deque), 1);
        assert(pv_varg != NULL);
        _deque_get_varg_value_auxiliary(pdeq_deque, val_elemlist, pv_varg);

        /* copy the elements from src range to dest deque */
        it_begin = deque_begin(pdeq_deque);
        it_end = deque_end(pdeq_deque);
        for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_iter), pv_varg, &b_result);
            assert(b_result);
        }

        _deque_destroy_varg_value_auxiliary(pdeq_deque, pv_varg);
        _alloc_deallocate(&pdeq_deque->_t_allocator, pv_varg, _GET_DEQUE_TYPE_SIZE(pdeq_deque), 1);
    }
}

/**
 * Add specificed element at the end of deque container. 
 */
void _deque_push_back(deque_t* pdeq_deque, ...)
{
    va_list val_elemlist;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    va_start(val_elemlist, pdeq_deque);
    _deque_push_back_varg(pdeq_deque, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Add specificed element from variable argument list at the end of deque container. 
 */
void _deque_push_back_varg(deque_t* pdeq_deque, va_list val_elemlist)
{
    deque_iterator_t it_oldend = _create_deque_iterator();

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    it_oldend = _deque_expand_at_end(pdeq_deque, 1, NULL);
    _type_get_varg_value(&pdeq_deque->_t_typeinfo, val_elemlist, _deque_iterator_get_pointer_auxiliary(it_oldend));
}

/**
 * Add specificed element at the begin of deque container. 
 */
void _deque_push_front(deque_t* pdeq_deque, ...)
{
    va_list val_elemlist;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    va_start(val_elemlist, pdeq_deque);
    _deque_push_front_varg(pdeq_deque, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Add specificed element from variable argument list at the begin of deque container. 
 */
void _deque_push_front_varg(deque_t* pdeq_deque, va_list val_elemlist)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    _deque_expand_at_begin(pdeq_deque, 1, NULL);
    _type_get_varg_value(&pdeq_deque->_t_typeinfo, val_elemlist,
        _deque_iterator_get_pointer_auxiliary(deque_begin(pdeq_deque)));
}

/**
 * Insert multiple copys of element befor specificed position.
 */
deque_iterator_t _deque_insert_n(deque_t* pdeq_deque, deque_iterator_t it_pos, size_t t_count, ...)
{
    deque_iterator_t it_iter;
    va_list val_elemlist;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_pos));

    va_start(val_elemlist, t_count);
    it_iter = _deque_insert_n_varg(pdeq_deque, it_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 */
deque_iterator_t _deque_insert_n_varg(deque_t* pdeq_deque, deque_iterator_t it_pos, size_t t_count, va_list val_elemlist)
{
    deque_iterator_t it_resultpos;
    void*            pv_varg = NULL;
    bool_t           b_result = false;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_pos));

    /* get varg value only once */
    pv_varg = _alloc_allocate(&pdeq_deque->_t_allocator, _GET_DEQUE_TYPE_SIZE(pdeq_deque), 1);
    assert(pv_varg != NULL);
    _deque_get_varg_value_auxiliary(pdeq_deque, val_elemlist, pv_varg);

    /* if the element number after insert pos is little then insert in front */
    if (iterator_distance(deque_begin(pdeq_deque), it_pos) < (int)deque_size(pdeq_deque) / 2) {
        deque_iterator_t it_oldbegin;
        deque_iterator_t it_gap;

        /* expand one element at front */
        it_oldbegin = _deque_expand_at_begin(pdeq_deque, t_count, &it_pos);
        /* move the element range [oldfront, pos) to [newfront, pos) */
        it_resultpos = it_gap = _deque_move_elem_to_begin(pdeq_deque, it_oldbegin, it_pos, t_count);
        assert(iterator_distance(it_gap, it_pos) == (int)t_count);

        for (; !iterator_equal(it_gap, it_pos); it_gap = iterator_next(it_gap)) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_gap), pv_varg, &b_result);
            assert(b_result);
        }
        assert(iterator_equal(it_gap, it_pos));
    } else {
        size_t i = 0;
        deque_iterator_t it_oldend = _deque_expand_at_end(pdeq_deque, t_count, &it_pos);
        deque_iterator_t it_gap = _deque_move_elem_to_end(pdeq_deque, it_pos, it_oldend, t_count);
        it_resultpos = it_gap;

        assert(iterator_equal(it_pos, it_gap));

        for (i = 0; i < t_count; ++i) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_pos), pv_varg, &b_result);
            it_pos = iterator_next(it_pos);
            assert(b_result);
        }
    }

    _deque_destroy_varg_value_auxiliary(pdeq_deque, pv_varg);
    _alloc_deallocate(&pdeq_deque->_t_allocator, pv_varg, _GET_DEQUE_TYPE_SIZE(pdeq_deque), 1);

    return it_resultpos;
}

/**
 * Reset the size of deque elements.
 */
void _deque_resize_elem(deque_t* pdeq_deque, size_t t_resize, ...)
{
    va_list val_elemlist;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    va_start(val_elemlist, t_resize);
    _deque_resize_elem_varg(pdeq_deque, t_resize, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Reset the size of deque elements, and filled element is from variable argument list.
 */
void _deque_resize_elem_varg(deque_t* pdeq_deque, size_t t_resize, va_list val_elemlist)
{
    void*  pv_varg = NULL;
    bool_t b_result = false;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    if (t_resize < deque_size(pdeq_deque)) {
        _deque_shrink_at_end(pdeq_deque, deque_size(pdeq_deque) - t_resize);
    } else if (t_resize > deque_size(pdeq_deque)) {
        deque_iterator_t it_oldend = _deque_expand_at_end(pdeq_deque, t_resize - deque_size(pdeq_deque), NULL);
        deque_iterator_t it_end;

        /* get varg value only once */
        pv_varg = _alloc_allocate(&pdeq_deque->_t_allocator, _GET_DEQUE_TYPE_SIZE(pdeq_deque), 1);
        assert(pv_varg != NULL);
        _deque_get_varg_value_auxiliary(pdeq_deque, val_elemlist, pv_varg);

        it_end = deque_end(pdeq_deque);
        for (; !iterator_equal(it_oldend, it_end); it_oldend = iterator_next(it_oldend)) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_oldend), pv_varg, &b_result);
            assert(b_result);
        }

        _deque_destroy_varg_value_auxiliary(pdeq_deque, pv_varg);
        _alloc_deallocate(&pdeq_deque->_t_allocator, pv_varg, _GET_DEQUE_TYPE_SIZE(pdeq_deque), 1);
    }
}

/**
 * Initialize element with deque element type auxiliary function.
 */
void _deque_init_elem_auxiliary(deque_t* pdeq_deque, void* pv_elem)
{
    assert(pdeq_deque != NULL);
    assert(pv_elem != NULL);
    assert(_deque_is_inited(pdeq_deque) || _deque_is_created(pdeq_deque));

    /* initialize new elements */
    if (_GET_DEQUE_TYPE_STYLE(pdeq_deque) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_DEQUE_TYPE_NAME(pdeq_deque), s_elemtypename);

        _GET_DEQUE_TYPE_INIT_FUNCTION(pdeq_deque)(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _GET_DEQUE_TYPE_INIT_FUNCTION(pdeq_deque)(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

