/*
 *  The implementation of set.
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
#include <cstl/cstl_iterator_private.h>

#ifdef CSTL_SET_AVL_TREE
#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#include <cstl/cstl_avl_tree.h>
#else
#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>
#endif

#include <cstl/cstl_set_iterator.h>
#include <cstl/cstl_set_private.h>
#include <cstl/cstl_set.h>

#include "cstl_set_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize set container.
 */
void set_init(set_t* pset_set)
{
    assert(pset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init(&pset_set->_t_tree, NULL);
#else
    _rb_tree_init(&pset_set->_t_tree, NULL);
#endif
}

/**
 * Initialize set container with user define compare function.
 */
void set_init_ex(set_t* pset_set, binary_function_t t_compare)
{
    assert(pset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init(&pset_set->_t_tree, t_compare);
#else
    _rb_tree_init(&pset_set->_t_tree, t_compare);
#endif
}

void set_destroy(set_t* pset_set)
{
    assert(pset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_destroy(&pset_set->_t_tree);
#else
    _rb_tree_destroy(&pset_set->_t_tree);
#endif
}

void set_init_copy(set_t* pset_dest, const set_t* cpset_src)
{
    assert(pset_dest != NULL && cpset_src != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy(&pset_dest->_t_tree, &cpset_src->_t_tree);
#else
    _rb_tree_init_copy(&pset_dest->_t_tree, &cpset_src->_t_tree);
#endif
}

void set_init_copy_range(set_t* pset_dest, set_iterator_t it_begin, set_iterator_t it_end)
{
    assert(pset_dest != NULL);
    assert(_GET_SET_CONTAINER_TYPE(it_begin) == _SET_CONTAINER &&
           _GET_SET_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_SET_CONTAINER_TYPE(it_end) == _SET_CONTAINER &&
           _GET_SET_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_SET_CONTAINER(it_begin) != pset_dest &&
           _GET_SET_CONTAINER(it_end) != pset_dest &&
           _GET_SET_CONTAINER(it_begin) == _GET_SET_CONTAINER(it_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_range(&pset_dest->_t_tree, it_begin, it_end);
#else
    _rb_tree_init_copy_range(&pset_dest->_t_tree, it_begin, it_end);
#endif
}

void set_init_copy_range_ex(
    set_t* pset_dest, set_iterator_t it_begin, set_iterator_t it_end, binary_function_t t_compare)
{
    assert(pset_dest != NULL);
    assert(_GET_SET_CONTAINER_TYPE(it_begin) == _SET_CONTAINER &&
           _GET_SET_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR &&
           _GET_SET_CONTAINER_TYPE(it_end) == _SET_CONTAINER &&
           _GET_SET_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_SET_CONTAINER(it_begin) != pset_dest &&
           _GET_SET_CONTAINER(it_end) != pset_dest &&
           _GET_SET_CONTAINER(it_begin) == _GET_SET_CONTAINER(it_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_range_ex(&pset_dest->_t_tree, it_begin, it_end, t_compare);
#else
    _rb_tree_init_copy_range_ex(&pset_dest->_t_tree, it_begin, it_end, t_compare);
#endif
}

void set_assign(set_t* pset_dest, const set_t* cpset_src)
{
    assert(pset_dest != NULL && cpset_src != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_assign(&pset_dest->_t_tree, &cpset_src->_t_tree);
#else
    _rb_tree_assign(&pset_dest->_t_tree, &cpset_src->_t_tree);
#endif
}

bool_t set_empty(const set_t* cpset_set)
{
    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_empty(&cpset_set->_t_tree);
#else
    return _rb_tree_empty(&cpset_set->_t_tree);
#endif
}

size_t set_size(const set_t* cpset_set)
{
    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_size(&cpset_set->_t_tree);
#else
    return _rb_tree_size(&cpset_set->_t_tree);
#endif
}

size_t set_max_size(const set_t* cpset_set)
{
    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_max_size(&cpset_set->_t_tree);
#else
    return _rb_tree_max_size(&cpset_set->_t_tree);
#endif
}

set_iterator_t set_begin(const set_t* cpset_set)
{
    set_iterator_t t_newiterator;

    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_begin(&cpset_set->_t_tree);
#else
    t_newiterator = _rb_tree_begin(&cpset_set->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (set_t*)cpset_set;
    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_end(const set_t* cpset_set)
{
    set_iterator_t t_newiterator;

    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_end(&cpset_set->_t_tree);
#else
    t_newiterator = _rb_tree_end(&cpset_set->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (set_t*)cpset_set;
    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_rbegin(const set_t* cpset_set)
{
    set_iterator_t t_newiterator;

    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_rbegin(&cpset_set->_t_tree);
#else
    t_newiterator = _rb_tree_rbegin(&cpset_set->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (set_t*)cpset_set;
    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

set_iterator_t set_rend(const set_t* cpset_set)
{
    set_iterator_t t_newiterator;

    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    t_newiterator = _avl_tree_rend(&cpset_set->_t_tree);
#else
    t_newiterator = _rb_tree_rend(&cpset_set->_t_tree);
#endif

    _GET_CONTAINER(t_newiterator) = (set_t*)cpset_set;
    _GET_SET_CONTAINER_TYPE(t_newiterator) = _SET_CONTAINER;
    _GET_SET_ITERATOR_TYPE(t_newiterator) = _BIDIRECTIONAL_ITERATOR;

    return t_newiterator;
}

binary_function_t set_key_comp(const set_t* cpset_set)
{
    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_key_comp(&cpset_set->_t_tree);
#else
    return _rb_tree_key_comp(&cpset_set->_t_tree);
#endif
}

binary_function_t set_value_comp(const set_t* cpset_set)
{
    return set_key_comp(cpset_set);
}

void set_clear(set_t* pset_set)
{
    assert(pset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_clear(&pset_set->_t_tree);
#else
    _rb_tree_clear(&pset_set->_t_tree);
#endif
}

bool_t set_equal(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL && cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

bool_t set_not_equal(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL && cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_not_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_not_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

bool_t set_less(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL && cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_less(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_less(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

bool_t set_less_equal(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL && cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_less_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_less_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

bool_t set_greater(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL && cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_greater(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_greater(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

bool_t set_greater_equal(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL && cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_greater_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_greater_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

void set_swap(set_t* pset_first, set_t* pset_second)
{
    assert(pset_first != NULL && pset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_swap(&pset_first->_t_tree, &pset_second->_t_tree);
#else
    _rb_tree_swap(&pset_first->_t_tree, &pset_second->_t_tree);
#endif
}

void set_insert_range(set_t* pset_set, set_iterator_t it_begin, set_iterator_t it_end)
{
    assert(pset_set != NULL);
    assert(_GET_SET_CONTAINER_TYPE(it_begin) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER_TYPE(it_end) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_SET_CONTAINER(it_begin) != pset_set && 
           _GET_SET_CONTAINER(it_end) != pset_set && 
           _GET_SET_CONTAINER(it_begin) == _GET_SET_CONTAINER(it_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_insert_unique_range(&pset_set->_t_tree, it_begin, it_end);
#else
    _rb_tree_insert_unique_range(&pset_set->_t_tree, it_begin, it_end);
#endif
}

void set_erase_pos(set_t* pset_set, set_iterator_t t_pos)
{
    assert(pset_set != NULL);
    assert(_GET_SET_CONTAINER_TYPE(t_pos) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(t_pos) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER(t_pos) == pset_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_erase_pos(&pset_set->_t_tree, t_pos);
#else
    _rb_tree_erase_pos(&pset_set->_t_tree, t_pos);
#endif
}

void set_erase_range(set_t* pset_set, set_iterator_t it_begin, set_iterator_t it_end)
{
    assert(pset_set != NULL);
    assert(_GET_SET_CONTAINER_TYPE(it_begin) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR && 
           _GET_SET_CONTAINER_TYPE(it_end) == _SET_CONTAINER && 
           _GET_SET_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_GET_SET_CONTAINER(it_begin) == pset_set && 
           _GET_SET_CONTAINER(it_end) == pset_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_erase_range(&pset_set->_t_tree, it_begin, it_end);
#else
    _rb_tree_erase_range(&pset_set->_t_tree, it_begin, it_end);
#endif
}

/** local function implementation section **/

/** eof **/

