/*
 *  The implementation of rb tree.
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

#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>

#include "cstl_rb_tree_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create rb tree container.
 */
_rb_tree_t* _create_rb_tree(const char* s_typename)
{
    _rb_tree_t*  pt_rb_tree = NULL;

    if ((pt_rb_tree = (_rb_tree_t*)malloc(sizeof(_rb_tree_t))) == NULL) {
        return NULL;
    }

    if (!_create_rb_tree_auxiliary(pt_rb_tree, s_typename)) {
        free(pt_rb_tree);
        return NULL;
    }

    return pt_rb_tree;
}

/**
 * Initialize rb tree container.
 */
void _rb_tree_init(_rb_tree_t* pt_rb_tree, bfun_t t_compare)
{
    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_created(pt_rb_tree));

    pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;


    pt_rb_tree->_t_compare = t_compare != NULL ? t_compare : _GET_RB_TREE_TYPE_LESS_FUNCTION(pt_rb_tree);
}

/**
 * Destroy rb tree.
 */
void _rb_tree_destroy(_rb_tree_t* pt_rb_tree)
{
    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree) || _rb_tree_is_created(pt_rb_tree));

    _rb_tree_destroy_auxiliary(pt_rb_tree);
    free(pt_rb_tree);
}

/**
 * Initialize rb tree container with rb tree.
 */
void _rb_tree_init_copy(_rb_tree_t* pt_dest, const _rb_tree_t* cpt_src)
{
    _rb_tree_iterator_t it_iter;
    _rb_tree_iterator_t it_begin;
    _rb_tree_iterator_t it_end;

    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(_rb_tree_is_inited(cpt_src));
    assert(_rb_tree_same_type(pt_dest, cpt_src));

    _rb_tree_init(pt_dest, cpt_src->_t_compare);
    it_begin = _rb_tree_begin(cpt_src);
    it_end = _rb_tree_end(cpt_src);

    for (it_iter = it_begin;
         !_rb_tree_iterator_equal(it_iter, it_end);
         it_iter = _rb_tree_iterator_next(it_iter)) {
        _rb_tree_insert_equal(pt_dest, _rb_tree_iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Initialize rb tree container with specific range.
 */
void _rb_tree_init_copy_equal_range(_rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end)
{
    assert(pt_dest != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(_rb_tree_same_iterator_type(pt_dest, it_begin));
    assert(_rb_tree_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _rb_tree_init(pt_dest, NULL);
    _rb_tree_insert_equal_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize rb tree container with specific range.
 */
void _rb_tree_init_copy_unique_range(_rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end)
{
    assert(pt_dest != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(_rb_tree_same_iterator_type(pt_dest, it_begin));
    assert(_rb_tree_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _rb_tree_init(pt_dest, NULL);
    _rb_tree_insert_unique_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize rb tree container with specific array.
 */
void _rb_tree_init_copy_equal_array(_rb_tree_t* pt_dest, const void* cpv_array, size_t t_count)
{
    assert(pt_dest != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(cpv_array != NULL);

    _rb_tree_init(pt_dest, NULL);
    _rb_tree_insert_equal_array(pt_dest, cpv_array, t_count);
}

/**
 * Initialize rb tree container with specific array.
 */
void _rb_tree_init_copy_unique_array(_rb_tree_t* pt_dest, const void* cpv_array, size_t t_count)
{
    assert(pt_dest != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(cpv_array != NULL);

    _rb_tree_init(pt_dest, NULL);
    _rb_tree_insert_unique_array(pt_dest, cpv_array, t_count);
}

/**
 * Initialize rb tree container with specific range and compare function.
 */
void _rb_tree_init_copy_equal_range_ex(
    _rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end, bfun_t t_compare)
{
    assert(pt_dest != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(_rb_tree_same_iterator_type(pt_dest, it_begin));
    assert(_rb_tree_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _rb_tree_init(pt_dest, t_compare);
    _rb_tree_insert_equal_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize rb tree container with specific range and compare function.
 */
void _rb_tree_init_copy_unique_range_ex(
    _rb_tree_t* pt_dest, iterator_t it_begin, iterator_t it_end, bfun_t t_compare)
{
    assert(pt_dest != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(_rb_tree_same_iterator_type(pt_dest, it_begin));
    assert(_rb_tree_same_iterator_type(pt_dest, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    _rb_tree_init(pt_dest, t_compare);
    _rb_tree_insert_unique_range(pt_dest, it_begin, it_end);
}

/**
 * Initialize rb tree container with specific array and compare function.
 */
void _rb_tree_init_copy_equal_array_ex(
    _rb_tree_t* pt_dest, const void* cpv_array, size_t t_count, bfun_t t_compare)
{
    assert(pt_dest != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(cpv_array != NULL);

    _rb_tree_init(pt_dest, t_compare);
    _rb_tree_insert_equal_array(pt_dest, cpv_array, t_count);
}

/**
 * Initialize rb tree container with specific array and compare function.
 */
void _rb_tree_init_copy_unique_array_ex(
    _rb_tree_t* pt_dest, const void* cpv_array, size_t t_count, bfun_t t_compare)
{
    assert(pt_dest != NULL);
    assert(_rb_tree_is_created(pt_dest));
    assert(cpv_array != NULL);

    _rb_tree_init(pt_dest, t_compare);
    _rb_tree_insert_unique_array(pt_dest, cpv_array, t_count);
}

/**
 * Assign rb tree container.
 */
void _rb_tree_assign(_rb_tree_t* pt_dest, const _rb_tree_t* cpt_src)
{
    assert(pt_dest != NULL);
    assert(cpt_src != NULL);
    assert(_rb_tree_is_inited(pt_dest));
    assert(_rb_tree_is_inited(cpt_src));
    assert(_rb_tree_same_type_ex(pt_dest, cpt_src));

    if (!_rb_tree_equal(pt_dest, cpt_src)) {
        _rb_tree_iterator_t it_iter;
        _rb_tree_iterator_t it_begin;
        _rb_tree_iterator_t it_end;

        /* clear dest rb tree */
        _rb_tree_clear(pt_dest);
        it_begin = _rb_tree_begin(cpt_src);
        it_end = _rb_tree_end(cpt_src);

        /* insert all elements of src into dest */
        for (it_iter = it_begin;
             !_rb_tree_iterator_equal(it_iter, it_end);
             it_iter = _rb_tree_iterator_next(it_iter)) {
            _rb_tree_insert_equal(pt_dest, _rb_tree_iterator_get_pointer_ignore_cstr(it_iter));
        }
    }
}

/**
 * Test if an rb tree is empty.
 */
bool_t _rb_tree_empty(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    return cpt_rb_tree->_t_nodecount == 0 ? true : false;
}

/**
 * Get the number of elements int the rb tree.
 */
size_t _rb_tree_size(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    return cpt_rb_tree->_t_nodecount;
}

/**
 * Get the maximum number of elements int the rb tree.
 */
size_t _rb_tree_max_size(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    return (size_t)(-1) / _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
}

/**
 * Return an iterator that addresses the first element in the rb tree.
 */
_rb_tree_iterator_t _rb_tree_begin(const _rb_tree_t* cpt_rb_tree)
{
    _rb_tree_iterator_t it_begin = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    _RB_TREE_ITERATOR_TREE_POINTER(it_begin) = (void*)cpt_rb_tree;
    _RB_TREE_ITERATOR_COREPOS(it_begin) = (_byte_t*)cpt_rb_tree->_t_rbroot._pt_left;

    return it_begin;
}

/**
 * Return an iterator that addresses the location succeeding the last element in the rb tree.
 */
_rb_tree_iterator_t _rb_tree_end(const _rb_tree_t* cpt_rb_tree)
{
    _rb_tree_iterator_t it_end = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    _RB_TREE_ITERATOR_TREE_POINTER(it_end) = (void*)cpt_rb_tree;
    _RB_TREE_ITERATOR_COREPOS(it_end) = (_byte_t*)&cpt_rb_tree->_t_rbroot;

    return it_end;
}

_rb_tree_iterator_t _rb_tree_rend(const _rb_tree_t* cpt_rb_tree)
{
    _rb_tree_iterator_t it_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _RB_TREE_ITERATOR_TREE_POINTER(it_newiterator) = (void*)cpt_rb_tree;
    _RB_TREE_ITERATOR_COREPOS(it_newiterator) = (_byte_t*)&cpt_rb_tree->_t_rbroot;

    return it_newiterator;
}

_rb_tree_iterator_t _rb_tree_rbegin(const _rb_tree_t* cpt_rb_tree)
{
    _rb_tree_iterator_t it_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _RB_TREE_ITERATOR_TREE_POINTER(it_newiterator) = (void*)cpt_rb_tree;
    _RB_TREE_ITERATOR_COREPOS(it_newiterator) = (_byte_t*)cpt_rb_tree->_t_rbroot._pt_right;

    return it_newiterator;
}

/**
 * Return the compare function of key.
 */
bfun_t _rb_tree_key_comp(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    return cpt_rb_tree->_t_compare;
}

/**
 * Find specific element.
 */
_rb_tree_iterator_t _rb_tree_find(const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    _rb_tree_iterator_t it_iter;

    assert(cpt_rb_tree != NULL);
    assert(cpv_value != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    _RB_TREE_ITERATOR_TREE_POINTER(it_iter) = (void*)cpt_rb_tree;
    _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)_rb_tree_find_value(
        cpt_rb_tree, cpt_rb_tree->_t_rbroot._pt_parent, cpv_value);
    if (_RB_TREE_ITERATOR_COREPOS(it_iter) == NULL) {
        _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)&cpt_rb_tree->_t_rbroot;
    }

    return it_iter;
}

/**
 * Erases all the elements of an rb tree.
 */
void _rb_tree_clear(_rb_tree_t* pt_rb_tree)
{
    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));

    pt_rb_tree->_t_rbroot._pt_parent = _rb_tree_destroy_subtree(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent);
    assert(pt_rb_tree->_t_rbroot._pt_parent == NULL);
    pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_nodecount = 0;
}

/**
 * Tests if the two rb tree are equal.
 */
bool_t _rb_tree_equal(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second)
{
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_first_begin;
    _rb_tree_iterator_t it_first_end;
    _rb_tree_iterator_t it_second;
    _rb_tree_iterator_t it_second_begin;
    _rb_tree_iterator_t it_second_end;
    bool_t              b_less = false;
    bool_t              b_greater = false;

    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_rb_tree_is_inited(cpt_first));
    assert(_rb_tree_is_inited(cpt_second));
    assert(_rb_tree_same_type_ex(cpt_first, cpt_second));

    if (cpt_first == cpt_second) {
        return true;
    }
    
    /* test rb tree size */
    if (_rb_tree_size(cpt_first) != _rb_tree_size(cpt_second)) {
        return false;
    }

    it_first_begin = _rb_tree_begin(cpt_first);
    it_first_end = _rb_tree_end(cpt_first);
    it_second_begin = _rb_tree_begin(cpt_second);
    it_second_end = _rb_tree_end(cpt_second);

    /* test each element */
    for (it_first = it_first_begin, it_second = it_second_begin;
         !_rb_tree_iterator_equal(it_first, it_first_end) && !_rb_tree_iterator_equal(it_second, it_second_end);
         it_first = _rb_tree_iterator_next(it_first), it_second = _rb_tree_iterator_next(it_second)) {
        b_less = b_greater = _GET_RB_TREE_TYPE_SIZE(cpt_first);
        _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_first)(
            ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_first))->_pby_data,
            ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_second))->_pby_data, &b_less);
        _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_first)(
            ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_second))->_pby_data,
            ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_first))->_pby_data, &b_greater);
        if (b_less || b_greater) {
            return false;
        }
    }

    assert(_rb_tree_iterator_equal(it_first, it_first_end) && _rb_tree_iterator_equal(it_second, it_second_end));

    return true;
}

/**
 * Tests if the two rb tree are not equal.
 */
bool_t _rb_tree_not_equal(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second)
{
    return !_rb_tree_equal(cpt_first, cpt_second);
}

/**
 * Tests if the first rb tree is less than the second rb tree.
 */
bool_t _rb_tree_less(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second)
{
    _rb_tree_iterator_t it_first;
    _rb_tree_iterator_t it_first_begin;
    _rb_tree_iterator_t it_first_end;
    _rb_tree_iterator_t it_second;
    _rb_tree_iterator_t it_second_begin;
    _rb_tree_iterator_t it_second_end;
    bool_t              b_result = false;

    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_rb_tree_is_inited(cpt_first));
    assert(_rb_tree_is_inited(cpt_second));
    assert(_rb_tree_same_type_ex(cpt_first, cpt_second));

    it_first_begin = _rb_tree_begin(cpt_first);
    it_first_end = _rb_tree_end(cpt_first);
    it_second_begin = _rb_tree_begin(cpt_second);
    it_second_end = _rb_tree_end(cpt_second);

    /* test each element */
    for (it_first = it_first_begin, it_second = it_second_begin;
         !_rb_tree_iterator_equal(it_first, it_first_end) && !_rb_tree_iterator_equal(it_second, it_second_end);
         it_first = _rb_tree_iterator_next(it_first), it_second = _rb_tree_iterator_next(it_second)) {
        b_result = _GET_RB_TREE_TYPE_SIZE(cpt_first);
        _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_first)(
            ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_first))->_pby_data,
            ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_second))->_pby_data, &b_result);
        if (b_result) {
            return true;
        }

        b_result = _GET_RB_TREE_TYPE_SIZE(cpt_first);
        _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_first)(
            ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_second))->_pby_data,
            ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_first))->_pby_data, &b_result);
        if (b_result) {
            return false;
        }
    }

    return _rb_tree_size(cpt_first) < _rb_tree_size(cpt_second) ? true : false;
}

/**
 * Tests if the first rb tree is less than or equal to the second rb tree.
 */
bool_t _rb_tree_less_equal(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second)
{
    return (_rb_tree_less(cpt_first, cpt_second) || _rb_tree_equal(cpt_first, cpt_second)) ? true : false;
}

/**
 * Tests if the first rb tree is greater than the second rb tree.
 */
bool_t _rb_tree_greater(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second)
{
    return _rb_tree_less(cpt_second, cpt_first);
}

/**
 * Tests if the first rb tree is greater than or equal to the second rb tree.
 */
bool_t _rb_tree_greater_equal(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second)
{
    return (_rb_tree_greater(cpt_first, cpt_second) || _rb_tree_equal(cpt_first, cpt_second)) ? true : false;
}

/**
 * Swap the datas of first rb_tree and second rb_tree.
 */
void _rb_tree_swap(_rb_tree_t* pt_first, _rb_tree_t* pt_second)
{
    _rb_tree_t t_temp;

    assert(pt_first != NULL);
    assert(pt_second != NULL);
    assert(_rb_tree_is_inited(pt_first));
    assert(_rb_tree_is_inited(pt_second));
    assert(_rb_tree_same_type_ex(pt_first, pt_second));

    if (_rb_tree_equal(pt_first, pt_second)) {
        return;
    }

    t_temp = *pt_first;
    *pt_first = *pt_second;
    *pt_second = t_temp;

    if (_rb_tree_empty(pt_first)) {
        pt_first->_t_rbroot._pt_left = &pt_first->_t_rbroot;
        pt_first->_t_rbroot._pt_right = &pt_first->_t_rbroot;
    } else {
        pt_first->_t_rbroot._pt_parent->_pt_parent =  &pt_first->_t_rbroot;
    }

    if (_rb_tree_empty(pt_second)) {
        pt_second->_t_rbroot._pt_left = &pt_second->_t_rbroot;
        pt_second->_t_rbroot._pt_right = &pt_second->_t_rbroot;
    } else {
        pt_second->_t_rbroot._pt_parent->_pt_parent = &pt_second->_t_rbroot;
    }
}

/**
 * Return the number of specific elements in an rb tree
 */
size_t _rb_tree_count(const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    range_t r_range;

    assert(cpt_rb_tree != NULL);
    assert(cpv_value != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    r_range = _rb_tree_equal_range(cpt_rb_tree, cpv_value);
    return abs(_rb_tree_iterator_distance(r_range.it_begin, r_range.it_end));
}

/**
 * Return an iterator to the first element that is equal to or greater than a specific element.
 */
_rb_tree_iterator_t _rb_tree_lower_bound(const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    _rbnode_t*          pt_cur = NULL;
    _rbnode_t*          pt_prev = NULL;
    _rb_tree_iterator_t it_iter;
    bool_t              b_less = false;
    bool_t              b_greater = false;

    assert(cpt_rb_tree != NULL);
    assert(cpv_value != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    it_iter = _create_rb_tree_iterator();
    _RB_TREE_ITERATOR_TREE_POINTER(it_iter) = (void*)cpt_rb_tree;

    if (!_rb_tree_empty(cpt_rb_tree)) {
        pt_prev = cpt_rb_tree->_t_rbroot._pt_parent;

        b_less = b_greater = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
        _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pby_data, &b_less);
        _rb_tree_elem_compare_auxiliary(cpt_rb_tree, pt_prev->_pby_data, cpv_value, &b_greater);

        pt_cur = (b_less || !b_greater) ? pt_prev->_pt_left : pt_prev->_pt_right;
        while (pt_cur != NULL) {
            pt_prev = pt_cur;
            b_less = b_greater = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
            _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pby_data, &b_less);
            _rb_tree_elem_compare_auxiliary(cpt_rb_tree, pt_prev->_pby_data, cpv_value, &b_greater);

            pt_cur = (b_less || !b_greater) ? pt_prev->_pt_left : pt_prev->_pt_right;
        }

        if (b_less || !b_greater) {
            assert(pt_prev->_pt_left == NULL);
            _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
            assert(_rb_tree_iterator_belong_to_rb_tree(cpt_rb_tree, it_iter));
        } else {
            assert(pt_prev->_pt_right == NULL);
            _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
            it_iter = _rb_tree_iterator_next(it_iter);
        }
    } else {
        it_iter = _rb_tree_end(cpt_rb_tree);
    }

    return it_iter;
}

/**
 * Return an iterator to the first element that is greater than a specific element.
 */
_rb_tree_iterator_t _rb_tree_upper_bound(const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    _rbnode_t*          pt_cur = NULL;
    _rbnode_t*          pt_prev = NULL;
    _rb_tree_iterator_t it_iter;
    bool_t              b_result = false;

    assert(cpt_rb_tree != NULL);
    assert(cpv_value != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    it_iter = _create_rb_tree_iterator();
    _RB_TREE_ITERATOR_TREE_POINTER(it_iter) = (void*)cpt_rb_tree;

    if (!_rb_tree_empty(cpt_rb_tree)) {
        pt_prev = cpt_rb_tree->_t_rbroot._pt_parent;

        b_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
        _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pby_data, &b_result);

        pt_cur = b_result ? pt_prev->_pt_left : pt_prev->_pt_right;
        while (pt_cur != NULL) {
            pt_prev = pt_cur;
            b_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
            _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pby_data, &b_result);

            pt_cur = b_result ? pt_prev->_pt_left : pt_prev->_pt_right;
        }

        if (b_result) {
            assert(pt_prev->_pt_left == NULL);
            _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
            assert(_rb_tree_iterator_belong_to_rb_tree(cpt_rb_tree, it_iter));
        } else {
            assert(pt_prev->_pt_right == NULL);
            _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
            it_iter = _rb_tree_iterator_next(it_iter);
        }
    } else {
        it_iter = _rb_tree_end(cpt_rb_tree);
    }

    return it_iter;
}

/**
 * Return an iterator range that is equal to a specific element.
 */
range_t _rb_tree_equal_range(const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    range_t r_range;

    assert(cpt_rb_tree != NULL);
    assert(cpv_value != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    r_range.it_begin = _rb_tree_lower_bound(cpt_rb_tree, cpv_value);
    r_range.it_end = _rb_tree_upper_bound(cpt_rb_tree, cpv_value);

    return r_range;
}

/**
 * Inserts an element into a rb tree.
 */
_rb_tree_iterator_t _rb_tree_insert_equal(_rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    _rb_tree_iterator_t it_iter = _create_rb_tree_iterator();

    assert(pt_rb_tree != NULL);
    assert(cpv_value != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));

    _RB_TREE_ITERATOR_TREE_POINTER(it_iter) = pt_rb_tree;
    _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)_rb_tree_insert_rbnode(pt_rb_tree, cpv_value);

    pt_rb_tree->_t_rbroot._pt_left = _rb_tree_get_min_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
    pt_rb_tree->_t_rbroot._pt_right = _rb_tree_get_max_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
    pt_rb_tree->_t_nodecount++;

    return it_iter;
}

/**
 * Inserts an unique element into a rb tree.
 */
_rb_tree_iterator_t _rb_tree_insert_unique(_rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    assert(pt_rb_tree != NULL);
    assert(cpv_value != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));

    /* if the rb tree is empty */
    if (_rb_tree_empty(pt_rb_tree)) {
        return _rb_tree_insert_equal(pt_rb_tree, cpv_value);
    } else {
        /* find value in rb tree */
        _rb_tree_iterator_t it_iter = _rb_tree_find(pt_rb_tree, cpv_value);
        /* if the value is exist */
        if (!_rb_tree_iterator_equal(it_iter, _rb_tree_end(pt_rb_tree))) {
            return _rb_tree_end(pt_rb_tree);
        } else {
            /* insert value into rb tree */
            return _rb_tree_insert_equal(pt_rb_tree, cpv_value);
        }
    }
}

/**
 * Inserts an range into a rb tree.
 */
void _rb_tree_insert_equal_range(_rb_tree_t* pt_rb_tree, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));
    assert(_rb_tree_same_iterator_type(pt_rb_tree, it_begin));
    assert(_rb_tree_same_iterator_type(pt_rb_tree, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        _rb_tree_insert_equal(pt_rb_tree, _iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Inserts an array into a rb tree.
 */
void _rb_tree_insert_equal_array(_rb_tree_t* pt_rb_tree, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));
    assert(cpv_array != NULL);

    /*
     * Copy the elements from src array to dest rb tree.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_RB_TREE_TYPE_BASENAME(pt_rb_tree), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);
        for (i = 0; i < t_count; ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            _rb_tree_insert_equal(pt_rb_tree, pstr_elem);
        }
        string_destroy(pstr_elem);
    } else if (_GET_RB_TREE_TYPE_STYLE(pt_rb_tree) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_count; ++i) {
            _rb_tree_insert_equal(pt_rb_tree, (unsigned char*)cpv_array + i * _GET_RB_TREE_TYPE_SIZE(pt_rb_tree));
        }
    } else {
        for (i = 0; i < t_count; ++i) {
            _rb_tree_insert_equal(pt_rb_tree, *((void**)cpv_array + i));
        }
    }
}

/**
 * Inserts an range of unique element into a rb tree.
 */
void _rb_tree_insert_unique_range(_rb_tree_t* pt_rb_tree, iterator_t it_begin, iterator_t it_end)
{
    iterator_t it_iter;

    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));
    assert(_rb_tree_same_iterator_type(pt_rb_tree, it_begin));
    assert(_rb_tree_same_iterator_type(pt_rb_tree, it_end));
    assert(iterator_equal(it_begin, it_end) || _iterator_before(it_begin, it_end));

    for (it_iter = it_begin; !iterator_equal(it_iter, it_end); it_iter = iterator_next(it_iter)) {
        _rb_tree_insert_unique(pt_rb_tree, _iterator_get_pointer_ignore_cstr(it_iter));
    }
}

/**
 * Inserts an array of unique element into a rb tree.
 */
void _rb_tree_insert_unique_array(_rb_tree_t* pt_rb_tree, const void* cpv_array, size_t t_count)
{
    size_t i = 0;

    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));
    assert(cpv_array != NULL);

    /*
     * Copy the elements from src array to dest rb tree.
     * The array of c builtin and user define or cstl builtin are different,
     * the elements of c builtin array are element itself, but the elements of 
     * c string, user define or cstl are pointer of element.
     */
    if (strncmp(_GET_RB_TREE_TYPE_BASENAME(pt_rb_tree), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        /*
         * We need built a string_t for c string element.
         */
        string_t* pstr_elem = create_string();
        assert(pstr_elem != NULL);
        string_init(pstr_elem);
        for (i = 0; i < t_count; ++i) {
            string_assign_cstr(pstr_elem, *((const char**)cpv_array + i));
            _rb_tree_insert_unique(pt_rb_tree, pstr_elem);
        }
        string_destroy(pstr_elem);
    } else if (_GET_RB_TREE_TYPE_STYLE(pt_rb_tree) == _TYPE_C_BUILTIN) {
        for (i = 0; i < t_count; ++i) {
            _rb_tree_insert_unique(pt_rb_tree, (unsigned char*)cpv_array + i * _GET_RB_TREE_TYPE_SIZE(pt_rb_tree));
        }
    } else {
        for (i = 0; i < t_count; ++i) {
            _rb_tree_insert_unique(pt_rb_tree, *((void**)cpv_array + i));
        }
    }
}

/*
 * Erase an element in an rb tree from specificed position.
 */
void _rb_tree_erase_pos(_rb_tree_t* pt_rb_tree, _rb_tree_iterator_t it_pos)
{
    _rbnode_t* pt_parent = NULL;
    _rbnode_t* pt_cur = NULL;
    _rbnode_t* pt_parenttmp = NULL;
    _rbnode_t* pt_curtmp = NULL;
    _color_t   t_colortmp;            /* temporary color for deletion */
    bool_t     b_result = false;

    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));
    assert(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, it_pos));
    assert(!_rb_tree_iterator_equal(it_pos, _rb_tree_end(pt_rb_tree)));
    
    pt_cur = (_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_pos);
    pt_parent = pt_cur->_pt_parent;

    /* delete the current node pointted by it_pos */
    if (pt_cur == pt_parent->_pt_parent) {
        assert(pt_cur == pt_rb_tree->_t_rbroot._pt_parent);
        if (pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL) {
            /*
             *    p         p
             *    |    =>
             *    c
             */
            pt_parent->_pt_parent = NULL;
        } else if (pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL) {
            /*
             *   p         p
             *   |         |
             *   c    =>   l
             *  /
             * l
             */
            pt_parent->_pt_parent = pt_cur->_pt_left;
            pt_parent->_pt_parent->_pt_parent = pt_parent;

            pt_parent->_pt_parent->_t_color = _COLOR_BLACK;
        } else if (pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL) {
            /*
             *    p         p
             *    |         |
             *    c     =>  r
             *     \
             *      r
             */
            pt_parent->_pt_parent = pt_cur->_pt_right;
            pt_parent->_pt_parent->_pt_parent = pt_parent;

            pt_parent->_pt_parent->_t_color = _COLOR_BLACK;
        } else {
            /* 
             * here the real deleted node is pt_curtmp, so the 
             * color of pt_curtmp is used.
             */
            pt_curtmp = _rb_tree_get_min_rbnode(pt_cur->_pt_right);
            t_colortmp = pt_curtmp->_t_color;
            if (pt_cur == pt_curtmp->_pt_parent) {
                /*
                 *   p           p
                 *   |           |
                 *   c     =>    r 
                 *  / \         / \
                 * l   r       l   rr
                 *      \
                 *       rr
                 */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_parent = pt_curtmp;
                pt_curtmp->_t_color = pt_cur->_t_color;
                pt_cur->_t_color = t_colortmp;

                if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                    _rb_tree_fixup_deletion(pt_rb_tree, pt_curtmp->_pt_right, pt_curtmp);
                }
            } else {
                /*
                 *       p                 p
                 *       |                 |
                 *       c         =>      rll
                 *      / \               /  \
                 *     l   r             l    r
                 *        / \                / \
                 *       rl  rr             rl  rr
                 *      / \   \              \   \
                 *     rll rlr rrr           rlr rrr
                 */
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
                pt_curtmp->_t_color = pt_cur->_t_color;
                pt_cur->_t_color = t_colortmp;

                if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                    _rb_tree_fixup_deletion(pt_rb_tree, pt_parenttmp->_pt_left, pt_parenttmp);
                }
            }
        }
    } else if (pt_cur == pt_parent->_pt_left) {
        if (pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL) {
            /*
             *    p         p
             *   /    =>
             *  c
             */
            pt_parent->_pt_left = NULL;

            if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                _rb_tree_fixup_deletion(pt_rb_tree, pt_parent->_pt_left, pt_parent);
            }
        } else if (pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL) {
            /*
             *     p         p
             *    /         /
             *   c    =>   l
             *  /
             * l
             */
            pt_parent->_pt_left = pt_cur->_pt_left;
            pt_parent->_pt_left->_pt_parent = pt_parent;

            if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                _rb_tree_fixup_deletion(pt_rb_tree, pt_parent->_pt_left, pt_parent);
            }
        } else if (pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL) {
            /*
             *      p         p
             *     /         /
             *    c     =>  r
             *     \
             *      r
             */
            pt_parent->_pt_left = pt_cur->_pt_right;
            pt_parent->_pt_left->_pt_parent = pt_parent;

            if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                _rb_tree_fixup_deletion(pt_rb_tree, pt_parent->_pt_left, pt_parent);
            }
        } else {
            /* 
             * here the real deleted node is pt_curtmp, so the 
             * color of pt_curtmp is used.
             */
            pt_curtmp = _rb_tree_get_min_rbnode(pt_cur->_pt_right);
            t_colortmp = pt_curtmp->_t_color;
            if (pt_cur == pt_curtmp->_pt_parent) {
                /*
                 *     p           p
                 *    /           /
                 *   c     =>    r 
                 *  / \         / \
                 * l   r       l   rr
                 *      \
                 *       rr
                 */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_left = pt_curtmp;
                pt_curtmp->_t_color = pt_cur->_t_color;
                pt_cur->_t_color = t_colortmp;

                if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                    _rb_tree_fixup_deletion(pt_rb_tree, pt_curtmp->_pt_right, pt_curtmp);
                }
            } else {
                /*
                 *         p                 p
                 *        /                 /
                 *       c         =>      rll
                 *      / \               /  \
                 *     l   r             l    r
                 *        / \                / \
                 *       rl  rr             rl  rr
                 *      / \   \              \   \
                 *     rll rlr rrr           rlr rrr
                 */
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
                pt_curtmp->_t_color = pt_cur->_t_color;
                pt_cur->_t_color = t_colortmp;

                if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                    _rb_tree_fixup_deletion(pt_rb_tree, pt_parenttmp->_pt_left, pt_parenttmp);
                }
            }
        }
    } else {
        if (pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL) {
            /*
             *  p         p
             *   \    =>
             *    c
             */
            pt_parent->_pt_right = NULL;

            if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                _rb_tree_fixup_deletion(pt_rb_tree, pt_parent->_pt_right, pt_parent);
            }
        } else if (pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL) {
            /*
             * p         p
             *  \         \
             *   c    =>   l
             *  /
             * l
             */
            pt_parent->_pt_right = pt_cur->_pt_left;
            pt_parent->_pt_right->_pt_parent = pt_parent;
 
            if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                _rb_tree_fixup_deletion(pt_rb_tree, pt_parent->_pt_right, pt_parent);
            }
        } else if (pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL) {
            /*
             *  p         p
             *   \         \
             *    c     =>  r
             *     \
             *      r
             */
            pt_parent->_pt_right = pt_cur->_pt_right;
            pt_parent->_pt_right->_pt_parent = pt_parent;

            if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                _rb_tree_fixup_deletion(pt_rb_tree, pt_parent->_pt_right, pt_parent);
            }
        } else {
            /* 
             * here the real deleted node is pt_curtmp, so the 
             * color of pt_curtmp is used.
             */
            pt_curtmp = _rb_tree_get_min_rbnode(pt_cur->_pt_right);
            t_colortmp = pt_curtmp->_t_color;
            if (pt_cur == pt_curtmp->_pt_parent) {
                /*
                 * p           p
                 *  \           \
                 *   c     =>    r 
                 *  / \         / \
                 * l   r       l   rr
                 *      \
                 *       rr
                 */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_right = pt_curtmp;
                pt_curtmp->_t_color = pt_cur->_t_color;
                pt_cur->_t_color = t_colortmp;

                if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                    _rb_tree_fixup_deletion(pt_rb_tree, pt_curtmp->_pt_right, pt_curtmp);
                }
            } else {
                /*
                 *     p                 p
                 *      \                 \
                 *       c         =>      rll
                 *      / \               /  \
                 *     l   r             l    r
                 *        / \                / \
                 *       rl  rr             rl  rr
                 *      / \   \              \   \
                 *     rll rlr rrr           rlr rrr
                 */
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
                pt_curtmp->_t_color = pt_cur->_t_color;
                pt_cur->_t_color = t_colortmp;

                if (_rb_tree_get_color(pt_cur) == _COLOR_BLACK) {
                    _rb_tree_fixup_deletion(pt_rb_tree, pt_parenttmp->_pt_left, pt_parenttmp);
                }
            }
        }
    }

    /* destroy the node */
    b_result = _GET_RB_TREE_TYPE_SIZE(pt_rb_tree);
    _GET_RB_TREE_TYPE_DESTROY_FUNCTION(pt_rb_tree)(pt_cur->_pby_data, &b_result);
    assert(b_result);
    _alloc_deallocate(&pt_rb_tree->_t_allocator, pt_cur, _RB_TREE_NODE_SIZE(_GET_RB_TREE_TYPE_SIZE(pt_rb_tree)), 1);
    pt_rb_tree->_t_nodecount--;
    /* update the left and right pointer */
    if (pt_rb_tree->_t_nodecount == 0) {
        pt_rb_tree->_t_rbroot._pt_parent = NULL;
        pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
        pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;
    } else {
        pt_rb_tree->_t_rbroot._pt_left = _rb_tree_get_min_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
        pt_rb_tree->_t_rbroot._pt_right = _rb_tree_get_max_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
    }
}

/*
 * Erase a range of element in an rb tree.
 */
void _rb_tree_erase_range(_rb_tree_t* pt_rb_tree, _rb_tree_iterator_t it_begin, _rb_tree_iterator_t it_end)
{
    _rb_tree_iterator_t it_iter;
    _rb_tree_iterator_t it_next;

    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));
    assert(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, it_begin));
    assert(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, it_end));
    assert(_rb_tree_iterator_equal(it_begin, it_end) || _rb_tree_iterator_before(it_begin, it_end));

    it_iter = it_next = it_begin;
    if (!_rb_tree_iterator_equal(it_next, _rb_tree_end(pt_rb_tree))) {
        it_next = _rb_tree_iterator_next(it_next);
    }
    while (!_rb_tree_iterator_equal(it_iter, it_end)) {
        _rb_tree_erase_pos(pt_rb_tree, it_iter);
        
        it_iter = it_next;
        if (!_rb_tree_iterator_equal(it_next, _rb_tree_end(pt_rb_tree))) {
            it_next = _rb_tree_iterator_next(it_next);
        }
    }
}

/**
 * Erase an element from a rb tree that match a specified element.
 */
size_t _rb_tree_erase(_rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    size_t  t_count = 0;
    range_t r_range;

    assert(pt_rb_tree != NULL);
    assert(cpv_value != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree));

    t_count = _rb_tree_count(pt_rb_tree, cpv_value);
    r_range = _rb_tree_equal_range(pt_rb_tree, cpv_value);

    if (!_rb_tree_iterator_equal(r_range.it_begin, _rb_tree_end(pt_rb_tree))) {
        _rb_tree_erase_range(pt_rb_tree, r_range.it_begin, r_range.it_end);
    }

    return t_count;
}

/** local function implementation section **/

/** eof **/

