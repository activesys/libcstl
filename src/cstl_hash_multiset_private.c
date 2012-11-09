/*
 *  The implementation of hash_multiset private interface.
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
#include <cstl/chash_set.h>

#include "cstl_hash_multiset_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create hash_multiset container.
 */
hash_multiset_t* _create_hash_multiset(const char* s_typename)
{
    return (hash_multiset_t*)_create_hashtable(s_typename);
}

/**
 * Create hash_multiset container auxiliary function.
 */
bool_t _create_hash_multiset_auxiliary(hash_multiset_t* phmset_set, const char* s_typename)
{
    assert(phmset_set != NULL);
    assert(s_typename != NULL);

    return _create_hashtable_auxiliary(&phmset_set->_t_hashtable, s_typename);
}

/**
 * Destroy hash_multiset container auxiliary function.
 */
void _hash_multiset_destroy_auxiliary(hash_multiset_t* phmset_set)
{
    assert(phmset_set != NULL);

    _hashtable_destroy_auxiliary(&phmset_set->_t_hashtable);
}

/**
 * Find specific element.
 */
hash_multiset_iterator_t _hash_multiset_find(const hash_multiset_t* cphmset_set, ...)
{
    hash_multiset_iterator_t it_iter;
    va_list val_elemlist;

    assert(cphmset_set != NULL);

    va_start(val_elemlist, cphmset_set);
    it_iter = _hash_multiset_find_varg(cphmset_set, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Find specific element.
 */
hash_multiset_iterator_t _hash_multiset_find_varg(const hash_multiset_t* cphmset_set, va_list val_elemlist)
{
    hash_multiset_iterator_t it_iter;
    void*                    pv_varg = NULL;

    assert(cphmset_set != NULL);

    pv_varg = _alloc_allocate(
        &((hash_multiset_t*)cphmset_set)->_t_hashtable._t_allocator, _GET_HASH_MULTISET_TYPE_SIZE(cphmset_set), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary((hash_multiset_t*)cphmset_set, val_elemlist, pv_varg);

    it_iter = _hashtable_find(&cphmset_set->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary((hash_multiset_t*)cphmset_set, pv_varg);
    _alloc_deallocate(
        &((hash_multiset_t*)cphmset_set)->_t_hashtable._t_allocator, pv_varg, _GET_HASH_MULTISET_TYPE_SIZE(cphmset_set), 1);

    _ITERATOR_CONTAINER(it_iter) = (hash_multiset_t*)cphmset_set;
    _HASH_MULTISET_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_MULTISET_CONTAINER;
    _HASH_MULTISET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return the number of specific elements in an hash_multiset
 */
size_t _hash_multiset_count(const hash_multiset_t* cphmset_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    assert(cphmset_set != NULL);

    va_start(val_elemlist, cphmset_set);
    t_count = _hash_multiset_count_varg(cphmset_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Return the number of specific elements in an hash_multiset
 */
size_t _hash_multiset_count_varg(const hash_multiset_t* cphmset_set, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(cphmset_set != NULL);

    pv_varg = _alloc_allocate(
        &((hash_multiset_t*)cphmset_set)->_t_hashtable._t_allocator, _GET_HASH_MULTISET_TYPE_SIZE(cphmset_set), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary((hash_multiset_t*)cphmset_set, val_elemlist, pv_varg);

    t_count = _hashtable_count(&cphmset_set->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary((hash_multiset_t*)cphmset_set, pv_varg);
    _alloc_deallocate(
        &((hash_multiset_t*)cphmset_set)->_t_hashtable._t_allocator, pv_varg, _GET_HASH_MULTISET_TYPE_SIZE(cphmset_set), 1);

    return t_count;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hash_multiset_equal_range(const hash_multiset_t* cphmset_set, ...)
{
    range_t r_range;
    va_list val_elemlist;

    assert(cphmset_set != NULL);

    va_start(val_elemlist, cphmset_set);
    r_range = _hash_multiset_equal_range_varg(cphmset_set, val_elemlist);
    va_end(val_elemlist);

    return r_range;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hash_multiset_equal_range_varg(const hash_multiset_t* cphmset_set, va_list val_elemlist)
{
    range_t r_range;
    void*   pv_varg = NULL;

    assert(cphmset_set != NULL);

    pv_varg = _alloc_allocate(
        &((hash_multiset_t*)cphmset_set)->_t_hashtable._t_allocator, _GET_HASH_MULTISET_TYPE_SIZE(cphmset_set), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary((hash_multiset_t*)cphmset_set, val_elemlist, pv_varg);

    r_range = _hashtable_equal_range(&cphmset_set->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary((hash_multiset_t*)cphmset_set, pv_varg);
    _alloc_deallocate(
        &((hash_multiset_t*)cphmset_set)->_t_hashtable._t_allocator, pv_varg, _GET_HASH_MULTISET_TYPE_SIZE(cphmset_set), 1);

    _ITERATOR_CONTAINER(r_range.it_begin) = (hash_multiset_t*)cphmset_set;
    _HASH_MULTISET_ITERATOR_CONTAINER_TYPE(r_range.it_begin) = _HASH_MULTISET_CONTAINER;
    _HASH_MULTISET_ITERATOR_ITERATOR_TYPE(r_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _ITERATOR_CONTAINER(r_range.it_end) = (hash_multiset_t*)cphmset_set;
    _HASH_MULTISET_ITERATOR_CONTAINER_TYPE(r_range.it_end) = _HASH_MULTISET_CONTAINER;
    _HASH_MULTISET_ITERATOR_ITERATOR_TYPE(r_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return r_range;
}

/**
 * Inserts an unique element into a hash_multiset.
 */
hash_multiset_iterator_t _hash_multiset_insert(hash_multiset_t* phmset_set, ...)
{
    hash_multiset_iterator_t it_iter;
    va_list val_elemlist;

    assert(phmset_set != NULL);

    va_start(val_elemlist, phmset_set);
    it_iter = _hash_multiset_insert_varg(phmset_set, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Inserts an unique element into a hash_multiset.
 */
hash_multiset_iterator_t _hash_multiset_insert_varg(hash_multiset_t* phmset_set, va_list val_elemlist)
{
    hash_multiset_iterator_t it_iter;
    void*                    pv_varg = NULL;

    assert(phmset_set != NULL);

    pv_varg = _alloc_allocate(&phmset_set->_t_hashtable._t_allocator, _GET_HASH_MULTISET_TYPE_SIZE(phmset_set), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary(phmset_set, val_elemlist, pv_varg);

    it_iter = _hashtable_insert_equal(&phmset_set->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary(phmset_set, pv_varg);
    _alloc_deallocate(&phmset_set->_t_hashtable._t_allocator, pv_varg, _GET_HASH_MULTISET_TYPE_SIZE(phmset_set), 1);

    _ITERATOR_CONTAINER(it_iter) = phmset_set;
    _HASH_MULTISET_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_MULTISET_CONTAINER;
    _HASH_MULTISET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Erase an element from a hash_multiset that match a specified element.
 */
size_t _hash_multiset_erase(hash_multiset_t* phmset_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    assert(phmset_set != NULL);

    va_start(val_elemlist, phmset_set);
    t_count = _hash_multiset_erase_varg(phmset_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Erase an element from a hash_multiset that match a specified element.
 */
size_t _hash_multiset_erase_varg(hash_multiset_t* phmset_set, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(phmset_set != NULL);

    pv_varg = _alloc_allocate(&phmset_set->_t_hashtable._t_allocator, _GET_HASH_MULTISET_TYPE_SIZE(phmset_set), 1);
    assert(pv_varg != NULL);
    _hash_multiset_get_varg_value_auxiliary(phmset_set, val_elemlist, pv_varg);

    t_count = _hashtable_erase(&phmset_set->_t_hashtable, pv_varg);

    _hash_multiset_destroy_varg_value_auxiliary(phmset_set, pv_varg);
    _alloc_deallocate(&phmset_set->_t_hashtable._t_allocator, pv_varg, _GET_HASH_MULTISET_TYPE_SIZE(phmset_set), 1);

    return t_count;
}

/**
 * Initialize element auxiliary function
 */
void _hash_multiset_init_elem_auxiliary(hash_multiset_t* phmset_set, void* pv_elem)
{
    assert(phmset_set != NULL);
    assert(pv_elem != NULL);

    /* initialize new elements */
    if (_GET_HASH_MULTISET_TYPE_STYLE(phmset_set) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_HASH_MULTISET_TYPE_NAME(phmset_set), s_elemtypename);

        _GET_HASH_MULTISET_TYPE_INIT_FUNCTION(phmset_set)(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = _GET_HASH_MULTISET_TYPE_SIZE(phmset_set);
        _GET_HASH_MULTISET_TYPE_INIT_FUNCTION(phmset_set)(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

