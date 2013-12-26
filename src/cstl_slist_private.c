/*
 *  The implementation of slist private function.
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
#include <cstl/cslist.h>

#include "cstl_slist_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create slist container.
 */
slist_t* _create_slist(const char* s_typename)
{
    slist_t* pslist_new = NULL;

    assert(s_typename != NULL);

    /* allocate memory for slist */
    if ((pslist_new = (slist_t*)malloc(sizeof(slist_t))) == NULL) {
        return NULL;
    }

    if (!_create_slist_auxiliary(pslist_new, s_typename)) {
        free(pslist_new);
        return NULL;
    }

    return pslist_new;
}

/**
 * Create slist container auxiliary function.
 */
bool_t _create_slist_auxiliary(slist_t* pslist_slist, const char* s_typename)
{
    assert(pslist_slist != NULL);
    assert(s_typename != NULL);

    _type_get_type(&pslist_slist->_t_typeinfo, s_typename);
    if (pslist_slist->_t_typeinfo._t_style == _TYPE_INVALID) {
        return false;
    }

    pslist_slist->_t_head._pt_next = NULL;

    _alloc_init(&pslist_slist->_t_allocator);
    return true;
}

/**
 * Initialize slist with specified element.
 */
void _slist_init_elem(slist_t* pslist_slist, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pslist_slist != NULL);
    assert(_slist_is_created(pslist_slist));

    va_start(val_elemlist, t_count);
    _slist_init_elem_varg(pslist_slist, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Initialize slist with variable argument slist of specified element.
 */
void _slist_init_elem_varg(slist_t* pslist_slist, size_t t_count, va_list val_elemlist)
{
    _slistnode_t* pt_varg = NULL;
    bool_t        b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_created(pslist_slist));

    /* allocate memory for n_elemcount slist node */
    if (t_count > 0) {
        size_t        i = 0;
        _slistnode_t* pt_node = NULL;

        /* get varg value only once */
        pt_varg = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
        assert(pt_varg != NULL);
        _slist_get_varg_value_auxiliary(pslist_slist, val_elemlist, pt_varg);

        for (i = 0; i < t_count; ++i) {
            pt_node = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
            assert(pt_node != NULL);
            _slist_init_node_auxiliary(pslist_slist, pt_node);
            /* copy value from varg */
            b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
            _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(pt_node->_pby_data, pt_varg->_pby_data, &b_result);
            assert(b_result);

            /* insert the new slist node after the head */
            pt_node->_pt_next = pslist_slist->_t_head._pt_next;
            pslist_slist->_t_head._pt_next = pt_node;
            pt_node = NULL;
        }

        _slist_destroy_varg_value_auxiliary(pslist_slist, pt_varg);
        _alloc_deallocate(&pslist_slist->_t_allocator, pt_varg, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
    }
}

/**
 * Destroy slist container auxiliary function.
 */
void _slist_destroy_auxiliary(slist_t* pslist_slist)
{
    _slistnode_t* pt_node = NULL;
    bool_t        b_result = false;

    /* test the pslist_slist is valid */
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist) || _slist_is_created(pslist_slist));

    /* _alloc_deallocate all nodes in slist */
    while (pslist_slist->_t_head._pt_next != NULL) {
        /* take out each node from the slist */
        pt_node = pslist_slist->_t_head._pt_next;
        pslist_slist->_t_head._pt_next = pt_node->_pt_next;
        pt_node->_pt_next = NULL;

        /* destroy the node itself */
        b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_DESTROY_FUNCTION(pslist_slist)(pt_node->_pby_data, &b_result);
        assert(b_result);

        _alloc_deallocate(&pslist_slist->_t_allocator, pt_node, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
        pt_node = NULL;
    }

    /* _alloc_deallocate the allocator */
    _alloc_destroy(&pslist_slist->_t_allocator);
}


/**
 * Assign slist with specificed element.
 */
void _slist_assign_elem(slist_t* pslist_slist, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    va_start(val_elemlist, t_count);
    _slist_assign_elem_varg(pslist_slist, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Assign slist with variable argument of specificed element.
 */
void _slist_assign_elem_varg(slist_t* pslist_slist, size_t t_count, va_list val_elemlist)
{
    slist_iterator_t it_iter;
    slist_iterator_t it_begin;
    slist_iterator_t it_end;
    _slistnode_t*    pt_varg = NULL;
    bool_t           b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    slist_resize(pslist_slist, t_count);

    /* get varg value */
    pt_varg = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
    assert(pt_varg != NULL);
    _slist_get_varg_value_auxiliary(pslist_slist, val_elemlist, pt_varg);

    it_begin = slist_begin(pslist_slist);
    it_end = slist_end(pslist_slist);

    /* copy value from varg */
    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, pt_varg->_pby_data, &b_result);
        assert(b_result);
    }

    /* destroy varg value */
    _slist_destroy_varg_value_auxiliary(pslist_slist, pt_varg);
    _alloc_deallocate(&pslist_slist->_t_allocator, pt_varg, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
}

/**
 * Add specificed element at the begin of slist container. 
 */
void _slist_push_front(slist_t* pslist_slist, ...)
{
    va_list val_elemlist;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    va_start(val_elemlist, pslist_slist);
    _slist_push_front_varg(pslist_slist, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Add specificed element from variable argument slist at the begin of slist container. 
 */
void _slist_push_front_varg(slist_t* pslist_slist, va_list val_elemlist)
{
    _slistnode_t* pt_node = NULL;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    /* allocate memory for new element and copy the element from elemlist */
    pt_node = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
    assert(pt_node != NULL);
    _slist_get_varg_value_auxiliary(pslist_slist, val_elemlist, pt_node);

    /* insert the element after the head */
    pt_node->_pt_next = pslist_slist->_t_head._pt_next;
    pslist_slist->_t_head._pt_next = pt_node;
}

/**
 * Insert one copy of element befor specificed position.
 */
slist_iterator_t _slist_insert(slist_t* pslist_slist, slist_iterator_t it_pos, ...)
{
    va_list val_elemlist;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));

    /* if the pos is slist begin iterator */
    va_start(val_elemlist, it_pos);
    if (iterator_equal(it_pos, slist_begin(pslist_slist))) {
        /* call push front */
        _slist_push_front_varg(pslist_slist, val_elemlist);
    } else {
        /* call insert_after */
        _slist_insert_after_n_varg(pslist_slist, slist_previous(pslist_slist, it_pos), 1, val_elemlist);
    }
    va_end(val_elemlist);

    /* return the new element iterator */
    return slist_previous(pslist_slist, it_pos);
}

/**
 * Insert one copy of element after specificed position.
 */
slist_iterator_t _slist_insert_after(slist_t* pslist_slist, slist_iterator_t it_pos, ...)
{
    va_list val_elemlist;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(!iterator_equal(it_pos, slist_end(pslist_slist)));

    va_start(val_elemlist, it_pos);
    _slist_insert_after_n_varg(pslist_slist, it_pos, 1, val_elemlist);
    va_end(val_elemlist);

    return iterator_next(it_pos);
}

/**
 * Insert multiple copys of element befor specificed position.
 */
void _slist_insert_n(slist_t* pslist_slist, slist_iterator_t it_pos, size_t t_count, ...)
{
    va_list val_elemlist;

    /* test the slist pointer and pos is valid */
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));

    /* if the pos is slist begin */
    va_start(val_elemlist, t_count);
    if (iterator_equal(it_pos, slist_begin(pslist_slist))) {
        size_t i = 0;
        /* call slist push front t_count times */
        for (i = 0; i < t_count; ++i) {
            va_list val_elemlist_copy;

            va_copy(val_elemlist_copy, val_elemlist);
            _slist_push_front_varg(pslist_slist, val_elemlist_copy);
            va_end(val_elemlist_copy);
        }
    } else {
        _slist_insert_after_n_varg(pslist_slist, slist_previous(pslist_slist, it_pos), t_count, val_elemlist);
    }
    va_end(val_elemlist);
}

/**
 * Insert multiple copys of element after specificed position.
 */
void _slist_insert_after_n(slist_t* pslist_slist, slist_iterator_t it_pos, size_t t_count, ...)
{
    va_list val_elemlist;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(!iterator_equal(it_pos, slist_end(pslist_slist)));

    va_start(val_elemlist, t_count);
    _slist_insert_after_n_varg(pslist_slist, it_pos, t_count, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Insert multiple copys of element after specificed position.
 */
void _slist_insert_after_n_varg(slist_t* pslist_slist, slist_iterator_t it_pos, size_t t_count, va_list val_elemlist)
{
    size_t        i = 0;
    _slistnode_t* pt_node = NULL;
    _slistnode_t* pt_varg = NULL;
    bool_t        b_result = false;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));
    assert(_slist_iterator_belong_to_slist(pslist_slist, it_pos));
    assert(!iterator_equal(it_pos, slist_end(pslist_slist)));

    /* get varg value only once */
    pt_varg = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
    assert(pt_varg != NULL);
    _slist_get_varg_value_auxiliary(pslist_slist, val_elemlist, pt_varg);

    for (i = 0; i < t_count; ++i) {
        /* allocate slist node */
        pt_node = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
        assert(pt_node != NULL);
        _slist_init_node_auxiliary(pslist_slist, pt_node);

        /* copy value from varg */
        b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(pt_node->_pby_data, pt_varg->_pby_data, &b_result);
        assert(b_result);

        /* link the node to slist */
        pt_node->_pt_next = ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pt_next;
        ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pt_next = pt_node;
        pt_node = NULL;
    }

    /* destroy varg value */
    _slist_destroy_varg_value_auxiliary(pslist_slist, pt_varg);
    _alloc_deallocate(&pslist_slist->_t_allocator, pt_varg, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
}

/**
 * Remove specificed element from slist container.
 */
void _slist_remove(slist_t* pslist_slist, ...)
{
    va_list val_elemlist;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    va_start(val_elemlist, pslist_slist);
    _slist_remove_varg(pslist_slist, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Remove element that specificed by variable argument slist from slist container.
 */
void _slist_remove_varg(slist_t* pslist_slist, va_list val_elemlist)
{
    slist_iterator_t it_iter; /* for iterate */
    slist_iterator_t it_end;
    _slistnode_t*    pt_varg = NULL;
    bool_t           b_less = false;
    bool_t           b_greater = false;

    /* test the pointer is valid */
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    pt_varg = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
    assert(pt_varg != NULL);
    _slist_get_varg_value_auxiliary(pslist_slist, val_elemlist, pt_varg);

    it_iter = slist_begin(pslist_slist);
    it_end = slist_end(pslist_slist);
    while (!iterator_equal(it_iter, it_end)) {
        b_less = b_greater = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_LESS_FUNCTION(pslist_slist)(
            pt_varg->_pby_data, ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, &b_less);
        _GET_SLIST_TYPE_LESS_FUNCTION(pslist_slist)(
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_iter))->_pby_data, pt_varg->_pby_data, &b_greater);
        if (b_less || b_greater) {
            it_iter = iterator_next(it_iter);
        } else {
            it_iter = slist_erase(pslist_slist, it_iter);
        }
    }

    _slist_destroy_varg_value_auxiliary(pslist_slist, pt_varg);
    _alloc_deallocate(&pslist_slist->_t_allocator, pt_varg, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
}

/**
 * Reset the size of slist elements.
 */
void _slist_resize_elem(slist_t* pslist_slist, size_t t_resize, ...)
{
    va_list val_elemlist;

    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    va_start(val_elemlist, t_resize);
    _slist_resize_elem_varg(pslist_slist, t_resize, val_elemlist);
    va_end(val_elemlist);
}

/**
 * Reset the size of slist elements, and filled element is from variable argument slist.
 */
void _slist_resize_elem_varg(slist_t* pslist_slist, size_t t_resize, va_list val_elemlist)
{
    assert(pslist_slist != NULL);
    assert(_slist_is_inited(pslist_slist));

    if (t_resize <= slist_size(pslist_slist)) {
        slist_iterator_t it_pos = iterator_advance(slist_begin(pslist_slist), t_resize);
        slist_erase_range(pslist_slist, it_pos, slist_end(pslist_slist));
    } else {
        slist_iterator_t it_pos;
        _slistnode_t*    pt_node = NULL;
        _slistnode_t*    pt_varg = NULL;
        size_t           t_size = slist_size(pslist_slist);
        size_t           i = 0;
        bool_t           b_result = false;

        if (!slist_empty(pslist_slist)) {
            it_pos = slist_previous(pslist_slist, slist_end(pslist_slist));
        } else {
            _SLIST_ITERATOR_COREPOS(it_pos) = (_byte_t*)&pslist_slist->_t_head;
        }

        /* get varg value only once */
        pt_varg = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
        assert(pt_varg != NULL);
        _slist_get_varg_value_auxiliary(pslist_slist, val_elemlist, pt_varg);

        for (i = 0; i < t_resize - t_size; ++i) {
            pt_node = _alloc_allocate(&pslist_slist->_t_allocator, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
            assert(pt_node != NULL);
            _slist_init_node_auxiliary(pslist_slist, pt_node);

            /* copy value from varg */
            b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
            _GET_SLIST_TYPE_COPY_FUNCTION(pslist_slist)(pt_node->_pby_data, pt_varg->_pby_data, &b_result);
            assert(b_result);

            pt_node->_pt_next = ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pt_next;
            ((_slistnode_t*)_SLIST_ITERATOR_COREPOS(it_pos))->_pt_next = pt_node;
            pt_node = NULL;
        }

        _slist_destroy_varg_value_auxiliary(pslist_slist, pt_varg);
        _alloc_deallocate(&pslist_slist->_t_allocator, pt_varg, _SLIST_NODE_SIZE(_GET_SLIST_TYPE_SIZE(pslist_slist)), 1);
    }
}

/**
 * Initialize element with slist element type auxiliary function.
 */
void _slist_init_elem_auxiliary(slist_t* pslist_slist, void* pv_value)
{
    assert(pslist_slist != NULL);
    assert(pv_value != NULL);
    assert(_slist_is_inited(pslist_slist) || _slist_is_created(pslist_slist));

    /* initialize new elements */
    if (_GET_SLIST_TYPE_STYLE(pslist_slist) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_SLIST_TYPE_NAME(pslist_slist), s_elemtypename);

        _GET_SLIST_TYPE_INIT_FUNCTION(pslist_slist)(pv_value, s_elemtypename);
    } else {
        bool_t b_result = _GET_SLIST_TYPE_SIZE(pslist_slist);
        _GET_SLIST_TYPE_INIT_FUNCTION(pslist_slist)(pv_value, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

