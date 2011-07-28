/*
 *  The implemetation of pair private interface.
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

#include <cstl/cstl_pair_private.h>
#include <cstl/cstl_pair.h>

#include <cstl/cstring.h>

#include "cstl_pair_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* private function */
pair_t* _create_pair(const char* s_typename)
{
    pair_t*     pt_newpair = NULL;

    if((pt_newpair = (pair_t*)malloc(sizeof(pair_t))) == NULL)
    {
        return NULL;
    }

    if(!_create_pair_auxiliary(pt_newpair, s_typename))
    {
        free(pt_newpair);
        return NULL;
    }

    return pt_newpair;
}

bool_t _create_pair_auxiliary(pair_t* pt_pair, const char* s_typename)
{
    assert(pt_pair != NULL && s_typename != NULL);

    _type_get_type_pair(&pt_pair->_t_typeinfofirst, &pt_pair->_t_typeinfosecond, s_typename);
    if(pt_pair->_t_typeinfofirst._t_style == _TYPE_INVALID ||
       pt_pair->_t_typeinfosecond._t_style == _TYPE_INVALID)
    {
        return false;
    }

    pt_pair->_pv_first = NULL;
    pt_pair->_pv_second = NULL;

    /* this two members are only used for map key and value compare. */
    pt_pair->_t_mapkeycompare = NULL;
    pt_pair->_t_mapvaluecompare = NULL;

    return true;
}

void _pair_make_first(pair_t* pt_pair, ...)
{
    va_list val_elemlist;

    assert(pt_pair != NULL);
    assert(pt_pair->_pv_first != NULL && pt_pair->_pv_second != NULL);

    va_start(val_elemlist, pt_pair);
    _type_get_varg_value(&pt_pair->_t_typeinfofirst, val_elemlist, pt_pair->_pv_first);
    va_end(val_elemlist);
}

void _pair_make_second(pair_t* pt_pair, ...)
{
    va_list val_elemlist;

    assert(pt_pair != NULL);
    assert(pt_pair->_pv_first != NULL && pt_pair->_pv_second != NULL);

    va_start(val_elemlist, pt_pair);
    _type_get_varg_value(&pt_pair->_t_typeinfosecond, val_elemlist, pt_pair->_pv_second);
    va_end(val_elemlist);
}

void _pair_destroy_auxiliary(pair_t* pt_pair)
{
    bool_t t_result = false;

    assert(pt_pair != NULL);
    assert(pt_pair->_pv_first != NULL && pt_pair->_pv_second != NULL);

    /* destroy first */
    t_result = _GET_PAIR_FIRST_TYPE_SIZE(pt_pair);
    _GET_PAIR_FIRST_TYPE_DESTROY_FUNCTION(pt_pair)(pt_pair->_pv_first, &t_result);
    assert(t_result);
    free(pt_pair->_pv_first);
    pt_pair->_pv_first = NULL;

    /* destroy second */
    t_result = _GET_PAIR_SECOND_TYPE_SIZE(pt_pair);
    _GET_PAIR_SECOND_TYPE_DESTROY_FUNCTION(pt_pair)(pt_pair->_pv_second, &t_result);
    assert(t_result);
    free(pt_pair->_pv_second);
    pt_pair->_pv_second = NULL;

    pt_pair->_t_mapkeycompare = NULL;
    pt_pair->_t_mapvaluecompare = NULL;
}

/**
 * Test pair is created by create_pair.
 */
bool_t _pair_is_created(const pair_t* cppair_pair)
{
    assert(cppair_pair != NULL);

    if((cppair_pair->_t_typeinfofirst._t_style != _TYPE_C_BUILTIN &&
        cppair_pair->_t_typeinfofirst._t_style != _TYPE_CSTL_BUILTIN &&
        cppair_pair->_t_typeinfofirst._t_style != _TYPE_USER_DEFINE) ||
       (cppair_pair->_t_typeinfosecond._t_style != _TYPE_C_BUILTIN &&
        cppair_pair->_t_typeinfosecond._t_style != _TYPE_CSTL_BUILTIN &&
        cppair_pair->_t_typeinfosecond._t_style != _TYPE_USER_DEFINE))
    {
        return false;
    }
    if(cppair_pair->_t_typeinfofirst._pt_type == NULL || cppair_pair->_t_typeinfosecond._pt_type == NULL)
    {
        return false;
    }

    if(cppair_pair->_pv_first != NULL || cppair_pair->_pv_second != NULL ||
       cppair_pair->_t_mapkeycompare != NULL || cppair_pair->_t_mapvaluecompare != NULL)
    {
        return false;
    }

    return true;
}

/**
 * Test pair is initialized by pair initialization functions.
 */
bool_t _pair_is_inited(const pair_t* cppair_pair)
{
    return true;
}


/** local function implementation section **/

/** eof **/

