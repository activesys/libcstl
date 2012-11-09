/*
 *  The implementation of map iterator.
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
 * Create map iterator.
 */
map_iterator_t create_map_iterator(void)
{
    map_iterator_t it_iter;

#ifdef CSTL_MAP_AVL_TREE
    it_iter = _create_avl_tree_iterator();
#else
    it_iter = _create_rb_tree_iterator();
#endif

    _MAP_ITERATOR_CONTAINER_TYPE(it_iter) = _MAP_CONTAINER;
    _MAP_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Get data value referenced by iterator.
 */
void _map_iterator_get_value(map_iterator_t it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_iter) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    _avl_tree_iterator_get_value(it_iter, pv_value);
#else
    _rb_tree_iterator_get_value(it_iter, pv_value);
#endif
}

/**
 * Get data value pointer referenced by iterator.
 */
const void* _map_iterator_get_pointer(map_iterator_t it_iter)
{
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_iter) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_get_pointer(it_iter);
#else
    return _rb_tree_iterator_get_pointer(it_iter);
#endif
}

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 */
const void* _map_iterator_get_pointer_ignore_cstr(map_iterator_t it_iter)
{
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_iter) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_get_pointer_ignore_cstr(it_iter);
#else
    return _rb_tree_iterator_get_pointer_ignore_cstr(it_iter);
#endif
}

/**
 * Return iterator reference next element.
 */
map_iterator_t _map_iterator_next(map_iterator_t it_iter)
{
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_iter) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_next(it_iter);
#else
    return _rb_tree_iterator_next(it_iter);
#endif
}

/**
 * Return iterator reference previous element.
 */
map_iterator_t _map_iterator_prev(map_iterator_t it_iter)
{
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_iter) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_prev(it_iter);
#else
    return _rb_tree_iterator_prev(it_iter);
#endif
}

/**
 * Test the two map iterator are equal.
 */
bool_t _map_iterator_equal(map_iterator_t it_first, map_iterator_t it_second)
{
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_first) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_first) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_second) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_second) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_equal(it_first, it_second);
#else
    return _rb_tree_iterator_equal(it_first, it_second);
#endif
}

/**
 * Calculate distance between two iterators.
 */
int _map_iterator_distance(map_iterator_t it_first, map_iterator_t it_second)
{
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_first) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_first) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_second) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_second) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER(it_first) == _MAP_ITERATOR_CONTAINER(it_second));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_distance(it_first, it_second);
#else
    return _rb_tree_iterator_distance(it_first, it_second);
#endif
}

/**
 * Test the first iterator is before the second.
 */
bool_t _map_iterator_before(map_iterator_t it_first, map_iterator_t it_second)
{
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_first) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_first) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER_TYPE(it_second) == _MAP_CONTAINER);
    assert(_MAP_ITERATOR_ITERATOR_TYPE(it_second) == _BIDIRECTIONAL_ITERATOR);
    assert(_MAP_ITERATOR_CONTAINER(it_first) == _MAP_ITERATOR_CONTAINER(it_second));

#ifdef CSTL_MAP_AVL_TREE
    return _avl_tree_iterator_before(it_first, it_second);
#else
    return _rb_tree_iterator_before(it_first, it_second);
#endif
}

/** local function implementation section **/

/** eof **/

