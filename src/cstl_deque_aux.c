/*
 *  The implement of deque auxiliary function.
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

#ifndef NDEBUG
/**
 * Test iterator referenced data is within the deque.
 */
bool_t _deque_iterator_belong_to_deque(const deque_t* cpdeq_deque, deque_iterator_t it_iter)
{
    deque_iterator_t it_cur = _create_deque_iterator();
    _byte_t*         pby_startpos = NULL;
    _byte_t*         pby_finishpos = NULL;

    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque));
    assert(_DEQUE_ITERATOR_CONTAINER(it_iter) == cpdeq_deque);
    assert(_DEQUE_ITERATOR_CONTAINER_TYPE(it_iter) == _DEQUE_CONTAINER);
    assert(_DEQUE_ITERATOR_ITERATOR_TYPE(it_iter) == _RANDOM_ACCESS_ITERATOR);
   
    /* the the map pointer is valid */
    for (_DEQUE_ITERATOR_MAP_POINTER(it_cur) = _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_start);
         _DEQUE_ITERATOR_MAP_POINTER(it_cur) <= _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_finish);
         _DEQUE_ITERATOR_MAP_POINTER(it_cur) += 1) {
        if (_DEQUE_ITERATOR_MAP_POINTER(it_cur) == _DEQUE_ITERATOR_MAP_POINTER(it_iter)) {
            _DEQUE_ITERATOR_FIRST_POS(it_cur) = *_DEQUE_ITERATOR_MAP_POINTER(it_cur);
            _DEQUE_ITERATOR_AFTERLAST_POS(it_cur) = 
                _DEQUE_ITERATOR_FIRST_POS(it_cur) + _GET_DEQUE_TYPE_SIZE(cpdeq_deque) * _DEQUE_ELEM_COUNT;
            break;
        }
    }
    if (_DEQUE_ITERATOR_FIRST_POS(it_cur) == NULL) {
        return false;
    }

    /* test the iterator in suti with the map node */
    if (_DEQUE_ITERATOR_FIRST_POS(it_cur) != _DEQUE_ITERATOR_FIRST_POS(it_iter) ||
        _DEQUE_ITERATOR_AFTERLAST_POS(it_cur) != _DEQUE_ITERATOR_AFTERLAST_POS(it_iter)) {
        return false;
    }

    /* test the element pointer is valid */
    /* 
     * if the current pos equal begin pos 
     * +-----------------------------------------+
     * |first|  ... ... | corepos | ... data ... | afterlast
     * +-----------------------------------------+
     * or corepos == afterlast
     */
    if (_DEQUE_ITERATOR_MAP_POINTER(it_cur) == _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_start)) {
        /* the begin pointer point to afterlast and the it_cur is begin */
        if (_DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_start) == _DEQUE_ITERATOR_AFTERLAST_POS(cpdeq_deque->_t_start)) {
            if (_DEQUE_ITERATOR_COREPOS(it_iter) == _DEQUE_ITERATOR_AFTERLAST_POS(it_iter)) {
                return true;
            } else {
                return false;
            }
        } else {
            /* in begin container and the begin pointer not point to afterlast */
            pby_startpos = _DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_start);
            pby_finishpos = _DEQUE_ITERATOR_AFTERLAST_POS(cpdeq_deque->_t_start) - _GET_DEQUE_TYPE_SIZE(cpdeq_deque);
        }
    } else if (_DEQUE_ITERATOR_MAP_POINTER(it_cur) == _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_finish)) {
        /* if the current pos equal end pos 
         * +------------------------------------------+
         * |first|  ... data ... | corepos | ...  ... | afterlast
         * +------------------------------------------+
         */
        pby_startpos = _DEQUE_ITERATOR_FIRST_POS(cpdeq_deque->_t_finish);
        pby_finishpos = _DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_finish);
    } else {
        pby_startpos = _DEQUE_ITERATOR_FIRST_POS(it_cur);
        pby_finishpos = _DEQUE_ITERATOR_AFTERLAST_POS(it_cur) - _GET_DEQUE_TYPE_SIZE(cpdeq_deque);
    }

    for (_DEQUE_ITERATOR_COREPOS(it_cur) = pby_startpos;
         _DEQUE_ITERATOR_COREPOS(it_cur) <= pby_finishpos;
         _DEQUE_ITERATOR_COREPOS(it_cur) += _GET_DEQUE_TYPE_SIZE(cpdeq_deque)) {
        if (_DEQUE_ITERATOR_COREPOS(it_cur) == _DEQUE_ITERATOR_COREPOS(it_iter)) {
            return true;
        }
    }

    return false;
}

/**
 * Test the type that saved in the deque container and referenced by it_iter are same.
 */
bool_t _deque_same_deque_iterator_type(const deque_t* cpdeq_deque, deque_iterator_t it_iter)
{
    assert(cpdeq_deque != NULL);
    assert(_DEQUE_ITERATOR_CONTAINER(it_iter) != NULL);
    assert(_DEQUE_ITERATOR_CONTAINER_TYPE(it_iter) == _DEQUE_CONTAINER);
    assert(_DEQUE_ITERATOR_ITERATOR_TYPE(it_iter) == _RANDOM_ACCESS_ITERATOR);

    return _deque_same_type(cpdeq_deque, _DEQUE_ITERATOR_CONTAINER(it_iter));
}

/**
 * Test the type that saved in the deque container and referenced by it_iter are same.
 */
bool_t _deque_same_iterator_type(const deque_t* cpdeq_deque, iterator_t it_iter)
{
    assert(cpdeq_deque != NULL);
    assert(_deque_is_inited(cpdeq_deque) || _deque_is_created(cpdeq_deque));
    assert(_iterator_is_valid(it_iter));

    return _type_is_same_ex(&cpdeq_deque->_t_typeinfo, _iterator_get_typeinfo(it_iter));
}

/**
 * Test deque is created by create_deque.
 */
bool_t _deque_is_created(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);

    if (cpdeq_deque->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
        cpdeq_deque->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
        cpdeq_deque->_t_typeinfo._t_style != _TYPE_USER_DEFINE) {
        return false;
    }
    if (cpdeq_deque->_t_typeinfo._pt_type == NULL) {
        return false;
    }

    if (cpdeq_deque->_ppby_map != NULL || cpdeq_deque->_t_mapsize != 0) {
        return false;
    }

    if (_DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_start) != NULL ||
        _DEQUE_ITERATOR_FIRST_POS(cpdeq_deque->_t_start) != NULL ||
        _DEQUE_ITERATOR_AFTERLAST_POS(cpdeq_deque->_t_start) != NULL ||
        _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_start) != NULL ||
        _DEQUE_ITERATOR_CONTAINER(cpdeq_deque->_t_start) != NULL ||
        _DEQUE_ITERATOR_CONTAINER_TYPE(cpdeq_deque->_t_start) != _DEQUE_CONTAINER ||
        _DEQUE_ITERATOR_ITERATOR_TYPE(cpdeq_deque->_t_start) != _RANDOM_ACCESS_ITERATOR) {
        return false;
    }
    if (_DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_finish) != NULL ||
        _DEQUE_ITERATOR_FIRST_POS(cpdeq_deque->_t_finish) != NULL ||
        _DEQUE_ITERATOR_AFTERLAST_POS(cpdeq_deque->_t_finish) != NULL ||
        _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_finish) != NULL ||
        _DEQUE_ITERATOR_CONTAINER(cpdeq_deque->_t_finish) != NULL ||
        _DEQUE_ITERATOR_CONTAINER_TYPE(cpdeq_deque->_t_finish) != _DEQUE_CONTAINER ||
        _DEQUE_ITERATOR_ITERATOR_TYPE(cpdeq_deque->_t_finish) != _RANDOM_ACCESS_ITERATOR) {
        return false;
    }

    return _alloc_is_inited(&cpdeq_deque->_t_allocator);
}
#endif /* NDEBUG */

/**
 * Test deque is initialized by deque initialization functions.
 */
bool_t _deque_is_inited(const deque_t* cpdeq_deque)
{
    assert(cpdeq_deque != NULL);

    if (cpdeq_deque->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
        cpdeq_deque->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
        cpdeq_deque->_t_typeinfo._t_style != _TYPE_USER_DEFINE) {
        return false;
    }
    if (cpdeq_deque->_t_typeinfo._pt_type == NULL) {
        return false;
    }

    if (cpdeq_deque->_ppby_map == NULL ||
        cpdeq_deque->_t_mapsize < _DEQUE_MAP_COUNT ||
        cpdeq_deque->_t_mapsize % _DEQUE_MAP_GROW_STEP != 0) {
        return false;
    }

    if (_DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_start) == NULL ||
        _DEQUE_ITERATOR_FIRST_POS(cpdeq_deque->_t_start) == NULL ||
        _DEQUE_ITERATOR_AFTERLAST_POS(cpdeq_deque->_t_start) == NULL ||
        _DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_start) == NULL ||
        _DEQUE_ITERATOR_CONTAINER(cpdeq_deque->_t_start) != cpdeq_deque ||
        _DEQUE_ITERATOR_CONTAINER_TYPE(cpdeq_deque->_t_start) != _DEQUE_CONTAINER ||
        _DEQUE_ITERATOR_ITERATOR_TYPE(cpdeq_deque->_t_start) != _RANDOM_ACCESS_ITERATOR) {
        return false;
    }
    if (_DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_finish) == NULL ||
        _DEQUE_ITERATOR_FIRST_POS(cpdeq_deque->_t_finish) == NULL ||
        _DEQUE_ITERATOR_AFTERLAST_POS(cpdeq_deque->_t_finish) == NULL ||
        _DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_finish) == NULL ||
        _DEQUE_ITERATOR_CONTAINER(cpdeq_deque->_t_finish) != cpdeq_deque ||
        _DEQUE_ITERATOR_CONTAINER_TYPE(cpdeq_deque->_t_finish) != _DEQUE_CONTAINER ||
        _DEQUE_ITERATOR_ITERATOR_TYPE(cpdeq_deque->_t_finish) != _RANDOM_ACCESS_ITERATOR) {
        return false;
    }

    if (_DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_start) < cpdeq_deque->_ppby_map ||
        _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_start) >= cpdeq_deque->_ppby_map + cpdeq_deque->_t_mapsize) {
        return false;
    }
    if (_DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_finish) < cpdeq_deque->_ppby_map ||
        _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_finish) >= cpdeq_deque->_ppby_map + cpdeq_deque->_t_mapsize) {
        return false;
    }
    if (_DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_start) > _DEQUE_ITERATOR_MAP_POINTER(cpdeq_deque->_t_finish)) {
        return false;
    }

    if (_DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_start) < _DEQUE_ITERATOR_FIRST_POS(cpdeq_deque->_t_start) ||
        _DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_start) > _DEQUE_ITERATOR_AFTERLAST_POS(cpdeq_deque->_t_start)) {
        return false;
    }
    if (_DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_finish) < _DEQUE_ITERATOR_FIRST_POS(cpdeq_deque->_t_finish) ||
        _DEQUE_ITERATOR_COREPOS(cpdeq_deque->_t_finish) > _DEQUE_ITERATOR_AFTERLAST_POS(cpdeq_deque->_t_finish)) {
        return false;
    }

    return true;
}

/**
 * Test the type that saved in the deque container is same.
 */
bool_t _deque_same_type(const deque_t* cpdeq_first, const deque_t* cpdeq_second)
{
    assert(cpdeq_first != NULL);
    assert(cpdeq_second != NULL);
    assert(_deque_is_inited(cpdeq_first) || _deque_is_created(cpdeq_first));
    assert(_deque_is_inited(cpdeq_second) || _deque_is_created(cpdeq_second));

    if (cpdeq_first == cpdeq_second) {
        return true;
    }

    return (cpdeq_first->_t_typeinfo._pt_type == cpdeq_second->_t_typeinfo._pt_type) &&
           (cpdeq_first->_t_typeinfo._t_style == cpdeq_second->_t_typeinfo._t_style) &&
           _type_is_same(_GET_DEQUE_TYPE_NAME(cpdeq_first), _GET_DEQUE_TYPE_NAME(cpdeq_second));
}

/**
 * Expand deque at end.
 */
deque_iterator_t _deque_expand_at_end(deque_t* pdeq_deque, size_t t_expandsize, deque_iterator_t* pit_pos)
{
    deque_iterator_t it_oldend;
    size_t           t_remainsize = 0; /* the remain size in last container */

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
#ifndef NDEBUG
    if (pit_pos != NULL) {
        assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(*pit_pos), *pit_pos));
    }
#endif /* NDEBUG */

    it_oldend = deque_end(pdeq_deque);

    /* if the capacity of last container is enough for expand size */
    t_remainsize = (_DEQUE_ITERATOR_AFTERLAST_POS(it_oldend) - _DEQUE_ITERATOR_COREPOS(it_oldend)) / _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    if (t_expandsize < t_remainsize) {
        /* set the new end iterator */
        _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_finish) += t_expandsize * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    } else {
        size_t    t_nomemsize = 0;        /* the size that they have no memory */
        size_t    t_chunksize = 0;        /* the chunk for new element */
        size_t    t_suffixsize = 0;       /* the valid size in end container */
        size_t    t_remainendmapsize = 0; /* the remain space at the map end */
        size_t    t_remainmapsize = 0;    /* the remain space in the map */
        _byte_t** ppby_newchunk = NULL;    /* the pointer to new chunk */
        size_t    i = 0;

        /* caculate the expand container number */
        t_nomemsize = t_expandsize - t_remainsize;
        t_chunksize = (t_nomemsize + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT;
        t_suffixsize = t_nomemsize % _DEQUE_ELEM_COUNT;
        if (t_suffixsize == 0) {
            t_chunksize++;
        }

        t_remainendmapsize = (pdeq_deque->_ppby_map + pdeq_deque->_t_mapsize) - _DEQUE_ITERATOR_MAP_POINTER(it_oldend) - 1;
        t_remainmapsize = 
            pdeq_deque->_t_mapsize - (_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) - _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + 1);

        /* if container remain space is not enough for expand size then grow the map for expand container */
        if (t_chunksize > t_remainmapsize) {
            size_t t_validmapsize = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) - _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + 1;
            size_t t_newmapstartpos = 0;
            size_t t_oldmapstartpos = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) - pdeq_deque->_ppby_map;
            size_t t_posdistance = 0;                          /* the distance of pit_pos and map */
            size_t t_growsize =                                /* grow size multiple of eight */
                (t_chunksize - t_remainmapsize + _DEQUE_MAP_GROW_STEP - 1) / _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
            _mappointer_t ppby_oldmap = pdeq_deque->_ppby_map;  /* save the old map */
            size_t t_oldmapsize = pdeq_deque->_t_mapsize;

            /* new map */
            pdeq_deque->_t_mapsize += t_growsize;
            pdeq_deque->_ppby_map = _alloc_allocate(&pdeq_deque->_t_allocator, sizeof(_byte_t*), pdeq_deque->_t_mapsize);
            assert(pdeq_deque->_ppby_map != NULL);
            memset(pdeq_deque->_ppby_map, 0x00, sizeof(_byte_t*) * pdeq_deque->_t_mapsize);

            /* copy the chunk pointer from old map to new map */
            t_newmapstartpos = (pdeq_deque->_t_mapsize - (t_validmapsize + t_chunksize)) / 2;
            memcpy(pdeq_deque->_ppby_map + t_newmapstartpos, ppby_oldmap + t_oldmapstartpos, sizeof(_byte_t*) * t_validmapsize);
            /* get the pit_pos distance */
            if (pit_pos != NULL) {
                t_posdistance = _DEQUE_ITERATOR_MAP_POINTER(*pit_pos) - _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start);
            }
            /* reset the start, finish and old front iterator */
            _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) = pdeq_deque->_ppby_map + t_newmapstartpos;
            _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) = pdeq_deque->_ppby_map + t_newmapstartpos + t_validmapsize - 1;
            _DEQUE_ITERATOR_MAP_POINTER(it_oldend) = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish);
            /* modify pit_pos */
            if (pit_pos != NULL) {
                _DEQUE_ITERATOR_MAP_POINTER(*pit_pos) = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + t_posdistance;
            }
            _alloc_deallocate(&pdeq_deque->_t_allocator, ppby_oldmap, sizeof(_byte_t*), t_oldmapsize);
        } else if (t_chunksize > t_remainendmapsize && t_chunksize <= t_remainmapsize) {
            /* if the chunk remain space is enough for expand size */
            size_t t_oldvalidmapsize = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) -
                _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + 1;                                       /* old valid chunk count in old map */
            size_t t_newvalidmapsize = t_oldvalidmapsize + t_chunksize;                                      /* the valid chunk count in new map */
            size_t t_oldstartpossize = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) - pdeq_deque->_ppby_map; /* the chunk start pos in old map */
            size_t t_newstartpossize = (pdeq_deque->_t_mapsize - t_newvalidmapsize) / 2;                     /* the chunk start pos in new map */
            size_t t_movesize = t_oldstartpossize - t_newstartpossize;                                       /* the distance of move */

            /* move the valid container pointer in map */
            memmove(_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) - t_movesize,
                _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start), sizeof(_byte_t*) * t_oldvalidmapsize);
            /* reset the start, finish and oldend iterator */
            _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) -= t_movesize;
            _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) -= t_movesize;
            _DEQUE_ITERATOR_MAP_POINTER(it_oldend) -= t_movesize;
            if (pit_pos != NULL) {
                _DEQUE_ITERATOR_MAP_POINTER(*pit_pos) -= t_movesize;
            }
        }

        /* allocate the container */
        for (i = 0, ppby_newchunk = _DEQUE_ITERATOR_MAP_POINTER(it_oldend) + 1; i < t_chunksize; ++i, ++ppby_newchunk) {
            *ppby_newchunk = _alloc_allocate(&pdeq_deque->_t_allocator, _GET_DEQUE_TYPE_SIZE(pdeq_deque), _DEQUE_ELEM_COUNT);
            assert(*ppby_newchunk != NULL);
        }

        /* set new end iterator */
        _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) = _DEQUE_ITERATOR_MAP_POINTER(it_oldend) + t_chunksize;
        _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) = *_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish);
        _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_finish) = 
            _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) + _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_finish) = 
            _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_finish) + t_suffixsize * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    }

    /* initialize all new elements */
    _deque_init_elem_range_auxiliary(pdeq_deque, it_oldend, deque_end(pdeq_deque));

    return it_oldend;
}

/**
 * Expand deque at begin.
 */
deque_iterator_t _deque_expand_at_begin(deque_t* pdeq_deque, size_t t_expandsize, deque_iterator_t* pit_pos)
{
    deque_iterator_t it_oldbegin;
    size_t           t_remainsize = 0; /* the remain size in first container */

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
#ifndef NDEBUG
    if (pit_pos != NULL) {
        assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(*pit_pos), *pit_pos));
    }
#endif /* NDEBUG */

    it_oldbegin = deque_begin(pdeq_deque);

    /* if the capacity of first container is enough for expand size */
    t_remainsize = (_DEQUE_ITERATOR_COREPOS(it_oldbegin) - _DEQUE_ITERATOR_FIRST_POS(it_oldbegin)) / _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    if (t_expandsize < t_remainsize) {
        /* set the new begin iterator */
        _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_start) -= t_expandsize * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    } else {
        size_t    t_nomemsize = 0;          /* the size that they have no memory */
        size_t    t_chunksize = 0;          /* the chunk for new element */
        size_t    t_prefixsize = 0;         /* the valid size in front chunk */
        size_t    t_remainfrontmapsize = 0; /* the remain space at the map begin */
        size_t    t_remainmapsize = 0;      /* the remain space in the map */
        _byte_t** ppby_newchunk = NULL;      /* the pointer to new chunk */
        size_t    i = 0;

        /* caculate the expand chunk number */
        t_nomemsize = t_expandsize - t_remainsize;
        t_chunksize = (t_nomemsize + _DEQUE_ELEM_COUNT - 1) / _DEQUE_ELEM_COUNT;
        t_prefixsize = t_nomemsize % _DEQUE_ELEM_COUNT;
        if (t_prefixsize == 0) {
            t_chunksize++;
        }

        t_remainfrontmapsize = _DEQUE_ITERATOR_MAP_POINTER(it_oldbegin) - pdeq_deque->_ppby_map;
        t_remainmapsize = pdeq_deque->_t_mapsize - 
            (_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) - _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + 1);

        /* if chunk remain space is not enough for expand size then grow the map for expand chunk */
        if (t_chunksize > t_remainmapsize) {
            size_t t_validmapsize = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) - _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + 1;
            int n_newmapstartpos = 0;
            int n_oldmapstartpos = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) - pdeq_deque->_ppby_map;
            int n_newposofoldchunk = 0;
            int n_posdistance = 0;                             /* the distance of pit_pos and map */
            size_t t_growsize =                                /* grow size multiple of eight */ 
                (t_chunksize - t_remainmapsize + _DEQUE_MAP_GROW_STEP - 1) / _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
            _mappointer_t ppby_oldmap = pdeq_deque->_ppby_map;  /* old map */
            size_t t_oldmapsize = pdeq_deque->_t_mapsize;

            /* new map */
            pdeq_deque->_t_mapsize += t_growsize;
            pdeq_deque->_ppby_map = _alloc_allocate(&pdeq_deque->_t_allocator, sizeof(_byte_t*), pdeq_deque->_t_mapsize);
            assert(pdeq_deque->_ppby_map != NULL);
            memset(pdeq_deque->_ppby_map, 0x00, sizeof(_byte_t*) * pdeq_deque->_t_mapsize);

            /* copy the chunk pointer from old map to new map */
            n_newmapstartpos = (pdeq_deque->_t_mapsize - (t_validmapsize + t_chunksize)) / 2; 
            n_newposofoldchunk = n_newmapstartpos + t_chunksize;
            memcpy(pdeq_deque->_ppby_map + n_newposofoldchunk, ppby_oldmap + n_oldmapstartpos, sizeof(_byte_t*) * t_validmapsize);
            /* get the pit_pos distance */
            if (pit_pos != NULL) {
                n_posdistance = _DEQUE_ITERATOR_MAP_POINTER(*pit_pos) - _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start);
            }
            /* reset the start, finish and old front iterator */
            _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) = pdeq_deque->_ppby_map + n_newposofoldchunk;
            _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) = pdeq_deque->_ppby_map + n_newposofoldchunk + t_validmapsize - 1;
            _DEQUE_ITERATOR_MAP_POINTER(it_oldbegin) = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start);
            /* modify pit_pos */
            if (pit_pos != NULL) {
                _DEQUE_ITERATOR_MAP_POINTER(*pit_pos) = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + n_posdistance;
            }
            _alloc_deallocate(&pdeq_deque->_t_allocator, ppby_oldmap, sizeof(_byte_t*), t_oldmapsize);
        } else if (t_chunksize > t_remainfrontmapsize && t_chunksize <= t_remainmapsize) {
            /* if the chunk remain space is enough for expand size */
            size_t t_oldvalidmapsize = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) -
                _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + 1;                                            /* old valid chunk count in old map */
            size_t t_newvalidmapsize = t_oldvalidmapsize + t_chunksize;                                      /* the valid chunk count in new map */
            size_t t_oldstartpossize = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) - pdeq_deque->_ppby_map; /* the chunk start pos in old map */
            size_t t_newstartpossize = (pdeq_deque->_t_mapsize - t_newvalidmapsize) / 2;                     /* the chunk start pos in new map */
            size_t t_newposofoldchunk = t_newstartpossize + t_chunksize;                                     /* the chunk in new map pos */
            size_t t_movesize = t_newposofoldchunk - t_oldstartpossize;                                      /* the distance of move */
            /* move the valid chunk pointer in map */
            memmove(_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) + t_movesize,
                _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start), sizeof(_byte_t*) * t_oldvalidmapsize);
            /* reset the start, finish and oldend iterator */
            _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) += t_movesize;
            _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) += t_movesize;
            _DEQUE_ITERATOR_MAP_POINTER(it_oldbegin) += t_movesize;
            if (pit_pos != NULL) {
                _DEQUE_ITERATOR_MAP_POINTER(*pit_pos) += t_movesize;
            }
        }

        /* allocate the chunk */
        for (i = 0, ppby_newchunk = _DEQUE_ITERATOR_MAP_POINTER(it_oldbegin) - 1; i < t_chunksize; ++i, --ppby_newchunk) {
            *ppby_newchunk = _alloc_allocate(&pdeq_deque->_t_allocator, _GET_DEQUE_TYPE_SIZE(pdeq_deque), _DEQUE_ELEM_COUNT);
            assert(*ppby_newchunk != NULL);
        }

        /* set new start iterator */
        _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) = _DEQUE_ITERATOR_MAP_POINTER(it_oldbegin) - t_chunksize;
        _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_start) = *_DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start);
        _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_start) = 
            _DEQUE_ITERATOR_FIRST_POS(pdeq_deque->_t_start) + _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _DEQUE_ITERATOR_COREPOS(pdeq_deque->_t_start) = 
            _DEQUE_ITERATOR_AFTERLAST_POS(pdeq_deque->_t_start) - t_prefixsize * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    }

    /* the old front is original front */
    if (_DEQUE_ITERATOR_COREPOS(it_oldbegin) == _DEQUE_ITERATOR_AFTERLAST_POS(it_oldbegin)) {
        assert(*(_DEQUE_ITERATOR_MAP_POINTER(it_oldbegin) + 1) != NULL);
        _DEQUE_ITERATOR_MAP_POINTER(it_oldbegin) += 1;
        _DEQUE_ITERATOR_FIRST_POS(it_oldbegin) = *_DEQUE_ITERATOR_MAP_POINTER(it_oldbegin);
        _DEQUE_ITERATOR_AFTERLAST_POS(it_oldbegin) = _DEQUE_ITERATOR_FIRST_POS(it_oldbegin) + 
            _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _DEQUE_ITERATOR_COREPOS(it_oldbegin) = _DEQUE_ITERATOR_FIRST_POS(it_oldbegin);
    }
    /* the *pit_pos is original front */
    if (pit_pos != NULL && _DEQUE_ITERATOR_COREPOS(*pit_pos) == _DEQUE_ITERATOR_AFTERLAST_POS(*pit_pos)) {
        assert(*(_DEQUE_ITERATOR_MAP_POINTER(*pit_pos) + 1) != NULL);
        _DEQUE_ITERATOR_MAP_POINTER(*pit_pos) += 1;
        _DEQUE_ITERATOR_FIRST_POS(*pit_pos) = *_DEQUE_ITERATOR_MAP_POINTER(*pit_pos);
        _DEQUE_ITERATOR_AFTERLAST_POS(*pit_pos) = _DEQUE_ITERATOR_FIRST_POS(*pit_pos) +
            _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _DEQUE_ITERATOR_COREPOS(*pit_pos) = _DEQUE_ITERATOR_FIRST_POS(*pit_pos);
    }

    /* initialize all new elements */
    _deque_init_elem_range_auxiliary(pdeq_deque, deque_begin(pdeq_deque), it_oldbegin);

    return it_oldbegin;
}

/**
 * Shrink deque at end.
 */
void _deque_shrink_at_end(deque_t* pdeq_deque, size_t t_shrinksize)
{
    deque_iterator_t it_oldend;
    deque_iterator_t it_newend;
    deque_iterator_t it_iter;
    _mappointer_t    ppby_map = NULL;
    bool_t           b_result = false;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    it_oldend = deque_end(pdeq_deque);
    t_shrinksize = t_shrinksize < deque_size(pdeq_deque) ? t_shrinksize : deque_size(pdeq_deque);
    it_newend = iterator_prev_n(deque_end(pdeq_deque), t_shrinksize);
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_newend));

    /* destroy all elements */
    for (it_iter = it_newend; !iterator_equal(it_iter, it_oldend); it_iter = iterator_next(it_iter)) {
        b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _GET_DEQUE_TYPE_DESTROY_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_iter), &b_result);
        assert(b_result);
    }
    pdeq_deque->_t_finish = it_newend;

    for (ppby_map = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_finish) + 1; ppby_map <= _DEQUE_ITERATOR_MAP_POINTER(it_oldend); ++ppby_map) {
        _alloc_deallocate(&pdeq_deque->_t_allocator, *ppby_map, _GET_DEQUE_TYPE_SIZE(pdeq_deque), _DEQUE_ELEM_COUNT);
        *ppby_map = NULL;
    }
}

/**
 * Shrink deque at begin.
 */
void _deque_shrink_at_begin(deque_t* pdeq_deque, size_t t_shrinksize)
{
    deque_iterator_t it_oldbegin;
    deque_iterator_t it_newbegin;
    deque_iterator_t it_iter;
    _mappointer_t    ppby_map = NULL;
    bool_t           b_result = false;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));

    it_oldbegin = deque_begin(pdeq_deque);
    t_shrinksize = t_shrinksize < deque_size(pdeq_deque) ? t_shrinksize : deque_size(pdeq_deque);
    it_newbegin = iterator_next_n(deque_begin(pdeq_deque), t_shrinksize);
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_newbegin));

    /* destroy all elements */
    for (it_iter = it_oldbegin; !iterator_equal(it_iter, it_newbegin); it_iter = iterator_next(it_iter)) {
        b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
        _GET_DEQUE_TYPE_DESTROY_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_iter), &b_result);
        assert(b_result);
    }
    pdeq_deque->_t_start = it_newbegin;

    for (ppby_map = _DEQUE_ITERATOR_MAP_POINTER(pdeq_deque->_t_start) - 1; ppby_map >= _DEQUE_ITERATOR_MAP_POINTER(it_oldbegin); --ppby_map) {
        _alloc_deallocate(&pdeq_deque->_t_allocator, *ppby_map, _GET_DEQUE_TYPE_SIZE(pdeq_deque), _DEQUE_ELEM_COUNT);
        *ppby_map = NULL;
    }
}

/**
 * Move element range to deque end.
 */
deque_iterator_t _deque_move_elem_to_end(
    deque_t* pdeq_deque, deque_iterator_t it_begin, deque_iterator_t it_end, size_t t_step)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_begin));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_end));
    assert(iterator_equal(it_begin, it_end) || _deque_iterator_before(it_begin, it_end));

    /* if it_begin != it_end then do move */
    if (!iterator_equal(it_begin, it_end) && t_step != 0) {
        /* the target range of move */
        deque_iterator_t it_targetbegin;
        deque_iterator_t it_targetend;
        bool_t           b_result = false;

        it_targetbegin = it_begin;
        it_targetend = it_end;
        it_targetbegin = iterator_next_n(it_targetbegin, t_step);
        it_targetend = iterator_next_n(it_targetend, t_step);
        assert(_deque_iterator_before(it_targetbegin, it_targetend));

        while (!iterator_equal(it_targetbegin, it_targetend) && !iterator_equal(it_begin, it_end)) {
            it_targetend = iterator_prev(it_targetend);
            it_end = iterator_prev(it_end);
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                _deque_iterator_get_pointer_auxiliary(it_targetend),
                _deque_iterator_get_pointer_auxiliary(it_end), &b_result);
            assert(b_result);
        }
        assert(iterator_equal(it_begin, it_end) && iterator_equal(it_targetbegin, it_targetend));
    }

    return it_begin;
}

/**
 * Move element range to deque begin.
 */
deque_iterator_t _deque_move_elem_to_begin(
    deque_t* pdeq_deque, deque_iterator_t it_begin, deque_iterator_t it_end, size_t t_step)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_begin));
    assert(_deque_iterator_belong_to_deque(pdeq_deque, it_end));
    assert(iterator_equal(it_begin, it_end) || _deque_iterator_before(it_begin, it_end));

    if (!iterator_equal(it_begin, it_end) && t_step != 0) {
        deque_iterator_t it_targetbegin;
        deque_iterator_t it_targetend;
        bool_t           b_result = false;

        it_targetbegin = it_begin;
        it_targetend = it_end;
        it_targetbegin = iterator_prev_n(it_targetbegin, t_step);
        it_targetend = iterator_prev_n(it_targetend, t_step);
        assert(_deque_iterator_before(it_targetbegin, it_targetend));

        for (;
             iterator_less(it_targetbegin, it_targetend) && iterator_less(it_begin, it_end);
             it_targetbegin = iterator_next(it_targetbegin), it_begin = iterator_next(it_begin)) {
            b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pdeq_deque)(
                _deque_iterator_get_pointer_auxiliary(it_targetbegin),
                _deque_iterator_get_pointer_auxiliary(it_begin), &b_result);
            assert(b_result);
        }
        assert(iterator_equal(it_targetbegin, it_targetend) && iterator_equal(it_begin, it_end));

        return it_targetend;
    } else {
        return iterator_prev_n(it_end, t_step);
    }
}

/**
 * Obtain data from variable argument list, the data type and deque element data type are same.
 */
void _deque_get_varg_value_auxiliary(deque_t* pdeq_deque, va_list val_elemlist, void* pv_varg)
{
    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque) || _deque_is_created(pdeq_deque));

    _deque_init_elem_auxiliary(pdeq_deque, pv_varg);
    _type_get_varg_value(&pdeq_deque->_t_typeinfo, val_elemlist, pv_varg);
}

/**
 * Destroy data, the data type and deque element data type are same.
 */
void _deque_destroy_varg_value_auxiliary(deque_t* pdeq_deque, void* pv_varg)
{
    bool_t b_result = false;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque) || _deque_is_created(pdeq_deque));

    /* destroy varg value and free memory */
    b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
    _GET_DEQUE_TYPE_DESTROY_FUNCTION(pdeq_deque)(pv_varg, &b_result);
    assert(b_result);
}

/**
 * Initialize data within range [it_begin, it_end) according to deque element data type.
 */
void _deque_init_elem_range_auxiliary(deque_t* pdeq_deque, deque_iterator_t it_begin, deque_iterator_t it_end)
{
    deque_iterator_t it_iter;

    assert(pdeq_deque != NULL);
    assert(_deque_is_inited(pdeq_deque) || _deque_is_created(pdeq_deque));
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_begin), it_begin));
    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_end), it_end));
    assert(iterator_equal(it_begin, it_end) || _deque_iterator_before(it_begin, it_end));

    /* initialize new elements */
    if (_GET_DEQUE_TYPE_STYLE(pdeq_deque) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_DEQUE_TYPE_NAME(pdeq_deque), s_elemtypename);

        for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
            _GET_DEQUE_TYPE_INIT_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_iter), s_elemtypename);
        }
    } else {
        for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
            bool_t b_result = _GET_DEQUE_TYPE_SIZE(pdeq_deque);
            _GET_DEQUE_TYPE_INIT_FUNCTION(pdeq_deque)(_deque_iterator_get_pointer_auxiliary(it_iter), &b_result);
            assert(b_result);
        }
    }
}

/**
 * Get the iterator pointer auxiliary function.
 */
void* _deque_iterator_get_pointer_auxiliary(iterator_t it_iter)
{
    _byte_t* pby_pos = NULL;

    assert(_deque_iterator_belong_to_deque(_DEQUE_ITERATOR_CONTAINER(it_iter), it_iter));
    assert(!iterator_equal(it_iter, deque_end(_DEQUE_ITERATOR_CONTAINER(it_iter))));

    if (_DEQUE_ITERATOR_COREPOS(it_iter) != _DEQUE_ITERATOR_AFTERLAST_POS(it_iter)) {
        pby_pos = _DEQUE_ITERATOR_COREPOS(it_iter);
    } else {
        /* 
         * when the iterator is begin and the corepos equal to afterlast 
         * then get the first element in next chunk.
         */
        _mappointer_t ppby_next = _DEQUE_ITERATOR_MAP_POINTER(it_iter) + 1;
        pby_pos = *ppby_next;
    }
    assert(pby_pos != NULL);

    return pby_pos;
}

/** local function implementation section **/

/** eof **/

