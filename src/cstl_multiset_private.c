/*
 *  The implementation of multiset.
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

#ifdef CSTL_MULTISET_AVL_TREE
#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#include <cstl/cstl_avl_tree.h>
#else
#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>
#endif

#include <cstl/cstl_multiset_iterator.h>
#include <cstl/cstl_multiset_private.h>
#include <cstl/cstl_multiset.h>

#include "cstl_multiset_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create multiset container.
 */
multiset_t* _create_multiset(const char* s_typename)
{
#ifdef CSTL_MULTISET_AVL_TREE
    return (multiset_t*)_create_avl_tree(s_typename);
#else
    return (multiset_t*)_create_rb_tree(s_typename);
#endif
}

bool_t _create_multiset_auxiliary(multiset_t* pt_multiset, const char* s_typename)
{
    assert(pt_multiset != NULL && s_typename != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _create_avl_tree_auxiliary(&pt_multiset->_t_tree, s_typename);
#else
    return _create_rb_tree_auxiliary(&pt_multiset->_t_tree, s_typename);
#endif
}

void _multiset_destroy_auxiliary(multiset_t* pt_multiset)
{
    assert(pt_multiset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_destroy_auxiliary(&pt_multiset->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pt_multiset->_t_tree);
#endif
}

multiset_iterator_t _multiset_find(const multiset_t* cpt_multiset, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_iter = _multiset_find_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_find_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    multiset_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(cpt_multiset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_iter = _avl_tree_find(&cpt_multiset->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_find(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    _GET_CONTAINER(t_iter) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iter) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

size_t _multiset_count(const multiset_t* cpt_multiset, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_count = _multiset_count_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _multiset_count_varg(const multiset_t* cpt_multiset, va_list val_elemlist)
{
    size_t  t_count = 0;
    void*   pv_varg = NULL;

    assert(cpt_multiset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_count = _avl_tree_count(&cpt_multiset->_t_tree, pv_varg);
#else
    t_count = _rb_tree_count(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    return t_count;
}

multiset_iterator_t _multiset_lower_bound(const multiset_t* cpt_multiset, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_iter = _multiset_lower_bound_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_lower_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    multiset_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(cpt_multiset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_iter = _avl_tree_lower_bound(&cpt_multiset->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_lower_bound(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    _GET_CONTAINER(t_iter) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iter) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

multiset_iterator_t _multiset_upper_bound(const multiset_t* cpt_multiset, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_iter = _multiset_upper_bound_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_upper_bound_varg(
    const multiset_t* cpt_multiset, va_list val_elemlist)
{
    multiset_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(cpt_multiset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_iter = _avl_tree_upper_bound(&cpt_multiset->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_upper_bound(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    _GET_CONTAINER(t_iter) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iter) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

range_t _multiset_equal_range(const multiset_t* cpt_multiset, ...)
{
    range_t t_range;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_multiset);
    t_range = _multiset_equal_range_varg(cpt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_range;
}

range_t _multiset_equal_range_varg(const multiset_t* cpt_multiset, va_list val_elemlist)
{
    void*   pv_varg = NULL;
    range_t t_range;

    assert(cpt_multiset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_range = _avl_tree_equal_range(&cpt_multiset->_t_tree, pv_varg);
#else
    t_range = _rb_tree_equal_range(&cpt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpt_multiset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpt_multiset)->_t_tree._t_allocator, pv_varg,
        _GET_MULTISET_TYPE_SIZE(cpt_multiset), 1);

    _GET_CONTAINER(t_range.it_begin) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_range.it_begin) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _GET_CONTAINER(t_range.it_end) = (multiset_t*)cpt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_range.it_end) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return t_range;
}

multiset_iterator_t _multiset_insert(multiset_t* pt_multiset, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, pt_multiset);
    t_iter = _multiset_insert_varg(pt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_insert_varg(multiset_t* pt_multiset, va_list val_elemlist)
{
    multiset_iterator_t t_iter;
    void*               pv_varg = NULL;

    assert(pt_multiset != NULL);

    pv_varg = _alloc_allocate(&pt_multiset->_t_tree._t_allocator,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_iter = _avl_tree_insert_equal(&pt_multiset->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_insert_equal(&pt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pt_multiset, pv_varg);
    _alloc_deallocate(&pt_multiset->_t_tree._t_allocator, pv_varg,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);

    _GET_CONTAINER(t_iter) = pt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_iter) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

multiset_iterator_t _multiset_insert_hint(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, ...)
{
    multiset_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_hint);
    t_iter = _multiset_insert_hint_varg(pt_multiset, t_hint, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

multiset_iterator_t _multiset_insert_hint_varg(
    multiset_t* pt_multiset, multiset_iterator_t t_hint, va_list val_elemlist)
{
    void*               pv_varg = NULL;

    assert(pt_multiset != NULL);

    pv_varg = _alloc_allocate(&pt_multiset->_t_tree._t_allocator,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_hint = _avl_tree_insert_equal(&pt_multiset->_t_tree, pv_varg);
#else
    t_hint = _rb_tree_insert_equal(&pt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pt_multiset, pv_varg);
    _alloc_deallocate(&pt_multiset->_t_tree._t_allocator, pv_varg,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);

    _GET_CONTAINER(t_hint) = pt_multiset;
    _GET_MULTISET_CONTAINER_TYPE(t_hint) = _MULTISET_CONTAINER;
    _GET_MULTISET_ITERATOR_TYPE(t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

size_t _multiset_erase(multiset_t* pt_multiset, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, pt_multiset);
    t_count = _multiset_erase_varg(pt_multiset, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _multiset_erase_varg(multiset_t* pt_multiset, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(pt_multiset != NULL);

    pv_varg = _alloc_allocate(&pt_multiset->_t_tree._t_allocator,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pt_multiset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_count = _avl_tree_erase(&pt_multiset->_t_tree, pv_varg);
#else
    t_count = _rb_tree_erase(&pt_multiset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pt_multiset, pv_varg);
    _alloc_deallocate(&pt_multiset->_t_tree._t_allocator, pv_varg,
        _GET_MULTISET_TYPE_SIZE(pt_multiset), 1);

    return t_count;
}

void _multiset_init_elem_auxiliary(multiset_t* pt_multiset, void* pv_elem)
{
    assert(pt_multiset != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_MULTISET_TYPE_STYLE(pt_multiset) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_MULTISET_TYPE_NAME(pt_multiset), s_elemtypename);

        _GET_MULTISET_TYPE_INIT_FUNCTION(pt_multiset)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_MULTISET_TYPE_SIZE(pt_multiset);
        _GET_MULTISET_TYPE_INIT_FUNCTION(pt_multiset)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/

/** eof **/

