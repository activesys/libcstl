/*
 *  The interface of tree test.
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
 *  Author Email: activesys.wb@gmail.com
 *                activesys@sina.com.cn
 */

#ifndef _TREE_TRAVERSE_H
#define _TREE_TRAVERSE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: test_travel_avl_tree
 *        Parameters: in) pt_root: avlnode_t*
 *                        the root.
 *                    in) pfun_op: void (*)(avlnode_t*)
 *           Returns: void
 *       Description: travel tree.
 *
 * ----------------------------------------------------------------------------
 */
extern void test_travel_avl_tree(
    avlnode_t* pt_root, size_t t_indentsize, void (*pfun_op)(avlnode_t*));

extern void test_travel_rb_tree(
    rbnode_t* pt_root, size_t t_indentsize, void (*pfun_op)(rbnode_t*));

extern void show_avlnode_info(avlnode_t* pt_root);

extern void show_rbnode_info(rbnode_t* pt_root);
extern void show_map_rbnode_info(rbnode_t* pt_root);

extern void test_travel_hashtable(vector_t* pt_vector);
extern void test_travel_hashtable_pair(vector_t* pt_vector);
#ifdef __cplusplus
}
#endif

#endif /* _TREE_TRAVERSE_H */
/** eof **/

