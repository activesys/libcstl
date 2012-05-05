/*
 *  The interface of rb tree auxiliary function.
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

#ifndef _CSTL_RB_TREE_AUX_H_
#define _CSTL_RB_TREE_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_RB_TREE_TYPE_SIZE(pt_rb_tree)             ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_RB_TREE_TYPE_NAME(pt_rb_tree)             ((pt_rb_tree)->_t_typeinfo._s_typename)
#define _GET_RB_TREE_TYPE_BASENAME(pt_rb_tree)         ((pt_rb_tree)->_t_typeinfo._pt_type->_s_typename)
#define _GET_RB_TREE_TYPE_INIT_FUNCTION(pt_rb_tree)    ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typeinit)
#define _GET_RB_TREE_TYPE_COPY_FUNCTION(pt_rb_tree)    ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typecopy)
#define _GET_RB_TREE_TYPE_LESS_FUNCTION(pt_rb_tree)    ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typeless)
#define _GET_RB_TREE_TYPE_DESTROY_FUNCTION(pt_rb_tree) ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typedestroy)
#define _GET_RB_TREE_TYPE_STYLE(pt_rb_tree)            ((pt_rb_tree)->_t_typeinfo._t_style)

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
#ifndef NDEBUG
/**
 * Test rb tree is created by _create_rb tree.
 * @param cpt_rb_tree           rb tree container.
 * @return if rb tree is created by create_rb tree, then return true, else return false.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined.
 */
extern bool_t _rb_tree_is_created(const _rb_tree_t* cpt_rb_tree);

/**
 * Test rb tree is initialized by rb tree initialization functions.
 * @param cpt_rb_tree           rb tree container.
 * @return if rb tree is initialized by rb tree initialization functions, then return true, else return false.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined.
 */
extern bool_t _rb_tree_is_inited(const _rb_tree_t* cpt_rb_tree);

/**
 * Test iterator referenced data is within the rb tree.
 * @param cpt_rb_tree           point to rb tree.
 * @param it_iter               rb tree iterator.
 * @return if iterator referenced is within the rb tree, then return true, otherwise return false.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined, cpt_rb_tree must be initialized, otherwise the
 *          behavior is undefined. the it_iter must be valie rb tree iterator, otherwist the behavior is undefined. 
 */
extern bool_t _rb_tree_iterator_belong_to_rb_tree(const _rb_tree_t* cpt_rb_tree, _rb_tree_iterator_t it_iter);

/**
 * Test the type that saved in the rb tree container and referenced by it_iter are same.
 * @param cpt_rb_tree           rb tree container.
 * @param it_iter               iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined.
 */
extern bool_t _rb_tree_same_iterator_type(const _rb_tree_t* cpt_rb_tree, iterator_t it_iter);

/**
 * Test the type that saved in the rb tree container and referenced by it_iter are same.
 * @param cpt_rb_tree           rb tree container.
 * @param it_iter               rb tree iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_rb_tree == NULL or it_iter is not rb tree iterator, then the behavior is undefined.
 */
extern bool_t _rb_tree_same_rb_tree_iterator_type(const _rb_tree_t* cpt_rb_tree, _rb_tree_iterator_t it_iter);

/**
 * Test the type and compare function that saved in the rb tree container and referenced by it_iter are same.
 * @param cpt_rb_tree           rb tree container.
 * @param it_iter               rb tree iterator.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_rb_tree == NULL or it_iter is not rb tree iterator, then the behavior is undefined.
 */
extern bool_t _rb_tree_same_rb_tree_iterator_type_ex(const _rb_tree_t* cpt_rb_tree, _rb_tree_iterator_t it_iter);

/**
 * Test rb node is within the sub rb tree.
 * @param cpt_root              the root of sub rb tree.
 * @param cpt_pos               rb node.
 * @return if rb node is within the rb tree, then return true, otherwise return false.
 * @remarks if cpt_root == NULL or cpt_pos == NULL, then return false.
 */
extern bool_t _rb_tree_rbnode_belong_to_rb_tree(const _rbnode_t* cpt_root, const _rbnode_t* cpt_pos);
#endif /* NDEBUG */

/**
 * Test the type that saved in the rb tree container is same.
 * @param cpt_first             first rb tree.
 * @param cpt_second            second rb tree.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, the behavior is undefined. the two rb tree must be initialized
 *          or created by _create_rb_tree(), otherwise the behavior is undefined. if cpt_first == cpt_second then
 *          return true.
 */
extern bool_t _rb_tree_same_type(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second);

/**
 * Test the type and compare function that saved in the rb tree container is same.
 * @param cpt_first             first rb tree.
 * @param cpt_second            second rb tree.
 * @return if the type is same, return true, else return false.
 * @remarks if cpt_first == NULL or cpt_second == NULL, the behavior is undefined. the two rb tree must be initialized
 *          or created by _create_rb_tree(), otherwise the behavior is undefined. if cpt_first == cpt_second then
 *          return true.
 */
extern bool_t _rb_tree_same_type_ex(const _rb_tree_t* cpt_first, const _rb_tree_t* cpt_second);

/**
 * Destroy the subtree with postorder traverse.
 * @param pt_rb_tree            rb tree.
 * @param pt_root               root of sub rb tree.
 * @return NULL.
 * @remarks if pt_rb_tree == NULL, the behavior is undefined. rb tree must be initialized or created by _create_rb_tree(),
 *          otherwise the behavior is undefined.
 */
extern _rbnode_t* _rb_tree_destroy_subtree(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_root);

/**
 * Travel subtree for find the value in preorder.
 * @param cpt_rb_tree           rb tree.
 * @param cpt_root              root of sub rb tree.
 * @param cpv_value             specific value.
 * @return rb node that save the specific value, else return NULL.
 * @remarks if cpt_rb_tree == NULL or cpv_value == NULL, then the behavior is undefined. rb tree must be initialized,
 *          otherwise the behavior is undefine.
 */
extern _rbnode_t* _rb_tree_find_value(const _rb_tree_t* cpt_rb_tree, const _rbnode_t* cpt_root, const void* cpv_value); 

/**
 * Insert the value into subtree.
 * @param cpt_rb_tree           rb tree.
 * @param cpv_value             insert value.
 * @return inserted node.
 * @remarks if cpt_rb_tree == NULL or cpv_value == NULL, then the behavior is undefined. the rb tree must be initialized,
 *          otherwise the behavior is undefined.
 */
extern _rbnode_t* _rb_tree_insert_rbnode(_rb_tree_t* pt_rb_tree, const void* cpv_value);

/**
 * Rebalance the rb tree.
 * @param pt_rb_tree            rb tree.
 * @param pt_pos                imbalanced node.
 * @return void.
 * @remarks if pt_rb_tree == NULL or pt_pos == NULL, then the behavior is undefined. the rb tree must be initialized,
 *          otherwise the behavior is undefined. the pt_pos must be not the root of rb tree, otherwise the behavior
 *          is undefined.
 */
extern void _rb_tree_rebalance(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_pos);

/**
 * Rebalance the subtree after deletion.
 * @param pt_rb_tree            rb tree.
 * @param pt_pos                imbalanced node.
 * @param pt_parent             parent nodef of imbalanced node.
 * @return void.
 * @remarks if pt_rb_tree == NULL or pt_parent == NULL, then the behavior is undefined. the rb tree must be initialized,
 *          otherwise the behavior is undefined. the pt_parent must be have one child node at least, otherwise the
 *          behavior is undefined.
 */
extern void _rb_tree_fixup_deletion(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_pos, _rbnode_t* pt_parent);

/**
 * Get minimum rbnode.
 * @param cpt_root              root of sub rb node.
 * @return minimum rb node.
 * @remarks if cpt_root == NULL, the behavior is undefined.
 */
extern _rbnode_t* _rb_tree_get_min_rbnode(const _rbnode_t* cpt_root);

/**
 * Get maximum rbnode.
 * @param cpt_root              root of sub rb node.
 * @return maximum rb node.
 * @remarks if cpt_root == NULL, the behavior is undefined.
 */
extern _rbnode_t* _rb_tree_get_max_rbnode(const _rbnode_t* cpt_root);

/**
 * Get rb node color.
 * @param cpt_root                  rb node.
 * @return rb node color.
 * @remarks if cpt_root == NULL, then return black.
 */
extern _color_t _rb_tree_get_color(const _rbnode_t* cpt_root);

/**
 * Anticlockwise rotation
 * @param pt_root               root of sub rb tree.
 * @return new root of sub rb tree.
 * @remarks is pt_root == NULL or pt_root->_pt_right == NULL, the behavior is undefined.
 */
extern _rbnode_t* _rb_tree_anticlockwise_rotation(_rbnode_t* pt_root);

/**
 * Clockwise rotation
 * @param pt_root               root of sub rb tree.
 * @return new root of sub rb tree.
 * @remarks is pt_root == NULL or pt_root->_pt_left == NULL, the behavior is undefined.
 */
extern _rbnode_t* _rb_tree_clockwise_rotation(_rbnode_t* pt_root);

/**
 * Initialize element auxiliary function
 * @param pt_rb_tree            rb tree.
 * @param pt_node               rb node.
 * @return void.
 * @remarks if pt_rb_tree == NULL or pt_node == NULL, then the behavior is undefine. pt_rb_tree must be initialized or
 *          created by _create_rb_tree(), otherwise the behavior is undefined.
 */
extern void _rb_tree_init_elem_auxiliary(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_node);

/**
 * Element compare function auxiliary
 * @param cpt_rb_tree           rb tree.
 * @param cpv_first             first element.
 * @param cpv_second            second element.
 * @param pv_output             output.
 * @return void.
 * @remarks if cpt_rb_tree == NULL or cpv_first == NULL or cpv_second == NULL or pv_output == NULL, the behavior is
 *          undefined. cpt_rb_tree must be initialized or created by _create_rb_tree(), otherwise the behavior is
 *          undefined.
 */
extern void _rb_tree_elem_compare_auxiliary(
    const _rb_tree_t* cpt_rb_tree, const void* cpv_first, const void* cpv_second, void* pv_output);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_RB_TREE_AUX_H_ */
/** eof **/

