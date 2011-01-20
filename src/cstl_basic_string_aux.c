/*
 *  The implementation of basic_string auxiliary functions.
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
#include <cstl/cvector.h>

#include <cstl/cstl_basic_string_iterator.h>
#include <cstl/cstl_basic_string_private.h>
#include <cstl/cstl_basic_string.h>

#include "cstl_basic_string_aux.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
#ifndef NDEBUG
bool_t _iterator_belong_to_basic_string(
    const basic_string_t* cpt_basic_string,
    basic_string_iterator_t t_iter)
{
    assert(cpt_basic_string != NULL);
    assert(_GET_BASIC_STRING_CONTAINER_TYPE(t_iter) == _BASIC_STRING_CONTAINER &&
           _GET_BASIC_STRING_ITERATOR_TYPE(t_iter) == _RANDOM_ACCESS_ITERATOR &&
           _GET_BASIC_STRING_CONTAINER(t_iter) == cpt_basic_string);

    return true;
}

bool_t _basic_string_same_type(
    const basic_string_t* cpt_basic_stringfirst,
    const basic_string_t* cpt_basic_stringsecond)
{
    assert(cpt_basic_stringfirst != NULL && cpt_basic_stringsecond != NULL);
    return _type_is_same(_GET_BASIC_STRING_TYPE_NAME(cpt_basic_stringfirst),
                         _GET_BASIC_STRING_TYPE_NAME(cpt_basic_stringsecond)) &&
           (cpt_basic_stringfirst->_t_vector._t_typeinfo._pt_type ==
            cpt_basic_stringsecond->_t_vector._t_typeinfo._pt_type);
}
#endif /* NDEBUG */

size_t _get_valuestring_len(
    const basic_string_t* cpt_basic_string, const void* cpv_valuestring)
{
    size_t t_typesize = 0;

    assert(cpt_basic_string != NULL && cpv_valuestring != NULL);

    t_typesize = _GET_BASIC_STRING_TYPE_SIZE(cpt_basic_string);
    /* char type */
    if(strncmp(_GET_BASIC_STRING_TYPE_BASENAME(cpt_basic_string),
        _CHAR_TYPE, _TYPE_NAME_SIZE) == 0)
    {
        assert(t_typesize == 1);
        return strlen(cpv_valuestring);
    }
    else
    {
        size_t t_len = 0;
        char*  pc_nullterminated = NULL;
        bool_t t_less = false;
        bool_t t_greater = false;

        pc_nullterminated = (char*)_alloc_allocate(
            &((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater, t_typesize, 1);
        assert(pc_nullterminated != NULL);
        memset(pc_nullterminated, 0x00, t_typesize);

        t_less = t_greater = t_typesize;
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            cpv_valuestring, pc_nullterminated, &t_less);
        _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
            pc_nullterminated, cpv_valuestring, &t_greater);
        while(t_less || t_greater)
        {
            t_len++;

            t_less = t_greater = t_typesize;
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                (char*)cpv_valuestring+t_len*t_typesize, pc_nullterminated, &t_less);
            _GET_BASIC_STRING_TYPE_LESS_FUNCTION(cpt_basic_string)(
                pc_nullterminated, (char*)cpv_valuestring+t_len*t_typesize, &t_greater);
        }
        
        _alloc_deallocate(&((basic_string_t*)cpt_basic_string)->_t_vector._t_allocater,
            pc_nullterminated, t_typesize, 1);

        return t_len;
    }
}

void _basic_string_get_varg_value_auxiliary(
    basic_string_t* pt_basic_string, va_list val_elemlist, void* pv_varg)
{
    _basic_string_init_elem_auxiliary(pt_basic_string, pv_varg);
    _type_get_varg_value(&pt_basic_string->_t_vector._t_typeinfo, val_elemlist, pv_varg);
}

void _basic_string_destroy_varg_value_auxiliary(
    basic_string_t* pt_basic_string, void* pv_varg)
{
    bool_t t_result = false;

    assert(pt_basic_string != NULL && pv_varg != NULL);

    t_result = _GET_BASIC_STRING_TYPE_SIZE(pt_basic_string);
    _GET_BASIC_STRING_TYPE_DESTROY_FUNCTION(pt_basic_string)(pv_varg, &t_result);
    assert(t_result);
}

/** local function implementation section **/

/** eof **/

