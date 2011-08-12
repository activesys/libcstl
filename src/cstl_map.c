/*
 *  The implementation of map.
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

#ifdef CSTL_MAP_AVL_TREE
#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#include <cstl/cstl_avl_tree.h>
#else
#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>
#endif
#include <cstl/cutility.h>
#include <cstl/cstring.h>

#include <cstl/cstl_map_iterator.h>
#include <cstl/cstl_map_private.h>
#include <cstl/cstl_map.h>

#include "cstl_map_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize map container.
 */
void map_init(map_t* pmap_map)
{
    assert(pmap_map != NULL);
    assert(_pair_is_created(&pmap_map->_t_pair));

    /* initialize the pair */
    pair_init(&pmap_map->_t_pair);
    /* initialize the tree */
#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_init(&pmap_map->_t_tree, _map_value_compare);
#else
    _rb_tree_init(&pmap_map->_t_tree, _map_value_compare);
#endif
}

/**
 * Initialize map container with user define compare function.
 */
void map_init_ex(map_t* pmap_map, binary_function_t t_keycompare)
{
    assert(pmap_map != NULL);
    assert(_pair_is_created(&pmap_map->_t_pair));

    pair_init(&pmap_map->_t_pair);
    pmap_map->_t_keycompare = t_keycompare;
    pmap_map->_t_pair._t_mapkeycompare = t_keycompare;

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_init(&pmap_map->_t_tree, _map_value_compare);
#else
    _rb_tree_init(&pmap_map->_t_tree, _map_value_compare);
#endif
}

void map_destroy(map_t* pmap_map)
{
    _map_destroy_auxiliary(pmap_map);
    free(pmap_map);
}

/**
 * Initialize map container with map.
 */
void map_init_copy(map_t* pmap_dest, const map_t* cpmap_src)
{
    assert(pmap_dest != NULL && cpmap_src != NULL);

    /* initialize dest map with src map attribute */
    map_init(pmap_dest);
    pmap_dest->_t_keycompare = cpmap_src->_t_keycompare;
    pmap_dest->_t_valuecompare = cpmap_src->_t_valuecompare;
    pmap_dest->_t_pair._t_mapkeycompare = cpmap_src->_t_pair._t_mapkeycompare;
    pmap_dest->_t_pair._t_mapvaluecompare = cpmap_src->_t_pair._t_mapvaluecompare;

    assert(_map_same_pair_type(&pmap_dest->_t_pair, &cpmap_src->_t_pair));
    /* insert all element from src to dest */
    if(!map_empty(cpmap_src))
    {
        map_insert_range(pmap_dest, map_begin(cpmap_src), map_end(cpmap_src));
    }
}

/**
 * Initialize map container with specific range.
 */
void map_init_copy_range(map_t* pmap_dest, map_iterator_t t_begin, map_iterator_t t_end)
{
    assert(pmap_dest != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pmap_dest &&
           _GET_MAP_CONTAINER(t_end) != pmap_dest &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    /* initialize dest map with src map attribute */
    map_init(pmap_dest);
    /* insert all element from src to dest */
    if(!map_empty(_GET_MAP_CONTAINER(t_begin)))
    {
        map_insert_range(pmap_dest, t_begin, t_end);
    }
}

/**
 * Initialize map container with specific range and compare function.
 */
void map_init_copy_range_ex(map_t* pmap_dest, map_iterator_t t_begin, map_iterator_t t_end, binary_function_t t_keycompare)
{
    assert(pmap_dest != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pmap_dest &&
           _GET_MAP_CONTAINER(t_end) != pmap_dest &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    /* initialize dest map with src map attribute */
    map_init_ex(pmap_dest, t_keycompare);
    /* insert all element from src to dest */
    if(!map_empty(_GET_MAP_CONTAINER(t_begin)))
    {
        map_insert_range(pmap_dest, t_begin, t_end);
    }
}

void map_assign(map_t* pmap_dest, const map_t* cpmap_src)
{
    assert(pmap_dest != NULL && cpmap_src != NULL);
    assert(_map_same_pair_type(&pmap_dest->_t_pair, &cpmap_src->_t_pair));

    /* clear */
    map_clear(pmap_dest);
    /* insert all element from src to dest */
    if(!map_empty(cpmap_src))
    {
        map_insert_range(pmap_dest, map_begin(cpmap_src), map_end(cpmap_src));
    }
}

void map_swap(map_t* pmap_first, map_t* pmap_second)
{
    assert(pmap_first != NULL && pmap_second != NULL);
    assert(_map_same_pair_type(&pmap_first->_t_pair, &pmap_second->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_swap(&pmap_first->_t_tree, &pmap_second->_t_tree);
#else
    _rb_tree_swap(&pmap_first->_t_tree, &pmap_second->_t_tree);
#endif
}

bool_t map_empty(const map_t* cpmap_map)
{
    assert(cpmap_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_empty(&cpmap_map->_t_tree);
#else
    return _rb_tree_empty(&cpmap_map->_t_tree);
#endif
}

size_t map_size(const map_t* cpmap_map)
{
    assert(cpmap_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_size(&cpmap_map->_t_tree);
#else
    return _rb_tree_size(&cpmap_map->_t_tree);
#endif
}

size_t map_max_size(const map_t* cpmap_map)
{
    assert(cpmap_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_max_size(&cpmap_map->_t_tree);
#else
    return _rb_tree_max_size(&cpmap_map->_t_tree);
#endif
}

binary_function_t map_key_comp(const map_t* cpmap_map)
{
    assert(cpmap_map != NULL);

    if(cpmap_map->_t_keycompare != NULL)
    {
        return cpmap_map->_t_keycompare;
    }
    else
    {
        return _GET_MAP_FIRST_TYPE_LESS_FUNCTION(cpmap_map);
    }
}

binary_function_t map_value_comp(const map_t* cpmap_map)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cpmap_map;
    pv_avoidwarning = NULL;
#endif
    assert(cpmap_map != NULL);

    return _map_value_compare;
}

void map_clear(map_t* pmap_map)
{
    assert(pmap_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_clear(&pmap_map->_t_tree);
#else
    _rb_tree_clear(&pmap_map->_t_tree);
#endif
}

bool_t map_equal(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL && cpmap_second != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

bool_t map_not_equal(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL && cpmap_second != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_not_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_not_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

bool_t map_less(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL && cpmap_second != NULL);
    assert(_map_same_pair_type(&cpmap_first->_t_pair, &cpmap_second->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_less(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

bool_t map_less_equal(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL && cpmap_second != NULL);
    assert(_map_same_pair_type(&cpmap_first->_t_pair, &cpmap_second->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_less_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

bool_t map_greater(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL && cpmap_second != NULL);
    assert(_map_same_pair_type(&cpmap_first->_t_pair, &cpmap_second->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_greater(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_greater(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

bool_t map_greater_equal(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL && cpmap_second != NULL);
    assert(_map_same_pair_type(&cpmap_first->_t_pair, &cpmap_second->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_greater_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_greater_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

map_iterator_t map_begin(const map_t* cpmap_map)
{
    map_iterator_t t_newiterator;

    assert(cpmap_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_begin(&cpmap_map->_t_tree);
#else
    t_newiterator = _rb_tree_begin(&cpmap_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpmap_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_iterator_t map_end(const map_t* cpmap_map)
{
    map_iterator_t t_newiterator;

    assert(cpmap_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_end(&cpmap_map->_t_tree);
#else
    t_newiterator = _rb_tree_end(&cpmap_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpmap_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_reverse_iterator_t map_rbegin(const map_t* cpmap_map)
{
    map_reverse_iterator_t t_newiterator;

    assert(cpmap_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_rbegin(&cpmap_map->_t_tree);
#else
    t_newiterator = _rb_tree_rbegin(&cpmap_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpmap_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_reverse_iterator_t map_rend(const map_t* cpmap_map)
{
    map_reverse_iterator_t t_newiterator;

    assert(cpmap_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_rend(&cpmap_map->_t_tree);
#else
    t_newiterator = _rb_tree_rend(&cpmap_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpmap_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_iterator_t map_insert(map_t* pmap_map, const pair_t* cpt_pair)
{
    map_iterator_t t_iter;

    assert(pmap_map != NULL && cpt_pair != NULL);

    /* set key less function and value less function */
    ((pair_t*)cpt_pair)->_t_mapkeycompare = pmap_map->_t_keycompare;
    ((pair_t*)cpt_pair)->_t_mapvaluecompare = pmap_map->_t_valuecompare;

    assert(_map_same_pair_type(&pmap_map->_t_pair, cpt_pair));

    /* insert pair into tree */
#ifdef CSTL_MAP_AVL_TREE
    t_iter =  _avl_tree_insert_unique(&pmap_map->_t_tree, cpt_pair);
#else
    t_iter = _rb_tree_insert_unique(&pmap_map->_t_tree, cpt_pair);
#endif

    _GET_CONTAINER(t_iter) = pmap_map;
    _GET_MAP_CONTAINER_TYPE(t_iter) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

map_iterator_t map_insert_hint(map_t* pmap_map, map_iterator_t t_hint, const pair_t* cpt_pair)
{
    assert(pmap_map != NULL && cpt_pair != NULL);

    /* set key less function and value less function */
    ((pair_t*)cpt_pair)->_t_mapkeycompare = pmap_map->_t_keycompare;
    ((pair_t*)cpt_pair)->_t_mapvaluecompare = pmap_map->_t_valuecompare;

    assert(_map_same_pair_type(&pmap_map->_t_pair, cpt_pair));

#ifdef CSTL_MAP_AVL_TREE
    t_hint = _avl_tree_insert_unique(&pmap_map->_t_tree, cpt_pair);
#else
    t_hint = _rb_tree_insert_unique(&pmap_map->_t_tree, cpt_pair);
#endif

    _GET_CONTAINER(t_hint) = pmap_map;
    _GET_MAP_CONTAINER_TYPE(t_hint) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

void map_insert_range(map_t* pmap_map, map_iterator_t t_begin, map_iterator_t t_end)
{
    map_iterator_t t_iterator;

    assert(pmap_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pmap_map &&
           _GET_MAP_CONTAINER(t_end) != pmap_map &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    for(t_iterator = t_begin;
        !iterator_equal(t_iterator, t_end);
        t_iterator = iterator_next(t_iterator))
    {
        map_insert(pmap_map, (pair_t*)iterator_get_pointer(t_iterator));
    }
}

void map_erase_pos(map_t* pmap_map, map_iterator_t t_pos)
{
    assert(pmap_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_pos) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER(t_pos) == pmap_map);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_erase_pos(&pmap_map->_t_tree, t_pos);
#else
    _rb_tree_erase_pos(&pmap_map->_t_tree, t_pos);
#endif
}

void map_erase_range(map_t* pmap_map, map_iterator_t t_begin, map_iterator_t t_end)
{
    assert(pmap_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) == pmap_map && _GET_MAP_CONTAINER(t_end) == pmap_map);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_erase_range(&pmap_map->_t_tree, t_begin, t_end);
#else
    _rb_tree_erase_range(&pmap_map->_t_tree, t_begin, t_end);
#endif
}

/** local function implementation section **/

/** eof **/

