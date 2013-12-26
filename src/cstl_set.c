/*
 *  The implementation of set.
 *  Copyright (C)  2008 - 2014  Wangbo
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
void set_init_ex(set_t* pset_set, bfun_t bfun_compare)
{
    assert(pset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init(&pset_set->_t_tree, bfun_compare);
#else
    _rb_tree_init(&pset_set->_t_tree, bfun_compare);
#endif
}

/**
 * Destroy set.
 */
void set_destroy(set_t* pset_set)
{
    assert(pset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_destroy(&pset_set->_t_tree);
#else
    _rb_tree_destroy(&pset_set->_t_tree);
#endif
}

/**
 * Initialize set container with set.
 */
void set_init_copy(set_t* pset_dest, const set_t* cpset_src)
{
    assert(pset_dest != NULL);
    assert(cpset_src != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy(&pset_dest->_t_tree, &cpset_src->_t_tree);
#else
    _rb_tree_init_copy(&pset_dest->_t_tree, &cpset_src->_t_tree);
#endif
}

/**
 * Initialize set container with specific range.
 */
void set_init_copy_range(set_t* pset_dest, iterator_t it_begin, iterator_t it_end)
{
    assert(pset_dest != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_unique_range(&pset_dest->_t_tree, it_begin, it_end);
#else
    _rb_tree_init_copy_unique_range(&pset_dest->_t_tree, it_begin, it_end);
#endif
}

/**
 * Initialize set container with specific array.
 */
void set_init_copy_array(set_t* pset_dest, const void* cpv_array, size_t t_count)
{
    assert(pset_dest != NULL);
    assert(cpv_array != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_unique_array(&pset_dest->_t_tree, cpv_array, t_count);
#else
    _rb_tree_init_copy_unique_array(&pset_dest->_t_tree, cpv_array, t_count);
#endif
}

/**
 * Initialize set container with specific range and compare function.
 */
void set_init_copy_range_ex(
    set_t* pset_dest, iterator_t it_begin, iterator_t it_end, bfun_t bfun_compare)
{
    assert(pset_dest != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_unique_range_ex(&pset_dest->_t_tree, it_begin, it_end, bfun_compare);
#else
    _rb_tree_init_copy_unique_range_ex(&pset_dest->_t_tree, it_begin, it_end, bfun_compare);
#endif
}

/**
 * Initialize set container with specific array and compare function.
 */
void set_init_copy_array_ex(
    set_t* pset_dest, const void* cpv_array, size_t t_count, bfun_t bfun_compare)
{
    assert(pset_dest != NULL);
    assert(cpv_array != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_init_copy_unique_array_ex(&pset_dest->_t_tree, cpv_array, t_count, bfun_compare);
#else
    _rb_tree_init_copy_unique_array_ex(&pset_dest->_t_tree, cpv_array, t_count, bfun_compare);
#endif
}

/**
 * Assign set container.
 */
void set_assign(set_t* pset_dest, const set_t* cpset_src)
{
    assert(pset_dest != NULL);
    assert(cpset_src != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_assign(&pset_dest->_t_tree, &cpset_src->_t_tree);
#else
    _rb_tree_assign(&pset_dest->_t_tree, &cpset_src->_t_tree);
#endif
}

/**
 * Test if an set is empty.
 */
bool_t set_empty(const set_t* cpset_set)
{
    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_empty(&cpset_set->_t_tree);
#else
    return _rb_tree_empty(&cpset_set->_t_tree);
#endif
}

/**
 * Get the number of elements int the set.
 */
size_t set_size(const set_t* cpset_set)
{
    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_size(&cpset_set->_t_tree);
#else
    return _rb_tree_size(&cpset_set->_t_tree);
#endif
}

/**
 * Get the maximum number of elements int the set.
 */
size_t set_max_size(const set_t* cpset_set)
{
    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_max_size(&cpset_set->_t_tree);
#else
    return _rb_tree_max_size(&cpset_set->_t_tree);
#endif
}

/**
 * Return an iterator that addresses the first element in the set.
 */
set_iterator_t set_begin(const set_t* cpset_set)
{
    set_iterator_t it_begin;

    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    it_begin = _avl_tree_begin(&cpset_set->_t_tree);
#else
    it_begin = _rb_tree_begin(&cpset_set->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_begin) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_begin) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_begin) = _BIDIRECTIONAL_ITERATOR;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the set.
 */
set_iterator_t set_end(const set_t* cpset_set)
{
    set_iterator_t it_end;

    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    it_end = _avl_tree_end(&cpset_set->_t_tree);
#else
    it_end = _rb_tree_end(&cpset_set->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_end) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_end) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_end) = _BIDIRECTIONAL_ITERATOR;

    return it_end;
}

set_iterator_t set_rbegin(const set_t* cpset_set)
{
    set_iterator_t it_rbegin;

    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    it_rbegin = _avl_tree_rbegin(&cpset_set->_t_tree);
#else
    it_rbegin = _rb_tree_rbegin(&cpset_set->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_rbegin) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_rbegin) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_rbegin) = _BIDIRECTIONAL_ITERATOR;

    return it_rbegin;
}

set_iterator_t set_rend(const set_t* cpset_set)
{
    set_iterator_t it_rend;

    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    it_rend = _avl_tree_rend(&cpset_set->_t_tree);
#else
    it_rend = _rb_tree_rend(&cpset_set->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_rend) = (set_t*)cpset_set;
    _SET_ITERATOR_CONTAINER_TYPE(it_rend) = _SET_CONTAINER;
    _SET_ITERATOR_ITERATOR_TYPE(it_rend) = _BIDIRECTIONAL_ITERATOR;

    return it_rend;
}

/**
 * Return the compare function of key.
 */
bfun_t set_key_comp(const set_t* cpset_set)
{
    assert(cpset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_key_comp(&cpset_set->_t_tree);
#else
    return _rb_tree_key_comp(&cpset_set->_t_tree);
#endif
}

/**
 * Return the compare function of value.
 */
bfun_t set_value_comp(const set_t* cpset_set)
{
    return set_key_comp(cpset_set);
}

/**
 * Erases all the elements of an set.
 */
void set_clear(set_t* pset_set)
{
    assert(pset_set != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_clear(&pset_set->_t_tree);
#else
    _rb_tree_clear(&pset_set->_t_tree);
#endif
}

/**
 * Tests if the two set are equal.
 */
bool_t set_equal(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL);
    assert(cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

/**
 * Tests if the two set are not equal.
 */
bool_t set_not_equal(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL);
    assert(cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_not_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_not_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

/**
 * Tests if the first set is less than the second set.
 */
bool_t set_less(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL);
    assert(cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_less(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_less(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

/**
 * Tests if the first set is less than or equal to the second set.
 */
bool_t set_less_equal(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL);
    assert(cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_less_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_less_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

/**
 * Tests if the first set is greater than the second set.
 */
bool_t set_greater(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL);
    assert(cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_greater(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_greater(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

/**
 * Tests if the first set is greater than or equal to the second set.
 */
bool_t set_greater_equal(const set_t* cpset_first, const set_t* cpset_second)
{
    assert(cpset_first != NULL);
    assert(cpset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    return _avl_tree_greater_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#else
    return _rb_tree_greater_equal(&cpset_first->_t_tree, &cpset_second->_t_tree);
#endif
}

/**
 * Swap the datas of first set and second set.
 */
void set_swap(set_t* pset_first, set_t* pset_second)
{
    assert(pset_first != NULL);
    assert(pset_second != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_swap(&pset_first->_t_tree, &pset_second->_t_tree);
#else
    _rb_tree_swap(&pset_first->_t_tree, &pset_second->_t_tree);
#endif
}

/**
 * Inserts an range of unique element into a set.
 */
void set_insert_range(set_t* pset_set, iterator_t it_begin, iterator_t it_end)
{
    assert(pset_set != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_insert_unique_range(&pset_set->_t_tree, it_begin, it_end);
#else
    _rb_tree_insert_unique_range(&pset_set->_t_tree, it_begin, it_end);
#endif
}

/**
 * Inserts an array of unique element into a set.
 */
void set_insert_array(set_t* pset_set, const void* cpv_array, size_t t_count)
{
    assert(pset_set != NULL);
    assert(cpv_array != NULL);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_insert_unique_array(&pset_set->_t_tree, cpv_array, t_count);
#else
    _rb_tree_insert_unique_array(&pset_set->_t_tree, cpv_array, t_count);
#endif
}

/*
 * Erase an element in an set from specificed position.
 */
void set_erase_pos(set_t* pset_set, set_iterator_t it_pos)
{
    assert(pset_set != NULL);
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_pos) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_pos) == _BIDIRECTIONAL_ITERATOR);
    assert(_SET_ITERATOR_CONTAINER(it_pos) == pset_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_erase_pos(&pset_set->_t_tree, it_pos);
#else
    _rb_tree_erase_pos(&pset_set->_t_tree, it_pos);
#endif
}

/*
 * Erase a range of element in an set.
 */
void set_erase_range(set_t* pset_set, set_iterator_t it_begin, set_iterator_t it_end)
{
    assert(pset_set != NULL);
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_begin) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR);
    assert(_SET_ITERATOR_CONTAINER_TYPE(it_end) == _SET_CONTAINER);
    assert(_SET_ITERATOR_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_SET_ITERATOR_CONTAINER(it_begin) == pset_set);
    assert(_SET_ITERATOR_CONTAINER(it_end) == pset_set);

#ifdef CSTL_SET_AVL_TREE
    _avl_tree_erase_range(&pset_set->_t_tree, it_begin, it_end);
#else
    _rb_tree_erase_range(&pset_set->_t_tree, it_begin, it_end);
#endif
}

/** local function implementation section **/

/** eof **/

