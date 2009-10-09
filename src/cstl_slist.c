/*
 *  The implementation of slist.
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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_iterator_private.h"
#include "cfunctional.h"

#include "cstl_slist_iterator.h"
#include "cstl_slist_private.h"
#include "cstl_slist.h"

#include "cstring.h"

/** local constant declaration and local macro section **/
#define _SLIST_NODE_SIZE(typesize)\
    ((typesize) + sizeof(slistnode_t) - 1)

/* macros for type informations */
#define _GET_SLIST_TYPE_SIZE(pt_slist)\
    ((pt_slist)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_SLIST_TYPE_NAME(pt_slist)\
    ((pt_slist)->_t_typeinfo._sz_typename)
#define _GET_SLIST_TYPE_BASENAME(pt_slist)\
    ((pt_slist)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_SLIST_TYPE_INIT_FUNCTION(pt_slist)\
    ((pt_slist)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)\
    ((pt_slist)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)\
    ((pt_slist)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)\
    ((pt_slist)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_SLIST_TYPE_STYLE(pt_slist)\
    ((pt_slist)->_t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Iterator support for assert.
 */
static bool_t _slist_iterator_belong_to_slist(
    const slist_t* cpt_slist, slist_iterator_t t_iter);
static bool_t _slist_same_slist_iterator_type(
    const slist_t* cpt_slist, slist_iterator_t t_iter);
#endif /* NDEBUG */
static bool_t _slist_same_type(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond);

/*
 * Transfer functions.
 */
static void _transfer(
    slist_iterator_t t_pos, slist_iterator_t t_begin, slist_iterator_t t_end);
static void _transfer_after(
    slist_iterator_t t_pos, slist_iterator_t t_begin, slist_iterator_t t_end);

static void _slist_get_varg_value_auxiliary(
    slist_t* pt_slist, va_list val_elemlist, slistnode_t* pt_node);
static void _slist_destroy_varg_value_auxiliary(slist_t* pt_slist, slistnode_t* pt_node);
static void _slist_init_node_auxiliary(slist_t* pt_slist, slistnode_t* pt_node);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* slist iterator function */
slist_iterator_t create_slist_iterator(void)
{
    slist_iterator_t t_newiterator;

    _GET_SLIST_ITERATOR_TYPE(t_newiterator) = _FORWARD_ITERATOR;
    _GET_SLIST_CONTAINER_TYPE(t_newiterator) = _SLIST_CONTAINER;
    _GET_CONTAINER(t_newiterator) = NULL;
    _GET_SLIST_COREPOS(t_newiterator) = NULL;

    return t_newiterator;
}

void _slist_iterator_get_value(slist_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_slist_iterator_belong_to_slist(_GET_SLIST_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, slist_end(_GET_SLIST_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_SLIST_TYPE_BASENAME(_GET_SLIST_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str(
            (string_t*)((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        bool_t t_result = _GET_SLIST_TYPE_SIZE(_GET_SLIST_CONTAINER(t_iter));
        _GET_SLIST_TYPE_COPY_FUNCTION(_GET_SLIST_CONTAINER(t_iter))(
            pv_value, ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, &t_result);
        assert(t_result);
    }
}

void _slist_iterator_set_value(slist_iterator_t t_iter, const void* cpv_value)
{
    assert(cpv_value != NULL);
    assert(_slist_iterator_belong_to_slist(_GET_SLIST_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, slist_end(_GET_SLIST_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_SLIST_TYPE_BASENAME(_GET_SLIST_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        string_assign_cstr(
            (string_t*)((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, (char*)cpv_value);
    }
    else
    {
        bool_t t_result = _GET_SLIST_TYPE_SIZE(_GET_SLIST_CONTAINER(t_iter));
        _GET_SLIST_TYPE_COPY_FUNCTION(_GET_SLIST_CONTAINER(t_iter))(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, cpv_value, &t_result);
        assert(t_result);
    }
}

bool_t _slist_iterator_equal(
    slist_iterator_t t_iterfirst, slist_iterator_t t_itersecond)
{
    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_SLIST_CONTAINER(t_iterfirst) == _GET_SLIST_CONTAINER(t_itersecond));
    assert(_slist_iterator_belong_to_slist(_GET_SLIST_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_slist_iterator_belong_to_slist(_GET_SLIST_CONTAINER(t_itersecond), t_itersecond));

    if(_GET_SLIST_COREPOS(t_iterfirst) == _GET_SLIST_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

const void* _slist_iterator_get_pointer(slist_iterator_t t_iter)
{
    assert(_slist_iterator_belong_to_slist(_GET_SLIST_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, slist_end(_GET_SLIST_CONTAINER(t_iter))));

    /* char* */
    if(strncmp(_GET_SLIST_TYPE_BASENAME(_GET_SLIST_CONTAINER(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return string_c_str((string_t*)((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        return ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data;
    }
}

slist_iterator_t _slist_iterator_next(slist_iterator_t t_iter)
{
    assert(_slist_iterator_belong_to_slist(_GET_SLIST_CONTAINER(t_iter), t_iter));
    assert(!iterator_equal(t_iter, slist_end(_GET_SLIST_CONTAINER(t_iter))));

    _GET_SLIST_COREPOS(t_iter) = (char*)(((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pt_next);

    return t_iter;
}

int _slist_iterator_distance(
    slist_iterator_t t_iterfirst, slist_iterator_t t_itersecond)
{
    int n_distance = 0;
    slistnode_t* pt_slistnode = NULL;

    if(_slist_iterator_before(t_iterfirst, t_itersecond))
    {
        for(pt_slistnode = (slistnode_t*)_GET_SLIST_COREPOS(t_iterfirst);
            pt_slistnode != (slistnode_t*)_GET_SLIST_COREPOS(t_itersecond);
            pt_slistnode = pt_slistnode->_pt_next)
        {
            n_distance++;
        }

        return n_distance;
    }
    else if(_slist_iterator_before(t_itersecond, t_iterfirst))
    {
        for(pt_slistnode = (slistnode_t*)_GET_SLIST_COREPOS(t_itersecond);
            pt_slistnode != (slistnode_t*)_GET_SLIST_COREPOS(t_iterfirst);
            pt_slistnode = pt_slistnode->_pt_next)
        {
            n_distance++;
        }

        return -n_distance;
    }
    else
    {
        return 0;
    }
}

bool_t _slist_iterator_before(
    slist_iterator_t t_iterfirst, slist_iterator_t t_itersecond)
{
    slistnode_t* pt_slistnode = NULL;

    assert(_iterator_same_type(t_iterfirst, t_itersecond));
    assert(_GET_SLIST_CONTAINER(t_iterfirst) == _GET_SLIST_CONTAINER(t_itersecond));
    assert(_slist_iterator_belong_to_slist(_GET_SLIST_CONTAINER(t_iterfirst), t_iterfirst));
    assert(_slist_iterator_belong_to_slist(_GET_SLIST_CONTAINER(t_itersecond), t_itersecond));
    assert(_GET_SLIST_CONTAINER(t_iterfirst) != NULL &&
           _GET_SLIST_CONTAINER(t_itersecond) != NULL);

    if(_GET_SLIST_COREPOS(t_iterfirst) == _GET_SLIST_COREPOS(t_itersecond))
    {
        return false;
    }

    for(pt_slistnode = (slistnode_t*)_GET_SLIST_COREPOS(t_iterfirst);
        pt_slistnode != NULL;
        pt_slistnode = pt_slistnode->_pt_next)
    {
        if(pt_slistnode == (slistnode_t*)_GET_SLIST_COREPOS(t_itersecond))
        {
            return true;
        }
    }

    if(_GET_SLIST_COREPOS(t_itersecond) == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

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

    return true;
}

/* slist function */
void slist_init(slist_t* pt_slist)
{
    slist_init_n(pt_slist, 0);
}

void slist_init_n(slist_t* pt_slist, size_t t_count)
{
    assert(pt_slist != NULL && pt_slist->_t_head._pt_next == NULL);

    /* initialize the allocator */
    allocate_init(&pt_slist->_t_allocater);

    /* allocate memory for n_elemcount slist node */
    if(t_count > 0)
    {
        size_t t_index = 0;
        slistnode_t* pt_slistnode = NULL;

        for(t_index = 0; t_index < t_count; ++t_index)
        {
            pt_slistnode = allocate(&pt_slist->_t_allocater,
                _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
            assert(pt_slistnode != NULL);
            _slist_init_node_auxiliary(pt_slist, pt_slistnode);

            /* insert the new slist node after the head */
            pt_slistnode->_pt_next = pt_slist->_t_head._pt_next;
            pt_slist->_t_head._pt_next = pt_slistnode;
            pt_slistnode = NULL;
        }
    }
}

void _slist_init_elem(slist_t* pt_slist, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _slist_init_elem_varg(pt_slist, t_count, val_elemlist);
}

void _slist_init_elem_varg(slist_t* pt_slist, size_t t_count, va_list val_elemlist)
{
    slistnode_t* pt_varg = NULL;
    bool_t       t_result = false;

    assert(pt_slist != NULL && pt_slist->_t_head._pt_next == NULL);

    /* initialize the allocator */
    allocate_init(&pt_slist->_t_allocater);

    /* allocate memory for n_elemcount slist node */
    if(t_count > 0)
    {
        size_t t_index = 0;
        slistnode_t* pt_slistnode = NULL;

        /* get varg value only once */
        pt_varg = allocate(&pt_slist->_t_allocater,
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
        assert(pt_varg != NULL);
        _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

        for(t_index = 0; t_index < t_count; ++t_index)
        {
            pt_slistnode = allocate(&pt_slist->_t_allocater,
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
        deallocate(&pt_slist->_t_allocater, pt_varg,
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    }
}

void slist_destroy(slist_t* pt_slist)
{
    _slist_destroy_auxiliary(pt_slist);
    free(pt_slist);
}

void _slist_destroy_auxiliary(slist_t* pt_slist)
{
    slistnode_t* pt_slistnode = NULL;
    bool_t       t_result = false;

    /* test the pt_slist is valid */
    assert(pt_slist != NULL);

    /* deallocate all nodes in slist */
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
        deallocate(&pt_slist->_t_allocater, pt_slistnode, 
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
        pt_slistnode = NULL;
    }

    /* deallocate the allocator */
    allocate_destroy(&pt_slist->_t_allocater);
}

slist_iterator_t slist_begin(const slist_t* cpt_slist)
{
    slist_iterator_t t_newiterator;

    assert(cpt_slist != NULL);

    /* create new slist iterator */
    t_newiterator = create_slist_iterator();
    /* the core pos point to the node after head */
    _GET_CONTAINER(t_newiterator) = (slist_t*)cpt_slist;
    _GET_SLIST_COREPOS(t_newiterator) = (char*)(cpt_slist->_t_head._pt_next);

    return t_newiterator;
}

slist_iterator_t slist_end(const slist_t* cpt_slist)
{
    slist_iterator_t t_newiterator;

    assert(cpt_slist != NULL);

    /* create new slist iterator */
    t_newiterator = create_slist_iterator();
    /* the end iterator core pos equal to NULL */
    _GET_CONTAINER(t_newiterator) = (slist_t*)cpt_slist;
    _GET_SLIST_COREPOS(t_newiterator) = NULL;

    return t_newiterator;
}

size_t slist_size(const slist_t* cpt_slist)
{
    slistnode_t* pt_slistnode = NULL;
    size_t       t_slistsize = 0;

    assert(cpt_slist != NULL);

    /* iterate all element and count the size */
    for(pt_slistnode = cpt_slist->_t_head._pt_next;
        pt_slistnode != NULL;
        pt_slistnode = pt_slistnode->_pt_next)
    {
        t_slistsize++;
    }

    return t_slistsize;
}

bool_t slist_empty(const slist_t* cpt_slist)
{
    assert(cpt_slist != NULL);

    if(cpt_slist->_t_head._pt_next == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t slist_max_size(const slist_t* cpt_slist)
{
    assert(cpt_slist != NULL);

    return (size_t)(-1) / _GET_SLIST_TYPE_SIZE(cpt_slist);
}

void slist_init_copy(slist_t* pt_slistdest, const slist_t* cpt_slistsrc)
{
    slist_init_copy_range(
        pt_slistdest, slist_begin(cpt_slistsrc), slist_end(cpt_slistsrc));
}

void slist_init_copy_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end)
{
    slist_iterator_t t_dest;
    slist_iterator_t t_src;
    bool_t           t_result = false;

    /* test the dest slist and [t_begin, t_end) is valid */
    assert(pt_slist != NULL && pt_slist->_t_head._pt_next == NULL);
    assert(_slist_same_slist_iterator_type(pt_slist, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));

    /* initialize the dest slist use the iterator slist */
    slist_init_n(pt_slist, iterator_distance(t_begin, t_end));
    /* copy the element from range [t_begin, t_end) to dest slist */
    for(t_dest = slist_begin(pt_slist), t_src = t_begin;
        !iterator_equal(t_dest, slist_end(pt_slist)) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_dest))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_src))->_pc_data, &t_result);
        assert(t_result);
    } 
    assert(iterator_equal(t_dest, slist_end(pt_slist)) && iterator_equal(t_src, t_end));
}

void slist_assign(slist_t* pt_slistdest, const slist_t* cpt_slistsrc)
{
    slist_assign_range(pt_slistdest, slist_begin(cpt_slistsrc), slist_end(cpt_slistsrc));
}

void _slist_assign_elem(slist_t* pt_slist, size_t t_count, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_count);
    _slist_assign_elem_varg(pt_slist, t_count, val_elemlist);
}

void _slist_assign_elem_varg(slist_t* pt_slist, size_t t_count, va_list val_elemlist)
{
    slist_iterator_t t_iter;
    slistnode_t*     pt_varg = NULL;
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    slist_resize(pt_slist, t_count);

    /* get varg value */
    pt_varg = allocate(&pt_slist->_t_allocater,
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
    deallocate(&pt_slist->_t_allocater, pt_varg,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
}

void slist_assign_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end)
{
    slist_iterator_t t_dest;
    slist_iterator_t t_src;
    bool_t           t_result = false;

    /* test the dest slist and [t_begin, t_end) is valid */
    assert(_slist_same_slist_iterator_type(pt_slist, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));

    slist_resize(pt_slist, iterator_distance(t_begin, t_end));

    /* copy value from [t_begin, t_end) */
    for(t_dest = slist_begin(pt_slist), t_src = t_begin;
        !iterator_equal(t_dest, slist_end(pt_slist)) && !iterator_equal(t_src, t_end);
        t_dest = iterator_next(t_dest), t_src = iterator_next(t_src))
    {
        t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_dest))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_src))->_pc_data, &t_result);
        assert(t_result);
    }
}

void slist_swap(slist_t* pt_slistfirst, slist_t* pt_slistsecond)
{
    slist_t t_slisttmp;  /* for swap */

    assert(_slist_same_type(pt_slistfirst, pt_slistsecond));

    t_slisttmp = *pt_slistfirst;
    *pt_slistfirst = *pt_slistsecond;
    *pt_slistsecond = t_slisttmp;
}

void* slist_front(const slist_t* cpt_slist)
{
    assert(cpt_slist != NULL);

    if(slist_empty(cpt_slist))
    {
        return NULL;
    }
    else if(strncmp(_GET_SLIST_TYPE_BASENAME(cpt_slist), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str((string_t*)cpt_slist->_t_head._pt_next->_pc_data);
    }
    else
    {
        return cpt_slist->_t_head._pt_next->_pc_data;
    }
}

void _slist_push_front(slist_t* pt_slist, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_slist);
    _slist_push_front_varg(pt_slist, val_elemlist);
}

void _slist_push_front_varg(slist_t* pt_slist, va_list val_elemlist)
{
    slistnode_t* pt_slistnode = NULL;

    assert(pt_slist != NULL);

    /* allocate memory for new element and copy the element from elemlist */
    pt_slistnode = allocate(&pt_slist->_t_allocater,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    assert(pt_slistnode != NULL);
    _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_slistnode);

    /* insert the element after the head */
    pt_slistnode->_pt_next = pt_slist->_t_head._pt_next;
    pt_slist->_t_head._pt_next = pt_slistnode;
}

void slist_pop_front(slist_t* pt_slist)
{
    slistnode_t* pt_slistnode = NULL;
    bool_t       t_result = false;

    assert(pt_slist != NULL);
    assert(slist_size(pt_slist) > 0);

    /* take out the front slist node */
    pt_slistnode = pt_slist->_t_head._pt_next;
    assert(pt_slistnode != NULL);
    pt_slist->_t_head._pt_next = pt_slistnode->_pt_next;

    t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
    _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)(pt_slistnode->_pc_data, &t_result);
    assert(t_result);
    deallocate(&pt_slist->_t_allocater, pt_slistnode, 
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
}

slist_iterator_t slist_previous(
    const slist_t* cpt_slist, slist_iterator_t t_pos)
{
    slist_iterator_t t_previous;
    slist_iterator_t t_iterator;

    /* test slist pointer and t_pos is valid */
    assert(_slist_iterator_belong_to_slist(cpt_slist, t_pos));
    assert(!iterator_equal(t_pos, slist_begin(cpt_slist)));

    t_previous = slist_begin(cpt_slist);
    t_iterator = t_previous;
    t_iterator = iterator_next(t_iterator);
    while(!iterator_equal(t_iterator, t_pos))
    {
        t_iterator = iterator_next(t_iterator);
        t_previous = iterator_next(t_previous);
    }

    return t_previous;
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

    /* return the new element iterator */
    return slist_previous(pt_slist, t_pos);
}

slist_iterator_t _slist_insert_after(
    slist_t* pt_slist, slist_iterator_t t_pos, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_pos);
    _slist_insert_after_n_varg(pt_slist, t_pos, 1, val_elemlist);
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
            _slist_push_front_varg(pt_slist, val_elemlist);
        }
    }
    /* else get the previous iterator */
    else
    {
        /* call slist insert after n function */
        _slist_insert_after_n_varg(
            pt_slist, slist_previous(pt_slist, t_pos), t_count, val_elemlist);
    }
}

void _slist_insert_after_n(
    slist_t* pt_slist, slist_iterator_t t_pos, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _slist_insert_after_n_varg(pt_slist, t_pos, t_count, val_elemlist);
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
    pt_varg = allocate(&pt_slist->_t_allocater,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    assert(pt_varg != NULL);
    _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

    for(t_index = 0; t_index < t_count; ++t_index)
    {
        /* allocate slist node */
        pt_slistnode = allocate(&pt_slist->_t_allocater,
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
    deallocate(&pt_slist->_t_allocater, pt_varg,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
}


void slist_insert_range(
    slist_t* pt_slist, slist_iterator_t t_pos,
    slist_iterator_t t_begin, slist_iterator_t t_end)
{
    /* test the slist pointer and pos is valide */
    /* test the range [t_begin, t_end) is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_same_slist_iterator_type(pt_slist, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));

    /* if pos is equal to slist begin iterator */
    if(iterator_equal(t_pos, slist_begin(pt_slist)))
    {
        slistnode_t*     pt_begin = NULL;
        slistnode_t*     pt_end = NULL;
        slistnode_t*     pt_slistnode = NULL;
        slist_iterator_t t_iter;
        bool_t           t_result = false;

        for(t_iter= t_begin; !iterator_equal(t_iter, t_end); t_iter= iterator_next(t_iter))
        {
            pt_slistnode = allocate(&pt_slist->_t_allocater,
                _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
            assert(pt_slistnode != NULL);
            _slist_init_node_auxiliary(pt_slist, pt_slistnode);

            /* copy value form range [t_begin, t_end) */
            t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)(pt_slistnode->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, &t_result);
            assert(t_result);

            /* make new node link */
            if(pt_begin == NULL)
            {
                assert(pt_end == NULL);
                pt_begin = pt_end = pt_slistnode;
            }
            else
            {
                assert(pt_end != NULL);
                pt_end->_pt_next = pt_slistnode;
                pt_end = pt_slistnode;
            }
            pt_slistnode = NULL;
        }

        /* insert the range into front pos */
        if(pt_begin != NULL && pt_end != NULL)
        {
            pt_end->_pt_next = pt_slist->_t_head._pt_next;
            pt_slist->_t_head._pt_next = pt_begin;
        }
    }
    else
    {
        /* call slist insert after range */
        slist_insert_after_range(pt_slist, slist_previous(pt_slist, t_pos), t_begin, t_end);
    }
}

void slist_insert_after_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_iterator_t t_begin, slist_iterator_t t_end)
{
    slistnode_t*     pt_begin = NULL;    /* the first node of duplicate list */
    slistnode_t*     pt_end = NULL;      /* the last node of duplicate list */
    slistnode_t*     pt_slistnode = NULL;
    slist_iterator_t t_iter;
    bool_t           t_result = false;

    /* test the slist pointer and pos is valid */
    /* test the range [t_begin, t_end) is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(!iterator_equal(t_pos, slist_end(pt_slist)));
    assert(_slist_same_slist_iterator_type(pt_slist, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));

    /* allocate new elements and copy the element from range */
    for(t_iter= t_begin; !iterator_equal(t_iter, t_end); t_iter = iterator_next(t_iter))
    {
        pt_slistnode = allocate(&pt_slist->_t_allocater,
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
        assert(pt_slistnode != NULL);
        _slist_init_node_auxiliary(pt_slist, pt_slistnode);

        /* copy value from [t_begin, t_end) */
        t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pt_slist)(pt_slistnode->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, &t_result);
        assert(t_result);

        /* make new node link */
        if(pt_begin == NULL)
        {
            assert(pt_end == NULL);
            pt_begin = pt_end = pt_slistnode;
        }
        else
        {
            assert(pt_end != NULL);
            pt_end->_pt_next = pt_slistnode;
            pt_end = pt_slistnode;
        }
        pt_slistnode = NULL;
    }

    /* insert the range into the pos */
    if(pt_begin != NULL && pt_end != NULL)
    {
        pt_end->_pt_next = ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pt_next;
        ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pt_next = pt_begin;
    }
}

slist_iterator_t slist_erase_after(slist_t* pt_slist, slist_iterator_t t_pos)
{
    slistnode_t* pt_slistnode = NULL; /* for erase */
    bool_t       t_result = false;

    /* test the slist pointer and the pos is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(!iterator_equal(t_pos, slist_end(pt_slist)));

    /* get the next iterator */
    /* test the pos is valid */
    pt_slistnode = ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pt_next;
    /* t_pos is the last element(not end iterator) */
    if(pt_slistnode != NULL)
    {
        /* take out the element node */
        ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pt_next = pt_slistnode->_pt_next;
        /* destroy the element and destroy the node */
        t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)(pt_slistnode->_pc_data, &t_result);
        assert(t_result);
        deallocate(&pt_slist->_t_allocater, pt_slistnode, 
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);

        t_pos = iterator_next(t_pos);
        return t_pos;
    }
    else
    {
        return slist_end(pt_slist);
    }
}

slist_iterator_t slist_erase(slist_t* pt_slist, slist_iterator_t t_pos)
{
    /* if the pos is the begin iterator of slist */
    if(iterator_equal(t_pos, slist_begin(pt_slist)))
    {
        /* call the pop front */
        slist_pop_front(pt_slist);
        return slist_begin(pt_slist);
    }
    /* else get the previous iterator */
    else
    {
        /* call erase after */
        return slist_erase_after(pt_slist, slist_previous(pt_slist, t_pos));
    }
}

slist_iterator_t slist_erase_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end)
{
    /* test the pointer and range is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));

    /* if the t_begin is equal begin iterator */
    if(iterator_equal(t_begin, slist_begin(pt_slist)))
    {
        size_t t_index = 0;
        size_t t_count = iterator_distance(t_begin, t_end);

        /* call pop front n_elemcount times */
        for(t_index = 0; t_index < t_count; ++t_index)
        {
            slist_pop_front(pt_slist);
        }
        assert(iterator_equal(t_end, slist_begin(pt_slist)));

        return t_end;
    }
    /* else get the previous */
    else
    {
        /* call erase after range */
        return slist_erase_after_range(
            pt_slist, slist_previous(pt_slist, t_begin), t_end);
    }
}

slist_iterator_t slist_erase_after_range(
    slist_t* pt_slist, slist_iterator_t t_begin, slist_iterator_t t_end)
{
    /* test the range t_begin, t_end is valid */
    assert(_slist_iterator_belong_to_slist(pt_slist, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));

    if(!iterator_equal(t_begin, t_end) &&
       ((slistnode_t*)_GET_SLIST_COREPOS(t_begin))->_pt_next !=
       ((slistnode_t*)_GET_SLIST_COREPOS(t_end)))
    {
        slistnode_t*     pt_begin = NULL;
        slistnode_t*     pt_end = NULL;
        slistnode_t*     pt_iter = NULL;
        slist_iterator_t t_endprevious = slist_previous(pt_slist, t_end);
        bool_t           t_result = false;

        /* take out the range [t_begin+1, t_end) */
        pt_begin = ((slistnode_t*)_GET_SLIST_COREPOS(t_begin))->_pt_next;
        pt_end = (slistnode_t*)_GET_SLIST_COREPOS(t_endprevious);
        ((slistnode_t*)_GET_SLIST_COREPOS(t_begin))->_pt_next = pt_end->_pt_next;
        pt_end->_pt_next = NULL;
        /* destroy all elements and destroy all nodes */
        pt_iter = pt_begin;
        while(pt_iter != NULL)
        {
            pt_begin = pt_iter->_pt_next;
            t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)(pt_iter->_pc_data, &t_result);
            assert(t_result);
            deallocate(&pt_slist->_t_allocater, pt_iter,
                _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);

            pt_iter = pt_begin;
        }
    }

    return t_end;
}

void slist_splice(
    slist_t* pt_slist, slist_iterator_t t_pos, slist_t* pt_slistsrc)
{
#ifdef NDEBUG
    slist_t* pt_avoidwarning = NULL;
    pt_avoidwarning = pt_slist;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(pt_slist != pt_slistsrc);

    if(!slist_empty(pt_slistsrc))
    {
        _transfer(t_pos, slist_begin(pt_slistsrc), slist_end(pt_slistsrc));
    }
}

void slist_splice_pos(
    slist_t* pt_slist, slist_iterator_t t_pos,
    slist_t* pt_slistsrc, slist_iterator_t t_possrc)
{
    slist_iterator_t t_possrcnext;

#ifdef NDEBUG
    slist_t* pt_avoidwarning = NULL;
    pt_avoidwarning = pt_slist;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_iterator_belong_to_slist(pt_slistsrc, t_possrc));
    assert(pt_slist != pt_slistsrc);

    t_possrcnext = t_possrc;
    t_possrcnext = iterator_next(t_possrcnext);
    if(!slist_empty(pt_slistsrc) &&
       !iterator_equal(t_possrc, slist_end(pt_slistsrc)))
    {
        _transfer(t_pos, t_possrc, t_possrcnext);
    }
}

void slist_splice_range(
    slist_t* pt_slist, slist_iterator_t t_pos,
    slist_t* pt_slistsrc, slist_iterator_t t_begin, slist_iterator_t t_end)
{
#ifdef NDEBUG
    slist_t* pt_avoidwarning1 = NULL;
    slist_t* pt_avoidwarning2 = NULL;
    pt_avoidwarning1 = pt_slist;
    pt_avoidwarning2 = pt_slistsrc;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_iterator_belong_to_slist(pt_slistsrc, t_begin));
    assert(iterator_equal(t_begin, t_end) || _slist_iterator_before(t_begin, t_end));
    assert(pt_slist != pt_slistsrc);

    _transfer(t_pos, t_begin, t_end);
}

void slist_splice_after_pos(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_prev)
{
    slist_iterator_t t_prevnext;

#ifdef NDEBUG
    slist_t* pt_avoidwarning1 = NULL;
    slist_t* pt_avoidwarning2 = NULL;
    pt_avoidwarning1 = pt_slist;
    pt_avoidwarning2 = pt_slistsrc;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_iterator_belong_to_slist(pt_slistsrc, t_prev));
    assert(pt_slist != pt_slistsrc);

    t_prev = iterator_next(t_prev);
    t_prevnext = t_prev;
    t_prevnext = iterator_next(t_prevnext);
    _transfer_after(t_pos, t_prev, t_prevnext);
}

void slist_splice_after_range(
    slist_t* pt_slist, slist_iterator_t t_pos, 
    slist_t* pt_slistsrc, slist_iterator_t t_beforefirst, slist_iterator_t t_beforelast)
{
#ifdef NDEBUG
    slist_t* pt_avoidwarning1 = NULL;
    slist_t* pt_avoidwarning2 = NULL;
    pt_avoidwarning1 = pt_slist;
    pt_avoidwarning2 = pt_slistsrc;
#endif

    assert(_slist_same_type(pt_slist, pt_slistsrc));
    assert(_slist_iterator_belong_to_slist(pt_slist, t_pos));
    assert(_slist_iterator_belong_to_slist(pt_slistsrc, t_beforefirst));
    assert(iterator_equal(t_beforefirst, t_beforelast) || 
           _slist_iterator_before(t_beforefirst, t_beforelast));
    assert(pt_slist != pt_slistsrc);

    t_beforefirst = iterator_next(t_beforefirst);
    t_beforelast = iterator_next(t_beforelast);
    _transfer_after(t_pos, t_beforefirst, t_beforelast);
}

void _slist_remove(slist_t* pt_slist, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, pt_slist);
    _slist_remove_varg(pt_slist, val_elemlist);
}

void _slist_remove_varg(slist_t* pt_slist, va_list val_elemlist)
{
    slist_iterator_t t_iter; /* for iterate */
    slistnode_t*     pt_varg = NULL;
    bool_t           t_less = false;
    bool_t           t_great = false;

    /* test the pointer is valid */
    assert(pt_slist != NULL);

    pt_varg = allocate(&pt_slist->_t_allocater,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    assert(pt_varg != NULL);
    _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

    t_iter = slist_begin(pt_slist);
    while(!iterator_equal(t_iter, slist_end(pt_slist)))
    {
        t_less = t_great = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
            pt_varg->_pc_data, ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, &t_less);
        _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_iter))->_pc_data, pt_varg->_pc_data, &t_great);
        if(t_less || t_great)
        {
            t_iter = iterator_next(t_iter);
        }
        else
        {
            t_iter = slist_erase(pt_slist, t_iter);
        }
    }

    _slist_destroy_varg_value_auxiliary(pt_slist, pt_varg);
    deallocate(&pt_slist->_t_allocater, pt_varg,
        _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
}

void slist_remove_if(slist_t* pt_slist, unary_function_t t_unary_op)
{
    slist_iterator_t t_pos;
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    if(t_unary_op == NULL)
    {
        t_unary_op = fun_default_unary;
    }

    t_pos = slist_begin(pt_slist);
    /* iterate the slist from begin to end */
    while(!iterator_equal(t_pos, slist_end(pt_slist)))
    {
        /* operate each element use pufn_op, if it yield true */
        (*t_unary_op)(((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pc_data, &t_result);
        if(t_result)
        {
            /* erase element */
            t_pos = slist_erase(pt_slist, t_pos);
        }
        else
        {
            t_pos = iterator_next(t_pos);
        }
    }
}

void slist_unique(slist_t* pt_slist)
{
    slist_iterator_t t_poscur;
    slist_iterator_t t_posnext;
    bool_t           t_less = false;
    bool_t           t_great = false;

    /* test the slist is valid */
    assert(pt_slist != NULL);

    /* if the size great then 1 */
    if(slist_size(pt_slist) > 1)
    {
        t_poscur = slist_begin(pt_slist);
        t_posnext = iterator_next(t_poscur);
        while(!iterator_equal(t_posnext, slist_end(pt_slist)))
        {
            t_less = t_great = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
                ((slistnode_t*)_GET_SLIST_COREPOS(t_poscur))->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_posnext))->_pc_data, &t_less);
            _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
                ((slistnode_t*)_GET_SLIST_COREPOS(t_posnext))->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_poscur))->_pc_data, &t_great);
            if(t_less || t_great)
            {
                t_poscur = iterator_next(t_poscur);
                t_posnext = iterator_next(t_posnext);
            }
            else
            {
                /* then erase next */
                t_posnext = slist_erase(pt_slist, t_posnext);
            }
        }
    }
}

void slist_unique_if(slist_t* pt_slist, binary_function_t t_binary_op)
{
    slist_iterator_t t_poscur;
    slist_iterator_t t_posnext;
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    if(slist_size(pt_slist) > 1)
    {
        t_poscur = slist_begin(pt_slist);
        t_posnext = iterator_next(t_poscur);

        while(!iterator_equal(t_posnext, slist_end(pt_slist)))
        {
            (*t_binary_op)(
                ((slistnode_t*)_GET_SLIST_COREPOS(t_poscur))->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_posnext))->_pc_data,
                &t_result);
            if(t_result)
            {
                t_posnext = slist_erase(pt_slist, t_posnext);
            }
            else
            {
                t_poscur = iterator_next(t_poscur);
                t_posnext = iterator_next(t_posnext);
            }
        }
    }
}

void slist_reverse(slist_t* pt_slist)
{
    slist_iterator_t t_poscur;
    slist_iterator_t t_posnext;

    assert(pt_slist != NULL);

    if(slist_size(pt_slist) > 1)
    {
        t_poscur = slist_begin(pt_slist);
        t_poscur = iterator_next(t_poscur);

        while(!iterator_equal(t_poscur, slist_end(pt_slist)))
        {
            t_posnext = iterator_next(t_poscur);
            _transfer(slist_begin(pt_slist), t_poscur, t_posnext);
            t_poscur = t_posnext;
        }
    }
}

void slist_sort(slist_t* pt_slist)
{
    /* 
     * sort the slist use insert sort algorithm (O(N^2))instead of 
     * quick sort algorithm (O(NlogN)). because the quick sort need 
     * the previous iterator each step, so the efficiency in quick 
     * sort used in slist is more slow then O(NlogN).
     */

    slist_iterator_t t_pos;       /* iterating for insert */
    slist_iterator_t t_disorder;  /* the first pos of disorder element */
    slist_iterator_t t_insert;    /* the insert node */
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    t_disorder = slist_begin(pt_slist);
    while(!iterator_equal(t_disorder, slist_end(pt_slist)))
    {
        for(t_pos = slist_begin(pt_slist);
            !iterator_equal(t_pos, t_disorder);
            t_pos = iterator_next(t_pos))
        {
            t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
            _GET_SLIST_TYPE_LESS_FUNCTION(pt_slist)(
                ((slistnode_t*)_GET_SLIST_COREPOS(t_disorder))->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pc_data, &t_result);
            if(t_result)
            {
                t_insert = t_disorder;
                t_disorder = iterator_next(t_disorder);
                _transfer(t_pos, t_insert, t_disorder);
                break;
            }
        }

        if(iterator_equal(t_pos, t_disorder))
        {
            t_disorder = iterator_next(t_disorder);
        }
    }
}

void slist_sort_if(slist_t* pt_slist, binary_function_t t_binary_op)
{
    slist_iterator_t t_pos;       /* iterating for insert */
    slist_iterator_t t_disorder;  /* the first pos of disorder element */
    slist_iterator_t t_insert;    /* the insert node */
    bool_t           t_result = false;

    assert(pt_slist != NULL);

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    t_disorder = slist_begin(pt_slist);
    while(!iterator_equal(t_disorder, slist_end(pt_slist)))
    {
        for(t_pos = slist_begin(pt_slist);
            !iterator_equal(t_pos, t_disorder);
            t_pos = iterator_next(t_pos))
        {
            (*t_binary_op)(
                ((slistnode_t*)_GET_SLIST_COREPOS(t_disorder))->_pc_data,
                ((slistnode_t*)_GET_SLIST_COREPOS(t_pos))->_pc_data,
                &t_result);
            if(t_result)
            {
                t_insert = t_disorder;
                t_disorder = iterator_next(t_disorder);
                _transfer(t_pos, t_insert, t_disorder);
                break;
            }
        }

        if(iterator_equal(t_pos, t_disorder))
        {
            t_disorder = iterator_next(t_disorder);
        }
    }
}

void slist_merge(slist_t* pt_slistdest, slist_t* pt_slistsrc)
{
    slist_iterator_t t_dest;
    slist_iterator_t t_src;
    slist_iterator_t t_srcnext;
    bool_t           t_result = false;

    /* test the dest and src slist is valid */
    assert(_slist_same_type(pt_slistdest, pt_slistsrc));

    /* iterate dest and src slist */
    t_dest = slist_begin(pt_slistdest); 
    while(!iterator_equal(t_dest, slist_end(pt_slistdest)) && !slist_empty(pt_slistsrc))
    {
        t_src = slist_begin(pt_slistsrc);
        t_result = _GET_SLIST_TYPE_SIZE(pt_slistdest);
        _GET_SLIST_TYPE_LESS_FUNCTION(pt_slistdest)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_src))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_dest))->_pc_data, &t_result);
        if(t_result)
        {
            /* transfer the element fromt src to dest */
            t_srcnext = t_src;
            t_srcnext = iterator_next(t_srcnext);
            _transfer(t_dest, t_src, t_srcnext);
        }
        else
        {
            t_dest = iterator_next(t_dest);
        }
    }
    
    /* if the src is not ended */
    t_src = slist_begin(pt_slistsrc);
    if(!iterator_equal(t_src, slist_end(pt_slistsrc)))
    {
        assert(iterator_equal(t_dest, slist_end(pt_slistdest)));
        /* transfer the remain elements in src slist to dest */
        _transfer(t_dest, t_src, slist_end(pt_slistsrc));
    }
}

void slist_merge_if(
    slist_t* pt_slistdest, slist_t* pt_slistsrc, 
    binary_function_t t_binary_op)
{
    slist_iterator_t t_dest;
    slist_iterator_t t_src;
    slist_iterator_t t_srcnext;
    bool_t           t_result = false;

    assert(_slist_same_type(pt_slistdest, pt_slistsrc));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    /* iterate dest and src slist */
    t_dest = slist_begin(pt_slistdest); 
    while(!iterator_equal(t_dest, slist_end(pt_slistdest)) && !slist_empty(pt_slistsrc))
    {
        t_src = slist_begin(pt_slistsrc);
        /* if src slist less then dest */
        (*t_binary_op)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_src))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_dest))->_pc_data,
            &t_result);
        if(t_result)
        {
            /* transfer the element fromt src to dest */
            t_srcnext = t_src;
            t_srcnext = iterator_next(t_srcnext);
            _transfer(t_dest, t_src, t_srcnext);
        }
        else
        {
            t_dest = iterator_next(t_dest);
        }
    }

    /* if the src is not ended */
    t_src = slist_begin(pt_slistsrc);
    if(!iterator_equal(t_src, slist_end(pt_slistsrc)))
    {
        assert(iterator_equal(t_dest, slist_end(pt_slistdest)));
        /* transfer the remain elements in src slist to dest */
        _transfer(t_dest, t_src, slist_end(pt_slistsrc));
    }
}

void slist_clear(slist_t* pt_slist)
{
    slist_erase_range(pt_slist, slist_begin(pt_slist), slist_end(pt_slist));
}

void _slist_resize_elem(slist_t* pt_slist, size_t t_resize, ...)
{
    va_list val_elemlist;
    va_start(val_elemlist, t_resize);
    _slist_resize_elem_varg(pt_slist, t_resize, val_elemlist);
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
        pt_varg = allocate(&pt_slist->_t_allocater,
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
        assert(pt_varg != NULL);
        _slist_get_varg_value_auxiliary(pt_slist, val_elemlist, pt_varg);

        for(t_index = 0; t_index < t_resize - t_slistsize; ++t_index)
        {
            pt_slistnode = allocate(&pt_slist->_t_allocater,
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
        deallocate(&pt_slist->_t_allocater, pt_varg, 
            _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
    }
}

void slist_resize(slist_t* pt_slist, size_t t_resize)
{
    slist_iterator_t t_pos;
    size_t           t_index = 0;

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

        if(!slist_empty(pt_slist))
        {
            t_slistlast = slist_previous(pt_slist, slist_end(pt_slist));
        }
        else
        {
            _GET_SLIST_COREPOS(t_slistlast) = (char*)&pt_slist->_t_head;
        }

        for(t_index = 0; t_index < t_resize - t_slistsize; ++t_index)
        {
            pt_slistnode = allocate(&pt_slist->_t_allocater,
                _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pt_slist)), 1);
            assert(pt_slistnode != NULL);
            _slist_init_node_auxiliary(pt_slist, pt_slistnode);

            pt_slistnode->_pt_next = ((slistnode_t*)_GET_SLIST_COREPOS(t_slistlast))->_pt_next;
            ((slistnode_t*)_GET_SLIST_COREPOS(t_slistlast))->_pt_next = pt_slistnode;
            pt_slistnode = NULL;
        }
    }
}

bool_t slist_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond)
{
    slist_iterator_t t_first;  /* iterator for first slist */
    slist_iterator_t t_second; /* iterator for second slist */
    bool_t           t_less = false;
    bool_t           t_great = false;

    assert(cpt_slistfirst != NULL && cpt_slistsecond != NULL);

    /* test element type */
    if(!_slist_same_type(cpt_slistfirst, cpt_slistsecond))
    {
        return false;
    }

    /* test slist size */
    if(slist_size(cpt_slistfirst) != slist_size(cpt_slistsecond))
    {
        return false;
    }

    for(t_first = slist_begin(cpt_slistfirst), t_second = slist_begin(cpt_slistsecond);
        !iterator_equal(t_first, slist_end(cpt_slistfirst)) &&
        !iterator_equal(t_second, slist_end(cpt_slistsecond));
        t_first = iterator_next(t_first), t_second = iterator_next(t_second))
    {
        t_less = t_great = _GET_SLIST_TYPE_SIZE(cpt_slistfirst);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpt_slistfirst)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_first))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_second))->_pc_data, &t_less);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpt_slistfirst)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_second))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_first))->_pc_data, &t_great);
        if(t_less || t_great)
        {
            return false;
        }
    }
    assert(iterator_equal(t_first, slist_end(cpt_slistfirst)) &&
           iterator_equal(t_second, slist_end(cpt_slistsecond)));

    return true;
}

bool_t slist_not_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond)
{
    return !slist_equal(cpt_slistfirst, cpt_slistsecond);
}

bool_t slist_less(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond)
{
    slist_iterator_t t_first;  /* iterator for first slist */
    slist_iterator_t t_second; /* iterator for second slist */
    bool_t           t_result = false;

    assert(_slist_same_type(cpt_slistfirst, cpt_slistsecond));

    for(t_first = slist_begin(cpt_slistfirst), t_second = slist_begin(cpt_slistsecond);
        !iterator_equal(t_first, slist_end(cpt_slistfirst)) &&
        !iterator_equal(t_second, slist_end(cpt_slistsecond));
        t_first = iterator_next(t_first), t_second = iterator_next(t_second))
    {
        t_result = _GET_SLIST_TYPE_SIZE(cpt_slistfirst);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpt_slistfirst)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_first))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_second))->_pc_data, &t_result);
        if(t_result)
        {
            return true;
        }

        t_result = _GET_SLIST_TYPE_SIZE(cpt_slistfirst);
        _GET_SLIST_TYPE_LESS_FUNCTION(cpt_slistfirst)(
            ((slistnode_t*)_GET_SLIST_COREPOS(t_second))->_pc_data,
            ((slistnode_t*)_GET_SLIST_COREPOS(t_first))->_pc_data, &t_result);
        if(t_result)
        {
            return false;
        }
    }

    /* after test if the first slist size < the second return true */
    if(slist_size(cpt_slistfirst) < slist_size(cpt_slistsecond))
    {
        return true;
    }
    /* else return false */
    else
    {
        return false;
    }
}

bool_t slist_less_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond)
{
    return (slist_less(cpt_slistfirst, cpt_slistsecond) ||
            slist_equal(cpt_slistfirst, cpt_slistsecond)) ? true : false;
}

bool_t slist_great(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond)
{
    return !slist_less_equal(cpt_slistfirst, cpt_slistsecond);
}

bool_t slist_great_equal(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond)
{
    return (slist_great(cpt_slistfirst, cpt_slistsecond) ||
            slist_equal(cpt_slistfirst, cpt_slistsecond)) ? true : false;
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
#ifndef NDEBUG
static bool_t _slist_iterator_belong_to_slist(
    const slist_t* cpt_slist, slist_iterator_t t_iter)
{
    slistnode_t* pt_slistnode = NULL;

    assert(cpt_slist != NULL);
    assert(_GET_SLIST_CONTAINER(t_iter) == cpt_slist);

    /* the end iterator of slist corepos is NULL */
    if(_GET_SLIST_COREPOS(t_iter) == NULL)
    {
        return true;
    }

    for(pt_slistnode = cpt_slist->_t_head._pt_next;
        pt_slistnode != NULL;
        pt_slistnode = pt_slistnode->_pt_next)
    {
        if(pt_slistnode == (slistnode_t*)_GET_SLIST_COREPOS(t_iter))
        {
            return true;
        }
    }

    return false;
}

static bool_t _slist_same_slist_iterator_type(
    const slist_t* cpt_slist, slist_iterator_t t_iter)
{
    assert(cpt_slist != NULL && _GET_SLIST_CONTAINER(t_iter) != NULL);
    assert(_GET_SLIST_CONTAINER_TYPE(t_iter) == _SLIST_CONTAINER &&
           _GET_SLIST_ITERATOR_TYPE(t_iter) == _FORWARD_ITERATOR);
    return _slist_same_type(cpt_slist, _GET_SLIST_CONTAINER(t_iter));
}
#endif /* NDEBUG */

static bool_t _slist_same_type(
    const slist_t* cpt_slistfirst, const slist_t* cpt_slistsecond)
{
    /* test the container pointer is valid */
    assert(cpt_slistfirst != NULL && cpt_slistsecond != NULL);
    /* test the container type is the same */
    return _type_is_same(_GET_SLIST_TYPE_NAME(cpt_slistfirst),
                         _GET_SLIST_TYPE_NAME(cpt_slistsecond)) &&
           (cpt_slistfirst->_t_typeinfo._pt_type == cpt_slistsecond->_t_typeinfo._pt_type) &&
           (cpt_slistfirst->_t_typeinfo._t_style == cpt_slistsecond->_t_typeinfo._t_style);
}

static void _transfer_after(
    slist_iterator_t t_pos, slist_iterator_t t_begin, slist_iterator_t t_end)
{
    /* insert the range [t_begin+1, t_end) to slist */
    slist_insert_after_range(_GET_SLIST_CONTAINER(t_pos), t_pos, t_begin, t_end);
    /* delete te range [t_begin+1, t_end) */
    slist_erase_after_range(_GET_SLIST_CONTAINER(t_begin), 
        slist_previous(_GET_SLIST_CONTAINER(t_begin), t_begin), t_end);
}

static void _transfer(
    slist_iterator_t t_pos, slist_iterator_t t_begin, slist_iterator_t t_end)
{
    slist_insert_range(_GET_SLIST_CONTAINER(t_pos), t_pos, t_begin, t_end);
    slist_erase_range(_GET_SLIST_CONTAINER(t_begin), t_begin, t_end);
}

static void _slist_get_varg_value_auxiliary(
    slist_t* pt_slist, va_list val_elemlist, slistnode_t* pt_node)
{
    _slist_init_node_auxiliary(pt_slist, pt_node);
    _type_get_varg_value(&pt_slist->_t_typeinfo, val_elemlist, pt_node->_pc_data);
}

static void _slist_destroy_varg_value_auxiliary(slist_t* pt_slist, slistnode_t* pt_node)
{
    bool_t t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
    _GET_SLIST_TYPE_DESTROY_FUNCTION(pt_slist)(pt_node->_pc_data, &t_result);
    assert(t_result);
}

static void _slist_init_node_auxiliary(slist_t* pt_slist, slistnode_t* pt_node)
{
    assert(pt_slist != NULL && pt_node != NULL);

    /* initialize new elements */
    if(_GET_SLIST_TYPE_STYLE(pt_slist) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_SLIST_TYPE_NAME(pt_slist), s_elemtypename);

        _GET_SLIST_TYPE_INIT_FUNCTION(pt_slist)(pt_node->_pc_data, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_SLIST_TYPE_SIZE(pt_slist);
        _GET_SLIST_TYPE_INIT_FUNCTION(pt_slist)(pt_node->_pc_data, &t_result);
        assert(t_result);
    }
}

/** eof **/

