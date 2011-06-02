/*
 *  The implementation of rb tree.
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

#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>

#include <cstl/cstring.h>

#include "cstl_rb_tree_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* rb tree iterator function */
_rb_tree_iterator_t _create_rb_tree_iterator(void)
{
    _rb_tree_iterator_t t_newiterator;

    _GET_RB_TREE_COREPOS(t_newiterator) = NULL;
    _GET_RB_TREE_POINTER(t_newiterator) = NULL;

    _GET_CONTAINER(t_newiterator) = NULL;

    return t_newiterator;
}

bool_t _rb_tree_iterator_equal(
    _rb_tree_iterator_t t_iterfirst, _rb_tree_iterator_t t_itersecond)
{
    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_iterfirst), t_iterfirst));
    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_itersecond), t_itersecond));

    if(_GET_RB_TREE_COREPOS(t_iterfirst) == _GET_RB_TREE_COREPOS(t_itersecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _rb_tree_iterator_get_value(_rb_tree_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_iter), t_iter));
    assert(!_rb_tree_iterator_equal(t_iter, _rb_tree_end(_GET_RB_TREE(t_iter))));

    /* char* */
    if(strncmp(_GET_RB_TREE_TYPE_BASENAME(_GET_RB_TREE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str(
            (string_t*)((_rbnode_t*)_GET_RB_TREE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        bool_t t_result = _GET_RB_TREE_TYPE_SIZE(_GET_RB_TREE(t_iter));
        _GET_RB_TREE_TYPE_COPY_FUNCTION(_GET_RB_TREE(t_iter))(
            pv_value, ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_iter))->_pc_data, &t_result);
        assert(t_result);
    }
}

const void* _rb_tree_iterator_get_pointer(_rb_tree_iterator_t t_iter)
{
    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_iter), t_iter));
    assert(!_rb_tree_iterator_equal(t_iter, _rb_tree_end(_GET_RB_TREE(t_iter))));

    /* char* */
    if(strncmp(_GET_RB_TREE_TYPE_BASENAME(_GET_RB_TREE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str(
            (string_t*)((_rbnode_t*)_GET_RB_TREE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        return ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_iter))->_pc_data;
    }
}

_rb_tree_iterator_t _rb_tree_iterator_next(_rb_tree_iterator_t t_iter)
{
    _rbnode_t* pt_next = NULL;  /* next pos */
    _rbnode_t* pt_cur = (_rbnode_t*)_GET_RB_TREE_COREPOS(t_iter);

    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_iter), t_iter));
    assert(!_rb_tree_iterator_equal(t_iter, _rb_tree_end(_GET_RB_TREE(t_iter))));

    if(pt_cur->_pt_right != NULL)
    {
        pt_next = pt_cur->_pt_right;
        while(pt_next->_pt_left != NULL)
        {
            pt_next = pt_next->_pt_left;
        }

        _GET_RB_TREE_COREPOS(t_iter) = (char*)pt_next;
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
         * when the rb tree has only one node, this condition is came.
         */
        if(pt_cur->_pt_right != pt_next)
        {
            _GET_RB_TREE_COREPOS(t_iter) = (char*)pt_next;
        }
        else /* here is special condition */
        {
            _GET_RB_TREE_COREPOS(t_iter) = (char*)pt_cur;
        }
    }

    return t_iter;
}

_rb_tree_iterator_t _rb_tree_iterator_prev(_rb_tree_iterator_t t_iter)
{
    _rbnode_t* pt_prev = NULL;
    _rbnode_t* pt_cur = (_rbnode_t*)_GET_RB_TREE_COREPOS(t_iter);

    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_iter), t_iter));
    assert(!_rb_tree_iterator_equal(t_iter, _rb_tree_begin(_GET_RB_TREE(t_iter))));

    /* previous end */
    if(_rb_tree_iterator_equal(t_iter, _rb_tree_end(_GET_RB_TREE(t_iter))))
    {
        _GET_RB_TREE_COREPOS(t_iter) = (char*)_GET_RB_TREE(t_iter)->_t_rbroot._pt_right;
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

            _GET_RB_TREE_COREPOS(t_iter) = (char*)pt_prev;
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
            _GET_RB_TREE_COREPOS(t_iter) = (char*)pt_prev;
        }
    }

    return t_iter;
}

int _rb_tree_iterator_distance(
    _rb_tree_iterator_t t_iterfirst, _rb_tree_iterator_t t_itersecond)
{
    _rb_tree_iterator_t t_iterator;
    int                n_distance = 0;

    if(_rb_tree_iterator_before(t_iterfirst, t_itersecond))
    {
        for(t_iterator = t_iterfirst; 
            !_rb_tree_iterator_equal(t_iterator, t_itersecond);
            t_iterator = _rb_tree_iterator_next(t_iterator))
        {
            n_distance++;
        }

        return n_distance;
    }
    else if(_rb_tree_iterator_before(t_itersecond, t_iterfirst))
    {
        for(t_iterator = t_itersecond;
            !_rb_tree_iterator_equal(t_iterator, t_iterfirst);
            t_iterator = _rb_tree_iterator_next(t_iterator))
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

bool_t _rb_tree_iterator_before(
    _rb_tree_iterator_t t_iterfirst, _rb_tree_iterator_t t_itersecond)
{
    _rb_tree_iterator_t t_iterator;
    _rb_tree_t*         pt_rb_tree = NULL;

    assert(_GET_RB_TREE(t_iterfirst) == _GET_RB_TREE(t_itersecond));
    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_iterfirst), t_iterfirst) &&
           _rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_itersecond), t_itersecond));
    assert(_GET_RB_TREE(t_iterfirst) != NULL &&
           _GET_RB_TREE(t_itersecond) != NULL);
    assert(_GET_RB_TREE_COREPOS(t_iterfirst) != NULL &&
           _GET_RB_TREE_COREPOS(t_itersecond) != NULL);

    /* first iterator equal to second iterator */
    if(_GET_RB_TREE_COREPOS(t_iterfirst) == _GET_RB_TREE_COREPOS(t_itersecond))
    {
        return false;
    }
    /* else travel subtree for search second iterator */
    pt_rb_tree = _GET_RB_TREE(t_iterfirst);
    for(t_iterator = t_iterfirst;
        !_rb_tree_iterator_equal(t_iterator, _rb_tree_end(pt_rb_tree));
        t_iterator = _rb_tree_iterator_next(t_iterator))
    {
        if(_rb_tree_iterator_equal(t_iterator, t_itersecond))
        {
            return true;
        }
    }

    if(_rb_tree_iterator_equal(t_itersecond, _rb_tree_end(pt_rb_tree)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* rb tree private function */
_rb_tree_t* _create_rb_tree(const char* s_typename)
{
    _rb_tree_t*  pt_newrbtree = NULL;

    if((pt_newrbtree = (_rb_tree_t*)malloc(sizeof(_rb_tree_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_rb_tree_auxiliary(pt_newrbtree, s_typename))
    {
        free(pt_newrbtree);
        return NULL;
    }

    return pt_newrbtree;
}

bool_t _create_rb_tree_auxiliary(_rb_tree_t* pt_rb_tree, const char* s_typename)
{
    /* get type information */
    _type_get_type(&pt_rb_tree->_t_typeinfo, s_typename);
    if(pt_rb_tree->_t_typeinfo._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    pt_rb_tree->_t_rbroot._pt_left = NULL;
    pt_rb_tree->_t_rbroot._pt_right = NULL;
    pt_rb_tree->_t_rbroot._t_color = red;
    pt_rb_tree->_t_nodecount = 0;

    pt_rb_tree->_t_compare = NULL;

    _alloc_init(&pt_rb_tree->_t_allocator);
    return true;
}

void _rb_tree_init(_rb_tree_t* pt_rb_tree, binary_function_t t_compare)
{
    assert(pt_rb_tree != NULL &&
           pt_rb_tree->_t_nodecount == 0 &&
           pt_rb_tree->_t_rbroot._pt_parent == NULL &&
           pt_rb_tree->_t_rbroot._pt_left == NULL &&
           pt_rb_tree->_t_rbroot._pt_right == NULL && 
           pt_rb_tree->_t_rbroot._t_color == red &&
           pt_rb_tree->_t_compare == NULL);

    pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;

    if(t_compare != NULL)
    {
        pt_rb_tree->_t_compare = t_compare;
    }
    else
    {
        pt_rb_tree->_t_compare = _GET_RB_TREE_TYPE_LESS_FUNCTION(pt_rb_tree);
    }
}

void _rb_tree_destroy_auxiliary(_rb_tree_t* pt_rb_tree)
{
    assert(pt_rb_tree != NULL);

    /* destroy all elements */
    pt_rb_tree->_t_rbroot._pt_parent =
        _destroy_rb_tree(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent);
    assert(pt_rb_tree->_t_rbroot._pt_parent == NULL);
    pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_nodecount = 0;

    /* destroy allocator */
    _alloc_destroy(&pt_rb_tree->_t_allocator);

    pt_rb_tree->_t_compare = NULL;
}

void _rb_tree_destroy(_rb_tree_t* pt_rb_tree)
{
    _rb_tree_destroy_auxiliary(pt_rb_tree);
    free(pt_rb_tree);
}

void _rb_tree_init_copy(
    _rb_tree_t* pt_rb_tree_dest, const _rb_tree_t* cpt_rb_tree_src)
{
    assert(pt_rb_tree_dest != NULL && cpt_rb_tree_src != NULL);
    assert(pt_rb_tree_dest->_t_typeinfo._pt_type == cpt_rb_tree_src->_t_typeinfo._pt_type);

    /* init the rb tree with the src rb tree */
    _rb_tree_init(pt_rb_tree_dest, cpt_rb_tree_src->_t_compare);
    /* insert all elements of src into dest */
    if(!_rb_tree_empty(cpt_rb_tree_src))
    {
        _rb_tree_insert_equal_range(pt_rb_tree_dest,
            _rb_tree_begin(cpt_rb_tree_src), _rb_tree_end(cpt_rb_tree_src));
    }
}

void _rb_tree_init_copy_range(
    _rb_tree_t* pt_rb_tree_dest, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end)
{
    assert(pt_rb_tree_dest != NULL);
    assert(pt_rb_tree_dest->_t_typeinfo._pt_type ==
           _GET_RB_TREE(t_begin)->_t_typeinfo._pt_type);
    assert(_rb_tree_iterator_equal(t_begin, t_end) ||
           _rb_tree_iterator_before(t_begin, t_end));

    /* init the rb tree with the src rb tree */
    _rb_tree_init(pt_rb_tree_dest,
        _GET_RB_TREE_TYPE_LESS_FUNCTION(_GET_RB_TREE(t_begin)));
    /* insert all elements of src into dest */
    if(!_rb_tree_empty(_GET_RB_TREE(t_begin)))
    {
        _rb_tree_insert_equal_range(pt_rb_tree_dest, t_begin, t_end);
    }
}

void _rb_tree_init_copy_range_ex(
    _rb_tree_t* pt_rb_tree_dest, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end,
    binary_function_t t_compare)
{
    assert(pt_rb_tree_dest != NULL);
    assert(pt_rb_tree_dest->_t_typeinfo._pt_type ==
           _GET_RB_TREE(t_begin)->_t_typeinfo._pt_type);
    assert(_rb_tree_iterator_equal(t_begin, t_end) ||
           _rb_tree_iterator_before(t_begin, t_end));

    /* init the rb tree with the src rb tree */
    _rb_tree_init(pt_rb_tree_dest, t_compare);
    /* insert all elements of src into dest */
    if(!_rb_tree_empty(_GET_RB_TREE(t_begin)))
    {
        _rb_tree_insert_equal_range(pt_rb_tree_dest, t_begin, t_end);
    }
}

void _rb_tree_assign(_rb_tree_t* pt_rb_tree_dest, const _rb_tree_t* cpt_rb_tree_src)
{
    assert(_rb_tree_same_type(pt_rb_tree_dest, cpt_rb_tree_src));

    /* clear dest rb tree */
    _rb_tree_clear(pt_rb_tree_dest);
    /* insert all elements of src into dest */
    if(!_rb_tree_empty(cpt_rb_tree_src))
    {
        _rb_tree_insert_equal_range(pt_rb_tree_dest,
            _rb_tree_begin(cpt_rb_tree_src), _rb_tree_end(cpt_rb_tree_src));
    }
}

bool_t _rb_tree_empty(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    if(cpt_rb_tree->_t_nodecount == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t _rb_tree_size(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    return cpt_rb_tree->_t_nodecount;
}

size_t _rb_tree_max_size(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    return (size_t)(-1) / _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
}

_rb_tree_iterator_t _rb_tree_begin(const _rb_tree_t* cpt_rb_tree)
{
    _rb_tree_iterator_t t_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _GET_RB_TREE_POINTER(t_newiterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_newiterator) = (char*)cpt_rb_tree->_t_rbroot._pt_left;

    return t_newiterator;
}

_rb_tree_iterator_t _rb_tree_end(const _rb_tree_t* cpt_rb_tree)
{
    _rb_tree_iterator_t t_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _GET_RB_TREE_POINTER(t_newiterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_newiterator) = (char*)&cpt_rb_tree->_t_rbroot;

    return t_newiterator;
}

_rb_tree_iterator_t _rb_tree_rend(const _rb_tree_t* cpt_rb_tree)
{
    _rb_tree_iterator_t t_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _GET_RB_TREE_POINTER(t_newiterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_newiterator) = (char*)&cpt_rb_tree->_t_rbroot;

    return t_newiterator;
}

_rb_tree_iterator_t _rb_tree_rbegin(const _rb_tree_t* cpt_rb_tree)
{
    _rb_tree_iterator_t t_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _GET_RB_TREE_POINTER(t_newiterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_newiterator) = (char*)cpt_rb_tree->_t_rbroot._pt_right;

    return t_newiterator;
}

binary_function_t _rb_tree_key_comp(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    return cpt_rb_tree->_t_compare;
}

_rb_tree_iterator_t _rb_tree_find(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    _rb_tree_iterator_t t_iterator;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    _GET_RB_TREE_POINTER(t_iterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_iterator) = (char*)_find_value(
        cpt_rb_tree, cpt_rb_tree->_t_rbroot._pt_parent, cpv_value);
    if(_GET_RB_TREE_COREPOS(t_iterator) == NULL)
    {
        _GET_RB_TREE_COREPOS(t_iterator) = (char*)&cpt_rb_tree->_t_rbroot;
    }

    return t_iterator;
}

void _rb_tree_clear(_rb_tree_t* pt_rb_tree)
{
    assert(pt_rb_tree != NULL);

    pt_rb_tree->_t_rbroot._pt_parent = _destroy_rb_tree(
        pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent);
    assert(pt_rb_tree->_t_rbroot._pt_parent == NULL);
    pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_nodecount = 0;
}

bool_t _rb_tree_equal(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond)
{
    _rb_tree_iterator_t t_first;
    _rb_tree_iterator_t t_second;
    bool_t             t_less = false;
    bool_t             t_greater = false;

    assert(cpt_rb_treefirst != NULL && cpt_rb_treesecond != NULL);
    
    /* test type */
    if(!_rb_tree_same_type(cpt_rb_treefirst, cpt_rb_treesecond))
    {
        return false;
    }
    /* test rb tree size */
    if(_rb_tree_size(cpt_rb_treefirst) != _rb_tree_size(cpt_rb_treesecond))
    {
        return false;
    }
    /* test each element */
    for(t_first = _rb_tree_begin(cpt_rb_treefirst), 
        t_second = _rb_tree_begin(cpt_rb_treesecond);
        !_rb_tree_iterator_equal(t_first, _rb_tree_end(cpt_rb_treefirst)) &&
        !_rb_tree_iterator_equal(t_second, _rb_tree_end(cpt_rb_treesecond));
        t_first = _rb_tree_iterator_next(t_first),
        t_second = _rb_tree_iterator_next(t_second))
    {
        t_less = t_greater = _GET_RB_TREE_TYPE_SIZE(cpt_rb_treefirst);
        _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_rb_treefirst)(
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data,
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data, &t_less);
        _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_rb_treefirst)(
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data,
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data, &t_greater);
        if(t_less || t_greater)
        {
            return false;
        }
    }

    assert(_rb_tree_iterator_equal(t_first, _rb_tree_end(cpt_rb_treefirst)) &&
           _rb_tree_iterator_equal(t_second, _rb_tree_end(cpt_rb_treesecond)));

    return true;
}

bool_t _rb_tree_not_equal(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond)
{
    return!_rb_tree_equal(cpt_rb_treefirst, cpt_rb_treesecond);
}

bool_t _rb_tree_less(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond)
{
    _rb_tree_iterator_t t_first;
    _rb_tree_iterator_t t_second;
    bool_t             t_result = false;

    assert(_rb_tree_same_type(cpt_rb_treefirst, cpt_rb_treesecond));

    /* test each element */
    for(t_first = _rb_tree_begin(cpt_rb_treefirst), 
        t_second = _rb_tree_begin(cpt_rb_treesecond);
        !_rb_tree_iterator_equal(t_first, _rb_tree_end(cpt_rb_treefirst)) &&
        !_rb_tree_iterator_equal(t_second, _rb_tree_end(cpt_rb_treesecond));
        t_first = _rb_tree_iterator_next(t_first),
        t_second = _rb_tree_iterator_next(t_second))
    {
        t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_treefirst);
        _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_rb_treefirst)(
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data,
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data, &t_result);
        if(t_result)
        {
            return true;
        }

        t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_treefirst);
        _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_rb_treefirst)(
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data,
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data, &t_result);
        if(t_result)
        {
            return false;
        }
    }

    if(_rb_tree_size(cpt_rb_treefirst) < _rb_tree_size(cpt_rb_treesecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _rb_tree_less_equal(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond)
{
    return (_rb_tree_less(cpt_rb_treefirst, cpt_rb_treesecond) ||
            _rb_tree_equal(cpt_rb_treefirst, cpt_rb_treesecond)) ? true : false;
}

bool_t _rb_tree_greater(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond)
{
    return _rb_tree_less(cpt_rb_treesecond, cpt_rb_treefirst);
}

bool_t _rb_tree_greater_equal(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond)
{
    return (_rb_tree_greater(cpt_rb_treefirst, cpt_rb_treesecond) ||
            _rb_tree_equal(cpt_rb_treefirst, cpt_rb_treesecond)) ? true : false;
}

void _rb_tree_swap(_rb_tree_t* pt_rb_treefirst, _rb_tree_t* pt_rb_treesecond)
{
    _rb_tree_t t_rb_treetmp;

    assert(pt_rb_treefirst != NULL && pt_rb_treesecond != NULL);

    t_rb_treetmp = *pt_rb_treefirst;
    *pt_rb_treefirst = *pt_rb_treesecond;
    *pt_rb_treesecond = t_rb_treetmp;

    if(_rb_tree_empty(pt_rb_treefirst))
    {
        pt_rb_treefirst->_t_rbroot._pt_left = &pt_rb_treefirst->_t_rbroot;
        pt_rb_treefirst->_t_rbroot._pt_right = &pt_rb_treefirst->_t_rbroot;
    }
    else
    {
        pt_rb_treefirst->_t_rbroot._pt_parent->_pt_parent = 
            &pt_rb_treefirst->_t_rbroot;
    }

    if(_rb_tree_empty(pt_rb_treesecond))
    {
        pt_rb_treesecond->_t_rbroot._pt_left = &pt_rb_treesecond->_t_rbroot;
        pt_rb_treesecond->_t_rbroot._pt_right = &pt_rb_treesecond->_t_rbroot;
    }
    else
    {
        pt_rb_treesecond->_t_rbroot._pt_parent->_pt_parent = 
            &pt_rb_treesecond->_t_rbroot;
    }
}

size_t _rb_tree_count(const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    range_t t_range;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    t_range = _rb_tree_equal_range(cpt_rb_tree, cpv_value);

    return abs(_rb_tree_iterator_distance(t_range.it_begin, t_range.it_end));
}

_rb_tree_iterator_t _rb_tree_lower_bound(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    _rbnode_t*          pt_cur = NULL;
    _rbnode_t*          pt_prev = NULL;
    _rb_tree_iterator_t t_iterator;
    bool_t             t_less = false;
    bool_t             t_greater = false;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    t_iterator = _create_rb_tree_iterator();
    _GET_RB_TREE_POINTER(t_iterator) = (void*)cpt_rb_tree;

    if(!_rb_tree_empty(cpt_rb_tree))
    {
        pt_prev = cpt_rb_tree->_t_rbroot._pt_parent;

        t_less = t_greater = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
        _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pc_data, &t_less);
        _rb_tree_elem_compare_auxiliary(cpt_rb_tree, pt_prev->_pc_data, cpv_value, &t_greater);
        if(t_less || !t_greater)
        {
            pt_cur = pt_prev->_pt_left;
        }
        else
        {
            pt_cur = pt_prev->_pt_right;
        }
        while(pt_cur != NULL)
        {
            pt_prev = pt_cur;
            t_less = t_greater = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
            _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pc_data, &t_less);
            _rb_tree_elem_compare_auxiliary(cpt_rb_tree, pt_prev->_pc_data, cpv_value, &t_greater);
            if(t_less || !t_greater)
            {
                pt_cur = pt_prev->_pt_left;
            }
            else
            {
                pt_cur = pt_prev->_pt_right;
            }
        }

        if(t_less || !t_greater)
        {
            assert(pt_prev->_pt_left == NULL);
            _GET_RB_TREE_COREPOS(t_iterator) = (char*)pt_prev;
            assert(_rb_tree_iterator_belong_to_rb_tree(cpt_rb_tree, t_iterator));
        }
        else
        {
            assert(pt_prev->_pt_right == NULL);
            _GET_RB_TREE_COREPOS(t_iterator) = (char*)pt_prev;
            t_iterator = _rb_tree_iterator_next(t_iterator);
        }
    }
    else
    {
        t_iterator = _rb_tree_end(cpt_rb_tree);
    }

    return t_iterator;
}

_rb_tree_iterator_t _rb_tree_upper_bound(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    _rbnode_t*          pt_cur = NULL;
    _rbnode_t*          pt_prev = NULL;
    _rb_tree_iterator_t t_iterator;
    bool_t             t_result = false;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    t_iterator = _create_rb_tree_iterator();
    _GET_RB_TREE_POINTER(t_iterator) = (void*)cpt_rb_tree;

    if(!_rb_tree_empty(cpt_rb_tree))
    {
        pt_prev = cpt_rb_tree->_t_rbroot._pt_parent;

        t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
        _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pc_data, &t_result);
        if(t_result)
        {
            pt_cur = pt_prev->_pt_left;
        }
        else
        {
            pt_cur = pt_prev->_pt_right;
        }
        while(pt_cur != NULL)
        {
            pt_prev = pt_cur;
            t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
            _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pc_data, &t_result);
            if(t_result)
            {
                pt_cur = pt_prev->_pt_left;
            }
            else
            {
                pt_cur = pt_prev->_pt_right;
            }
        }

        if(t_result)
        {
            assert(pt_prev->_pt_left == NULL);
            _GET_RB_TREE_COREPOS(t_iterator) = (char*)pt_prev;
            assert(_rb_tree_iterator_belong_to_rb_tree(cpt_rb_tree, t_iterator));
        }
        else
        {
            assert(pt_prev->_pt_right == NULL);
            _GET_RB_TREE_COREPOS(t_iterator) = (char*)pt_prev;
            t_iterator = _rb_tree_iterator_next(t_iterator);
        }
    }
    else
    {
        t_iterator = _rb_tree_end(cpt_rb_tree);
    }

    return t_iterator;
}

range_t _rb_tree_equal_range(const _rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    range_t t_range;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    t_range.it_begin = _rb_tree_lower_bound(cpt_rb_tree, cpv_value);
    t_range.it_end = _rb_tree_upper_bound(cpt_rb_tree, cpv_value);

    return t_range;
}

_rb_tree_iterator_t _rb_tree_insert_equal(_rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    _rb_tree_iterator_t t_iterator = _create_rb_tree_iterator();

    assert(pt_rb_tree != NULL && cpv_value != NULL);

    _GET_RB_TREE_POINTER(t_iterator) = pt_rb_tree;
    _GET_RB_TREE_COREPOS(t_iterator) = (char*)_insert_rbnode(pt_rb_tree, cpv_value);

    pt_rb_tree->_t_rbroot._pt_left = _get_min_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
    pt_rb_tree->_t_rbroot._pt_right = _get_max_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
    pt_rb_tree->_t_nodecount++;

    return t_iterator;
}

_rb_tree_iterator_t _rb_tree_insert_unique(_rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    assert(pt_rb_tree != NULL && cpv_value != NULL);

    /* if the rb tree is empty */
    if(_rb_tree_empty(pt_rb_tree))
    {
        return _rb_tree_insert_equal(pt_rb_tree, cpv_value);
    }
    else
    {
        /* find value in rb tree */
        _rb_tree_iterator_t t_iter = _rb_tree_find(pt_rb_tree, cpv_value);
        /* if the value is exist */
        if(!_rb_tree_iterator_equal(t_iter, _rb_tree_end(pt_rb_tree)))
        {
            return _rb_tree_end(pt_rb_tree);
        }
        else
        {
            /* insert value into rb tree */
            return _rb_tree_insert_equal(pt_rb_tree, cpv_value);
        }
    }
}

void _rb_tree_insert_equal_range(
    _rb_tree_t* pt_rb_tree, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end)
{
    _rb_tree_iterator_t t_iterator;

    assert(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, t_begin));
    assert(_rb_tree_iterator_equal(t_begin, t_end) ||
           _rb_tree_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_rb_tree_iterator_equal(t_iterator, t_end);
        t_iterator = _rb_tree_iterator_next(t_iterator))
    {
        _rb_tree_insert_equal(pt_rb_tree, 
            ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_iterator))->_pc_data);
    }
}

void _rb_tree_insert_unique_range(
    _rb_tree_t* pt_rb_tree, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end)
{
    _rb_tree_iterator_t t_iterator;

    assert(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, t_begin));
    assert(_rb_tree_iterator_equal(t_begin, t_end) ||
           _rb_tree_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_rb_tree_iterator_equal(t_iterator, t_end);
        t_iterator = _rb_tree_iterator_next(t_iterator))
    {
        _rb_tree_insert_unique(
            pt_rb_tree, ((_rbnode_t*)_GET_RB_TREE_COREPOS(t_iterator))->_pc_data);
    }
}

void _rb_tree_erase_pos(_rb_tree_t* pt_rb_tree, _rb_tree_iterator_t t_pos)
{
    _rbnode_t* pt_parent = NULL;
    _rbnode_t* pt_cur = NULL;
    _rbnode_t* pt_parenttmp = NULL;
    _rbnode_t* pt_curtmp = NULL;
    color_t   t_colortmp;            /* temporary color for deletion */
    bool_t    t_result = false;

    assert(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, t_pos));
    assert(!_rb_tree_iterator_equal(t_pos, _rb_tree_end(pt_rb_tree)));
    
    pt_cur = (_rbnode_t*)_GET_RB_TREE_COREPOS(t_pos);
    pt_parent = pt_cur->_pt_parent;

    /* delete the current node pointted by t_pos */
    if(pt_cur == pt_parent->_pt_parent)
    {
        assert(pt_cur == pt_rb_tree->_t_rbroot._pt_parent);
        if(pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL)
        {
            /*
             *    p         p
             *    |    =>
             *    c
             */
            pt_parent->_pt_parent = NULL;
        }
        else if(pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL)
        {
            /*
             *   p         p
             *   |         |
             *   c    =>   l
             *  /
             * l
             */
            pt_parent->_pt_parent = pt_cur->_pt_left;
            pt_parent->_pt_parent->_pt_parent = pt_parent;

            pt_parent->_pt_parent->_t_color = black;
        }
        else if(pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL)
        {
            /*
             *    p         p
             *    |         |
             *    c     =>  r
             *     \
             *      r
             */
            pt_parent->_pt_parent = pt_cur->_pt_right;
            pt_parent->_pt_parent->_pt_parent = pt_parent;

            pt_parent->_pt_parent->_t_color = black;
        }
        else
        {
            /* 
             * here the real deleted node is pt_curtmp, so the 
             * color of pt_curtmp is used.
             */
            pt_curtmp = _get_min_rbnode(pt_cur->_pt_right);
            t_colortmp = pt_curtmp->_t_color;
            if(pt_cur == pt_curtmp->_pt_parent)
            {
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

                if(_get_color(pt_cur) == black)
                {
                    _fixup_deletion(pt_rb_tree, pt_curtmp->_pt_right, pt_curtmp);
                }
            }
            else
            {
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
                if(pt_parenttmp->_pt_left != NULL)
                {
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

                if(_get_color(pt_cur) == black)
                {
                    _fixup_deletion(pt_rb_tree, pt_parenttmp->_pt_left, pt_parenttmp);
                }
            }
        }
    }
    else if(pt_cur == pt_parent->_pt_left)
    {
        if(pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL)
        {
            /*
             *    p         p
             *   /    =>
             *  c
             */
            pt_parent->_pt_left = NULL;

            if(_get_color(pt_cur) == black)
            {
                _fixup_deletion(pt_rb_tree, pt_parent->_pt_left, pt_parent);
            }
        }
        else if(pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL)
        {
            /*
             *     p         p
             *    /         /
             *   c    =>   l
             *  /
             * l
             */
            pt_parent->_pt_left = pt_cur->_pt_left;
            pt_parent->_pt_left->_pt_parent = pt_parent;

            if(_get_color(pt_cur) == black)
            {
                _fixup_deletion(pt_rb_tree, pt_parent->_pt_left, pt_parent);
            }
        }
        else if(pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL)
        {
            /*
             *      p         p
             *     /         /
             *    c     =>  r
             *     \
             *      r
             */
            pt_parent->_pt_left = pt_cur->_pt_right;
            pt_parent->_pt_left->_pt_parent = pt_parent;

            if(_get_color(pt_cur) == black)
            {
                _fixup_deletion(pt_rb_tree, pt_parent->_pt_left, pt_parent);
            }
        }
        else
        {
            /* 
             * here the real deleted node is pt_curtmp, so the 
             * color of pt_curtmp is used.
             */
            pt_curtmp = _get_min_rbnode(pt_cur->_pt_right);
            t_colortmp = pt_curtmp->_t_color;
            if(pt_cur == pt_curtmp->_pt_parent)
            {
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

                if(_get_color(pt_cur) == black)
                {
                    _fixup_deletion(pt_rb_tree, pt_curtmp->_pt_right, pt_curtmp);
                }
            }
            else
            {
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
                if(pt_parenttmp->_pt_left != NULL)
                {
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

                if(_get_color(pt_cur) == black)
                {
                    _fixup_deletion(pt_rb_tree, pt_parenttmp->_pt_left, pt_parenttmp);
                }
            }
        }
    }
    else
    {
        if(pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL)
        {
            /*
             *  p         p
             *   \    =>
             *    c
             */
            pt_parent->_pt_right = NULL;

            if(_get_color(pt_cur) == black)
            {
                _fixup_deletion(pt_rb_tree, pt_parent->_pt_right, pt_parent);
            }
        }
        else if(pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL)
        {
            /*
             * p         p
             *  \         \
             *   c    =>   l
             *  /
             * l
             */
            pt_parent->_pt_right = pt_cur->_pt_left;
            pt_parent->_pt_right->_pt_parent = pt_parent;
 
            if(_get_color(pt_cur) == black)
            {
                _fixup_deletion(pt_rb_tree, pt_parent->_pt_right, pt_parent);
            }
        }
        else if(pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL)
        {
            /*
             *  p         p
             *   \         \
             *    c     =>  r
             *     \
             *      r
             */
            pt_parent->_pt_right = pt_cur->_pt_right;
            pt_parent->_pt_right->_pt_parent = pt_parent;

            if(_get_color(pt_cur) == black)
            {
                _fixup_deletion(pt_rb_tree, pt_parent->_pt_right, pt_parent);
            }
        }
        else
        {
            /* 
             * here the real deleted node is pt_curtmp, so the 
             * color of pt_curtmp is used.
             */
            pt_curtmp = _get_min_rbnode(pt_cur->_pt_right);
            t_colortmp = pt_curtmp->_t_color;
            if(pt_cur == pt_curtmp->_pt_parent)
            {
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

                if(_get_color(pt_cur) == black)
                {
                    _fixup_deletion(pt_rb_tree, pt_curtmp->_pt_right, pt_curtmp);
                }
            }
            else
            {
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
                if(pt_parenttmp->_pt_left != NULL)
                {
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

                if(_get_color(pt_cur) == black)
                {
                    _fixup_deletion(pt_rb_tree, pt_parenttmp->_pt_left, pt_parenttmp);
                }
            }
        }
    }

    /* destroy the node */
    t_result = _GET_RB_TREE_TYPE_SIZE(pt_rb_tree);
    _GET_RB_TREE_TYPE_DESTROY_FUNCTION(pt_rb_tree)(pt_cur->_pc_data, &t_result);
    assert(t_result);
    _alloc_deallocate(&pt_rb_tree->_t_allocator, pt_cur, 
        _RB_TREE_NODE_SIZE(_GET_RB_TREE_TYPE_SIZE(pt_rb_tree)), 1);
    pt_rb_tree->_t_nodecount--;
    /* update the left and right pointer */
    if(pt_rb_tree->_t_nodecount == 0)
    {
        pt_rb_tree->_t_rbroot._pt_parent = NULL;
        pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
        pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;
    }
    else
    {
        pt_rb_tree->_t_rbroot._pt_left = _get_min_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
        pt_rb_tree->_t_rbroot._pt_right = _get_max_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
    }
}

void _rb_tree_erase_range(
    _rb_tree_t* pt_rb_tree, _rb_tree_iterator_t t_begin, _rb_tree_iterator_t t_end)
{
    _rb_tree_iterator_t t_iterator;
    _rb_tree_iterator_t t_next;

    assert(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, t_begin));
    assert(_rb_tree_iterator_equal(t_begin, t_end) ||
           _rb_tree_iterator_before(t_begin, t_end));

    t_iterator = t_next = t_begin;
    if(!_rb_tree_iterator_equal(t_next, _rb_tree_end(pt_rb_tree)))
    {
        t_next = _rb_tree_iterator_next(t_next);
    }
    while(!_rb_tree_iterator_equal(t_iterator, t_end))
    {
        _rb_tree_erase_pos(pt_rb_tree, t_iterator);
        
        t_iterator = t_next;
        if(!_rb_tree_iterator_equal(t_next, _rb_tree_end(pt_rb_tree)))
        {
            t_next = _rb_tree_iterator_next(t_next);
        }
    }
}

size_t _rb_tree_erase(_rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    size_t t_countsize = _rb_tree_count(pt_rb_tree, cpv_value);
    range_t t_range = _rb_tree_equal_range(pt_rb_tree, cpv_value);

    if(!_rb_tree_iterator_equal(t_range.it_begin, _rb_tree_end(pt_rb_tree)))
    {
        _rb_tree_erase_range(pt_rb_tree, t_range.it_begin, t_range.it_end);
    }

    return t_countsize;
}

/** local function implementation section **/

/** eof **/

