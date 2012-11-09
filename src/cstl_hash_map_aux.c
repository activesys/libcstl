/*
 *  The implementation of hash_map auxiliary interface.
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
#include <cstl/chash_map.h>

#include "cstl_hash_map_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
#ifndef NDEBUG
/**
 * Test the two pair is have the same type.
 */
bool_t _hash_map_same_pair_type(const pair_t* cppair_first, const pair_t* cppair_second)
{
    assert(cppair_first != NULL);
    assert(cppair_second != NULL);
    assert(_pair_is_inited(cppair_first) || _pair_is_created(cppair_first));
    assert(_pair_is_inited(cppair_second) || _pair_is_created(cppair_second));

    if (cppair_first == cppair_second) {
        return true;
    }

    return (cppair_first->_t_typeinfofirst._pt_type == cppair_second->_t_typeinfofirst._pt_type) &&
           (cppair_first->_t_typeinfofirst._t_style == cppair_second->_t_typeinfofirst._t_style) &&
           (cppair_first->_t_typeinfosecond._pt_type == cppair_second->_t_typeinfosecond._pt_type) &&
           (cppair_first->_t_typeinfosecond._t_style == cppair_second->_t_typeinfosecond._t_style) &&
           _type_is_same(cppair_first->_t_typeinfofirst._s_typename, cppair_second->_t_typeinfofirst._s_typename) &&
           _type_is_same(cppair_first->_t_typeinfosecond._s_typename, cppair_second->_t_typeinfosecond._s_typename);
}

/**
 * Test the two pair is have the same type.
 */
bool_t _hash_map_same_pair_type_ex(const pair_t* cppair_first, const pair_t* cppair_second)
{
    assert(cppair_first != NULL);
    assert(cppair_second != NULL);
    assert(_pair_is_inited(cppair_first) || _pair_is_created(cppair_first));
    assert(_pair_is_inited(cppair_second) || _pair_is_created(cppair_second));

    if (cppair_first == cppair_second) {
        return true;
    }

    return (cppair_first->_t_typeinfofirst._pt_type == cppair_second->_t_typeinfofirst._pt_type) &&
           (cppair_first->_t_typeinfofirst._t_style == cppair_second->_t_typeinfofirst._t_style) &&
           (cppair_first->_t_typeinfosecond._pt_type == cppair_second->_t_typeinfosecond._pt_type) &&
           (cppair_first->_t_typeinfosecond._t_style == cppair_second->_t_typeinfosecond._t_style) &&
           (cppair_first->_bfun_mapkeycompare == cppair_second->_bfun_mapkeycompare) &&
           (cppair_first->_bfun_mapvaluecompare == cppair_second->_bfun_mapvaluecompare) &&
           _type_is_same(cppair_first->_t_typeinfofirst._s_typename, cppair_second->_t_typeinfofirst._s_typename) &&
           _type_is_same(cppair_first->_t_typeinfosecond._s_typename, cppair_second->_t_typeinfosecond._s_typename);
}
#endif /* NDEBUG */

/**
 * hash_map key compare and value compare
 */
void _hash_map_value_compare(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    pair_t* ppair_first = NULL;
    pair_t* ppair_second = NULL;

    assert(cpv_first != NULL);
    assert(cpv_second != NULL);
    assert(pv_output != NULL);

    ppair_first = (pair_t*)cpv_first;
    ppair_second = (pair_t*)cpv_second;

    assert(_hash_map_same_pair_type_ex(ppair_first, ppair_second));

    *(bool_t*)pv_output = ppair_first->_t_typeinfofirst._pt_type->_t_typesize;
    if (ppair_first->_bfun_mapkeycompare != NULL) {
        ppair_first->_bfun_mapkeycompare(pair_first(ppair_first), pair_first(ppair_second), pv_output);
    } else {
        ppair_first->_t_typeinfofirst._pt_type->_t_typeless(ppair_first->_pv_first, ppair_second->_pv_first, pv_output);
    }
}

/**
 * hash_map default hash function.
 */
void _hash_map_default_hash(const void* cpv_input, void* pv_output)
{
    pair_t*  ppair_pair = NULL;
    _byte_t* pby_value = NULL;
    size_t   t_sum = 0;
    size_t   i = 0;
    size_t   t_len = 0;

    assert(cpv_input != NULL);
    assert(pv_output != NULL);

    ppair_pair = (pair_t*)cpv_input;
    pby_value = (_byte_t*)pair_first(ppair_pair);
    if (strncmp(ppair_pair->_t_typeinfofirst._pt_type->_s_typename, _C_STRING_TYPE, _TYPE_NAME_SIZE) == 0) {
        t_len = strlen((char*)pby_value);
    } else {
        t_len = ppair_pair->_t_typeinfofirst._pt_type->_t_typesize;
    }

    for (i = 0; i < t_len; ++i) {
        t_sum += (size_t)pby_value[i];
    }

    *(size_t*)pv_output = t_sum;
}

/** local function implementation section **/

/** eof **/

