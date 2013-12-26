/*
 *  The implementation of rb tree iterator.
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
 * Create rb tree iterator.
 */
_rb_tree_iterator_t _create_rb_tree_iterator(void)
{
    _rb_tree_iterator_t it_iter;

    _RB_TREE_ITERATOR_COREPOS(it_iter) = NULL;
    _RB_TREE_ITERATOR_TREE_POINTER(it_iter) = NULL;

    _ITERATOR_CONTAINER(it_iter) = NULL;

    return it_iter;
}

/**
 * Test the two rb tree iterator are equal.
 */
bool_t _rb_tree_iterator_equal(_rb_tree_iterator_t it_first, _rb_tree_iterator_t it_second)
{
    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_first), it_first));
    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_second), it_second));
    assert(_RB_TREE_ITERATOR_TREE(it_first) == _RB_TREE_ITERATOR_TREE(it_second));

    return _RB_TREE_ITERATOR_COREPOS(it_first) == _RB_TREE_ITERATOR_COREPOS(it_second) ? true : false;
}

/**
 * Get data value referenced by iterator.
 */
void _rb_tree_iterator_get_value(_rb_tree_iterator_t it_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_rb_tree_iterator_equal(it_iter, _rb_tree_end(_RB_TREE_ITERATOR_TREE(it_iter))));

    /* char* */
    if (strncmp(_GET_RB_TREE_TYPE_BASENAME(_RB_TREE_ITERATOR_TREE(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        *(char**)pv_value = (char*)string_c_str((string_t*)((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        bool_t b_result = _GET_RB_TREE_TYPE_SIZE(_RB_TREE_ITERATOR_TREE(it_iter));
        _GET_RB_TREE_TYPE_COPY_FUNCTION(_RB_TREE_ITERATOR_TREE(it_iter))(
            pv_value, ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_iter))->_pby_data, &b_result);
        assert(b_result);
    }
}

/**
 * Get data value pointer referenced by iterator.
 */
const void* _rb_tree_iterator_get_pointer(_rb_tree_iterator_t it_iter)
{
    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_rb_tree_iterator_equal(it_iter, _rb_tree_end(_RB_TREE_ITERATOR_TREE(it_iter))));

    /* char* */
    if (strncmp(_GET_RB_TREE_TYPE_BASENAME(_RB_TREE_ITERATOR_TREE(it_iter)), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        return (char*)string_c_str((string_t*)((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_iter))->_pby_data);
    } else {
        return ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_iter))->_pby_data;
    }
}

/**
 * Get data value pointer referenced by iterator, but ignore char*.
 */
const void* _rb_tree_iterator_get_pointer_ignore_cstr(_rb_tree_iterator_t it_iter)
{
    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_rb_tree_iterator_equal(it_iter, _rb_tree_end(_RB_TREE_ITERATOR_TREE(it_iter))));

    return ((_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_iter))->_pby_data;
}

/**
 * Return iterator reference next element.
 */
_rb_tree_iterator_t _rb_tree_iterator_next(_rb_tree_iterator_t it_iter)
{
    _rbnode_t* pt_next = NULL;  /* next pos */
    _rbnode_t* pt_cur = (_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_iter);

    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_rb_tree_iterator_equal(it_iter, _rb_tree_end(_RB_TREE_ITERATOR_TREE(it_iter))));

    if (pt_cur->_pt_right != NULL) {
        pt_next = pt_cur->_pt_right;
        while (pt_next->_pt_left != NULL) {
            pt_next = pt_next->_pt_left;
        }

        _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_next;
    } else {
        pt_next = pt_cur->_pt_parent;
        while (pt_cur == pt_next->_pt_right) {
            pt_cur = pt_next;
            pt_next = pt_next->_pt_parent;
        }
        /* 
         * this is special condition, when the next pos is root's parent.
         * when the rb tree has only one node, this condition is came.
         */
        if (pt_cur->_pt_right != pt_next) {
            _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_next;
        } else {
            _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_cur;
        }
    }

    return it_iter;
}

/**
 * Return iterator reference previous element.
 */
_rb_tree_iterator_t _rb_tree_iterator_prev(_rb_tree_iterator_t it_iter)
{
    _rbnode_t* pt_prev = NULL;
    _rbnode_t* pt_cur = (_rbnode_t*)_RB_TREE_ITERATOR_COREPOS(it_iter);

    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_iter), it_iter));
    assert(!_rb_tree_iterator_equal(it_iter, _rb_tree_begin(_RB_TREE_ITERATOR_TREE(it_iter))));

    /* previous end */
    if (_rb_tree_iterator_equal(it_iter, _rb_tree_end(_RB_TREE_ITERATOR_TREE(it_iter)))) {
        _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)_RB_TREE_ITERATOR_TREE(it_iter)->_t_rbroot._pt_right;
    } else {
        if (pt_cur->_pt_left != NULL) {
            pt_prev = pt_cur->_pt_left;
            while (pt_prev->_pt_right != NULL) {
                pt_prev = pt_prev->_pt_right;
            }

            _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
        } else {
            pt_prev = pt_cur->_pt_parent;
            while (pt_cur == pt_prev->_pt_left) {
                pt_cur = pt_prev;
                pt_prev = pt_prev->_pt_parent;
            }

            /* 
             * there is no same special condition as next, because the begin 
             * iterator is the valid iterator 
             */
            _RB_TREE_ITERATOR_COREPOS(it_iter) = (_byte_t*)pt_prev;
        }
    }

    return it_iter;
}

/**
 * Calculate distance between two iterators.
 */
int _rb_tree_iterator_distance(_rb_tree_iterator_t it_first, _rb_tree_iterator_t it_second)
{
    _rb_tree_iterator_t it_iter;
    int                 n_distance = 0;

    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_first), it_first));
    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_second), it_second));
    assert(_RB_TREE_ITERATOR_TREE(it_first) == _RB_TREE_ITERATOR_TREE(it_second));

    if (_rb_tree_iterator_before(it_first, it_second)) {
        for (it_iter = it_first; !_rb_tree_iterator_equal(it_iter, it_second); it_iter = _rb_tree_iterator_next(it_iter)) {
            n_distance++;
        }

        return n_distance;
    } else if (_rb_tree_iterator_before(it_second, it_first)) {
        for (it_iter = it_second; !_rb_tree_iterator_equal(it_iter, it_first); it_iter = _rb_tree_iterator_next(it_iter)) {
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
bool_t _rb_tree_iterator_before(_rb_tree_iterator_t it_first, _rb_tree_iterator_t it_second)
{
    _rb_tree_iterator_t it_iter;
    _rb_tree_iterator_t it_end;
    _rb_tree_t*         pt_rb_tree = NULL;

    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_first), it_first));
    assert(_rb_tree_iterator_belong_to_rb_tree(_RB_TREE_ITERATOR_TREE(it_second), it_second));
    assert(_RB_TREE_ITERATOR_TREE(it_first) == _RB_TREE_ITERATOR_TREE(it_second));

    /* first iterator equal to second iterator */
    if (_RB_TREE_ITERATOR_COREPOS(it_first) == _RB_TREE_ITERATOR_COREPOS(it_second)) {
        return false;
    }
    /* else travel subtree for search second iterator */
    pt_rb_tree = _RB_TREE_ITERATOR_TREE(it_first);
    it_end = _rb_tree_end(pt_rb_tree);
    for (it_iter = it_first;
         !_rb_tree_iterator_equal(it_iter, it_end);
         it_iter = _rb_tree_iterator_next(it_iter)) {
        if (_rb_tree_iterator_equal(it_iter, it_second)) {
            return true;
        }
    }

    return _rb_tree_iterator_equal(it_second, it_end) ? true : false;
}

/** local function implementation section **/

/** eof **/

