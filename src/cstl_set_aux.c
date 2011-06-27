/*
 *  The implementation of set auxiliary function.
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
#include <cstl/cstl_iterator_private.h>

#ifdef CSTL_SET_AVL_TREE
#include <cstl/cstl_avl_tree_iterator.h>
#include <cstl/cstl_avl_tree_private.h>
#include <cstl/cstl_avl_tree.h>
#else
#include <cstl/cstl_rb_tree_iterator.h>
#include <cstl/cstl_rb_tree_private.h>
#include <cstl/cstl_rb_tree.h>
#endif

#include <cstl/cstl_set_iterator.h>
#include <cstl/cstl_set_private.h>
#include <cstl/cstl_set.h>

#include "cstl_set_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void _set_get_varg_value_auxiliary(set_t* pt_set, va_list val_elemlist, void* pv_varg)
{
    _set_init_elem_auxiliary(pt_set, pv_varg);
    _type_get_varg_value(&pt_set->_t_tree._t_typeinfo, val_elemlist, pv_varg);
}

void _set_destroy_varg_value_auxiliary(set_t* pt_set, void* pv_varg)
{
    /* destroy varg value and free memory */
    bool_t t_result = _GET_SET_TYPE_SIZE(pt_set);
    _GET_SET_TYPE_DESTROY_FUNCTION(pt_set)(pv_varg, &t_result);
    assert(t_result);
}

/** local function implementation section **/

/** eof **/

