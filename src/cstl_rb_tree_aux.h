/*
 *  The interface of rb tree auxiliary function.
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

#ifndef _CSTL_RB_TREE_AUX_H_
#define _CSTL_RB_TREE_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/* macros for type informations */
#define _GET_RB_TREE_TYPE_SIZE(pt_rb_tree)             ((pt_rb_tree)->_t_typeinfo._pt_type->_t_typesize)
#define _GET_RB_TREE_TYPE_NAME(pt_rb_tree)             ((pt_rb_tree)->_t_typeinfo._sz_typename)
#define _GET_RB_TREE_TYPE_BASENAME(pt_rb_tree)         ((pt_rb_tree)->_t_typeinfo._pt_type->_sz_typename)
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
 * @param cpt_rb_tree          rb tree container.
 * @return if rb tree is created by create_rb tree, then return true, else return false.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined.
 */
extern bool_t _rb_tree_is_created(const _rb_tree_t* cpt_rb_tree);

/**
 * Test rb tree is initialized by rb tree initialization functions.
 * @param cpt_rb_tree          rb tree container.
 * @return if rb tree is initialized by rb tree initialization functions, then return true, else return false.
 * @remarks if cpt_rb_tree == NULL, then the behavior is undefined.
 */
extern bool_t _rb_tree_is_inited(const _rb_tree_t* cpt_rb_tree);
/*
 * Assert support function.
 */
extern bool_t _rb_tree_iterator_belong_to_rb_tree(
    const _rb_tree_t* cpt_rb_tree, _rb_tree_iterator_t t_iter);
extern bool_t _rb_tree_same_rb_tree_iterator_type(
    const _rb_tree_t* cpt_rb_tree, _rb_tree_iterator_t t_iter);
extern bool_t _find_iterator(
    const _rbnode_t* cpt_root, const _rbnode_t* cpt_pos);
#endif /* NDEBUG */
extern bool_t _rb_tree_same_type(
    const _rb_tree_t* cpt_rb_treefirst, const _rb_tree_t* cpt_rb_treesecond);

/*
 * Destroy the subtree with postorder traverse.
 */
extern _rbnode_t* _destroy_rb_tree(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_root);

/*
 * Travel subtree for find the value in preorder.
 */
extern _rbnode_t* _find_value(
    const _rb_tree_t* cpt_rb_tree, const _rbnode_t* cpt_root, const void* cpv_value); 

/*
 * Insert the value into subtree.
 */
extern _rbnode_t* _insert_rbnode(_rb_tree_t* pt_rb_tree, const void* cpv_value);

/*
 * Rebalance the subtree.
 */
extern void _rebalance_rb_tree(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_pos);

/*
 * Rebalance the subtree after deletion.
 */
extern void _fixup_deletion(
    _rb_tree_t* pt_rb_tree, _rbnode_t* pt_pos, _rbnode_t* pt_parent);

/*
 * Get minimum and maximum rbnode pointer.
 */
extern _rbnode_t* _get_min_rbnode(const _rbnode_t* cpt_root);
extern _rbnode_t* _get_max_rbnode(const _rbnode_t* cpt_root);

/*
 * Get rb node color.
 */
extern color_t _get_color(const _rbnode_t* cpt_root);

/*
 * Left rotate and right rotate.
 */
extern _rbnode_t* _widdershins_rotate(_rbnode_t* pt_root);
extern _rbnode_t* _deasil_rotate(_rbnode_t* pt_root);

/* initiallize the element */
extern void _rb_tree_init_elem_auxiliary(_rb_tree_t* pt_rb_tree, _rbnode_t* pt_node);

/* element compare function auxiliary */
extern void _rb_tree_elem_compare_auxiliary(const _rb_tree_t* cpt_rb_tree,
    const void* cpv_first, const void* cpv_second, void* pv_output);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_RB_TREE_AUX_H_ */
/** eof **/

