/*
 *  The implement of list private interface.
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
#include <cstl/cfunctional.h>
#include <cstl/cstring.h>
#include <cstl/clist.h>

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

    if ((plist_new = (list_t*)malloc(sizeof(list_t))) == NULL) {
        return NULL;
    }

    if (!_create_list_auxiliary(plist_new, s_typename)) {
        free(plist_new);
        return NULL;
    }

    return plist_new;
}

/**
 * Create list container auxiliary function.
 */
bool_t _create_list_auxiliary(list_t* plist_list, const char* s_typename)
{
    assert(plist_list != NULL);
    assert(s_typename != NULL);

    _type_get_type(&plist_list->_t_typeinfo, s_typename);
    if (plist_list->_t_typeinfo._t_style == _TYPE_INVALID) {
        return false;
    }

    plist_list->_pt_node = NULL;

    _alloc_init(&plist_list->_t_allocator);
    return true;
}

/**
 * Initialize list with specified element.
 */
void _list_init_elem(list_t* plist_list, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(plist_list != NULL);
    assert(_list_is_created(plist_list));

    va_start(val_elemlist, t_count);
    _list_init_elem_varg(plist_list, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Initialize list with variable argument list of specified element.
 */
void _list_init_elem_varg(list_t* plist_list, size_t t_count, va_list val_elemlist)
{
    _listnode_t* pt_varg = NULL;

    assert(plist_list != NULL);
    assert(_list_is_created(plist_list));

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
    plist_list->_pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    assert(plist_list->_pt_node != NULL);
    plist_list->_pt_node->_pt_next = plist_list->_pt_node;
    plist_list->_pt_node->_pt_prev = plist_list->_pt_node;

    if (t_count > 0) {
        size_t       i = 0;
        _listnode_t* pt_node = NULL;
        bool_t       b_result = false;

        /* get varg value only once */
        pt_varg = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
        assert(pt_varg != NULL);
        _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_varg);

        for (i = 0; i < t_count; ++i) {
            pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(plist_list, pt_node);

            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(pt_node->_pby_data, pt_varg->_pby_data, &b_result);
            assert(b_result);

            pt_node->_pt_next = plist_list->_pt_node;
            pt_node->_pt_prev = plist_list->_pt_node->_pt_prev;
            plist_list->_pt_node->_pt_prev->_pt_next = pt_node;
            plist_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }

        _list_destroy_varg_value_auxiliary(plist_list, pt_varg);
        _alloc_deallocate(&plist_list->_t_allocator, pt_varg, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    }
}

/**
 * Destroy list container auxiliary function.
 */
void _list_destroy_auxiliary(list_t* plist_list)
{
    _listnode_t* pt_node = NULL;         /* for destroy element */
    _listnode_t* pt_destroynode = NULL;  /* for destroy node itself */
    bool_t       b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list) || _list_is_created(plist_list));

    if (plist_list->_pt_node != NULL) {
        pt_node = plist_list->_pt_node->_pt_next;
        /* destroy all element and node except the end node */
        while (pt_node != plist_list->_pt_node) {
            pt_destroynode = pt_node;
            pt_node = pt_node->_pt_next;
            /* delete the destroy node from the link list */
            pt_node->_pt_prev = pt_destroynode->_pt_prev;
            pt_destroynode->_pt_prev->_pt_next = pt_node;
            /* destroy the node */

            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_DESTROY_FUNCTION(plist_list)(pt_destroynode->_pby_data, &b_result);
            assert(b_result);
            _alloc_deallocate(&plist_list->_t_allocator, pt_destroynode, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
        }
        /* destroy the end node */
        _alloc_deallocate(&plist_list->_t_allocator, plist_list->_pt_node, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    }

    _alloc_destroy(&plist_list->_t_allocator);
    plist_list->_pt_node = NULL;
}

/**
 * Assign list with specificed element.
 */
void _list_assign_elem(list_t* plist_list, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    va_start(val_elemlist, t_count);
    _list_assign_elem_varg(plist_list, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Assign list with variable argument of specificed element.
 */
void _list_assign_elem_varg(list_t* plist_list, size_t t_count, va_list val_elemlist)
{
    _listnode_t*    pt_varg = NULL;
    bool_t          b_result = false;
    list_iterator_t it_iter;
    list_iterator_t it_begin;
    list_iterator_t it_end;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    list_resize(plist_list, t_count);

    /* get varg value */
    pt_varg = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_varg);

    it_begin = list_begin(plist_list);
    it_end = list_end(plist_list);

    /* copy value form varg */
    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        b_result = _GET_LIST_TYPE_SIZE(plist_list);
        _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(((_listnode_t*)_LIST_ITERATOR_COREPOS(it_iter))->_pby_data, pt_varg->_pby_data, &b_result);
        assert(b_result);
    }

    /* destroy varg value */
    _list_destroy_varg_value_auxiliary(plist_list, pt_varg);
    _alloc_deallocate(&plist_list->_t_allocator, pt_varg, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
}

/**
 * Insert multiple copys of element befor specificed position.
 */
list_iterator_t _list_insert_n(list_t* plist_list, list_iterator_t it_pos, size_t t_count, ...)
{
    list_iterator_t it_iter;
    va_list val_elemlist;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_iterator_belong_to_list(plist_list, it_pos));

    va_start(val_elemlist, t_count);
    it_iter = _list_insert_n_varg(plist_list, it_pos, t_count, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Insert multiple copys of element befor specificed position, the element is from variable argument list.
 */
list_iterator_t _list_insert_n_varg(list_t* plist_list, list_iterator_t it_pos, size_t t_count, va_list val_elemlist)
{
    _listnode_t* pt_node = NULL;    /* the insert node */
    size_t       i = 0;
    _listnode_t* pt_varg = NULL;
    bool_t       b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));
    assert(_list_iterator_belong_to_list(plist_list, it_pos));

    if (t_count == 0) {
        return it_pos;
    }

    /* get varg value only once */
    pt_varg = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_varg);

    for (i = 0; i < t_count; ++i) {
        /* allocate the memory for insert node */
        pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
        assert(pt_node != NULL);
        _list_init_node_auxiliary(plist_list, pt_node);

        /* copy value from varg */
        b_result = _GET_LIST_TYPE_SIZE(plist_list);
        _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(pt_node->_pby_data, pt_varg->_pby_data, &b_result);
        assert(b_result);

        /* insert the element in the position it_pos */
        pt_node->_pt_next = (_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos);
        pt_node->_pt_prev = ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev;
        ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev->_pt_next = pt_node;
        ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pt_prev = pt_node;
        pt_node = NULL;
    }

    /* destroy varg value */
    _list_destroy_varg_value_auxiliary(plist_list, pt_varg);
    _alloc_deallocate(&plist_list->_t_allocator, pt_varg, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);

    return iterator_advance(it_pos, -(int)t_count);
}

/**
 * Add specificed element at the end of list container. 
 */
void _list_push_back(list_t* plist_list, ...)
{
    va_list val_elemlist;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    va_start(val_elemlist, plist_list);
    _list_push_back_varg(plist_list, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Add specificed element from variable argument list at the end of list container. 
 */
void _list_push_back_varg(list_t* plist_list, va_list val_elemlist)
{
    _listnode_t* pt_node = NULL;    /* the insert node */

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    /* allocate the insert node */
    pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    assert(pt_node != NULL);
    _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_node);
    /* insert the node before the end node */
    pt_node->_pt_next = plist_list->_pt_node;
    pt_node->_pt_prev = plist_list->_pt_node->_pt_prev;
    plist_list->_pt_node->_pt_prev->_pt_next = pt_node;
    plist_list->_pt_node->_pt_prev = pt_node;
}

/**
 * Add specificed element at the begin of list container. 
 */
void _list_push_front(list_t* plist_list, ...)
{
    va_list val_elemlist;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    va_start(val_elemlist, plist_list);
    _list_push_front_varg(plist_list, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Add specificed element from variable argument list at the begin of list container. 
 */
void _list_push_front_varg(list_t* plist_list, va_list val_elemlist)
{
    _listnode_t* pt_node = NULL;    /* the allocate node */

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    /* allocate the node */
    pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    assert(pt_node != NULL);
    _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_node);
    /* insert the node into the first position */
    pt_node->_pt_next = plist_list->_pt_node->_pt_next;
    pt_node->_pt_prev = plist_list->_pt_node;
    plist_list->_pt_node->_pt_next->_pt_prev = pt_node;
    plist_list->_pt_node->_pt_next = pt_node;
}

/**
 * Remove specificed element from list container.
 */
void _list_remove(list_t* plist_list, ...)
{
    va_list val_elemlist;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    va_start(val_elemlist, plist_list);
    _list_remove_varg(plist_list, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Remove element that specificed by variable argument list from list container.
 */
void _list_remove_varg(list_t* plist_list, va_list val_elemlist)
{
    list_iterator_t it_pos;    /* the remove element position */
    list_iterator_t it_end;
    _listnode_t*    pt_varg = NULL;
    bool_t          b_less = false;
    bool_t          b_greater = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    pt_varg = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    assert(pt_varg != NULL);
    _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_varg);

    it_pos = list_begin(plist_list);
    it_end = list_end(plist_list);
    while (!iterator_equal(it_pos, it_end)) {
        b_less = b_greater = _GET_LIST_TYPE_SIZE(plist_list);
        _GET_LIST_TYPE_LESS_FUNCTION(plist_list)(((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pby_data, pt_varg->_pby_data, &b_less);
        _GET_LIST_TYPE_LESS_FUNCTION(plist_list)(pt_varg->_pby_data, ((_listnode_t*)_LIST_ITERATOR_COREPOS(it_pos))->_pby_data, &b_greater);

        it_pos = (b_less || b_greater) ? iterator_next(it_pos) : list_erase(plist_list, it_pos);
    }

    _list_destroy_varg_value_auxiliary(plist_list, pt_varg);
    _alloc_deallocate(&plist_list->_t_allocator, pt_varg, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
}

/**
 * Reset the size of list elements.
 */
void _list_resize_elem(list_t* plist_list, size_t t_resize, ...)
{
    va_list val_elemlist;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    va_start(val_elemlist, t_resize);
    _list_resize_elem_varg(plist_list, t_resize, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Reset the size of list elements, and filled element is from variable argument list.
 */
void _list_resize_elem_varg(list_t* plist_list, size_t t_resize, va_list val_elemlist)
{
    _listnode_t* pt_node = NULL; /* the node for allocate */
    size_t       t_listsize = 0; /* the list size */
    size_t       i = 0;
    _listnode_t* pt_varg = NULL;
    bool_t       b_result = false;

    assert(plist_list != NULL);
    assert(_list_is_inited(plist_list));

    t_listsize = list_size(plist_list);
    if (t_resize == t_listsize) {
        return;
    } else if (t_resize < t_listsize) {
        for (i = 0; i < t_listsize - t_resize; ++i) {
            list_pop_back(plist_list);
        }
    } else {
        /* get varg value only once */
        pt_varg = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
        assert(pt_varg != NULL);
        _list_get_varg_value_auxiliary(plist_list, val_elemlist, pt_varg);

        for (i = 0; i < t_resize - t_listsize; ++i) {
            pt_node = _alloc_allocate(&plist_list->_t_allocator, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
            assert(pt_node != NULL);
            _list_init_node_auxiliary(plist_list, pt_node);
            b_result = _GET_LIST_TYPE_SIZE(plist_list);
            _GET_LIST_TYPE_COPY_FUNCTION(plist_list)(pt_node->_pby_data, pt_varg->_pby_data, &b_result);
            assert(b_result);

            pt_node->_pt_next = plist_list->_pt_node;
            pt_node->_pt_prev = plist_list->_pt_node->_pt_prev;
            plist_list->_pt_node->_pt_prev->_pt_next = pt_node;
            plist_list->_pt_node->_pt_prev = pt_node;
            pt_node = NULL;
        }

        _list_destroy_varg_value_auxiliary(plist_list, pt_varg);
        _alloc_deallocate(&plist_list->_t_allocator, pt_varg, _LIST_NODE_SIZE(_GET_LIST_TYPE_SIZE(plist_list)), 1);
    }
}

/**
 * Initialize element with list element type auxiliary function.
 */
void _list_init_elem_auxiliary(list_t* plist_list, void* pv_elem)
{
    assert(plist_list != NULL);
    assert(pv_elem != NULL);
    assert(_list_is_inited(plist_list) || _list_is_created(plist_list));

    /* initialize new elements */
    if (_GET_LIST_TYPE_STYLE(plist_list) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_LIST_TYPE_NAME(plist_list), s_elemtypename);

        _GET_LIST_TYPE_INIT_FUNCTION(plist_list)(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = _GET_LIST_TYPE_SIZE(plist_list);
        _GET_LIST_TYPE_INIT_FUNCTION(plist_list)(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

