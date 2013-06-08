/*
 *  The implementation of multiset.
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
#include <cstl/cset.h>

#include "cstl_multiset_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Initialize multiset container.
 */
void multiset_init(multiset_t* pmset_mset)
{
    assert(pmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init(&pmset_mset->_t_tree, NULL);
#else
    _rb_tree_init(&pmset_mset->_t_tree, NULL);
#endif
}

/**
 * Initialize multiset container with user define compare function.
 */
void multiset_init_ex(multiset_t* pmset_mset, bfun_t bfun_compare)
{
    assert(pmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init(&pmset_mset->_t_tree, bfun_compare);
#else
    _rb_tree_init(&pmset_mset->_t_tree, bfun_compare);
#endif
}

/**
 * Destroy multiset.
 */
void multiset_destroy(multiset_t* pmset_mset)
{
    assert(pmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_destroy(&pmset_mset->_t_tree);
#else
    _rb_tree_destroy(&pmset_mset->_t_tree);
#endif
}

/**
 * Initialize multiset container with multiset.
 */
void multiset_init_copy(multiset_t* pmset_dest, const multiset_t* cpmset_src)
{
    assert(pmset_dest != NULL);
    assert(cpmset_src != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy(&pmset_dest->_t_tree, &cpmset_src->_t_tree);
#else
    _rb_tree_init_copy(&pmset_dest->_t_tree, &cpmset_src->_t_tree);
#endif
}

/**
 * Initialize multiset container with specific range.
 */
void multiset_init_copy_range(multiset_t* pmset_dest, iterator_t it_begin, iterator_t it_end)
{
    assert(pmset_dest != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy_equal_range(&pmset_dest->_t_tree, it_begin, it_end);
#else
    _rb_tree_init_copy_equal_range(&pmset_dest->_t_tree, it_begin, it_end);
#endif
}

/**
 * Initialize multiset container with specific array.
 */
void multiset_init_copy_array(multiset_t* pmset_dest, const void* cpv_array, size_t t_count)
{
    assert(pmset_dest != NULL);
    assert(cpv_array != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy_equal_array(&pmset_dest->_t_tree, cpv_array, t_count);
#else
    _rb_tree_init_copy_equal_array(&pmset_dest->_t_tree, cpv_array, t_count);
#endif
}

/**
 * Initialize multiset container with specific range and compare function.
 */
void multiset_init_copy_range_ex(
    multiset_t* pmset_dest, iterator_t it_begin, iterator_t it_end, bfun_t bfun_compare)
{
    assert(pmset_dest != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy_equal_range_ex(&pmset_dest->_t_tree, it_begin, it_end, bfun_compare);
#else
    _rb_tree_init_copy_equal_range_ex(&pmset_dest->_t_tree, it_begin, it_end, bfun_compare);
#endif
}

/**
 * Initialize multiset container with specific array and compare function.
 */
void multiset_init_copy_array_ex(
    multiset_t* pmset_dest, const void* cpv_array, size_t t_count, bfun_t bfun_compare)
{
    assert(pmset_dest != NULL);
    assert(cpv_array != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_init_copy_equal_array_ex(&pmset_dest->_t_tree, cpv_array, t_count, bfun_compare);
#else
    _rb_tree_init_copy_equal_array_ex(&pmset_dest->_t_tree, cpv_array, t_count, bfun_compare);
#endif
}

/**
 * Assign multiset container.
 */
void multiset_assign(multiset_t* pmset_dest, const multiset_t* cpmset_src)
{
    assert(pmset_dest != NULL);
    assert(cpmset_src != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_assign(&pmset_dest->_t_tree, &cpmset_src->_t_tree);
#else
    _rb_tree_assign(&pmset_dest->_t_tree, &cpmset_src->_t_tree);
#endif
}

/**
 * Test if an multiset is empty.
 */
bool_t multiset_empty(const multiset_t* cpmset_mset)
{
    assert(cpmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_empty(&cpmset_mset->_t_tree);
#else
    return _rb_tree_empty(&cpmset_mset->_t_tree);
#endif
}

/**
 * Get the number of elements int the multiset.
 */
size_t multiset_size(const multiset_t* cpmset_mset)
{
    assert(cpmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_size(&cpmset_mset->_t_tree);
#else
    return _rb_tree_size(&cpmset_mset->_t_tree);
#endif
}

/**
 * Get the maximum number of elements int the multiset.
 */
size_t multiset_max_size(const multiset_t* cpmset_mset)
{
    assert(cpmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_max_size(&cpmset_mset->_t_tree);
#else
    return _rb_tree_max_size(&cpmset_mset->_t_tree);
#endif
}

/**
 * Return an iterator that addresses the first element in the multiset.
 */
multiset_iterator_t multiset_begin(const multiset_t* cpmset_mset)
{
    multiset_iterator_t it_begin;

    assert(cpmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    it_begin = _avl_tree_begin(&cpmset_mset->_t_tree);
#else
    it_begin = _rb_tree_begin(&cpmset_mset->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_begin) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_begin) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_begin) = _BIDIRECTIONAL_ITERATOR;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the multiset.
 */
multiset_iterator_t multiset_end(const multiset_t* cpmset_mset)
{
    multiset_iterator_t it_end;

    assert(cpmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    it_end = _avl_tree_end(&cpmset_mset->_t_tree);
#else
    it_end = _rb_tree_end(&cpmset_mset->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_end) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_end) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_end) = _BIDIRECTIONAL_ITERATOR;

    return it_end;
}

multiset_iterator_t multiset_rbegin(const multiset_t* cpmset_mset)
{
    multiset_iterator_t it_rbegin;

    assert(cpmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    it_rbegin = _avl_tree_rbegin(&cpmset_mset->_t_tree);
#else
    it_rbegin = _rb_tree_rbegin(&cpmset_mset->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_rbegin) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_rbegin) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_rbegin) = _BIDIRECTIONAL_ITERATOR;

    return it_rbegin;
}

multiset_iterator_t multiset_rend(const multiset_t* cpmset_mset)
{
    multiset_iterator_t it_rend;

    assert(cpmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    it_rend = _avl_tree_rend(&cpmset_mset->_t_tree);
#else
    it_rend = _rb_tree_rend(&cpmset_mset->_t_tree);
#endif

    _ITERATOR_CONTAINER(it_rend) = (multiset_t*)cpmset_mset;
    _MULTISET_ITERATOR_CONTAINER_TYPE(it_rend) = _MULTISET_CONTAINER;
    _MULTISET_ITERATOR_ITERATOR_TYPE(it_rend) = _BIDIRECTIONAL_ITERATOR;

    return it_rend;
}

/**
 * Return the compare function of key.
 */
bfun_t multiset_key_comp(const multiset_t* cpmset_mset)
{
    assert(cpmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_key_comp(&cpmset_mset->_t_tree);
#else
    return _rb_tree_key_comp(&cpmset_mset->_t_tree);
#endif
}

/**
 * Return the compare function of value.
 */
bfun_t multiset_value_comp(const multiset_t* cpmset_mset)
{
    return multiset_key_comp(cpmset_mset);
}

/**
 * Erases all the elements of an multiset.
 */
void multiset_clear(multiset_t* pmset_mset)
{
    assert(pmset_mset != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_clear(&pmset_mset->_t_tree);
#else
    _rb_tree_clear(&pmset_mset->_t_tree);
#endif
}

/**
 * Tests if the two multiset are equal.
 */
bool_t multiset_equal(const multiset_t* cpmset_first, const multiset_t* cpmset_second)
{
    assert(cpmset_first != NULL);
    assert(cpmset_second != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_equal(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#else
    return _rb_tree_equal(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#endif
}

/**
 * Tests if the two multiset are not equal.
 */
bool_t multiset_not_equal(const multiset_t* cpmset_first, const multiset_t* cpmset_second)
{
    assert(cpmset_first != NULL);
    assert(cpmset_second != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_not_equal(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#else
    return _rb_tree_not_equal(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#endif
}

/**
 * Tests if the first multiset is less than the second multiset.
 */
bool_t multiset_less(const multiset_t* cpmset_first, const multiset_t* cpmset_second)
{
    assert(cpmset_first != NULL);
    assert(cpmset_second != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_less(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#else
    return _rb_tree_less(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#endif
}

/**
 * Tests if the first multiset is less than or equal to the second multiset.
 */
bool_t multiset_less_equal(const multiset_t* cpmset_first, const multiset_t* cpmset_second)
{
    assert(cpmset_first != NULL);
    assert(cpmset_second != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_less_equal(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#else
    return _rb_tree_less_equal(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#endif
}

/**
 * Tests if the first multiset is greater than the second multiset.
 */
bool_t multiset_greater(const multiset_t* cpmset_first, const multiset_t* cpmset_second)
{
    assert(cpmset_first != NULL);
    assert(cpmset_second != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_greater(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#else
    return _rb_tree_greater(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#endif
}

/**
 * Tests if the first multiset is greater than or equal to the second multiset.
 */
bool_t multiset_greater_equal(const multiset_t* cpmset_first, const multiset_t* cpmset_second)
{
    assert(cpmset_first != NULL);
    assert(cpmset_second != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    return _avl_tree_greater_equal(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#else
    return _rb_tree_greater_equal(&cpmset_first->_t_tree, &cpmset_second->_t_tree);
#endif
}

/**
 * Swap the datas of first multiset and second multiset.
 */
void multiset_swap(multiset_t* pmset_first, multiset_t* pmset_second)
{
    assert(pmset_first != NULL);
    assert(pmset_second != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_swap(&pmset_first->_t_tree, &pmset_second->_t_tree);
#else
    _rb_tree_swap(&pmset_first->_t_tree, &pmset_second->_t_tree);
#endif
}

/**
 * Inserts an range of element into a multiset.
 */
void multiset_insert_range(multiset_t* pmset_mset, iterator_t it_begin, iterator_t it_end)
{
    assert(pmset_mset != NULL);
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_insert_equal_range(&pmset_mset->_t_tree, it_begin, it_end);
#else
    _rb_tree_insert_equal_range(&pmset_mset->_t_tree, it_begin, it_end);
#endif
}

/**
 * Inserts an array of element into a multiset.
 */
void multiset_insert_array(multiset_t* pmset_mset, const void* cpv_array, size_t t_count)
{
    assert(pmset_mset != NULL);
    assert(cpv_array != NULL);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_insert_equal_array(&pmset_mset->_t_tree, cpv_array, t_count);
#else
    _rb_tree_insert_equal_array(&pmset_mset->_t_tree, cpv_array, t_count);
#endif
}

/*
 * Erase an element in an multiset from specificed position.
 */
void multiset_erase_pos(multiset_t* pmset_mset, multiset_iterator_t it_pos)
{
    assert(pmset_mset != NULL);
    assert(_MULTISET_ITERATOR_CONTAINER_TYPE(it_pos) == _MULTISET_CONTAINER);
    assert(_MULTISET_ITERATOR_ITERATOR_TYPE(it_pos) == _BIDIRECTIONAL_ITERATOR);
    assert(_MULTISET_ITERATOR_CONTAINER(it_pos) == pmset_mset);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_erase_pos(&pmset_mset->_t_tree, it_pos);
#else
    _rb_tree_erase_pos(&pmset_mset->_t_tree, it_pos);
#endif
}

/*
 * Erase a range of element in an multiset.
 */
void multiset_erase_range(multiset_t* pmset_mset, multiset_iterator_t it_begin, multiset_iterator_t it_end)
{
    assert(pmset_mset != NULL);
    assert(_MULTISET_ITERATOR_CONTAINER_TYPE(it_begin) == _MULTISET_CONTAINER);
    assert(_MULTISET_ITERATOR_ITERATOR_TYPE(it_begin) == _BIDIRECTIONAL_ITERATOR);
    assert(_MULTISET_ITERATOR_CONTAINER_TYPE(it_end) == _MULTISET_CONTAINER);
    assert(_MULTISET_ITERATOR_ITERATOR_TYPE(it_end) == _BIDIRECTIONAL_ITERATOR);
    assert(_MULTISET_ITERATOR_CONTAINER(it_begin) == pmset_mset);
    assert(_MULTISET_ITERATOR_CONTAINER(it_end) == pmset_mset);

#ifdef CSTL_MULTISET_AVL_TREE
    _avl_tree_erase_range(&pmset_mset->_t_tree, it_begin, it_end);
#else
    _rb_tree_erase_range(&pmset_mset->_t_tree, it_begin, it_end);
#endif
}

/** local function implementation section **/

/** eof **/

