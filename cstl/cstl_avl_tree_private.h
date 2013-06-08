/*
 *  The private interface of avl tree.
 *  Copyright (C)  2008 - 2013  Wangbo
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

#ifndef _CSTL_AVL_TREE_PRIVATE_H_
#define _CSTL_AVL_TREE_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _AVL_TREE_NODE_SIZE(typesize) ((typesize) + sizeof(_avlnode_t) - sizeof(_byte_t))

/** data type declaration and struct, union, enum section **/
/*
 * +-----------+
 * | parent    |
 * +-----------+
 * | left      |
 * +-----------+
 * | right     |
 * +-----------+
 * | height    |
 * +-----------+
 * | data      |
 * |   ...     |
 * +-----------+
 */
typedef struct _tagavlnode
{
    struct _tagavlnode* _pt_parent;
    struct _tagavlnode* _pt_left;
    struct _tagavlnode* _pt_right;
    unsigned int        _un_height;
    _byte_t             _pby_data[1];
}_avlnode_t;

typedef struct _tagavltree
{
    /* element type information */
    _typeinfo_t       _t_typeinfo;

    /* memory allocate */
    _alloc_t          _t_allocator;

    /* avl tree node */
    _avlnode_t        _t_avlroot;
    size_t            _t_nodecount;

    /* compare function for the inserting order */
    bfun_t            _t_compare;
}_avl_tree_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create avl tree container auxiliary function.
 * @param pt_avl_tree       uncreated container.
 * @param s_typename        element type name.
 * @return if create avl tree successfully return true, otherwise return false.
 * @remarks if pt_avl_tree == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_avl_tree_auxiliary(_avl_tree_t* pt_avl_tree, const char* s_typename);

/**
 * Destroy avl tree container auxiliary function.
 * @param pt_avl_tree       avl tree container.
 * @return void.
 * @remarks if pt_avl_tree == NULL, then the behavior is undefined. avl tree must be initialized or created by
 *          _create_avl_tree(), otherwise the behavior is undefine.
 */
extern void _avl_tree_destroy_auxiliary(_avl_tree_t* pt_avl_tree);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_AVL_TREE_PRIVATE_H_ */
/** eof **/

