/*
 *  The implementation of avl tree iterator interface.
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
 * Create avl tree iterator.
 */
_avl_tree_iterator_t _create_avl_tree_iterator(void)
{
    _avl_tree_iterator_t it_iter;

    _AVL_TREE_ITERATOR_COREPOS(it_iter) = NULL;
    _AVL_TREE_ITERATOR_TREE_POINTER(it_iter) = NULL;

    _ITERATOR_CONTAINER(it_iter) = NULL;

    return it_iter;
}

/**
 * Test the two avl tree iterator are equal.
 */
bool_t _avl_tree_iterator_equal(_avl_tree_iterator_t it_first, _avl_tree_iterator_t it_second)
{
    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_first), it_first));
    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_second), it_second));
    assert(_AVL_TREE_ITERATOR_TREE(it_first) == _AVL_TREE_ITERATOR_TREE(it_second));

    return _AVL_TREE_ITERATOR_COREPOS(it_first) == _AVL_TREE_ITERATOR_COREPOS(it_second) ? true : false;
}

/**
 * Get data value referenced by iterator.
 */
void _avl_tree_iterator_get_value(_avl_tree_iterator_t it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_avl_tree_iterator_equal(it_iter, _avl_tree_end(_AVL_TREE_ITERATOR_TREE(it_iter))));

    /* char* */
    if (strncmp(_GET_AVL_TREE_TYPE_BASENAME(_AVL_TREE_ITERATOR_TREE(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        *(char**)pv_value = (char*)string_c_str((string_t*)((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        bool_t b_result = _GET_AVL_TREE_TYPE_SIZE(_AVL_TREE_ITERATOR_TREE(it_iter));
        _GET_AVL_TREE_TYPE_COPY_FUNCTION(_AVL_TREE_ITERATOR_TREE(it_iter))(
            pv_value, ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_iter))->_pby_data, &b_result);
        assert(b_result);
    }
}

/**
 * Get data value pointer referenced by iterator.
 */
const void* _avl_tree_iterator_get_pointer(_avl_tree_iterator_t it_iter)
{
    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_avl_tree_iterator_equal(it_iter, _avl_tree_end(_AVL_TREE_ITERATOR_TREE(it_iter))));

    /* char* */
    if (strncmp(_GET_AVL_TREE_TYPE_BASENAME(_AVL_TREE_ITERATOR_TREE(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return (char*)string_c_str((string_t*)((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        return ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_iter))->_pby_data;
    }
}

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 */
const void* _avl_tree_iterator_get_pointer_ignore_cstr(_avl_tree_iterator_t it_iter)
{
    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_avl_tree_iterator_equal(it_iter, _avl_tree_end(_AVL_TREE_ITERATOR_TREE(it_iter))));

    return ((_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_iter))->_pby_data;
}

/**
 * Return iterator reference next element.
 */
_avl_tree_iterator_t _avl_tree_iterator_next(_avl_tree_iterator_t it_iter)
{
    _avlnode_t* pt_next = NULL;  /* next pos */
    _avlnode_t* pt_cur = (_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_iter);

    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_avl_tree_iterator_equal(it_iter, _avl_tree_end(_AVL_TREE_ITERATOR_TREE(it_iter))));

    if (pt_cur->_pt_right != NULL) {
        /*
         *        A
         *       / \
         *      B   C
         *     / \   \
         *    D   E   F
         *       /
         *      G
         *  current : B
         *  next    : G
         */
        pt_next = pt_cur->_pt_right;
        while (pt_next->_pt_left != NULL) {
            pt_next = pt_next->_pt_left;
        }

        _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_next;
    } else {
        /*
         *     avlroot
         *        |
         *        A
         *       / \
         *      B   C
         *     / \   \
         *    D   E   F
         *       /
         *      G
         */
        pt_next = pt_cur->_pt_parent;
        while (pt_cur == pt_next->_pt_right) {
            pt_cur = pt_next;
            pt_next = pt_next->_pt_parent;
        }
        /* 
         * this is special condition, when the next pos is root's parent.
         * when the avl tree has only one node, this condition is came.
         */
        if (pt_cur->_pt_right != pt_next) {
            /*
             * current : E or F
             * next    : A or avlroot
             */
            _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_next;
        } else {
            /* here is special condition */
            /*
             *   avlroot
             *      |
             *      A
             */
            _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_cur;
        }
    }

    return it_iter;
}

/**
 * Return iterator reference previous element.
 */
_avl_tree_iterator_t _avl_tree_iterator_prev(_avl_tree_iterator_t it_iter)
{
    _avlnode_t* pt_prev = NULL;
    _avlnode_t* pt_cur = (_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_iter);

    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_avl_tree_iterator_equal(it_iter, _avl_tree_begin(_AVL_TREE_ITERATOR_TREE(it_iter))));

    /* previous end */
    if (_avl_tree_iterator_equal(it_iter, _avl_tree_end(_AVL_TREE_ITERATOR_TREE(it_iter)))) {
        _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)_AVL_TREE_ITERATOR_TREE(it_iter)->_t_avlroot._pt_right;
    } else {
        if (pt_cur->_pt_left != NULL) {
            /*
             *        A
             *       / \
             *      B   C
             *     / \   \
             *    D   E   F
             *       /
             *      G
             *  current  : A
             *  previous : E
             */
            pt_prev = pt_cur->_pt_left;
            while (pt_prev->_pt_right != NULL) {
                pt_prev = pt_prev->_pt_right;
            }

            _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
        } else {
            /*
             *        A
             *       / \
             *      B   C
             *     /   / \
             *    D   E   F
             *       /
             *      G
             * 
             *  current  : G
             *  previous : A
             */
            pt_prev = pt_cur->_pt_parent;
            while (pt_cur == pt_prev->_pt_left) {
                pt_cur = pt_prev;
                pt_prev = pt_prev->_pt_parent;
            }

            /* 
             * there is no same special condition as next, because the begin 
             * iterator is the valid iterator 
             */
            _AVL_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
        }
    }

    return it_iter;
}

/**
 * Calculate distance between two iterators.
 */
int _avl_tree_iterator_distance(_avl_tree_iterator_t it_first, _avl_tree_iterator_t it_second)
{
    _avl_tree_iterator_t it_iter;
    int                  n_distance = 0;

    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_first), it_first));
    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_second), it_second));
    assert(_AVL_TREE_ITERATOR_TREE(it_first) == _AVL_TREE_ITERATOR_TREE(it_second));

    if (_avl_tree_iterator_before(it_first, it_second)) {
        for (it_iter = it_first; !_avl_tree_iterator_equal(it_iter, it_second); it_iter = _avl_tree_iterator_next(it_iter)) {
            n_distance++;
        }

        return n_distance;
    } else if (_avl_tree_iterator_before(it_second, it_first)) {
        for (it_iter = it_second; !_avl_tree_iterator_equal(it_iter, it_first); it_iter = _avl_tree_iterator_next(it_iter)) {
            n_distance++;
        }

        return -n_distance;
    } else {
        return 0;
    }
}

/**
 * Test the first iterator is before the second.
 */
bool_t _avl_tree_iterator_before(_avl_tree_iterator_t it_first, _avl_tree_iterator_t it_second)
{
    _avl_tree_iterator_t it_iter;
    _avl_tree_iterator_t it_end;
    _avl_tree_t*         pt_avl_tree = NULL;

    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_first), it_first));
    assert(_avl_tree_iterator_belong_to_avl_tree(_AVL_TREE_ITERATOR_TREE(it_second), it_second));
    assert(_AVL_TREE_ITERATOR_TREE(it_first) == _AVL_TREE_ITERATOR_TREE(it_second));

    /* first iterator equal to second iterator */
    if (_AVL_TREE_ITERATOR_COREPOS(it_first) == _AVL_TREE_ITERATOR_COREPOS(it_second)) {
        return false;
    }
    /* else travel subtree for search second iterator */
    pt_avl_tree = _AVL_TREE_ITERATOR_TREE(it_first);
    it_end = _avl_tree_end(pt_avl_tree);
    for (it_iter = it_first;
         !_avl_tree_iterator_equal(it_iter, it_end);
         it_iter = _avl_tree_iterator_next(it_iter)) {
        if (_avl_tree_iterator_equal(it_iter, it_second)) {
            return true;
        }
    }

    return _avl_tree_iterator_equal(it_second, it_end) ? true : false;
}

/** local function implementation section **/

/** eof **/

