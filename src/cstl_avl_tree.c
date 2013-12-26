/*
 *  The implementation of avl tree.
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
#include <cstl/cstring.h>

#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#include <cstl/cstl_avl_tree.h>

#include "cstl_avl_tree_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create avl tree container.
 */
_avl_tree_t* _create_avl_tree(const char* s_typename)
{
    _avl_tree_t* pt_avl_tree = NULL;

    if ((pt_avl_tree = (_avl_tree_t*)malloc(sizeof(_avl_tree_t))) == NULL) {
        return NULL;
    }

    if (!_create_avl_tree_auxiliary(pt_avl_tree, s_typename)) {
        free(pt_avl_tree);
        return NULL;
    }

    return pt_avl_tree;
}

/**
 * Initialize avl tree container.
 */
void _avl_tree_init(_avl_tree_t* pt_avl_tree, bfun_t t_compare)
{
    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_created(pt_avl_tree));

    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;

    if (t_compare != NULL) {
        pt_avl_tree->_t_compare = t_compare;
    } else {
        pt_avl_tree->_t_compare = _GET_AVL_TREE_TYPE_LESS_FUNCTION(pt_avl_tree);
    }
}

/**
 * Destroy avl tree.
 */
void _avl_tree_destroy(_avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree) || _avl_tree_is_created(pt_avl_tree));

    _avl_tree_destroy_auxiliary(pt_avl_tree);
    free(pt_avl_tree);
}

/**
 * Initialize avl tree container with avl tree.
 */
void _avl_tree_init_copy(_avl_tree_t* pt_dest, const _avl_tree_t* cpt_src)
{
    _avl_tree_iterator_t it_iter;
    _avl_tree_iterator_t it_begin;
    _avl_tree_iterator_t it_end;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(_avl_tree_is_inited(cpt_src));
    assert(_avl_tree_same_type(pt_dest, cpt_src));

    /* init the avl tree with the src avl tree */
    _avl_tree_init(pt_dest,  cpt_src->_t_compare);
    it_begin = _avl_tree_begin(cpt_src);
    it_end = _avl_tree_end(cpt_src);

    /* insert all elements of src into dest */
    for (it_iter = it_begin;
         !_avl_tree_iterator_equal(it_iter, it_end);
         it_iter = _avl_tree_iterator_next(it_iter)) {
        _avl_tree_insert_equal(pt_dest, _avl_tree_iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Initialize avl tree container with specific range.
 */
void _avl_tree_init_copy_equal_range(_avl_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end)
{
    assert(pt_dest != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(_avl_tree_same_iterator_type(pt_dest, it_begin));
    assert(_avl_tree_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _avl_tree_init(pt_dest, NULL);
    _avl_tree_insert_equal_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize avl tree container with specific array.
 */
void _avl_tree_init_copy_equal_array(_avl_tree_t* pt_dest, const void* cpv_array, size_t t_count)
{
    assert(pt_dest != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(cpv_array != NULL);

    _avl_tree_init(pt_dest, NULL);
    _avl_tree_insert_equal_array(pt_dest, cpv_array, t_count);
}

/**
 * Initialize avl tree container with specific range.
 */
void _avl_tree_init_copy_unique_range(_avl_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end)
{
    assert(pt_dest != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(_avl_tree_same_iterator_type(pt_dest, it_begin));
    assert(_avl_tree_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _avl_tree_init(pt_dest, NULL);
    _avl_tree_insert_unique_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize avl tree container with specific array.
 */
void _avl_tree_init_copy_unique_array(_avl_tree_t* pt_dest, const void* cpv_array, size_t t_count)
{
    assert(pt_dest != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(cpv_array != NULL);

    _avl_tree_init(pt_dest, NULL);
    _avl_tree_insert_unique_array(pt_dest, cpv_array, t_count);
}

/**
 * Initialize avl tree container with specific range and compare function.
 */
void _avl_tree_init_copy_equal_range_ex(_avl_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end, bfun_t t_compare)
{
    assert(pt_dest != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(_avl_tree_same_iterator_type(pt_dest, it_begin));
    assert(_avl_tree_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _avl_tree_init(pt_dest, t_compare);
    _avl_tree_insert_equal_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize avl tree container with specific array and compare function.
 */
void _avl_tree_init_copy_equal_array_ex(_avl_tree_t* pt_dest, const void* cpv_array, size_t t_count, bfun_t t_compare)
{
    assert(pt_dest != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(cpv_array != NULL);

    _avl_tree_init(pt_dest, t_compare);
    _avl_tree_insert_equal_array(pt_dest, cpv_array, t_count);
}

/**
 * Initialize avl tree container with specific range and compare function.
 */
void _avl_tree_init_copy_unique_range_ex(_avl_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end, bfun_t t_compare)
{
    assert(pt_dest != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(_avl_tree_same_iterator_type(pt_dest, it_begin));
    assert(_avl_tree_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _avl_tree_init(pt_dest, t_compare);
    _avl_tree_insert_unique_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize avl tree container with specific array and compare function.
 */
void _avl_tree_init_copy_unique_array_ex(_avl_tree_t* pt_dest, const void* cpv_array, size_t t_count, bfun_t t_compare)
{
    assert(pt_dest != NULL);
    assert(_avl_tree_is_created(pt_dest));
    assert(cpv_array != NULL);

    _avl_tree_init(pt_dest, t_compare);
    _avl_tree_insert_unique_array(pt_dest, cpv_array, t_count);
}

/**
 * Assign avl tree container.
 */
void _avl_tree_assign(_avl_tree_t* pt_dest, const _avl_tree_t* cpt_src)
{
    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_avl_tree_is_inited(pt_dest));
    assert(_avl_tree_is_inited(cpt_src));
    assert(_avl_tree_same_type_ex(pt_dest, cpt_src));

    if (!_avl_tree_equal(pt_dest, cpt_src)) {
        _avl_tree_iterator_t it_iter;
        _avl_tree_iterator_t it_begin;
        _avl_tree_iterator_t it_end;

        /* clear dest avl tree */
        _avl_tree_clear(pt_dest);
        it_begin = _avl_tree_begin(cpt_src);
        it_end = _avl_tree_end(cpt_src);

        /* insert all elements of src into dest */
        for (it_iter = it_begin;
             !_avl_tree_iterator_equal(it_iter, it_end);
             it_iter = _avl_tree_iterator_next(it_iter)) {
            _avl_tree_insert_equal(pt_dest, _avl_tree_iterator_get_pointer_ignore_cstr(it_iter));
        }
    }
}

/**
 * Test if a avl tree is empty.
 */
bool_t _avl_tree_empty(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    return cpt_avl_tree->_t_nodecount == 0 ? true : false;
}

/**
 * Get the number of elements int the avl tree.
 */
size_t _avl_tree_size(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    return cpt_avl_tree->_t_nodecount;
}

/**
 * Get the maximum number of elements int the avl tree.
 */
size_t _avl_tree_max_size(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    return (size_t)(-1) / _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
}

/**
 * Return an iterator that addresses the first element in the avl tree.
 */
_avl_tree_iterator_t _avl_tree_begin(const _avl_tree_t* cpt_avl_tree)
{
    _avl_tree_iterator_t it_begin = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    _AVL_TREE_ITERATOR_TREE_POINTER(it_begin) = (void*)cpt_avl_tree;
    _AVL_TREE_ITERATOR_COREPOS(it_begin) = (_byte_t*)cpt_avl_tree->_t_avlroot._pt_left;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the avl tree.
 */
_avl_tree_iterator_t _avl_tree_end(const _avl_tree_t* cpt_avl_tree)
{
    _avl_tree_iterator_t it_end = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    _AVL_TREE_ITERATOR_TREE_POINTER(it_end) = (void*)cpt_avl_tree;
    _AVL_TREE_ITERATOR_COREPOS(it_end) = (_byte_t*)&cpt_avl_tree->_t_avlroot;

    return it_end;
}

_avl_tree_reverse_iterator_t _avl_tree_rbegin(const _avl_tree_t* cpt_avl_tree)
{
    _avl_tree_reverse_iterator_t it_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _AVL_TREE_ITERATOR_TREE_POINTER(it_newiterator) = (void*)cpt_avl_tree;
    _AVL_TREE_ITERATOR_COREPOS(it_newiterator) = (_byte_t*)cpt_avl_tree->_t_avlroot._pt_right;

    return it_newiterator;
}

_avl_tree_reverse_iterator_t _avl_tree_rend(const _avl_tree_t* cpt_avl_tree)
{
    _avl_tree_reverse_iterator_t it_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _AVL_TREE_ITERATOR_TREE_POINTER(it_newiterator) = (void*)cpt_avl_tree;
    _AVL_TREE_ITERATOR_COREPOS(it_newiterator) = (_byte_t*)&cpt_avl_tree->_t_avlroot;

    return it_newiterator;
}

/**
 * Return the compare function of key.
 */
bfun_t _avl_tree_key_comp(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    return cpt_avl_tree->_t_compare;
}

/**
 * Find specific element.
 */
_avl_tree_iterator_t _avl_tree_find(const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    _avl_tree_iterator_t it_iter;

    assert(cpt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    _AVL_TREE_ITERATOR_TREE_POINTER(it_iter) = (void*)cpt_avl_tree;
    _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)_avl_tree_find_value(
        cpt_avl_tree, cpt_avl_tree->_t_avlroot._pt_parent, cpv_value);
    if (_AVL_TREE_ITERATOR_COREPOS(it_iter) == NULL) {
        _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)&cpt_avl_tree->_t_avlroot;
    }

    return it_iter;
}

/**
 * Erases all the elements of a avl tree.
 */
void _avl_tree_clear(_avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));

    /* destroy all elements */
    pt_avl_tree->_t_avlroot._pt_parent = _avl_tree_destroy_subtree(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_nodecount = 0;
}

/**
 * Return the number of specific elements in an avl tree
 */
size_t _avl_tree_count(const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    range_t r_range;

    assert(cpt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    r_range = _avl_tree_equal_range(cpt_avl_tree, cpv_value);
    return abs(_avl_tree_iterator_distance(r_range.it_begin, r_range.it_end));
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
_avl_tree_iterator_t _avl_tree_lower_bound(const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    _avlnode_t*          pt_cur = NULL;
    _avlnode_t*          pt_prev = NULL;
    bool_t               b_less = false;
    bool_t               b_greater = false;
    _avl_tree_iterator_t it_iter;

    assert(cpt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    it_iter = _create_avl_tree_iterator();
    _AVL_TREE_ITERATOR_TREE_POINTER(it_iter) = (void*)cpt_avl_tree;

    if (!_avl_tree_empty(cpt_avl_tree)) {
        pt_prev = cpt_avl_tree->_t_avlroot._pt_parent;

        b_less = b_greater = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
        _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_prev->_pby_data, &b_less);
        _avl_tree_elem_compare_auxiliary(cpt_avl_tree, pt_prev->_pby_data, cpv_value, &b_greater);

        pt_cur = (b_less || !b_greater) ? pt_prev->_pt_left : pt_prev->_pt_right;
        while (pt_cur != NULL) {
            pt_prev = pt_cur;
            b_less = b_greater = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
            _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_prev->_pby_data, &b_less);
            _avl_tree_elem_compare_auxiliary(cpt_avl_tree, pt_prev->_pby_data, cpv_value, &b_greater);

            pt_cur = (b_less || !b_greater) ? pt_prev->_pt_left : pt_prev->_pt_right;
        }

        if (b_less || !b_greater) {
            assert(pt_prev->_pt_left == NULL);
            _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
            assert(_avl_tree_iterator_belong_to_avl_tree(cpt_avl_tree, it_iter));
        } else {
            assert(pt_prev->_pt_right == NULL);
            _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
            it_iter = _avl_tree_iterator_next(it_iter);
        }
    } else {
        it_iter = _avl_tree_end(cpt_avl_tree);
    }

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
_avl_tree_iterator_t _avl_tree_upper_bound(const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    _avlnode_t*          pt_cur = NULL;
    _avlnode_t*          pt_prev = NULL;
    bool_t               b_result = false;
    _avl_tree_iterator_t it_iter;

    assert(cpt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    it_iter = _create_avl_tree_iterator();
    _AVL_TREE_ITERATOR_TREE_POINTER(it_iter) = (void*)cpt_avl_tree;

    if (!_avl_tree_empty(cpt_avl_tree)) {
        pt_prev = cpt_avl_tree->_t_avlroot._pt_parent;
        b_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
        _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_prev->_pby_data, &b_result);

        pt_cur = b_result ? pt_prev->_pt_left : pt_prev->_pt_right;
        while(pt_cur != NULL)
        {
            pt_prev = pt_cur;
            b_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
            _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_prev->_pby_data, &b_result);

            pt_cur = b_result ? pt_prev->_pt_left : pt_prev->_pt_right;
        }

        if (b_result) {
            assert(pt_prev->_pt_left == NULL);
            _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
            assert(_avl_tree_iterator_belong_to_avl_tree(cpt_avl_tree, it_iter));
        } else {
            assert(pt_prev->_pt_right == NULL);
            _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
            it_iter = _avl_tree_iterator_next(it_iter);
        }
    } else {
        it_iter = _avl_tree_end(cpt_avl_tree);
    }

    return it_iter;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _avl_tree_equal_range(const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    range_t r_range;

    assert(cpt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    r_range.it_begin = _avl_tree_lower_bound(cpt_avl_tree, cpv_value);
    r_range.it_end = _avl_tree_upper_bound(cpt_avl_tree, cpv_value);

    return r_range;
}

/**
 * Tests if the two avl tree are equal.
 */
bool_t _avl_tree_equal(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second)
{
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_first_begin;
    _avl_tree_iterator_t it_first_end;
    _avl_tree_iterator_t it_second;
    _avl_tree_iterator_t it_second_begin;
    _avl_tree_iterator_t it_second_end;
    bool_t               b_less = false;
    bool_t               b_greater = false;

    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_avl_tree_is_inited(cpt_first));
    assert(_avl_tree_is_inited(cpt_second));
    assert(_avl_tree_same_type_ex(cpt_first, cpt_second));

    if (cpt_first == cpt_second) {
        return true;
    }

    /* test avl tree size */
    if (_avl_tree_size(cpt_first) != _avl_tree_size(cpt_second)) {
        return false;
    }

    it_first_begin = _avl_tree_begin(cpt_first);
    it_first_end = _avl_tree_end(cpt_first);
    it_second_begin = _avl_tree_begin(cpt_second);
    it_second_end = _avl_tree_end(cpt_second);

    /* test each element */
    for (it_first = it_first_begin, it_second = it_second_begin;
         !_avl_tree_iterator_equal(it_first, it_first_end) && !_avl_tree_iterator_equal(it_second, it_second_end);
         it_first = _avl_tree_iterator_next(it_first), it_second = _avl_tree_iterator_next(it_second)) {
        b_less = b_greater = _GET_AVL_TREE_TYPE_SIZE(cpt_first);
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_first)(
            ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_first))->_pby_data,
            ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_second))->_pby_data, &b_less);
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_first)(
            ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_second))->_pby_data,
            ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_first))->_pby_data, &b_greater);
        if (b_less || b_greater) {
            return false;
        }
    }
    assert(_avl_tree_iterator_equal(it_first, it_first_end) && _avl_tree_iterator_equal(it_second, it_second_end));

    return true;
}

/**
 * Tests if the two avl tree are not equal.
 */
bool_t _avl_tree_not_equal(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second)
{
    return !_avl_tree_equal(cpt_first, cpt_second);
}

/**
 * Tests if the first avl tree is less than the second avl tree.
 */
bool_t _avl_tree_less(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second)
{
    _avl_tree_iterator_t it_first;
    _avl_tree_iterator_t it_first_begin;
    _avl_tree_iterator_t it_first_end;
    _avl_tree_iterator_t it_second;
    _avl_tree_iterator_t it_second_begin;
    _avl_tree_iterator_t it_second_end;
    bool_t               b_result = false;

    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_avl_tree_is_inited(cpt_first));
    assert(_avl_tree_is_inited(cpt_second));
    assert(_avl_tree_same_type_ex(cpt_first, cpt_second));

    it_first_begin = _avl_tree_begin(cpt_first);
    it_first_end = _avl_tree_end(cpt_first);
    it_second_begin = _avl_tree_begin(cpt_second);
    it_second_end = _avl_tree_end(cpt_second);

    /* test each element */
    for (it_first = it_first_begin, it_second = it_second_begin;
         !_avl_tree_iterator_equal(it_first, it_first_end) && !_avl_tree_iterator_equal(it_second, it_second_end);
         it_first = _avl_tree_iterator_next(it_first), it_second = _avl_tree_iterator_next(it_second)) {
        b_result = _GET_AVL_TREE_TYPE_SIZE(cpt_first);
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_first)(
            ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_first))->_pby_data,
            ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_second))->_pby_data, &b_result);
        if (b_result) {
            return true;
        }
        b_result = _GET_AVL_TREE_TYPE_SIZE(cpt_first);
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_first)(
            ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_second))->_pby_data,
            ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_first))->_pby_data, &b_result);
        if (b_result) {
            return false;
        }
    }

    return _avl_tree_size(cpt_first) < _avl_tree_size(cpt_second) ? true : false;
}

/**
 * Tests if the first avl tree is less than or equal to the second avl tree.
 */
bool_t _avl_tree_less_equal(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second)
{
    return (_avl_tree_less(cpt_first, cpt_second) || _avl_tree_equal(cpt_first, cpt_second)) ? true : false;
}

/**
 * Tests if the first avl tree is greater than the second avl tree.
 */
bool_t _avl_tree_greater(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second)
{
    return _avl_tree_less(cpt_second, cpt_first);
}

/**
 * Tests if the first avl tree is greater than or equal to the second avl tree.
 */
bool_t _avl_tree_greater_equal(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second)
{
    return (_avl_tree_greater(cpt_first, cpt_second) || _avl_tree_equal(cpt_first, cpt_second)) ? true : false;
}

/**
 * Swap the datas of first avl_tree and second avl_tree.
 */
void _avl_tree_swap(_avl_tree_t* pt_first, _avl_tree_t* pt_second)
{
    _avl_tree_t t_temp;

    assert(pt_first != NULL);
    assert(pt_second != NULL);
    assert(_avl_tree_is_inited(pt_first));
    assert(_avl_tree_is_inited(pt_second));
    assert(_avl_tree_same_type_ex(pt_first, pt_second));

    if (_avl_tree_equal(pt_first, pt_second)) {
        return;
    }

    t_temp = *pt_first;
    *pt_first = *pt_second;
    *pt_second = t_temp;

    if (_avl_tree_empty(pt_first)) {
        pt_first->_t_avlroot._pt_left = &pt_first->_t_avlroot;
        pt_first->_t_avlroot._pt_right = &pt_first->_t_avlroot;
    } else {
        pt_first->_t_avlroot._pt_parent->_pt_parent = &pt_first->_t_avlroot;
    }

    if (_avl_tree_empty(pt_second)) {
        pt_second->_t_avlroot._pt_left = &pt_second->_t_avlroot;
        pt_second->_t_avlroot._pt_right = &pt_second->_t_avlroot;
    } else {
        pt_second->_t_avlroot._pt_parent->_pt_parent = &pt_second->_t_avlroot;
    }
}

/**
 * Inserts an element into a avl tree.
 */
_avl_tree_iterator_t _avl_tree_insert_equal(_avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    _avl_tree_insert_result_t t_result;
    _avl_tree_iterator_t      it_iter = _create_avl_tree_iterator();

    assert(pt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));

    t_result = _avl_tree_insert_avlnode(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, cpv_value);
    assert(t_result._pt_adjust != NULL && t_result._pt_new != NULL);

    pt_avl_tree->_t_avlroot._pt_parent = t_result._pt_adjust;
    pt_avl_tree->_t_avlroot._pt_parent->_pt_parent = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_left = _avl_tree_get_min_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    pt_avl_tree->_t_avlroot._pt_right = _avl_tree_get_max_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    pt_avl_tree->_t_nodecount++;

    _AVL_TREE_ITERATOR_TREE_POINTER(it_iter) = pt_avl_tree;
    _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)t_result._pt_new;

    return it_iter;
}

/**
 * Inserts an unique element into a avl tree.
 */
_avl_tree_iterator_t _avl_tree_insert_unique(_avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    assert(pt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));

    /* if the avl tree is empty */
    if (_avl_tree_empty(pt_avl_tree)) {
        return _avl_tree_insert_equal(pt_avl_tree, cpv_value);
    } else {
        /* find value in avl tree */
        _avl_tree_iterator_t it_iter = _avl_tree_find(pt_avl_tree, cpv_value);
        /* if the value is exist */
        if (!_avl_tree_iterator_equal(it_iter, _avl_tree_end(pt_avl_tree))) {
            return _avl_tree_end(pt_avl_tree);
        } else {
            /* insert value into avl tree */
            return _avl_tree_insert_equal(pt_avl_tree, cpv_value);
        }
    }
}

/**
 * Inserts an range into a avl tree.
 */
void _avl_tree_insert_equal_range(_avl_tree_t* pt_avl_tree, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));
    assert(_avl_tree_same_iterator_type(pt_avl_tree, it_begin));
    assert(_avl_tree_same_iterator_type(pt_avl_tree, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        _avl_tree_insert_equal(pt_avl_tree, _iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Inserts an array into a avl tree.
 */
void _avl_tree_insert_equal_array(_avl_tree_t* pt_avl_tree, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));
    assert(cpv_array != NULL);

    /*
     * Copy the elements from src array to dest avl tree.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_AVL_TREE_TYPE_BASENAME(pt_avl_tree), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);
        for (i = 0; i < t_count; ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            _avl_tree_insert_equal(pt_avl_tree, pstr_elem);
        }
        string_destroy(pstr_elem);
    } else if (_GET_AVL_TREE_TYPE_STYLE(pt_avl_tree) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_count; ++i) {
            _avl_tree_insert_equal(pt_avl_tree, (unsigned char*)cpv_array + i * _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree));
        }
    } else {
        for (i = 0; i < t_count; ++i) {
            _avl_tree_insert_equal(pt_avl_tree, *((void**)cpv_array + i));
        }
    }
}

/**
 * Inserts an range of unique element into a avl tree.
 */
void _avl_tree_insert_unique_range(_avl_tree_t* pt_avl_tree, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));
    assert(_avl_tree_same_iterator_type(pt_avl_tree, it_begin));
    assert(_avl_tree_same_iterator_type(pt_avl_tree, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        _avl_tree_insert_unique(pt_avl_tree, _iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Inserts an array of unique element into a avl tree.
 */
void _avl_tree_insert_unique_array(_avl_tree_t* pt_avl_tree, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));
    assert(cpv_array != NULL);

    /*
     * Copy the elements from src array to dest avl tree.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_AVL_TREE_TYPE_BASENAME(pt_avl_tree), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);
        for (i = 0; i < t_count; ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            _avl_tree_insert_unique(pt_avl_tree, pstr_elem);
        }
        string_destroy(pstr_elem);
    } else if (_GET_AVL_TREE_TYPE_STYLE(pt_avl_tree) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_count; ++i) {
            _avl_tree_insert_unique(pt_avl_tree, (unsigned char*)cpv_array + i * _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree));
        }
    } else {
        for (i = 0; i < t_count; ++i) {
            _avl_tree_insert_unique(pt_avl_tree, *((void**)cpv_array + i));
        }
    }
}

/*
 * Erase an element in an avl tree from specificed position.
 */
void _avl_tree_erase_pos(_avl_tree_t* pt_avl_tree, _avl_tree_iterator_t it_pos)
{
    _avlnode_t* pt_parent = NULL;
    _avlnode_t* pt_cur = NULL;
    bool_t      b_result = false;

    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));
    assert(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, it_pos));
    assert(!_avl_tree_iterator_equal(it_pos, _avl_tree_end(pt_avl_tree)));
    
    pt_cur = (_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_pos);
    pt_parent = pt_cur->_pt_parent;

    /* delete node X express deleting */
    if (pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL) {
        if (pt_parent == &pt_avl_tree->_t_avlroot) {
            /*
             *  P       P
             *  |   =>   
             *  X
             */
            pt_parent->_pt_parent = NULL;
        } else if (pt_cur == pt_parent->_pt_left) {
            /*
             *    P       P
             *   /   =>   
             *  X
             */
            pt_parent->_pt_left = NULL;
        } else {
            /*
             *   P         P
             *    \   =>  
             *     X
             */
            pt_parent->_pt_right = NULL;
        }
    } else if (pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL) {
        if (pt_parent == &pt_avl_tree->_t_avlroot) {
            /*
             *   P          P
             *   |          |
             *   X     =>   L
             *  /
             * L
             */
            pt_parent->_pt_parent = pt_cur->_pt_left;
            pt_parent->_pt_parent->_pt_parent = pt_parent;
        } else if (pt_cur == pt_parent->_pt_left) {
            /*
             *     P          P
             *    /          /
             *   X     =>   L
             *  /
             * L
             */
            pt_parent->_pt_left = pt_cur->_pt_left;
            pt_parent->_pt_left->_pt_parent = pt_parent;
        } else {
            /*
             *  P           P
             *   \           \
             *    X   =>      L
             *   /
             *  L
             */
            pt_parent->_pt_right = pt_cur->_pt_left;
            pt_parent->_pt_right->_pt_parent = pt_parent;
        }
    } else if (pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL) {
        if (pt_parent == &pt_avl_tree->_t_avlroot) {
            /*
             *     P             P
             *     |             |
             *     X     =>      R
             *      \
             *       R
             */
            pt_parent->_pt_parent = pt_cur->_pt_right;
            pt_parent->_pt_parent->_pt_parent = pt_parent;
        } else if (pt_cur == pt_parent->_pt_right) {
            /*
             *   P             P
             *    \             \
             *     X     =>      R
             *      \
             *       R
             */
            pt_parent->_pt_right = pt_cur->_pt_right;
            pt_parent->_pt_right->_pt_parent = pt_parent;
        } else {
            /*
             *    P              R
             *   /              /
             *  X       =>     R
             *   \
             *    R
             */
            pt_parent->_pt_left = pt_cur->_pt_right;
            pt_parent->_pt_left->_pt_parent = pt_parent;
        }
    } else {
        _avlnode_t* pt_parenttmp = NULL;
        _avlnode_t* pt_curtmp = NULL;

        if (pt_parent == &pt_avl_tree->_t_avlroot) {
            pt_curtmp = _avl_tree_get_min_avlnode(pt_cur->_pt_right);
            if (pt_cur == pt_curtmp->_pt_parent) {
                /*
                 *     P              P
                 *     |              | 
                 *     X       =>     B
                 *    / \            / \
                 *   A   B          A   C
                 *        \
                 *         C
                 */
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_parent = pt_curtmp;

                pt_parent = pt_curtmp;
            } else {
                /*
                 *     P              P
                 *     |              | 
                 *     X       =>     S
                 *    / \            / \
                 *   A   B          A   B
                 *      / \            / \
                 *     S   C          D   C
                 *      \
                 *       D
                 */
                /* pt_curtmp express S; pt_parenttmp express B */
                pt_parenttmp = pt_curtmp->_pt_parent;
                pt_parenttmp->_pt_left = pt_curtmp->_pt_right;
                if (pt_parenttmp->_pt_left != NULL) {
                    pt_parenttmp->_pt_left->_pt_parent = pt_parenttmp;
                }

                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_right = pt_cur->_pt_right;
                pt_curtmp->_pt_right->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_parent = pt_curtmp;

                pt_parent = pt_parenttmp;
            }
        } else if (pt_cur == pt_parent->_pt_left) {
            pt_curtmp = _avl_tree_get_min_avlnode(pt_cur->_pt_right);
            if (pt_cur == pt_curtmp->_pt_parent) {
                /*
                 *       P              P
                 *      /              / 
                 *     X       =>     B
                 *    / \            / \
                 *   A   B          A   C
                 *        \
                 *         C
                 */
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_left = pt_curtmp;

                pt_parent = pt_curtmp;
            } else {
                /*
                 *       P              P
                 *      /              / 
                 *     X       =>     S
                 *    / \            / \
                 *   A   B          A   B
                 *      / \            / \
                 *     S   C          D   C
                 *      \
                 *       D
                 */
                /* pt_curtmp express S; pt_parenttmp express B */
                pt_parenttmp = pt_curtmp->_pt_parent;
                pt_parenttmp->_pt_left = pt_curtmp->_pt_right;
                if (pt_parenttmp->_pt_left != NULL) {
                    pt_parenttmp->_pt_left->_pt_parent = pt_parenttmp;
                }

                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_right = pt_cur->_pt_right;
                pt_curtmp->_pt_right->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_left = pt_curtmp;

                pt_parent = pt_parenttmp;
            }
        } else {
            pt_curtmp = _avl_tree_get_min_avlnode(pt_cur->_pt_right);
            if (pt_cur == pt_curtmp->_pt_parent) {
                /*
                 *      P            P
                 *       \            \
                 *        X     =>     B
                 *       / \          / \
                 *      A   B        A   C
                 *           \
                 *            C
                 */
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_right = pt_curtmp;

                pt_parent = pt_curtmp;
            } else {
                /*
                 *      P            P
                 *       \            \
                 *        X     =>     S
                 *       / \          / \
                 *      A   B        A   B
                 *         / \          / \
                 *        C   D        C   D
                 *       / \          / \
                 *      S   E        F   E
                 *       \
                 *        F
                 */
                /* pt_curtmp express S; pt_parenttmp express C */
                pt_parenttmp = pt_curtmp->_pt_parent;
                pt_parenttmp->_pt_left = pt_curtmp->_pt_right;
                if (pt_parenttmp->_pt_left != NULL) {
                    pt_parenttmp->_pt_left->_pt_parent = pt_parenttmp;
                }

                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_right = pt_cur->_pt_right;
                pt_curtmp->_pt_right->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_right = pt_curtmp;

                pt_parent = pt_parenttmp;
            }
        }
    }

    /* rebalance until to root */
    if (pt_parent != &pt_avl_tree->_t_avlroot) {
        _avlnode_t* pt_newcur = pt_parent;
        pt_parent = pt_newcur->_pt_parent;
        while (pt_parent != &pt_avl_tree->_t_avlroot) {
            if (pt_newcur == pt_parent->_pt_left) {
                pt_parent->_pt_left = _avl_tree_rebalance(pt_parent->_pt_left);
                pt_parent->_pt_left->_pt_parent = pt_parent;
            } else {
                pt_parent->_pt_right = _avl_tree_rebalance(pt_parent->_pt_right);
                pt_parent->_pt_right->_pt_parent = pt_parent;
            }

            pt_newcur = pt_parent;
            pt_parent = pt_newcur->_pt_parent;
        }
    }

    /* rebalance root */
    if (pt_parent->_pt_parent != NULL) {
        pt_parent->_pt_parent = _avl_tree_rebalance(pt_parent->_pt_parent);
        pt_parent->_pt_parent->_pt_parent = pt_parent;
    }

    /* destroy node */
    b_result = _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree);
    _GET_AVL_TREE_TYPE_DESTROY_FUNCTION(pt_avl_tree)(pt_cur->_pby_data, &b_result);
    assert(b_result);
    _alloc_deallocate(&pt_avl_tree->_t_allocator, pt_cur,
        _AVL_TREE_NODE_SIZE(_GET_AVL_TREE_TYPE_SIZE(pt_avl_tree)), 1);
    pt_avl_tree->_t_nodecount--;
    if (pt_avl_tree->_t_nodecount == 0) {
        pt_avl_tree->_t_avlroot._pt_parent = NULL;
        pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
        pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    } else {
        pt_avl_tree->_t_avlroot._pt_left = _avl_tree_get_min_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
        pt_avl_tree->_t_avlroot._pt_right = _avl_tree_get_max_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    }
}

/*
 * Erase a range of element in an avl tree.
 */
void _avl_tree_erase_range(_avl_tree_t* pt_avl_tree, _avl_tree_iterator_t it_begin, _avl_tree_iterator_t it_end)
{
    _avl_tree_iterator_t it_iter;
    _avl_tree_iterator_t it_next;

    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree));
    assert(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, it_begin));
    assert(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, it_end));
    assert(_avl_tree_iterator_equal(it_begin, it_end) || _avl_tree_iterator_before(it_begin, it_end));

    it_iter = it_next = it_begin;
    if (!_avl_tree_iterator_equal(it_next, _avl_tree_end(pt_avl_tree))) {
        it_next = _avl_tree_iterator_next(it_next);
    }
    while (!_avl_tree_iterator_equal(it_iter, it_end)) {
        _avl_tree_erase_pos(pt_avl_tree, it_iter);
        
        it_iter = it_next;
        if (!_avl_tree_iterator_equal(it_next, _avl_tree_end(pt_avl_tree))) {
            it_next = _avl_tree_iterator_next(it_next);
        }
    }
}

/**
 * Erase an element from a avl tree that match a specified element.
 */
size_t _avl_tree_erase(_avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    size_t  t_count = _avl_tree_count(pt_avl_tree, cpv_value);
    range_t r_range = _avl_tree_equal_range(pt_avl_tree, cpv_value);

    if (!_avl_tree_iterator_equal(r_range.it_begin, _avl_tree_end(pt_avl_tree))) {
        _avl_tree_erase_range(pt_avl_tree, r_range.it_begin, r_range.it_end);
    }

    return t_count;
}

/** local function implementation section **/

/** eof **/

