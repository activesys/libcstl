/*
 *  The implementation of rb tree auxiliary functions.
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

#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>

#include "cstl_rb_tree_aux.h"

/** local constant declaration and local macro section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
#ifndef NDEBUG
/**
 * Test rb tree is created by _create_rb tree.
 */
bool_t _rb_tree_is_created(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    if(cpt_rb_tree->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
       cpt_rb_tree->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
       cpt_rb_tree->_t_typeinfo._t_style != _TYPE_USER_DEFINE)
    {
        return false;
    }
    if(cpt_rb_tree->_t_typeinfo._pt_type == NULL)
    {
        return false;
    }

    if(cpt_rb_tree->_t_rbroot._pt_parent != NULL || cpt_rb_tree->_t_rbroot._pt_left != NULL ||
       cpt_rb_tree->_t_rbroot._pt_right != NULL || cpt_rb_tree->_t_rbroot._t_color != red ||
       cpt_rb_tree->_t_nodecount != 0 || cpt_rb_tree->_t_compare != NULL)
    {
        return false;
    }

    return _alloc_is_inited(&cpt_rb_tree->_t_allocator);
}

/**
 * Test rb tree is initialized by rb tree initialization functions.
 */
bool_t _rb_tree_is_inited(const _rb_tree_t* cpt_rb_tree)
{
    assert(cpt_rb_tree != NULL);

    if(cpt_rb_tree->_t_typeinfo._t_style != _TYPE_C_BUILTIN &&
       cpt_rb_tree->_t_typeinfo._t_style != _TYPE_CSTL_BUILTIN &&
       cpt_rb_tree->_t_typeinfo._t_style != _TYPE_USER_DEFINE)
    {
        return false;
    }
    if(cpt_rb_tree->_t_typeinfo._pt_type == NULL)
    {
        return false;
    }

    if(cpt_rb_tree->_t_rbroot._pt_left == NULL || cpt_rb_tree->_t_rbroot._pt_right == NULL ||
       cpt_rb_tree->_t_rbroot._t_color != red || cpt_rb_tree->_t_compare == NULL)
    {
        return false;
    }

    return true;
}

/**
 * Test iterator referenced data is within the rb tree.
 */
bool_t _rb_tree_iterator_belong_to_rb_tree(const _rb_tree_t* cpt_rb_tree, _rb_tree_iterator_t it_iter)
{
    assert(cpt_rb_tree != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));
    assert(_GET_RB_TREE_COREPOS(it_iter) != NULL);
    assert(_GET_RB_TREE(it_iter) == cpt_rb_tree);

    /* if iterator is end */
    if(_GET_RB_TREE_COREPOS(it_iter) == (char*)&cpt_rb_tree->_t_rbroot)
    {
        return true;
    }
    /* else travel rb tree for search the pointer */
    else
    {
        return _rb_tree_rbnode_belong_to_rb_tree(
            cpt_rb_tree->_t_rbroot._pt_parent, (_rbnode_t*)_GET_RB_TREE_COREPOS(it_iter));
    }
}

/**
 * Test the type that saved in the rb tree container and referenced by it_iter are same.
 */
bool_t _rb_tree_same_rb_tree_iterator_type(const _rb_tree_t* cpt_rb_tree, _rb_tree_iterator_t it_iter)
{
    assert(cpt_rb_tree != NULL);
    assert(_rb_tree_is_inited(cpt_rb_tree));

    return _rb_tree_same_type(cpt_rb_tree, _GET_RB_TREE(it_iter));
}

/**
 * Test the type and compare function that saved in the rb tree container and referenced by it_iter are same.
 */
bool_t _rb_tree_same_rb_tree_iterator_type_ex(const _rb_tree_t* cpt_rb_tree, _rb_tree_iterator_t it_iter)
{
    assert(cpt_rb_tree != NULL);
    assert( _GET_RB_TREE(it_iter) != NULL);

    return _rb_tree_same_type_ex(cpt_rb_tree, _GET_RB_TREE(it_iter));
}

/**
 * Test rb node is within the sub rb tree.
 */
bool_t _rb_tree_rbnode_belong_to_rb_tree(const _rbnode_t* cpt_root, const _rbnode_t* cpt_pos)
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
        return _rb_tree_rbnode_belong_to_rb_tree(cpt_root->_pt_left, cpt_pos) ||
               _rb_tree_rbnode_belong_to_rb_tree(cpt_root->_pt_right, cpt_pos);
    }
}
#endif /* NEDBUG */

bool_t _rb_tree_same_type(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond)
{
    assert(cpt_rb_treefirst != NULL && cpt_rb_treesecond != NULL);

    return _type_is_same(_GET_RB_TREE_TYPE_NAME(cpt_rb_treefirst),
                         _GET_RB_TREE_TYPE_NAME(cpt_rb_treesecond)) &&
           (cpt_rb_treefirst->_t_typeinfo._t_style ==
            cpt_rb_treesecond->_t_typeinfo._t_style) &&
           (cpt_rb_treefirst->_t_typeinfo._pt_type ==
            cpt_rb_treesecond->_t_typeinfo._pt_type) &&
           (cpt_rb_treefirst->_t_compare == cpt_rb_treesecond->_t_compare);
}

/**
 * Test the type and compare function that saved in the rb tree container is same.
 */
bool_t _rb_tree_same_type_ex(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second)
{
    assert(cpt_first != NULL);
    assert(cpt_second != NULL);
    assert(_rb_tree_is_inited(cpt_first) || _rb_tree_is_created(cpt_first));
    assert(_rb_tree_is_inited(cpt_second) || _rb_tree_is_created(cpt_second));

    if(cpt_first == cpt_second)
    {
        return true;
    }

    return (cpt_first->_t_compare == cpt_second->_t_compare) && _rb_tree_same_type(cpt_first, cpt_second);
}

_rbnode_t* _destroy_rb_tree(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_root)
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
        _alloc_deallocate(&pt_rb_tree->_t_allocator, pt_root, 
            _RB_TREE_NODE_SIZE(_GET_RB_TREE_TYPE_SIZE(pt_rb_tree)), 1);
    }
    
    return NULL;
}

_rbnode_t* _find_value(
    const _rb_tree_t* cpt_rb_tree, const _rbnode_t* cpt_root, const void* cpv_value)
{
    bool_t t_result = false;

    assert(cpt_rb_tree != NULL && cpv_value != NULL);

    if(cpt_root == NULL)
    {
        return NULL;
    }

    t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
    _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpv_value, cpt_root->_pc_data, &t_result);
    if(t_result)
    {
        return _find_value(cpt_rb_tree, cpt_root->_pt_left, cpv_value);
    }

    t_result = _GET_RB_TREE_TYPE_SIZE(cpt_rb_tree);
    _rb_tree_elem_compare_auxiliary(cpt_rb_tree, cpt_root->_pc_data, cpv_value, &t_result);
    if(t_result)
    {
        return _find_value(cpt_rb_tree, cpt_root->_pt_right, cpv_value);
    }
    else
    {
        return (_rbnode_t*)cpt_root;
    }
}

_rbnode_t* _get_min_rbnode(const _rbnode_t* cpt_root)
{
    _rbnode_t* pt_min = (_rbnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while(pt_min->_pt_left != NULL)
    {
        pt_min = pt_min->_pt_left;
    }

    return pt_min;
}

_rbnode_t* _get_max_rbnode(const _rbnode_t* cpt_root)
{
    _rbnode_t* pt_max = (_rbnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while(pt_max->_pt_right != NULL)
    {
        pt_max = pt_max->_pt_right;
    }

    return pt_max;
}

color_t _get_color(const _rbnode_t* cpt_root)
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

_rbnode_t* _insert_rbnode(_rb_tree_t* pt_rb_tree, const void* cpv_value)
{
    _rbnode_t* pt_parent = NULL;
    _rbnode_t* pt_cur = NULL;
    bool_t    t_result = false;
    bool_t    t_less = false;

    assert(pt_rb_tree != NULL && cpv_value != NULL);

    /* if the rb tree is empty */
    if(_rb_tree_empty(pt_rb_tree))
    {
        /* allocat a new root */
        pt_cur = _alloc_allocate((_alloc_t*)&pt_rb_tree->_t_allocator,
            _RB_TREE_NODE_SIZE(_GET_RB_TREE_TYPE_SIZE(pt_rb_tree)), 1);
        assert(pt_cur != NULL);
        _rb_tree_init_elem_auxiliary(pt_rb_tree, pt_cur);
        /* set its color is black */
        pt_cur->_pt_left = pt_cur->_pt_right = NULL;
        pt_cur->_t_color = black;
        pt_cur->_pt_parent = (_rbnode_t*)&pt_rb_tree->_t_rbroot;
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
        _rb_tree_elem_compare_auxiliary(pt_rb_tree, cpv_value, pt_parent->_pc_data, &t_less);

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
            _rb_tree_elem_compare_auxiliary(pt_rb_tree, cpv_value, pt_parent->_pc_data, &t_less);

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
        pt_cur = _alloc_allocate((_alloc_t*)&pt_rb_tree->_t_allocator,
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
_rbnode_t* _deasil_rotate(_rbnode_t* pt_root)
{
    _rbnode_t* pt_left = NULL;

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
_rbnode_t* _widdershins_rotate(_rbnode_t* pt_root)
{
    _rbnode_t* pt_right = NULL;

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

void _rebalance_rb_tree(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_pos)
{
    _rbnode_t* pt_parent = NULL;
    _rbnode_t* pt_sparent = NULL;   /* the sibling of parent */
    _rbnode_t* pt_gparent = NULL;   /* grand parent node */
    _rbnode_t* pt_ggparent = NULL;  /* grand grand parent node */

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

void _fixup_deletion(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_pos, _rbnode_t* pt_parent)
{
    _rbnode_t* pt_sibling = NULL;
    _rbnode_t* pt_gparent = NULL;

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
                _rbnode_t* pt_sleft = pt_sibling->_pt_left;
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
                _rbnode_t* pt_sright = pt_sibling->_pt_right;
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

void _rb_tree_init_elem_auxiliary(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_node)
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

void _rb_tree_elem_compare_auxiliary(const _rb_tree_t* cpt_rb_tree,
    const void* cpv_first, const void* cpv_second, void* pv_output)
{
    assert(cpt_rb_tree != NULL && cpv_first != NULL &&
           cpv_second != NULL && pv_output != NULL); 

    if(strncmp(_GET_RB_TREE_TYPE_BASENAME(cpt_rb_tree),
        _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0 &&
       cpt_rb_tree->_t_compare != _GET_RB_TREE_TYPE_LESS_FUNCTION(cpt_rb_tree))
    {
        cpt_rb_tree->_t_compare(string_c_str((string_t*)cpv_first),
            string_c_str((string_t*)cpv_second), pv_output);
    }
    else
    {
        cpt_rb_tree->_t_compare(cpv_first, cpv_second, pv_output);
    }
}

/** local function implementation section **/

/** eof **/

