/*
 *  The implementation of rb tree.
 *  Copyright (C)  2008,2009,2010  Wangbo
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
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cstl_alloc.h"
#include "cstl_types.h"
#include "cstl_iterator.h"

#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"

#include "cstring.h"

/** local constant declaration and local macro section **/
#define _RB_TREE_NODE_SIZE(typesize)\
    ((typesize) + sizeof(rbnode_t) - 1)

/* macros for type informations */
#define _GET_RB_TREE_TYPE_SIZE(pt_rb_tree)\
    ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_RB_TREE_TYPE_NAME(pt_rb_tree)\
    ((pt_rb_tree)->_t_typeinfo._sz_typename)
#define _GET_RB_TREE_TYPE_BASENAME(pt_rb_tree)\
    ((pt_rb_tree)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_RB_TREE_TYPE_INIT_FUNCTION(pt_rb_tree)\
    ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_RB_TREE_TYPE_COPY_FUNCTION(pt_rb_tree)\
    ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_RB_TREE_TYPE_LESS_FUNCTION(pt_rb_tree)\
    ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_RB_TREE_TYPE_DESTROY_FUNCTION(pt_rb_tree)\
    ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_RB_TREE_TYPE_STYLE(pt_rb_tree)\
    ((pt_rb_tree)->_t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support function.
 */
static bool_t _rb_tree_iterator_belong_to_rb_tree(
    const rb_tree_t* cpt_rb_tree, rb_tree_iterator_t t_iter);
static bool_t _rb_tree_same_rb_tree_iterator_type(
    const rb_tree_t* cpt_rb_tree, rb_tree_iterator_t t_iter);
static bool_t _find_iterator(
    const rbnode_t* cpt_root, const rbnode_t* cpt_pos);
#endif /* NDEBUG */
static bool_t _rb_tree_same_type(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond);

/*
 * Destroy the subtree with postorder traverse.
 */
static rbnode_t* _destroy_rb_tree(rb_tree_t* pt_rb_tree, rbnode_t* pt_root);

/*
 * Travel subtree for find the value in preorder.
 */
static rbnode_t* _find_value(
    const rb_tree_t* cpt_rb_tree, const rbnode_t* cpt_root, const void* cpv_value); 

/*
 * Insert the value into subtree.
 */
static rbnode_t* _insert_rbnode(rb_tree_t* pt_rb_tree, const void* cpv_value);

/*
 * Rebalance the subtree.
 */
static void _rebalance_rb_tree(rb_tree_t* pt_rb_tree, rbnode_t* pt_pos);

/*
 * Rebalance the subtree after deletion.
 */
static void _fixup_deletion(
    rb_tree_t* pt_rb_tree, rbnode_t* pt_pos, rbnode_t* pt_parent);

/*
 * Get minimum and maximum rbnode pointer.
 */
static rbnode_t* _get_min_rbnode(const rbnode_t* cpt_root);
static rbnode_t* _get_max_rbnode(const rbnode_t* cpt_root);

/*
 * Get rb node color.
 */
static color_t _get_color(const rbnode_t* cpt_root);

/*
 * Left rotate and right rotate.
 */
static rbnode_t* _widdershins_rotate(rbnode_t* pt_root);
static rbnode_t* _deasil_rotate(rbnode_t* pt_root);

/* initiallize the element */
static void _rb_tree_init_elem_auxiliary(rb_tree_t* pt_rb_tree, rbnode_t* pt_node);

/* element less function auxiliary */
static void _rb_tree_elem_less_auxiliary(const rb_tree_t* cpt_rb_tree,
    const void* cpv_first, const void* cpv_second, void* pv_output);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* rb tree iterator function */
rb_tree_iterator_t _create_rb_tree_iterator(void)
{
    rb_tree_iterator_t t_newiterator;

    _GET_RB_TREE_COREPOS(t_newiterator) = NULL;
    _GET_RB_TREE_POINTER(t_newiterator) = NULL;

    _GET_CONTAINER(t_newiterator) = NULL;

    return t_newiterator;
}

bool_t _rb_tree_iterator_equal(
    rb_tree_iterator_t t_iterfirst, rb_tree_iterator_t t_itersecond)
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

void _rb_tree_iterator_get_value(rb_tree_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_iter), t_iter));
    assert(!_rb_tree_iterator_equal(t_iter, _rb_tree_end(_GET_RB_TREE(t_iter))));

    /* char* */
    if(strncmp(_GET_RB_TREE_TYPE_BASENAME(_GET_RB_TREE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str(
            (string_t*)((rbnode_t*)_GET_RB_TREE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        bool_t t_result = _GET_RB_TREE_TYPE_SIZE(_GET_RB_TREE(t_iter));
        _GET_RB_TREE_TYPE_COPY_FUNCTION(_GET_RB_TREE(t_iter))(
            pv_value, ((rbnode_t*)_GET_RB_TREE_COREPOS(t_iter))->_pc_data, &t_result);
        assert(t_result);
    }
}

const void* _rb_tree_iterator_get_pointer(rb_tree_iterator_t t_iter)
{
    assert(_rb_tree_iterator_belong_to_rb_tree(_GET_RB_TREE(t_iter), t_iter));
    assert(!_rb_tree_iterator_equal(t_iter, _rb_tree_end(_GET_RB_TREE(t_iter))));

    /* char* */
    if(strncmp(_GET_RB_TREE_TYPE_BASENAME(_GET_RB_TREE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str(
            (string_t*)((rbnode_t*)_GET_RB_TREE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        return ((rbnode_t*)_GET_RB_TREE_COREPOS(t_iter))->_pc_data;
    }
}

rb_tree_iterator_t _rb_tree_iterator_next(rb_tree_iterator_t t_iter)
{
    rbnode_t* pt_next = NULL;  /* next pos */
    rbnode_t* pt_cur = (rbnode_t*)_GET_RB_TREE_COREPOS(t_iter);

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

rb_tree_iterator_t _rb_tree_iterator_prev(rb_tree_iterator_t t_iter)
{
    rbnode_t* pt_prev = NULL;
    rbnode_t* pt_cur = (rbnode_t*)_GET_RB_TREE_COREPOS(t_iter);

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
    rb_tree_iterator_t t_iterfirst, rb_tree_iterator_t t_itersecond)
{
    rb_tree_iterator_t t_iterator;
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
    rb_tree_iterator_t t_iterfirst, rb_tree_iterator_t t_itersecond)
{
    rb_tree_iterator_t t_iterator;
    rb_tree_t*         pt_rb_tree = NULL;

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
rb_tree_t* _create_rb_tree(const char* s_typename)
{
    rb_tree_t*  pt_newrbtree = NULL;

    if((pt_newrbtree = (rb_tree_t*)malloc(sizeof(rb_tree_t))) == NULL)
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

bool_t _create_rb_tree_auxiliary(rb_tree_t* pt_rb_tree, const char* s_typename)
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

    pt_rb_tree->_t_less = NULL;

    return true;
}

void _rb_tree_init(rb_tree_t* pt_rb_tree, binary_function_t t_less)
{
    assert(pt_rb_tree != NULL &&
           pt_rb_tree->_t_nodecount == 0 &&
           pt_rb_tree->_t_rbroot._pt_parent == NULL &&
           pt_rb_tree->_t_rbroot._pt_left == NULL &&
           pt_rb_tree->_t_rbroot._pt_right == NULL && 
           pt_rb_tree->_t_rbroot._t_color == red &&
           pt_rb_tree->_t_less == NULL);

    pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;

    allocate_init(&pt_rb_tree->_t_allocater);

    if(t_less != NULL)
    {
        pt_rb_tree->_t_less = t_less;
    }
    else
    {
        pt_rb_tree->_t_less = _GET_RB_TREE_TYPE_LESS_FUNCTION(pt_rb_tree);
    }
}

void _rb_tree_destroy_auxiliary(rb_tree_t* pt_rb_tree)
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
    allocate_destroy(&pt_rb_tree->_t_allocater);

    pt_rb_tree->_t_less = NULL;
}

void _rb_tree_destroy(rb_tree_t* pt_rb_tree)
{
    _rb_tree_destroy_auxiliary(pt_rb_tree);
    free(pt_rb_tree);
}

void _rb_tree_init_copy(
    rb_tree_t* pt_rb_tree_dest, const rb_tree_t* cpt_rb_tree_src)
{
    assert(pt_rb_tree_dest != NULL && cpt_rb_tree_src != NULL);
    assert(pt_rb_tree_dest->_t_typeinfo._pt_type == cpt_rb_tree_src->_t_typeinfo._pt_type);

    /* init the rb tree with the src rb tree */
    _rb_tree_init(pt_rb_tree_dest, cpt_rb_tree_src->_t_less);
    /* insert all elements of src into dest */
    if(!_rb_tree_empty(cpt_rb_tree_src))
    {
        _rb_tree_insert_equal_range(pt_rb_tree_dest,
            _rb_tree_begin(cpt_rb_tree_src), _rb_tree_end(cpt_rb_tree_src));
    }
}

void _rb_tree_init_copy_range(
    rb_tree_t* pt_rb_tree_dest, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end)
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
    rb_tree_t* pt_rb_tree_dest, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end,
    binary_function_t t_less)
{
    assert(pt_rb_tree_dest != NULL);
    assert(pt_rb_tree_dest->_t_typeinfo._pt_type ==
           _GET_RB_TREE(t_begin)->_t_typeinfo._pt_type);
    assert(_rb_tree_iterator_equal(t_begin, t_end) ||
           _rb_tree_iterator_before(t_begin, t_end));

    /* init the rb tree with the src rb tree */
    _rb_tree_init(pt_rb_tree_dest, t_less);
    /* insert all elements of src into dest */
    if(!_rb_tree_empty(_GET_RB_TREE(t_begin)))
    {
        _rb_tree_insert_equal_range(pt_rb_tree_dest, t_begin, t_end);
    }
}

void _rb_tree_assign(rb_tree_t* pt_rb_tree_dest, const rb_tree_t* cpt_rb_tree_src)
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

bool_t _rb_tree_empty(const rb_tree_t* cpt_rb_tree)
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

size_t _rb_tree_size(const rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    return cpt_rb_tree->_t_nodecount;
}

size_t _rb_tree_max_size(const rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    return (size_t)(-1) / _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
}

rb_tree_iterator_t _rb_tree_begin(const rb_tree_t* cpt_rb_tree)
{
    rb_tree_iterator_t t_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _GET_RB_TREE_POINTER(t_newiterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_newiterator) = (char*)cpt_rb_tree->_t_rbroot._pt_left;

    return t_newiterator;
}

rb_tree_iterator_t _rb_tree_end(const rb_tree_t* cpt_rb_tree)
{
    rb_tree_iterator_t t_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _GET_RB_TREE_POINTER(t_newiterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_newiterator) = (char*)&cpt_rb_tree->_t_rbroot;

    return t_newiterator;
}

rb_tree_iterator_t _rb_tree_rend(const rb_tree_t* cpt_rb_tree)
{
    rb_tree_iterator_t t_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _GET_RB_TREE_POINTER(t_newiterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_newiterator) = (char*)&cpt_rb_tree->_t_rbroot;

    return t_newiterator;
}

rb_tree_iterator_t _rb_tree_rbegin(const rb_tree_t* cpt_rb_tree)
{
    rb_tree_iterator_t t_newiterator = _create_rb_tree_iterator();

    assert(cpt_rb_tree != NULL);

    _GET_RB_TREE_POINTER(t_newiterator) = (void*)cpt_rb_tree;
    _GET_RB_TREE_COREPOS(t_newiterator) = (char*)cpt_rb_tree->_t_rbroot._pt_right;

    return t_newiterator;
}

binary_function_t _rb_tree_key_less(const rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    return cpt_rb_tree->_t_less;
}

rb_tree_iterator_t _rb_tree_find(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    rb_tree_iterator_t t_iterator;

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

void _rb_tree_clear(rb_tree_t* pt_rb_tree)
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
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond)
{
    rb_tree_iterator_t t_first;
    rb_tree_iterator_t t_second;
    bool_t             t_less = false;
    bool_t             t_great = false;

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
        t_less = t_great = _GET_RB_TREE_TYPE_SIZE(cpt_rb_treefirst);
        /*
        cpt_rb_treefirst->_t_less(((rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data, &t_less);
        cpt_rb_treefirst->_t_less(((rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data, &t_great);
        */
        _rb_tree_elem_less_auxiliary(cpt_rb_treefirst,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data, &t_less);
        _rb_tree_elem_less_auxiliary(cpt_rb_treefirst,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data, &t_great);
        if(t_less || t_great)
        {
            return false;
        }
    }

    assert(_rb_tree_iterator_equal(t_first, _rb_tree_end(cpt_rb_treefirst)) &&
           _rb_tree_iterator_equal(t_second, _rb_tree_end(cpt_rb_treesecond)));

    return true;
}

bool_t _rb_tree_not_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond)
{
    return!_rb_tree_equal(cpt_rb_treefirst, cpt_rb_treesecond);
}

bool_t _rb_tree_less(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond)
{
    rb_tree_iterator_t t_first;
    rb_tree_iterator_t t_second;
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
        /*
        cpt_rb_treefirst->_t_less(((rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data, &t_result);
        */
        _rb_tree_elem_less_auxiliary(cpt_rb_treefirst,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data, &t_result);
        if(t_result)
        {
            return true;
        }

        t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_treefirst);
        /*
        cpt_rb_treefirst->_t_less(((rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data, &t_result);
        */
        _rb_tree_elem_less_auxiliary(cpt_rb_treefirst,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_second))->_pc_data,
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_first))->_pc_data, &t_result);
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
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond)
{
    return (_rb_tree_less(cpt_rb_treefirst, cpt_rb_treesecond) ||
            _rb_tree_equal(cpt_rb_treefirst, cpt_rb_treesecond)) ? true : false;
}

bool_t _rb_tree_great(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond)
{
    return _rb_tree_less(cpt_rb_treesecond, cpt_rb_treefirst);
}

bool_t _rb_tree_great_equal(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond)
{
    return (_rb_tree_great(cpt_rb_treefirst, cpt_rb_treesecond) ||
            _rb_tree_equal(cpt_rb_treefirst, cpt_rb_treesecond)) ? true : false;
}

void _rb_tree_swap(rb_tree_t* pt_rb_treefirst, rb_tree_t* pt_rb_treesecond)
{
    rb_tree_t t_rb_treetmp;

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

size_t _rb_tree_count(const rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    range_t t_range;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    t_range = _rb_tree_equal_range(cpt_rb_tree, cpv_value);

    return abs(_rb_tree_iterator_distance(t_range.t_begin, t_range.t_end));
}

rb_tree_iterator_t _rb_tree_lower_bound(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    rbnode_t*          pt_cur = NULL;
    rbnode_t*          pt_prev = NULL;
    rb_tree_iterator_t t_iterator;
    bool_t             t_less = false;
    bool_t             t_great = false;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    t_iterator = _create_rb_tree_iterator();
    _GET_RB_TREE_POINTER(t_iterator) = (void*)cpt_rb_tree;

    if(!_rb_tree_empty(cpt_rb_tree))
    {
        pt_prev = cpt_rb_tree->_t_rbroot._pt_parent;

        t_less = t_great = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
        /*
        cpt_rb_tree->_t_less(cpv_value, pt_prev->_pc_data, &t_less);
        cpt_rb_tree->_t_less(pt_prev->_pc_data, cpv_value, &t_great);
        */
        _rb_tree_elem_less_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pc_data, &t_less);
        _rb_tree_elem_less_auxiliary(cpt_rb_tree, pt_prev->_pc_data, cpv_value, &t_great);
        /* t_less || (!t_less && !t_great) i.e. cpv_value <= pt_prev->_pc_data */
        if(t_less || !t_great)
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
            t_less = t_great = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
            /*
            cpt_rb_tree->_t_less(cpv_value, pt_prev->_pc_data, &t_less);
            cpt_rb_tree->_t_less(pt_prev->_pc_data, cpv_value, &t_great);
            */
            _rb_tree_elem_less_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pc_data, &t_less);
            _rb_tree_elem_less_auxiliary(cpt_rb_tree, pt_prev->_pc_data, cpv_value, &t_great);
            if(t_less || !t_great)
            {
                pt_cur = pt_prev->_pt_left;
            }
            else
            {
                pt_cur = pt_prev->_pt_right;
            }
        }

        if(t_less || !t_great)
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

rb_tree_iterator_t _rb_tree_upper_bound(
    const rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    rbnode_t*          pt_cur = NULL;
    rbnode_t*          pt_prev = NULL;
    rb_tree_iterator_t t_iterator;
    bool_t             t_result = false;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    t_iterator = _create_rb_tree_iterator();
    _GET_RB_TREE_POINTER(t_iterator) = (void*)cpt_rb_tree;

    if(!_rb_tree_empty(cpt_rb_tree))
    {
        pt_prev = cpt_rb_tree->_t_rbroot._pt_parent;

        t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
        /*cpt_rb_tree->_t_less(cpv_value, pt_prev->_pc_data, &t_result);*/
        _rb_tree_elem_less_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pc_data, &t_result);
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
            /*cpt_rb_tree->_t_less(cpv_value, pt_prev->_pc_data, &t_result);*/
            _rb_tree_elem_less_auxiliary(cpt_rb_tree, cpv_value, pt_prev->_pc_data, &t_result);
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

range_t _rb_tree_equal_range(const rb_tree_t* cpt_rb_tree, const void* cpv_value)
{
    range_t t_range;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    t_range.t_begin = _rb_tree_lower_bound(cpt_rb_tree, cpv_value);
    t_range.t_end = _rb_tree_upper_bound(cpt_rb_tree, cpv_value);

    return t_range;
}

rb_tree_iterator_t _rb_tree_insert_equal(rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    rb_tree_iterator_t t_iterator = _create_rb_tree_iterator();

    assert(pt_rb_tree != NULL && cpv_value != NULL);

    _GET_RB_TREE_POINTER(t_iterator) = pt_rb_tree;
    _GET_RB_TREE_COREPOS(t_iterator) = (char*)_insert_rbnode(pt_rb_tree, cpv_value);

    pt_rb_tree->_t_rbroot._pt_left = _get_min_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
    pt_rb_tree->_t_rbroot._pt_right = _get_max_rbnode(pt_rb_tree->_t_rbroot._pt_parent);
    pt_rb_tree->_t_nodecount++;

    return t_iterator;
}

rb_tree_iterator_t _rb_tree_insert_unique(rb_tree_t* pt_rb_tree, const void* cpv_value)
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
        rb_tree_iterator_t t_iter = _rb_tree_find(pt_rb_tree, cpv_value);
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
    rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end)
{
    rb_tree_iterator_t t_iterator;

    assert(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, t_begin));
    assert(_rb_tree_iterator_equal(t_begin, t_end) ||
           _rb_tree_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_rb_tree_iterator_equal(t_iterator, t_end);
        t_iterator = _rb_tree_iterator_next(t_iterator))
    {
        _rb_tree_insert_equal(pt_rb_tree, 
            ((rbnode_t*)_GET_RB_TREE_COREPOS(t_iterator))->_pc_data);
    }
}

void _rb_tree_insert_unique_range(
    rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end)
{
    rb_tree_iterator_t t_iterator;

    assert(_rb_tree_same_rb_tree_iterator_type(pt_rb_tree, t_begin));
    assert(_rb_tree_iterator_equal(t_begin, t_end) ||
           _rb_tree_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_rb_tree_iterator_equal(t_iterator, t_end);
        t_iterator = _rb_tree_iterator_next(t_iterator))
    {
        _rb_tree_insert_unique(
            pt_rb_tree, ((rbnode_t*)_GET_RB_TREE_COREPOS(t_iterator))->_pc_data);
    }
}

void _rb_tree_erase_pos(rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_pos)
{
    rbnode_t* pt_parent = NULL;
    rbnode_t* pt_cur = NULL;
    rbnode_t* pt_parenttmp = NULL;
    rbnode_t* pt_curtmp = NULL;
    color_t   t_colortmp;            /* temporary color for deletion */
    bool_t    t_result = false;

    assert(_rb_tree_iterator_belong_to_rb_tree(pt_rb_tree, t_pos));
    assert(!_rb_tree_iterator_equal(t_pos, _rb_tree_end(pt_rb_tree)));
    
    pt_cur = (rbnode_t*)_GET_RB_TREE_COREPOS(t_pos);
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
    deallocate(&pt_rb_tree->_t_allocater, pt_cur, 
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
    rb_tree_t* pt_rb_tree, rb_tree_iterator_t t_begin, rb_tree_iterator_t t_end)
{
    rb_tree_iterator_t t_iterator;
    rb_tree_iterator_t t_next;

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

size_t _rb_tree_erase(rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    size_t t_countsize = _rb_tree_count(pt_rb_tree, cpv_value);
    range_t t_range = _rb_tree_equal_range(pt_rb_tree, cpv_value);

    if(!_rb_tree_iterator_equal(t_range.t_begin, _rb_tree_end(pt_rb_tree)))
    {
        _rb_tree_erase_range(pt_rb_tree, t_range.t_begin, t_range.t_end);
    }

    return t_countsize;
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _rb_tree_iterator_belong_to_rb_tree(
    const rb_tree_t* cpt_rb_tree, rb_tree_iterator_t t_iter)
{
    assert(cpt_rb_tree != NULL);
    assert(_GET_RB_TREE_COREPOS(t_iter) != NULL);
    assert(_GET_RB_TREE(t_iter) == cpt_rb_tree);

    /* if iterator is end */
    if(_GET_RB_TREE_COREPOS(t_iter) == (char*)&cpt_rb_tree->_t_rbroot)
    {
        return true;
    }
    /* else travel rb tree for search the pointer */
    else
    {
        return _find_iterator(cpt_rb_tree->_t_rbroot._pt_parent, 
            (rbnode_t*)_GET_RB_TREE_COREPOS(t_iter));
    }
}

static bool_t _rb_tree_same_rb_tree_iterator_type(
    const rb_tree_t* cpt_rb_tree, rb_tree_iterator_t t_iter)
{
    assert(cpt_rb_tree != NULL && _GET_RB_TREE(t_iter) != NULL);

    /*return _rb_tree_same_type(cpt_rb_tree, _GET_RB_TREE(t_iter));*/
    return _type_is_same(_GET_RB_TREE_TYPE_NAME(cpt_rb_tree),
                         _GET_RB_TREE_TYPE_NAME(_GET_RB_TREE(t_iter))) &&
           (cpt_rb_tree->_t_typeinfo._t_style ==
            _GET_RB_TREE(t_iter)->_t_typeinfo._t_style) &&
           (cpt_rb_tree->_t_typeinfo._pt_type ==
            _GET_RB_TREE(t_iter)->_t_typeinfo._pt_type);
}

static bool_t _find_iterator(const rbnode_t* cpt_root, const rbnode_t* cpt_pos)
{
    if(cpt_root == NULL || cpt_pos == NULL)
    {
        return false;
    }
    else if(cpt_root == cpt_pos)
    {
        return true;
    }
    else
    {
        return _find_iterator(cpt_root->_pt_left, cpt_pos) ||
               _find_iterator(cpt_root->_pt_right, cpt_pos);
    }
}
#endif /* NEDBUG */

static bool_t _rb_tree_same_type(
    const rb_tree_t* cpt_rb_treefirst, const rb_tree_t* cpt_rb_treesecond)
{
    assert(cpt_rb_treefirst != NULL && cpt_rb_treesecond != NULL);

    return _type_is_same(_GET_RB_TREE_TYPE_NAME(cpt_rb_treefirst),
                         _GET_RB_TREE_TYPE_NAME(cpt_rb_treesecond)) &&
           (cpt_rb_treefirst->_t_typeinfo._t_style ==
            cpt_rb_treesecond->_t_typeinfo._t_style) &&
           (cpt_rb_treefirst->_t_typeinfo._pt_type ==
            cpt_rb_treesecond->_t_typeinfo._pt_type) &&
           (cpt_rb_treefirst->_t_less == cpt_rb_treesecond->_t_less);
}

static rbnode_t* _destroy_rb_tree(rb_tree_t* pt_rb_tree, rbnode_t* pt_root)
{
    bool_t t_result = false;

    assert(pt_rb_tree != NULL);

    if(pt_root != NULL)
    {
        pt_root->_pt_left = _destroy_rb_tree(pt_rb_tree, pt_root->_pt_left);
        pt_root->_pt_right = _destroy_rb_tree(pt_rb_tree, pt_root->_pt_right);

        assert(pt_root->_pt_left == NULL && pt_root->_pt_right == NULL);

        t_result = _GET_RB_TREE_TYPE_SIZE(pt_rb_tree);
        _GET_RB_TREE_TYPE_DESTROY_FUNCTION(pt_rb_tree)(pt_root->_pc_data, &t_result);
        assert(t_result);
        deallocate(&pt_rb_tree->_t_allocater, pt_root, 
            _RB_TREE_NODE_SIZE(_GET_RB_TREE_TYPE_SIZE(pt_rb_tree)), 1);
    }
    
    return NULL;
}

static rbnode_t* _find_value(
    const rb_tree_t* cpt_rb_tree, const rbnode_t* cpt_root, const void* cpv_value)
{
    bool_t t_result = false;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    if(cpt_root == NULL)
    {
        return NULL;
    }

    t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
    /*cpt_rb_tree->_t_less(cpv_value, cpt_root->_pc_data, &t_result);*/
    _rb_tree_elem_less_auxiliary(cpt_rb_tree, cpv_value, cpt_root->_pc_data, &t_result);
    if(t_result)
    {
        return _find_value(cpt_rb_tree, cpt_root->_pt_left, cpv_value);
    }

    t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
    /*cpt_rb_tree->_t_less(cpt_root->_pc_data, cpv_value, &t_result);*/
    _rb_tree_elem_less_auxiliary(cpt_rb_tree, cpt_root->_pc_data, cpv_value, &t_result);
    if(t_result)
    {
        return _find_value(cpt_rb_tree, cpt_root->_pt_right, cpv_value);
    }
    else
    {
        return (rbnode_t*)cpt_root;
    }
}

static rbnode_t* _get_min_rbnode(const rbnode_t* cpt_root)
{
    rbnode_t* pt_min = (rbnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while(pt_min->_pt_left != NULL)
    {
        pt_min = pt_min->_pt_left;
    }

    return pt_min;
}

static rbnode_t* _get_max_rbnode(const rbnode_t* cpt_root)
{
    rbnode_t* pt_max = (rbnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while(pt_max->_pt_right != NULL)
    {
        pt_max = pt_max->_pt_right;
    }

    return pt_max;
}

static color_t _get_color(const rbnode_t* cpt_root)
{
    if(cpt_root == NULL)
    {
        /* the color of NULL is black */
        return black;
    }
    else
    {
        return cpt_root->_t_color;
    }
}

static rbnode_t* _insert_rbnode(rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    rbnode_t* pt_parent = NULL;
    rbnode_t* pt_cur = NULL;
    bool_t    t_result = false;
    bool_t    t_less = false;

    assert(pt_rb_tree != NULL && cpv_value != NULL);

    /* if the rb tree is empty */
    if(_rb_tree_empty(pt_rb_tree))
    {
        /* allocat a new root */
        pt_cur = allocate((alloc_t*)&pt_rb_tree->_t_allocater,
            _RB_TREE_NODE_SIZE(_GET_RB_TREE_TYPE_SIZE(pt_rb_tree)), 1);
        assert(pt_cur != NULL);
        _rb_tree_init_elem_auxiliary(pt_rb_tree, pt_cur);
        /* set its color is black */
        pt_cur->_pt_left = pt_cur->_pt_right = NULL;
        pt_cur->_t_color = black;
        pt_cur->_pt_parent = (rbnode_t*)&pt_rb_tree->_t_rbroot;
        t_result = _GET_RB_TREE_TYPE_SIZE(pt_rb_tree);
        _GET_RB_TREE_TYPE_COPY_FUNCTION(pt_rb_tree)(pt_cur->_pc_data, cpv_value, &t_result);
        assert(t_result);
        /* insert the node */
        pt_rb_tree->_t_rbroot._pt_parent = pt_cur;
    }
    else
    {
        pt_parent = pt_rb_tree->_t_rbroot._pt_parent;

        t_less = _GET_RB_TREE_TYPE_SIZE(pt_rb_tree);
        /*pt_rb_tree->_t_less(cpv_value, pt_parent->_pc_data, &t_less);*/
        _rb_tree_elem_less_auxiliary(pt_rb_tree, cpv_value, pt_parent->_pc_data, &t_less);

        if(t_less)
        {
            pt_cur = pt_parent->_pt_left;
        }
        else
        {
            pt_cur = pt_parent->_pt_right;
        }
        /* from the root to insert position */
        while(pt_cur != NULL)
        {
            /* next current position */
            pt_parent = pt_cur;
            t_less = _GET_RB_TREE_TYPE_SIZE(pt_rb_tree);
            /*pt_rb_tree->_t_less(cpv_value, pt_parent->_pc_data, &t_less);*/
            _rb_tree_elem_less_auxiliary(pt_rb_tree, cpv_value, pt_parent->_pc_data, &t_less);

            if(t_less)
            {
                pt_cur = pt_parent->_pt_left;
            }
            else
            {
                pt_cur = pt_parent->_pt_right;
            }
        }

        /* allocate new node */
        pt_cur = allocate((alloc_t*)&pt_rb_tree->_t_allocater,
            _RB_TREE_NODE_SIZE(_GET_RB_TREE_TYPE_SIZE(pt_rb_tree)), 1);
        assert(pt_cur != NULL);
        _rb_tree_init_elem_auxiliary(pt_rb_tree, pt_cur);

        pt_cur->_pt_left = pt_cur->_pt_right = NULL;
        pt_cur->_t_color = red;
        pt_cur->_pt_parent = pt_parent;
        t_result = _GET_RB_TREE_TYPE_SIZE(pt_rb_tree);
        _GET_RB_TREE_TYPE_COPY_FUNCTION(pt_rb_tree)(pt_cur->_pc_data, cpv_value, &t_result);
        assert(t_result);

        if(t_less)
        {
            assert(pt_parent->_pt_left == NULL);
            pt_parent->_pt_left = pt_cur;
        }
        else
        {
            assert(pt_parent->_pt_right == NULL);
            pt_parent->_pt_right = pt_cur;
        }

        if(_get_color(pt_parent) == red)
        {
            _rebalance_rb_tree(pt_rb_tree, pt_cur);
        }
    }

    return pt_cur;
}

/*
 *     A         B
 *    /         / \       \
 *   B    =>   C   A       \ deasil
 *  / \           /        V
 * C   D         D
 */
static rbnode_t* _deasil_rotate(rbnode_t* pt_root)
{
    rbnode_t* pt_left = NULL;

    assert(pt_root != NULL && pt_root->_pt_left != NULL);
    
    /* rotate */
    pt_left = pt_root->_pt_left;
    pt_root->_pt_left = pt_left->_pt_right;
    pt_left->_pt_right = pt_root;
    /* change parent */
    pt_root->_pt_parent = pt_left;
    if(pt_root->_pt_left != NULL)
    {
        pt_root->_pt_left->_pt_parent = pt_root;
    }

    return pt_left;
}

/*
 *  A              B
 *   \            / \         /
 *    B     =>   A   D       /    widdershins
 *   / \          \          V
 *  C   D          C
 */
static rbnode_t* _widdershins_rotate(rbnode_t* pt_root)
{
    rbnode_t* pt_right = NULL;

    assert(pt_root != NULL && pt_root->_pt_right != NULL);

    /* rotate */
    pt_right = pt_root->_pt_right;
    pt_root->_pt_right = pt_right->_pt_left;
    pt_right->_pt_left = pt_root;
    /* change parent */
    pt_root->_pt_parent = pt_right;
    if(pt_root->_pt_right != NULL)
    {
        pt_root->_pt_right->_pt_parent = pt_root;
    }

    return pt_right;
}

static void _rebalance_rb_tree(rb_tree_t* pt_rb_tree, rbnode_t* pt_pos)
{
    rbnode_t* pt_parent = NULL;
    rbnode_t* pt_sparent = NULL;   /* the sibling of parent */
    rbnode_t* pt_gparent = NULL;   /* grand parent node */
    rbnode_t* pt_ggparent = NULL;  /* grand grand parent node */

    assert(pt_rb_tree != NULL && pt_pos != NULL);

    pt_parent = pt_pos->_pt_parent;
    while(pt_pos != pt_rb_tree->_t_rbroot._pt_parent && 
          _get_color(pt_pos) == red && 
          _get_color(pt_parent) == red)
    {
        assert(pt_parent != pt_rb_tree->_t_rbroot._pt_parent);
        pt_gparent = pt_parent->_pt_parent;
        pt_ggparent = pt_gparent->_pt_parent;

        if(pt_parent == pt_gparent->_pt_left)
        {
            pt_sparent = pt_gparent->_pt_right;
            if(_get_color(pt_sparent) == red)
            {
                /*
                 *     ggp(?)          ggp(?)         ggp(?)       ggp(?) 
                 *      /                /             /            /
                 *     gp(b)     =>   gp(r)      or   gp(b)   =>   gp(r)
                 *    /    \           /   \         /  \         /  \
                 *   p(r)  sp(r)      p(b) sp(b)    p(r) sp(r)   p(b) sp(b)
                 *  /                /               \            \
                 * c(r)             c(r)              c(r)         c(r)
                 *
                 *     ggp(?)         ggp(?)          ggp(?)         ggp(?)
                 *       \              \               \              \
                 *      gp(b)    =>    gp(r)      or    gp(b)    =>   gp(r)
                 *    /    \           /  \             /   \         /  \
                 *   p(r)  sp(r)     p(b) sp(b)       p(r)  sp(r)   p(b) sp(b)
                 *  /                /                  \            \
                 * c(r)            c(r)                 c(r)        c(r)
                 *
                 *     ggp(?)         ggp(?)          ggp(?)         ggp(?)
                 *       |              |               |              |
                 *      gp(b)    =>    gp(b)      or    gp(b)    =>   gp(b)
                 *    /    \           /  \             /   \         /  \
                 *   p(r)  sp(r)     p(b) sp(b)       p(r)  sp(r)   p(b) sp(b)
                 *  /                /                  \            \
                 * c(r)            c(r)                 c(r)        c(r)
                 * gp is root
                 */
                assert(pt_sparent != NULL);
                pt_parent->_t_color = black;
                pt_sparent->_t_color = black;
                if(pt_gparent != pt_rb_tree->_t_rbroot._pt_parent)
                {
                    pt_gparent->_t_color = red;
                }

                pt_pos = pt_gparent;
                pt_parent = pt_ggparent;
            }
            else
            {
                if(pt_pos == pt_parent->_pt_left)
                {
                    /* muset check root first */
                    if(pt_gparent == pt_ggparent->_pt_parent)
                    {
                        /*
                         *      ggp(?)               ggp(?)
                         *       |                     |
                         *      gp(b)      =>          p(b)
                         *    /    \                  /  \
                         *   p(r)  sp(b)             c(r) gp(r)
                         *  /                              \
                         * c(r)                            sp(b)
                         *
                         * gp is root
                         */
                        assert(pt_gparent == pt_rb_tree->_t_rbroot._pt_parent);
                        pt_ggparent->_pt_parent = _deasil_rotate(pt_gparent);
                        pt_ggparent->_pt_parent->_pt_parent = pt_ggparent;
                        assert(pt_parent == pt_ggparent->_pt_parent);
                    }
                    else if(pt_gparent == pt_ggparent->_pt_left)
                    {
                        /*
                         *        ggp(?)               ggp(?)
                         *        /                     /
                         *      gp(b)      =>          p(b)
                         *    /    \                  /  \
                         *   p(r)  sp(b)             c(r) gp(r)
                         *  /                              \
                         * c(r)                            sp(b)
                         */
                        pt_ggparent->_pt_left = _deasil_rotate(pt_gparent);
                        pt_ggparent->_pt_left->_pt_parent = pt_ggparent;
                        assert(pt_parent == pt_ggparent->_pt_left);
                    }
                    else
                    {
                        /*
                         *      ggp(?)               ggp(?)
                         *       \                     \
                         *      gp(b)      =>          p(b)
                         *    /    \                  /  \
                         *   p(r)  sp(b)             c(r) gp(r)
                         *  /                              \
                         * c(r)                            sp(b)
                         */
                        pt_ggparent->_pt_right = _deasil_rotate(pt_gparent);
                        pt_ggparent->_pt_right->_pt_parent = pt_ggparent;
                        assert(pt_parent == pt_ggparent->_pt_right);
                    }

                    pt_parent->_t_color = black;
                    pt_gparent->_t_color = red;
                }
                else
                {
                    /*
                     *        ggp(?)      ggp(?)        ggp(?)          ggp(?)
                     *        /            /              \               \
                     *      gp(b)   =>    gp(b)    or    gp(b)   =>      gp(b)
                     *    /    \         /   \           /  \             /  \
                     *   p(r)  sp(b)    c(r) sp(b)     p(r) sp(b)       c(r) sp(b)
                     *    \            /                \               /
                     *     c(r)       p(r)              c(r)           p(r)
                     *
                     *       ggp(?)      ggp(?)
                     *        |            |
                     *      gp(b)   =>    gp(b)
                     *    /    \         /   \
                     *   p(r)  sp(b)    c(r) sp(b)
                     *    \            /
                     *     c(r)       p(r)
                     * gp is root
                     */
                    pt_gparent->_pt_left = _widdershins_rotate(pt_parent);
                    pt_gparent->_pt_left->_pt_parent = pt_gparent;
                    assert(pt_pos == pt_gparent->_pt_left);

                    /*
                     * check root first, because when root has only one child
                     * the check is error.
                     */
                    if(pt_gparent == pt_ggparent->_pt_parent)
                    {
                        /*
                         *      ggp(?)        ggp(?)
                         *       |             |
                         *>    gp(b)   =>     c(b)
                         *     /   \          /   \
                         *  c(r) sp(b)     p(r) gp(r)
                         *   /                      \
                         * p(r)                   s(b)
                         *
                         * gp is root
                         */
                        assert(pt_gparent == pt_rb_tree->_t_rbroot._pt_parent);
                        pt_ggparent->_pt_parent = _deasil_rotate(pt_gparent);
                        pt_ggparent->_pt_parent->_pt_parent = pt_ggparent;
                        assert(pt_pos == pt_ggparent->_pt_parent);
                    }
                    else if(pt_gparent == pt_ggparent->_pt_left)
                    {
                        /*
                         *      ggp(?)         ggp(?)
                         *       /              /
                         *>    gp(b)   =>     c(b)
                         *     /   \          /   \
                         *  c(r) sp(b)     p(r) gp(r)
                         *   /                      \
                         * p(r)                   s(b)
                         */
                        pt_ggparent->_pt_left = _deasil_rotate(pt_gparent);
                        pt_ggparent->_pt_left->_pt_parent = pt_ggparent;
                        assert(pt_pos == pt_ggparent->_pt_left);
                    }
                    else
                    {
                        /*
                         *      ggp(?)        ggp(?)
                         *       \              \
                         *>    gp(b)   =>     c(b)
                         *     /   \          /   \
                         *  c(r) sp(b)     p(r) gp(r)
                         *   /                      \
                         * p(r)                   s(b)
                         */
                        pt_ggparent->_pt_right = _deasil_rotate(pt_gparent);
                        pt_ggparent->_pt_right->_pt_parent = pt_ggparent;
                        assert(pt_pos == pt_ggparent->_pt_right);
                    }

                    pt_pos->_t_color = black;
                    pt_gparent->_t_color = red;
                }
            }
        }
        else
        {
            pt_sparent = pt_gparent->_pt_left;
            if(_get_color(pt_sparent) == red)
            {
                /*
                 *    ggp(?)      ggp(?)         ggp(?)         ggp(?)
                 *     /           /              /              /
                 *    gp(b)  =>   gp(r)    or    gp(b)   =>    gp(r)
                 *   /    \      /   \          /   \          /  \
                 * sp(r)  p(r)  sp(b) p(b)    sp(r) p(r)    sp(b) p(b)
                 *        /           /               \             \
                 *       c(r)        c(r)             c(r)          c(r)
                 *
                 *    ggp(?)      ggp(?)         ggp(?)       ggp(?)
                 *     \           \              \             \
                 *    gp(b)  =>   gp(r)    or    gp(b)   =>    gp(r)
                 *   /    \      /   \          /   \          /  \
                 * sp(r)  p(r)  sp(b) p(b)    sp(r) p(r)    sp(b) p(b)
                 *        /           /               \             \
                 *       c(r)        c(r)             c(r)          c(r)
                 *
                 *    ggp(?)      ggp(?)         ggp(?)       ggp(?)
                 *     |           |              |             |
                 *    gp(b)  =>   gp(b)    or    gp(b)   =>    gp(b)
                 *   /    \      /   \          /   \          /  \
                 * sp(r)  p(r)  sp(b) p(b)    sp(r) p(r)    sp(b) p(b)
                 *        /           /               \             \
                 *       c(r)        c(r)             c(r)          c(r)
                 * gp is root
                 */
                assert(pt_sparent != NULL);
                pt_parent->_t_color = black;
                pt_sparent->_t_color = black;
                if(pt_gparent != pt_rb_tree->_t_rbroot._pt_parent)
                {
                    pt_gparent->_t_color = red;
                }

                pt_pos = pt_gparent;
                pt_parent = pt_ggparent;
            }
            else
            {
                if(pt_pos == pt_parent->_pt_left)
                {
                    /*
                     *      ggp(?)        ggp(?)           ggp(?)     ggp(?)
                     *       /             /                \           \
                     *      gp(b)   =>    gp(b)     or     gp(b)  =>    gp(b)
                     *    /    \         /   \            /   \         /  \
                     *   sp(b)  p(r)   sp(b)  c(r)      sp(b) p(r)   sp(b) c(r)
                     *          /              \              /             \
                     *         c(r)            p(r)          c(r)           p(r)
                     *
                     *      ggp(?)        ggp(?)
                     *       |             |
                     *      gp(b)   =>    gp(b)
                     *    /    \         /   \
                     *   sp(b)  p(r)   sp(b)  c(r)
                     *          /              \
                     *         c(r)            p(r)
                     * gp is root
                     */
                    pt_gparent->_pt_right = _deasil_rotate(pt_parent);
                    pt_gparent->_pt_right->_pt_parent = pt_gparent;
                    assert(pt_pos == pt_gparent->_pt_right);

                    /* must be check root first */
                    if(pt_gparent == pt_ggparent->_pt_parent)
                    {
                        /*
                         *      ggp(?)           ggp(?)
                         *       |                |
                         *>    gp(b)     =>     c(b)
                         *     /   \            /   \
                         *  sp(b)  c(r)      gp(r) p(r)
                         *           \        /
                         *          p(r)    sp(b)
                         * gp is root
                         */
                        assert(pt_gparent == pt_rb_tree->_t_rbroot._pt_parent);
                        pt_ggparent->_pt_parent = _widdershins_rotate(pt_gparent);
                        pt_ggparent->_pt_parent->_pt_parent = pt_ggparent;
                        assert(pt_pos == pt_ggparent->_pt_parent);
                    }
                    else if(pt_gparent == pt_ggparent->_pt_left)
                    {
                        /*
                         *      ggp(?)           ggp(?)
                         *       /                /
                         *>    gp(b)     =>     c(b)
                         *     /   \            /   \
                         *   sp(b)  c(r)      gp(r) p(r)
                         *           \        /
                         *          p(r)    sp(b)
                         */
                        pt_ggparent->_pt_left = _widdershins_rotate(pt_gparent);
                        pt_ggparent->_pt_left->_pt_parent = pt_ggparent;
                        assert(pt_pos == pt_ggparent->_pt_left);
                    }
                    else
                    {
                        /*
                         *      ggp(?)           ggp(?)
                         *       \                \
                         *>    gp(b)     =>     c(b)
                         *     /   \            /   \
                         *  sp(b)  c(r)      gp(r) p(r)
                         *           \        /
                         *          p(r)    sp(b)
                         */
                        pt_ggparent->_pt_right = _widdershins_rotate(pt_gparent);
                        pt_ggparent->_pt_right->_pt_parent = pt_ggparent;
                        assert(pt_pos == pt_ggparent->_pt_right);
                    }

                    pt_pos->_t_color = black;
                    pt_gparent->_t_color = red;
                }
                else
                {
                    if(pt_gparent == pt_ggparent->_pt_parent)
                    {
                        /*
                         *      ggp(?)            ggp(?)
                         *       |                 |
                         *      gp(b)     =>     p(b)
                         *    /    \             /  \
                         *   sp(b)  p(r)       gp(r) c(r)
                         *           \         /
                         *           c(r)     sp(b)
                         * gp is root
                         */
                        assert(pt_gparent == pt_rb_tree->_t_rbroot._pt_parent);
                        pt_ggparent->_pt_parent = _widdershins_rotate(pt_gparent);
                        pt_ggparent->_pt_parent->_pt_parent = pt_ggparent;
                        assert(pt_parent == pt_ggparent->_pt_parent);
                    }
                    else if(pt_gparent == pt_ggparent->_pt_left)
                    {
                        /*
                         *      ggp(?)            ggp(?)
                         *       /                 /
                         *      gp(b)     =>     p(b)
                         *    /    \             /  \
                         *   sp(b)  p(r)       gp(r) c(r)
                         *           \         /
                         *           c(r)     sp(b)
                         */
                        pt_ggparent->_pt_left = _widdershins_rotate(pt_gparent);
                        pt_ggparent->_pt_left->_pt_parent = pt_ggparent;
                        assert(pt_parent == pt_ggparent->_pt_left);
                    }
                    else
                    {
                        /*
                         *      ggp(?)            ggp(?)
                         *       \                 \
                         *      gp(b)     =>     p(b)
                         *    /    \             /  \
                         *   sp(b)  p(r)       gp(r) c(r)
                         *           \         /
                         *           c(r)     sp(b)
                         */
                        pt_ggparent->_pt_right = _widdershins_rotate(pt_gparent);
                        pt_ggparent->_pt_right->_pt_parent = pt_ggparent;
                        assert(pt_parent == pt_ggparent->_pt_right);
                    }

                    pt_parent->_t_color = black;
                    pt_gparent->_t_color = red;
                }
            }
        }
    }
}

static void _fixup_deletion(rb_tree_t* pt_rb_tree, rbnode_t* pt_pos, rbnode_t* pt_parent)
{
    rbnode_t* pt_sibling = NULL;
    rbnode_t* pt_gparent = NULL;

    assert(pt_rb_tree != NULL && pt_parent != NULL);
    assert(pt_parent->_pt_left != NULL || pt_parent->_pt_right != NULL);

    /* this deletion algorithm refer to <<Introduction in algorithms>> */
    while(pt_pos != pt_rb_tree->_t_rbroot._pt_parent && 
          _get_color(pt_pos) == black)
    {
        pt_gparent = pt_parent->_pt_parent;

        if(pt_pos == pt_parent->_pt_left)
        {
            pt_sibling = pt_parent->_pt_right;
            assert(pt_sibling != NULL);

            if(_get_color(pt_sibling) == red)
            {
                /* Case:1
                 *        gp(?)            gp(?)
                 *         |                |
                 *         p(b)    =>       s(b)
                 *        / \              /   \
                 *     x(b) s(r)         p(r)  r(b)
                 *          /  \         /  \
                 *        l(b) r(b)    x(b) l(b) new s
                 */
                assert(pt_sibling->_pt_left != NULL && 
                       pt_sibling->_pt_right != NULL);
                assert(_get_color(pt_sibling->_pt_left) == black &&
                       _get_color(pt_sibling->_pt_right) == black);

                if(pt_parent == pt_gparent->_pt_parent)
                {
                    assert(pt_parent == pt_rb_tree->_t_rbroot._pt_parent);
                    pt_gparent->_pt_parent = _widdershins_rotate(pt_parent);
                    pt_gparent->_pt_parent->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_parent);
                }
                else if(pt_parent == pt_gparent->_pt_left)
                {
                    pt_gparent->_pt_left = _widdershins_rotate(pt_parent);
                    pt_gparent->_pt_left->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_left);
                }
                else
                {
                    pt_gparent->_pt_right = _widdershins_rotate(pt_parent);
                    pt_gparent->_pt_right->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_right);
                }
                pt_sibling->_t_color = black;
                pt_parent->_t_color = red;
            }
            else if(_get_color(pt_sibling) == black &&
                    _get_color(pt_sibling->_pt_left) == black &&
                    _get_color(pt_sibling->_pt_right) == black)
            {
                /* Case:2
                 *         gp(?)               gp(?)
                 *          |                   |
                 *          p(?)        =>      p(?)  new x
                 *         /  \                /  \
                 *       x(b) s(b)            x(b) s(r)
                 *            /  \                 /  \
                 *           l(b) r(b)            l(b) r(b)
                 */
                pt_sibling->_t_color = red;

                pt_pos = pt_parent;
                pt_parent = pt_pos->_pt_parent;
            }
            else if(_get_color(pt_sibling) == black && 
                    _get_color(pt_sibling->_pt_left) == red && 
                    _get_color(pt_sibling->_pt_right) == black)
            {
                /* Case:3
                 *        gp(?)                    gp(?)
                 *         |                        |
                 *         p(?)          =>         p(?)
                 *        /  \                     /   \
                 *       x(b) s(b)               x(b)  l(b)  new s
                 *            /  \                       \
                 *           l(r) r(b)                    s(r)
                 *                                         \
                 *                                          r(b)
                 */
                rbnode_t* pt_sleft = pt_sibling->_pt_left;
                pt_parent->_pt_right = _deasil_rotate(pt_sibling);
                pt_parent->_pt_right->_pt_parent = pt_parent;
                assert(pt_sleft == pt_parent->_pt_right);

                pt_sleft->_t_color = black;
                pt_sibling->_t_color = red;
            }
            else
            {
                /* Case:4
                 *         gp(?)                   gp(?)
                 *          |                       |
                 *          p(?)          =>       s(?)
                 *         /  \                   /   \
                 *        x(b) s(b)              p(b) r(b)
                 *            /   \             /  \
                 *           l(?) r(r)        x(b) l(?)     new x = root
                 */
                assert(
                    _get_color(pt_sibling) == black && 
                    _get_color(pt_sibling->_pt_right) == red);

                if(pt_parent == pt_gparent->_pt_parent)
                {
                    assert(pt_parent == pt_rb_tree->_t_rbroot._pt_parent);
                    pt_gparent->_pt_parent = _widdershins_rotate(pt_parent);
                    pt_gparent->_pt_parent->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_parent);
                }
                else if(pt_parent == pt_gparent->_pt_left)
                {
                    pt_gparent->_pt_left = _widdershins_rotate(pt_parent);
                    pt_gparent->_pt_left->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_left);
                }
                else
                {
                    pt_gparent->_pt_right = _widdershins_rotate(pt_parent);
                    pt_gparent->_pt_right->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_right);
                }
                pt_sibling->_t_color = pt_parent->_t_color;
                pt_parent->_t_color = black;
                pt_sibling->_pt_right->_t_color = black;

                pt_pos = pt_rb_tree->_t_rbroot._pt_parent;
            }
        }
        else
        {
            pt_sibling = pt_parent->_pt_left;
            assert(pt_sibling != NULL);

            if(_get_color(pt_sibling) == red)
            {
                /* Case:1
                 *        gp(?)            gp(?)
                 *         |                |
                 *         p(b)    =>       s(b)
                 *        /  \             /   \
                 *      s(r) x(b)         l(b)  p(r)
                 *      /  \                    /  \
                 *     l(b) r(b)               r(b) x(b)
                 */
                assert(pt_sibling->_pt_left != NULL && 
                       pt_sibling->_pt_right != NULL);
                assert(_get_color(pt_sibling->_pt_left) == black &&
                       _get_color(pt_sibling->_pt_right) == black);

                if(pt_parent == pt_gparent->_pt_parent)
                {
                    assert(pt_parent == pt_rb_tree->_t_rbroot._pt_parent);
                    pt_gparent->_pt_parent = _deasil_rotate(pt_parent);
                    pt_gparent->_pt_parent->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_parent);
                }
                else if(pt_parent == pt_gparent->_pt_left)
                {
                    pt_gparent->_pt_left = _deasil_rotate(pt_parent);
                    pt_gparent->_pt_left->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_left);
                }
                else
                {
                    pt_gparent->_pt_right = _deasil_rotate(pt_parent);
                    pt_gparent->_pt_right->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_right);
                }
                pt_sibling->_t_color = black;
                pt_parent->_t_color = red;
            }
            else if(_get_color(pt_sibling) == black &&
                    _get_color(pt_sibling->_pt_left) == black &&
                    _get_color(pt_sibling->_pt_right) == black)
            {
                /* Case:2
                 *         gp(?)               gp(?)
                 *          |                   |
                 *          p(?)        =>      p(?)  new x
                 *         /  \                /  \
                 *       s(b) x(b)            s(r) x(b)
                 *      /  \                 /  \
                 *    l(b) r(b)            l(b) r(b)
                 */
                pt_sibling->_t_color = red;

                pt_pos = pt_parent;
                pt_parent = pt_pos->_pt_parent;
            }
            else if(_get_color(pt_sibling) == black && 
                    _get_color(pt_sibling->_pt_left) == black && 
                    _get_color(pt_sibling->_pt_right) == red)
            {
                /* Case:3
                 *        gp(?)                    gp(?)
                 *         |                        |
                 *         p(?)          =>         p(?)
                 *        /  \                     /   \
                 *       s(b) x(b)         new s r(b)  x(b)
                 *      /  \                     /
                 *    l(b) r(r)                s(r)
                 *                             /
                 *                           l(b)
                 */
                rbnode_t* pt_sright = pt_sibling->_pt_right;
                /*pt_parent->_pt_left = _deasil_rotate(pt_sibling);*/
                pt_parent->_pt_left = _widdershins_rotate(pt_sibling);
                pt_parent->_pt_left->_pt_parent = pt_parent;
                assert(pt_sright == pt_parent->_pt_left);

                pt_sright->_t_color = black;
                pt_sibling->_t_color = red;
            }
            else
            {
                /* Case:4
                 *         gp(?)                   gp(?)
                 *          |                       |
                 *          p(?)          =>       s(?)
                 *         /  \                   /   \
                 *        s(b) x(b)              l(b) p(b)
                 *       /   \                        /  \
                 *      l(r) r(?)                    r(?) x(b)     new x = root
                 */
                assert(
                    _get_color(pt_sibling) == black && 
                    _get_color(pt_sibling->_pt_left) == red);

                if(pt_parent == pt_gparent->_pt_parent)
                {
                    assert(pt_parent == pt_rb_tree->_t_rbroot._pt_parent);
                    pt_gparent->_pt_parent = _deasil_rotate(pt_parent);
                    pt_gparent->_pt_parent->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_parent);
                }
                else if(pt_parent == pt_gparent->_pt_left)
                {
                    pt_gparent->_pt_left = _deasil_rotate(pt_parent);
                    pt_gparent->_pt_left->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_left);
                }
                else
                {
                    pt_gparent->_pt_right = _deasil_rotate(pt_parent);
                    pt_gparent->_pt_right->_pt_parent = pt_gparent;
                    assert(pt_sibling == pt_gparent->_pt_right);
                }
                pt_sibling->_t_color = pt_parent->_t_color;
                pt_parent->_t_color = black;
                pt_sibling->_pt_left->_t_color = black;

                pt_pos = pt_rb_tree->_t_rbroot._pt_parent;
            }
        }
    }
    pt_pos->_t_color = black;
}

static void _rb_tree_init_elem_auxiliary(rb_tree_t* pt_rb_tree, rbnode_t* pt_node)
{
    assert(pt_rb_tree != NULL && pt_node != NULL);

    /* initialize new elements */
    if(_GET_RB_TREE_TYPE_STYLE(pt_rb_tree) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_RB_TREE_TYPE_NAME(pt_rb_tree), s_elemtypename);

        _GET_RB_TREE_TYPE_INIT_FUNCTION(pt_rb_tree)(pt_node->_pc_data, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_RB_TREE_TYPE_SIZE(pt_rb_tree);
        _GET_RB_TREE_TYPE_INIT_FUNCTION(pt_rb_tree)(pt_node->_pc_data, &t_result);
        assert(t_result);
    }
}

static void _rb_tree_elem_less_auxiliary(const rb_tree_t* cpt_rb_tree,
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpt_rb_tree != NULL && cpv_first != NULL &&
           cpv_second != NULL && pv_output != NULL); 

    if(strncmp(_GET_RB_TREE_TYPE_BASENAME(cpt_rb_tree),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0 &&
       cpt_rb_tree->_t_less != _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_rb_tree))
    {
        cpt_rb_tree->_t_less(string_c_str((string_t*)cpv_first),
            string_c_str((string_t*)cpv_second), pv_output);
    }
    else
    {
        cpt_rb_tree->_t_less(cpv_first, cpv_second, pv_output);
    }
}

/** eof **/

