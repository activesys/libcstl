/*
 *  The implementation of slist private function.
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
#include <cstl/cfunctional.h>

#include <cstl/cstl_slist_iterator.h>
#include <cstl/cstl_slist_private.h>
#include <cstl/cstl_slist.h>

#include <cstl/cstring.h>

#include "cstl_slist_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/

/* slist private function */
slist_t* _create_slist(const char* s_typename)
{
    slist_t*    pt_newslist = NULL;

    /* allocate memory for slist */
    if((pt_newslist = (slist_t*)malloc(sizeof(slist_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_slist_auxiliary(pt_newslist, s_typename))
    {
        free(pt_newslist);
        return NULL;
    }

    return pt_newslist;
}

bool_t _create_slist_auxiliary(slist_t* pt_slist, const char* s_typename)
{
    assert(pt_slist != NULL && s_typename != NULL);

    _type_get_type(&pt_slist->_t_typeinfo, s_typename);
    if(pt_slist->_t_typeinfo._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pt_slist->_t_head._pt_next = NULL;

    _alloc_init(&pt_slist->_t_allocater);
    return true;
}


void _slist_init_elem(slist_t* pt_slist, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _slist_init_elem_varg(pt_slist, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _slist_init_elem_varg(slist_t* pt_slist, size_t t_count, va_list val_elemlist)
{
    slistnode_t* pt_varg = NULL;
    bool_t       t_result = false;

    assert(pt_slist != NULL && pt_slist->_t_head._pt_next == NULL);

    /* initialize the allocator */
    /*_alloc_init(&pt_slist->_t_allocater);*/

    /* allocate memory for n_elemcount slist node */
    if(t_count > 0)
    {
        size_t t_index = 0;
        slistnode_t* pt_slistnode = NULL;

        /* get varg value only once */
        pt_varg = _alloc_allocate(&pt_slist->_t_allocater,
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
        assert(pt_varg != NULL);
        _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

        for(t_index = 0; t_index < t_count; ++t_index)
        {
            pt_slistnode = _alloc_allocate(&pt_slist->_t_allocater,
                _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
            assert(pt_slistnode != NULL);
            _slist_init_node_auxiliary(pt_slist, pt_slistnode);
            /* copy value from varg */
            t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)(
                pt_slistnode->_pc_data, pt_varg->_pc_data, &t_result);
            assert(t_result);

            /* insert the new slist node after the head */
            pt_slistnode->_pt_next = pt_slist->_t_head._pt_next;
            pt_slist->_t_head._pt_next = pt_slistnode;
            pt_slistnode = NULL;
        }

        _slist_destroy_varg_value_auxiliary(pt_slist, pt_varg);
        _alloc_deallocate(&pt_slist->_t_allocater, pt_varg,
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    }
}


void _slist_destroy_auxiliary(slist_t* pt_slist)
{
    slistnode_t* pt_slistnode = NULL;
    bool_t       t_result = false;

    /* test the pt_slist is valid */
    assert(pt_slist != NULL);

    /* _alloc_deallocate all nodes in slist */
    while(pt_slist->_t_head._pt_next != NULL)
    {
        pt_slistnode = pt_slist->_t_head._pt_next;
        /* take out each node from the slist */
        pt_slist->_t_head._pt_next = pt_slistnode->_pt_next;
        pt_slistnode->_pt_next = NULL;

        /* destroy the node itself */
        t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)(pt_slistnode->_pc_data, &t_result);
        assert(t_result);
        _alloc_deallocate(&pt_slist->_t_allocater, pt_slistnode, 
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
        pt_slistnode = NULL;
    }

    /* _alloc_deallocate the allocator */
    _alloc_destroy(&pt_slist->_t_allocater);
}


void _slist_assign_elem(slist_t* pt_slist, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _slist_assign_elem_varg(pt_slist, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _slist_assign_elem_varg(slist_t* pt_slist, size_t t_count, va_list val_elemlist)
{
    slist_iterator_t t_iter;
    slistnode_t*     pt_varg = NULL;
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    slist_resize(pt_slist, t_count);

    /* get varg value */
    pt_varg = _alloc_allocate(&pt_slist->_t_allocater,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    assert(pt_varg != NULL);
    _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

    /* copy value from varg */
    for(t_iter = slist_begin(pt_slist);
        !iterator_equal(t_iter, slist_end(pt_slist));
        t_iter = iterator_next(t_iter))
    {
        t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data,
            pt_varg->_pc_data, &t_result);
        assert(t_result);
    }

    /* destroy varg value */
    _slist_destroy_varg_value_auxiliary(pt_slist, pt_varg);
    _alloc_deallocate(&pt_slist->_t_allocater, pt_varg,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
}


void _slist_push_front(slist_t* pt_slist, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_slist);
    _slist_push_front_varg(pt_slist, val_elemlist);
    va_end(val_elemlist);
}

void _slist_push_front_varg(slist_t* pt_slist, va_list val_elemlist)
{
    slistnode_t* pt_slistnode = NULL;

    assert(pt_slist != NULL);

    /* allocate memory for new element and copy the element from elemlist */
    pt_slistnode = _alloc_allocate(&pt_slist->_t_allocater,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    assert(pt_slistnode != NULL);
    _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_slistnode);

    /* insert the element after the head */
    pt_slistnode->_pt_next = pt_slist->_t_head._pt_next;
    pt_slist->_t_head._pt_next = pt_slistnode;
}


slist_iterator_t _slist_insert(slist_t* pt_slist, slist_iterator_t t_pos, ...)
{
    va_list val_elemlist;

    /* test the list pointer and pos is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));

    /* if the pos is slist begin iterator */
    va_start(val_elemlist, t_pos);
    if(iterator_equal(t_pos, slist_begin(pt_slist)))
    {
        /* call push front */
        _slist_push_front_varg(pt_slist, val_elemlist);
    }
    else
    {
        /* call insert_after */
        _slist_insert_after_n_varg(pt_slist, slist_previous(pt_slist, t_pos), 1, val_elemlist);
    }
    va_end(val_elemlist);

    /* return the new element iterator */
    return slist_previous(pt_slist, t_pos);
}

slist_iterator_t _slist_insert_after(
    slist_t* pt_slist, slist_iterator_t t_pos, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    _slist_insert_after_n_varg(pt_slist, t_pos, 1, val_elemlist);
    va_end(val_elemlist);
    t_pos = iterator_next(t_pos);

    return t_pos;
}

void _slist_insert_n(
    slist_t* pt_slist, slist_iterator_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;

    /* test the slist pointer and pos is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));

    /* if the pos is slist begin */
    va_start(val_elemlist, t_count);
    if(iterator_equal(t_pos, slist_begin(pt_slist)))
    {
        size_t t_index = 0;
        /* call slist push front n_elemcount times */
        for(t_index = 0; t_index < t_count; ++t_index)
        {
            va_list val_elemlist_copy;

            va_copy(val_elemlist_copy, val_elemlist);
            _slist_push_front_varg(pt_slist, val_elemlist_copy);
            va_end(val_elemlist_copy);
        }
    }
    /* else get the previous iterator */
    else
    {
        va_list val_elemlist_copy;

        /* call slist insert after n function */
        va_copy(val_elemlist_copy, val_elemlist);
        _slist_insert_after_n_varg(
            pt_slist, slist_previous(pt_slist, t_pos), t_count, val_elemlist_copy);
        va_end(val_elemlist_copy);
    }
    va_end(val_elemlist);
}

void _slist_insert_after_n(
    slist_t* pt_slist, slist_iterator_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _slist_insert_after_n_varg(pt_slist, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _slist_insert_after_n_varg(
    slist_t* pt_slist, slist_iterator_t t_pos, size_t t_count, va_list val_elemlist)
{
    size_t       t_index = 0;
    slistnode_t* pt_slistnode = NULL;
    slistnode_t* pt_varg = NULL;
    bool_t       t_result = false;

    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(!iterator_equal(t_pos, slist_end(pt_slist)));

    /* get varg value only once */
    pt_varg = _alloc_allocate(&pt_slist->_t_allocater,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    assert(pt_varg != NULL);
    _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

    for(t_index = 0; t_index < t_count; ++t_index)
    {
        /* allocate slist node */
        pt_slistnode = _alloc_allocate(&pt_slist->_t_allocater,
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
        assert(pt_slistnode != NULL);
        _slist_init_node_auxiliary(pt_slist, pt_slistnode);

        /* copy value from varg */
        t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)(
            pt_slistnode->_pc_data, pt_varg->_pc_data, &t_result);
        assert(t_result);

        /* link the node to slist */
        pt_slistnode->_pt_next = ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pt_next;
        ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pt_next = pt_slistnode;
        pt_slistnode = NULL;
    }

    /* destroy varg value */
    _slist_destroy_varg_value_auxiliary(pt_slist, pt_varg);
    _alloc_deallocate(&pt_slist->_t_allocater, pt_varg,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
}


void _slist_remove(slist_t* pt_slist, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_slist);
    _slist_remove_varg(pt_slist, val_elemlist);
    va_end(val_elemlist);
}

void _slist_remove_varg(slist_t* pt_slist, va_list val_elemlist)
{
    slist_iterator_t t_iter; /* for iterate */
    slistnode_t*     pt_varg = NULL;
    bool_t           t_less = false;
    bool_t           t_greater = false;

    /* test the pointer is valid */
    assert(pt_slist != NULL);

    pt_varg = _alloc_allocate(&pt_slist->_t_allocater,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    assert(pt_varg != NULL);
    _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

    t_iter = slist_begin(pt_slist);
    while(!iterator_equal(t_iter, slist_end(pt_slist)))
    {
        t_less = t_greater = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
            pt_varg->_pc_data, ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, &t_less);
        _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, pt_varg->_pc_data, &t_greater);
        if(t_less || t_greater)
        {
            t_iter = iterator_next(t_iter);
        }
        else
        {
            t_iter = slist_erase(pt_slist, t_iter);
        }
    }

    _slist_destroy_varg_value_auxiliary(pt_slist, pt_varg);
    _alloc_deallocate(&pt_slist->_t_allocater, pt_varg,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
}


void _slist_resize_elem(slist_t* pt_slist, size_t t_resize, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_resize);
    _slist_resize_elem_varg(pt_slist, t_resize, val_elemlist);
    va_end(val_elemlist);
}

void _slist_resize_elem_varg(slist_t* pt_slist, size_t t_resize, va_list val_elemlist)
{
    slist_iterator_t t_pos;
    size_t           t_index = 0;
    slistnode_t*     pt_varg = NULL;

    assert(pt_slist != NULL);

    for(t_index = 0, t_pos = slist_begin(pt_slist);
        t_index < t_resize && !iterator_equal(t_pos, slist_end(pt_slist));
        ++t_index, t_pos = iterator_next(t_pos))
    {
        continue;
    }

    if(t_index == t_resize)
    {
        if(!iterator_equal(t_pos, slist_end(pt_slist)))
        {
            slist_erase_range(pt_slist, t_pos, slist_end(pt_slist));
        }
    }
    else
    {
        slist_iterator_t t_slistlast;
        slistnode_t*     pt_slistnode = NULL;
        size_t           t_slistsize = slist_size(pt_slist);
        bool_t           t_result = false;

        if(!slist_empty(pt_slist))
        {
            t_slistlast = slist_previous(pt_slist, slist_end(pt_slist));
        }
        else
        {
            _GET_SLIST_COREPOS(t_slistlast) = (char*)&pt_slist->_t_head;
        }

        /* get varg value only once */
        pt_varg = _alloc_allocate(&pt_slist->_t_allocater,
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
        assert(pt_varg != NULL);
        _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

        for(t_index = 0; t_index < t_resize - t_slistsize; ++t_index)
        {
            pt_slistnode = _alloc_allocate(&pt_slist->_t_allocater,
                _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
            assert(pt_slistnode != NULL);
            _slist_init_node_auxiliary(pt_slist, pt_slistnode);

            /* copy value from varg */
            t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)(
                pt_slistnode->_pc_data, pt_varg->_pc_data, &t_result);
            assert(t_result);

            pt_slistnode->_pt_next = ((slistnode_t*)_GET_SLIST_COREPOS(t_slistlast))->_pt_next;
            ((slistnode_t*)_GET_SLIST_COREPOS(t_slistlast))->_pt_next = pt_slistnode;
            pt_slistnode = NULL;
        }

        _slist_destroy_varg_value_auxiliary(pt_slist, pt_varg);
        _alloc_deallocate(&pt_slist->_t_allocater, pt_varg, 
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    }
}

void _slist_init_elem_auxiliary(slist_t* pt_slist, void* pv_value)
{
    assert(pt_slist != NULL && pv_value != NULL);

    /* initialize new elements */
    if(_GET_SLIST_TYPE_STYLE(pt_slist) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_SLIST_TYPE_NAME(pt_slist), s_elemtypename);

        _GET_SLIST_TYPE_INIT_FUNCTION(pt_slist)(pv_value, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_INIT_FUNCTION(pt_slist)(pv_value, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/

/** eof **/

