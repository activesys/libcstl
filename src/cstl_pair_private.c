/*
 *  The implemetation of pair private interface.
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
 * Create pair container.
 */
pair_t* _create_pair(const char* s_typename)
{
    pair_t*     ppair_pair = NULL;

    if ((ppair_pair = (pair_t*)malloc(sizeof(pair_t))) == NULL) {
        return NULL;
    }

    if (!_create_pair_auxiliary(ppair_pair, s_typename)) {
        free(ppair_pair);
        return NULL;
    }

    return ppair_pair;
}

/**
 * Create pair container auxiliary function.
 */
bool_t _create_pair_auxiliary(pair_t* ppair_pair, const char* s_typename)
{
    assert(ppair_pair != NULL);
    assert(s_typename != NULL);

    _type_get_type_pair(&ppair_pair->_t_typeinfofirst, &ppair_pair->_t_typeinfosecond, s_typename);
    if (ppair_pair->_t_typeinfofirst._t_style == _TYPE_INVALID ||
        ppair_pair->_t_typeinfosecond._t_style == _TYPE_INVALID) {
        return false;
    }

    ppair_pair->_pv_first = NULL;
    ppair_pair->_pv_second = NULL;

    /* this two members are only used for map key and value compare. */
    ppair_pair->_bfun_mapkeycompare = NULL;
    ppair_pair->_bfun_mapvaluecompare = NULL;

    return true;
}

/**
 * Assignment for the first element of pair.
 */
void _pair_make_first(pair_t* ppair_pair, ...)
{
    va_list val_elemlist;

    assert(ppair_pair != NULL);
    assert(_pair_is_inited(ppair_pair));

    va_start(val_elemlist, ppair_pair);
    _type_get_varg_value(&ppair_pair->_t_typeinfofirst, val_elemlist, ppair_pair->_pv_first);
    va_end(val_elemlist);
}

/**
 * Assignment for the second element of pair.
 */
void _pair_make_second(pair_t* ppair_pair, ...)
{
    va_list val_elemlist;

    assert(ppair_pair != NULL);
    assert(_pair_is_inited(ppair_pair));

    va_start(val_elemlist, ppair_pair);
    _type_get_varg_value(&ppair_pair->_t_typeinfosecond, val_elemlist, ppair_pair->_pv_second);
    va_end(val_elemlist);
}

/**
 * Destroy pair container auxiliary function.
 */
void _pair_destroy_auxiliary(pair_t* ppair_pair)
{
    assert(ppair_pair != NULL);
    assert(_pair_is_inited(ppair_pair) || _pair_is_created(ppair_pair));

    if (ppair_pair->_pv_first != NULL && ppair_pair->_pv_second != NULL) {
        bool_t b_result = false;

        /* destroy first */
        b_result = _GET_PAIR_FIRST_TYPE_SIZE(ppair_pair);
        _GET_PAIR_FIRST_TYPE_DESTROY_FUNCTION(ppair_pair)(ppair_pair->_pv_first, &b_result);
        assert(b_result);
        free(ppair_pair->_pv_first);
        ppair_pair->_pv_first = NULL;

        /* destroy second */
        b_result = _GET_PAIR_SECOND_TYPE_SIZE(ppair_pair);
        _GET_PAIR_SECOND_TYPE_DESTROY_FUNCTION(ppair_pair)(ppair_pair->_pv_second, &b_result);
        assert(b_result);
        free(ppair_pair->_pv_second);
        ppair_pair->_pv_second = NULL;
    }

    ppair_pair->_bfun_mapkeycompare = NULL;
    ppair_pair->_bfun_mapvaluecompare = NULL;
}

/**
 * Test pair is created by create_pair.
 */
bool_t _pair_is_created(const pair_t* cppair_pair)
{
    assert(cppair_pair != NULL);

    if ((cppair_pair->_t_typeinfofirst._t_style != _TYPE_C_BUILTIN &&
         cppair_pair->_t_typeinfofirst._t_style != _TYPE_CSTL_BUILTIN &&
         cppair_pair->_t_typeinfofirst._t_style != _TYPE_USER_DEFINE) ||
        (cppair_pair->_t_typeinfosecond._t_style != _TYPE_C_BUILTIN &&
         cppair_pair->_t_typeinfosecond._t_style != _TYPE_CSTL_BUILTIN &&
         cppair_pair->_t_typeinfosecond._t_style != _TYPE_USER_DEFINE)) {
        return false;
    }
    if (cppair_pair->_t_typeinfofirst._pt_type == NULL || cppair_pair->_t_typeinfosecond._pt_type == NULL) {
        return false;
    }

    if (cppair_pair->_pv_first != NULL || cppair_pair->_pv_second != NULL ||
        cppair_pair->_bfun_mapkeycompare != NULL || cppair_pair->_bfun_mapvaluecompare != NULL) {
        return false;
    }

    return true;
}

/**
 * Test pair is initialized by pair initialization functions.
 */
bool_t _pair_is_inited(const pair_t* cppair_pair)
{
    assert(cppair_pair != NULL);

    if ((cppair_pair->_t_typeinfofirst._t_style != _TYPE_C_BUILTIN &&
         cppair_pair->_t_typeinfofirst._t_style != _TYPE_CSTL_BUILTIN &&
         cppair_pair->_t_typeinfofirst._t_style != _TYPE_USER_DEFINE) ||
        (cppair_pair->_t_typeinfosecond._t_style != _TYPE_C_BUILTIN &&
         cppair_pair->_t_typeinfosecond._t_style != _TYPE_CSTL_BUILTIN &&
         cppair_pair->_t_typeinfosecond._t_style != _TYPE_USER_DEFINE)) {
        return false;
    }
    if (cppair_pair->_t_typeinfofirst._pt_type == NULL || cppair_pair->_t_typeinfosecond._pt_type == NULL) {
        return false;
    }

    if (cppair_pair->_pv_first == NULL || cppair_pair->_pv_second == NULL) {
        return false;
    }

    return true;
}

/** local function implementation section **/

/** eof **/

