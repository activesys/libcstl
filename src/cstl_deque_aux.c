/*
 *  The implement of deque auxiliary function.
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

#ifndef NDEBUG
bool_t _deque_iterator_belong_to_deque(
    const deque_t* cpt_deque, deque_iterator_t t_iter)
{
    deque_iterator_t t_cur = _create_deque_iterator();
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
    assert(_GET_DEQUE_CONTAINER_TYPE(t_iter) == _DEQUE_CONTAINER);
    assert(_GET_DEQUE_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR);
    assert(_GET_DEQUE_CONTAINER(t_iter) == cpt_deque);
   
    /* the the map pointer is valid */
    for(_GET_DEQUE_MAP_POINTER(t_cur) = _GET_DEQUE_MAP_POINTER(cpt_deque->_t_start);
        _GET_DEQUE_MAP_POINTER(t_cur) <= _GET_DEQUE_MAP_POINTER(cpt_deque->_t_finish);
        _GET_DEQUE_MAP_POINTER(t_cur) += 1)
    {
        if(_GET_DEQUE_MAP_POINTER(t_cur) == _GET_DEQUE_MAP_POINTER(t_iter))
        {
            _GET_DEQUE_FIRST_POS(t_cur) = *_GET_DEQUE_MAP_POINTER(t_cur);
            _GET_DEQUE_AFTERLAST_POS(t_cur) = _GET_DEQUE_FIRST_POS(t_cur) +
                _GET_DEQUE_TYPE_SIZE(cpt_deque) * _DEQUE_ELEM_COUNT;
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
                _GET_DEQUE_TYPE_SIZE(cpt_deque);
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
        pc_finishpos = _GET_DEQUE_AFTERLAST_POS(t_cur) - _GET_DEQUE_TYPE_SIZE(cpt_deque);
    }

    for(_GET_DEQUE_COREPOS(t_cur) = pc_startpos;
        _GET_DEQUE_COREPOS(t_cur) <= pc_finishpos;
        _GET_DEQUE_COREPOS(t_cur) += _GET_DEQUE_TYPE_SIZE(cpt_deque))
    {
        if(_GET_DEQUE_COREPOS(t_cur) == _GET_DEQUE_COREPOS(t_iter))
        {
            return true;
        }
    }

    return false;
}

bool_t _deque_same_deque_iterator_type(
    const deque_t* cpt_deque, deque_iterator_t t_iter)
{
    assert(cpt_deque != NULL);
    assert(_GET_DEQUE_CONTAINER(t_iter) != NULL);
    assert(_GET_DEQUE_CONTAINER_TYPE(t_iter) == _DEQUE_CONTAINER &&
           _GET_DEQUE_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR);

    return _deque_same_type(cpt_deque, _GET_DEQUE_CONTAINER(t_iter));
}
#endif /* NDEBUG */

bool_t _deque_same_type(
    const deque_t* cpt_dequefirst, const deque_t* cpt_dequesecond)
{
    assert(cpt_dequefirst != NULL && cpt_dequesecond != NULL);

    return _type_is_same(_GET_DEQUE_TYPE_NAME(cpt_dequefirst),
                         _GET_DEQUE_TYPE_NAME(cpt_dequesecond)) &&
           (cpt_dequefirst->_t_typeinfo._pt_type ==
            cpt_dequesecond->_t_typeinfo._pt_type) &&
           (cpt_dequefirst->_t_typeinfo._t_style ==
            cpt_dequesecond->_t_typeinfo._t_style);
}

deque_iterator_t _expand_at_end(
    deque_t* pt_deque, size_t t_expandsize, deque_iterator_t* pt_pos)
{
    deque_iterator_t t_oldend;
    size_t           t_remainsize = 0; /* the remain size in last container */

    assert(pt_deque != NULL);
    t_oldend = deque_end(pt_deque);

    /* if the capacity of last container is enough for expand size */
    t_remainsize = (_GET_DEQUE_AFTERLAST_POS(t_oldend) - _GET_DEQUE_COREPOS(t_oldend)) /
        _GET_DEQUE_TYPE_SIZE(pt_deque);
    if(t_expandsize < t_remainsize)
    {
        /* set the new end iterator */
        _GET_DEQUE_COREPOS(pt_deque->_t_finish) +=
            t_expandsize * _GET_DEQUE_TYPE_SIZE(pt_deque);
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
        t_remainmapsize = pt_deque->_t_mapsize - (_GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -
            _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + 1);

        /* if container remain space is not enough for expand size
         * then grow the map for expand container */
        if(t_containersize > t_remainmapsize)
        {
            size_t t_validmapsize = _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) -
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + 1;
            int n_newmapstartpos = 0;
            int n_oldmapstartpos = (pt_deque->_t_mapsize - t_validmapsize) / 2;
            /* the distance of pt_pos and map */
            int n_posdistance = 0;
            /* grow size multiple of eight */
            size_t t_growsize = (t_containersize - t_remainmapsize + _DEQUE_MAP_GROW_STEP - 1)/
                _DEQUE_MAP_GROW_STEP * _DEQUE_MAP_GROW_STEP;
            /* save the old map */
            _mappointer_t t_oldmap = pt_deque->_ppc_map;
            size_t t_oldmapsize = pt_deque->_t_mapsize;

            /* new map */
            pt_deque->_t_mapsize += t_growsize;
            pt_deque->_ppc_map = _alloc_allocate(
                &pt_deque->_t_allocater, sizeof(char*), pt_deque->_t_mapsize);
            assert(pt_deque->_ppc_map != NULL);
            memset(pt_deque->_ppc_map, 0x00, sizeof(char*)*pt_deque->_t_mapsize);

            /* copy the container pointer from old map to new map */
            n_newmapstartpos = (pt_deque->_t_mapsize - (t_validmapsize + t_containersize)) / 2;
            memcpy(pt_deque->_ppc_map + n_newmapstartpos, t_oldmap + n_oldmapstartpos, 
                sizeof(char*) * t_validmapsize);
            /* get the pt_pos distance */
            if(pt_pos != NULL)
            {
                n_posdistance = _GET_DEQUE_MAP_POINTER(*pt_pos) - 
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
            _alloc_deallocate(&pt_deque->_t_allocater, t_oldmap, sizeof(char*), t_oldmapsize);
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
            memmove(_GET_DEQUE_MAP_POINTER(pt_deque->_t_start) - t_movesize,
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start), sizeof(char*) * t_oldvalidmapsize);
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
            *ppc_newcontainer = _alloc_allocate(
                &pt_deque->_t_allocater, _GET_DEQUE_TYPE_SIZE(pt_deque), _DEQUE_ELEM_COUNT);
            assert(*ppc_newcontainer != NULL);
        }

        /* set new end iterator */
        _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) = 
            _GET_DEQUE_MAP_POINTER(t_oldend) + t_containersize;
        _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) = 
            *_GET_DEQUE_MAP_POINTER(pt_deque->_t_finish);
        _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_finish) = 
            _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) + 
            _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_COREPOS(pt_deque->_t_finish) = 
            _GET_DEQUE_FIRST_POS(pt_deque->_t_finish) + 
            t_validendsize * _GET_DEQUE_TYPE_SIZE(pt_deque);
    }

    /* initialize all new elements */
    _deque_init_elem_range_auxiliary(pt_deque, t_oldend, deque_end(pt_deque));

    return t_oldend;
}

deque_iterator_t _expand_at_begin(
    deque_t* pt_deque, size_t t_expandsize, deque_iterator_t* pt_pos)
{
    deque_iterator_t t_oldbegin;
    size_t           t_remainsize = 0; /* the remain size in first container */

    assert(pt_deque != NULL);
    t_oldbegin = deque_begin(pt_deque);

    /* if the capacity of first container is enough for expand size */
    t_remainsize = (_GET_DEQUE_COREPOS(t_oldbegin) - _GET_DEQUE_FIRST_POS(t_oldbegin)) /
       _GET_DEQUE_TYPE_SIZE(pt_deque);
    if(t_expandsize < t_remainsize)
    {
        /* set the new begin iterator */
        _GET_DEQUE_COREPOS(pt_deque->_t_start) -=
            t_expandsize * _GET_DEQUE_TYPE_SIZE(pt_deque);
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
            _GET_DEQUE_MAP_POINTER(t_oldbegin) - pt_deque->_ppc_map;
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
            pt_deque->_ppc_map = _alloc_allocate(
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
            _GET_DEQUE_MAP_POINTER(t_oldbegin) = 
                _GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
            /** modify pt_pos **/
            if(pt_pos != NULL)
            {
                _GET_DEQUE_MAP_POINTER(*pt_pos) =
                    _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) + n_posdistance;
            }
            _alloc_deallocate(
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
            _GET_DEQUE_MAP_POINTER(t_oldbegin) += t_movesize;
            if(pt_pos != NULL)
            {
                _GET_DEQUE_MAP_POINTER(*pt_pos) += t_movesize;
            }
        }

        /* allocate the container */
        for(i = 0, ppc_newcontainer = _GET_DEQUE_MAP_POINTER(t_oldbegin) - 1;
            i < (int)t_containersize; 
            ++i, --ppc_newcontainer)
        {
            *ppc_newcontainer = _alloc_allocate(
                &pt_deque->_t_allocater, _GET_DEQUE_TYPE_SIZE(pt_deque), _DEQUE_ELEM_COUNT);
            assert(*ppc_newcontainer != NULL);
        }

        /* set new start iterator */
        _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) = 
            _GET_DEQUE_MAP_POINTER(t_oldbegin) - t_containersize;
        _GET_DEQUE_FIRST_POS(pt_deque->_t_start) = 
            *_GET_DEQUE_MAP_POINTER(pt_deque->_t_start);
        _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start) = 
            _GET_DEQUE_FIRST_POS(pt_deque->_t_start) + 
            _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_COREPOS(pt_deque->_t_start) = 
            _GET_DEQUE_AFTERLAST_POS(pt_deque->_t_start) - 
            t_validfrontsize * _GET_DEQUE_TYPE_SIZE(pt_deque);
    }

    /* the old front is original front */
    if(_GET_DEQUE_COREPOS(t_oldbegin) == _GET_DEQUE_AFTERLAST_POS(t_oldbegin))
    {
        assert(*(_GET_DEQUE_MAP_POINTER(t_oldbegin) + 1) != NULL);
        _GET_DEQUE_MAP_POINTER(t_oldbegin) += 1;
        _GET_DEQUE_FIRST_POS(t_oldbegin) = 
            *_GET_DEQUE_MAP_POINTER(t_oldbegin);
        _GET_DEQUE_AFTERLAST_POS(t_oldbegin) = 
            _GET_DEQUE_FIRST_POS(t_oldbegin) + 
            _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_COREPOS(t_oldbegin) = 
            _GET_DEQUE_FIRST_POS(t_oldbegin);
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
            _DEQUE_ELEM_COUNT * _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_COREPOS(*pt_pos) = 
            _GET_DEQUE_FIRST_POS(*pt_pos);
    }

    /* initialize all new elements */
    _deque_init_elem_range_auxiliary(pt_deque, deque_begin(pt_deque), t_oldbegin);

    return t_oldbegin;
}

void _shrink_at_end(deque_t* pt_deque, size_t t_shrinksize)
{
    deque_iterator_t t_oldend;
    deque_iterator_t t_newend;
    deque_iterator_t t_iter;
    _mappointer_t    ppc_map = NULL;
    bool_t           t_result = false;

    assert(pt_deque != NULL);

    t_oldend = deque_end(pt_deque);
    t_shrinksize = t_shrinksize < deque_size(pt_deque) ? t_shrinksize : deque_size(pt_deque);
    t_newend = iterator_prev_n(deque_end(pt_deque), t_shrinksize);
    assert(_deque_iterator_belong_to_deque(pt_deque, t_newend));

    /* destroy all elements */
    for(t_iter = t_newend;
        !iterator_equal(t_iter, t_oldend);
        t_iter = iterator_next(t_iter))
    {
        t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_TYPE_DESTROY_FUNCTION(pt_deque)(
            _deque_iterator_get_pointer_auxiliary(t_iter), &t_result);
        assert(t_result);
    }
    pt_deque->_t_finish = t_newend;

    for(ppc_map = _GET_DEQUE_MAP_POINTER(pt_deque->_t_finish) + 1;
        ppc_map <= _GET_DEQUE_MAP_POINTER(t_oldend);
        ++ppc_map)
    {
        _alloc_deallocate(&pt_deque->_t_allocater, *ppc_map,
            _GET_DEQUE_TYPE_SIZE(pt_deque), _DEQUE_ELEM_COUNT);
        *ppc_map = NULL;
    }
}

void _shrink_at_begin(deque_t* pt_deque, size_t t_shrinksize)
{
    deque_iterator_t t_oldbegin;
    deque_iterator_t t_newbegin;
    deque_iterator_t t_iter;
    _mappointer_t    ppc_map = NULL;
    bool_t           t_result = false;

    t_oldbegin = deque_begin(pt_deque);
    t_shrinksize = t_shrinksize < deque_size(pt_deque) ? t_shrinksize : deque_size(pt_deque);
    t_newbegin = iterator_next_n(deque_begin(pt_deque), t_shrinksize);
    assert(_deque_iterator_belong_to_deque(pt_deque, t_newbegin));

    /* destroy all elements */
    for(t_iter = t_oldbegin;
        !iterator_equal(t_iter, t_newbegin);
        t_iter = iterator_next(t_iter))
    {
        t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
        _GET_DEQUE_TYPE_DESTROY_FUNCTION(pt_deque)(
            _deque_iterator_get_pointer_auxiliary(t_iter), &t_result);
        assert(t_result);
    }
    pt_deque->_t_start = t_newbegin;

    for(ppc_map = _GET_DEQUE_MAP_POINTER(pt_deque->_t_start) - 1;
        ppc_map >= _GET_DEQUE_MAP_POINTER(t_oldbegin);
        --ppc_map)
    {
        _alloc_deallocate(&pt_deque->_t_allocater, *ppc_map,
            _GET_DEQUE_TYPE_SIZE(pt_deque), _DEQUE_ELEM_COUNT);
        *ppc_map = NULL;
    }
}

deque_iterator_t _move_elem_to_end(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end, size_t t_movesize)
{
    /* if t_begin != t_end then do move */
    if(!iterator_equal(t_begin, t_end) && t_movesize != 0)
    {
        /* the target range of move */
        deque_iterator_t t_targetbegin;
        deque_iterator_t t_targetend;
        bool_t           t_result = false;

        assert(_deque_iterator_belong_to_deque(pt_deque, t_begin));
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
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_targetend),
                _deque_iterator_get_pointer_auxiliary(t_end), &t_result);
            assert(t_result);
        }

        t_targetend = iterator_next(t_targetend);
        t_end = iterator_next(t_end);
        assert(iterator_equal(t_begin, t_end) && iterator_equal(t_targetbegin, t_targetend));
    }

    return t_begin;
}

deque_iterator_t _move_elem_to_begin(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end, size_t t_movesize)
{
    if(!iterator_equal(t_begin, t_end) && t_movesize != 0)
    {
        deque_iterator_t t_targetbegin;
        deque_iterator_t t_targetend;
        bool_t           t_result = false;

        assert(_deque_iterator_belong_to_deque(pt_deque, t_begin));
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
            t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_COPY_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_targetbegin),
                _deque_iterator_get_pointer_auxiliary(t_begin), &t_result);
            assert(t_result);
        }

        assert(iterator_equal(t_targetbegin, t_targetend) && iterator_equal(t_begin, t_end));

        return t_targetend;
    }
    else
    {
        return iterator_prev_n(t_end, t_movesize);
    }
}

void _deque_get_varg_value_auxiliary(
    deque_t* pt_deque, va_list val_elemlist, void* pv_varg)
{
    _deque_init_elem_auxiliary(pt_deque, pv_varg);
    _type_get_varg_value(&pt_deque->_t_typeinfo, val_elemlist, pv_varg);
}

void _deque_destroy_varg_value_auxiliary(deque_t* pt_deque, void* pv_varg)
{
    /* destroy varg value and free memory */
    bool_t t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
    _GET_DEQUE_TYPE_DESTROY_FUNCTION(pt_deque)(pv_varg, &t_result);
    assert(t_result);
}

void _deque_init_elem_range_auxiliary(
    deque_t* pt_deque, deque_iterator_t t_begin, deque_iterator_t t_end)
{
    deque_iterator_t t_iter;

    assert(pt_deque != NULL);

    /* initialize new elements */
    if(_GET_DEQUE_TYPE_STYLE(pt_deque) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_DEQUE_TYPE_NAME(pt_deque), s_elemtypename);

        for(t_iter = t_begin; !iterator_equal(t_iter, t_end); t_iter = iterator_next(t_iter))
        {
            _GET_DEQUE_TYPE_INIT_FUNCTION(pt_deque)(
                iterator_get_pointer(t_iter), s_elemtypename);
        }
    }
    else
    {
        for(t_iter = t_begin; !iterator_equal(t_iter, t_end); t_iter = iterator_next(t_iter))
        {
            bool_t t_result = _GET_DEQUE_TYPE_SIZE(pt_deque);
            _GET_DEQUE_TYPE_INIT_FUNCTION(pt_deque)(
                _deque_iterator_get_pointer_auxiliary(t_iter), &t_result);
            assert(t_result);
        }
    }
}

void* _deque_iterator_get_pointer_auxiliary(iterator_t t_iter)
{
    char* pc_pos = NULL;

    assert(_deque_iterator_belong_to_deque(_GET_DEQUE_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, deque_end(_GET_DEQUE_CONTAINER(t_iter))));

    if(_GET_DEQUE_COREPOS(t_iter) != _GET_DEQUE_AFTERLAST_POS(t_iter))
    {
        pc_pos = _GET_DEQUE_COREPOS(t_iter);
    }
    else
    {
        /* 
         * when the iterator is begin and the corepos equal to afterlast 
         * then get the first element in next container.
         */
        _mappointer_t t_nextcontainer = _GET_DEQUE_MAP_POINTER(t_iter) + 1;
        pc_pos = *t_nextcontainer;
    }
    assert(pc_pos != NULL);

    return pc_pos;
}

/** local function implementation section **/

/** eof **/

