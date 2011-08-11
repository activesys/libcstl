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
/* map function */
void map_init(map_t* pt_map)
{
    assert(pt_map != NULL);

    /* initialize the pair */
    pair_init(&pt_map->_t_pair);
    /* initialize the tree */
#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_init(&pt_map->_t_tree, _map_value_compare);
#else
    _rb_tree_init(&pt_map->_t_tree, _map_value_compare);
#endif
}

void map_init_ex(map_t* pt_map, binary_function_t t_keycompare)
{
    assert(pt_map != NULL);

    pt_map->_t_keycompare = t_keycompare;
    pt_map->_t_pair._t_mapkeycompare = t_keycompare;

    pair_init(&pt_map->_t_pair);
#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_init(&pt_map->_t_tree, _map_value_compare);
#else
    _rb_tree_init(&pt_map->_t_tree, _map_value_compare);
#endif
}

void map_destroy(map_t* pt_map)
{
    _map_destroy_auxiliary(pt_map);
    free(pt_map);
}

void map_init_copy(map_t* pt_mapdest, const map_t* cpt_mapsrc)
{
    assert(pt_mapdest != NULL && cpt_mapsrc != NULL);

    /* initialize dest map with src map attribute */
    map_init(pt_mapdest);
    pt_mapdest->_t_keycompare = cpt_mapsrc->_t_keycompare;
    pt_mapdest->_t_valuecompare = cpt_mapsrc->_t_valuecompare;
    pt_mapdest->_t_pair._t_mapkeycompare = cpt_mapsrc->_t_pair._t_mapkeycompare;
    pt_mapdest->_t_pair._t_mapvaluecompare = cpt_mapsrc->_t_pair._t_mapvaluecompare;

    assert(_map_same_pair_type(&pt_mapdest->_t_pair, &cpt_mapsrc->_t_pair));
    /* insert all element from src to dest */
    if(!map_empty(cpt_mapsrc))
    {
        map_insert_range(pt_mapdest, map_begin(cpt_mapsrc), map_end(cpt_mapsrc));
    }
}

void map_init_copy_range(map_t* pt_mapdest, map_iterator_t t_begin, map_iterator_t t_end)
{
    assert(pt_mapdest != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_end) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    /* initialize dest map with src map attribute */
    map_init(pt_mapdest);
    /* insert all element from src to dest */
    if(!map_empty(_GET_MAP_CONTAINER(t_begin)))
    {
        map_insert_range(pt_mapdest, t_begin, t_end);
    }
}

void map_init_copy_range_ex(map_t* pt_mapdest,
    map_iterator_t t_begin, map_iterator_t t_end, binary_function_t t_keycompare)
{
    assert(pt_mapdest != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_end) != pt_mapdest &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    /* initialize dest map with src map attribute */
    map_init_ex(pt_mapdest, t_keycompare);
    /* insert all element from src to dest */
    if(!map_empty(_GET_MAP_CONTAINER(t_begin)))
    {
        map_insert_range(pt_mapdest, t_begin, t_end);
    }
}

void map_assign(map_t* pt_mapdest, const map_t* cpt_mapsrc)
{
    assert(pt_mapdest != NULL && cpt_mapsrc != NULL);
    assert(_map_same_pair_type(&pt_mapdest->_t_pair, &cpt_mapsrc->_t_pair));

    /* clear */
    map_clear(pt_mapdest);
    /* insert all element from src to dest */
    if(!map_empty(cpt_mapsrc))
    {
        map_insert_range(pt_mapdest, map_begin(cpt_mapsrc), map_end(cpt_mapsrc));
    }
}

void map_swap(map_t* pt_mapfirst, map_t* pt_mapsecond)
{
    assert(pt_mapfirst != NULL && pt_mapsecond != NULL);
    assert(_map_same_pair_type(&pt_mapfirst->_t_pair, &pt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_swap(&pt_mapfirst->_t_tree, &pt_mapsecond->_t_tree);
#else
    _rb_tree_swap(&pt_mapfirst->_t_tree, &pt_mapsecond->_t_tree);
#endif
}

bool_t map_empty(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_empty(&cpt_map->_t_tree);
#else
    return _rb_tree_empty(&cpt_map->_t_tree);
#endif
}

size_t map_size(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_size(&cpt_map->_t_tree);
#else
    return _rb_tree_size(&cpt_map->_t_tree);
#endif
}

size_t map_max_size(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_max_size(&cpt_map->_t_tree);
#else
    return _rb_tree_max_size(&cpt_map->_t_tree);
#endif
}

binary_function_t map_key_comp(const map_t* cpt_map)
{
    assert(cpt_map != NULL);

    if(cpt_map->_t_keycompare != NULL)
    {
        return cpt_map->_t_keycompare;
    }
    else
    {
        return _GET_MAP_FIRST_TYPE_LESS_FUNCTION(cpt_map);
    }
}

binary_function_t map_value_comp(const map_t* cpt_map)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cpt_map;
    pv_avoidwarning = NULL;
#endif
    assert(cpt_map != NULL);

    return _map_value_compare;
}

void map_clear(map_t* pt_map)
{
    assert(pt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_clear(&pt_map->_t_tree);
#else
    _rb_tree_clear(&pt_map->_t_tree);
#endif
}

bool_t map_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_not_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_not_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_not_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_less(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_map_same_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_less(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_less_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_map_same_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_less_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_greater(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_map_same_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_greater(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_greater(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

bool_t map_greater_equal(const map_t* cpt_mapfirst, const map_t* cpt_mapsecond)
{
    assert(cpt_mapfirst != NULL && cpt_mapsecond != NULL);
    assert(_map_same_pair_type(&cpt_mapfirst->_t_pair, &cpt_mapsecond->_t_pair));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_greater_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#else
    return _rb_tree_greater_equal(&cpt_mapfirst->_t_tree, &cpt_mapsecond->_t_tree);
#endif
}

map_iterator_t map_begin(const map_t* cpt_map)
{
    map_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_begin(&cpt_map->_t_tree);
#else
    t_newiterator = _rb_tree_begin(&cpt_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_iterator_t map_end(const map_t* cpt_map)
{
    map_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_end(&cpt_map->_t_tree);
#else
    t_newiterator = _rb_tree_end(&cpt_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_reverse_iterator_t map_rbegin(const map_t* cpt_map)
{
    map_reverse_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_rbegin(&cpt_map->_t_tree);
#else
    t_newiterator = _rb_tree_rbegin(&cpt_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_reverse_iterator_t map_rend(const map_t* cpt_map)
{
    map_reverse_iterator_t t_newiterator;

    assert(cpt_map != NULL);

#ifdef CSTL_MAP_AVL_TREE
    t_newiterator = _avl_tree_rend(&cpt_map->_t_tree);
#else
    t_newiterator = _rb_tree_rend(&cpt_map->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (map_t*)cpt_map;
    _GET_MAP_CONTAINER_TYPE(t_newiterator) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

map_iterator_t map_insert(map_t* pt_map, const pair_t* cpt_pair)
{
    map_iterator_t t_iter;

    assert(pt_map != NULL && cpt_pair != NULL);

    /* set key less function and value less function */
    ((pair_t*)cpt_pair)->_t_mapkeycompare = pt_map->_t_keycompare;
    ((pair_t*)cpt_pair)->_t_mapvaluecompare = pt_map->_t_valuecompare;

    assert(_map_same_pair_type(&pt_map->_t_pair, cpt_pair));

    /* insert pair into tree */
#ifdef CSTL_MAP_AVL_TREE
    t_iter =  _avl_tree_insert_unique(&pt_map->_t_tree, cpt_pair);
#else
    t_iter = _rb_tree_insert_unique(&pt_map->_t_tree, cpt_pair);
#endif

    _GET_CONTAINER(t_iter) = pt_map;
    _GET_MAP_CONTAINER_TYPE(t_iter) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_iter) = _BIDIRECTIONAL_ITERATOR;

    return t_iter;
}

map_iterator_t map_insert_hint(map_t* pt_map, map_iterator_t t_hint, const pair_t* cpt_pair)
{
    assert(pt_map != NULL && cpt_pair != NULL);

    /* set key less function and value less function */
    ((pair_t*)cpt_pair)->_t_mapkeycompare = pt_map->_t_keycompare;
    ((pair_t*)cpt_pair)->_t_mapvaluecompare = pt_map->_t_valuecompare;

    assert(_map_same_pair_type(&pt_map->_t_pair, cpt_pair));

#ifdef CSTL_MAP_AVL_TREE
    t_hint = _avl_tree_insert_unique(&pt_map->_t_tree, cpt_pair);
#else
    t_hint = _rb_tree_insert_unique(&pt_map->_t_tree, cpt_pair);
#endif

    _GET_CONTAINER(t_hint) = pt_map;
    _GET_MAP_CONTAINER_TYPE(t_hint) = _MAP_CONTAINER;
    _GET_MAP_ITERATOR_TYPE(t_hint) = _BIDIRECTIONAL_ITERATOR;

    return t_hint;
}

void map_insert_range(map_t* pt_map, map_iterator_t t_begin, map_iterator_t t_end)
{
    map_iterator_t t_iterator;

    assert(pt_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) != pt_map &&
           _GET_MAP_CONTAINER(t_end) != pt_map &&
           _GET_MAP_CONTAINER(t_begin) == _GET_MAP_CONTAINER(t_end));

    for(t_iterator = t_begin;
        !iterator_equal(t_iterator, t_end);
        t_iterator = iterator_next(t_iterator))
    {
        map_insert(pt_map, (pair_t*)iterator_get_pointer(t_iterator));
    }
}

void map_erase_pos(map_t* pt_map, map_iterator_t t_pos)
{
    assert(pt_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_pos) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER(t_pos) == pt_map);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_erase_pos(&pt_map->_t_tree, t_pos);
#else
    _rb_tree_erase_pos(&pt_map->_t_tree, t_pos);
#endif
}

void map_erase_range(map_t* pt_map, map_iterator_t t_begin, map_iterator_t t_end)
{
    assert(pt_map != NULL);
    assert(_GET_MAP_CONTAINER_TYPE(t_begin) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_MAP_CONTAINER_TYPE(t_end) == _MAP_CONTAINER &&
           _GET_MAP_ITERATOR_TYPE(t_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_MAP_CONTAINER(t_begin) == pt_map && _GET_MAP_CONTAINER(t_end) == pt_map);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_erase_range(&pt_map->_t_tree, t_begin, t_end);
#else
    _rb_tree_erase_range(&pt_map->_t_tree, t_begin, t_end);
#endif
}

/** local function implementation section **/

/** eof **/

