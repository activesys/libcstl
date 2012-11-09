/*
 *  The implementation of hash_map private interface.
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

#include "cstl_hash_map_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create hash_map container.
 */
hash_map_t* _create_hash_map(const char* s_typename)
{
    hash_map_t* phmap_map = NULL;

    if ((phmap_map = (hash_map_t*)malloc(sizeof(hash_map_t))) == NULL) {
        return NULL;
    }

    if (!_create_hash_map_auxiliary(phmap_map, s_typename)) {
        free(phmap_map);
        return NULL;
    }

    return phmap_map;
}

/**
 * Create hash_map container auxiliary function.
 */
bool_t _create_hash_map_auxiliary(hash_map_t* phmap_map, const char* s_typename)
{
    char s_typenameex[_TYPE_NAME_SIZE + 1];

    assert(phmap_map != NULL);
    assert(s_typename != NULL);

    if (!_create_pair_auxiliary(&phmap_map->_pair_temp, s_typename)) {
        return false;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, "pair_t", _TYPE_NAME_SIZE);
    strncat(s_typenameex, "<", _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, ">", _TYPE_NAME_SIZE);

    phmap_map->_bfun_keycompare = NULL;
    phmap_map->_bfun_valuecompare = NULL;

    return _create_hashtable_auxiliary(&phmap_map->_t_hashtable, s_typenameex);
}

/**
 * Destroy hash_map container auxiliary function.
 */
void _hash_map_destroy_auxiliary(hash_map_t* phmap_map)
{
    assert(phmap_map != NULL);

    _pair_destroy_auxiliary(&phmap_map->_pair_temp);
    _hashtable_destroy_auxiliary(&phmap_map->_t_hashtable);

    phmap_map->_bfun_keycompare = NULL;
    phmap_map->_bfun_valuecompare = NULL;
}

/**
 * Find specific element.
 */
hash_map_iterator_t _hash_map_find(const hash_map_t* cphmap_map, ...)
{
    hash_map_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cphmap_map);
    it_iter = _hash_map_find_varg(cphmap_map, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Find specific element.
 */
hash_map_iterator_t _hash_map_find_varg(const hash_map_t* cphmap_map, va_list val_elemlist)
{
    hash_map_iterator_t it_iter;

    assert(cphmap_map != NULL);

    _type_get_varg_value(&((hash_map_t*)cphmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cphmap_map->_pair_temp._pv_first);

    it_iter = _hashtable_find(&cphmap_map->_t_hashtable, &cphmap_map->_pair_temp);

    _ITERATOR_CONTAINER(it_iter) = (hash_map_t*)cphmap_map;
    _HASH_MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_MAP_CONTAINER;
    _HASH_MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return the number of specific elements in an hash_map
 */
size_t _hash_map_count(const hash_map_t* cphmap_map, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cphmap_map);
    t_count = _hash_map_count_varg(cphmap_map, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Return the number of specific elements in an hash_map
 */
size_t _hash_map_count_varg(const hash_map_t* cphmap_map, va_list val_elemlist)
{
    assert(cphmap_map != NULL);

    _type_get_varg_value(&((hash_map_t*)cphmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cphmap_map->_pair_temp._pv_first);

    return _hashtable_count(&cphmap_map->_t_hashtable, &cphmap_map->_pair_temp);
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hash_map_equal_range(const hash_map_t* cphmap_map, ...)
{
    range_t r_range;
    va_list val_elemlist;

    va_start(val_elemlist, cphmap_map);
    r_range = _hash_map_equal_range_varg(cphmap_map, val_elemlist);
    va_end(val_elemlist);

    return r_range;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _hash_map_equal_range_varg(const hash_map_t* cphmap_map, va_list val_elemlist)
{
    range_t r_range;

    assert(cphmap_map != NULL);

    _type_get_varg_value(&((hash_map_t*)cphmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cphmap_map->_pair_temp._pv_first);

    r_range = _hashtable_equal_range(&cphmap_map->_t_hashtable, &cphmap_map->_pair_temp);

    _ITERATOR_CONTAINER(r_range.it_begin) = (hash_map_t*)cphmap_map;
    _HASH_MAP_ITERATOR_CONTAINER_TYPE(r_range.it_begin) = _HASH_MAP_CONTAINER;
    _HASH_MAP_ITERATOR_ITERATOR_TYPE(r_range.it_begin) = _BIDIRECTIONAL_ITERATOR;

    _ITERATOR_CONTAINER(r_range.it_end) = (hash_map_t*)cphmap_map;
    _HASH_MAP_ITERATOR_CONTAINER_TYPE(r_range.it_end) = _HASH_MAP_CONTAINER;
    _HASH_MAP_ITERATOR_ITERATOR_TYPE(r_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return r_range;
}

/**
 * Erase an element from a hash_map that match a specified element.
 */
size_t _hash_map_erase(hash_map_t* phmap_map, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, phmap_map);
    t_count = _hash_map_erase_varg(phmap_map, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Erase an element from a hash_map that match a specified element.
 */
size_t _hash_map_erase_varg(hash_map_t* phmap_map, va_list val_elemlist)
{
    assert(phmap_map != NULL);

    _type_get_varg_value(&phmap_map->_pair_temp._t_typeinfofirst, val_elemlist, phmap_map->_pair_temp._pv_first);

    return _hashtable_erase(&phmap_map->_t_hashtable, &phmap_map->_pair_temp);
}

/**
 * Access an element with specific index.
 */
void* _hash_map_at(hash_map_t* phmap_map, ...)
{
    void* pv_result = NULL;
    va_list val_elemlist;

    va_start(val_elemlist, phmap_map);
    pv_result = _hash_map_at_varg(phmap_map, val_elemlist);
    va_end(val_elemlist);

    return pv_result;
}

/**
 * Access an element with specific index.
 */
void* _hash_map_at_varg(hash_map_t* phmap_map, va_list val_elemlist)
{
    hash_map_iterator_t it_iter;
    va_list val_elemlist_copy;

    assert(phmap_map != NULL);

    va_copy(val_elemlist_copy, val_elemlist);
    _type_get_varg_value(&phmap_map->_pair_temp._t_typeinfofirst, val_elemlist, phmap_map->_pair_temp._pv_first);

    it_iter = _hashtable_insert_unique(&phmap_map->_t_hashtable, &phmap_map->_pair_temp);
    _ITERATOR_CONTAINER(it_iter) = phmap_map;
    _HASH_MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _HASH_MAP_CONTAINER;
    _HASH_MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    if (iterator_equal(it_iter, hash_map_end(phmap_map))) {
        it_iter = _hash_map_find_varg(phmap_map, val_elemlist_copy);
    }

    va_end(val_elemlist_copy);

    /* char* */
    if (strncmp(_GET_HASH_MAP_SECOND_TYPE_BASENAME(phmap_map), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return (char*)string_c_str((string_t*)((pair_t*)iterator_get_pointer(it_iter))->_pv_second);
    } else {
        return ((pair_t*)iterator_get_pointer(it_iter))->_pv_second;
    }
}

/**
 * Initialize element auxiliary function
 */
void _hash_map_init_elem_auxiliary(hash_map_t* phmap_map, void* pv_elem)
{
    assert(phmap_map != NULL);
    assert(pv_elem != NULL);
    assert(_pair_is_inited(&phmap_map->_pair_temp) || _pair_is_created(&phmap_map->_pair_temp));

    /* initialize new elements */
    if (phmap_map->_t_hashtable._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(phmap_map->_t_hashtable._t_typeinfo._s_typename, s_elemtypename);

        phmap_map->_t_hashtable._t_typeinfo._pt_type->_t_typeinit(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = phmap_map->_t_hashtable._t_typeinfo._pt_type->_t_typesize;
        phmap_map->_t_hashtable._t_typeinfo._pt_type->_t_typeinit(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

