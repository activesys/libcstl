/*
 *  The implementation of multiset.
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

/**
 * Create multiset container auxiliary function.
 */
bool_t _create_multiset_auxiliary(multiset_t* pmset_mset, const char* s_typename)
{
    assert(pmset_mset != NULL);
    assert(s_typename != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _create_avl_tree_auxiliary(&pmset_mset->_t_tree, s_typename);
#else
    return _create_rb_tree_auxiliary(&pmset_mset->_t_tree, s_typename);
#endif
}

/**
 * Destroy multiset container auxiliary function.
 */
void _multiset_destroy_auxiliary(multiset_t* pmset_mset)
{
    assert(pmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_destroy_auxiliary(&pmset_mset->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pmset_mset->_t_tree);
#endif
}

/**
 * Find specific element.
 */
multiset_iterator_t _multiset_find(const multiset_t* cpmset_mset, ...)
{
    multiset_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmset_mset);
    it_iter = _multiset_find_varg(cpmset_mset, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Find specific element.
 */
multiset_iterator_t _multiset_find_varg(const multiset_t* cpmset_mset, va_list val_elemlist)
{
    multiset_iterator_t it_iter;
    void*               pv_varg = NULL;

    assert(cpmset_mset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpmset_mset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    it_iter = _avl_tree_find(&cpmset_mset->_t_tree, pv_varg);
#else
    it_iter = _rb_tree_find(&cpmset_mset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpmset_mset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, pv_varg, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);

    _ITERATOR_CONTAINER(it_iter) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return the number of specific elements in an multiset
 */
size_t _multiset_count(const multiset_t* cpmset_mset, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cpmset_mset);
    t_count = _multiset_count_varg(cpmset_mset, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Return the number of specific elements in an multiset
 */
size_t _multiset_count_varg(const multiset_t* cpmset_mset, va_list val_elemlist)
{
    size_t  t_count = 0;
    void*   pv_varg = NULL;

    assert(cpmset_mset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpmset_mset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_count = _avl_tree_count(&cpmset_mset->_t_tree, pv_varg);
#else
    t_count = _rb_tree_count(&cpmset_mset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpmset_mset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, pv_varg, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);

    return t_count;
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
multiset_iterator_t _multiset_lower_bound(const multiset_t* cpmset_mset, ...)
{
    multiset_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmset_mset);
    it_iter = _multiset_lower_bound_varg(cpmset_mset, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
multiset_iterator_t _multiset_lower_bound_varg(const multiset_t* cpmset_mset, va_list val_elemlist)
{
    multiset_iterator_t it_iter;
    void*               pv_varg = NULL;

    assert(cpmset_mset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpmset_mset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    it_iter = _avl_tree_lower_bound(&cpmset_mset->_t_tree, pv_varg);
#else
    it_iter = _rb_tree_lower_bound(&cpmset_mset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpmset_mset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, pv_varg, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);

    _ITERATOR_CONTAINER(it_iter) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
multiset_iterator_t _multiset_upper_bound(const multiset_t* cpmset_mset, ...)
{
    multiset_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmset_mset);
    it_iter = _multiset_upper_bound_varg(cpmset_mset, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
multiset_iterator_t _multiset_upper_bound_varg(const multiset_t* cpmset_mset, va_list val_elemlist)
{
    multiset_iterator_t it_iter;
    void*               pv_varg = NULL;

    assert(cpmset_mset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpmset_mset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    it_iter = _avl_tree_upper_bound(&cpmset_mset->_t_tree, pv_varg);
#else
    it_iter = _rb_tree_upper_bound(&cpmset_mset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpmset_mset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, pv_varg, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);

    _ITERATOR_CONTAINER(it_iter) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _multiset_equal_range(const multiset_t* cpmset_mset, ...)
{
    range_t r_range;
    va_list val_elemlist;

    va_start(val_elemlist, cpmset_mset);
    r_range = _multiset_equal_range_varg(cpmset_mset, val_elemlist);
    va_end(val_elemlist);

    return r_range;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _multiset_equal_range_varg(const multiset_t* cpmset_mset, va_list val_elemlist)
{
    void*   pv_varg = NULL;
    range_t r_range;

    assert(cpmset_mset != NULL);

    pv_varg = _alloc_allocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary((multiset_t*)cpmset_mset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    r_range = _avl_tree_equal_range(&cpmset_mset->_t_tree, pv_varg);
#else
    r_range = _rb_tree_equal_range(&cpmset_mset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary((multiset_t*)cpmset_mset, pv_varg);
    _alloc_deallocate(&((multiset_t*)cpmset_mset)->_t_tree._t_allocator, pv_varg, _GET_MULTISET_TYPE_SIZE(cpmset_mset), 1);

    _ITERATOR_CONTAINER(r_range.it_begin) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(r_range.it_begin) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(r_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _ITERATOR_CONTAINER(r_range.it_end) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(r_range.it_end) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(r_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return r_range;
}

/**
 * Inserts an element into a multiset.
 */
multiset_iterator_t _multiset_insert(multiset_t* pmset_mset, ...)
{
    multiset_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, pmset_mset);
    it_iter = _multiset_insert_varg(pmset_mset, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Inserts an element into a multiset.
 */
multiset_iterator_t _multiset_insert_varg(multiset_t* pmset_mset, va_list val_elemlist)
{
    multiset_iterator_t it_iter;
    void*               pv_varg = NULL;

    assert(pmset_mset != NULL);

    pv_varg = _alloc_allocate(&pmset_mset->_t_tree._t_allocator, _GET_MULTISET_TYPE_SIZE(pmset_mset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pmset_mset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    it_iter = _avl_tree_insert_equal(&pmset_mset->_t_tree, pv_varg);
#else
    it_iter = _rb_tree_insert_equal(&pmset_mset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pmset_mset, pv_varg);
    _alloc_deallocate(&pmset_mset->_t_tree._t_allocator, pv_varg, _GET_MULTISET_TYPE_SIZE(pmset_mset), 1);

    _ITERATOR_CONTAINER(it_iter) = pmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Inserts an element into a multiset with hint.
 */
multiset_iterator_t _multiset_insert_hint(multiset_t* pmset_mset, multiset_iterator_t it_hint, ...)
{
    multiset_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, it_hint);
    it_iter = _multiset_insert_hint_varg(pmset_mset, it_hint, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Inserts an element into a multiset with hint.
 */
multiset_iterator_t _multiset_insert_hint_varg(multiset_t* pmset_mset, multiset_iterator_t it_hint, va_list val_elemlist)
{
    void*               pv_varg = NULL;

    assert(pmset_mset != NULL);

    pv_varg = _alloc_allocate(&pmset_mset->_t_tree._t_allocator, _GET_MULTISET_TYPE_SIZE(pmset_mset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pmset_mset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    it_hint = _avl_tree_insert_equal(&pmset_mset->_t_tree, pv_varg);
#else
    it_hint = _rb_tree_insert_equal(&pmset_mset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pmset_mset, pv_varg);
    _alloc_deallocate(&pmset_mset->_t_tree._t_allocator, pv_varg, _GET_MULTISET_TYPE_SIZE(pmset_mset), 1);

    _ITERATOR_CONTAINER(it_hint) = pmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_hint) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_hint) = _BIDIRECTIONAL_ITERATOR;

    return it_hint;
}

/**
 * Erase an element from a multiset that match a specified element.
 */
size_t _multiset_erase(multiset_t* pmset_mset, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, pmset_mset);
    t_count = _multiset_erase_varg(pmset_mset, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Erase an element from a multiset that match a specified element.
 */
size_t _multiset_erase_varg(multiset_t* pmset_mset, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(pmset_mset != NULL);

    pv_varg = _alloc_allocate(&pmset_mset->_t_tree._t_allocator, _GET_MULTISET_TYPE_SIZE(pmset_mset), 1);
    assert(pv_varg != NULL);
    _multiset_get_varg_value_auxiliary(pmset_mset, val_elemlist, pv_varg);

#ifdef CSTL_MULTISET_AVL_TREE
    t_count = _avl_tree_erase(&pmset_mset->_t_tree, pv_varg);
#else
    t_count = _rb_tree_erase(&pmset_mset->_t_tree, pv_varg);
#endif

    _multiset_destroy_varg_value_auxiliary(pmset_mset, pv_varg);
    _alloc_deallocate(&pmset_mset->_t_tree._t_allocator, pv_varg, _GET_MULTISET_TYPE_SIZE(pmset_mset), 1);

    return t_count;
}

/**
 * Initialize element auxiliary function
 */
void _multiset_init_elem_auxiliary(multiset_t* pmset_mset, void* pv_elem)
{
    assert(pmset_mset != NULL);
    assert(pv_elem != NULL);

    /* initialize new elements */
    if (_GET_MULTISET_TYPE_STYLE(pmset_mset) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_MULTISET_TYPE_NAME(pmset_mset), s_elemtypename);

        _GET_MULTISET_TYPE_INIT_FUNCTION(pmset_mset)(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = _GET_MULTISET_TYPE_SIZE(pmset_mset);
        _GET_MULTISET_TYPE_INIT_FUNCTION(pmset_mset)(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

