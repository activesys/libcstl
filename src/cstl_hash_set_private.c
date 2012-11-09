/*
 *  The implementation of hash_set private functions.
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

#include "cstl_hash_set_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create hash_set container.
 */
hash_set_t* _create_hash_set(const char* s_typename)
{
    return (hash_set_t*)_create_hashtable(s_typename);
}

/**
 * Create hash_set container auxiliary function.
 */
bool_t _create_hash_set_auxiliary(hash_set_t* phset_set, const char* s_typename)
{
    assert(phset_set != NULL);
    assert(s_typename != NULL);

    return _create_hashtable_auxiliary(&phset_set->_t_hashtable, s_typename);
}

/**
 * Destroy hash_set container auxiliary function.
 */
void _hash_set_destroy_auxiliary(hash_set_t* phset_set)
{
    assert(phset_set != NULL);

    _hashtable_destroy_auxiliary(&phset_set->_t_hashtable);
}

/**
 * Find specific element.
 */
hash_set_iterator_t _hash_set_find(const hash_set_t* cphset_set, ...)
{
    hash_set_iterator_t it_iter;
    va_list val_elemlist;

    assert(cphset_set != NULL);

    va_start(val_elemlist, cphset_set);
    it_iter = _hash_set_find_varg(cphset_set, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Find specific element.
 */
hash_set_iterator_t _hash_set_find_varg(const hash_set_t* cphset_set, va_list val_elemlist)
{
    hash_set_iterator_t it_iter;
    void*               pv_varg = NULL;

    assert(cphset_set != NULL);

    pv_varg = _alloc_allocate(&((hash_set_t*)cphset_set)->_t_hashtable._t_allocator, _GET_HASH_SET_TYPE_SIZE(cphset_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary((hash_set_t*)cphset_set, val_elemlist, pv_varg);

    it_iter = _hashtable_find(&cphset_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary((hash_set_t*)cphset_set, pv_varg);
    _alloc_deallocate(&((hash_set_t*)cphset_set)->_t_hashtable._t_allocator, pv_varg, _GET_HASH_SET_TYPE_SIZE(cphset_set), 1);

    _ITERATOR_CONTAINER(it_iter) = (hash_set_t*)cphset_set;
    _HASH_SET_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_SET_CONTAINER;
    _HASH_SET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return the number of specific elements in an hash_set
 */
size_t _hash_set_count(const hash_set_t* cphset_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    assert(cphset_set != NULL);

    va_start(val_elemlist, cphset_set);
    t_count = _hash_set_count_varg(cphset_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Return the number of specific elements in an hash_set
 */
size_t _hash_set_count_varg(const hash_set_t* cphset_set, va_list val_elemlist)
{
    size_t t_count = 0;
    void*  pv_varg = NULL;

    assert(cphset_set != NULL);

    pv_varg = _alloc_allocate(&((hash_set_t*)cphset_set)->_t_hashtable._t_allocator, _GET_HASH_SET_TYPE_SIZE(cphset_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary((hash_set_t*)cphset_set, val_elemlist, pv_varg);

    t_count = _hashtable_count(&cphset_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary((hash_set_t*)cphset_set, pv_varg);
    _alloc_deallocate(&((hash_set_t*)cphset_set)->_t_hashtable._t_allocator, pv_varg, _GET_HASH_SET_TYPE_SIZE(cphset_set), 1);

    return t_count;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hash_set_equal_range(const hash_set_t* cphset_set, ...)
{
    range_t r_range;
    va_list val_elemlist;

    assert(cphset_set != NULL);

    va_start(val_elemlist, cphset_set);
    r_range = _hash_set_equal_range_varg(cphset_set, val_elemlist);
    va_end(val_elemlist);

    return r_range;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hash_set_equal_range_varg(const hash_set_t* cphset_set, va_list val_elemlist)
{
    range_t r_range;
    void*   pv_varg = NULL;

    assert(cphset_set != NULL);

    pv_varg = _alloc_allocate(&((hash_set_t*)cphset_set)->_t_hashtable._t_allocator, _GET_HASH_SET_TYPE_SIZE(cphset_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary((hash_set_t*)cphset_set, val_elemlist, pv_varg);

    r_range = _hashtable_equal_range(&cphset_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary((hash_set_t*)cphset_set, pv_varg);
    _alloc_deallocate(&((hash_set_t*)cphset_set)->_t_hashtable._t_allocator, pv_varg, _GET_HASH_SET_TYPE_SIZE(cphset_set), 1);

    _ITERATOR_CONTAINER(r_range.it_begin) = (hash_set_t*)cphset_set;
    _HASH_SET_ITERATOR_CONTAINER_TYPE(r_range.it_begin) = _HASH_SET_CONTAINER;
    _HASH_SET_ITERATOR_ITERATOR_TYPE(r_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _ITERATOR_CONTAINER(r_range.it_end) = (hash_set_t*)cphset_set;
    _HASH_SET_ITERATOR_CONTAINER_TYPE(r_range.it_end) = _HASH_SET_CONTAINER;
    _HASH_SET_ITERATOR_ITERATOR_TYPE(r_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return r_range;
}

/**
 * Inserts an unique element into a hash_set.
 */
hash_set_iterator_t _hash_set_insert(hash_set_t* phset_set, ...)
{
    hash_set_iterator_t it_iter;
    va_list val_elemlist;

    assert(phset_set != NULL);

    va_start(val_elemlist, phset_set);
    it_iter = _hash_set_insert_varg(phset_set, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Inserts an unique element into a hash_set.
 */
hash_set_iterator_t _hash_set_insert_varg(hash_set_t* phset_set, va_list val_elemlist)
{
    hash_set_iterator_t it_iter;
    void*               pv_varg = NULL;

    assert(phset_set != NULL);

    pv_varg = _alloc_allocate(&phset_set->_t_hashtable._t_allocator, _GET_HASH_SET_TYPE_SIZE(phset_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary(phset_set, val_elemlist, pv_varg);

    it_iter = _hashtable_insert_unique(&phset_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary(phset_set, pv_varg);
    _alloc_deallocate(&phset_set->_t_hashtable._t_allocator, pv_varg, _GET_HASH_SET_TYPE_SIZE(phset_set), 1);

    _ITERATOR_CONTAINER(it_iter) = phset_set;
    _HASH_SET_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_SET_CONTAINER;
    _HASH_SET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Erase an element from a hash_set that match a specified element.
 */
size_t _hash_set_erase(hash_set_t* phset_set, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    assert(phset_set != NULL);

    va_start(val_elemlist, phset_set);
    t_count = _hash_set_erase_varg(phset_set, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Erase an element from a hash_set that match a specified element.
 */
size_t _hash_set_erase_varg(hash_set_t* phset_set, va_list val_elemlist)
{
    size_t  t_count = 0;
    void*   pv_varg = NULL;

    assert(phset_set != NULL);

    pv_varg = _alloc_allocate(&phset_set->_t_hashtable._t_allocator, _GET_HASH_SET_TYPE_SIZE(phset_set), 1);
    assert(pv_varg != NULL);
    _hash_set_get_varg_value_auxiliary(phset_set, val_elemlist, pv_varg);

    t_count = _hashtable_erase(&phset_set->_t_hashtable, pv_varg);

    _hash_set_destroy_varg_value_auxiliary(phset_set, pv_varg);
    _alloc_deallocate(&phset_set->_t_hashtable._t_allocator, pv_varg, _GET_HASH_SET_TYPE_SIZE(phset_set), 1);

    return t_count;
}

/**
 * Initialize element auxiliary function
 */
void _hash_set_init_elem_auxiliary(hash_set_t* phset_set, void* pv_elem)
{
    assert(phset_set != NULL);
    assert(pv_elem != NULL);

    /* initialize new elements */
    if (_GET_HASH_SET_TYPE_STYLE(phset_set) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_HASH_SET_TYPE_NAME(phset_set), s_elemtypename);

        _GET_HASH_SET_TYPE_INIT_FUNCTION(phset_set)(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = _GET_HASH_SET_TYPE_SIZE(phset_set);
        _GET_HASH_SET_TYPE_INIT_FUNCTION(phset_set)(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

