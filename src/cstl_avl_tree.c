/*
 *  The implementation of avl tree.
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

#include "cstl_avl_tree_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* avl tree iterator function */
_avl_tree_iterator_t _create_avl_tree_iterator(void)
{
    _avl_tree_iterator_t t_newiterator;

    _GET_AVL_TREE_COREPOS(t_newiterator) = NULL;
    _GET_AVL_TREE_POINTER(t_newiterator) = NULL;

    _GET_CONTAINER(t_newiterator) = NULL;

    return t_newiterator;
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

/* avl private function */
_avl_tree_t* _create_avl_tree(const char* s_typename)
{
    _avl_tree_t* pt_avl_tree = NULL;

    if((pt_avl_tree = (_avl_tree_t*)malloc(sizeof(_avl_tree_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_avl_tree_auxiliary(pt_avl_tree, s_typename))
    {
        free(pt_avl_tree);
        return NULL;
    }

    return pt_avl_tree;
}

bool_t _create_avl_tree_auxiliary(_avl_tree_t* pt_avl_tree, const char* s_typename)
{
    assert(pt_avl_tree != NULL && s_typename != NULL);

    /* get type information */
    _type_get_type(&pt_avl_tree->_t_typeinfo, s_typename);
    if(pt_avl_tree->_t_typeinfo._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pt_avl_tree->_t_avlroot._pt_parent = NULL;
    pt_avl_tree->_t_avlroot._pt_left = NULL;
    pt_avl_tree->_t_avlroot._pt_right = NULL;
    pt_avl_tree->_t_avlroot._un_height = 0;
    pt_avl_tree->_t_nodecount = 0;

    pt_avl_tree->_t_compare = NULL;

    return true;
}

void _avl_tree_init(_avl_tree_t* pt_avl_tree, binary_function_t t_compare)
{
    assert(pt_avl_tree != NULL &&
           pt_avl_tree->_t_nodecount == 0 &&
           pt_avl_tree->_t_avlroot._pt_parent == NULL &&
           pt_avl_tree->_t_avlroot._pt_left == NULL &&
           pt_avl_tree->_t_avlroot._pt_right == NULL &&
           pt_avl_tree->_t_avlroot._un_height == 0 &&
           pt_avl_tree->_t_compare == NULL);

    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;

    _alloc_init(&pt_avl_tree->_t_allocator);

    if(t_compare != NULL)
    {
        pt_avl_tree->_t_compare = t_compare;
    }
    else
    {
        pt_avl_tree->_t_compare = _GET_AVL_TREE_TYPE_LESS_FUNCTION(pt_avl_tree);
    }
}

void _avl_tree_destroy_auxiliary(_avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);

    /* destroy all elements */
    pt_avl_tree->_t_avlroot._pt_parent = 
        _avl_tree_destroy_subtree(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_nodecount = 0;

    /* destroy allocator */
    _alloc_destroy(&pt_avl_tree->_t_allocator);

    pt_avl_tree->_t_compare = NULL;
}

void _avl_tree_destroy(_avl_tree_t* pt_avl_tree)
{
    _avl_tree_destroy_auxiliary(pt_avl_tree);
    free(pt_avl_tree);
}

void _avl_tree_init_copy(
    _avl_tree_t* pt_avl_tree_dest, const _avl_tree_t* cpt_avl_tree_src)
{
    assert(pt_avl_tree_dest != NULL && cpt_avl_tree_src != NULL);
    assert(pt_avl_tree_dest->_t_typeinfo._pt_type == cpt_avl_tree_src->_t_typeinfo._pt_type);

    /* init the avl tree with the src avl tree */
    _avl_tree_init(pt_avl_tree_dest,  cpt_avl_tree_src->_t_compare);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(cpt_avl_tree_src))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest,
            _avl_tree_begin(cpt_avl_tree_src), _avl_tree_end(cpt_avl_tree_src));
    }
}

void _avl_tree_init_copy_range(
    _avl_tree_t* pt_avl_tree_dest, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end)
{
    assert(pt_avl_tree_dest != NULL);
    assert(pt_avl_tree_dest->_t_typeinfo._pt_type ==
           _GET_AVL_TREE(t_begin)->_t_typeinfo._pt_type);
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    /* init the avl tree with the src avl tree */
    _avl_tree_init(pt_avl_tree_dest,
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(_GET_AVL_TREE(t_begin)));
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(_GET_AVL_TREE(t_begin)))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest, t_begin, t_end);
    }
}

void _avl_tree_init_copy_range_ex(
    _avl_tree_t* pt_avl_tree_dest, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end,
    binary_function_t t_compare)
{
    assert(pt_avl_tree_dest != NULL);
    assert(pt_avl_tree_dest->_t_typeinfo._pt_type ==
           _GET_AVL_TREE(t_begin)->_t_typeinfo._pt_type);
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    /* init the avl tree with the src avl tree */
    _avl_tree_init(pt_avl_tree_dest, t_compare);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(_GET_AVL_TREE(t_begin)))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest, t_begin, t_end);
    }
}

void _avl_tree_assign(_avl_tree_t* pt_avl_tree_dest, const _avl_tree_t* cpt_avl_tree_src)
{
    assert(_avl_tree_same_type(pt_avl_tree_dest, cpt_avl_tree_src));

    /* clear dest avl tree */
    _avl_tree_clear(pt_avl_tree_dest);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(cpt_avl_tree_src))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest,
            _avl_tree_begin(cpt_avl_tree_src), _avl_tree_end(cpt_avl_tree_src));
    }
}

bool_t _avl_tree_empty(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    if(cpt_avl_tree->_t_nodecount == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t _avl_tree_size(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    return cpt_avl_tree->_t_nodecount;
}

size_t _avl_tree_max_size(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    return (size_t)(-1) / _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
}

_avl_tree_iterator_t _avl_tree_begin(const _avl_tree_t* cpt_avl_tree)
{
    _avl_tree_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_newiterator) = (char*)cpt_avl_tree->_t_avlroot._pt_left;

    return t_newiterator;
}

_avl_tree_iterator_t _avl_tree_end(const _avl_tree_t* cpt_avl_tree)
{
    _avl_tree_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_newiterator) = (char*)&cpt_avl_tree->_t_avlroot;

    return t_newiterator;
}

_avl_tree_reverse_iterator_t _avl_tree_rbegin(const _avl_tree_t* cpt_avl_tree)
{
    _avl_tree_reverse_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_newiterator) = (char*)cpt_avl_tree->_t_avlroot._pt_right;

    return t_newiterator;
}

_avl_tree_reverse_iterator_t _avl_tree_rend(const _avl_tree_t* cpt_avl_tree)
{
    _avl_tree_reverse_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_newiterator) = (char*)&cpt_avl_tree->_t_avlroot;

    return t_newiterator;
}

binary_function_t _avl_tree_key_comp(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    return cpt_avl_tree->_t_compare;
}

_avl_tree_iterator_t _avl_tree_find(const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    _avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    _GET_AVL_TREE_POINTER(t_iterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_iterator) = (char*)_avl_tree_find_value(
            cpt_avl_tree, cpt_avl_tree->_t_avlroot._pt_parent, cpv_value);
    if(_GET_AVL_TREE_COREPOS(t_iterator) == NULL)
    {
        _GET_AVL_TREE_COREPOS(t_iterator) = (char*)&cpt_avl_tree->_t_avlroot;
    }

    return t_iterator;
}

void _avl_tree_clear(_avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);

    /* destroy all elements */
    pt_avl_tree->_t_avlroot._pt_parent =
        _avl_tree_destroy_subtree(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_nodecount = 0;
}

size_t _avl_tree_count(const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    range_t t_range;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_range = _avl_tree_equal_range(cpt_avl_tree, cpv_value);
    return abs(_avl_tree_iterator_distance(t_range.it_begin, t_range.it_end));
}

_avl_tree_iterator_t _avl_tree_lower_bound(
    const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    _avlnode_t*          pt_cur = NULL;
    _avlnode_t*          pt_prev = NULL;
    bool_t              t_less = false;
    bool_t              t_greater = false;
    _avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_iterator = _create_avl_tree_iterator();
    _GET_AVL_TREE_POINTER(t_iterator) = (void*)cpt_avl_tree;

    if(!_avl_tree_empty(cpt_avl_tree))
    {
        pt_prev = cpt_avl_tree->_t_avlroot._pt_parent;

        t_less = t_greater = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
        _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_prev->_pc_data, &t_less);
        _avl_tree_elem_compare_auxiliary(cpt_avl_tree, pt_prev->_pc_data, cpv_value, &t_greater);
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
            t_less = t_greater = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
            _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_prev->_pc_data, &t_less);
            _avl_tree_elem_compare_auxiliary(cpt_avl_tree, pt_prev->_pc_data, cpv_value, &t_greater);
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
            _GET_AVL_TREE_COREPOS(t_iterator) = (char*)pt_prev;
            assert(_avl_tree_iterator_belong_to_avl_tree(cpt_avl_tree, t_iterator));
        }
        else
        {
            assert(pt_prev->_pt_right == NULL);
            _GET_AVL_TREE_COREPOS(t_iterator) = (char*)pt_prev;
            t_iterator = _avl_tree_iterator_next(t_iterator);
        }
    }
    else
    {
        t_iterator = _avl_tree_end(cpt_avl_tree);
    }

    return t_iterator;
}

_avl_tree_iterator_t _avl_tree_upper_bound(
    const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    _avlnode_t*          pt_cur = NULL;
    _avlnode_t*          pt_prev = NULL;
    bool_t              t_result = false;
    _avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_iterator = _create_avl_tree_iterator();
    _GET_AVL_TREE_POINTER(t_iterator) = (void*)cpt_avl_tree;

    if(!_avl_tree_empty(cpt_avl_tree))
    {
        pt_prev = cpt_avl_tree->_t_avlroot._pt_parent;
        t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
        _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_prev->_pc_data, &t_result);
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
            t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
            _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_prev->_pc_data, &t_result);
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
            _GET_AVL_TREE_COREPOS(t_iterator) = (char*)pt_prev;
            assert(_avl_tree_iterator_belong_to_avl_tree(cpt_avl_tree, t_iterator));
        }
        else
        {
            assert(pt_prev->_pt_right == NULL);
            _GET_AVL_TREE_COREPOS(t_iterator) = (char*)pt_prev;
            t_iterator = _avl_tree_iterator_next(t_iterator);
        }
    }
    else
    {
        t_iterator = _avl_tree_end(cpt_avl_tree);
    }

    return t_iterator;
}

range_t _avl_tree_equal_range(
    const _avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    range_t t_range;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_range.it_begin = _avl_tree_lower_bound(cpt_avl_tree, cpv_value);
    t_range.it_end = _avl_tree_upper_bound(cpt_avl_tree, cpv_value);

    return t_range;
}

bool_t _avl_tree_equal(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond)
{
    _avl_tree_iterator_t t_first;
    _avl_tree_iterator_t t_second;
    bool_t              t_less = false;
    bool_t              t_greater = false;

    assert(cpt_avl_treefirst != NULL && cpt_avl_treesecond != NULL);
    
    /* test type */
    if(!_avl_tree_same_type(cpt_avl_treefirst, cpt_avl_treesecond))
    {
        return false;
    }
    /* test avl tree size */
    if(_avl_tree_size(cpt_avl_treefirst) != _avl_tree_size(cpt_avl_treesecond))
    {
        return false;
    }
    /* test each element */
    for(t_first = _avl_tree_begin(cpt_avl_treefirst), 
        t_second = _avl_tree_begin(cpt_avl_treesecond);
        !_avl_tree_iterator_equal(t_first, _avl_tree_end(cpt_avl_treefirst)) &&
        !_avl_tree_iterator_equal(t_second, _avl_tree_end(cpt_avl_treesecond));
        t_first = _avl_tree_iterator_next(t_first),
        t_second = _avl_tree_iterator_next(t_second))
    {
        t_less = t_greater = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_treefirst);
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_avl_treefirst)(
            ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_first))->_pc_data,
            ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_second))->_pc_data, &t_less);
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_avl_treefirst)(
            ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_second))->_pc_data,
            ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_first))->_pc_data, &t_greater);
        if(t_less || t_greater)
        {
            return false;
        }
    }
    assert(_avl_tree_iterator_equal(t_first, _avl_tree_end(cpt_avl_treefirst)) &&
           _avl_tree_iterator_equal(t_second, _avl_tree_end(cpt_avl_treesecond)));

    return true;
}

bool_t _avl_tree_not_equal(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond)
{
    return!_avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond);
}

bool_t _avl_tree_less(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond)
{
    _avl_tree_iterator_t t_first;
    _avl_tree_iterator_t t_second;
    bool_t              t_result = false;

    assert(_avl_tree_same_type(cpt_avl_treefirst, cpt_avl_treesecond));

    /* test each element */
    for(t_first = _avl_tree_begin(cpt_avl_treefirst), 
        t_second = _avl_tree_begin(cpt_avl_treesecond);
        !_avl_tree_iterator_equal(t_first, _avl_tree_end(cpt_avl_treefirst)) &&
        !_avl_tree_iterator_equal(t_second, _avl_tree_end(cpt_avl_treesecond));
        t_first = _avl_tree_iterator_next(t_first),
        t_second = _avl_tree_iterator_next(t_second))
    {
        t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_treefirst);
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_avl_treefirst)(
            ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_first))->_pc_data,
            ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_second))->_pc_data, &t_result);
        if(t_result)
        {
            return true;
        }
        t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_treefirst);
        _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_avl_treefirst)(
            ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_second))->_pc_data,
            ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_first))->_pc_data, &t_result);
        if(t_result)
        {
            return false;
        }
    }

    if(_avl_tree_size(cpt_avl_treefirst) < _avl_tree_size(cpt_avl_treesecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _avl_tree_less_equal(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond)
{
    return (_avl_tree_less(cpt_avl_treefirst, cpt_avl_treesecond) ||
            _avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond)) ? true : false;
}

bool_t _avl_tree_greater(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond)
{
    return _avl_tree_less(cpt_avl_treesecond, cpt_avl_treefirst);
}

bool_t _avl_tree_greater_equal(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond)
{
    return (_avl_tree_greater(cpt_avl_treefirst, cpt_avl_treesecond) ||
            _avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond)) ? true : false;
}

void _avl_tree_swap(_avl_tree_t* pt_avl_treefirst, _avl_tree_t* pt_avl_treesecond)
{
    _avl_tree_t t_avl_treetmp;

    assert(pt_avl_treefirst != NULL && pt_avl_treesecond != NULL);

    t_avl_treetmp = *pt_avl_treefirst;
    *pt_avl_treefirst = *pt_avl_treesecond;
    *pt_avl_treesecond = t_avl_treetmp;

    if(_avl_tree_empty(pt_avl_treefirst))
    {
        pt_avl_treefirst->_t_avlroot._pt_left = &pt_avl_treefirst->_t_avlroot;
        pt_avl_treefirst->_t_avlroot._pt_right = &pt_avl_treefirst->_t_avlroot;
    }
    else
    {
        pt_avl_treefirst->_t_avlroot._pt_parent->_pt_parent = 
            &pt_avl_treefirst->_t_avlroot;
    }

    if(_avl_tree_empty(pt_avl_treesecond))
    {
        pt_avl_treesecond->_t_avlroot._pt_left = &pt_avl_treesecond->_t_avlroot;
        pt_avl_treesecond->_t_avlroot._pt_right = &pt_avl_treesecond->_t_avlroot;
    }
    else
    {
        pt_avl_treesecond->_t_avlroot._pt_parent->_pt_parent = 
            &pt_avl_treesecond->_t_avlroot;
    }
}

_avl_tree_iterator_t _avl_tree_insert_equal(_avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    _avl_tree_insert_result_t    t_insert_result;
    _avl_tree_iterator_t t_iterator = _create_avl_tree_iterator();

    assert(pt_avl_tree != NULL && cpv_value != NULL);

    t_insert_result = _avl_tree_insert_avlnode(
        pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, cpv_value);
    assert(t_insert_result._pt_adjust != NULL && t_insert_result._pt_new != NULL);

    pt_avl_tree->_t_avlroot._pt_parent = t_insert_result._pt_adjust;
    pt_avl_tree->_t_avlroot._pt_parent->_pt_parent = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_left = _avl_tree_get_min_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    pt_avl_tree->_t_avlroot._pt_right = _avl_tree_get_max_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    pt_avl_tree->_t_nodecount++;

    _GET_AVL_TREE_POINTER(t_iterator) = pt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_iterator) = (char*)t_insert_result._pt_new;

    return t_iterator;
}

_avl_tree_iterator_t _avl_tree_insert_unique(_avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    assert(pt_avl_tree != NULL && cpv_value != NULL);

    /* if the avl tree is empty */
    if(_avl_tree_empty(pt_avl_tree))
    {
        return _avl_tree_insert_equal(pt_avl_tree, cpv_value);
    }
    else
    {
        /* find value in avl tree */
        _avl_tree_iterator_t t_iter = _avl_tree_find(pt_avl_tree, cpv_value);
        /* if the value is exist */
        if(!_avl_tree_iterator_equal(t_iter, _avl_tree_end(pt_avl_tree)))
        {
            return _avl_tree_end(pt_avl_tree);
        }
        else
        {
            /* insert value into avl tree */
            return _avl_tree_insert_equal(pt_avl_tree, cpv_value);
        }
    }
}

void _avl_tree_insert_equal_range(
    _avl_tree_t* pt_avl_tree, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end)
{
    _avl_tree_iterator_t t_iterator;

    assert(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, t_begin));
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_avl_tree_iterator_equal(t_iterator, t_end);
        t_iterator = _avl_tree_iterator_next(t_iterator))
    {
        _avl_tree_insert_equal(
            pt_avl_tree, ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_iterator))->_pc_data);
    }
}

void _avl_tree_insert_unique_range(
    _avl_tree_t* pt_avl_tree, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end)
{
    _avl_tree_iterator_t t_iterator;

    assert(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, t_begin));
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_avl_tree_iterator_equal(t_iterator, t_end);
        t_iterator = _avl_tree_iterator_next(t_iterator))
    {
        _avl_tree_insert_unique(
            pt_avl_tree, ((_avlnode_t*)_GET_AVL_TREE_COREPOS(t_iterator))->_pc_data);
    }
}

void _avl_tree_erase_pos(_avl_tree_t* pt_avl_tree, _avl_tree_iterator_t t_pos)
{
    _avlnode_t* pt_parent = NULL;
    _avlnode_t* pt_cur = NULL;
    bool_t     t_result = false;

    assert(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, t_pos));
    assert(!_avl_tree_iterator_equal(t_pos, _avl_tree_end(pt_avl_tree)));
    
    pt_cur = (_avlnode_t*)_GET_AVL_TREE_COREPOS(t_pos);
    pt_parent = pt_cur->_pt_parent;

    /* delete node X express deleting */
    if(pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL)
    {
        /*
         *  P       P
         *  |   =>   
         *  X
         */
        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_parent->_pt_parent = NULL;
        }
        /*
         *    P       P
         *   /   =>   
         *  X
         */
        else if(pt_cur == pt_parent->_pt_left)
        {
            pt_parent->_pt_left = NULL;
        }
        /*
         *   P         P
         *    \   =>  
         *     X
         */
        else
        {
            pt_parent->_pt_right = NULL;
        }
    }
    else if(pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL)
    {
        /*
         *   P          P
         *   |          |
         *   X     =>   L
         *  /
         * L
         */
        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_parent->_pt_parent = pt_cur->_pt_left;
            pt_parent->_pt_parent->_pt_parent = pt_parent;
        }
        /*
         *     P          P
         *    /          /
         *   X     =>   L
         *  /
         * L
         */
        else if(pt_cur == pt_parent->_pt_left)
        {
            pt_parent->_pt_left = pt_cur->_pt_left;
            pt_parent->_pt_left->_pt_parent = pt_parent;
        }
        /*
         *  P           P
         *   \           \
         *    X   =>      L
         *   /
         *  L
         */
        else
        {
            pt_parent->_pt_right = pt_cur->_pt_left;
            pt_parent->_pt_right->_pt_parent = pt_parent;
        }
    }
    else if(pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL)
    {
        /*
         *     P             P
         *     |             |
         *     X     =>      R
         *      \
         *       R
         */
        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_parent->_pt_parent = pt_cur->_pt_right;
            pt_parent->_pt_parent->_pt_parent = pt_parent;
        }
        /*
         *   P             P
         *    \             \
         *     X     =>      R
         *      \
         *       R
         */
        else if(pt_cur == pt_parent->_pt_right)
        {
            pt_parent->_pt_right = pt_cur->_pt_right;
            pt_parent->_pt_right->_pt_parent = pt_parent;
        }
        /*
         *    P              R
         *   /              /
         *  X       =>     R
         *   \
         *    R
         */
        else
        {
            pt_parent->_pt_left = pt_cur->_pt_right;
            pt_parent->_pt_left->_pt_parent = pt_parent;
        }
    }
    else
    {
        _avlnode_t* pt_parenttmp = NULL;
        _avlnode_t* pt_curtmp = NULL;

        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_curtmp = _avl_tree_get_min_avlnode(pt_cur->_pt_right);
            /*
             *     P              P
             *     |              | 
             *     X       =>     B
             *    / \            / \
             *   A   B          A   C
             *        \
             *         C
             */
            if(pt_cur == pt_curtmp->_pt_parent)
            {
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_parent = pt_curtmp;

                pt_parent = pt_curtmp;
            }
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
            else
            {
                /* pt_curtmp express S; pt_parenttmp express B */
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

                pt_parent = pt_parenttmp;
            }
        }
        else if(pt_cur == pt_parent->_pt_left)
        {
            pt_curtmp = _avl_tree_get_min_avlnode(pt_cur->_pt_right);
            /*
             *       P              P
             *      /              / 
             *     X       =>     B
             *    / \            / \
             *   A   B          A   C
             *        \
             *         C
             */
            if(pt_cur == pt_curtmp->_pt_parent)
            {
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_left = pt_curtmp;

                pt_parent = pt_curtmp;
            }
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
            else
            {
                /* pt_curtmp express S; pt_parenttmp express B */
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

                pt_parent = pt_parenttmp;
            }
        }
        else
        {
            pt_curtmp = _avl_tree_get_min_avlnode(pt_cur->_pt_right);
            /*
             *      P            P
             *       \            \
             *        X     =>     B
             *       / \          / \
             *      A   B        A   C
             *           \
             *            C
             */
            if(pt_cur == pt_curtmp->_pt_parent)
            {
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_right = pt_curtmp;

                pt_parent = pt_curtmp;
            }
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
            else
            {
                /* pt_curtmp express S; pt_parenttmp express C */
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

                pt_parent = pt_parenttmp;
            }
        }
    }

    /* rebalance until to root */
    if(pt_parent != &pt_avl_tree->_t_avlroot)
    {
        _avlnode_t* pt_newcur = pt_parent;
        pt_parent = pt_newcur->_pt_parent;
        while(pt_parent != &pt_avl_tree->_t_avlroot)
        {
            if(pt_newcur == pt_parent->_pt_left)
            {
                pt_parent->_pt_left = _avl_tree_rebalance(pt_parent->_pt_left);
                pt_parent->_pt_left->_pt_parent = pt_parent;
            }
            else
            {
                pt_parent->_pt_right = _avl_tree_rebalance(pt_parent->_pt_right);
                pt_parent->_pt_right->_pt_parent = pt_parent;
            }

            pt_newcur = pt_parent;
            pt_parent = pt_newcur->_pt_parent;
        }
    }

    /* rebalance root */
    if(pt_parent->_pt_parent != NULL)
    {
        pt_parent->_pt_parent = _avl_tree_rebalance(pt_parent->_pt_parent);
        pt_parent->_pt_parent->_pt_parent = pt_parent;
    }

    /* destroy node */
    t_result = _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree);
    _GET_AVL_TREE_TYPE_DESTROY_FUNCTION(pt_avl_tree)(pt_cur->_pc_data, &t_result);
    assert(t_result);
    _alloc_deallocate(&pt_avl_tree->_t_allocator, pt_cur,
        _AVL_TREE_NODE_SIZE(_GET_AVL_TREE_TYPE_SIZE(pt_avl_tree)), 1);
    pt_avl_tree->_t_nodecount--;
    if(pt_avl_tree->_t_nodecount == 0)
    {
        pt_avl_tree->_t_avlroot._pt_parent = NULL;
        pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
        pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    }
    else
    {
        pt_avl_tree->_t_avlroot._pt_left =
            _avl_tree_get_min_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
        pt_avl_tree->_t_avlroot._pt_right = 
            _avl_tree_get_max_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    }
}

void _avl_tree_erase_range(
    _avl_tree_t* pt_avl_tree, _avl_tree_iterator_t t_begin, _avl_tree_iterator_t t_end)
{
    _avl_tree_iterator_t t_iterator;
    _avl_tree_iterator_t t_next;

    assert(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, t_begin));
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    t_iterator = t_next = t_begin;
    if(!_avl_tree_iterator_equal(t_next, _avl_tree_end(pt_avl_tree)))
    {
        t_next = _avl_tree_iterator_next(t_next);
    }
    while(!_avl_tree_iterator_equal(t_iterator, t_end))
    {
        _avl_tree_erase_pos(pt_avl_tree, t_iterator);
        
        t_iterator = t_next;
        if(!_avl_tree_iterator_equal(t_next, _avl_tree_end(pt_avl_tree)))
        {
            t_next = _avl_tree_iterator_next(t_next);
        }
    }
}

size_t _avl_tree_erase(_avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    size_t t_countsize = _avl_tree_count(pt_avl_tree, cpv_value);
    range_t t_range = _avl_tree_equal_range(pt_avl_tree, cpv_value);

    if(!_avl_tree_iterator_equal(t_range.it_begin, _avl_tree_end(pt_avl_tree)))
    {
        _avl_tree_erase_range(pt_avl_tree, t_range.it_begin, t_range.it_end);
    }

    return t_countsize;
}

/** local function implementation section **/

/** eof **/

