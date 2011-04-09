/*
 *  The implementation of avl tree iterator interface.
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

    _GET_AVL_TREE_COREPOS(it_iter) = NULL;
    _GET_AVL_TREE_POINTER(it_iter) = NULL;

    _GET_CONTAINER(it_iter) = NULL;

    return it_iter;
}

bool_t _avl_tree_iterator_equal(
    _avl_tree_iterator_t t_iterfirst, _avl_tree_iterator_t t_itersecond)
{
    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_iterfirst), t_iterfirst));
    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_itersecond), t_itersecond));

    if(_GET_AVL_TREE_COREPOS(t_iterfirst) == _GET_AVL_TREE_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _avl_tree_iterator_get_value(_avl_tree_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_iter), t_iter));
    assert(!_avl_tree_iterator_equal(t_iter, _avl_tree_end(_GET_AVL_TREE(t_iter))));

    /* char* */
    if(strncmp(_GET_AVL_TREE_TYPE_BASENAME(_GET_AVL_TREE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str(
            (string_t*)((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        bool_t t_result = _GET_AVL_TREE_TYPE_SIZE(_GET_AVL_TREE(t_iter));
        _GET_AVL_TREE_TYPE_COPY_FUNCTION(_GET_AVL_TREE(t_iter))(
            pv_value, ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter))->_pc_data, &t_result);
        assert(t_result);
    }
}

const void* _avl_tree_iterator_get_pointer(_avl_tree_iterator_t t_iter)
{
    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_iter), t_iter));
    assert(!_avl_tree_iterator_equal(t_iter, _avl_tree_end(_GET_AVL_TREE(t_iter))));

    /* char* */
    if(strncmp(_GET_AVL_TREE_TYPE_BASENAME(_GET_AVL_TREE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str(
            (string_t*)((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        return ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter))->_pc_data;
    }
}

_avl_tree_iterator_t _avl_tree_iterator_next(_avl_tree_iterator_t t_iter)
{
    _avlnode_t* pt_next = NULL;  /* next pos */
    _avlnode_t* pt_cur = (_avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter);

    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_iter), t_iter));
    assert(!_avl_tree_iterator_equal(t_iter, _avl_tree_end(_GET_AVL_TREE(t_iter))));

    if(pt_cur->_pt_right != NULL)
    {
        pt_next = pt_cur->_pt_right;
        while(pt_next->_pt_left != NULL)
        {
            pt_next = pt_next->_pt_left;
        }

        _GET_AVL_TREE_COREPOS(t_iter) = (char*)pt_next;
    }
    else
    {
        pt_next = pt_cur->_pt_parent;
        while(pt_cur == pt_next->_pt_right)
        {
            pt_cur = pt_next;
            pt_next = pt_next->_pt_parent;
        }
        /* 
         * this is special condition, when the next pos is root's parent.
         * when the avl tree has only one node, this condition is came.
         */
        if(pt_cur->_pt_right != pt_next)
        {
            _GET_AVL_TREE_COREPOS(t_iter) = (char*)pt_next;
        }
        else /* here is special condition */
        {
            _GET_AVL_TREE_COREPOS(t_iter) = (char*)pt_cur;
        }
    }

    return t_iter;
}

_avl_tree_iterator_t _avl_tree_iterator_prev(_avl_tree_iterator_t t_iter)
{
    _avlnode_t* pt_prev = NULL;
    _avlnode_t* pt_cur = (_avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter);

    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_iter), t_iter));
    assert(!_avl_tree_iterator_equal(t_iter, _avl_tree_begin(_GET_AVL_TREE(t_iter))));

    /* previous end */
    if(_avl_tree_iterator_equal(t_iter, _avl_tree_end(_GET_AVL_TREE(t_iter))))
    {
        _GET_AVL_TREE_COREPOS(t_iter) = (char*)_GET_AVL_TREE(t_iter)->_t_avlroot._pt_right;
    }
    else
    {
        if(pt_cur->_pt_left != NULL)
        {
            pt_prev = pt_cur->_pt_left;
            while(pt_prev->_pt_right != NULL)
            {
                pt_prev = pt_prev->_pt_right;
            }

            _GET_AVL_TREE_COREPOS(t_iter) = (char*)pt_prev;
        }
        else
        {
            pt_prev = pt_cur->_pt_parent;
            while(pt_cur == pt_prev->_pt_left)
            {
                pt_cur = pt_prev;
                pt_prev = pt_prev->_pt_parent;
            }

            /* 
             * there is no same special condition as next, because the begin 
             * iterator is the valid iterator 
             */
            _GET_AVL_TREE_COREPOS(t_iter) = (char*)pt_prev;
        }
    }

    return t_iter;
}

int _avl_tree_iterator_distance(
    _avl_tree_iterator_t t_iterfirst, _avl_tree_iterator_t t_itersecond)
{
    _avl_tree_iterator_t t_iterator;
    int                 n_distance = 0;

    if(_avl_tree_iterator_before(t_iterfirst, t_itersecond))
    {
        for(t_iterator = t_iterfirst; 
            !_avl_tree_iterator_equal(t_iterator, t_itersecond);
            t_iterator = _avl_tree_iterator_next(t_iterator))
        {
            n_distance++;
        }

        return n_distance;
    }
    else if(_avl_tree_iterator_before(t_itersecond, t_iterfirst))
    {
        for(t_iterator = t_itersecond;
            !_avl_tree_iterator_equal(t_iterator, t_iterfirst);
            t_iterator = _avl_tree_iterator_next(t_iterator))
        {
            n_distance++;
        }

        return -n_distance;
    }
    else
    {
        return 0;
    }
}

bool_t _avl_tree_iterator_before(
    _avl_tree_iterator_t t_iterfirst, _avl_tree_iterator_t t_itersecond)
{
    _avl_tree_iterator_t t_iterator;
    _avl_tree_t*         pt_avl_tree = NULL;

    assert(_GET_AVL_TREE(t_iterfirst) == _GET_AVL_TREE(t_itersecond));
    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_iterfirst), t_iterfirst) &&
           _avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_itersecond), t_itersecond));
    assert(_GET_AVL_TREE(t_iterfirst) != NULL && _GET_AVL_TREE(t_itersecond) != NULL);
    assert(_GET_AVL_TREE_COREPOS(t_iterfirst) != NULL &&
           _GET_AVL_TREE_COREPOS(t_itersecond) != NULL);

    /* first iterator equal to second iterator */
    if(_GET_AVL_TREE_COREPOS(t_iterfirst) == _GET_AVL_TREE_COREPOS(t_itersecond))
    {
        return false;
    }
    /* else travel subtree for search second iterator */
    pt_avl_tree = _GET_AVL_TREE(t_iterfirst);
    for(t_iterator = t_iterfirst;
        !_avl_tree_iterator_equal(t_iterator, _avl_tree_end(pt_avl_tree));
        t_iterator = _avl_tree_iterator_next(t_iterator))
    {
        if(_avl_tree_iterator_equal(t_iterator, t_itersecond))
        {
            return true;
        }
    }

    if(_avl_tree_iterator_equal(t_itersecond, _avl_tree_end(pt_avl_tree)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** local function implementation section **/

/** eof **/

