/*
 *  The implementation of map private interface.
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
#include <cstl/cmap.h>

#include "cstl_map_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create map container.
 */
map_t* _create_map(const char* s_typename)
{
    map_t* pmap_map = NULL;

    if ((pmap_map = (map_t*)malloc(sizeof(map_t))) == NULL) {
        return NULL;
    }

    if (!_create_map_auxiliary(pmap_map, s_typename)) {
        free(pmap_map);
        return NULL;
    }

    return pmap_map;
}

/**
 * Create map container auxiliary function.
 */
bool_t _create_map_auxiliary(map_t* pmap_map, const char* s_typename)
{
    char   s_typenameex[_TYPE_NAME_SIZE + 1];
    bool_t b_result = false;

    assert(pmap_map != NULL);
    assert(s_typename != NULL);

    b_result = _create_pair_auxiliary(&pmap_map->_pair_temp, s_typename);
    if (!b_result) {
        return false;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, "pair_t", _TYPE_NAME_SIZE);
    strncat(s_typenameex, "<", _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, ">", _TYPE_NAME_SIZE);

#ifdef CSTL_MAP_AVL_TREE
    b_result = _create_avl_tree_auxiliary(&pmap_map->_t_tree, s_typenameex);
#else
    b_result = _create_rb_tree_auxiliary(&pmap_map->_t_tree, s_typenameex);
#endif

    pmap_map->_bfun_keycompare = NULL;
    pmap_map->_bfun_valuecompare = NULL;

    return b_result;
}

/**
 * Destroy map container auxiliary function.
 */
void _map_destroy_auxiliary(map_t* pmap_map)
{
    assert(pmap_map != NULL);

    _pair_destroy_auxiliary(&pmap_map->_pair_temp);
#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_destroy_auxiliary(&pmap_map->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pmap_map->_t_tree);
#endif

    pmap_map->_bfun_keycompare = NULL;
    pmap_map->_bfun_valuecompare = NULL;
}

/**
 * Find specific element.
 */
map_iterator_t _map_find(const map_t* cpmap_map, ...)
{
    map_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmap_map);
    it_iter = _map_find_varg(cpmap_map, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Find specific element.
 */
map_iterator_t _map_find_varg(const map_t* cpmap_map, va_list val_elemlist)
{
    map_iterator_t it_iter;

    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

    /* get key */
    _type_get_varg_value(&((map_t*)cpmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmap_map->_pair_temp._pv_first);
    /* find key in tree */
#ifdef CSTL_MAP_AVL_TREE
    it_iter = _avl_tree_find(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#else
    it_iter = _rb_tree_find(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(it_iter) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return the number of specific elements in an map
 */
size_t _map_count(const map_t* cpmap_map, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cpmap_map);
    t_count = _map_count_varg(cpmap_map, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Return the number of specific elements in an map
 */
size_t _map_count_varg(const map_t* cpmap_map, va_list val_elemlist)
{
    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

    _type_get_varg_value(&((map_t*)cpmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmap_map->_pair_temp._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_count(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#else
    return _rb_tree_count(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#endif
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
map_iterator_t _map_lower_bound(const map_t* cpmap_map, ...)
{
    map_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmap_map);
    it_iter = _map_lower_bound_varg(cpmap_map, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
map_iterator_t _map_lower_bound_varg(const map_t* cpmap_map, va_list val_elemlist)
{
    map_iterator_t it_iter;

    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

    _type_get_varg_value(&((map_t*)cpmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmap_map->_pair_temp._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    it_iter = _avl_tree_lower_bound(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#else
    it_iter = _rb_tree_lower_bound(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(it_iter) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
map_iterator_t _map_upper_bound(const map_t* cpmap_map, ...)
{
    map_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmap_map);
    it_iter = _map_upper_bound_varg(cpmap_map, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
map_iterator_t _map_upper_bound_varg(const map_t* cpmap_map, va_list val_elemlist)
{
    map_iterator_t it_iter;

    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

    _type_get_varg_value(&((map_t*)cpmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmap_map->_pair_temp._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    it_iter = _avl_tree_upper_bound(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#else
    it_iter = _rb_tree_upper_bound(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(it_iter) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _map_equal_range(const map_t* cpmap_map, ...)
{
    range_t r_range;
    va_list val_elemlist;

    va_start(val_elemlist, cpmap_map);
    r_range = _map_equal_range_varg(cpmap_map, val_elemlist);
    va_end(val_elemlist);

    return r_range;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _map_equal_range_varg(const map_t* cpmap_map, va_list val_elemlist)
{
    range_t r_range;

    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

    _type_get_varg_value(&((map_t*)cpmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmap_map->_pair_temp._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    r_range = _avl_tree_equal_range(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#else
    r_range = _rb_tree_equal_range(&cpmap_map->_t_tree, &cpmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(r_range.it_begin) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(r_range.it_begin) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(r_range.it_begin) = _BIDIRECTIONAL_ITERATOR;
    _ITERATOR_CONTAINER(r_range.it_end) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(r_range.it_end) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(r_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return r_range;
}

/**
 * Erase an element from a map that match a specified element.
 */
size_t _map_erase(map_t* pmap_map, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, pmap_map);
    t_count = _map_erase_varg(pmap_map, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Erase an element from a map that match a specified element.
 */
size_t _map_erase_varg(map_t* pmap_map, va_list val_elemlist)
{
    assert(pmap_map != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));

    /* get key */
    _type_get_varg_value(&pmap_map->_pair_temp._t_typeinfofirst, val_elemlist, pmap_map->_pair_temp._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_erase(&pmap_map->_t_tree, &pmap_map->_pair_temp);
#else
    return _rb_tree_erase(&pmap_map->_t_tree, &pmap_map->_pair_temp);
#endif
}

/**
 * Access an element with specific index.
 */
void* _map_at(map_t* pmap_map, ...)
{
    void* pv_result = NULL;
    va_list val_elemlist;

    va_start(val_elemlist, pmap_map);
    pv_result = _map_at_varg(pmap_map, val_elemlist);
    va_end(val_elemlist);

    return pv_result;
}

/**
 * Access an element with specific index.
 */
void* _map_at_varg(map_t* pmap_map, va_list val_elemlist)
{
    map_iterator_t it_iter;
    va_list val_elemlist_copy;

    assert(pmap_map != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));

    va_copy(val_elemlist_copy, val_elemlist);
    _type_get_varg_value(&pmap_map->_pair_temp._t_typeinfofirst, val_elemlist, pmap_map->_pair_temp._pv_first);
#ifdef CSTL_MAP_AVL_TREE
    it_iter = _avl_tree_insert_unique(&pmap_map->_t_tree, &pmap_map->_pair_temp);
#else
    it_iter = _rb_tree_insert_unique(&pmap_map->_t_tree, &pmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(it_iter) = pmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    if (iterator_equal(it_iter, map_end(pmap_map))) {
        it_iter = _map_find_varg(pmap_map, val_elemlist_copy);
    }

    va_end(val_elemlist_copy);

    /* char* */
    if (strncmp(_GET_MAP_SECOND_TYPE_BASENAME(pmap_map), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return (char*)string_c_str((string_t*)((pair_t*)iterator_get_pointer(it_iter))->_pv_second);
    } else {
        return ((pair_t*)iterator_get_pointer(it_iter))->_pv_second;
    }
}

/**
 * Initialize element auxiliary function
 */
void _map_init_elem_auxiliary(map_t* pmap_map, void* pv_elem)
{
    assert(pmap_map != NULL);
    assert(pv_elem != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp) || _pair_is_created(&pmap_map->_pair_temp));

    /* initialize new elements */
    if (pmap_map->_t_tree._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(pmap_map->_t_tree._t_typeinfo._s_typename, s_elemtypename);

        pmap_map->_t_tree._t_typeinfo._pt_type->_t_typeinit(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = pmap_map->_t_tree._t_typeinfo._pt_type->_t_typesize;
        pmap_map->_t_tree._t_typeinfo._pt_type->_t_typeinit(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

