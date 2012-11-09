/*
 *  The implementation of avl tree auxiliary functions.
 *  Copyright (C)  2008 - 2012  Wangbo
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

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
#ifndef NDEBUG
/**
 * Test avl tree is created by _create_avl tree.
 */
bool_t _avl_tree_is_created(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    if (cpt_avl_tree->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
        cpt_avl_tree->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
        cpt_avl_tree->_t_typeinfo._t_style != _TYPE_USER_DEFINE) {
        return false;
    }
    if (cpt_avl_tree->_t_typeinfo._pt_type == NULL) {
        return false;
    }

    if (cpt_avl_tree->_t_avlroot._pt_parent != NULL || cpt_avl_tree->_t_avlroot._pt_left != NULL ||
        cpt_avl_tree->_t_avlroot._pt_right != NULL || cpt_avl_tree->_t_avlroot._un_height != 0 ||
        cpt_avl_tree->_t_nodecount != 0 || cpt_avl_tree->_t_compare != NULL) {
        return false;
    }

    return _alloc_is_inited(&cpt_avl_tree->_t_allocator);
}

/**
 * Test avl tree is initialized by avl tree initialization functions.
 */
bool_t _avl_tree_is_inited(const _avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    if (cpt_avl_tree->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
        cpt_avl_tree->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
        cpt_avl_tree->_t_typeinfo._t_style != _TYPE_USER_DEFINE) {
        return false;
    }
    if (cpt_avl_tree->_t_typeinfo._pt_type == NULL) {
        return false;
    }

    if (cpt_avl_tree->_t_avlroot._pt_left == NULL || cpt_avl_tree->_t_avlroot._pt_right == NULL ||
        cpt_avl_tree->_t_avlroot._un_height != 0 || cpt_avl_tree->_t_compare == NULL) {
        return false;
    }

    return true;
}

/**
 * Test iterator referenced data is within the avl tree.
 */
bool_t _avl_tree_iterator_belong_to_avl_tree(const _avl_tree_t* cpt_avl_tree, _avl_tree_iterator_t it_iter)
{
    assert(cpt_avl_tree != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));
    assert(_AVL_TREE_ITERATOR_COREPOS(it_iter) != NULL);
    assert(_AVL_TREE_ITERATOR_TREE(it_iter) == cpt_avl_tree);

    /* if iterator is end */
    if (_AVL_TREE_ITERATOR_COREPOS(it_iter) == (_byte_t*)&cpt_avl_tree->_t_avlroot) {
        return true;
    } else {
        /* travel avl tree for search the pointer */
        return _avl_tree_avlnode_belong_to_avl_tree(
            cpt_avl_tree->_t_avlroot._pt_parent, (_avlnode_t*)_AVL_TREE_ITERATOR_COREPOS(it_iter));
    }
}

/**
 * Test the type that saved in the avl tree container and referenced by it_iter are same.
 */
bool_t _avl_tree_same_avl_tree_iterator_type(const _avl_tree_t* cpt_avl_tree, _avl_tree_iterator_t it_iter)
{
    assert(cpt_avl_tree != NULL);
    assert( _AVL_TREE_ITERATOR_TREE(it_iter) != NULL);

    return _avl_tree_same_type(cpt_avl_tree, _AVL_TREE_ITERATOR_TREE(it_iter));
}

/**
 * Test the type that saved in the avl tree container and referenced by it_iter are same.
 */
bool_t _avl_tree_same_iterator_type(const _avl_tree_t* cpt_avl_tree, iterator_t it_iter)
{
    assert(cpt_avl_tree != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree) || _avl_tree_is_created(cpt_avl_tree));
    assert(_iterator_is_valid(it_iter));

    return _type_is_same_ex(&cpt_avl_tree->_t_typeinfo, _iterator_get_typeinfo(it_iter));
}

/**
 * Test the type and compare function that saved in the avl tree container and referenced by it_iter are same.
 */
bool_t _avl_tree_same_avl_tree_iterator_type_ex(const _avl_tree_t* cpt_avl_tree, _avl_tree_iterator_t it_iter)
{
    assert(cpt_avl_tree != NULL);
    assert( _AVL_TREE_ITERATOR_TREE(it_iter) != NULL);

    return _avl_tree_same_type_ex(cpt_avl_tree, _AVL_TREE_ITERATOR_TREE(it_iter));
}

/**
 * Test avl node is within the sub avl tree.
 */
bool_t _avl_tree_avlnode_belong_to_avl_tree(const _avlnode_t* cpt_root, const _avlnode_t* cpt_pos)
{
    if (cpt_root == NULL || cpt_pos == NULL) {
        return false;
    } else if (cpt_root == cpt_pos) {
        return true;
    } else {
        return _avl_tree_avlnode_belong_to_avl_tree(cpt_root->_pt_left, cpt_pos) ||
               _avl_tree_avlnode_belong_to_avl_tree(cpt_root->_pt_right, cpt_pos);
    }
}
#endif /* NDEBUG */

/**
 * Test the type that saved in the avl tree container is same.
 */
bool_t _avl_tree_same_type(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_avl_tree_is_inited(cpt_first) || _avl_tree_is_created(cpt_first));
    assert(_avl_tree_is_inited(cpt_second) || _avl_tree_is_created(cpt_second));

    if (cpt_first == cpt_second) {
        return true;
    }

    return (cpt_first->_t_typeinfo._t_style == cpt_second->_t_typeinfo._t_style) &&
           (cpt_first->_t_typeinfo._pt_type == cpt_second->_t_typeinfo._pt_type) &&
           _type_is_same(_GET_AVL_TREE_TYPE_NAME(cpt_first), _GET_AVL_TREE_TYPE_NAME(cpt_second));
}

/**
 * Test the type and compare function that saved in the avl tree container is same.
 */
bool_t _avl_tree_same_type_ex(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_avl_tree_is_inited(cpt_first) || _avl_tree_is_created(cpt_first));
    assert(_avl_tree_is_inited(cpt_second) || _avl_tree_is_created(cpt_second));

    if (cpt_first == cpt_second) {
        return true;
    }

    return (cpt_first->_t_compare == cpt_second->_t_compare) && _avl_tree_same_type(cpt_first, cpt_second);
}

/**
 * Travel subtree for find the value in preorder.
 */
_avlnode_t* _avl_tree_find_value(const _avl_tree_t* cpt_avl_tree, const _avlnode_t* cpt_root, const void* cpv_value) 
{
    bool_t b_result = false;

    assert(cpt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    if (cpt_root == NULL) {
        return NULL;
    }

    b_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
    _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, cpt_root->_pby_data, &b_result);
    if (b_result) {
        return _avl_tree_find_value(cpt_avl_tree, cpt_root->_pt_left, cpv_value);
    }

    b_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
    _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpt_root->_pby_data, cpv_value, &b_result);
    if (b_result) {
        return _avl_tree_find_value(cpt_avl_tree, cpt_root->_pt_right, cpv_value);
    } else {
        return (_avlnode_t*)cpt_root;
    }
}


/**
 * Destroy the subtree with postorder traverse.
 */
_avlnode_t* _avl_tree_destroy_subtree(_avl_tree_t* pt_avl_tree, _avlnode_t* pt_root)
{
    bool_t b_result = false;

    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree) || _avl_tree_is_created(pt_avl_tree));

    if (pt_root != NULL) {
        pt_root->_pt_left = _avl_tree_destroy_subtree(pt_avl_tree, pt_root->_pt_left);
        pt_root->_pt_right = _avl_tree_destroy_subtree(pt_avl_tree, pt_root->_pt_right);

        assert(pt_root->_pt_left == NULL && pt_root->_pt_right == NULL);

        b_result = _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree);
        _GET_AVL_TREE_TYPE_DESTROY_FUNCTION(pt_avl_tree)(pt_root->_pby_data, &b_result);
        assert(b_result);
        _alloc_deallocate(&pt_avl_tree->_t_allocator, pt_root,_AVL_TREE_NODE_SIZE(_GET_AVL_TREE_TYPE_SIZE(pt_avl_tree)), 1);
    }
    
    return NULL;
}

/**
 * ll Rotate.
 */
_avlnode_t* _avl_tree_left_signal_rotate(_avlnode_t* pt_root)
{
    /*
     *     A         B
     *    /         / \
     *   B    =>   C   A
     *  / \           /
     * C   D         D
     */
    _avlnode_t* pt_left = NULL;

    assert(pt_root != NULL);
    assert(pt_root->_pt_left != NULL);
    
    /* rotate */
    pt_left = pt_root->_pt_left;
    pt_root->_pt_left = pt_left->_pt_right;
    pt_left->_pt_right = pt_root;
    /* change parent */
    pt_root->_pt_parent = pt_left;
    if (pt_root->_pt_left != NULL) {
        pt_root->_pt_left->_pt_parent = pt_root;
    }
    /* update height */
    pt_root->_un_height = (unsigned int)(
        (_avl_tree_get_height(pt_root->_pt_left) > _avl_tree_get_height(pt_root->_pt_right) ?
         _avl_tree_get_height(pt_root->_pt_left) : _avl_tree_get_height(pt_root->_pt_right)) + 1);
    pt_left->_un_height = (unsigned int)(
        (_avl_tree_get_height(pt_left->_pt_left) > _avl_tree_get_height(pt_left->_pt_right) ?
         _avl_tree_get_height(pt_left->_pt_left) : _avl_tree_get_height(pt_left->_pt_right)) + 1);

    return pt_left;
}

/**
 * rr Rotate.
 */
_avlnode_t* _avl_tree_right_signal_rotate(_avlnode_t* pt_root)
{
    /*
     *  A              B
     *   \            / \
     *    B     =>   A   D
     *   / \          \
     *  C   D          C
     */
    _avlnode_t* pt_right = NULL;

    assert(pt_root != NULL);
    assert(pt_root->_pt_right != NULL);

    /* rotate */
    pt_right = pt_root->_pt_right;
    pt_root->_pt_right = pt_right->_pt_left;
    pt_right->_pt_left = pt_root;
    /* change parent */
    pt_root->_pt_parent = pt_right;
    if (pt_root->_pt_right != NULL) {
        pt_root->_pt_right->_pt_parent = pt_root;
    }
    /* update height */
    pt_root->_un_height = (unsigned int)(
        (_avl_tree_get_height(pt_root->_pt_left) > _avl_tree_get_height(pt_root->_pt_right) ?
         _avl_tree_get_height(pt_root->_pt_left) : _avl_tree_get_height(pt_root->_pt_right)) + 1);
    pt_right->_un_height = (unsigned int)(
        (_avl_tree_get_height(pt_right->_pt_left) > _avl_tree_get_height(pt_right->_pt_right) ?
         _avl_tree_get_height(pt_right->_pt_left) : _avl_tree_get_height(pt_right->_pt_right)) + 1);

    return pt_right;
}

/**
 * lr Rotate.
 */
_avlnode_t* _avl_tree_left_double_rotate(_avlnode_t* pt_root)
{
    /*
     *       A               A                 E
     *      / \             / \              /   \
     *     B   C           E   C            B     A
     *    / \       =>    / \        =>    / \   / \
     *   D   E           B   G            D   F G   C
     *      / \         / \
     *     F   G       D   F
     */        
    assert(pt_root != NULL);

    pt_root->_pt_left = _avl_tree_right_signal_rotate(pt_root->_pt_left);
    pt_root->_pt_left->_pt_parent = pt_root;
    return _avl_tree_left_signal_rotate(pt_root);
}

/**
 * rl Rotate.
 */
_avlnode_t* _avl_tree_right_double_rotate(_avlnode_t* pt_root)
{
    /*
     *       A               A                   D 
     *      / \             / \                /   \
     *     B   C           B   D              A     C
     *        / \    =>       / \       =>   / \   / \
     *       D   E           F   C          B   F G   E
     *      / \                 / \
     *     F   G               G   E
     */
    assert(pt_root != NULL);

    pt_root->_pt_right = _avl_tree_left_signal_rotate(pt_root->_pt_right);
    pt_root->_pt_right->_pt_parent = pt_root;
    return _avl_tree_right_signal_rotate(pt_root);
}

/**
 * Get avl node height.
 */
int _avl_tree_get_height(const _avlnode_t* cpt_root)
{
    return cpt_root == NULL ? -1 : (int)cpt_root->_un_height;
}

/**
 * Get minimum avlnode.
 */
_avlnode_t* _avl_tree_get_min_avlnode(const _avlnode_t* cpt_root)
{
    _avlnode_t* pt_min = (_avlnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while (pt_min->_pt_left != NULL) {
        pt_min = pt_min->_pt_left;
    }

    return pt_min;
}

/**
 * Get maximum avlnode.
 */
_avlnode_t* _avl_tree_get_max_avlnode(const _avlnode_t* cpt_root)
{
    _avlnode_t* pt_max = (_avlnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while (pt_max->_pt_right != NULL) {
        pt_max = pt_max->_pt_right;
    }

    return pt_max;
}

/**
 * Insert the value into subtree.
 */
_avl_tree_insert_result_t _avl_tree_insert_avlnode(
    const _avl_tree_t* cpt_avl_tree, _avlnode_t* pt_root, const void* cpv_value)
{
    _avl_tree_insert_result_t t_insert_result;
    bool_t           b_result = false;

    assert(cpt_avl_tree != NULL);
    assert(cpv_value != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    /* if root is NULL then allocate memory */
    if (pt_root == NULL) {
        pt_root = _alloc_allocate(
            (_alloc_t*)&cpt_avl_tree->_t_allocator, _AVL_TREE_NODE_SIZE(_GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree)), 1);
        assert(pt_root != NULL);
        _avl_tree_init_elem_auxiliary((_avl_tree_t*)cpt_avl_tree, pt_root);

        pt_root->_pt_left = pt_root->_pt_right = NULL;
        pt_root->_un_height = 0;
        t_insert_result._pt_adjust = pt_root;
        t_insert_result._pt_new = pt_root;
        b_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
        _GET_AVL_TREE_TYPE_COPY_FUNCTION(cpt_avl_tree)(pt_root->_pby_data, cpv_value, &b_result);
        assert(b_result);

        return t_insert_result;
    }

    /* compare the value and current node */
    /* if value < current node then insert into left subtree */
    b_result = _GET_AVL_TREE_TYPE_SIZE(cpt_avl_tree);
    _avl_tree_elem_compare_auxiliary(cpt_avl_tree, cpv_value, pt_root->_pby_data, &b_result);
    if (b_result) {
        t_insert_result = _avl_tree_insert_avlnode(cpt_avl_tree, pt_root->_pt_left, cpv_value);
        pt_root->_pt_left = t_insert_result._pt_adjust;
        pt_root->_pt_left->_pt_parent = pt_root;

        pt_root = _avl_tree_rebalance(pt_root);
        t_insert_result._pt_adjust = pt_root;

        return t_insert_result;
    } else {
        /* insert into right subtree */
        t_insert_result = _avl_tree_insert_avlnode(cpt_avl_tree, pt_root->_pt_right, cpv_value);
        pt_root->_pt_right =  t_insert_result._pt_adjust;
        pt_root->_pt_right->_pt_parent = pt_root;

        pt_root = _avl_tree_rebalance(pt_root);
        t_insert_result._pt_adjust = pt_root;

        return t_insert_result;
    }
}

/**
 * Rebalance the subtree and update the root height.
 */
_avlnode_t* _avl_tree_rebalance(_avlnode_t* pt_root)
{
    if (pt_root != NULL) {
        /* if left - right > 1 */
        if (_avl_tree_get_height(pt_root->_pt_left) - _avl_tree_get_height(pt_root->_pt_right) > 1) {
            /* ll */
            if (_avl_tree_get_height(pt_root->_pt_left->_pt_left) >=
                _avl_tree_get_height(pt_root->_pt_left->_pt_right)) {
                pt_root = _avl_tree_left_signal_rotate(pt_root);
            } else {
            /* lr */
                pt_root = _avl_tree_left_double_rotate(pt_root);
            }
        } else if (_avl_tree_get_height(pt_root->_pt_right) - _avl_tree_get_height(pt_root->_pt_left) > 1) {
        /* else if right - left > 1 */
            /* rr */
            if (_avl_tree_get_height(pt_root->_pt_right->_pt_right) >= 
                _avl_tree_get_height(pt_root->_pt_right->_pt_left)) {
                pt_root = _avl_tree_right_signal_rotate(pt_root);
            } else {
            /* rl */
                pt_root = _avl_tree_right_double_rotate(pt_root);
            }
        }

        pt_root->_un_height = (unsigned int)(
            (_avl_tree_get_height(pt_root->_pt_left) > _avl_tree_get_height(pt_root->_pt_right) ?
             _avl_tree_get_height(pt_root->_pt_left) : _avl_tree_get_height(pt_root->_pt_right)) + 1);
    }

    return pt_root;
}

/**
 * Initialize element auxiliary function
 */
void _avl_tree_init_elem_auxiliary(_avl_tree_t* pt_avl_tree, _avlnode_t* pt_node)
{
    assert(pt_avl_tree != NULL);
    assert(pt_node != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree) || _avl_tree_is_created(pt_avl_tree));

    /* initialize new elements */
    if (_GET_AVL_TREE_TYPE_STYLE(pt_avl_tree) == _TYPE_CSTL_BUILTIN) {
        /* get element type name */
        char s_elemtypename[_TYPE_NAME_SIZE + 1];
        _type_get_elem_typename(_GET_AVL_TREE_TYPE_NAME(pt_avl_tree), s_elemtypename);

        _GET_AVL_TREE_TYPE_INIT_FUNCTION(pt_avl_tree)(pt_node->_pby_data, s_elemtypename);
    } else {
        bool_t b_result = _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree);
        _GET_AVL_TREE_TYPE_INIT_FUNCTION(pt_avl_tree)(pt_node->_pby_data, &b_result);
        assert(b_result);
    }
}

/**
 * Element compare function auxiliary
 */
void _avl_tree_elem_compare_auxiliary(
    const _avl_tree_t* cpt_avl_tree, const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpt_avl_tree != NULL);
    assert(cpv_first != NULL);
    assert(cpv_second != NULL);
    assert(pv_output != NULL);
    assert(_avl_tree_is_inited(cpt_avl_tree));

    if (strncmp(_GET_AVL_TREE_TYPE_BASENAME(cpt_avl_tree), _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0 &&
        cpt_avl_tree->_t_compare != _GET_AVL_TREE_TYPE_LESS_FUNCTION(cpt_avl_tree)) {
        cpt_avl_tree->_t_compare(string_c_str((string_t*)cpv_first), string_c_str((string_t*)cpv_second), pv_output);
    } else {
        cpt_avl_tree->_t_compare(cpv_first, cpv_second, pv_output);
    }
}

/** local function implementation section **/

/** eof **/

