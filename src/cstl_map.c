/*
 *  The implementation of map.
 *  Copyright (C)  2008 - 2013  Wangbo
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
 * Initialize map container.
 */
void map_init(map_t* pmap_map)
{
    assert(pmap_map != NULL);
    assert(_pair_is_created(&pmap_map->_pair_temp));

    /* initialize the pair */
    pair_init(&pmap_map->_pair_temp);
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
void map_init_ex(map_t* pmap_map, bfun_t bfun_keycompare)
{
    assert(pmap_map != NULL);
    assert(_pair_is_created(&pmap_map->_pair_temp));

    pair_init(&pmap_map->_pair_temp);
    pmap_map->_bfun_keycompare = bfun_keycompare;
    pmap_map->_pair_temp._bfun_mapkeycompare = bfun_keycompare;

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_init(&pmap_map->_t_tree, _map_value_compare);
#else
    _rb_tree_init(&pmap_map->_t_tree, _map_value_compare);
#endif
}

/**
 * Destroy map.
 */
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
    assert(pmap_dest != NULL);
    assert(cpmap_src != NULL);
    assert(_pair_is_created(&pmap_dest->_pair_temp));
    assert(_pair_is_inited(&cpmap_src->_pair_temp));

    /* initialize dest map with src map attribute */
    map_init(pmap_dest);
    pmap_dest->_bfun_keycompare = cpmap_src->_bfun_keycompare;
    pmap_dest->_bfun_valuecompare = cpmap_src->_bfun_valuecompare;
    pmap_dest->_pair_temp._bfun_mapkeycompare = cpmap_src->_pair_temp._bfun_mapkeycompare;
    pmap_dest->_pair_temp._bfun_mapvaluecompare = cpmap_src->_pair_temp._bfun_mapvaluecompare;

    assert(_map_same_pair_type_ex(&pmap_dest->_pair_temp, &cpmap_src->_pair_temp));
    /* insert all element from src to dest */
    if (!map_empty(cpmap_src)) {
        map_insert_range(pmap_dest, map_begin(cpmap_src), map_end(cpmap_src));
    }
}

/**
 * Initialize map container with specific range.
 */
void map_init_copy_range(map_t* pmap_dest, iterator_t it_begin, iterator_t it_end)
{
    assert(pmap_dest != NULL);
    assert(_pair_is_created(&pmap_dest->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    map_init(pmap_dest);
    map_insert_range(pmap_dest, it_begin, it_end);
}

/**
 * Initialize map container with specific array.
 */
void map_init_copy_array(map_t* pmap_dest, const void* cpv_array, size_t t_count)
{
    assert(pmap_dest != NULL);
    assert(_pair_is_created(&pmap_dest->_pair_temp));
    assert(cpv_array != NULL);

    map_init(pmap_dest);
    map_insert_array(pmap_dest, cpv_array, t_count);
}

/**
 * Initialize map container with specific range and compare function.
 */
void map_init_copy_range_ex(map_t* pmap_dest, iterator_t it_begin, iterator_t it_end, bfun_t bfun_keycompare)
{
    assert(pmap_dest != NULL);
    assert(_pair_is_created(&pmap_dest->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    map_init_ex(pmap_dest, bfun_keycompare);
    map_insert_range(pmap_dest, it_begin, it_end);
}

/**
 * Initialize map container with specific array and compare function.
 */
void map_init_copy_array_ex(
    map_t* pmap_dest, const void* cpv_array, size_t t_count, bfun_t bfun_keycompare)
{
    assert(pmap_dest != NULL);
    assert(_pair_is_created(&pmap_dest->_pair_temp));
    assert(cpv_array != NULL);

    map_init_ex(pmap_dest, bfun_keycompare);
    map_insert_array(pmap_dest, cpv_array, t_count);
}

/**
 * Assign map container.
 */
void map_assign(map_t* pmap_dest, const map_t* cpmap_src)
{
    assert(pmap_dest != NULL);
    assert(cpmap_src != NULL);
    assert(_pair_is_inited(&pmap_dest->_pair_temp));
    assert(_pair_is_inited(&cpmap_src->_pair_temp));
    assert(_map_same_pair_type_ex(&pmap_dest->_pair_temp, &cpmap_src->_pair_temp));

    /* clear */
    map_clear(pmap_dest);
    /* insert all element from src to dest */
    if (!map_empty(cpmap_src)) {
        map_insert_range(pmap_dest, map_begin(cpmap_src), map_end(cpmap_src));
    }
}

/**
 * Swap the datas of first map and second map.
 */
void map_swap(map_t* pmap_first, map_t* pmap_second)
{
    assert(pmap_first != NULL);
    assert(pmap_second != NULL);
    assert(_pair_is_inited(&pmap_first->_pair_temp));
    assert(_pair_is_inited(&pmap_second->_pair_temp));
    assert(_map_same_pair_type_ex(&pmap_first->_pair_temp, &pmap_second->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_swap(&pmap_first->_t_tree, &pmap_second->_t_tree);
#else
    _rb_tree_swap(&pmap_first->_t_tree, &pmap_second->_t_tree);
#endif
}

/**
 * Test if an map is empty.
 */
bool_t map_empty(const map_t* cpmap_map)
{
    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_empty(&cpmap_map->_t_tree);
#else
    return _rb_tree_empty(&cpmap_map->_t_tree);
#endif
}

/**
 * Get the number of elements int the map.
 */
size_t map_size(const map_t* cpmap_map)
{
    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_size(&cpmap_map->_t_tree);
#else
    return _rb_tree_size(&cpmap_map->_t_tree);
#endif
}

/**
 * Get the maximum number of elements int the map.
 */
size_t map_max_size(const map_t* cpmap_map)
{
    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_max_size(&cpmap_map->_t_tree);
#else
    return _rb_tree_max_size(&cpmap_map->_t_tree);
#endif
}

/**
 * Return the compare function of key.
 */
bfun_t map_key_comp(const map_t* cpmap_map)
{
    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

    if (cpmap_map->_bfun_keycompare != NULL) {
        return cpmap_map->_bfun_keycompare;
    } else {
        return _GET_MAP_FIRST_TYPE_LESS_FUNCTION(cpmap_map);
    }
}

/**
 * Return the compare function of value.
 */
bfun_t map_value_comp(const map_t* cpmap_map)
{
#ifdef NDEBUG
    void* pv_avoidwarning = (void*)cpmap_map;
    pv_avoidwarning = NULL;
#endif
    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

    return _map_value_compare;
}

/**
 * Erases all the elements of an map.
 */
void map_clear(map_t* pmap_map)
{
    assert(pmap_map != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_clear(&pmap_map->_t_tree);
#else
    _rb_tree_clear(&pmap_map->_t_tree);
#endif
}

/**
 * Tests if the two map are equal.
 */
bool_t map_equal(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL);
    assert(cpmap_second != NULL);
    assert(_pair_is_inited(&cpmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmap_second->_pair_temp));

    if (cpmap_first->_bfun_keycompare != cpmap_second->_bfun_keycompare) {
        return false;
    }
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

/**
 * Tests if the two map are not equal.
 */
bool_t map_not_equal(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL);
    assert(cpmap_second != NULL);
    assert(_pair_is_inited(&cpmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmap_second->_pair_temp));

    if (cpmap_first->_bfun_keycompare != cpmap_second->_bfun_keycompare) {
        return true;
    }
#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_not_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_not_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

/**
 * Tests if the first map is less than the second map.
 */
bool_t map_less(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL);
    assert(cpmap_second != NULL);
    assert(_pair_is_inited(&cpmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmap_second->_pair_temp));
    assert(_map_same_pair_type_ex(&cpmap_first->_pair_temp, &cpmap_second->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_less(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

/**
 * Tests if the first map is less than or equal to the second map.
 */
bool_t map_less_equal(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL);
    assert(cpmap_second != NULL);
    assert(_pair_is_inited(&cpmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmap_second->_pair_temp));
    assert(_map_same_pair_type_ex(&cpmap_first->_pair_temp, &cpmap_second->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_less_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_less_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

/**
 * Tests if the first map is greater than the second map.
 */
bool_t map_greater(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL);
    assert(cpmap_second != NULL);
    assert(_pair_is_inited(&cpmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmap_second->_pair_temp));
    assert(_map_same_pair_type_ex(&cpmap_first->_pair_temp, &cpmap_second->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_greater(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_greater(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

/**
 * Tests if the first map is greater than or equal to the second map.
 */
bool_t map_greater_equal(const map_t* cpmap_first, const map_t* cpmap_second)
{
    assert(cpmap_first != NULL);
    assert(cpmap_second != NULL);
    assert(_pair_is_inited(&cpmap_first->_pair_temp));
    assert(_pair_is_inited(&cpmap_second->_pair_temp));
    assert(_map_same_pair_type_ex(&cpmap_first->_pair_temp, &cpmap_second->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_greater_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#else
    return _rb_tree_greater_equal(&cpmap_first->_t_tree, &cpmap_second->_t_tree);
#endif
}

/**
 * Return an iterator that addresses the first element in the map.
 */
map_iterator_t map_begin(const map_t* cpmap_map)
{
    map_iterator_t it_begin;

    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    it_begin = _avl_tree_begin(&cpmap_map->_t_tree);
#else
    it_begin = _rb_tree_begin(&cpmap_map->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_begin) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_begin) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_begin) = _BIDIRECTIONAL_ITERATOR;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the map.
 */
map_iterator_t map_end(const map_t* cpmap_map)
{
    map_iterator_t it_end;

    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    it_end = _avl_tree_end(&cpmap_map->_t_tree);
#else
    it_end = _rb_tree_end(&cpmap_map->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_end) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_end) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_end) = _BIDIRECTIONAL_ITERATOR;

    return it_end;
}

map_reverse_iterator_t map_rbegin(const map_t* cpmap_map)
{
    map_reverse_iterator_t it_rbegin;

    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    it_rbegin = _avl_tree_rbegin(&cpmap_map->_t_tree);
#else
    it_rbegin = _rb_tree_rbegin(&cpmap_map->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_rbegin) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_rbegin) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_rbegin) = _BIDIRECTIONAL_ITERATOR;

    return it_rbegin;
}

map_reverse_iterator_t map_rend(const map_t* cpmap_map)
{
    map_reverse_iterator_t it_rend;

    assert(cpmap_map != NULL);
    assert(_pair_is_inited(&cpmap_map->_pair_temp));

#ifdef CSTL_MAP_AVL_TREE
    it_rend = _avl_tree_rend(&cpmap_map->_t_tree);
#else
    it_rend = _rb_tree_rend(&cpmap_map->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_rend) = (map_t*)cpmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_rend) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_rend) = _BIDIRECTIONAL_ITERATOR;

    return it_rend;
}

/**
 * Inserts an unique element into a map.
 */
map_iterator_t map_insert(map_t* pmap_map, const pair_t* cppair_pair)
{
    map_iterator_t it_iter;

    assert(pmap_map != NULL);
    assert(cppair_pair != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));
    assert(_pair_is_inited(cppair_pair));

    /* set key less function and value less function */
    ((pair_t*)cppair_pair)->_bfun_mapkeycompare = pmap_map->_bfun_keycompare;
    ((pair_t*)cppair_pair)->_bfun_mapvaluecompare = pmap_map->_bfun_valuecompare;

    assert(_map_same_pair_type_ex(&pmap_map->_pair_temp, cppair_pair));

    /* insert pair into tree */
#ifdef CSTL_MAP_AVL_TREE
    it_iter =  _avl_tree_insert_unique(&pmap_map->_t_tree, cppair_pair);
#else
    it_iter = _rb_tree_insert_unique(&pmap_map->_t_tree, cppair_pair);
#endif

    _ITERATOR_CONTAINER(it_iter) = pmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Inserts an unique element into a map with hint position.
 */
map_iterator_t map_insert_hint(map_t* pmap_map, map_iterator_t it_hint, const pair_t* cppair_pair)
{
    assert(pmap_map != NULL);
    assert(cppair_pair != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));
    assert(_pair_is_inited(cppair_pair));
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_hint) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_hint) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER(it_hint) == pmap_map);

    /* set key less function and value less function */
    ((pair_t*)cppair_pair)->_bfun_mapkeycompare = pmap_map->_bfun_keycompare;
    ((pair_t*)cppair_pair)->_bfun_mapvaluecompare = pmap_map->_bfun_valuecompare;

    assert(_map_same_pair_type_ex(&pmap_map->_pair_temp, cppair_pair));

#ifdef CSTL_MAP_AVL_TREE
    it_hint = _avl_tree_insert_unique(&pmap_map->_t_tree, cppair_pair);
#else
    it_hint = _rb_tree_insert_unique(&pmap_map->_t_tree, cppair_pair);
#endif

    _ITERATOR_CONTAINER(it_hint) = pmap_map;
    _MAP_ITERATOR_CONTAINER_TYPE(it_hint) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_hint) = _BIDIRECTIONAL_ITERATOR;

    return it_hint;
}

/**
 * Inserts an range of unique element into a map.
 */
void map_insert_range(map_t* pmap_map, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(pmap_map != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        assert(_map_same_pair_type(&pmap_map->_pair_temp, (pair_t*)iterator_get_pointer(it_iter)));
        map_insert(pmap_map, (pair_t*)iterator_get_pointer(it_iter));
    }
}

/**
 * Inserts an array of unique element into a map.
 */
void map_insert_array(map_t* pmap_map, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(pmap_map != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));
    assert(cpv_array != NULL);

    for (i = 0; i < t_count; ++i) {
        assert(_map_same_pair_type(&pmap_map->_pair_temp, ((pair_t**)cpv_array)[i]));
        map_insert(pmap_map, ((pair_t**)cpv_array)[i]);
    }
}

/*
 * Erase an element in an map from specificed position.
 */
void map_erase_pos(map_t* pmap_map, map_iterator_t it_pos)
{
    assert(pmap_map != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_pos) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_pos) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER(it_pos) == pmap_map);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_erase_pos(&pmap_map->_t_tree, it_pos);
#else
    _rb_tree_erase_pos(&pmap_map->_t_tree, it_pos);
#endif
}

/*
 * Erase a range of element in an map.
 */
void map_erase_range(map_t* pmap_map, map_iterator_t it_begin, map_iterator_t it_end)
{
    assert(pmap_map != NULL);
    assert(_pair_is_inited(&pmap_map->_pair_temp));
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_begin) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_end) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER(it_begin) == pmap_map && _MAP_ITERATOR_CONTAINER(it_end) == pmap_map);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_erase_range(&pmap_map->_t_tree, it_begin, it_end);
#else
    _rb_tree_erase_range(&pmap_map->_t_tree, it_begin, it_end);
#endif
}

/** local function implementation section **/

/** eof **/

