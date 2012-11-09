/*
 *  The implementation of hash_multimap private interface.
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
#include <cstl/cstring.h>
#include <cstl/chash_map.h>

#include "cstl_hash_multimap_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create hash_multimap container.
 */
hash_multimap_t* _create_hash_multimap(const char* s_typename)
{
    hash_multimap_t* phmmap_map = NULL;

    if ((phmmap_map = (hash_multimap_t*)malloc(sizeof(hash_multimap_t))) == NULL) {
        return NULL;
    }

    if (!_create_hash_multimap_auxiliary(phmmap_map, s_typename)) {
        free(phmmap_map);
        return NULL;
    }

    return phmmap_map;
}

/**
 * Create hash_multimap container auxiliary function.
 */
bool_t _create_hash_multimap_auxiliary(hash_multimap_t* phmmap_map, const char* s_typename)
{
    char s_typenameex[_TYPE_NAME_SIZE + 1];

    assert(phmmap_map != NULL);
    assert(s_typename != NULL);

    if (!_create_pair_auxiliary(&phmmap_map->_pair_temp, s_typename)) {
        return false;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, "pair_t", _TYPE_NAME_SIZE);
    strncat(s_typenameex, "<", _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, ">", _TYPE_NAME_SIZE);

    phmmap_map->_bfun_keycompare = NULL;
    phmmap_map->_bfun_valuecompare = NULL;

    return _create_hashtable_auxiliary(&phmmap_map->_t_hashtable, s_typenameex);
}

/**
 * Destroy hash_multimap container auxiliary function.
 */
void _hash_multimap_destroy_auxiliary(hash_multimap_t* phmmap_map)
{
    assert(phmmap_map != NULL);

    _pair_destroy_auxiliary(&phmmap_map->_pair_temp);
    _hashtable_destroy_auxiliary(&phmmap_map->_t_hashtable);

    phmmap_map->_bfun_keycompare = NULL;
    phmmap_map->_bfun_valuecompare = NULL;
}

/**
 * Find specific element.
 */
hash_multimap_iterator_t _hash_multimap_find(const hash_multimap_t* cphmmap_map, ...)
{
    hash_multimap_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cphmmap_map);
    it_iter = _hash_multimap_find_varg(cphmmap_map, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Find specific element.
 */
hash_multimap_iterator_t _hash_multimap_find_varg(const hash_multimap_t* cphmmap_map, va_list val_elemlist)
{
    hash_multimap_iterator_t it_iter;

    assert(cphmmap_map != NULL);

    _type_get_varg_value(&((hash_multimap_t*)cphmmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cphmmap_map->_pair_temp._pv_first);

    it_iter = _hashtable_find(&cphmmap_map->_t_hashtable, &cphmmap_map->_pair_temp);

    _ITERATOR_CONTAINER(it_iter) = (hash_multimap_t*)cphmmap_map;
    _HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_MULTIMAP_CONTAINER;
    _HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return the number of specific elements in an hash_multimap
 */
size_t _hash_multimap_count(const hash_multimap_t* cphmmap_map, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cphmmap_map);
    t_count = _hash_multimap_count_varg(cphmmap_map, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Return the number of specific elements in an hash_multimap
 */
size_t _hash_multimap_count_varg(const hash_multimap_t* cphmmap_map, va_list val_elemlist)
{
    assert(cphmmap_map != NULL);

    _type_get_varg_value(&((hash_multimap_t*)cphmmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cphmmap_map->_pair_temp._pv_first);

    return _hashtable_count(&cphmmap_map->_t_hashtable, &cphmmap_map->_pair_temp);
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hash_multimap_equal_range(const hash_multimap_t* cphmmap_map, ...)
{
    range_t r_range;
    va_list val_elemlist;

    va_start(val_elemlist, cphmmap_map);
    r_range = _hash_multimap_equal_range_varg(cphmmap_map, val_elemlist);
    va_end(val_elemlist);

    return r_range;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hash_multimap_equal_range_varg(const hash_multimap_t* cphmmap_map, va_list val_elemlist)
{
    range_t  r_range;

    assert(cphmmap_map != NULL);

    _type_get_varg_value(&((hash_multimap_t*)cphmmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cphmmap_map->_pair_temp._pv_first);

    r_range = _hashtable_equal_range(&cphmmap_map->_t_hashtable, &cphmmap_map->_pair_temp);

    _ITERATOR_CONTAINER(r_range.it_begin) = (hash_multimap_t*)cphmmap_map;
    _HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(r_range.it_begin) = _HASH_MULTIMAP_CONTAINER;
    _HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(r_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _ITERATOR_CONTAINER(r_range.it_end) = (hash_multimap_t*)cphmmap_map;
    _HASH_MULTIMAP_ITERATOR_CONTAINER_TYPE(r_range.it_end) = _HASH_MULTIMAP_CONTAINER;
    _HASH_MULTIMAP_ITERATOR_ITERATOR_TYPE(r_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return r_range;
}

/**
 * Erase an element from a hash_multimap that match a specified element.
 */
size_t _hash_multimap_erase(hash_multimap_t* phmmap_map, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, phmmap_map);
    t_count = _hash_multimap_erase_varg(phmmap_map, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Erase an element from a hash_multimap that match a specified element.
 */
size_t _hash_multimap_erase_varg(hash_multimap_t* phmmap_map, va_list val_elemlist)
{
    assert(phmmap_map != NULL);

    _type_get_varg_value(&phmmap_map->_pair_temp._t_typeinfofirst, val_elemlist, phmmap_map->_pair_temp._pv_first);

    return _hashtable_erase(&phmmap_map->_t_hashtable, &phmmap_map->_pair_temp);
}

/**
 * Initialize element auxiliary function
 */
void _hash_multimap_init_elem_auxiliary(hash_multimap_t* phmmap_map, void* pv_elem)
{
    assert(phmmap_map != NULL);
    assert(pv_elem != NULL);
    assert(_pair_is_inited(&phmmap_map->_pair_temp) || _pair_is_created(&phmmap_map->_pair_temp));

    /* initialize new elements */
    if (phmmap_map->_t_hashtable._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(phmmap_map->_t_hashtable._t_typeinfo._s_typename, s_elemtypename);

        phmmap_map->_t_hashtable._t_typeinfo._pt_type->_t_typeinit(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = phmmap_map->_t_hashtable._t_typeinfo._pt_type->_t_typesize;
        phmmap_map->_t_hashtable._t_typeinfo._pt_type->_t_typeinit(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

