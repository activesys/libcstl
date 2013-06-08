/*
 *  The implementation of rb tree private interface.
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

#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>

#include "cstl_rb_tree_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Create rb tree container auxiliary function.
 */
bool_t _create_rb_tree_auxiliary(_rb_tree_t* pt_rb_tree, const char* s_typename)
{
    assert(pt_rb_tree != NULL);
    assert(s_typename != NULL);

    /* get type information */
    _type_get_type(&pt_rb_tree->_t_typeinfo, s_typename);
    if (pt_rb_tree->_t_typeinfo._t_style == _TYPE_INVALID) {
        return false;
    }

    pt_rb_tree->_t_rbroot._pt_parent = NULL;
    pt_rb_tree->_t_rbroot._pt_left = NULL;
    pt_rb_tree->_t_rbroot._pt_right = NULL;
    pt_rb_tree->_t_rbroot._t_color = _COLOR_RED;
    pt_rb_tree->_t_nodecount = 0;

    pt_rb_tree->_t_compare = NULL;

    _alloc_init(&pt_rb_tree->_t_allocator);
    return true;
}

/**
 * Destroy rb tree container auxiliary function.
 */
void _rb_tree_destroy_auxiliary(_rb_tree_t* pt_rb_tree)
{
    assert(pt_rb_tree != NULL);
    assert(_rb_tree_is_inited(pt_rb_tree) || _rb_tree_is_created(pt_rb_tree));

    /* destroy all elements */
    pt_rb_tree->_t_rbroot._pt_parent = _rb_tree_destroy_subtree(pt_rb_tree, pt_rb_tree->_t_rbroot._pt_parent);
    assert(pt_rb_tree->_t_rbroot._pt_parent == NULL);
    pt_rb_tree->_t_rbroot._pt_left = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_rbroot._pt_right = &pt_rb_tree->_t_rbroot;
    pt_rb_tree->_t_nodecount = 0;

    /* destroy allocator */
    _alloc_destroy(&pt_rb_tree->_t_allocator);

    pt_rb_tree->_t_compare = NULL;
}

/** local function implementation section **/

/** eof **/

