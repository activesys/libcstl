/*
 *  The implemetation of pair auxiliary function.
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
#include <cstl/cstring.h>
#include <cstl/cutility.h>

#include "cstl_pair_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/**
 * Test the two pair is have the same type.
 */
bool_t _pair_same_type(const pair_t* cppair_first, const pair_t* cppair_second)
{
    assert(cppair_first != NULL);
    assert(cppair_second != NULL);
    assert(_pair_is_inited(cppair_first) || _pair_is_created(cppair_first));
    assert(_pair_is_inited(cppair_second) || _pair_is_created(cppair_second));

    if (cppair_first == cppair_second) {
        return true;
    }

    return cppair_first->_t_typeinfofirst._pt_type == cppair_second->_t_typeinfofirst._pt_type &&
           cppair_first->_t_typeinfofirst._t_style == cppair_second->_t_typeinfofirst._t_style &&
           cppair_first->_t_typeinfosecond._pt_type == cppair_second->_t_typeinfosecond._pt_type &&
           cppair_first->_t_typeinfosecond._t_style == cppair_second->_t_typeinfosecond._t_style &&
           _type_is_same(cppair_first->_t_typeinfofirst._s_typename, cppair_second->_t_typeinfofirst._s_typename) &&
           _type_is_same(cppair_first->_t_typeinfosecond._s_typename, cppair_second->_t_typeinfosecond._s_typename);
}

/** local function implementation section **/

/** eof **/

