/*
 *  The private interface of rb tree.
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

#ifndef _CSTL_RB_TREE_PRIVATE_H_
#define _CSTL_RB_TREE_PRIVATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _RB_TREE_NODE_SIZE(typesize) ((typesize) + sizeof(_rbnode_t) - sizeof(_byte_t))

/** data type declaration and struct, union, enum section **/
typedef enum _tagcolor
{
    _COLOR_RED, _COLOR_BLACK
}_color_t;
/*
 * +-----------+
 * | parent    |
 * +-----------+
 * | left      |
 * +-----------+
 * | right     |
 * +-----------+
 * | color     |
 * +-----------+
 * | data      |
 * |   ...     |
 * +-----------+
 */
typedef struct _tagrbnode
{
    struct _tagrbnode* _pt_parent;
    struct _tagrbnode* _pt_left;
    struct _tagrbnode* _pt_right;
    _color_t           _t_color;
    _byte_t            _pby_data[1];
}_rbnode_t;

typedef struct _tagrbtree
{
    /* element type information */
    _typeinfo_t       _t_typeinfo;

    /* memory allocate */
    _alloc_t          _t_allocator;

    /* rb tree node */
    _rbnode_t         _t_rbroot;
    size_t            _t_nodecount;

    /* compare function for the inserting order */
    bfun_t            _t_compare;
}_rb_tree_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/**
 * Create rb tree container auxiliary function.
 * @param pt_rb_tree        uncreated container.
 * @param s_typename        element type name.
 * @return if create rb tree successfully return true, otherwise return false.
 * @remarks if pt_rb_tree == NULL or s_typename == NULL, then the behavior is undefined. s_typename should be C builtin
 *          type name, libcstl builtin typename or registed user defined type name, otherwise the function will return false.
 */
extern bool_t _create_rb_tree_auxiliary(_rb_tree_t* pt_rb_tree, const char* s_typename);

/**
 * Destroy rb tree container auxiliary function.
 * @param pt_rb_tree        rb tree container.
 * @return void.
 * @remarks if pt_rb_tree == NULL, then the behavior is undefined. rb tree must be initialized or created by
 *          _create_rb_tree(), otherwise the behavior is undefine.
 */
extern void _rb_tree_destroy_auxiliary(_rb_tree_t* pt_rb_tree);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_RB_TREE_PRIVATE_H_ */
/** eof **/

