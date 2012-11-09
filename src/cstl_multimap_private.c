/*
 *  The implementation of multimap private interface.
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

#include "cstl_multimap_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create multimap container.
 */
multimap_t* _create_multimap(const char* s_typename)
{
    multimap_t* pmmap_map = NULL;

    if ((pmmap_map = (multimap_t*)malloc(sizeof(multimap_t))) == NULL) {
        return NULL;
    }

    if (!_create_multimap_auxiliary(pmmap_map, s_typename)) {
        free(pmmap_map);
        return NULL;
    }

    return pmmap_map;
}

/**
 * Create multimap container auxiliary function.
 */
bool_t _create_multimap_auxiliary(multimap_t* pmmap_map, const char* s_typename)
{
    char   s_typenameex[_TYPE_NAME_SIZE + 1];
    bool_t b_result = false;

    assert(pmmap_map != NULL);
    assert(s_typename != NULL);

    b_result = _create_pair_auxiliary(&pmmap_map->_pair_temp, s_typename);
    if (!b_result) {
        return false;
    }

    memset(s_typenameex, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(s_typenameex, "pair_t", _TYPE_NAME_SIZE);
    strncat(s_typenameex, "<", _TYPE_NAME_SIZE);
    strncat(s_typenameex, s_typename, _TYPE_NAME_SIZE - 8); /* 8 is length of "pair_t<>" */
    strncat(s_typenameex, ">", _TYPE_NAME_SIZE);

#ifdef CSTL_MULTIMAP_AVL_TREE
    b_result = _create_avl_tree_auxiliary(&pmmap_map->_t_tree, s_typenameex);
#else
    b_result = _create_rb_tree_auxiliary(&pmmap_map->_t_tree, s_typenameex);
#endif

    pmmap_map->_bfun_keycompare = NULL;
    pmmap_map->_bfun_valuecompare = NULL;

    return b_result;
}

/**
 * Destroy multimap container auxiliary function.
 */
void _multimap_destroy_auxiliary(multimap_t* pmmap_map)
{
    assert(pmmap_map != NULL);

    _pair_destroy_auxiliary(&pmmap_map->_pair_temp);
#ifdef CSTL_MULTIMAP_AVL_TREE
    _avl_tree_destroy_auxiliary(&pmmap_map->_t_tree);
#else
    _rb_tree_destroy_auxiliary(&pmmap_map->_t_tree);
#endif

    pmmap_map->_bfun_keycompare = NULL;
    pmmap_map->_bfun_valuecompare = NULL;
}

/**
 * Find specific element.
 */
multimap_iterator_t _multimap_find(const multimap_t* cpmmap_map, ...)
{
    multimap_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmmap_map);
    it_iter = _multimap_find_varg(cpmmap_map, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Find specific element.
 */
multimap_iterator_t _multimap_find_varg(const multimap_t* cpmmap_map, va_list val_elemlist)
{
    multimap_iterator_t it_iter;

    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

    /* get key */
    _type_get_varg_value(&((multimap_t*)cpmmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmmap_map->_pair_temp._pv_first);
    /* find key in tree */
#ifdef CSTL_MULTIMAP_AVL_TREE
    it_iter = _avl_tree_find(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#else
    it_iter = _rb_tree_find(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(it_iter) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return the number of specific elements in an multimap
 */
size_t _multimap_count(const multimap_t* cpmmap_map, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, cpmmap_map);
    t_count = _multimap_count_varg(cpmmap_map, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Return the number of specific elements in an multimap
 */
size_t _multimap_count_varg(const multimap_t* cpmmap_map, va_list val_elemlist)
{
    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

    _type_get_varg_value(&((multimap_t*)cpmmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmmap_map->_pair_temp._pv_first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_count(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#else
    return _rb_tree_count(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#endif
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
multimap_iterator_t _multimap_lower_bound(const multimap_t* cpmmap_map, ...)
{
    multimap_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmmap_map);
    it_iter = _multimap_lower_bound_varg(cpmmap_map, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
multimap_iterator_t _multimap_lower_bound_varg(const multimap_t* cpmmap_map, va_list val_elemlist)
{
    multimap_iterator_t it_iter;

    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

    _type_get_varg_value(&((multimap_t*)cpmmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmmap_map->_pair_temp._pv_first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    it_iter = _avl_tree_lower_bound(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#else
    it_iter = _rb_tree_lower_bound(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(it_iter) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
multimap_iterator_t _multimap_upper_bound(const multimap_t* cpmmap_map, ...)
{
    multimap_iterator_t it_iter;
    va_list val_elemlist;

    va_start(val_elemlist, cpmmap_map);
    it_iter = _multimap_upper_bound_varg(cpmmap_map, val_elemlist);
    va_end(val_elemlist);

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
multimap_iterator_t _multimap_upper_bound_varg(const multimap_t* cpmmap_map, va_list val_elemlist)
{
    multimap_iterator_t it_iter;

    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

    _type_get_varg_value(&((multimap_t*)cpmmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmmap_map->_pair_temp._pv_first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    it_iter = _avl_tree_upper_bound(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#else
    it_iter = _rb_tree_upper_bound(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(it_iter) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _multimap_equal_range(const multimap_t* cpmmap_map, ...)
{
    range_t r_range;
    va_list val_elemlist;

    va_start(val_elemlist, cpmmap_map);
    r_range = _multimap_equal_range_varg(cpmmap_map, val_elemlist);
    va_end(val_elemlist);

    return r_range;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _multimap_equal_range_varg(const multimap_t* cpmmap_map, va_list val_elemlist)
{
    range_t r_range;

    assert(cpmmap_map != NULL);
    assert(_pair_is_inited(&cpmmap_map->_pair_temp));

    _type_get_varg_value(&((multimap_t*)cpmmap_map)->_pair_temp._t_typeinfofirst, val_elemlist, cpmmap_map->_pair_temp._pv_first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    r_range = _avl_tree_equal_range(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#else
    r_range = _rb_tree_equal_range(&cpmmap_map->_t_tree, &cpmmap_map->_pair_temp);
#endif

    _ITERATOR_CONTAINER(r_range.it_begin) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(r_range.it_begin) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(r_range.it_begin) = _BIDIRECTIONAL_ITERATOR;
    _ITERATOR_CONTAINER(r_range.it_end) = (multimap_t*)cpmmap_map;
    _MULTIMAP_ITERATOR_CONTAINER_TYPE(r_range.it_end) = _MULTIMAP_CONTAINER;
    _MULTIMAP_ITERATOR_ITERATOR_TYPE(r_range.it_end) = _BIDIRECTIONAL_ITERATOR;

    return r_range;
}

/**
 * Erase an element from a multimap that match a specified element.
 */
size_t _multimap_erase(multimap_t* pmmap_map, ...)
{
    size_t t_count = 0;
    va_list val_elemlist;

    va_start(val_elemlist, pmmap_map);
    t_count = _multimap_erase_varg(pmmap_map, val_elemlist);
    va_end(val_elemlist);

    return t_count;
}

/**
 * Erase an element from a multimap that match a specified element.
 */
size_t _multimap_erase_varg(multimap_t* pmmap_map, va_list val_elemlist)
{
    assert(pmmap_map != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp));

    /* get key */
    _type_get_varg_value(&pmmap_map->_pair_temp._t_typeinfofirst, val_elemlist, pmmap_map->_pair_temp._pv_first);
#ifdef CSTL_MULTIMAP_AVL_TREE
    return _avl_tree_erase(&pmmap_map->_t_tree, &pmmap_map->_pair_temp);
#else
    return _rb_tree_erase(&pmmap_map->_t_tree, &pmmap_map->_pair_temp);
#endif
}

/**
 * Initialize element auxiliary function
 */
void _multimap_init_elem_auxiliary(multimap_t* pmmap_map, void* pv_elem)
{
    assert(pmmap_map != NULL);
    assert(pv_elem != NULL);
    assert(_pair_is_inited(&pmmap_map->_pair_temp) || _pair_is_created(&pmmap_map->_pair_temp));

    /* initialize new elements */
    if (pmmap_map->_t_tree._t_typeinfo._t_style == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(pmmap_map->_t_tree._t_typeinfo._s_typename, s_elemtypename);

        pmmap_map->_t_tree._t_typeinfo._pt_type->_t_typeinit(pv_elem, s_elemtypename);
    } else {
        bool_t b_result = pmmap_map->_t_tree._t_typeinfo._pt_type->_t_typesize;
        pmmap_map->_t_tree._t_typeinfo._pt_type->_t_typeinit(pv_elem, &b_result);
        assert(b_result);
    }
}

/** local function implementation section **/

/** eof **/

