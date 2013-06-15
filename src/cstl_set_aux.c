/*
 *  The implementation of set auxiliary function.
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

#include "cstl_set_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Obtain data from variable argument list, the data type and set element data type are same.
 */
void _set_get_varg_value_auxiliary(set_t* pset_set, va_list val_elemlist, void* pv_varg)
{
    assert(pset_set != NULL);
    assert(pv_varg != NULL);

    _set_init_elem_auxiliary(pset_set, pv_varg);
    _type_get_varg_value(&pset_set->_t_tree._t_typeinfo, val_elemlist, pv_varg);
}

/**
 * Destroy data, the data type and set element data type are same.
 */
void _set_destroy_varg_value_auxiliary(set_t* pset_set, void* pv_varg)
{
    bool_t b_result = false;

    assert(pset_set != NULL);
    assert(pv_varg != NULL);

    /* destroy varg value and free memory */
    b_result = _GET_SET_TYPE_SIZE(pset_set);
    _GET_SET_TYPE_DESTROY_FUNCTION(pset_set)(pv_varg, &b_result);
    assert(b_result);
}

/** local function implementation section **/

/** eof **/

