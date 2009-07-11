/*
 *  The implementation of avl tree.
 *  Copyright (C)  2008 2009  Wangbo
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

#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"

#include "cstring.h"

/** local constant declaration and local macro section **/
#define _AVL_TREE_NODE_SIZE(typesize)\
    ((typesize) + sizeof(avlnode_t) - 1)

/* macros for type informations */
#define _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree)\
    ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_AVL_TREE_TYPE_NAME(pt_avl_tree)\
    ((pt_avl_tree)->_t_typeinfo._sz_typename)
#define _GET_AVL_TREE_TYPE_BASENAME(pt_avl_tree)\
    ((pt_avl_tree)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_AVL_TREE_TYPE_INIT_FUNCTION(pt_avl_tree)\
    ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_AVL_TREE_TYPE_COPY_FUNCTION(pt_avl_tree)\
    ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_AVL_TREE_TYPE_LESS_FUNCTION(pt_avl_tree)\
    ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_AVL_TREE_TYPE_DESTROY_FUNCTION(pt_avl_tree)\
    ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_AVL_TREE_TYPE_STYLE(pt_avl_tree)\
    ((pt_avl_tree)->_t_typeinfo._t_style)

/** local data type declaration and local struct, union, enum section **/
/* this struct if for _insert_avlnode function */
typedef struct _taginsertresult
{
    avlnode_t* _pt_adjust;   /* the adjusted root avlnode_t pointer */
    avlnode_t* _pt_new;      /* the new inserting avlnode_t* pointer */
}_insert_result_t;

/** local function prototype section **/
#ifndef NDEBUG
/*
 * Assert support.
 */
static bool_t _avl_tree_iterator_belong_to_avl_tree(
    const avl_tree_t* cpt_avl_tree, avl_tree_iterator_t t_iter);
static bool_t _avl_tree_same_type(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);
static bool_t _avl_tree_same_avl_tree_iterator_type(
    const avl_tree_t* cpt_avl_tree, avl_tree_iterator_t t_iter);
static bool_t _find_iterator(
    const avlnode_t* cpt_root, const avlnode_t* cpt_pos);
#endif /* NDEBUG */

/*
 * Travel subtree for find the value in preorder.
 */
static avlnode_t* _find_value(
    const avl_tree_t* cpt_avl_tree, const avlnode_t* cpt_root, const void* cpv_value); 

/*
 * Destroy the subtree with postorder traverse.
 */
static avlnode_t* _destroy_avl_tree(avl_tree_t* pt_avl_tree, avlnode_t* pt_root);

/*
 * Rotate.
 */
/* ll rotate */
static avlnode_t* _left_signal_rotate(avlnode_t* pt_root);
/* rr rotate */
static avlnode_t* _right_signal_rotate(avlnode_t* pt_root);
/* lr rotate */
static avlnode_t* _left_double_rotate(avlnode_t* pt_root);
/* rl rotate */
static avlnode_t* _right_double_rotate(avlnode_t* pt_root);

/*
 * Insert the value into subtree.
 */
static _insert_result_t _insert_avlnode(
    const avl_tree_t* cpt_avl_tree, avlnode_t* pt_root, const void* cpv_value);

/*
 * Get avl node height.
 */
static int _get_height(const avlnode_t* cpt_root);

/*
 * Get minimum and maximum avlnode pointer.
 */
static avlnode_t* _get_min_avlnode(const avlnode_t* cpt_root);
static avlnode_t* _get_max_avlnode(const avlnode_t* cpt_root);

/*
 * Rebalance the subtree and update the root height.
 */
static avlnode_t* _rebalance_avl_tree(avlnode_t* pt_root);

/* initialize element auxiliary function */
static void _avl_tree_init_elem_auxiliary(avl_tree_t* pt_avl_tree, avlnode_t* pt_node);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* avl tree iterator function */
avl_tree_iterator_t _create_avl_tree_iterator(void)
{
    avl_tree_iterator_t t_newiterator;

    _GET_AVL_TREE_COREPOS(t_newiterator) = NULL;
    _GET_AVL_TREE_POINTER(t_newiterator) = NULL;

    _GET_CONTAINER(t_newiterator) = NULL;

    return t_newiterator;
}

bool_t _avl_tree_iterator_equal(
    avl_tree_iterator_t t_iterfirst, avl_tree_iterator_t t_itersecond)
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

void _avl_tree_iterator_get_value(avl_tree_iterator_t t_iter, void* pv_value)
{
    assert(pv_value != NULL);
    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_iter), t_iter));
    assert(!_avl_tree_iterator_equal(t_iter, _avl_tree_end(_GET_AVL_TREE(t_iter))));

    /* char* */
    if(strncmp(_GET_AVL_TREE_TYPE_BASENAME(_GET_AVL_TREE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        *(char**)pv_value = (char*)string_c_str(
            (string_t*)((avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        bool_t t_result = _GET_AVL_TREE_TYPE_SIZE(_GET_AVL_TREE(t_iter));
        _GET_AVL_TREE_TYPE_COPY_FUNCTION(_GET_AVL_TREE(t_iter))(
            pv_value, ((avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter))->_pc_data, &t_result);
        assert(t_result);
    }
}

const void* _avl_tree_iterator_get_pointer(avl_tree_iterator_t t_iter)
{
    assert(_avl_tree_iterator_belong_to_avl_tree(_GET_AVL_TREE(t_iter), t_iter));
    assert(!_avl_tree_iterator_equal(t_iter, _avl_tree_end(_GET_AVL_TREE(t_iter))));

    /* char* */
    if(strncmp(_GET_AVL_TREE_TYPE_BASENAME(_GET_AVL_TREE(t_iter)),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        return (char*)string_c_str(
            (string_t*)((avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter))->_pc_data);
    }
    else
    {
        return ((avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter))->_pc_data;
    }
}

avl_tree_iterator_t _avl_tree_iterator_next(avl_tree_iterator_t t_iter)
{
    avlnode_t* pt_next = NULL;  /* next pos */
    avlnode_t* pt_cur = (avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter);

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

avl_tree_iterator_t _avl_tree_iterator_prev(avl_tree_iterator_t t_iter)
{
    avlnode_t* pt_prev = NULL;
    avlnode_t* pt_cur = (avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter);

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
    avl_tree_iterator_t t_iterfirst, avl_tree_iterator_t t_itersecond)
{
    avl_tree_iterator_t t_iterator;
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
    avl_tree_iterator_t t_iterfirst, avl_tree_iterator_t t_itersecond)
{
    avl_tree_iterator_t t_iterator;
    avl_tree_t*         pt_avl_tree = NULL;

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
avl_tree_t* _create_avl_tree(const char* s_typename)
{
    avl_tree_t* pt_avl_tree = NULL;
    _typeinfo_t t_typeinfo;

    assert(s_typename != NULL);

    /* get type information */
    _type_get_type(&t_typeinfo, s_typename);
    if(t_typeinfo._t_style == _TYPE_INVALID)
    {
        return NULL;
    }

    if((pt_avl_tree = (avl_tree_t*)malloc(sizeof(avl_tree_t))) == NULL)
    {
        return NULL;
    }
    memset(pt_avl_tree->_t_typeinfo._sz_typename, '\0', _TYPE_NAME_SIZE + 1);
    strncpy(pt_avl_tree->_t_typeinfo._sz_typename, t_typeinfo._sz_typename, _TYPE_NAME_SIZE);
    pt_avl_tree->_t_typeinfo._t_style = t_typeinfo._t_style;
    pt_avl_tree->_t_typeinfo._pt_type = t_typeinfo._pt_type;

    pt_avl_tree->_t_avlroot._pt_parent = NULL;
    pt_avl_tree->_t_avlroot._pt_left = NULL;
    pt_avl_tree->_t_avlroot._pt_right = NULL;
    pt_avl_tree->_t_avlroot._un_height = 0;
    pt_avl_tree->_t_nodecount = 0;

    pt_avl_tree->_t_less = NULL;

    return pt_avl_tree;
}

bool_t _create_avl_tree_auxiliary(avl_tree_t* pt_avl_tree, const char* s_typename)
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

    pt_avl_tree->_t_less = NULL;

    return true;
}

void _avl_tree_init(avl_tree_t* pt_avl_tree, binary_function_t t_less)
{
    assert(pt_avl_tree != NULL &&
           pt_avl_tree->_t_nodecount == 0 &&
           pt_avl_tree->_t_avlroot._pt_parent == NULL &&
           pt_avl_tree->_t_avlroot._pt_left == NULL &&
           pt_avl_tree->_t_avlroot._pt_right == NULL &&
           pt_avl_tree->_t_avlroot._un_height == 0 &&
           pt_avl_tree->_t_less == NULL);

    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;

    allocate_init(&pt_avl_tree->_t_allocater);

    if(t_less != NULL)
    {
        pt_avl_tree->_t_less = t_less;
    }
    else
    {
        pt_avl_tree->_t_less = _GET_AVL_TREE_TYPE_LESS_FUNCTION(pt_avl_tree);
    }
}

void _avl_tree_destroy_auxiliary(avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);

    /* destroy all elements */
    pt_avl_tree->_t_avlroot._pt_parent = 
        _destroy_avl_tree(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_nodecount = 0;

    /* destroy allocator */
    allocate_destroy(&pt_avl_tree->_t_allocater);

    pt_avl_tree->_t_less = NULL;
}

void _avl_tree_destroy(avl_tree_t* pt_avl_tree)
{
    _avl_tree_destroy_auxiliary(pt_avl_tree);
    free(pt_avl_tree);
}

void _avl_tree_init_copy(
    avl_tree_t* pt_avl_tree_dest, const avl_tree_t* cpt_avl_tree_src)
{
    assert(pt_avl_tree_dest != NULL && cpt_avl_tree_src != NULL);
    assert(pt_avl_tree_dest->_t_typeinfo._pt_type == cpt_avl_tree_src->_t_typeinfo._pt_type);

    /* init the avl tree with the src avl tree */
    _avl_tree_init(pt_avl_tree_dest,  cpt_avl_tree_src->_t_less);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(cpt_avl_tree_src))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest,
            _avl_tree_begin(cpt_avl_tree_src), _avl_tree_end(cpt_avl_tree_src));
    }
}

void _avl_tree_init_copy_range(
    avl_tree_t* pt_avl_tree_dest, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end)
{
    assert(pt_avl_tree_dest != NULL);
    assert(pt_avl_tree_dest->_t_typeinfo._pt_type ==
           _GET_AVL_TREE(t_begin)->_t_typeinfo._pt_type);
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    /* init the avl tree with the src avl tree */
    _avl_tree_init(pt_avl_tree_dest, _GET_AVL_TREE(t_begin)->_t_less);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(_GET_AVL_TREE(t_begin)))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest, t_begin, t_end);
    }
}

void _avl_tree_init_copy_range_ex(
    avl_tree_t* pt_avl_tree_dest, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end,
    binary_function_t t_less)
{
    assert(pt_avl_tree_dest != NULL);
    assert(pt_avl_tree_dest->_t_typeinfo._pt_type ==
           _GET_AVL_TREE(t_begin)->_t_typeinfo._pt_type);
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    /* init the avl tree with the src avl tree */
    _avl_tree_init(pt_avl_tree_dest, t_less);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(_GET_AVL_TREE(t_begin)))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest, t_begin, t_end);
    }
}

void _avl_tree_assign(avl_tree_t* pt_avl_tree_dest, const avl_tree_t* cpt_avl_tree_src)
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

bool_t _avl_tree_empty(const avl_tree_t* cpt_avl_tree)
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

size_t _avl_tree_size(const avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    return cpt_avl_tree->_t_nodecount;
}

size_t _avl_tree_max_size(const avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    return (size_t)(-1) / _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
}

avl_tree_iterator_t _avl_tree_begin(const avl_tree_t* cpt_avl_tree)
{
    avl_tree_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_newiterator) = (char*)cpt_avl_tree->_t_avlroot._pt_left;

    return t_newiterator;
}

avl_tree_iterator_t _avl_tree_end(const avl_tree_t* cpt_avl_tree)
{
    avl_tree_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_newiterator) = (char*)&cpt_avl_tree->_t_avlroot;

    return t_newiterator;
}

avl_tree_reverse_iterator_t _avl_tree_rbegin(const avl_tree_t* cpt_avl_tree)
{
    avl_tree_reverse_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_newiterator) = (char*)cpt_avl_tree->_t_avlroot._pt_right;

    return t_newiterator;
}

avl_tree_reverse_iterator_t _avl_tree_rend(const avl_tree_t* cpt_avl_tree)
{
    avl_tree_reverse_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_newiterator) = (char*)&cpt_avl_tree->_t_avlroot;

    return t_newiterator;
}

binary_function_t _avl_tree_key_less(const avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    return cpt_avl_tree->_t_less;
}

avl_tree_iterator_t _avl_tree_find(const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    _GET_AVL_TREE_POINTER(t_iterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_iterator) = (char*)_find_value(
            cpt_avl_tree, cpt_avl_tree->_t_avlroot._pt_parent, cpv_value);
    if(_GET_AVL_TREE_COREPOS(t_iterator) == NULL)
    {
        _GET_AVL_TREE_COREPOS(t_iterator) = (char*)&cpt_avl_tree->_t_avlroot;
    }

    return t_iterator;
}

void _avl_tree_clear(avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);

    /* destroy all elements */
    pt_avl_tree->_t_avlroot._pt_parent =
        _destroy_avl_tree(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_nodecount = 0;
}

size_t _avl_tree_count(const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    range_t t_range;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_range = _avl_tree_equal_range(cpt_avl_tree, cpv_value);
    return abs(_avl_tree_iterator_distance(t_range.t_begin, t_range.t_end));
}

avl_tree_iterator_t _avl_tree_lower_bound(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    avlnode_t*          pt_cur = NULL;
    avlnode_t*          pt_prev = NULL;
    bool_t              t_less = false;
    bool_t              t_great = false;
    avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_iterator = _create_avl_tree_iterator();
    _GET_AVL_TREE_POINTER(t_iterator) = (void*)cpt_avl_tree;

    if(!_avl_tree_empty(cpt_avl_tree))
    {
        pt_prev = cpt_avl_tree->_t_avlroot._pt_parent;

        t_less = t_great = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
        cpt_avl_tree->_t_less(cpv_value, pt_prev->_pc_data, &t_less);
        cpt_avl_tree->_t_less(pt_prev->_pc_data, cpv_value, &t_great);
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
            t_less = t_great = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
            cpt_avl_tree->_t_less(cpv_value, pt_prev->_pc_data, &t_less);
            cpt_avl_tree->_t_less(pt_prev->_pc_data, cpv_value, &t_great);
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

avl_tree_iterator_t _avl_tree_upper_bound(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    avlnode_t*          pt_cur = NULL;
    avlnode_t*          pt_prev = NULL;
    bool_t              t_result = false;
    avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_iterator = _create_avl_tree_iterator();
    _GET_AVL_TREE_POINTER(t_iterator) = (void*)cpt_avl_tree;

    if(!_avl_tree_empty(cpt_avl_tree))
    {
        pt_prev = cpt_avl_tree->_t_avlroot._pt_parent;
        t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
        cpt_avl_tree->_t_less(cpv_value, pt_prev->_pc_data, &t_result);
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
            cpt_avl_tree->_t_less(cpv_value, pt_prev->_pc_data, &t_result);
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
    const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    range_t t_range;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_range.t_begin = _avl_tree_lower_bound(cpt_avl_tree, cpv_value);
    t_range.t_end = _avl_tree_upper_bound(cpt_avl_tree, cpv_value);

    return t_range;
}

bool_t _avl_tree_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    avl_tree_iterator_t t_first;
    avl_tree_iterator_t t_second;
    bool_t              t_less = false;
    bool_t              t_great = false;

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
        t_less = t_great = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_treefirst);
        cpt_avl_treefirst->_t_less(((avlnode_t*)_GET_AVL_TREE_COREPOS(t_first))->_pc_data,
            ((avlnode_t*)_GET_AVL_TREE_COREPOS(t_second))->_pc_data, &t_less);
        cpt_avl_treefirst->_t_less(((avlnode_t*)_GET_AVL_TREE_COREPOS(t_second))->_pc_data,
            ((avlnode_t*)_GET_AVL_TREE_COREPOS(t_first))->_pc_data, &t_great);
        if(t_less || t_great)
        {
            return false;
        }
    }
    assert(_avl_tree_iterator_equal(t_first, _avl_tree_end(cpt_avl_treefirst)) &&
           _avl_tree_iterator_equal(t_second, _avl_tree_end(cpt_avl_treesecond)));

    return true;
}

bool_t _avl_tree_not_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    return!_avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond);
}

bool_t _avl_tree_less(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    avl_tree_iterator_t t_first;
    avl_tree_iterator_t t_second;
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
        cpt_avl_treefirst->_t_less(((avlnode_t*)_GET_AVL_TREE_COREPOS(t_first))->_pc_data,
            ((avlnode_t*)_GET_AVL_TREE_COREPOS(t_second))->_pc_data, &t_result);
        if(t_result)
        {
            return true;
        }
        t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_treefirst);
        cpt_avl_treefirst->_t_less(((avlnode_t*)_GET_AVL_TREE_COREPOS(t_second))->_pc_data,
            ((avlnode_t*)_GET_AVL_TREE_COREPOS(t_first))->_pc_data, &t_result);
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
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    return (_avl_tree_less(cpt_avl_treefirst, cpt_avl_treesecond) ||
            _avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond)) ? true : false;
}

bool_t _avl_tree_great(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    return _avl_tree_less(cpt_avl_treesecond, cpt_avl_treefirst);
}

bool_t _avl_tree_great_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    return (_avl_tree_great(cpt_avl_treefirst, cpt_avl_treesecond) ||
            _avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond)) ? true : false;
}

void _avl_tree_swap(avl_tree_t* pt_avl_treefirst, avl_tree_t* pt_avl_treesecond)
{
    avl_tree_t t_avl_treetmp;

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

avl_tree_iterator_t _avl_tree_insert_equal(avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    _insert_result_t    t_insert_result;
    avl_tree_iterator_t t_iterator = _create_avl_tree_iterator();

    assert(pt_avl_tree != NULL && cpv_value != NULL);

    t_insert_result = _insert_avlnode(
        pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, cpv_value);
    assert(t_insert_result._pt_adjust != NULL && t_insert_result._pt_new != NULL);

    pt_avl_tree->_t_avlroot._pt_parent = t_insert_result._pt_adjust;
    pt_avl_tree->_t_avlroot._pt_parent->_pt_parent = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_left = _get_min_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    pt_avl_tree->_t_avlroot._pt_right = _get_max_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    pt_avl_tree->_t_nodecount++;

    _GET_AVL_TREE_POINTER(t_iterator) = pt_avl_tree;
    _GET_AVL_TREE_COREPOS(t_iterator) = (char*)t_insert_result._pt_new;

    return t_iterator;
}

avl_tree_iterator_t _avl_tree_insert_unique(avl_tree_t* pt_avl_tree, const void* cpv_value)
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
        avl_tree_iterator_t t_iter = _avl_tree_find(pt_avl_tree, cpv_value);
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
    avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end)
{
    avl_tree_iterator_t t_iterator;

    assert(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, t_begin));
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_avl_tree_iterator_equal(t_iterator, t_end);
        t_iterator = _avl_tree_iterator_next(t_iterator))
    {
        _avl_tree_insert_equal(
            pt_avl_tree, ((avlnode_t*)_GET_AVL_TREE_COREPOS(t_iterator))->_pc_data);
    }
}

void _avl_tree_insert_unique_range(
    avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end)
{
    avl_tree_iterator_t t_iterator;

    assert(_avl_tree_same_avl_tree_iterator_type(pt_avl_tree, t_begin));
    assert(_avl_tree_iterator_equal(t_begin, t_end) ||
           _avl_tree_iterator_before(t_begin, t_end));

    for(t_iterator = t_begin;
        !_avl_tree_iterator_equal(t_iterator, t_end);
        t_iterator = _avl_tree_iterator_next(t_iterator))
    {
        _avl_tree_insert_unique(
            pt_avl_tree, ((avlnode_t*)_GET_AVL_TREE_COREPOS(t_iterator))->_pc_data);
    }
}

void _avl_tree_erase_pos(avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_pos)
{
    avlnode_t* pt_parent = NULL;
    avlnode_t* pt_cur = NULL;
    bool_t     t_result = false;

    assert(_avl_tree_iterator_belong_to_avl_tree(pt_avl_tree, t_pos));
    assert(!_avl_tree_iterator_equal(t_pos, _avl_tree_end(pt_avl_tree)));
    
    pt_cur = (avlnode_t*)_GET_AVL_TREE_COREPOS(t_pos);
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
        avlnode_t* pt_parenttmp = NULL;
        avlnode_t* pt_curtmp = NULL;

        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_curtmp = _get_min_avlnode(pt_cur->_pt_right);
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
            pt_curtmp = _get_min_avlnode(pt_cur->_pt_right);
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
            pt_curtmp = _get_min_avlnode(pt_cur->_pt_right);
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
        avlnode_t* pt_newcur = pt_parent;
        pt_parent = pt_newcur->_pt_parent;
        while(pt_parent != &pt_avl_tree->_t_avlroot)
        {
            if(pt_newcur == pt_parent->_pt_left)
            {
                pt_parent->_pt_left = _rebalance_avl_tree(pt_parent->_pt_left);
                pt_parent->_pt_left->_pt_parent = pt_parent;
            }
            else
            {
                pt_parent->_pt_right = _rebalance_avl_tree(pt_parent->_pt_right);
                pt_parent->_pt_right->_pt_parent = pt_parent;
            }

            pt_newcur = pt_parent;
            pt_parent = pt_newcur->_pt_parent;
        }
    }

    /* rebalance root */
    if(pt_parent->_pt_parent != NULL)
    {
        pt_parent->_pt_parent = _rebalance_avl_tree(pt_parent->_pt_parent);
        pt_parent->_pt_parent->_pt_parent = pt_parent;
    }

    /* destroy node */
    t_result = _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree);
    _GET_AVL_TREE_TYPE_DESTROY_FUNCTION(pt_avl_tree)(pt_cur->_pc_data, &t_result);
    assert(t_result);
    deallocate(&pt_avl_tree->_t_allocater, pt_cur,
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
            _get_min_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
        pt_avl_tree->_t_avlroot._pt_right = 
            _get_max_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    }
}

void _avl_tree_erase_range(
    avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_begin, avl_tree_iterator_t t_end)
{
    avl_tree_iterator_t t_iterator;
    avl_tree_iterator_t t_next;

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

size_t _avl_tree_erase(avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    size_t t_countsize = _avl_tree_count(pt_avl_tree, cpv_value);
    range_t t_range = _avl_tree_equal_range(pt_avl_tree, cpv_value);

    if(!_avl_tree_iterator_equal(t_range.t_begin, _avl_tree_end(pt_avl_tree)))
    {
        _avl_tree_erase_range(pt_avl_tree, t_range.t_begin, t_range.t_end);
    }

    return t_countsize;
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _avl_tree_iterator_belong_to_avl_tree(
    const avl_tree_t* cpt_avl_tree, avl_tree_iterator_t t_iter)
{
    assert(cpt_avl_tree != NULL);
    assert(_GET_AVL_TREE_COREPOS(t_iter) != NULL);
    assert(_GET_AVL_TREE(t_iter) == cpt_avl_tree);

    /* if iterator is end */
    if(_GET_AVL_TREE_COREPOS(t_iter) == (char*)&cpt_avl_tree->_t_avlroot)
    {
        return true;
    }
    /* else travel avl tree for search the pointer */
    else
    {
        return _find_iterator(cpt_avl_tree->_t_avlroot._pt_parent, 
            (avlnode_t*)_GET_AVL_TREE_COREPOS(t_iter));
    }
}

static bool_t _avl_tree_same_type(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    assert(cpt_avl_treefirst != NULL && cpt_avl_treesecond != NULL);

    return _type_is_same(_GET_AVL_TREE_TYPE_NAME(cpt_avl_treefirst),
                         _GET_AVL_TREE_TYPE_NAME(cpt_avl_treesecond)) &&
           (cpt_avl_treefirst->_t_typeinfo._t_style ==
            cpt_avl_treesecond->_t_typeinfo._t_style) &&
           (cpt_avl_treefirst->_t_typeinfo._pt_type ==
            cpt_avl_treesecond->_t_typeinfo._pt_type) &&
           (cpt_avl_treefirst->_t_less == cpt_avl_treesecond->_t_less);
}

static bool_t _avl_tree_same_avl_tree_iterator_type(
    const avl_tree_t* cpt_avl_tree, avl_tree_iterator_t t_iter)
{
    assert(cpt_avl_tree != NULL && _GET_AVL_TREE(t_iter) != NULL);

    return _avl_tree_same_type(cpt_avl_tree, _GET_AVL_TREE(t_iter));
}

static bool_t _find_iterator(const avlnode_t* cpt_root, const avlnode_t* cpt_pos)
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
#endif /* NDEBUG */

static avlnode_t* _find_value(
    const avl_tree_t* cpt_avl_tree, const avlnode_t* cpt_root, const void* cpv_value) 
{
    bool_t t_result = false;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    if(cpt_root == NULL)
    {
        return NULL;
    }

    t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
    cpt_avl_tree->_t_less(cpv_value, cpt_root->_pc_data, &t_result);
    if(t_result)
    {
        return _find_value(cpt_avl_tree, cpt_root->_pt_left, cpv_value);
    }

    t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
    cpt_avl_tree->_t_less(cpt_root->_pc_data, cpv_value, &t_result);
    if(t_result)
    {
        return _find_value(cpt_avl_tree, cpt_root->_pt_right, cpv_value);
    }
    else
    {
        return (avlnode_t*)cpt_root;
    }
}

static avlnode_t* _destroy_avl_tree(avl_tree_t* pt_avl_tree, avlnode_t* pt_root)
{
    bool_t t_result = false;

    assert(pt_avl_tree != NULL);

    if(pt_root != NULL)
    {
        pt_root->_pt_left = _destroy_avl_tree(pt_avl_tree, pt_root->_pt_left);
        pt_root->_pt_right = _destroy_avl_tree(pt_avl_tree, pt_root->_pt_right);

        assert(pt_root->_pt_left == NULL && pt_root->_pt_right == NULL);

        t_result = _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree);
        _GET_AVL_TREE_TYPE_DESTROY_FUNCTION(pt_avl_tree)(pt_root->_pc_data, &t_result);
        assert(t_result);
        deallocate(&pt_avl_tree->_t_allocater, pt_root,
            _AVL_TREE_NODE_SIZE(_GET_AVL_TREE_TYPE_SIZE(pt_avl_tree)), 1);
    }
    
    return NULL;
}

/*
 *     A         B
 *    /         / \
 *   B    =>   C   A
 *  / \           /
 * C   D         D
 */
static avlnode_t* _left_signal_rotate(avlnode_t* pt_root)
{
    avlnode_t* pt_left = NULL;

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
    /* update height */
    pt_root->_un_height = (unsigned int)(
        (_get_height(pt_root->_pt_left) > _get_height(pt_root->_pt_right) ?
         _get_height(pt_root->_pt_left) : _get_height(pt_root->_pt_right))+1);
    pt_left->_un_height = (unsigned int)(
        (_get_height(pt_left->_pt_left) > _get_height(pt_left->_pt_right) ?
         _get_height(pt_left->_pt_left) : _get_height(pt_left->_pt_right))+1);

    return pt_left;
}

/*
 *  A              B
 *   \            / \
 *    B     =>   A   D
 *   / \          \
 *  C   D          C
 */
static avlnode_t* _right_signal_rotate(avlnode_t* pt_root)
{
    avlnode_t* pt_right = NULL;

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
    /* update height */
    pt_root->_un_height = (unsigned int)(
        (_get_height(pt_root->_pt_left) > _get_height(pt_root->_pt_right) ?
         _get_height(pt_root->_pt_left) : _get_height(pt_root->_pt_right))+1);
    pt_right->_un_height = (unsigned int)(
        (_get_height(pt_right->_pt_left) > _get_height(pt_right->_pt_right) ?
         _get_height(pt_right->_pt_left) : _get_height(pt_right->_pt_right))+1);

    return pt_right;
}

/*
 *       A               A                 E
 *      / \             / \              /   \
 *     B   C           E   C            B     A
 *    / \       =>    / \        =>    / \   / \
 *   D   E           B   G            D   F G   C
 *      / \         / \
 *     F   G       D   F
 */        
static avlnode_t* _left_double_rotate(avlnode_t* pt_root)
{
    assert(pt_root != NULL);

    pt_root->_pt_left = _right_signal_rotate(pt_root->_pt_left);
    pt_root->_pt_left->_pt_parent = pt_root;
    return _left_signal_rotate(pt_root);
}

/*
 *       A               A                   D 
 *      / \             / \                /   \
 *     B   C           B   D              A     C
 *        / \    =>       / \       =>   / \   / \
 *       D   E           F   C          B   F G   E
 *      / \                 / \
 *     F   G               G   E
 */
static avlnode_t* _right_double_rotate(avlnode_t* pt_root)
{
    assert(pt_root != NULL);

    pt_root->_pt_right = _left_signal_rotate(pt_root->_pt_right);
    pt_root->_pt_right->_pt_parent = pt_root;
    return _right_signal_rotate(pt_root);
}

static int _get_height(const avlnode_t* cpt_root)
{
    if(cpt_root == NULL)
    {
        return -1;
    }
    else
    {
        return (int)cpt_root->_un_height;
    }
}

static avlnode_t* _get_min_avlnode(const avlnode_t* cpt_root)
{
    avlnode_t* pt_min = (avlnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while(pt_min->_pt_left != NULL)
    {
        pt_min = pt_min->_pt_left;
    }

    return pt_min;
}

static avlnode_t* _get_max_avlnode(const avlnode_t* cpt_root)
{
    avlnode_t* pt_max = (avlnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while(pt_max->_pt_right != NULL)
    {
        pt_max = pt_max->_pt_right;
    }

    return pt_max;
}

static _insert_result_t _insert_avlnode(
    const avl_tree_t* cpt_avl_tree, avlnode_t* pt_root, const void* cpv_value)
{
    _insert_result_t t_insert_result;
    bool_t           t_result = false;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    /* if root is NULL then allocate memory */
    if(pt_root == NULL)
    {
        pt_root = allocate((alloc_t*)&cpt_avl_tree->_t_allocater,
            _AVL_TREE_NODE_SIZE(_GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree)), 1);
        assert(pt_root != NULL);
        _avl_tree_init_elem_auxiliary((avl_tree_t*)cpt_avl_tree, pt_root);

        pt_root->_pt_left = pt_root->_pt_right = NULL;
        pt_root->_un_height = 0;
        t_insert_result._pt_adjust = pt_root;
        t_insert_result._pt_new = pt_root;
        t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
        _GET_AVL_TREE_TYPE_COPY_FUNCTION(cpt_avl_tree)(
            pt_root->_pc_data, cpv_value, &t_result);
        assert(t_result);

        return t_insert_result;
    }

    /* compare the value and current node */
    /* if value < current node then insert into left subtree */
    t_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
    cpt_avl_tree->_t_less(cpv_value, pt_root->_pc_data, &t_result);
    if(t_result)
    {
        t_insert_result = _insert_avlnode(cpt_avl_tree, pt_root->_pt_left, cpv_value);
        pt_root->_pt_left = t_insert_result._pt_adjust;
        pt_root->_pt_left->_pt_parent = pt_root;

        pt_root = _rebalance_avl_tree(pt_root);
        t_insert_result._pt_adjust = pt_root;

        return t_insert_result;
    }
    /* else insert into right subtree */
    else
    {
        t_insert_result = _insert_avlnode(cpt_avl_tree, pt_root->_pt_right, cpv_value);
        pt_root->_pt_right =  t_insert_result._pt_adjust;
        pt_root->_pt_right->_pt_parent = pt_root;

        pt_root = _rebalance_avl_tree(pt_root);
        t_insert_result._pt_adjust = pt_root;

        return t_insert_result;
    }
}

static avlnode_t* _rebalance_avl_tree(avlnode_t* pt_root)
{
    if(pt_root != NULL)
    {
        /* if left - right > 1 */
        if(_get_height(pt_root->_pt_left) - _get_height(pt_root->_pt_right) > 1)
        {
            /* ll */
            if(_get_height(pt_root->_pt_left->_pt_left) >=
               _get_height(pt_root->_pt_left->_pt_right))
            {
                pt_root = _left_signal_rotate(pt_root);
            }
            /* lr */
            else
            {
                pt_root = _left_double_rotate(pt_root);
            }
        }
        /* else if right - left > 1 */
        else if(_get_height(pt_root->_pt_right) - _get_height(pt_root->_pt_left) > 1)
        {
            /* rr */
            if(_get_height(pt_root->_pt_right->_pt_right) >= 
               _get_height(pt_root->_pt_right->_pt_left))
            {
                pt_root = _right_signal_rotate(pt_root);
            }
            /* rl */
            else
            {
                pt_root = _right_double_rotate(pt_root);
            }
        }

        pt_root->_un_height = (unsigned int)(
            (_get_height(pt_root->_pt_left) > _get_height(pt_root->_pt_right) ?
             _get_height(pt_root->_pt_left) : _get_height(pt_root->_pt_right)) + 1);
    }

    return pt_root;
}

static void _avl_tree_init_elem_auxiliary(avl_tree_t* pt_avl_tree, avlnode_t* pt_node)
{
    assert(pt_avl_tree != NULL && pt_node != NULL);

    /* initialize new elements */
    if(_GET_AVL_TREE_TYPE_STYLE(pt_avl_tree) == _TYPE_CSTL_BUILTIN)
    {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_AVL_TREE_TYPE_NAME(pt_avl_tree), s_elemtypename);

        _GET_AVL_TREE_TYPE_INIT_FUNCTION(pt_avl_tree)(pt_node->_pc_data, s_elemtypename);
    }
    else
    {
        bool_t t_result = _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree);
        _GET_AVL_TREE_TYPE_INIT_FUNCTION(pt_avl_tree)(pt_node->_pc_data, &t_result);
        assert(t_result);
    }
}

/** eof **/

