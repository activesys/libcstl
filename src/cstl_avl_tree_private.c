/*
 *  The implementation of avl tree private functions.
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

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create avl tree container auxiliary function.
 */
bool_t _create_avl_tree_auxiliary(_avl_tree_t* pt_avl_tree, const char* s_typename)
{
    assert(pt_avl_tree != NULL);
    assert(s_typename != NULL);

    /* get type information */
    _type_get_type(&pt_avl_tree->_t_typeinfo, s_typename);
    if (pt_avl_tree->_t_typeinfo._t_style == _TYPE_INVALID) {
        return false;
    }

    pt_avl_tree->_t_avlroot._pt_parent = NULL;
    pt_avl_tree->_t_avlroot._pt_left = NULL;
    pt_avl_tree->_t_avlroot._pt_right = NULL;
    pt_avl_tree->_t_avlroot._un_height = 0;

    pt_avl_tree->_t_nodecount = 0;
    pt_avl_tree->_t_compare = NULL;

    _alloc_init(&pt_avl_tree->_t_allocator);
    return true;
}

/**
 * Destroy avl tree container auxiliary function.
 */
void _avl_tree_destroy_auxiliary(_avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);
    assert(_avl_tree_is_inited(pt_avl_tree) || _avl_tree_is_created(pt_avl_tree));

    /* destroy all elements */
    pt_avl_tree->_t_avlroot._pt_parent = _avl_tree_destroy_subtree(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;

    /* destroy allocator */
    _alloc_destroy(&pt_avl_tree->_t_allocator);

    pt_avl_tree->_t_nodecount = 0;
    pt_avl_tree->_t_compare = NULL;
}

/** local function implementation section **/

/** eof **/

