/*
 *  The implement of list private interface.
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
#include <cstl/cfunctional.h>

#include <cstl/cstl_list_iterator.h>
#include <cstl/cstl_list_private.h>
#include <cstl/cstl_list.h>

#include <cstl/cstring.h>

#include "cstl_list_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create list container.
 */
list_t* _create_list(const char* s_typename)
{
    list_t* plist_new = NULL;

    assert(s_typename != NULL);

    if((plist_new = (list_t*)malloc(sizeof(list_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_list_auxiliary(plist_new, s_typename))
    {
        free(plist_new);
        return NULL;
    }

    return plist_new;
}

bool_t _create_list_auxiliary(list_t* pt_list, const char* s_typename)
{
    assert(pt_list != NULL && s_typename != NULL);

    _type_get_type(&pt_list->_t_typeinfo, s_typename);
    if(pt_list->_t_typeinfo._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pt_list->_pt_node = NULL;

    _alloc_init(&pt_list->_t_allocater);
    return true;
}

/* list function */
void _list_init_elem_varg(list_t* pt_list, size_t t_count, va_list val_elemlist)
{
    listnode_t* pt_varg = NULL;

    assert(pt_list != NULL && pt_list->_pt_node == NULL);

    /* allocate the end element */
    /*
     * _pt_node --+
     *            V
     *     +-->+------+<--+
     *     +---| prev |   |
     *         +------+   |
     *         | next |---+
     *         +------+
     *         | data |
     *         +------+
     */
    /*_alloc_init(&pt_list->_t_allocater);*/
    pt_list->_pt_node = _alloc_allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_list->_pt_node != NULL);
    pt_list->_pt_node->_pt_next = pt_list->_pt_node;
    pt_list->_pt_node->_pt_prev = pt_list->_pt_node;

    if(t_count > 0)
    {
        size_t      t_index = 0;
        listnode_t* pt_node = NULL;
        bool_t      t_result = false;

        /* get varg value only once */
        pt_varg = _alloc_allocate(&pt_list->_t_allocater,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
        assert(pt_varg != NULL);
        _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

        for(t_index = 0; t_index < t_count; ++t_index)
        {
            pt_node = _alloc_allocate(&pt_list->_t_allocater,
                _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(pt_list, pt_node);

            t_result = _GET_LIST_TYPE_SIZE(pt_list);
            _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
                pt_node->_pc_data, pt_varg->_pc_data, &t_result);
            assert(t_result);

            pt_node->_pt_next = pt_list->_pt_node;
            pt_node->_pt_prev = pt_list->_pt_node->_pt_prev;
            pt_list->_pt_node->_pt_prev->_pt_next = pt_node;
            pt_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }

        _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
        _alloc_deallocate(&pt_list->_t_allocater, pt_varg,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    }
}

void _list_init_elem(list_t* pt_list, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _list_init_elem_varg(pt_list, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _list_destroy_auxiliary(list_t* pt_list)
{
    listnode_t* pt_node = NULL;         /* for destroy element */
    listnode_t* pt_destroynode = NULL;  /* for destroy node itself */
    bool_t      t_result = false;

    /*assert(pt_list != NULL && pt_list->_pt_node != NULL);*/

    if(pt_list->_pt_node != NULL)
    {
        pt_node = pt_list->_pt_node->_pt_next;
        /* destroy all element and node except the end node */
        while(pt_node != pt_list->_pt_node)
        {
            pt_destroynode = pt_node;
            pt_node = pt_node->_pt_next;
            /* delete the destroy node from the link list */
            pt_node->_pt_prev = pt_destroynode->_pt_prev;
            pt_destroynode->_pt_prev->_pt_next = pt_node;
            /* destroy the node */

            t_result = _GET_LIST_TYPE_SIZE(pt_list);
            _GET_LIST_TYPE_DESTROY_FUNCTION(pt_list)(pt_destroynode->_pc_data, &t_result);
            assert(t_result);
            _alloc_deallocate(&pt_list->_t_allocater, pt_destroynode,
                _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
        }
        /* destroy the end node */
        _alloc_deallocate(&pt_list->_t_allocater, pt_list->_pt_node,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    }

    _alloc_destroy(&pt_list->_t_allocater);
    pt_list->_pt_node = NULL;
}

void _list_assign_elem(list_t* pt_list, size_t t_count, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    _list_assign_elem_varg(pt_list, t_count, val_elemlist);
    va_end(val_elemlist);
}

void _list_assign_elem_varg(list_t* pt_list, size_t t_count, va_list val_elemlist)
{
    listnode_t*     pt_varg = NULL;
    list_iterator_t t_iter;
    bool_t          t_result = false;

    assert(pt_list != NULL);

    list_resize(pt_list, t_count);

    /* get varg value */
    pt_varg = _alloc_allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

    /* copy value form varg */
    for(t_iter = list_begin(pt_list);
        !iterator_equal(t_iter, list_end(pt_list));
        t_iter = iterator_next(t_iter))
    {
        t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
            ((listnode_t*)_GET_LIST_COREPOS(t_iter))->_pc_data, pt_varg->_pc_data, &t_result);
        assert(t_result);
    }

    /* destroy varg value */
    _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
    _alloc_deallocate(&pt_list->_t_allocater, pt_varg,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
}

list_iterator_t _list_insert_n(
    list_t* pt_list, list_iterator_t t_pos, size_t t_count, ...)
{
    list_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_count);
    t_iter = _list_insert_n_varg(pt_list, t_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

list_iterator_t _list_insert_n_varg(
    list_t* pt_list, list_iterator_t t_pos, size_t t_count, va_list val_elemlist)
{
    listnode_t* pt_node = NULL;    /* the insert node */
    size_t      t_index = 0;
    listnode_t* pt_varg = NULL;
    bool_t      t_result = false;

    assert(_list_iterator_belong_to_list(pt_list, t_pos));

    /* get varg value only once */
    pt_varg = _alloc_allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

    for(t_index = 0; t_index < t_count; ++t_index)
    {
        /* allocate the memory for insert node */
        pt_node = _alloc_allocate(&pt_list->_t_allocater,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
        assert(pt_node != NULL);
        _list_init_node_auxiliary(pt_list, pt_node);

        /* copy value from varg */
        t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(pt_node->_pc_data, pt_varg->_pc_data, &t_result);
        assert(t_result);

        /* insert the element in the position t_pos */
        pt_node->_pt_next = (listnode_t*)_GET_LIST_COREPOS(t_pos);
        pt_node->_pt_prev = ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev;
        ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev->_pt_next = pt_node;
        ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pt_prev = pt_node;
        pt_node = NULL;
    }

    /* destroy varg value */
    _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
    _alloc_deallocate(&pt_list->_t_allocater, pt_varg,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);

    return t_pos;
}

void _list_push_back(list_t* pt_list, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_list);
    _list_push_back_varg(pt_list, val_elemlist);
    va_end(val_elemlist);
}

void _list_push_back_varg(list_t* pt_list, va_list val_elemlist)
{
    listnode_t* pt_node = NULL;    /* the insert node */

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    /* allocate the insert node */
    pt_node = _alloc_allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_node != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_node);
    /* insert the node before the end node */
    pt_node->_pt_next = pt_list->_pt_node;
    pt_node->_pt_prev = pt_list->_pt_node->_pt_prev;
    pt_list->_pt_node->_pt_prev->_pt_next = pt_node;
    pt_list->_pt_node->_pt_prev = pt_node;
}

void _list_push_front(list_t* pt_list, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_list);
    _list_push_front_varg(pt_list, val_elemlist);
    va_end(val_elemlist);
}

void _list_push_front_varg(list_t* pt_list, va_list val_elemlist)
{
    listnode_t* pt_node = NULL;    /* the allocate node */

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    /* allocate the node */
    pt_node = _alloc_allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_node != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_node);
    /* insert the node into the first position */
    pt_node->_pt_next = pt_list->_pt_node->_pt_next;
    pt_node->_pt_prev = pt_list->_pt_node;
    pt_list->_pt_node->_pt_next->_pt_prev = pt_node;
    pt_list->_pt_node->_pt_next = pt_node;
}

void _list_remove(list_t* pt_list, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, pt_list);
    _list_remove_varg(pt_list, val_elemlist);
    va_end(val_elemlist);
}

void _list_remove_varg(list_t* pt_list, va_list val_elemlist)
{
    list_iterator_t t_pos;    /* the remove element position */
    listnode_t*     pt_varg = NULL;
    bool_t          t_less = false;
    bool_t          t_greater = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);

    pt_varg = _alloc_allocate(&pt_list->_t_allocater,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

    t_pos = list_begin(pt_list);
    while(!iterator_equal(t_pos, list_end(pt_list)))
    {
        t_less = t_greater = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_LESS_FUNCTION(pt_list)(
            ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pc_data, pt_varg->_pc_data, &t_less);
        _GET_LIST_TYPE_LESS_FUNCTION(pt_list)(
            pt_varg->_pc_data, ((listnode_t*)_GET_LIST_COREPOS(t_pos))->_pc_data, &t_greater);
        if(t_less || t_greater)
        {
            t_pos = iterator_next(t_pos);
        }
        else
        {
            t_pos = list_erase(pt_list, t_pos);
        }
    }

    _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
    _alloc_deallocate(&pt_list->_t_allocater, pt_varg,
        _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
}

void _list_resize_elem(list_t* pt_list, size_t t_resize, ...)
{
    va_list val_elemlist;

    va_start(val_elemlist, t_resize);
    _list_resize_elem_varg(pt_list, t_resize, val_elemlist);
    va_end(val_elemlist);
}

void _list_resize_elem_varg(list_t* pt_list, size_t t_resize, va_list val_elemlist)
{
    listnode_t* pt_node = NULL; /* the node for allocate */
    size_t      t_listsize = 0; /* the list size */
    size_t      t_index = 0;
    listnode_t* pt_varg = NULL;
    bool_t      t_result = false;

    assert(pt_list != NULL && pt_list->_pt_node != NULL);


    t_listsize = list_size(pt_list);
    if(t_resize < t_listsize)
    {
        for(t_index = 0; t_index < t_listsize - t_resize; ++t_index)
        {
            list_pop_back(pt_list);
        }
    }
    else
    {
        /* get varg value only once */
        pt_varg = _alloc_allocate(&pt_list->_t_allocater,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
        assert(pt_varg != NULL);
        _list_get_varg_value_auxiliary(pt_list, val_elemlist, pt_varg);

        for(t_index = 0; t_index < t_resize - t_listsize; ++t_index)
        {
            pt_node = _alloc_allocate(&pt_list->_t_allocater,
                _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(pt_list, pt_node);
            t_result = _GET_LIST_TYPE_SIZE(pt_list);
            _GET_LIST_TYPE_COPY_FUNCTION(pt_list)(
                pt_node->_pc_data, pt_varg->_pc_data, &t_result);
            assert(t_result);

            pt_node->_pt_next = pt_list->_pt_node;
            pt_node->_pt_prev = pt_list->_pt_node->_pt_prev;
            pt_list->_pt_node->_pt_prev->_pt_next = pt_node;
            pt_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }

        _list_destroy_varg_value_auxiliary(pt_list, pt_varg);
        _alloc_deallocate(&pt_list->_t_allocater, pt_varg,
            _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(pt_list)), 1);
    }
}

void _list_init_elem_auxiliary(list_t* pt_list, void* pv_elem)
{
    assert(pt_list != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_LIST_TYPE_STYLE(pt_list) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_LIST_TYPE_NAME(pt_list), s_elemtypename);

        _GET_LIST_TYPE_INIT_FUNCTION(pt_list)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_LIST_TYPE_SIZE(pt_list);
        _GET_LIST_TYPE_INIT_FUNCTION(pt_list)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/

/** eof **/

