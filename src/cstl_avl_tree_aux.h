/*
 *  The interface of avl tree auxiliary function.
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

#ifndef _CSTL_AVL_TREE_AUX_H_
#define _CSTL_AVL_TREE_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree)             ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_AVL_TREE_TYPE_NAME(pt_avl_tree)             ((pt_avl_tree)->_t_typeinfo._sz_typename)
#define _GET_AVL_TREE_TYPE_BASENAME(pt_avl_tree)         ((pt_avl_tree)->_t_typeinfo._pt_type->_sz_typename)
#define _GET_AVL_TREE_TYPE_INIT_FUNCTION(pt_avl_tree)    ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_AVL_TREE_TYPE_COPY_FUNCTION(pt_avl_tree)    ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_AVL_TREE_TYPE_LESS_FUNCTION(pt_avl_tree)    ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_AVL_TREE_TYPE_DESTROY_FUNCTION(pt_avl_tree) ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_AVL_TREE_TYPE_STYLE(pt_avl_tree)            ((pt_avl_tree)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/
typedef struct _tagavltreeinsertresult
{
    _avlnode_t* _pt_adjust;   /* the adjusted root _avlnode_t pointer */
    _avlnode_t* _pt_new;      /* the new inserting _avlnode_t* pointer */
}_avl_tree_insert_result_t;

/** exported global variable declaration section **/

/** exported function prototype section **/

/**
 * Test avl tree is created by _create_avl tree.
 * @param cpt_avl_tree          avl tree container.
 * @return if avl tree is created by create_avl tree, then return true, else return false.
 * @remarks if cpt_avl_tree == NULL, then the behavior is undefined.
 */
extern bool_t _avl_tree_is_created(const _avl_tree_t* cpt_avl_tree);

/**
 * Test avl tree is initialized by avl tree initialization functions.
 * @param cpt_avl_tree          avl tree container.
 * @return if avl tree is initialized by avl tree initialization functions, then return true, else return false.
 * @remarks if cpt_avl_tree == NULL, then the behavior is undefined.
 */
extern bool_t _avl_tree_is_inited(const _avl_tree_t* cpt_avl_tree);

#ifndef NDEBUG
/*
 * Assert support.
 */
extern bool_t _avl_tree_iterator_belong_to_avl_tree(
    const _avl_tree_t* cpt_avl_tree, _avl_tree_iterator_t t_iter);
extern bool_t _avl_tree_same_avl_tree_iterator_type(
    const _avl_tree_t* cpt_avl_tree, _avl_tree_iterator_t t_iter);
extern bool_t _avl_tree_avlnode_belong_to_avl_tree(
    const _avlnode_t* cpt_root, const _avlnode_t* cpt_pos);
#endif /* NDEBUG */
extern bool_t _avl_tree_same_type(
    const _avl_tree_t* cpt_avl_treefirst, const _avl_tree_t* cpt_avl_treesecond);

/*
 * Travel subtree for find the value in preorder.
 */
extern _avlnode_t* _avl_tree_find_value(
    const _avl_tree_t* cpt_avl_tree, const _avlnode_t* cpt_root, const void* cpv_value); 

/*
 * Destroy the subtree with postorder traverse.
 */
extern _avlnode_t* _avl_tree_destroy_subtree(_avl_tree_t* pt_avl_tree, _avlnode_t* pt_root);

/*
 * Rotate.
 */
/* ll rotate */
extern _avlnode_t* _avl_tree_left_signal_rotate(_avlnode_t* pt_root);
/* rr rotate */
extern _avlnode_t* _avl_tree_right_signal_rotate(_avlnode_t* pt_root);
/* lr rotate */
extern _avlnode_t* _avl_tree_left_double_rotate(_avlnode_t* pt_root);
/* rl rotate */
extern _avlnode_t* _avl_tree_right_double_rotate(_avlnode_t* pt_root);

/*
 * Insert the value into subtree.
 */
extern _avl_tree_insert_result_t _avl_tree_insert_avlnode(
    const _avl_tree_t* cpt_avl_tree, _avlnode_t* pt_root, const void* cpv_value);

/*
 * Get avl node height.
 */
extern int _avl_tree_get_height(const _avlnode_t* cpt_root);

/*
 * Get minimum and maximum avlnode pointer.
 */
extern _avlnode_t* _avl_tree_get_min_avlnode(const _avlnode_t* cpt_root);
extern _avlnode_t* _avl_tree_get_max_avlnode(const _avlnode_t* cpt_root);

/*
 * Rebalance the subtree and update the root height.
 */
extern _avlnode_t* _avl_tree_rebalance(_avlnode_t* pt_root);

/* initialize element auxiliary function */
extern void _avl_tree_init_elem_auxiliary(_avl_tree_t* pt_avl_tree, _avlnode_t* pt_node);

/* element compare function auxiliary */
extern void _avl_tree_elem_compare_auxiliary(const _avl_tree_t* cpt_avl_tree,
    const void* cpv_first, const void* cpv_second, void* pv_output);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_AVL_TREE_AUX_H_ */
/** eof **/

