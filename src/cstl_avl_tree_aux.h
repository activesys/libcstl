/*
 *  The interface of avl tree auxiliary function.
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

#ifndef _CSTL_AVL_TREE_AUX_H_
#define _CSTL_AVL_TREE_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_AVL_TREE_TYPE_SIZE(pt_avl_tree)             ((pt_avl_tree)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_AVL_TREE_TYPE_NAME(pt_avl_tree)             ((pt_avl_tree)->_t_typeinfo._s_typename)
#define _GET_AVL_TREE_TYPE_BASENAME(pt_avl_tree)         ((pt_avl_tree)->_t_typeinfo._pt_type->_s_typename)
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
#ifndef NDEBUG
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

/**
 * Test iterator referenced data is within the avl tree.
 * @param cpt_avl_tree          point to avl tree.
 * @param it_iter               avl tree iterator.
 * @return if iterator referenced is within the avl tree, then return true, otherwise return false.
 * @remarks if cpt_avl_tree == NULL, then the behavior is undefined, cpt_avl_tree must be initialized, otherwise the
 *          behavior is undefined. the it_iter must be valie avl tree iterator, otherwist the behavior is undefined. 
 */
extern bool_t _avl_tree_iterator_belong_to_avl_tree(const _avl_tree_t* cpt_avl_tree, _avl_tree_iterator_t it_iter);

/**
 * Test the type that saved in the avl tree container and referenced by it_iter are same.
 * @param cpt_avl_tree          avl tree container.
 * @param it_iter               avl tree iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_avl_tree == NULL or it_iter is not avl tree iterator, then the behavior is undefined.
 */
extern bool_t _avl_tree_same_avl_tree_iterator_type(const _avl_tree_t* cpt_avl_tree, _avl_tree_iterator_t it_iter);

/**
 * Test the type that saved in the avl tree container and referenced by it_iter are same.
 * @param cpt_avl_tree          avl tree container.
 * @param it_iter               iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_avl_tree == NULL, then the behavior is undefined.
 */
extern bool_t _avl_tree_same_iterator_type(const _avl_tree_t* cpt_avl_tree, iterator_t it_iter);

/**
 * Test the type and compare function that saved in the avl tree container and referenced by it_iter are same.
 * @param cpt_avl_tree          avl tree container.
 * @param it_iter               avl tree iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_avl_tree == NULL or it_iter is not avl tree iterator, then the behavior is undefined.
 */
extern bool_t _avl_tree_same_avl_tree_iterator_type_ex(const _avl_tree_t* cpt_avl_tree, _avl_tree_iterator_t it_iter);

/**
 * Test avl node is within the sub avl tree.
 * @param cpt_root              the root of sub avl tree.
 * @param cpt_pos               avl node.
 * @return if avl node is within the avl tree, then return true, otherwise return false.
 * @remarks if cpt_root == NULL or cpt_pos == NULL, then return false.
 */
extern bool_t _avl_tree_avlnode_belong_to_avl_tree(const _avlnode_t* cpt_root, const _avlnode_t* cpt_pos);
#endif /* NDEBUG */

/**
 * Test the type that saved in the avl tree container is same.
 * @param cpt_first             first avl tree.
 * @param cpt_second            second avl tree.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, the behavior is undefined. the two avl tree must be initialized
 *          or created by _create_avl_tree(), otherwise the behavior is undefined. if cpt_first == cpt_second then
 *          return true.
 */
extern bool_t _avl_tree_same_type(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second);

/**
 * Test the type and compare function that saved in the avl tree container is same.
 * @param cpt_first             first avl tree.
 * @param cpt_second            second avl tree.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, the behavior is undefined. the two avl tree must be initialized
 *          or created by _create_avl_tree(), otherwise the behavior is undefined. if cpt_first == cpt_second then
 *          return true.
 */
extern bool_t _avl_tree_same_type_ex(const _avl_tree_t* cpt_first, const _avl_tree_t* cpt_second);

/**
 * Travel subtree for find the value in preorder.
 * @param cpt_avl_tree          avl tree.
 * @param cpt_root              root of sub avl tree.
 * @param cpv_value             specific value.
 * @return avl node that save the specific value, else return NULL.
 * @remarks if cpt_avl_tree == NULL or cpv_value == NULL, then the behavior is undefined. avl tree must be initialized,
 *          otherwise the behavior is undefine.
 */
extern _avlnode_t* _avl_tree_find_value(const _avl_tree_t* cpt_avl_tree, const _avlnode_t* cpt_root, const void* cpv_value); 

/**
 * Destroy the subtree with postorder traverse.
 * @param pt_avl_tree           avl tree.
 * @param pt_root               root of sub avl tree.
 * @return NULL.
 * @remarks if pt_avl_tree == NULL, the behavior is undefined. avl tree must be initialized or created by _create_avl_tree(),
 *          otherwise the behavior is undefined.
 */
extern _avlnode_t* _avl_tree_destroy_subtree(_avl_tree_t* pt_avl_tree, _avlnode_t* pt_root);

/**
 * ll Rotate.
 * @param pt_root               root of sub avl tree.
 * @return new root of sub avl tree.
 * @remarks is pt_root == NULL or pt_root->_pt_left == NULL, the behavior is undefined.
 */
extern _avlnode_t* _avl_tree_left_signal_rotate(_avlnode_t* pt_root);

/**
 * rr Rotate.
 * @param pt_root               root of sub avl tree.
 * @return new root of sub avl tree.
 * @remarks is pt_root == NULL or pt_root->_pt_right == NULL, the behavior is undefined.
 */
extern _avlnode_t* _avl_tree_right_signal_rotate(_avlnode_t* pt_root);

/**
 * lr Rotate.
 * @param pt_root               root of sub avl tree.
 * @return new root of sub avl tree.
 * @remarks is pt_root == NULL, the behavior is undefined.
 */
extern _avlnode_t* _avl_tree_left_double_rotate(_avlnode_t* pt_root);

/**
 * rl Rotate
 * @param pt_root               root of sub avl tree.
 * @return new root of sub avl tree.
 * @remarks is pt_root == NULL, the behavior is undefined.
 */
extern _avlnode_t* _avl_tree_right_double_rotate(_avlnode_t* pt_root);

/**
 * Insert the value into subtree.
 * @param cpt_avl_tree          avl tree.
 * @param pt_root               root of sub avl tree.
 * @param cpv_value             insert value.
 * @return new root of sub avl tree and new inserted node.
 * @remarks if cpt_avl_tree == NULL or cpv_value == NULL, then the behavior is undefined. the avl tree must be initialized,
 *          otherwise the behavior is undefined.
 */
extern _avl_tree_insert_result_t _avl_tree_insert_avlnode(
    const _avl_tree_t* cpt_avl_tree, _avlnode_t* pt_root, const void* cpv_value);

/**
 * Get avl node height.
 * @param cpt_root              avl node.
 * @return avl node height.
 * @remarks if cpt_root == NULL, then return -1.
 */
extern int _avl_tree_get_height(const _avlnode_t* cpt_root);

/**
 * Get minimum avlnode.
 * @param cpt_root              root of sub avl node.
 * @return minimum avl node.
 * @remarks if cpt_root == NULL, the behavior is undefined.
 */
extern _avlnode_t* _avl_tree_get_min_avlnode(const _avlnode_t* cpt_root);

/**
 * Get maximum avlnode.
 * @param cpt_root              root of sub avl node.
 * @return maximum avl node.
 * @remarks if cpt_root == NULL, the behavior is undefined.
 */
extern _avlnode_t* _avl_tree_get_max_avlnode(const _avlnode_t* cpt_root);

/**
 * Rebalance the subtree and update the root height.
 * @param pt_root               root of sub avl tree.
 * @return new root.
 */
extern _avlnode_t* _avl_tree_rebalance(_avlnode_t* pt_root);

/**
 * Initialize element auxiliary function
 * @param pt_avl_tree           avl tree.
 * @param pt_node               avl node.
 * @return void.
 * @remarks if pt_avl_tree == NULL or pt_node == NULL, then the behavior is undefine. pt_avl_tree must be initialized or
 *          created by _create_avl_tree(), otherwise the behavior is undefined.
 */
extern void _avl_tree_init_elem_auxiliary(_avl_tree_t* pt_avl_tree, _avlnode_t* pt_node);

/**
 * Element compare function auxiliary
 * @param cpt_avl_tree          avl tree.
 * @param cpv_first             first element.
 * @param cpv_second            second element.
 * @param pv_output             output.
 * @return void.
 * @remarks if cpt_avl_tree == NULL or cpv_first == NULL or cpv_second == NULL or pv_output == NULL, the behavior is
 *          undefined. cpt_avl_tree must be initialized or created by _create_avl_tree(), otherwise the behavior is
 *          undefined.
 */
extern void _avl_tree_elem_compare_auxiliary(
    const _avl_tree_t* cpt_avl_tree, const void* cpv_first, const void* cpv_second, void* pv_output);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_AVL_TREE_AUX_H_ */
/** eof **/

