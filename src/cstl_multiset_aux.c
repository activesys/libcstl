/*
 *  The implementation of multiset auxiliary function.
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
#include <cstl/cset.h>

#include "cstl_multiset_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Obtain data from variable argument list, the data type and multiset element data type are same.
 */
void _multiset_get_varg_value_auxiliary(multiset_t* pmset_mset, va_list val_elemlist, void* pv_varg)
{
    assert(pmset_mset != NULL);
    assert(pv_varg != NULL);

    _multiset_init_elem_auxiliary(pmset_mset, pv_varg);
    _type_get_varg_value(&pmset_mset->_t_tree._t_typeinfo, val_elemlist, pv_varg);
}

/**
 * Destroy data, the data type and multiset element data type are same.
 */
void _multiset_destroy_varg_value_auxiliary(multiset_t* pmset_mset, void* pv_varg)
{
    bool_t b_result = false;

    assert(pmset_mset != NULL);
    assert(pv_varg != NULL);

    /* destroy varg value and free memory */
    b_result = _GET_MULTISET_TYPE_SIZE(pmset_mset);
    _GET_MULTISET_TYPE_DESTROY_FUNCTION(pmset_mset)(pv_varg, &b_result);
    assert(b_result);
}

/** local function implementation section **/

/** eof **/

