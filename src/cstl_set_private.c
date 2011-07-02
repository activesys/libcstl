/*
 *  The implementation of set private.
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

#ifdef CSTL_SET_AVL_TREE
#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#include <cstl/cstl_avl_tree.h>
#else
#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>
#endif

#include <cstl/cstl_set_iterator.h>
#include <cstl/cstl_set_private.h>
#include <cstl/cstl_set.h>

#include "cstl_set_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create set container.
 */
set_t* _create_set(const char* s_typename)
{
#ifdef CSTL_SET_AVL_TREE
    return (set_t*)_create_avl_tree(s_typename);
#else
    return (set_t*)_create_rb_tree(s_typename);
#endif
}

/**
 * Create set container auxiliary function.
 */
bool_t _create_set_auxiliary(set_t* pt_set, const char* s_typename)
{
    assert(pt_set != NULL);
    assert(s_typename != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _create_avl_tree_auxiliary(&pt_set->_t_tree, s_typename);
#else
    return _create_rb_tree_auxiliary(&pt_set->_t_tree, s_typename);
#endif
}

/**
 * Destroy set container auxiliary function.
 */
void _set_destroy_auxiliary(set_t* pt_set)
{
    assert(pt_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_destroy_auxiliary(&pt_set->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pt_set->_t_tree);
#endif
}

set_iterator_t _set_find(const set_t* cpt_set, ...)
{
    set_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_set);
    t_iter = _set_find_varg(cpt_set, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

set_iterator_t _set_find_varg(const set_t* cpt_set, va_list val_elemlist)
{
    set_iterator_t t_iter;
    void*          pv_varg = NULL;

    assert(cpt_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpt_set)->_t_tree._t_allocator,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_iter = _avl_tree_find(&cpt_set->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_find(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpt_set)->_t_tree._t_allocator, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    _GET_CONTAINER(t_iter) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_iter) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

size_t _set_count(const set_t* cpt_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_set);
    t_count = _set_count_varg(cpt_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _set_count_varg(const set_t* cpt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    size_t         t_count = 0;

    assert(cpt_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpt_set)->_t_tree._t_allocator,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_count = _avl_tree_count(&cpt_set->_t_tree, pv_varg);
#else
    t_count = _rb_tree_count(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpt_set)->_t_tree._t_allocator, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    return t_count;
}

set_iterator_t _set_lower_bound(const set_t* cpt_set, ...)
{
    set_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_set);
    t_iter = _set_lower_bound_varg(cpt_set, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

set_iterator_t _set_lower_bound_varg(const set_t* cpt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t t_iter;

    assert(cpt_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpt_set)->_t_tree._t_allocator,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_iter = _avl_tree_lower_bound(&cpt_set->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_lower_bound(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpt_set)->_t_tree._t_allocator, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    _GET_CONTAINER(t_iter) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_iter) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

set_iterator_t _set_upper_bound(const set_t* cpt_set, ...)
{
    set_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_set);
    t_iter = _set_upper_bound_varg(cpt_set, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

set_iterator_t _set_upper_bound_varg(const set_t* cpt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t t_iter;

    assert(cpt_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpt_set)->_t_tree._t_allocator,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_iter = _avl_tree_upper_bound(&cpt_set->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_upper_bound(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpt_set)->_t_tree._t_allocator, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    _GET_CONTAINER(t_iter) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_iter) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

range_t _set_equal_range(const set_t* cpt_set, ...)
{
    range_t t_range;
    va_list val_elemlist;

    va_start(val_elemlist, cpt_set);
    t_range = _set_equal_range_varg(cpt_set, val_elemlist);
    va_end(val_elemlist);

    return t_range;
}

range_t _set_equal_range_varg(const set_t* cpt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    range_t        t_range;

    assert(cpt_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpt_set)->_t_tree._t_allocator,
        _GET_SET_TYPE_SIZE(cpt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_range = _avl_tree_equal_range(&cpt_set->_t_tree, pv_varg);
#else
    t_range = _rb_tree_equal_range(&cpt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpt_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpt_set)->_t_tree._t_allocator, pv_varg,
        _GET_SET_TYPE_SIZE(cpt_set), 1);

    _GET_CONTAINER(t_range.it_begin) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_range.it_begin) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _GET_CONTAINER(t_range.it_end) = (set_t*)cpt_set;
    _GET_SET_CONTAINER_TYPE(t_range.it_end) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return t_range;
}

set_iterator_t _set_insert(set_t* pt_set, ...)
{
    set_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, pt_set);
    t_iter = _set_insert_varg(pt_set, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

set_iterator_t _set_insert_varg(set_t* pt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t t_iter;

    assert(pt_set != NULL);

    pv_varg = _alloc_allocate(&pt_set->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(pt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_iter = _avl_tree_insert_unique(&pt_set->_t_tree, pv_varg);
#else
    t_iter = _rb_tree_insert_unique(&pt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pt_set, pv_varg);
    _alloc_deallocate(&pt_set->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(pt_set), 1);

    _GET_CONTAINER(t_iter) = pt_set;
    _GET_SET_CONTAINER_TYPE(t_iter) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

set_iterator_t _set_insert_hint(set_t* pt_set, set_iterator_t t_hint, ...)
{
    set_iterator_t t_iter;
    va_list val_elemlist;

    va_start(val_elemlist, t_hint);
    t_iter = _set_insert_hint_varg(pt_set, t_hint, val_elemlist);
    va_end(val_elemlist);

    return t_iter;
}

set_iterator_t _set_insert_hint_varg(
    set_t* pt_set, set_iterator_t t_hint, va_list val_elemlist)
{
    void* pv_varg = NULL;

    assert(pt_set != NULL);

    pv_varg = _alloc_allocate(&pt_set->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(pt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_hint = _avl_tree_insert_unique(&pt_set->_t_tree, pv_varg);
#else
    t_hint = _rb_tree_insert_unique(&pt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pt_set, pv_varg);
    _alloc_deallocate(&pt_set->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(pt_set), 1);

    _GET_CONTAINER(t_hint) = pt_set;
    _GET_SET_CONTAINER_TYPE(t_hint) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

size_t _set_erase(set_t* pt_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, pt_set);
    t_count = _set_erase_varg(pt_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

size_t _set_erase_varg(set_t* pt_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    size_t         t_count = 0;

    assert(pt_set != NULL);

    pv_varg = _alloc_allocate(&pt_set->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(pt_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pt_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_count = _avl_tree_erase(&pt_set->_t_tree, pv_varg);
#else
    t_count = _rb_tree_erase(&pt_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pt_set, pv_varg);
    _alloc_deallocate(&pt_set->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(pt_set), 1);

    return t_count;
}

void _set_init_elem_auxiliary(set_t* pt_set, void* pv_elem)
{
    assert(pt_set != NULL && pv_elem != NULL);

    /* initialize new elements */
    if(_GET_SET_TYPE_STYLE(pt_set) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_SET_TYPE_NAME(pt_set), s_elemtypename);

        _GET_SET_TYPE_INIT_FUNCTION(pt_set)(pv_elem, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_SET_TYPE_SIZE(pt_set);
        _GET_SET_TYPE_INIT_FUNCTION(pt_set)(pv_elem, &t_result);
        assert(t_result);
    }
}

/** local function implementation section **/

/** eof **/

