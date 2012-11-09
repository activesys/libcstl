/*
 *  The implementation of set private.
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
#include <cstl/cset.h>

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
bool_t _create_set_auxiliary(set_t* pset_set, const char* s_typename)
{
    assert(pset_set != NULL);
    assert(s_typename != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _create_avl_tree_auxiliary(&pset_set->_t_tree, s_typename);
#else
    return _create_rb_tree_auxiliary(&pset_set->_t_tree, s_typename);
#endif
}

/**
 * Destroy set container auxiliary function.
 */
void _set_destroy_auxiliary(set_t* pset_set)
{
    assert(pset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_destroy_auxiliary(&pset_set->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pset_set->_t_tree);
#endif
}

/**
 * Find specific element.
 */
set_iterator_t _set_find(const set_t* cpset_set, ...)
{
    set_iterator_t it_iter;
    va_list val_elemlist;

    assert(cpset_set != NULL);

    va_start(val_elemlist, cpset_set);
    it_iter = _set_find_varg(cpset_set, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Find specific element.
 */
set_iterator_t _set_find_varg(const set_t* cpset_set, va_list val_elemlist)
{
    set_iterator_t it_iter;
    void*          pv_varg = NULL;

    assert(cpset_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpset_set)->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(cpset_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpset_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    it_iter = _avl_tree_find(&cpset_set->_t_tree, pv_varg);
#else
    it_iter = _rb_tree_find(&cpset_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpset_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpset_set)->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(cpset_set), 1);

    _ITERATOR_CONTAINER(it_iter) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_iter) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return the number of specific elements in an set
 */
size_t _set_count(const set_t* cpset_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    assert(cpset_set != NULL);

    va_start(val_elemlist, cpset_set);
    t_count = _set_count_varg(cpset_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Return the number of specific elements in an set
 */
size_t _set_count_varg(const set_t* cpset_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    size_t         t_count = 0;

    assert(cpset_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpset_set)->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(cpset_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpset_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_count = _avl_tree_count(&cpset_set->_t_tree, pv_varg);
#else
    t_count = _rb_tree_count(&cpset_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpset_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpset_set)->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(cpset_set), 1);

    return t_count;
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
set_iterator_t _set_lower_bound(const set_t* cpset_set, ...)
{
    set_iterator_t it_iter;
    va_list val_elemlist;

    assert(cpset_set != NULL);

    va_start(val_elemlist, cpset_set);
    it_iter = _set_lower_bound_varg(cpset_set, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
set_iterator_t _set_lower_bound_varg(const set_t* cpset_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t it_iter;

    assert(cpset_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpset_set)->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(cpset_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpset_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    it_iter = _avl_tree_lower_bound(&cpset_set->_t_tree, pv_varg);
#else
    it_iter = _rb_tree_lower_bound(&cpset_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpset_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpset_set)->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(cpset_set), 1);

    _ITERATOR_CONTAINER(it_iter) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_iter) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
set_iterator_t _set_upper_bound(const set_t* cpset_set, ...)
{
    set_iterator_t it_iter;
    va_list val_elemlist;

    assert(cpset_set != NULL);

    va_start(val_elemlist, cpset_set);
    it_iter = _set_upper_bound_varg(cpset_set, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
set_iterator_t _set_upper_bound_varg(const set_t* cpset_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t it_iter;

    assert(cpset_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpset_set)->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(cpset_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpset_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    it_iter = _avl_tree_upper_bound(&cpset_set->_t_tree, pv_varg);
#else
    it_iter = _rb_tree_upper_bound(&cpset_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpset_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpset_set)->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(cpset_set), 1);

    _ITERATOR_CONTAINER(it_iter) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_iter) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _set_equal_range(const set_t* cpset_set, ...)
{
    range_t r_range;
    va_list val_elemlist;

    assert(cpset_set != NULL);

    va_start(val_elemlist, cpset_set);
    r_range = _set_equal_range_varg(cpset_set, val_elemlist);
    va_end(val_elemlist);

    return r_range;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _set_equal_range_varg(const set_t* cpset_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    range_t        r_range;

    assert(cpset_set != NULL);

    pv_varg = _alloc_allocate(&((set_t*)cpset_set)->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(cpset_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary((set_t*)cpset_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    r_range = _avl_tree_equal_range(&cpset_set->_t_tree, pv_varg);
#else
    r_range = _rb_tree_equal_range(&cpset_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary((set_t*)cpset_set, pv_varg);
    _alloc_deallocate(&((set_t*)cpset_set)->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(cpset_set), 1);

    _ITERATOR_CONTAINER(r_range.it_begin) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(r_range.it_begin) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(r_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _ITERATOR_CONTAINER(r_range.it_end) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(r_range.it_end) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(r_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return r_range;
}

/**
 * Inserts an unique element into a set.
 */
set_iterator_t _set_insert(set_t* pset_set, ...)
{
    set_iterator_t it_iter;
    va_list val_elemlist;

    assert(pset_set != NULL);

    va_start(val_elemlist, pset_set);
    it_iter = _set_insert_varg(pset_set, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Inserts an unique element into a set.
 */
set_iterator_t _set_insert_varg(set_t* pset_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    set_iterator_t it_iter;

    assert(pset_set != NULL);

    pv_varg = _alloc_allocate(&pset_set->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(pset_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pset_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    it_iter = _avl_tree_insert_unique(&pset_set->_t_tree, pv_varg);
#else
    it_iter = _rb_tree_insert_unique(&pset_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pset_set, pv_varg);
    _alloc_deallocate(&pset_set->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(pset_set), 1);

    _ITERATOR_CONTAINER(it_iter) = pset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_iter) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Inserts an unique element into a set with hint.
 */
set_iterator_t _set_insert_hint(set_t* pset_set, set_iterator_t it_hint, ...)
{
    set_iterator_t it_iter;
    va_list val_elemlist;

    assert(pset_set != NULL);

    va_start(val_elemlist, it_hint);
    it_iter = _set_insert_hint_varg(pset_set, it_hint, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Inserts an unique element into a set with hint.
 */
set_iterator_t _set_insert_hint_varg(set_t* pset_set, set_iterator_t it_hint, va_list val_elemlist)
{
    void* pv_varg = NULL;

    assert(pset_set != NULL);

    pv_varg = _alloc_allocate(&pset_set->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(pset_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pset_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    it_hint = _avl_tree_insert_unique(&pset_set->_t_tree, pv_varg);
#else
    it_hint = _rb_tree_insert_unique(&pset_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pset_set, pv_varg);
    _alloc_deallocate(&pset_set->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(pset_set), 1);

    _ITERATOR_CONTAINER(it_hint) = pset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_hint) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_hint) = _BIDIRECTIONAL_ITERATOR;

    return it_hint;
}

/**
 * Erase an element from a set that match a specified element.
 */
size_t _set_erase(set_t* pset_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    assert(pset_set != NULL);

    va_start(val_elemlist, pset_set);
    t_count = _set_erase_varg(pset_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Erase an element from a set that match a specified element.
 */
size_t _set_erase_varg(set_t* pset_set, va_list val_elemlist)
{
    void*          pv_varg = NULL;
    size_t         t_count = 0;

    assert(pset_set != NULL);

    pv_varg = _alloc_allocate(&pset_set->_t_tree._t_allocator, _GET_SET_TYPE_SIZE(pset_set), 1);
    assert(pv_varg != NULL);
    _set_get_varg_value_auxiliary(pset_set, val_elemlist, pv_varg);

#ifdef CSTL_SET_AVL_TREE
    t_count = _avl_tree_erase(&pset_set->_t_tree, pv_varg);
#else
    t_count = _rb_tree_erase(&pset_set->_t_tree, pv_varg);
#endif

    _set_destroy_varg_value_auxiliary(pset_set, pv_varg);
    _alloc_deallocate(&pset_set->_t_tree._t_allocator, pv_varg, _GET_SET_TYPE_SIZE(pset_set), 1);

    return t_count;
}

/**
 * Initialize element auxiliary function
 */
void _set_init_elem_auxiliary(set_t* pset_set, void* pv_value)
{
    assert(pset_set != NULL);
    assert(pv_value != NULL);

    /* initialize new elements */
    if (_GET_SET_TYPE_STYLE(pset_set) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_SET_TYPE_NAME(pset_set), s_elemtypename);
        _GET_SET_TYPE_INIT_FUNCTION(pset_set)(pv_value, s_elemtypename);
    } else {
        bool_t b_result = _GET_SET_TYPE_SIZE(pset_set);
        _GET_SET_TYPE_INIT_FUNCTION(pset_set)(pv_value, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

