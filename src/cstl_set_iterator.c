/*
 *  The implementation of set iterator.
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
#include <cstl/cset.h>

#include "cstl_set_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create set iterator.
 */
set_iterator_t create_set_iterator(void)
{
    set_iterator_t it_iter;

#ifdef CSTL_SET_AVL_TREE
    it_iter = _create_avl_tree_iterator();
#else
    it_iter = _create_rb_tree_iterator();
#endif

    _SET_ITERATOR_CONTAINER_TYPE(it_iter) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_iter) = _BIDIRECTIONAL_ITERATOR;

    return it_iter;
}

/**
 * Get data value referenced by iterator.
 */
void _set_iterator_get_value(set_iterator_t it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_iter) == _SET_CONTAINER); 
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_iterator_get_value(it_iter, pv_value);
#else
    _rb_tree_iterator_get_value(it_iter, pv_value);
#endif
}

/**
 * Get data value pointer referenced by iterator.
 */
const void* _set_iterator_get_pointer(set_iterator_t it_iter)
{
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_iter) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_get_pointer(it_iter);
#else
    return _rb_tree_iterator_get_pointer(it_iter);
#endif
}

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 */
const void* _set_iterator_get_pointer_ignore_cstr(set_iterator_t it_iter)
{
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_iter) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_get_pointer_ignore_cstr(it_iter);
#else
    return _rb_tree_iterator_get_pointer_ignore_cstr(it_iter);
#endif
}

/**
 * Return iterator reference next element.
 */
set_iterator_t _set_iterator_next(set_iterator_t it_iter)
{
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_iter) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_next(it_iter);
#else
    return _rb_tree_iterator_next(it_iter);
#endif
}

/**
 * Return iterator reference previous element.
 */
set_iterator_t _set_iterator_prev(set_iterator_t it_iter)
{
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_iter) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_iter) == _BIDIRECTIONAL_ITERATOR); 

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_prev(it_iter);
#else
    return _rb_tree_iterator_prev(it_iter);
#endif
}

/**
 * Test the two set iterator are equal.
 */
bool_t _set_iterator_equal(set_iterator_t it_first, set_iterator_t it_second)
{
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_first) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_first) == _BIDIRECTIONAL_ITERATOR);
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_second) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_second) == _BIDIRECTIONAL_ITERATOR);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_equal(it_first, it_second);
#else
    return _rb_tree_iterator_equal(it_first, it_second);
#endif
}

/**
 * Calculate distance between two iterators.
 */
int _set_iterator_distance(set_iterator_t it_first, set_iterator_t it_second)
{
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_first) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_first) == _BIDIRECTIONAL_ITERATOR);
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_second) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_second) == _BIDIRECTIONAL_ITERATOR);
    assert(_SET_ITERATOR_CONTAINER(it_first) == _SET_ITERATOR_CONTAINER(it_second));

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_distance(it_first, it_second);
#else
    return _rb_tree_iterator_distance(it_first, it_second);
#endif
}

/**
 * Test the first iterator is before the second.
 */
bool_t _set_iterator_before(set_iterator_t it_first, set_iterator_t it_second)
{
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_first) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_first) == _BIDIRECTIONAL_ITERATOR);
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_second) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_second) == _BIDIRECTIONAL_ITERATOR);
    assert(_SET_ITERATOR_CONTAINER(it_first) == _SET_ITERATOR_CONTAINER(it_second));

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_iterator_before(it_first, it_second);
#else
    return _rb_tree_iterator_before(it_first, it_second);
#endif
}

/** local function implementation section **/

/** eof **/

